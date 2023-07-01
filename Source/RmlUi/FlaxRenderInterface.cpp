#include "RmlUiPlugin.h"

// Conflicts with both Flax and RmlUi Math.h
#undef RadiansToDegrees
#undef DegreesToRadians
#undef NormaliseAngle

#include "FlaxFontEngineInterface.h"
#include "FlaxRenderInterface.h"
#include "StaticIndexBuffer.h"
#include "StaticVertexBuffer.h"

#include <ThirdParty/RmlUi/Core/Context.h>
#include <ThirdParty/RmlUi/Core/Core.h>
#include <ThirdParty/RmlUi/Core/FontEngineInterface.h>

#include <Engine/Content/Assets/MaterialBase.h>
#include <Engine/Content/Assets/Shader.h>
#include <Engine/Content/Assets/Texture.h>
#include <Engine/Content/Content.h>
#include <Engine/Core/Collections/Array.h>
#include <Engine/Core/Collections/Dictionary.h>
#include <Engine/Core/Collections/HashSet.h>
#include <Engine/Core/Log.h>
#include <Engine/Core/Math/Matrix.h>
#include <Engine/Graphics/GPUContext.h>
#include <Engine/Graphics/GPUDevice.h>
#include <Engine/Graphics/GPUPipelineState.h>
#include <Engine/Graphics/Async/GPUTask.h>
#include <Engine/Graphics/Models/Types.h>
#include <Engine/Graphics/RenderTask.h>
#include <Engine/Graphics/Shaders/GPUShader.h>
#include <Engine/Graphics/Textures/GPUTexture.h>
#include <Engine/Profiler/Profiler.h>
#include <Engine/Render2D/FontManager.h>
#include <Engine/Render2D/RotatedRectangle.h>

struct BasicVertex
{
    Float2 Position;
    Half2 TexCoord;
    Color Color;
    Float2 ClipOrigin;
    RotatedRectangle ClipMask;
};

struct CompiledGeometry
{
public:
    CompiledGeometry()
        : reserved(true)
        , vertexBuffer(512, sizeof(BasicVertex), TEXT("RmlUI.VB"))
        , indexBuffer(64, sizeof(uint32), TEXT("RmlUI.IB"))
        , texture(nullptr)
        , isFont(false)
    {
    }

    ~CompiledGeometry()
    {
        Dispose(false);
    }

    void Dispose(bool preserveBuffers = true)
    {
        reserved = false;
        texture = nullptr;
        if (preserveBuffers)
        {
            vertexBuffer.Clear();
            indexBuffer.Clear();
        }
        else
        {
            vertexBuffer.Dispose();
            indexBuffer.Dispose();
        }
        isFont = false;
    }

    bool reserved;
    StaticVertexBuffer vertexBuffer;
    StaticIndexBuffer indexBuffer;
    GPUTexture* texture;
    bool isFont;
};

PACK_STRUCT(struct CustomData
{
    Matrix ViewProjection;
    Matrix Model;
    Float2 Offset;
    Float2 Dummy;
});

namespace
{
    RenderContext* CurrentRenderContext = nullptr;
    GPUContext* CurrentGPUContext = nullptr;
    Viewport CurrentViewport;
    Rectangle CurrentScissor;
    Matrix CurrentTransform;
    Matrix ViewProjection;
    bool UseScissor = false;
    AssetReference<Shader> BasicShader;
    GPUPipelineState* FontPipeline = nullptr;
    GPUPipelineState* ImagePipeline = nullptr;
    GPUPipelineState* ColorPipeline = nullptr;
    Array<CompiledGeometry*> GeometryCache(2);
    Dictionary<GPUTexture*, AssetReference<Texture>> LoadedTextureAssets(32);
    Array<GPUTexture*> LoadedTextures(32);
    Array<GPUTexture*> AllocatedTextures(32);
    HashSet<GPUTexture*> FontTextures(32);
#if !USE_RMLUI_6_0
    Dictionary<byte*, Rml::TextureHandle> AtlasGenerateTextureHandles;
#endif
}

CompiledGeometry* ReserveGeometry(Rml::CompiledGeometryHandle& geometryHandle)
{
    // Cache geometry structures in order to reduce allocations and recreating buffers
    for (int i = 1; i < GeometryCache.Count(); i++)
    {
        if (GeometryCache[i]->reserved)
            continue;

        GeometryCache[i]->reserved = true;
        geometryHandle = Rml::CompiledGeometryHandle(i);
        return GeometryCache[i];
    }

    CompiledGeometry* geometry = New<CompiledGeometry>();
    geometryHandle = Rml::CompiledGeometryHandle(GeometryCache.Count());
    GeometryCache.Add(geometry);
    return geometry;
}

void ReleaseGeometry(Rml::CompiledGeometryHandle handle)
{
    if ((int)handle == 0)
        return;
    GeometryCache[(int)handle]->Dispose();
}

FlaxRenderInterface::FlaxRenderInterface() : RenderInterface()
{
    UseScissor = true;

    Guid basicShaderGuid;
    Guid::Parse(StringAnsiView(RMLUI_PLUGIN_BASIC_SHADER), basicShaderGuid);
    BasicShader = Content::Load<Shader>(basicShaderGuid);
    if (!BasicShader)
        LOG(Error, "RmlUi: Failed to load shader with id {0}", basicShaderGuid.ToString());
    BasicShader.Get()->OnReloading.Bind<FlaxRenderInterface, &FlaxRenderInterface::InvalidateShaders>(this);

    // Handles with value of 0 are invalid, reserve the first slot in the arrays
    LoadedTextures.Add(nullptr);
    GeometryCache.Add(nullptr);
}

FlaxRenderInterface::~FlaxRenderInterface()
{
    BasicShader.Get()->OnReloading.Unbind<FlaxRenderInterface, &FlaxRenderInterface::InvalidateShaders>(this);
    InvalidateShaders();
}

void FlaxRenderInterface::InvalidateShaders(Asset* obj)
{
    SAFE_DELETE_GPU_RESOURCE(FontPipeline);
    SAFE_DELETE_GPU_RESOURCE(ImagePipeline);
    SAFE_DELETE_GPU_RESOURCE(ColorPipeline);
}

void FlaxRenderInterface::RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture_handle, const Rml::Vector2f& translation)
{
    CompiledGeometry compiledGeometry;
    CompileGeometry(&compiledGeometry, vertices, num_vertices, indices, num_indices, texture_handle);
    RenderCompiledGeometry(&compiledGeometry, translation);
}

Rml::CompiledGeometryHandle FlaxRenderInterface::CompileGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture_handle)
{
#if DISABLE_GEOMETRY_COMPILATION
    return {};
#endif

    Rml::CompiledGeometryHandle geometryHandle;
    CompiledGeometry* compiledGeometry = ReserveGeometry(geometryHandle);
    CompileGeometry(compiledGeometry, vertices, num_vertices, indices, num_indices, texture_handle);
    return (Rml::CompiledGeometryHandle)geometryHandle;
}

void FlaxRenderInterface::CompileGeometry(CompiledGeometry* compiledGeometry, Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture_handle)
{
    PROFILE_GPU_CPU("RmlUi.CompileGeometry");

    const Rectangle defaultBounds(CurrentViewport.Location, CurrentViewport.Size);
    const RotatedRectangle defaultMask(defaultBounds);

    compiledGeometry->texture = LoadedTextures.At((int32)texture_handle);
    compiledGeometry->vertexBuffer.Data.EnsureCapacity((int32)(num_vertices * sizeof(BasicVertex)));
    compiledGeometry->indexBuffer.Data.EnsureCapacity((int32)(num_indices * sizeof(uint32)));

    // FIXME: hacky way to detect if we are rendering text or images
    compiledGeometry->isFont = FontTextures.Contains(compiledGeometry->texture);

    for (int i = 0; i < num_vertices; i++)
    {
        BasicVertex vb0;
        vb0.Position = (Float2)vertices[i].position;
        vb0.TexCoord = Half2((Float2)vertices[i].tex_coord);
        vb0.Color = Color(Color32(vertices[i].colour.red, vertices[i].colour.green, vertices[i].colour.blue, vertices[i].colour.alpha));
        vb0.ClipOrigin = Float2::Zero;
        vb0.ClipMask = defaultMask;

        compiledGeometry->vertexBuffer.Write(vb0);
    }
    for (int i = 0; i < num_indices; i++)
        compiledGeometry->indexBuffer.Write((uint32)indices[i]);
}

void FlaxRenderInterface::RenderCompiledGeometry(Rml::CompiledGeometryHandle geometry, const Rml::Vector2f& translation)
{
    CompiledGeometry* compiledGeometry = GeometryCache[(int)geometry];
    if (compiledGeometry == nullptr)
        return;

    RenderCompiledGeometry(compiledGeometry, translation);
}

void FlaxRenderInterface::RenderCompiledGeometry(CompiledGeometry* compiledGeometry, const Rml::Vector2f& translation)
{
    PROFILE_GPU_CPU("RmlUi.RenderCompiledGeometry");

    compiledGeometry->vertexBuffer.Flush(CurrentGPUContext);
    compiledGeometry->indexBuffer.Flush(CurrentGPUContext);

    if (!BasicShader->IsLoaded() && BasicShader->WaitForLoaded())
        return;

    // Setup pipelines
    if (FontPipeline == nullptr || ImagePipeline == nullptr || ColorPipeline == nullptr)
    {
        bool useDepth = false;
        GPUPipelineState::Description desc = GPUPipelineState::Description::DefaultFullscreenTriangle;
        desc.DepthEnable = desc.DepthWriteEnable = useDepth;
        desc.DepthWriteEnable = false;
        desc.DepthClipEnable = false;
        desc.VS = BasicShader->GetShader()->GetVS("VS");
        desc.PS = BasicShader->GetShader()->GetPS("PS_Font");
        desc.CullMode = CullMode::TwoSided;
        desc.BlendMode = BlendingMode::AlphaBlend;

        FontPipeline = GPUDevice::Instance->CreatePipelineState();
        if (FontPipeline->Init(desc))
        {
            LOG(Error, "RmlUi: Failed to create font pipeline state");
            return;
        }

        desc.PS = BasicShader->GetShader()->GetPS("PS_Image");
        ImagePipeline = GPUDevice::Instance->CreatePipelineState();
        if (ImagePipeline->Init(desc))
        {
            LOG(Error, "RmlUi: Failed to create image pipeline state");
            return;
        }

        desc.PS = BasicShader->GetShader()->GetPS("PS_Color");
        ColorPipeline = GPUDevice::Instance->CreatePipelineState();
        if (ColorPipeline->Init(desc))
        {
            LOG(Error, "RmlUi: Failed to create color pipeline state");
            return;
        }
    }

    GPUPipelineState* pipeline;
    if (compiledGeometry->texture == nullptr)
        pipeline = ColorPipeline;
    else if (compiledGeometry->isFont)
        pipeline = FontPipeline;
    else
        pipeline = ImagePipeline;
    GPUConstantBuffer* constantBuffer = BasicShader->GetShader()->GetCB(0);
    GPUBuffer* vb = compiledGeometry->vertexBuffer.GetBuffer();
    GPUBuffer* ib = compiledGeometry->indexBuffer.GetBuffer();

    CurrentGPUContext->ResetSR();
    CurrentGPUContext->SetRenderTarget(CurrentRenderContext->Task->GetOutputView());
    if (UseScissor)
    {
        CurrentGPUContext->SetViewport(CurrentViewport);
        CurrentGPUContext->SetScissor(CurrentScissor);
    }
    else
        CurrentGPUContext->SetViewportAndScissors(CurrentViewport);
    CurrentGPUContext->FlushState();

    // Update constant buffer data
    CustomData data;
    Matrix::Transpose(ViewProjection, data.ViewProjection);
    Matrix::Transpose(CurrentTransform, data.Model);
    data.Offset = (Float2)translation;
    CurrentGPUContext->UpdateCB(constantBuffer, &data);

    // State and bindings
    CurrentGPUContext->BindCB(0, constantBuffer);
    if (compiledGeometry->texture != nullptr)
        CurrentGPUContext->BindSR(0, compiledGeometry->texture);
    CurrentGPUContext->BindVB(Span<GPUBuffer*>(&vb, 1));
    CurrentGPUContext->BindIB(ib);
    CurrentGPUContext->SetState(pipeline);

    CurrentGPUContext->DrawIndexed(compiledGeometry->indexBuffer.Data.Count() / sizeof(uint32));
}

void FlaxRenderInterface::ReleaseCompiledGeometry(Rml::CompiledGeometryHandle geometry)
{
    ReleaseGeometry(geometry);
}

void FlaxRenderInterface::EnableScissorRegion(bool enable)
{
    UseScissor = enable;
}

void FlaxRenderInterface::SetScissorRegion(int x, int y, int width, int height)
{
    CurrentScissor = Rectangle((float)x, (float)y, (float)width, (float)height);
}

bool FlaxRenderInterface::LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source)
{
    String contentPath = String(StringUtils::GetPathWithoutExtension(String(source.c_str()))) + ASSET_FILES_EXTENSION_WITH_DOT;
    AssetReference<Texture> textureAsset = Content::Load<Texture>(contentPath);
    if (textureAsset == nullptr)
        return false;

    GPUTexture* texture = textureAsset.Get()->GetTexture();
    LoadedTextureAssets.Add(texture, textureAsset);

    Float2 textureSize = textureAsset->Size();
    texture_dimensions.x = (int)textureSize.X;
    texture_dimensions.y = (int)textureSize.Y;

    texture_handle = RegisterTexture(texture);
    return true;
}

bool FlaxRenderInterface::GenerateTexture(Rml::TextureHandle& texture_handle, const Rml::byte* source, const Rml::Vector2i& source_dimensions)
{
#if !USE_RMLUI_6_0
    if (AtlasGenerateTextureHandles.TryGet(source, texture_handle))
    {
        // Texture handle was allocated in the texture callback function earlier, pass it back to the caller
        AtlasGenerateTextureHandles.Remove(source);
        return true;
    }
#endif

    GPUTextureDescription desc = GPUTextureDescription::New2D(source_dimensions.x, source_dimensions.y, PixelFormat::B8G8R8A8_UNorm);
    GPUTexture*  texture = GPUDevice::Instance->CreateTexture();
    if (texture->Init(desc))
        return false;

    texture_handle = RegisterTexture(texture);
    AllocatedTextures.Add(texture);

    BytesContainer data(source, source_dimensions.x * source_dimensions.y * 4);
    auto task = texture->UploadMipMapAsync(data, 0, true);
    if (task)
        task->Start();

    return true;
}

void FlaxRenderInterface::ReleaseTexture(Rml::TextureHandle texture_handle)
{
    GPUTexture* texture = LoadedTextures.At((int)texture_handle);
    AssetReference<Texture> textureAssetRef;
    if (LoadedTextureAssets.TryGet(texture, textureAssetRef))
    {
        textureAssetRef->DeleteObject();
        LoadedTextureAssets.Remove(texture);
    }
}

void FlaxRenderInterface::SetTransform(const Rml::Matrix4f* transform_)
{
    // We assume the library is not built with row-major matrices enabled
    CurrentTransform = transform_ != nullptr ? *(const Matrix*)transform_->data() : Matrix::Identity;
}

Viewport FlaxRenderInterface::GetViewport()
{
    return CurrentViewport;
}

void FlaxRenderInterface::SetViewport(int width, int height)
{
    CurrentViewport = Viewport(0, 0, (float)width, (float)height);
}

void FlaxRenderInterface::Begin(RenderContext* renderContext, GPUContext* gpuContext, Viewport viewport)
{
    CurrentRenderContext = renderContext;
    CurrentGPUContext = gpuContext;
    CurrentViewport = viewport;
    CurrentTransform = Matrix::Identity;
    CurrentScissor = viewport.GetBounds();

    Matrix view, projection;
    const float halfWidth = viewport.Width * 0.5f;
    const float halfHeight = viewport.Height * 0.5f;
    const float zNear = 0.0f;
    const float zFar = 1.0f;
    Matrix::OrthoOffCenter(-halfWidth, halfWidth, halfHeight, -halfHeight, zNear, zFar, projection);
    Matrix::Translation(-halfWidth, -halfHeight, 0, view);
    Matrix::Multiply(view, projection, ViewProjection);
}

void FlaxRenderInterface::End()
{
    // Flush generated glyphs to GPU
    FontManager::Flush();
    ((FlaxFontEngineInterface*)Rml::GetFontEngineInterface())->FlushFontAtlases();

    CurrentRenderContext = nullptr;
    CurrentGPUContext = nullptr;
}

Rml::TextureHandle FlaxRenderInterface::GetTextureHandle(GPUTexture* texture)
{
    if (texture == nullptr)
        return Rml::TextureHandle();

    for (int i = 1; i < LoadedTextures.Count(); i++)
    {
        if (LoadedTextures[i] == texture)
            return Rml::TextureHandle(i);
    }
    return Rml::TextureHandle();
}

Rml::TextureHandle FlaxRenderInterface::RegisterTexture(GPUTexture* texture, bool isFontTexture)
{
    Rml::TextureHandle handle = (Rml::TextureHandle)LoadedTextures.Count();
    LoadedTextures.Add(texture);

    if (isFontTexture)
        FontTextures.Add(texture);

    return handle;
}

void FlaxRenderInterface::ReleaseResources()
{
    LoadedTextureAssets.Clear();
    FontTextures.Clear();
    LoadedTextures.Clear();
    AllocatedTextures.ClearDelete();
    GeometryCache.ClearDelete();
}

#if !USE_RMLUI_6_0
void FlaxRenderInterface::AddFontAtlasTextureHandle(Rml::TextureHandle handle, byte* textureData)
{
    AtlasGenerateTextureHandles.Add(textureData, handle);
}
#endif

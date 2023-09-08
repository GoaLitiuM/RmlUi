#pragma once

#include <ThirdParty/RmlUi/Core/RenderInterface.h>
#include <Engine/Core/Math/Viewport.h>
#include <Engine/Content/AssetReference.h>

struct RenderContext;
struct CompiledGeometry;
class Asset;
class GPUContext;
class GPUTexture;
class Texture;

/// <summary>
/// The RenderInterface implementation for Flax Engine.
/// </summary>
class FlaxRenderInterface : public Rml::RenderInterface
{
public:
    friend class RmlUiPlugin;
    // [Rml::RenderInterface]
    FlaxRenderInterface();
    ~FlaxRenderInterface() override;

    void RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f& translation) override;
    Rml::CompiledGeometryHandle CompileGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture) override;
    void RenderCompiledGeometry(Rml::CompiledGeometryHandle geometry, const Rml::Vector2f& translation) override;
    void ReleaseCompiledGeometry(Rml::CompiledGeometryHandle geometry) override;
    void EnableScissorRegion(bool enable) override;
    void SetScissorRegion(int x, int y, int width, int height) override;
    bool LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source) override;
    bool GenerateTexture(Rml::TextureHandle& texture_handle, const byte* source, const Rml::Vector2i& source_dimensions) override;
    void ReleaseTexture(Rml::TextureHandle texture) override;
    void SetTransform(const Rml::Matrix4f* transform) override;

public:
    Viewport GetViewport();
    void SetViewport(int width, int height);
    void InvalidateShaders(Asset* obj = nullptr);
    void Begin(RenderContext* renderContext, GPUContext* context, Viewport viewport);
    void End();
    void CompileGeometry(CompiledGeometry* compiledGeometry, Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture_handle);
    void RenderCompiledGeometry(CompiledGeometry* compiledGeometry, const Rml::Vector2f& translation);
    Rml::TextureHandle GetTextureHandle(GPUTexture* texture);
    Rml::TextureHandle RegisterTexture(GPUTexture* texture, bool isFontTexture = false);
    void ReleaseResources();
    void DisposeCustomTextures();

#if !USE_RMLUI_6_0
    void AddFontAtlasTextureHandle(Rml::TextureHandle handle, byte* textureData);
#endif
};
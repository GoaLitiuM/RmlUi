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
    // [Rml::RenderInterface]
    FlaxRenderInterface();
    ~FlaxRenderInterface() override;

    //void RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f& translation) override;
    Rml::CompiledGeometryHandle CompileGeometry(Rml::Span<const Rml::Vertex> vertices, Rml::Span<const int> indices) override;
    void RenderGeometry(Rml::CompiledGeometryHandle geometry, Rml::Vector2f translation, Rml::TextureHandle texture) override;
    void ReleaseGeometry(Rml::CompiledGeometryHandle geometry) override;

    Rml::TextureHandle LoadTexture(Rml::Vector2i& texture_dimensions, const Rml::String& source) override;
    Rml::TextureHandle GenerateTexture(Rml::Span<const Rml::byte> source_data, Rml::Vector2i source_dimensions) override;
    void ReleaseTexture(Rml::TextureHandle texture) override;

    void EnableScissorRegion(bool enable) override;
    void SetScissorRegion(Rml::Rectanglei region) override;

    void EnableClipMask(bool enable) override;
    void RenderToClipMask(Rml::ClipMaskOperation mask_operation, Rml::CompiledGeometryHandle geometry, Rml::Vector2f translation) override;

    void SetTransform(const Rml::Matrix4f* transform) override;

    Rml::LayerHandle PushLayer() override;
    void CompositeLayers(Rml::LayerHandle source, Rml::LayerHandle destination, Rml::BlendMode blend_mode,
        Rml::Span<const Rml::CompiledFilterHandle> filters) override;
    void PopLayer() override;

    Rml::TextureHandle SaveLayerAsTexture(Rml::Vector2i dimensions) override;

    Rml::CompiledFilterHandle SaveLayerAsMaskImage() override;

    Rml::CompiledFilterHandle CompileFilter(const Rml::String& name, const Rml::Dictionary& parameters) override;
    void ReleaseFilter(Rml::CompiledFilterHandle filter) override;

    Rml::CompiledShaderHandle CompileShader(const Rml::String& name, const Rml::Dictionary& parameters) override;
    void RenderShader(Rml::CompiledShaderHandle shader_handle, Rml::CompiledGeometryHandle geometry_handle, Rml::Vector2f translation,
        Rml::TextureHandle texture) override;
    void ReleaseShader(Rml::CompiledShaderHandle effect_handle) override;

public:
    Viewport GetViewport();
    void SetViewport(int width, int height);
    void InvalidateShaders(Asset* obj = nullptr);
    void Begin(RenderContext* renderContext, GPUContext* context, Viewport viewport);
    void End();
    void CompileGeometry(CompiledGeometry* compiledGeometry, const Rml::Vertex* vertices, int num_vertices, const int* indices, int num_indices);
    void RenderCompiledGeometry(CompiledGeometry* compiledGeometry, const Rml::Vector2f& translation, Rml::TextureHandle texture);
    void HookGenerateTexture(Rml::TextureHandle textureHandle);
    Rml::TextureHandle GetTextureHandle(GPUTexture* texture);
    Rml::TextureHandle RegisterTexture(GPUTexture* texture, bool isFontTexture = false);
    void ReleaseResources();
    
private:
    Rml::TextureHandle _generateTextureOverride;
};
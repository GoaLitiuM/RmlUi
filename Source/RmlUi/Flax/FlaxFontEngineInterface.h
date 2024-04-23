#pragma once

#include <ThirdParty/RmlUi/Core/FontEngineInterface.h>
#include <ThirdParty/RmlUi/Core/RenderManager.h>
#include <ThirdParty/RmlUi/Core/Span.h>

#if !USE_RMLUI_6_0
namespace Rml
{
    struct FontMetrics
    {
        int size;
        float ascent;
        float descent;
        float line_spacing;
        float x_height;
        float underline_position;
        float underline_thickness;
    };
}
#endif

/// <summary>
/// The FontEngineInterface implementation for Flax Engine.
/// </summary>
class FlaxFontEngineInterface : public Rml::FontEngineInterface
{
public:
    // [Rml::FontEngineInterface]
    FlaxFontEngineInterface();
    void ReleaseFontResources() override;

    bool LoadFontFace(const Rml::String& file_name, bool fallback_face, Rml::Style::FontWeight weight) override;
    bool LoadFontFace(Rml::Span<const Rml::byte> data, const Rml::String& family, Rml::Style::FontStyle style, Rml::Style::FontWeight weight, bool fallback_face) override;

    Rml::FontFaceHandle GetFontFaceHandle(const Rml::String& family, Rml::Style::FontStyle style, Rml::Style::FontWeight weight, int size) override;
    Rml::FontEffectsHandle PrepareFontEffects(Rml::FontFaceHandle handle, const Rml::FontEffectList& font_effects) override;

    const Rml::FontMetrics& GetFontMetrics(Rml::FontFaceHandle handle) override;
    int GetStringWidth(Rml::FontFaceHandle handle, const Rml::String& String, const Rml::TextShapingContext& text_shaping_context, Rml::Character prior_character = Rml::Character::Null) override;
    int GenerateString(Rml::RenderManager& render_manager, Rml::FontFaceHandle face_handle, Rml::FontEffectsHandle font_effects_handle, const Rml::String& string,
        const Rml::Vector2f& position, Rml::ColourbPremultiplied colour, float opacity, const Rml::TextShapingContext& text_shaping_context,
        Rml::TexturedMeshList& mesh_list) override;

    int GetVersion(Rml::FontFaceHandle handle) override;

public:
    void FlushFontAtlases();
};
#pragma once

#include <ThirdParty/RmlUi/Core/FontEngineInterface.h>

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
    bool LoadFontFace(const Rml::byte* data, int data_size, const Rml::String& family, Rml::Style::FontStyle style, Rml::Style::FontWeight weight, bool fallback_face) override;
    Rml::FontFaceHandle GetFontFaceHandle(const Rml::String& family, Rml::Style::FontStyle style, Rml::Style::FontWeight weight, int size) override;
    Rml::FontEffectsHandle PrepareFontEffects(Rml::FontFaceHandle handle, const Rml::FontEffectList& font_effects) override;
#if USE_RMLUI_6_0
    const Rml::FontMetrics& GetFontMetrics(Rml::FontFaceHandle handle) override;
    int GetStringWidth(Rml::FontFaceHandle handle, const Rml::String& String, float letter_spacing, Rml::Character prior_character = Rml::Character::Null) override;
    int GenerateString(Rml::FontFaceHandle face_handle, Rml::FontEffectsHandle font_effects_handle, const Rml::String& String, const Rml::Vector2f& position, const Rml::Colourb& colour, float opacity, float letter_spacing, Rml::GeometryList& geometry) override;
#else
    int GetSize(Rml::FontFaceHandle handle) override;
    int GetXHeight(Rml::FontFaceHandle handle) override;
    int GetLineHeight(Rml::FontFaceHandle handle) override;
    int GetBaseline(Rml::FontFaceHandle handle) override;
    float GetUnderline(Rml::FontFaceHandle handle, float& thickness) override;
    const Rml::FontMetrics& GetFontMetrics(Rml::FontFaceHandle handle);
    int GetStringWidth(Rml::FontFaceHandle handle, const Rml::String& string, Rml::Character prior_character = Rml::Character::Null) override;
    int GenerateString(Rml::FontFaceHandle face_handle, Rml::FontEffectsHandle font_effects_handle, const Rml::String& String, const Rml::Vector2f& position, const Rml::Colourb& colour, float opacity, Rml::GeometryList& geometry) override;
#endif
    int GetVersion(Rml::FontFaceHandle handle) override;

public:
    void FlushFontAtlases();
};
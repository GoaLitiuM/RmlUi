#include "FlaxFontEngineInterface.h"
#include "FlaxRenderInterface.h"

#include <ThirdParty/RmlUi/Core/Core.h>
#include <ThirdParty/RmlUi/Core/FontEffect.h>
#include <ThirdParty/RmlUi/Core/FontGlyph.h>

#include <Engine/Content/Assets/Texture.h>
#include <Engine/Content/Content.h>
#include <Engine/Core/Collections/HashSet.h>
#include <Engine/Core/Log.h>
#include <Engine/Core/Math/Color.h>
#include <Engine/Core/Math/Color32.h>
#include <Engine/Core/Math/Rectangle.h>
#include <Engine/Core/Math/Vector2.h>
#include <Engine/Graphics/Textures/GPUTexture.h>
#include <Engine/Render2D/Font.h>
#include <Engine/Render2D/FontAsset.h>
#include <Engine/Render2D/FontManager.h>
#include <Engine/Render2D/FontTextureAtlas.h>
#include <Engine/Profiler/ProfilerCPU.h>

// FontManager scales the face size by DPI
#define DPI_ADJUSTMENT ((72.0f / DefaultDPI) / Platform::GetDpiScale())

#define EFFECT_FONT_ATLAS_SIZE 512

struct FontEffectLayer
{
    const Rml::FontEffect* effect;
    Dictionary<Char, FontCharacterEntry> characters;
};

struct FontEffect
{
    Rml::FontFaceHandle fontHandle;
    Array<FontEffectLayer> layers;
};

struct FontFace
{
    bool isFallback;
    int weight;
    Rml::Style::FontStyle style;
    int fontAssetIndex;
};

namespace
{
    Array<AssetReference<FontTextureAtlas>> EffectAtlases(4);
    Array<Rml::CallbackTexture> EffectAtlasTextures(4);
    Array<Rml::String> EffectAtlasTextureNames(4);
    Array<Rml::CallbackTexture> AtlasTextures(4);
    Array<Rml::String> AtlasTextureNames(4);
    Dictionary<StringAnsi, Array<FontFace>> FontFaces(32);
    StringAnsi FallbackFontFaceFamily;
    Array<AssetReference<FontAsset>> FontAssets;
    Dictionary<Font*, Rml::FontMetrics> FontMetrics(32);
    Array<FontEffect> FontEffects(8);
}

// RmlUi textures can be identified only by their source names, generate and cache names for the generated atlases

Rml::String GetEffectAtlasTextureNameHandle(int index)
{
    if (EffectAtlasTextureNames.Count() <= index)
    {
        StringAnsi handleName = StringAnsi::Format("GEN_EFF_ATLAS_{0}", index);
        EffectAtlasTextureNames.Add(Rml::String(handleName.Get(), handleName.Length()));
    }
    return EffectAtlasTextureNames[index];
}

Rml::String GetAtlasTextureNameHandle(int index)
{
    if (AtlasTextureNames.Count() <= index)
    {
        StringAnsi handleName = StringAnsi::Format("GEN_ATLAS_{0}", index);
        AtlasTextureNames.Add(Rml::String(handleName.Get(), handleName.Length()));
    }
    return AtlasTextureNames[index];
}

FlaxFontEngineInterface::FlaxFontEngineInterface()
{
    // Value of 0 is invalid handle, reserve it
    FontEffects.Add({0, {0}});
}

void FlaxFontEngineInterface::ReleaseFontResources()
{
    FontAssets.Clear();

    for (const auto& atlas : EffectAtlases)
        if (atlas->IsLoaded())
            atlas->DeleteObject();
    EffectAtlases.Clear();

    AtlasTextures.Clear();
    EffectAtlasTextures.Clear();
    FontMetrics.Clear();
    FontEffects.Clear();
    FontFaces.Clear();
}

Array<FontFace>* GetFontFacesForFamily(const StringAnsiView& familyName)
{
    Array<FontFace>* familyFonts = FontFaces.TryGet(familyName);
    if (familyFonts == nullptr)
    {
        FontFaces.Add(familyName, Array<FontFace>());
        familyFonts = FontFaces.TryGet(familyName);
    }
    return familyFonts;
}

bool FlaxFontEngineInterface::LoadFontFace(const Rml::String& file_name, bool fallback_face, Rml::Style::FontWeight weight)
{
    // Replace the extension with Flax asset extension
    String contentPath = String(StringUtils::GetPathWithoutExtension(String(file_name.c_str()))) + ASSET_FILES_EXTENSION_WITH_DOT;
    AssetReference<FontAsset> fontAsset = Content::Load<FontAsset>(contentPath);
    if (fontAsset == nullptr)
        return false;

    FontFlags fontStyleFlags = fontAsset->GetStyle();
    bool isItalic = EnumHasAnyFlags(fontStyleFlags, FontFlags::Italic);
    bool isBold = EnumHasAnyFlags(fontStyleFlags, FontFlags::Bold);
    if (weight == Rml::Style::FontWeight::Auto)
    {
        if (isBold)
            weight = Rml::Style::FontWeight::Bold;
        else
            weight = Rml::Style::FontWeight::Normal;
    }

    StringAnsi familyName(fontAsset->GetFamilyName().ToLower().ToStringAnsi());
    Array<FontFace>* fontFaces = GetFontFacesForFamily(familyName);

    FontFace fontFace;
    fontFace.isFallback = fallback_face;
    fontFace.weight = (int)weight;
    fontFace.style = isItalic ? Rml::Style::FontStyle::Italic : Rml::Style::FontStyle::Normal;
    fontFace.fontAssetIndex = FontAssets.Count();
    fontFaces->Add(fontFace);

    if (fallback_face)
        FallbackFontFaceFamily = familyName;

    FontAssets.Add(fontAsset);
    return true;
}

bool FlaxFontEngineInterface::LoadFontFace(Rml::Span<const Rml::byte> data, const Rml::String& family, Rml::Style::FontStyle style, Rml::Style::FontWeight weight, bool fallback_face)
{
    AssetReference<FontAsset> fontAsset = Content::CreateVirtualAsset<FontAsset>();
    BytesContainer fontData(data.begin(), (int)data.size());
    if (fontAsset->Init(fontData))
        return false;

    const StringAnsiView familyName(family.c_str(), (int)family.length());
    Array<FontFace>* fontFaces = GetFontFacesForFamily(familyName);

    FontFace fontFace;
    fontFace.isFallback = fallback_face;
    fontFace.weight = (int)weight;
    fontFace.style = style;
    fontFace.fontAssetIndex = FontAssets.Count();
    fontFaces->Add(fontFace);

    if (fallback_face)
        FallbackFontFaceFamily = familyName;

    FontAssets.Add(fontAsset);
    return true;
}

Rml::FontFaceHandle FlaxFontEngineInterface::GetFontFaceHandle(const Rml::String& family, Rml::Style::FontStyle style, Rml::Style::FontWeight weight, int size)
{
    const StringAnsiView familyName(family.c_str(), (int32)family.length());
    Array<FontFace>* fontFaces = GetFontFacesForFamily(familyName);
    int fallbackIndex = -1;
    int fallbackForBoldIndex = -1;
    AssetReference<FontAsset> fontAsset;
    for (int i = 0; i < fontFaces->Count(); i++)
    {
        FontFace& fontFace = fontFaces->At(i);
        if (fontFace.isFallback)
            fallbackIndex = i;
        if (fontFace.style == style && fontFace.weight == (int)Rml::Style::FontWeight::Normal && weight == Rml::Style::FontWeight::Bold)
            fallbackForBoldIndex = i;
        if (fontFace.style == style && fontFace.weight == (int)weight)
        {
            fontAsset = FontAssets[fontFace.fontAssetIndex];
            break;
        }
    }
    if (fontAsset == nullptr)
    {
        if (fallbackForBoldIndex >= 0) // When bold face is not found, create bold from the normal face
            fontAsset = FontAssets[fontFaces->At(fallbackForBoldIndex).fontAssetIndex];
        else if (fallbackIndex >= 0) // Prefer fallback face in the same family
            fontAsset = FontAssets[fontFaces->At(fallbackIndex).fontAssetIndex];
        else
        {
            // Use the last fallback face
            Array<FontFace>* fallbackFontFaces = GetFontFacesForFamily(FallbackFontFaceFamily);
            for (int i = fallbackFontFaces->Count() - 1; i >= 0; i--)
            {
                if (!fallbackFontFaces->At(i).isFallback)
                    continue;

                fallbackIndex = i;
                break;
            }

            if (fallbackIndex >= 0)
                fontAsset = FontAssets[fallbackFontFaces->At(fallbackIndex).fontAssetIndex];
        }
    }

    if (fontAsset == nullptr)
        return Rml::FontFaceHandle();

    Font* font;
    if (fallbackForBoldIndex >= 0)
        font = fontAsset->GetBold()->CreateFont((float)size * DPI_ADJUSTMENT);
    else
        font = fontAsset->CreateFont((float)size * DPI_ADJUSTMENT);
    return (Rml::FontFaceHandle)font;
}

Rml::FontEffectsHandle FlaxFontEngineInterface::PrepareFontEffects(Rml::FontFaceHandle font_handle, const Rml::FontEffectList& font_effects)
{
    if (font_effects.empty())
        return Rml::FontEffectsHandle();

    // Look for any existing effects with same layer setup
    for (int i = 0; i < FontEffects.Count(); i++)
    {
        if (FontEffects[i].fontHandle != font_handle)
            continue;
        if (FontEffects[i].layers.Count() != font_effects.size())
            continue;

        bool match = true;
        for (int j = 0; j < font_effects.size(); j++)
        {
            if (FontEffects[i].layers[j].effect->GetFingerprint() != font_effects[j]->GetFingerprint())
            {
                match = false;
                break;
            }
        }

        if (match)
            return (Rml::FontEffectsHandle)i;
    }

    FontEffect fontEffect;
    fontEffect.fontHandle = font_handle;
    fontEffect.layers.Resize((int32)font_effects.size());
    for (int i = 0; i < font_effects.size(); i++)
    {
        FontEffectLayer& layer = fontEffect.layers[i];
        layer.effect = font_effects[i].get();
    }

    const Rml::FontEffectsHandle effectsHandle(FontEffects.Count());
    FontEffects.Add(fontEffect);
    return effectsHandle;
}

#if !USE_RMLUI_6_0
int FlaxFontEngineInterface::GetSize(Rml::FontFaceHandle handle)
{
    return GetFontMetrics(handle).size;
}

int FlaxFontEngineInterface::GetXHeight(Rml::FontFaceHandle handle)
{
    return (int)GetFontMetrics(handle).x_height;
}

int FlaxFontEngineInterface::GetLineHeight(Rml::FontFaceHandle handle)
{
    return (int)GetFontMetrics(handle).line_spacing;
}

int FlaxFontEngineInterface::GetBaseline(Rml::FontFaceHandle handle)
{
    return (int)GetFontMetrics(handle).descent;
}

float FlaxFontEngineInterface::GetUnderline(Rml::FontFaceHandle handle, float& thickness)
{
    return GetFontMetrics(handle).underline_position;
}
#endif

const Rml::FontMetrics& FlaxFontEngineInterface::GetFontMetrics(Rml::FontFaceHandle handle)
{
    auto font = (Font*)handle;
    if (!FontMetrics.ContainsKey(font))
    {
        Rml::FontMetrics metrics;
        metrics.ascent = (float)font->GetAscender();
        metrics.descent = -(float)font->GetDescender();
        metrics.line_spacing = (float)font->GetHeight();
        metrics.size = (int)(font->GetSize() / DPI_ADJUSTMENT); // The original font size is multiplied by DPI
        metrics.underline_position = 0; // FIXME: -face->underline_position
        metrics.underline_thickness = 2; // FIXME: (float)face->underline_thickness

        FontCharacterEntry entry;
        font->GetCharacter('x', entry);
        metrics.x_height = entry.Height;

        FontMetrics.Add(font, metrics);
    }

    return FontMetrics[font];
}

int FlaxFontEngineInterface::GetStringWidth(Rml::FontFaceHandle handle, const Rml::String& str, const Rml::TextShapingContext& text_shaping_context, Rml::Character prior_character)
{
    const StringAnsiView text(str.c_str(), (int32)str.length());
    auto font = (Font*)handle;
    FontCharacterEntry entry, previous;
    float lineWidth = 0.0f;

    if (prior_character != Rml::Character::Null)
    {
        const Char c = (Char)prior_character;
        if (c != '\n')
            font->GetCharacter(c, previous);
    }

    for (int32 charIndex = 0; charIndex < text.Length(); charIndex++)
    {
        const Char c = text[charIndex];
        if (c == '\n')
            continue;

        font->GetCharacter(c, entry);

        if (!StringUtils::IsWhitespace(c) && previous.IsValid)
            lineWidth += (float)font->GetKerning(previous.Character, entry.Character);
        lineWidth += (float)entry.AdvanceX + text_shaping_context.letter_spacing;
        previous = entry;
    }
    return (int)lineWidth;
}

bool FontAtlasTextureCallback(const Rml::CallbackTextureInterface& texture_interface, const Rml::String& name)
{
    // RmlUi requests data to be generated here, but we have already copied the glyph data to the texture earlier,
    // so we prepare the texture handle pointing to the atlas texture in this callback instead of generating anything.

    PROFILE_CPU_NAMED("RmlUi.FontAtlasTextureCallback");

    FontTextureAtlas* atlas = nullptr;
    int32 fontAtlasIndex = 0;
    bool isFont = true;
    if (EffectAtlasTextureNames.Find(name, fontAtlasIndex))
    {
        atlas = EffectAtlases[fontAtlasIndex];
        isFont = false;
    }
    else if (AtlasTextureNames.Find(name, fontAtlasIndex))
        atlas = FontManager::GetAtlas(fontAtlasIndex);
    if (atlas == nullptr)
        return false;

    FlaxRenderInterface* renderInterface = (FlaxRenderInterface*)Rml::GetRenderInterface();
    GPUTexture* texture = atlas->GetTexture();
    Rml::TextureHandle texture_handle = renderInterface->GetTextureHandle(texture);
    if (!texture_handle)
        texture_handle = renderInterface->RegisterTexture(texture, isFont);

    const Float2 atlasTextureSize = atlas->GetSize();
    Rml::Vector2i texture_dimensions;
    texture_dimensions.x = (int)atlasTextureSize.X;
    texture_dimensions.y = (int)atlasTextureSize.Y;

    // HACK: Avoid copying texture data by returning the previously generated texture in GenerateTexture
    // instead of creating a new texture...
    renderInterface->HookGenerateTexture(texture_handle);
    texture_interface.GenerateTexture(Rml::Span<const Rml::byte>(), texture_dimensions);

#if !USE_RMLUI_6_0
    // HACK: We are not going to copy any data to the atlas textures here, just allocate something
    // in order to generate a unique pointer to act as a cookie for this texture handle...
    data.reset(new byte[1]);
    renderInterface->AddFontAtlasTextureHandle(texture_handle, (byte*)data.get());
    if (!texture->IsAllocated())
    {
        // Ensure the backing texture exists
        auto fontEngineInterface = (FlaxFontEngineInterface*)Rml::GetFontEngineInterface();
        fontEngineInterface->FlushFontAtlases();
    }
#endif

    return !!texture_handle;
}

Rml::TexturedMesh* GetOrAddGeometrySlot(Array<Rml::TexturedMesh>& geometryArray, Rml::Texture texture)
{
    int geometryIndex;
    for (geometryIndex = 0; geometryIndex < geometryArray.Count(); geometryIndex++)
    {
        if (geometryArray[geometryIndex].texture == texture)
            break;
    }
    if (geometryIndex < geometryArray.Count())
        return &geometryArray[geometryIndex];

    geometryArray.Resize(geometryArray.Count() + 1);
    geometryIndex = geometryArray.Count() - 1;
    Rml::TexturedMesh* geometry = &geometryArray[geometryIndex];
    geometry->texture = texture;
    return geometry;
}

void WriteCharacterRect(Float2 pointer, FontCharacterEntry& entry, Color32 color, Float2 invAtlasSize, Rml::TexturedMesh* geometry)
{
    // Calculate character size and atlas coordinates
    const float x = pointer.X + (float)entry.OffsetX;
    const float y = pointer.Y + (float)-entry.OffsetY;

    Rectangle charRect(x, y, entry.UVSize.X, entry.UVSize.Y);
    Float2 charBottomRight = charRect.GetBottomRight();
    Float2 charBottomLeft = charRect.GetBottomLeft();
    Float2 charUpperLeft = charRect.GetUpperLeft();
    Float2 charUpperRight = charRect.GetUpperRight();

    Float2 upperLeftUV = Float2(entry.UV.X, entry.UV.Y) * invAtlasSize;
    Float2 rightBottomUV = (Float2(entry.UV.X, entry.UV.Y) + Float2(entry.UVSize.X, entry.UVSize.Y)) * invAtlasSize;
    Float2 leftBottomUV = Float2(upperLeftUV.X, rightBottomUV.Y);
    Float2 rightUpperUV = Float2(rightBottomUV.X, upperLeftUV.Y);

    auto& vertices = geometry->mesh.vertices;
    auto& indices = geometry->mesh.indices;
    vertices.reserve(vertices.size() + 4);
    const auto startVertex = (int32)vertices.size();
    {
        Rml::Vertex vertex;
        vertex.position = *(Rml::Vector2f*)(&charBottomRight);
        vertex.colour = *(Rml::ColourbPremultiplied*)(&color);
        vertex.tex_coord = *(Rml::Vector2f*)(&rightBottomUV);
        vertices.push_back(vertex);
    }
    {
        Rml::Vertex vertex;
        vertex.position = *(Rml::Vector2f*)(&charBottomLeft);
        vertex.colour = *(Rml::ColourbPremultiplied*)(&color);
        vertex.tex_coord = *(Rml::Vector2f*)(&leftBottomUV);
        vertices.push_back(vertex);
    }
    {
        Rml::Vertex vertex;
        vertex.position = *(Rml::Vector2f*)(&charUpperLeft);
        vertex.colour = *(Rml::ColourbPremultiplied*)(&color);
        vertex.tex_coord = *(Rml::Vector2f*)(&upperLeftUV);
        vertices.push_back(vertex);
    }
    {
        Rml::Vertex vertex;
        vertex.position = *(Rml::Vector2f*)(&charUpperRight);
        vertex.colour = *(Rml::ColourbPremultiplied*)(&color);
        vertex.tex_coord = *(Rml::Vector2f*)(&rightUpperUV);
        vertices.push_back(vertex);
    }

    // Winding in counter-clockwise order
    indices.reserve(indices.size() + 6);
    indices.push_back(startVertex + 0);
    indices.push_back(startVertex + 1);
    indices.push_back(startVertex + 2);
    indices.push_back(startVertex + 2);
    indices.push_back(startVertex + 3);
    indices.push_back(startVertex + 0);
}



int FlaxFontEngineInterface::GenerateString(Rml::RenderManager& render_manager, Rml::FontFaceHandle handle, Rml::FontEffectsHandle font_effects_handle, const Rml::String& str,
    const Rml::Vector2f& position, Rml::ColourbPremultiplied colour, float opacity, const Rml::TextShapingContext& text_shaping_context,
    Rml::TexturedMeshList& mesh_list)
{
    const StringAnsiView text(str.c_str(), (int32)str.length());
    if (text.Length() == 0)
        return 0;

    PROFILE_CPU_NAMED("RmlUi.GenerateString");

    static Array<Rml::TexturedMesh> geometryBack;
    static Array<Rml::TexturedMesh> geometryMiddle;
    static Array<Rml::TexturedMesh> geometryFront;
    geometryBack.Resize(0);
    geometryMiddle.Resize(0);
    geometryFront.Resize(0);

    auto font = (Font*)handle;
    FontEffect* fontEffect = &FontEffects[(int)font_effects_handle];
    Color32 color(colour.red, colour.green, colour.blue, (byte)(colour.alpha / 255.0f * opacity * 255));
    FontTextureAtlas* fontAtlas = nullptr;
    byte fontAtlasIndex = 0;
    Float2 invAtlasSize = Float2::One;
    FontCharacterEntry entry, previousEntry;
    Rml::TexturedMesh* geometry = nullptr;
    Rml::TexturedMesh* geometryEffect = nullptr;
    float pointerX = position.x;
    for (int32 charIndex = 0; charIndex < text.Length(); charIndex++)
    {
        const Char c = text[charIndex];
        if (c == '\n')
            continue;

        font->GetCharacter(c, entry);

        // Check if need to select/change font atlas (since characters even in the same font may be located in different atlases)
        if (fontAtlas == nullptr || entry.TextureIndex != fontAtlasIndex)
        {
            // Get texture atlas that contains the current character
            fontAtlasIndex = entry.TextureIndex;
            fontAtlas = FontManager::GetAtlas(fontAtlasIndex);

            if (fontAtlas)
            {
                fontAtlas->EnsureTextureCreated();
                if (AtlasTextures.Count() <= fontAtlasIndex)
                {
                    // Texture data already exists, the callback only assigns the correct handle pointing to this atlas
                    auto callback = [fontAtlasIndex](const Rml::CallbackTextureInterface& texture_interface) -> bool
                        {
                            return FontAtlasTextureCallback(texture_interface, GetAtlasTextureNameHandle(fontAtlasIndex));
                        };
                    auto texture = render_manager.MakeCallbackTexture(MoveTemp(callback));
                    AtlasTextures.Add(MoveTemp(texture));
                }

                geometry = GetOrAddGeometrySlot(geometryMiddle, AtlasTextures[fontAtlasIndex]);
                invAtlasSize = 1.0f / fontAtlas->GetSize();
            }
            else
                invAtlasSize = 1.0f;
        }

        const bool isWhitespace = StringUtils::IsWhitespace(c);
        if (!isWhitespace && previousEntry.IsValid)
            pointerX += (float)font->GetKerning(previousEntry.Character, entry.Character);
        Float2 characterPosition(pointerX, position.y);
        pointerX += (float)entry.AdvanceX + text_shaping_context.letter_spacing;
        previousEntry = entry;

        if (isWhitespace)
            continue;

        // Draw the visible character to middle geometry layer
        WriteCharacterRect(characterPosition, entry, color, invAtlasSize, geometry);

        if (fontAtlas == nullptr)
            continue;

        // Generate geometry for effects
        for (auto& layer : fontEffect->layers)
        {
            PROFILE_CPU_NAMED("RmlUi.GenerateString.FontEffect");

            const Rml::FontEffect* fontEffectLayer = layer.effect;
            Array<Rml::TexturedMesh>& geometryLayer = fontEffectLayer->GetLayer() == Rml::FontEffect::Layer::Back ? geometryBack : geometryFront;

            // Multiply layer color with the text color
            Rml::Colourb layerColor = fontEffectLayer->GetColour();
            Color32 effectColor = Color32(Color(Color32(layerColor.red, layerColor.green, layerColor.blue, layerColor.alpha)) * Color(color));

            FontCharacterEntry effectEntry;
            AssetReference<FontTextureAtlas> effectFontAtlas;
            if (!layer.characters.TryGet(c, effectEntry))
            {
                // Generate new effect for this glyph
                effectEntry = entry;

                uint32 sourceGlyphWidth, sourceGlyphHeight, sourceGlyphStride;
                byte* sourceGlyphSlotData = fontAtlas->GetSlotData(entry.Slot, sourceGlyphWidth, sourceGlyphHeight, sourceGlyphStride);

                Rml::Vector2i effectGlyphOffset = Rml::Vector2i(0, 0);
                Rml::Vector2i effectGlyphSize = Rml::Vector2i((int32)sourceGlyphWidth, (int32)sourceGlyphHeight);
                Rml::FontGlyph effectGlyph; // FIXME: The glyph metrics might be needed for calculating metrics
                effectGlyph.color_format = Rml::ColorFormat::A8;
                if (!fontEffectLayer->GetGlyphMetrics(effectGlyphOffset, effectGlyphSize, effectGlyph))
                {
                    // No effect for this glyph, add a dummy entry
                    effectEntry.IsValid = false;
                    layer.characters.Add(c, effectEntry);
                }
                else
                {
                    // Copy original glyph data into sequential storage with no gaps between rows
                    static Array<byte> sourceGlyphBytes;
                    sourceGlyphBytes.Resize((int32)(sourceGlyphWidth * sourceGlyphHeight));
                    for (uint32 y = 0; y < sourceGlyphHeight; y++)
                        Platform::MemoryCopy(sourceGlyphBytes.Get() + y * sourceGlyphWidth, sourceGlyphSlotData + y * sourceGlyphStride, sourceGlyphWidth);

                    effectGlyph.color_format = Rml::ColorFormat::A8;
                    effectGlyph.bitmap_dimensions = Rml::Vector2i((int32)sourceGlyphWidth, (int32)sourceGlyphHeight);
                    effectGlyph.dimensions = Rml::Vector2i(entry.AdvanceX, entry.Height);
                    effectGlyph.advance = entry.AdvanceX;
                    effectGlyph.bearing = Rml::Vector2i(entry.AdvanceX, entry.BearingY);
                    effectGlyph.bitmap_data = sourceGlyphBytes.Get();

                    // Prepare temporary storage for generated glyph data
                    static Array<byte> effectGlyphBytes;
                    effectGlyphBytes.Resize(effectGlyphSize.x * effectGlyphSize.y * 4);

                    if (fontEffectLayer->HasUniqueTexture())
                        fontEffectLayer->GenerateGlyphTexture(effectGlyphBytes.Get(), effectGlyphSize, effectGlyphSize.x * 4, effectGlyph);
                    else
                    {
                        // Copy source glyph to effect glyph
                        byte* glyphBytes = effectGlyphBytes.Get();
                        for (uint32 y = 0; y < sourceGlyphHeight; y++)
                        {
                            for (uint32 x = 0; x < sourceGlyphWidth; x++)
                            {
                                uint32 src = (y * sourceGlyphWidth + x);
                                uint32 dst = src * 4;
                                glyphBytes[dst] = sourceGlyphBytes[src];
                                glyphBytes[dst+1] = sourceGlyphBytes[src];
                                glyphBytes[dst+2] = sourceGlyphBytes[src];
                                glyphBytes[dst+3] = sourceGlyphBytes[src];
                            }
                        }
                    }

                    // Find space for the glyph in existing atlases
                    byte effectAtlasIndex = 0;
                    FontTextureAtlasSlot* slot = nullptr;
                    for (byte i = 0; i < (byte)EffectAtlases.Count(); i++)
                    {
                        slot = EffectAtlases[i]->AddEntry(effectGlyphSize.x, effectGlyphSize.y, effectGlyphBytes);
                        if (slot != nullptr)
                        {
                            effectFontAtlas = EffectAtlases[i];
                            effectAtlasIndex = i;
                            break;
                        }
                    }
                    if (slot == nullptr)
                    {
                        // No space in existing atlases, create a new one
                        effectAtlasIndex = (byte)EffectAtlases.Count();
                        effectFontAtlas = Content::CreateVirtualAsset<FontTextureAtlas>();
                        effectFontAtlas->Setup(PixelFormat::B8G8R8A8_UNorm, FontTextureAtlas::PaddingStyle::PadWithZero);
                        effectFontAtlas->Init(EFFECT_FONT_ATLAS_SIZE, EFFECT_FONT_ATLAS_SIZE);
                        EffectAtlases.Add(effectFontAtlas);

                        // Texture data already exists, the callback only assigns the correct handle pointing to this atlas
                        auto callback = [effectAtlasIndex](const Rml::CallbackTextureInterface& texture_interface) -> bool
                            {
                                return FontAtlasTextureCallback(texture_interface, GetEffectAtlasTextureNameHandle(effectAtlasIndex));
                            };
                        auto atlasTexture = render_manager.MakeCallbackTexture(MoveTemp(callback));
                        EffectAtlasTextures.Add(MoveTemp(atlasTexture));

                        slot = effectFontAtlas->AddEntry(effectGlyphSize.x, effectGlyphSize.y, effectGlyphBytes);
                    }

                    if (slot)
                    {
                        const uint32 padding = effectFontAtlas->GetPaddingAmount();
                        effectEntry.TextureIndex = effectAtlasIndex;
                        effectEntry.UV.X = static_cast<float>(slot->X + padding);
                        effectEntry.UV.Y = static_cast<float>(slot->Y + padding);
                        effectEntry.UVSize.X = static_cast<float>(slot->Width - 2 * padding);
                        effectEntry.UVSize.Y = static_cast<float>(slot->Height - 2 * padding);
                        effectEntry.Slot = slot;
                        effectEntry.OffsetX += (int16)effectGlyphOffset.x;
                        effectEntry.OffsetY -= (int16)effectGlyphOffset.y;
                    }
                    else
                    {
                        LOG(Error, "RmlUi: Failed to add effect glyph to font atlas");
                        effectEntry.IsValid = false;
                    }
                    layer.characters.Add(c, effectEntry);
                }
            }
            if (!effectEntry.IsValid)
                continue;

            effectFontAtlas = EffectAtlases[effectEntry.TextureIndex];
            geometryEffect = GetOrAddGeometrySlot(geometryLayer, EffectAtlasTextures[effectEntry.TextureIndex]);
            WriteCharacterRect(characterPosition, effectEntry, effectColor, 1.0f / effectFontAtlas->GetSize(), geometryEffect);
        }
    }

    // Cull empty geometry collections from the list
    for (int i = 0; i < mesh_list.size(); i++)
    {
        if (!mesh_list[i].mesh.vertices.empty())
            continue;

        mesh_list.erase(mesh_list.begin() + i);
        i--;
    }

    // Insert the generated geometry to the list layer by layer
    mesh_list.reserve(mesh_list.size() + geometryBack.Count() + geometryMiddle.Count() + geometryFront.Count());
    for (Rml::TexturedMesh& geometry : geometryBack)
        mesh_list.push_back(MoveTemp(geometry));
    for (Rml::TexturedMesh& geometry : geometryMiddle)
        mesh_list.push_back(MoveTemp(geometry));
    for (Rml::TexturedMesh& geometry : geometryFront)
        mesh_list.push_back(MoveTemp(geometry));

    return (int)pointerX;
}

int FlaxFontEngineInterface::GetVersion(Rml::FontFaceHandle handle)
{
    // TODO: Invalidate existing geometry here when assets or relevant rendering settings change
    auto font = (Font*)handle;
    return 0;
}

void FlaxFontEngineInterface::FlushFontAtlases()
{
    // Flush generated effect glyphs to GPU
    for (const auto& atlas : EffectAtlases)
        atlas->Flush();
}
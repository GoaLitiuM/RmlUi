#pragma once

#include <Engine/Core/ISerializable.h>
#include <Engine/Render2D/FontAsset.h>

/// <summary>
/// Font asset information passed to RmlUi.
/// </summary>
API_STRUCT() struct RmlUiFont : ISerializable
{
    API_AUTO_SERIALIZATION();
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiFont);

    ~RmlUiFont() override
    {
    }

    /// <summary>
    /// The font asset.
    /// </summary>
    API_FIELD() AssetReference<FontAsset> Font;

    /// <summary>
    /// Use this font as fallback font when exact match of the requested font is not found.
    /// </summary>
    API_FIELD(Attributes="DefaultValue(false)") bool UseAsFallbackFont = false;

public:
    bool operator==(const RmlUiFont& other) const;
    FORCE_INLINE bool operator!=(const RmlUiFont& other) const
    {
        return !operator==(other);
    }
};

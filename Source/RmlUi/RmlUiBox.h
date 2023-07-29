#pragma once

#include <Engine/Core/Math/Vector2.h>

// Conflicts with both Flax and RmlUi Math.h
#undef RadiansToDegrees
#undef DegreesToRadians
#undef NormaliseAngle

#include <ThirdParty/RmlUi/Core/Box.h>

/// <inheritdoc />
API_ENUM(Namespace="RmlUi") enum class RmlUiBoxArea
{
    /// <inheritdoc />
    Margin = 0,

    /// <inheritdoc />
    Border = 1,

    /// <inheritdoc />
    Padding = 2,

    /// <inheritdoc />
    Content = 3,

    /// <inheritdoc />
    API_ENUM(Attributes="HideInEditor")
    NUM_AREAS = 3,

    /// <inheritdoc />
    API_ENUM(Attributes="HideInEditor")
    MAX = 3,
};

/// <inheritdoc />
API_ENUM(Namespace="RmlUi") enum class RmlUiBoxEdge
{
    /// <inheritdoc />
    Top = 0,

    /// <inheritdoc />
    Right = 1,

    /// <inheritdoc />
    Bottom = 2,

    /// <inheritdoc />
    Left = 3,

    /// <inheritdoc />
    API_ENUM(Attributes="HideInEditor")
    NUM_EDGES = 4,

    /// <inheritdoc />
    API_ENUM(Attributes="HideInEditor")
    MAX = 4,
};

/// <inheritdoc />
API_ENUM(Namespace="RmlUi") enum class RmlUiBoxDirection
{
    /// <inheritdoc />
    Vertical = 0,

    /// <inheritdoc />
    Horizontal = 1
};

/// <inheritdoc />
API_CLASS(Namespace="RmlUi") class RMLUI_API RmlUiBox
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiBox);

private:
    Rml::Box box;
    //Float2 content;
    //float area_edges[RmlUiBoxArea::NUM_AREAS][RmlUiBoxEdge::NUM_EDGES] = {};

public:
    /// <inheritdoc />
    RmlUiBox();
    /// <inheritdoc />
    RmlUiBox(const Rml::Box& box);
    /// <inheritdoc />
    explicit RmlUiBox(Float2 content);

    /// <inheritdoc />
    Float2 GetPosition(RmlUiBoxArea area = RmlUiBoxArea::Content) const;
    /// <inheritdoc />
    Float2 GetSize() const;
    /// <inheritdoc />
    Float2 GetSize(RmlUiBoxArea area) const;
    /// <inheritdoc />
    void SetContent(Float2 content);
    /// <inheritdoc />
    void SetEdge(RmlUiBoxArea area, RmlUiBoxEdge edge, float size);
    /// <inheritdoc />
    float GetEdge(RmlUiBoxArea area, RmlUiBoxEdge edge) const;
    /// <inheritdoc />
    float GetCumulativeEdge(RmlUiBoxArea area, RmlUiBoxEdge edge) const;
    /// <inheritdoc />
    float GetSizeAcross(RmlUiBoxDirection direction, RmlUiBoxArea area, RmlUiBoxArea area_end = RmlUiBoxArea::Content) const;

    bool operator==(const RmlUiBox& rhs) const;
    bool operator!=(const RmlUiBox& rhs) const;
    bool operator==(const Rml::Box& rhs) const;
    bool operator!=(const Rml::Box& rhs) const;

    operator Rml::Box&()
    {
        return box;
    }

    operator Rml::Box() const
    {
        return box;
    }
};
#pragma once

#include <Engine/Core/Math/Vector2.h>

// Conflicts with both Flax and RmlUi Math.h
#undef RadiansToDegrees
#undef DegreesToRadians
#undef NormaliseAngle

#include <ThirdParty/RmlUi/Core/Box.h>

API_ENUM(Namespace="RmlUi") enum class RmlUiBoxArea
{
    Margin = 0,
    Border = 1,
    Padding = 2,
    Content = 3,

    API_ENUM(Attributes="HideInEditor")
    NUM_AREAS = 3,

    API_ENUM(Attributes="HideInEditor")
    MAX = 3,
};

API_ENUM(Namespace="RmlUi") enum class RmlUiBoxEdge
{
    Top = 0,
    Right = 1,
    Bottom = 2,
    Left = 3,

    API_ENUM(Attributes="HideInEditor")
    NUM_EDGES = 4,

    API_ENUM(Attributes="HideInEditor")
    MAX = 4,
};

API_ENUM(Namespace="RmlUi") enum class RmlUiBoxDirection
{
    Vertical = 0,
    Horizontal = 1
};

API_CLASS(Namespace="RmlUi") class RMLUI_API RmlUiBox
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiBox);

private:
    Rml::Box box;
    //Float2 content;
    //float area_edges[RmlUiBoxArea::NUM_AREAS][RmlUiBoxEdge::NUM_EDGES] = {};

public:
    RmlUiBox();
    RmlUiBox(const Rml::Box& box);
    explicit RmlUiBox(Float2 content);

    Float2 GetPosition(RmlUiBoxArea area = RmlUiBoxArea::Content) const;
    Float2 GetSize() const;
    Float2 GetSize(RmlUiBoxArea area) const;
    void SetContent(Float2 content);
    void SetEdge(RmlUiBoxArea area, RmlUiBoxEdge edge, float size);
    float GetEdge(RmlUiBoxArea area, RmlUiBoxEdge edge) const;
    float GetCumulativeEdge(RmlUiBoxArea area, RmlUiBoxEdge edge) const;
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
#include "RmlUiBox.h"

#include "RmlUiHelpers.h"

RmlUiBox::RmlUiBox()
{
    box = Rml::Box();
}

RmlUiBox::RmlUiBox(const Rml::Box& box)
{
    this->box = box;
}

RmlUiBox::RmlUiBox(Float2 content)
{
    box = Rml::Box();
}

Float2 RmlUiBox::GetPosition(RmlUiBoxArea area) const
{
    return ToFloat2(box.GetPosition(static_cast<Rml::BoxArea>(area)));
}

Float2 RmlUiBox::GetSize() const
{
    return ToFloat2(box.GetSize());
}

Float2 RmlUiBox::GetSize(RmlUiBoxArea area) const
{
    return ToFloat2(box.GetSize(static_cast<Rml::BoxArea>(area)));
}

void RmlUiBox::SetContent(Float2 content)
{
    box.SetContent(ToVector2f(content));
}

void RmlUiBox::SetEdge(RmlUiBoxArea area, RmlUiBoxEdge edge, float size)
{
    box.SetEdge(static_cast<Rml::BoxArea>(area), static_cast<Rml::BoxEdge>(edge), size);
}

float RmlUiBox::GetEdge(RmlUiBoxArea area, RmlUiBoxEdge edge) const
{
    return box.GetEdge(static_cast<Rml::BoxArea>(area), static_cast<Rml::BoxEdge>(edge));
}

float RmlUiBox::GetCumulativeEdge(RmlUiBoxArea area, RmlUiBoxEdge edge) const
{
    return box.GetCumulativeEdge(static_cast<Rml::BoxArea>(area), static_cast<Rml::BoxEdge>(edge));
}

float RmlUiBox::GetSizeAcross(RmlUiBoxDirection direction, RmlUiBoxArea area, RmlUiBoxArea area_end) const
{
    return box.GetSizeAcross(static_cast<Rml::BoxDirection>(direction), static_cast<Rml::BoxArea>(area), static_cast<Rml::BoxArea>(area_end));
}

bool RmlUiBox::operator==(const RmlUiBox& rhs) const
{
    return box == rhs.box;
}

bool RmlUiBox::operator!=(const RmlUiBox& rhs) const
{
    return box != rhs.box;
}

bool RmlUiBox::operator==(const Rml::Box& rhs) const
{
    return box == rhs;
}

bool RmlUiBox::operator!=(const Rml::Box& rhs) const
{
    return box != rhs;
}
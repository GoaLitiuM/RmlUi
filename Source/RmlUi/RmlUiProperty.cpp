#include "RmlUiProperty.h"
#include "RmlUiTransform.h"

RmlUiProperty::RmlUiProperty(Rml::Property* property)
    : RmlUiProperty()
{
    this->property = property;
    ownedData = false;
}

RmlUiProperty::RmlUiProperty(const Rml::Property& property)
    : RmlUiProperty()
{
    this->property = New<Rml::Property>();
    *this->property = property;
    ownedData = true;
}

Matrix RmlUiProperty::GetMatrix()
{
    return ToMatrix(property->Get<Rml::Matrix4f>());
}

float RmlUiProperty::GetFloat()
{
    return property->Get<float>();
}

RmlUiTransform* RmlUiProperty::GetTransform()
{
    return New<RmlUiTransform>(property->Get<Rml::TransformPtr>());
}
#include "RmlUiProperty.h"

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
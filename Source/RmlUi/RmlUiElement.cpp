#include "RmlUiElement.h"
#include "RmlUiHelpers.h"

RmlUiElement::RmlUiElement(const SpawnParams& params)
    : Actor(params)
{
}

RmlUiElement::~RmlUiElement()
{
    wrappedChildElements.ClearDelete();
}

RmlUiElement::RmlUiElement(Rml::Element* element)
{
    this->element = element;
}

RmlUiElement* RmlUiElement::WrapChildElement(const Rml::Element* el)
{
    for (auto wrapped : wrappedChildElements)
    {
        if (wrapped->element == el)
            return wrapped;
    }
    auto wrapped = New<RmlUiElement>((Rml::Element*)el);
    wrappedChildElements.Add(wrapped);
    return wrapped;
}

RmlUiProperty* RmlUiElement::WrapProperty(const Rml::Property* property)
{
    for (auto wrapped : wrappedProperties)
    {
        if (wrapped->property == property)
            return wrapped;
    }
    auto wrapped = New<RmlUiProperty>((Rml::Property*)property);
    wrappedProperties.Add(wrapped);
    return wrapped;
}

void RmlUiElement::SetClass(const String& className, bool activate)
{
    element->SetClass(ToRmlString(className), activate);
}

bool RmlUiElement::IsClassSet(const String& className) const
{
    return element->IsClassSet(ToRmlString(className));
}

void RmlUiElement::SetClassNames(const String& classNames)
{
    element->SetClassNames(ToRmlString(classNames));
}

String RmlUiElement::GetClassNames() const
{
    return ToFlaxString(element->GetClassNames());
}

const Rml::StyleSheet* RmlUiElement::GetStyleSheet() const
{
    return element->GetStyleSheet();
}

String RmlUiElement::GetAddress(bool includePseudoClasses, bool includeParents) const
{
    return ToFlaxString(element->GetAddress(includePseudoClasses, includeParents));
}

void RmlUiElement::SetOffset(Float2 offset, RmlUiElement* offsetParent, bool offsetFixed)
{
    element->SetOffset(ToVector2f(offset), offsetParent != nullptr ? offsetParent->element : nullptr, offsetFixed);
}

Float2 RmlUiElement::GetRelativeOffset(RmlUiBoxArea area)
{
    return ToFloat2(element->GetRelativeOffset(static_cast<Rml::BoxArea>(area)));
}

Float2 RmlUiElement::GetAbsoluteOffset(RmlUiBoxArea area)
{
    return ToFloat2(element->GetAbsoluteOffset(static_cast<Rml::BoxArea>(area)));
}

bool RmlUiElement::SetProperty(const String& name, const String& value)
{
    return element->SetProperty(ToRmlString(name), ToRmlString(value));
}

bool RmlUiElement::SetProperty(RmlUiPropertyId id, const RmlUiProperty& property)
{
    return element->SetProperty(static_cast<Rml::PropertyId>(id), *property.property);
}

void RmlUiElement::RemoveProperty(const String& name)
{
    element->RemoveProperty(ToRmlString(name));
}

void RmlUiElement::RemoveProperty(RmlUiPropertyId id)
{
    element->RemoveProperty(static_cast<Rml::PropertyId>(id));
}

const RmlUiProperty* RmlUiElement::GetProperty(const String& name)
{
    return WrapProperty(element->GetProperty(ToRmlString(name)));
}

const RmlUiProperty* RmlUiElement::GetProperty(RmlUiPropertyId id)
{
    return WrapProperty(element->GetProperty(static_cast<Rml::PropertyId>(id)));
}

template <typename T>
T RmlUiElement::GetProperty(const String& name)
{
    return element->GetProperty<T>(ToRmlString(name));
}

const RmlUiProperty* RmlUiElement::GetLocalProperty(const String& name)
{
    return WrapProperty(element->GetLocalProperty(ToRmlString(name)));
}

const RmlUiProperty* RmlUiElement::GetLocalProperty(RmlUiPropertyId id)
{
    return WrapProperty(element->GetLocalProperty(static_cast<Rml::PropertyId>(id)));
}

const Dictionary<RmlUiPropertyId, RmlUiProperty*> RmlUiElement::GetLocalStyleProperties()
{
    auto dict = element->GetLocalStyleProperties();

    Dictionary<RmlUiPropertyId, RmlUiProperty*> wrappedDict;
    for (const auto& pair : dict)
        wrappedDict.Add(static_cast<RmlUiPropertyId>(pair.first), WrapProperty(&pair.second));
    return wrappedDict;
}

float RmlUiElement::ResolveNumericProperty(const RmlUiProperty& property, float baseValue)
{
    return element->ResolveNumericValue(property.property->GetNumericValue(), baseValue);
}

float RmlUiElement::ResolveNumericProperty(const String& propertyName)
{
    return element->ResolveNumericValue(element->GetProperty(ToRmlString(propertyName))->GetNumericValue(), 1);
}

float RmlUiElement::GetAbsoluteLeft()
{
    return element->GetAbsoluteLeft();
}

float RmlUiElement::GetAbsoluteTop()
{
    return element->GetAbsoluteTop();
}

float RmlUiElement::GetClientLeft()
{
    return element->GetClientLeft();
}

float RmlUiElement::GetClientTop()
{
    return element->GetClientTop();
}

float RmlUiElement::GetClientWidth()
{
    return element->GetClientWidth();
}

float RmlUiElement::GetClientHeight()
{
    return element->GetClientHeight();
}

void RmlUiElement::GetInnerRML(String& content) const
{
    Rml::String str;
    element->GetInnerRML(str);
    content = ToFlaxString(str);
}

String RmlUiElement::GetInnerRML() const
{
    return ToFlaxString(element->GetInnerRML());
}

void RmlUiElement::SetInnerRML(const String& rml)
{
    element->SetInnerRML(ToRmlString(rml));
}

RmlUiElement* RmlUiElement::GetElementById(const String& id)
{
    return WrapChildElement(element->GetElementById(ToRmlString(id)));
}

void RmlUiElement::GetElementsByTagName(Array<RmlUiElement*>& elements, const String& tag)
{
    Rml::ElementList list;
    element->GetElementsByTagName(list, ToRmlString(tag));
    for (const auto el : list)
        elements.Add(WrapChildElement(el));
}

void RmlUiElement::GetElementsByClassName(Array<RmlUiElement*>& elements, const String& className)
{
    Rml::ElementList list;
    element->GetElementsByClassName(list, ToRmlString(className));
    for (const auto el : list)
        elements.Add(WrapChildElement(el));
}

bool RmlUiElement::Animate(const String& propertyName, const RmlUiProperty& targetValue, float duration, RmlUiTween tween, int num_iterations, bool alternate_direction, float delay, const RmlUiProperty* startValue)
{
    return element->Animate(ToRmlString(propertyName), *targetValue.property, duration, tween, num_iterations, alternate_direction, delay, startValue != nullptr ? startValue->property : nullptr);
}

bool RmlUiElement::AddAnimationKey(const String& propertyName, const RmlUiProperty& targetValue, float duration, RmlUiTween tween)
{
    return element->AddAnimationKey(ToRmlString(propertyName), *targetValue.property, duration, tween);
}

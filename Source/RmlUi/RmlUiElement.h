#pragma once

#include "RmlUiBox.h"

// Conflicts with both Flax and RmlUi Math.h
#undef RadiansToDegrees
#undef DegreesToRadians
#undef NormaliseAngle

#include <ThirdParty/RmlUi/Core/Element.h>

#include <Engine/Core/Math/Vector2.h>
#include <Engine/Core/Collections/Array.h>
#include <Engine/Core/Collections/Dictionary.h>

#include <Engine/Level/Actor.h>

#include "RmlUiProperty.h"
#include "RmlUiTween.h"

API_CLASS(Namespace="RmlUi") class RMLUI_API RmlUiElement : public Actor
{
    DECLARE_SCENE_OBJECT(RmlUiElement);
protected:
	Rml::Element* element = nullptr;
	Array<RmlUiElement*> wrappedChildElements;
	Array<RmlUiProperty*> wrappedProperties;

protected:
	//RmlUiElement* WrapChildElement(const Rml::Element* element);
	RmlUiElement* WrapChildElement(const Rml::Element* element);
	RmlUiProperty* WrapProperty(const Rml::Property* property);
public:
	RmlUiElement(Rml::Element* element);
	~RmlUiElement();

    /// <summary>
    /// Returns the wrapped Rml::Element.
    /// </summary>
    FORCE_INLINE Rml::Element* GetWrappedElement() const { return element; }

    API_FUNCTION() void SetClass(const String& className, bool activate);
    API_FUNCTION() bool IsClassSet(const String& className) const;
    API_FUNCTION() void SetClassNames(const String& classNames);
    API_FUNCTION() String GetClassNames() const;

    const Rml::StyleSheet* GetStyleSheet() const;

    API_FUNCTION() String GetAddress(bool includePseudoClasses = false, bool includeParents = true) const;
    API_FUNCTION() void SetOffset(Float2 offset, RmlUiElement* offsetParent, bool offsetFixed = false);
    API_FUNCTION() Float2 GetRelativeOffset(RmlUiBoxArea area = RmlUiBoxArea::Content);
    API_FUNCTION() Float2 GetAbsoluteOffset(RmlUiBoxArea area = RmlUiBoxArea::Content);

#if false
    void SetClientArea(RmlUiBoxArea client_area);
	RmlUiBoxArea GetClientArea() const;

	void SetContentBox(Float2 content_offset, Float2 content_box);
	void SetBox(const RmlUiBox& box);
	void AddBox(const RmlUiBox& box, Float2 offset);
	const RmlUiBox& GetBox();
	const RmlUiBox& GetBox(int index, Float2& offset);
	int GetNumBoxes();

	bool GetIntrinsicDimensions(Float2& dimensions, float& ratio);

	bool IsPointWithinElement(Float2 point);

	bool IsVisible(bool include_ancestors = false) const;
	float GetZIndex() const;

	Rml::FontFaceHandle FontFaceHandle() const;
#endif
	API_FUNCTION() bool SetProperty(const String& name, const String& value);
	API_FUNCTION() bool SetProperty(RmlUiPropertyId id, const RmlUiProperty& property);
	API_FUNCTION() void RemoveProperty(const String& name);
	API_FUNCTION() void RemoveProperty(RmlUiPropertyId id);
	API_FUNCTION() const RmlUiProperty* GetProperty(const String& name);
	const RmlUiProperty* GetProperty(RmlUiPropertyId id);
	template <typename T> T GetProperty(const String& name);
	const RmlUiProperty* GetLocalProperty(const String& name);
	const RmlUiProperty* GetLocalProperty(RmlUiPropertyId id);
	API_FUNCTION() const Dictionary<RmlUiPropertyId, RmlUiProperty*> GetLocalStyleProperties();

	API_FUNCTION() float ResolveNumericProperty(const RmlUiProperty& property, float baseValue);
	API_FUNCTION() float ResolveNumericProperty(const String& propertyName);

#if false
	Float2 GetContainingBlock();
	Rml::Style::Position GetPosition();
	Rml::Style::Float GetFloat();
	Rml::Style::Display GetDisplay();
	float GetLineHeight();

	bool Project(Float2& point) const noexcept;
#endif
    API_FUNCTION() bool Animate(const String& propertyName, const RmlUiProperty& targetValue, float duration, RmlUiTween tween, int num_iterations = 1, bool alternate_direction = true, float delay = 0.0f, const RmlUiProperty* startValue = nullptr);
    API_FUNCTION() bool AddAnimationKey(const String& propertyName, const RmlUiProperty& targetValue, float duration, RmlUiTween tween);
    API_FUNCTION() bool AddAnimationKey(const String& propertyName, const RmlUiProperty& targetValue, float duration)
    {
        return AddAnimationKey(propertyName, targetValue, duration, new RmlUiTween());
    }
#if false
	Rml::PropertiesIteratorView IterateLocalProperties() const;

	void SetPseudoClass(const Rml::String& pseudo_class, bool activate);
	bool IsPseudoClassSet(const Rml::String& pseudo_class) const;
	bool ArePseudoClassesSet(const Rml::StringList& pseudo_classes) const;
	Rml::StringList GetActivePseudoClasses() const;

	template< typename T >
	void SetAttribute(const Rml::String& name, const T& value);
	Variant* GetAttribute(const Rml::String& name);
	const Variant* GetAttribute(const Rml::String& name) const;
	template< typename T >
	T GetAttribute(const Rml::String& name, const T& default_value) const;
	bool HasAttribute(const Rml::String& name) const;
	void RemoveAttribute(const Rml::String& name);
	void SetAttributes(const Rml::ElementAttributes& attributes);
	const Rml::ElementAttributes& GetAttributes() const; //{ return element->GetAttributes(); }
	int GetNumAttributes() const;

	Rml::Element* GetFocusLeafNode();

	Rml::Context* GetContext() const;

	const Rml::String& GetTagName() const;

	const Rml::String& GetId() const;
	void SetId(const Rml::String& id);

#endif
	API_FUNCTION() float GetAbsoluteLeft();
	API_FUNCTION() float GetAbsoluteTop();

	API_FUNCTION() float GetClientLeft();
	API_FUNCTION() float GetClientTop();
	API_FUNCTION() float GetClientWidth();
	API_FUNCTION() float GetClientHeight();
#if false

	Rml::Element* GetOffsetParent();
	float GetOffsetLeft();
	float GetOffsetTop();
	float GetOffsetWidth();
	float GetOffsetHeight();

	float GetScrollLeft();
	void SetScrollLeft(float scroll_left);
	float GetScrollTop();
	void SetScrollTop(float scroll_top);
	float GetScrollWidth();
	float GetScrollHeight();

	Rml::ElementStyle* GetStyle() const;

	Rml::ElementDocument* GetOwnerDocument() const;

	Rml::Element* GetParentNode() const;
	Rml::Element* Closest(const Rml::String& selectors) const;

	Rml::Element* GetNextSibling() const;
	Rml::Element* GetPreviousSibling() const;

	Rml::Element* GetFirstChild() const;
	Rml::Element* GetLastChild() const;
	Rml::Element* GetChild(int index) const;
	int GetNumChildren(bool include_non_dom_elements = false) const;
#endif
	API_FUNCTION() void GetInnerRML(String& content) const;
	API_FUNCTION() String GetInnerRML() const;
	API_FUNCTION() void SetInnerRML(const String& rml);
#if false

	bool Focus();
	void Blur();
	void Click();

	void AddEventListener(const Rml::String& event, Rml::EventListener* listener, bool in_capture_phase = false);
	void AddEventListener(Rml::EventId id, Rml::EventListener* listener, bool in_capture_phase = false);
	void RemoveEventListener(const Rml::String& event, Rml::EventListener* listener, bool in_capture_phase = false);
	void RemoveEventListener(Rml::EventId id, Rml::EventListener* listener, bool in_capture_phase = false);
	bool DispatchEvent(const Rml::String& type, const Rml::Dictionary& parameters);
	bool DispatchEvent(const Rml::String& type, const Rml::Dictionary& parameters, bool interruptible, bool bubbles = true);
	bool DispatchEvent(Rml::EventId id, const Rml::Dictionary& parameters);

	void ScrollIntoView(Rml::ScrollIntoViewOptions options);
	void ScrollIntoView(bool align_with_top = true);
	void ScrollTo(Float2 offset, Rml::ScrollBehavior behavior = Rml::ScrollBehavior::Instant);

	Rml::Element* AppendChild(Rml::ElementPtr element, bool dom_element = true);
	Rml::Element* InsertBefore(Rml::ElementPtr element, Rml::Element* adjacent_element);
	Rml::ElementPtr ReplaceChild(Rml::ElementPtr inserted_element, Rml::Element* replaced_element);
	Rml::ElementPtr RemoveChild(Rml::Element* element);
	bool HasChildNodes() const;
#endif

	API_FUNCTION() RmlUiElement* GetElementById(const String& id);
	API_FUNCTION() void GetElementsByTagName(Array<RmlUiElement*>& elements, const String& tag);
	API_FUNCTION() void GetElementsByClassName(Array<RmlUiElement*>& elements, const String& className);

#if false
	Rml::Element* QuerySelector(const Rml::String& selector);
	void QuerySelectorAll(Rml::ElementList& elements, const Rml::String& selectors);

	Rml::EventDispatcher* GetEventDispatcher() const;
	Rml::String GetEventDispatcherSummary() const;
	Rml::ElementDecoration* GetElementDecoration() const;
	Rml::ElementScroll* GetElementScroll() const;
	Rml::Element* GetClosestScrollableContainer();
	const Rml::TransformState* GetTransformState() const noexcept;
	Rml::DataModel* GetDataModel() const;
	Rml::RenderInterface* GetRenderInterface();
	void SetInstancer(Rml::ElementInstancer* instancer);
	void ProcessDefaultAction(Rml::Event& event);
	const Rml::ComputedValues& GetComputedValues() const;
#endif
};
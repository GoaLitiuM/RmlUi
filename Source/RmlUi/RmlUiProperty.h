#pragma once

#include <Engine/Core/Config.h>
#include <Engine/Core/Types/BaseTypes.h>

#include <ThirdParty/RmlUi/Core/Property.h>
#include <ThirdParty/RmlUi/Core/Colour.h>

#include <Engine/Core/Types/String.h>
#include <Engine/Core/Math/Color.h>
#include <Engine/Core/Math/Color32.h>
#include <Engine/Scripting/ScriptingObject.h>

#include "RmlUiHelpers.h"

/// <inheritdoc />
API_ENUM(Namespace="RmlUi") enum class RmlUiShorthandId : uint8
{
    /// <inheritdoc />
    Invalid,

    /// <inheritdoc />
    Margin,
    /// <inheritdoc />
    Padding,
    /// <inheritdoc />
    BorderWidth,
    /// <inheritdoc />
    BorderColor,
    /// <inheritdoc />
    BorderTop,
    /// <inheritdoc />
    BorderRight,
    /// <inheritdoc />
    BorderBottom,
    /// <inheritdoc />
    BorderLeft,
    /// <inheritdoc />
    Border,
    /// <inheritdoc />
    BorderRadius,
    /// <inheritdoc />
    Overflow,
    /// <inheritdoc />
    Background,
    /// <inheritdoc />
    Font,
    /// <inheritdoc />
    Gap,
    /// <inheritdoc />
    PerspectiveOrigin,
    /// <inheritdoc />
    TransformOrigin,
    /// <inheritdoc />
    Flex,
    /// <inheritdoc />
    FlexFlow,
    /// <inheritdoc />

    /// <inheritdoc />
    NumDefinedIds,
    /// <inheritdoc />
    FirstCustomId = NumDefinedIds,

    /// <inheritdoc />
    MaxNumIds = 0xff
};

/// <inheritdoc />
API_ENUM(Namespace="RmlUi") enum class RmlUiPropertyId : uint8
{
    /// <inheritdoc />
    Invalid,

    /// <inheritdoc />
    MarginTop,
    /// <inheritdoc />
    MarginRight,
    /// <inheritdoc />
    MarginBottom,
    /// <inheritdoc />
    MarginLeft,
    /// <inheritdoc />
    PaddingTop,
    /// <inheritdoc />
    PaddingRight,
    /// <inheritdoc />
    PaddingBottom,
    /// <inheritdoc />
    PaddingLeft,
    /// <inheritdoc />
    BorderTopWidth,
    /// <inheritdoc />
    BorderRightWidth,
    /// <inheritdoc />
    BorderBottomWidth,
    /// <inheritdoc />
    BorderLeftWidth,
    /// <inheritdoc />
    BorderTopColor,
    /// <inheritdoc />
    BorderRightColor,
    /// <inheritdoc />
    BorderBottomColor,
    /// <inheritdoc />
    BorderLeftColor,
    /// <inheritdoc />
    BorderTopLeftRadius,
    /// <inheritdoc />
    BorderTopRightRadius,
    /// <inheritdoc />
    BorderBottomRightRadius,
    /// <inheritdoc />
    BorderBottomLeftRadius,
    /// <inheritdoc />
    Display,
    /// <inheritdoc />
    Position,
    /// <inheritdoc />
    Top,
    /// <inheritdoc />
    Right,
    /// <inheritdoc />
    Bottom,
    /// <inheritdoc />
    Left,
    /// <inheritdoc />
    Float,
    /// <inheritdoc />
    Clear,
    /// <inheritdoc />
    BoxSizing,
    /// <inheritdoc />
    ZIndex,
    /// <inheritdoc />
    Width,
    /// <inheritdoc />
    MinWidth,
    /// <inheritdoc />
    MaxWidth,
    /// <inheritdoc />
    Height,
    /// <inheritdoc />
    MinHeight,
    /// <inheritdoc />
    MaxHeight,
    /// <inheritdoc />
    LineHeight,
    /// <inheritdoc />
    VerticalAlign,
    /// <inheritdoc />
    OverflowX,
    /// <inheritdoc />
    OverflowY,
    /// <inheritdoc />
    Clip,
    /// <inheritdoc />
    Visibility,
    /// <inheritdoc />
    BackgroundColor,
    /// <inheritdoc />
    Color,
    /// <inheritdoc />
    CaretColor,
    /// <inheritdoc />
    ImageColor,
    /// <inheritdoc />
    FontFamily,
    /// <inheritdoc />
    FontStyle,
    /// <inheritdoc />
    FontWeight,
    /// <inheritdoc />
    FontSize,
    /// <inheritdoc />
    TextAlign,
    /// <inheritdoc />
    TextDecoration,
    /// <inheritdoc />
    TextTransform,
    /// <inheritdoc />
    WhiteSpace,
    /// <inheritdoc />
    WordBreak,
    /// <inheritdoc />
    RowGap,
    /// <inheritdoc />
    ColumnGap,
    /// <inheritdoc />
    Cursor,
    /// <inheritdoc />
    Drag,
    /// <inheritdoc />
    TabIndex,
    /// <inheritdoc />
    ScrollbarMargin,
    /// <inheritdoc />
    OverscrollBehavior,

    /// <inheritdoc />
    Perspective,
    /// <inheritdoc />
    PerspectiveOriginX,
    /// <inheritdoc />
    PerspectiveOriginY,
    /// <inheritdoc />
    Transform,
    /// <inheritdoc />
    TransformOriginX,
    /// <inheritdoc />
    TransformOriginY,
    /// <inheritdoc />
    TransformOriginZ,

    /// <inheritdoc />
    Transition,
    /// <inheritdoc />
    Animation,

    /// <inheritdoc />
    Opacity,
    /// <inheritdoc />
    PointerEvents,
    /// <inheritdoc />
    Focus,

    /// <inheritdoc />
    Decorator,
    /// <inheritdoc />
    FontEffect,

    /// <inheritdoc />
    FillImage,

    /// <inheritdoc />
    AlignContent,
    /// <inheritdoc />
    AlignItems,
    /// <inheritdoc />
    AlignSelf,
    /// <inheritdoc />
    FlexBasis,
    /// <inheritdoc />
    FlexDirection,
    /// <inheritdoc />
    FlexGrow,
    /// <inheritdoc />
    FlexShrink,
    /// <inheritdoc />
    FlexWrap,
    /// <inheritdoc />
    JustifyContent,

    /// <inheritdoc />
    NumDefinedIds,
    /// <inheritdoc />
    FirstCustomId = NumDefinedIds,

    /// <inheritdoc />
    MaxNumIds = 128
};

/// <inheritdoc />
API_ENUM(Namespace="RmlUi") enum class RmlUiMediaQueryId : uint8
{
    /// <inheritdoc />
    Invalid,

    /// <inheritdoc />
    Width,
    /// <inheritdoc />
    MinWidth,
    /// <inheritdoc />
    MaxWidth,
    /// <inheritdoc />
    Height,
    /// <inheritdoc />
    MinHeight,
    /// <inheritdoc />
    MaxHeight,
    /// <inheritdoc />
    AspectRatio,
    /// <inheritdoc />
    MinAspectRatio,
    /// <inheritdoc />
    MaxAspectRatio,
    /// <inheritdoc />
    Resolution,
    /// <inheritdoc />
    MinResolution,
    /// <inheritdoc />
    MaxResolution,
    /// <inheritdoc />
    Orientation,
    /// <inheritdoc />
    Theme,

    /// <inheritdoc />
    NumDefinedIds
};

/// <inheritdoc />
API_ENUM(Namespace="RmlUi") enum class RmlUiEventId : uint16
{
    /// <inheritdoc />
    Invalid,

    /// <inheritdoc />
    Mousedown,
    /// <inheritdoc />
    Mousescroll,
    /// <inheritdoc />
    Mouseover,
    /// <inheritdoc />
    Mouseout,
    /// <inheritdoc />
    Focus,
    /// <inheritdoc />
    Blur,
    /// <inheritdoc />
    Keydown,
    /// <inheritdoc />
    Keyup,
    /// <inheritdoc />
    Textinput,
    /// <inheritdoc />
    Mouseup,
    /// <inheritdoc />
    Click,
    /// <inheritdoc />
    Dblclick,
    /// <inheritdoc />
    Load,
    /// <inheritdoc />
    Unload,
    /// <inheritdoc />
    Show,
    /// <inheritdoc />
    Hide,
    /// <inheritdoc />
    Mousemove,
    /// <inheritdoc />
    Dragmove,
    /// <inheritdoc />
    Drag,
    /// <inheritdoc />
    Dragstart,
    /// <inheritdoc />
    Dragover,
    /// <inheritdoc />
    Dragdrop,
    /// <inheritdoc />
    Dragout,
    /// <inheritdoc />
    Dragend,
    /// <inheritdoc />
    Handledrag,
    /// <inheritdoc />
    Resize,
    /// <inheritdoc />
    Scroll,
    /// <inheritdoc />
    Animationend,
    /// <inheritdoc />
    Transitionend,

    /// <inheritdoc />
    Change,
    /// <inheritdoc />
    Submit,
    /// <inheritdoc />
    Tabchange,
    /// <inheritdoc />
    Columnadd,
    /// <inheritdoc />
    Rowadd,
    /// <inheritdoc />
    Rowchange,
    /// <inheritdoc />
    Rowremove,
    /// <inheritdoc />
    Rowupdate,

    /// <inheritdoc />
    NumDefinedIds,
    /// <inheritdoc />
    FirstCustomId = NumDefinedIds,

    /// <inheritdoc />
    MaxNumIds = 0xffff
};

/// <inheritdoc />
API_ENUM(Namespace="RmlUi", Attributes = "Flags") enum class RmlUiUnit
{
    /// <inheritdoc />
    Unknown = 1 << 0,

    /// <inheritdoc />
    Keyword = 1 << 1,

    /// <inheritdoc />
    String = 1 << 2,

    /// <inheritdoc />
    Number = 1 << 3,
    /// <inheritdoc />
    Px = 1 << 4,
    /// <inheritdoc />
    Deg = 1 << 5,
    /// <inheritdoc />
    Rad = 1 << 6,
    /// <inheritdoc />
    Colour = 1 << 7,
    /// <inheritdoc />
    Dp = 1 << 8,
    /// <inheritdoc />
    X = 1 << 9,
    /// <inheritdoc />
    Vw = 1 << 10,
    /// <inheritdoc />
    Vh = 1 << 11,
    /// <inheritdoc />
    AbsoluteUnit = Number | Px | Dp | X | Deg | Rad | Colour | Vw | Vh,

    /// <inheritdoc />
    Em = 1 << 12,
    /// <inheritdoc />
    Percent = 1 << 13,
    /// <inheritdoc />
    Rem = 1 << 14,
    /// <inheritdoc />
    RelativeUnit = Em | Rem | Percent,

    /// <inheritdoc />
    Inch = 1 << 15,
    /// <inheritdoc />
    Cm = 1 << 16,
    /// <inheritdoc />
    Mm = 1 << 17,
    /// <inheritdoc />
    Pt = 1 << 18,
    /// <inheritdoc />
    Pc = 1 << 19,
    /// <inheritdoc />
    PpiUnit = Inch | Cm | Mm | Pt | Pc,
    /// <inheritdoc />

    /// <inheritdoc />
    Transform = 1 << 20,
    /// <inheritdoc />
    Transition = 1 << 21,
    /// <inheritdoc />
    Animation = 1 << 22,
    /// <inheritdoc />
    Decorator = 1 << 23,
    /// <inheritdoc />
    FontEffect = 1 << 24,
    /// <inheritdoc />
    Ratio = 1 << 25,

    /// <inheritdoc />
    Length = Px | Dp | PpiUnit | Em | Rem | Vw | Vh | X,
    /// <inheritdoc />
    LengthPercent = Length | Percent,
    /// <inheritdoc />
    NumberLengthPercent = Number | Length | Percent,
    /// <inheritdoc />
    AbsoluteLength = Px | Dp | PpiUnit | Vh | Vw | X,
    /// <inheritdoc />
    Angle = Deg | Rad
};

/// <inheritdoc />
API_STRUCT(Namespace="RmlUi") struct RMLUI_API RmlUiPropertySource
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiPropertySource);

    RmlUiPropertySource(String path, int line_number, String rule_name)
        : path(path), lineNumber(line_number), ruleName(rule_name)
    {
    }
    RmlUiPropertySource() = default;

    String path;
    int lineNumber;
    String ruleName;
};

/// <inheritdoc />
API_CLASS(Namespace="RmlUi") class RMLUI_API RmlUiProperty : public ScriptingObject
{
    DECLARE_SCRIPTING_TYPE_WITH_CONSTRUCTOR_IMPL(RmlUiProperty, ScriptingObject);
private:
    Rml::Property* property = nullptr;
    bool ownedData = false;

public:
    friend class RmlUiElement;

    /*RmlUiProperty()
        : ScriptingObject(SpawnParams(Guid::New(), TypeInitializer))
    {
    }*/

    ~RmlUiProperty()
    {
        if (ownedData)
            Delete(property);
    }

    // Generate custom constructors for C# class
    API_INJECT_CODE(csharp, "\
namespace RmlUi\
{\
public partial class RmlUiProperty\
{\
    public RmlUiProperty(float value, RmlUiUnit unit, int specificity = -1)\
    {\
        NewPropertyInternal(this, value, unit, specificity);\
    }\
    public RmlUiProperty(Color value, RmlUiUnit unit = RmlUiUnit.Colour, int specificity = -1)\
    {\
        NewPropertyInternal(this, value, unit, specificity);\
    }\
    public RmlUiProperty(Color32 value, RmlUiUnit unit = RmlUiUnit.Colour, int specificity = -1)\
    {\
        NewPropertyInternal(this, value, unit, specificity);\
    }\
}\
}")

    API_FUNCTION(Private) static void NewPropertyInternal(RmlUiProperty* prop, float value, RmlUiUnit unit, int specificity = -1)
    {
        prop->property = New<Rml::Property>(value, static_cast<Rml::Unit>(unit), specificity);
        prop->ownedData = true;
    }

    API_FUNCTION(Private) static void NewPropertyInternal(RmlUiProperty* prop, Color value, RmlUiUnit unit, int specificity = -1)
    {
        prop->property = New<Rml::Property>(Rml::Colourb((Rml::byte)(value.R * 255), (Rml::byte)(value.G * 255), (Rml::byte)(value.B * 255), (Rml::byte)(value.A * 255)), static_cast<Rml::Unit>(unit), specificity);
        prop->ownedData = true;
    }

    API_FUNCTION(Private) static void NewPropertyInternal(RmlUiProperty* prop, Color32 value, RmlUiUnit unit, int specificity = -1)
    {
        prop->property = New<Rml::Property>(Rml::Colourb(value.R, value.G, value.B, value.A), static_cast<Rml::Unit>(unit), specificity);
        prop->ownedData = true;
    }

    RmlUiProperty(Rml::Property* property);

    RmlUiProperty(const Rml::Property& property);

    operator Rml::Property*& ()
    {
        return property;
    }

    operator Rml::Property* () const
    {
        return property;
    }

    API_FUNCTION() Matrix GetMatrix();

    API_FUNCTION() float GetFloat();

    API_FUNCTION() class RmlUiTransform* GetTransform();

    /*
        API_FIELD() Variant& GetValue();
        API_FIELD() RmlUiUnit GetUnit();
        API_FIELD() int32 GetSpecificity();
        API_FIELD() byte* GetDefinition(); // PropertyDefinition*
        API_FIELD() int32 GetParserIndex();
        API_FIELD() RmlUiPropertySource GetSource();
    */
};
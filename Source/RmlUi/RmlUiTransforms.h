#pragma once

#include "RmlUiProperty.h"
#include "RmlUiHelpers.h"

// Conflicts with both Flax and RmlUi Math.h
#undef RadiansToDegrees
#undef DegreesToRadians
#undef NormaliseAngle

#include <ThirdParty/RmlUi/Core/Element.h>

#include <Engine/Core/Math/Vector2.h>
#include <Engine/Core/Collections/Array.h>
#include <Engine/Core/Collections/Dictionary.h>
#include <Engine/Core/Types/Span.h>

#include <Engine/Core/Math/Vector3.h>
#include <Engine/Core/Math/Vector4.h>
#include <Engine/Core/Math/Matrix.h>

API_STRUCT(NoDefault, Namespace = "RmlUi") struct RMLUI_API RmlUiMatrix2D
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiMatrix2D);

    /// <inheritdoc />
    API_FIELD() float value0;

    /// <inheritdoc />
    API_FIELD() float value1;

    /// <inheritdoc />
    API_FIELD() float value2;

    /// <inheritdoc />
    API_FIELD() float value3;

    /// <inheritdoc />
    API_FIELD() float value4;

    /// <inheritdoc />
    API_FIELD() float value5;
};

/// <inheritdoc />
API_STRUCT(NoDefault, Namespace = "RmlUi") struct RMLUI_API RmlUiUnresolvedPrimitiveFloat
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiUnresolvedPrimitiveFloat);

    RmlUiUnresolvedPrimitiveFloat() = default;

    RmlUiUnresolvedPrimitiveFloat(float number, RmlUiUnit unit)
        : number(number), unit(unit)
    {
    }

    RmlUiUnresolvedPrimitiveFloat(float number, Rml::Property::Unit unit)
        : number(number), unit((RmlUiUnit)unit)
    {
    }

    /// <inheritdoc />
    API_FIELD(Private) float number;

    /// <inheritdoc />
    API_FIELD(Private) RmlUiUnit unit;
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformMatrix2D
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformMatrix2D);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformMatrix2D()
        : type(Rml::TransformPrimitive::Type::MATRIX2D)
    {
    }

    RmlUiTransformMatrix2D(RmlUiMatrix2D matrix)
        : type(Rml::TransformPrimitive::Type::MATRIX2D)
        , matrix(matrix)
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) RmlUiMatrix2D matrix;
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformMatrix3D
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformMatrix3D);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformMatrix3D()
        : type(Rml::TransformPrimitive::Type::MATRIX3D)
    {
    }

    RmlUiTransformMatrix3D(Matrix matrix)
        : type(Rml::TransformPrimitive::Type::MATRIX3D)
        , matrix(matrix)
        //, matrix_3d(ToMatrix4f(matrix))
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) Matrix matrix;
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformTranslateX
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformTranslateX);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformTranslateX()
        : type(Rml::TransformPrimitive::Type::TRANSLATEX)
    {
    }

    RmlUiTransformTranslateX(float value, RmlUiUnit unit = RmlUiUnit::Px)
        : type(Rml::TransformPrimitive::Type::TRANSLATEX)
        , x(value, (Rml::Property::Unit)unit)
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat x;
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformTranslateY
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformTranslateY);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformTranslateY()
        : type(Rml::TransformPrimitive::Type::TRANSLATEY)
    {
    }

    RmlUiTransformTranslateY(float value, RmlUiUnit unit = RmlUiUnit::Px)
        : type(Rml::TransformPrimitive::Type::TRANSLATEY)
        , y(value, (Rml::Property::Unit)unit)
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat y;
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformTranslateZ
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformTranslateZ);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformTranslateZ()
        : type(Rml::TransformPrimitive::Type::TRANSLATEZ)
    {
    }

    RmlUiTransformTranslateZ(float value, RmlUiUnit unit = RmlUiUnit::Px)
        : type(Rml::TransformPrimitive::Type::TRANSLATEZ)
        , z(value, (Rml::Property::Unit)unit)
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat z;
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformTranslate2D
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformTranslate2D);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformTranslate2D()
        : type(Rml::TransformPrimitive::Type::TRANSLATE2D)
    {
    }

    RmlUiTransformTranslate2D(float x, float y, RmlUiUnit unit = RmlUiUnit::Px)
        : type(Rml::TransformPrimitive::Type::TRANSLATE2D)
        , x(x, (Rml::Property::Unit)unit), y(y, (Rml::Property::Unit)unit)
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat x;

    /// <inheritdoc />
    API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat y;
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformTranslate3D
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformTranslate3D);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformTranslate3D()
        : type(Rml::TransformPrimitive::Type::TRANSLATE3D)
    {
    }

    RmlUiTransformTranslate3D(float x, float y, float z, RmlUiUnit unit = RmlUiUnit::Px)
        : type(Rml::TransformPrimitive::Type::TRANSLATE3D)
        , x(x, (Rml::Property::Unit)unit), y(y, (Rml::Property::Unit)unit), z(z, (Rml::Property::Unit)unit)
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat x;

    /// <inheritdoc />
    API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat y;

    /// <inheritdoc />
    API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat z;
};

/// <inheritdoc />
API_STRUCT(NoDefault, Namespace = "RmlUi") struct RMLUI_API RmlUiTransformScaleX
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformScaleX);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformScaleX()
        : type(Rml::TransformPrimitive::Type::SCALEX)
    {
    }

    RmlUiTransformScaleX(float value)
        : type(Rml::TransformPrimitive::Type::SCALEX)
        , x(value)
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) float x;
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformScaleY
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformScaleY);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformScaleY()
        : type(Rml::TransformPrimitive::Type::SCALEY)
    {
    }

    RmlUiTransformScaleY(float value)
        : type(Rml::TransformPrimitive::Type::SCALEY)
        , y(value)
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) float y;
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformScaleZ
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformScaleZ);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformScaleZ()
        : type(Rml::TransformPrimitive::Type::SCALEZ)
    {
    }

    RmlUiTransformScaleZ(float value)
        : type(Rml::TransformPrimitive::Type::SCALEZ)
        , z(value)
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) float z;
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformScale2D
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformScale2D);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformScale2D()
        : type(Rml::TransformPrimitive::Type::SCALE2D)
    {
    }

    RmlUiTransformScale2D(float x, float y)
        : type(Rml::TransformPrimitive::Type::SCALE2D)
        , x(x), y(y)
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) float x;

    /// <inheritdoc />
    API_FIELD(Private) float y;
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformScale3D
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformScale3D);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformScale3D()
        : type(Rml::TransformPrimitive::Type::SCALE3D)
    {
    }

    RmlUiTransformScale3D(float x, float y, float z)
        : type(Rml::TransformPrimitive::Type::SCALE3D)
        , x(x), y(y), z(z)
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) float x;
    /// <inheritdoc />
    API_FIELD(Private) float y;
    /// <inheritdoc />
    API_FIELD(Private) float z;
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformRotateX
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformRotateX);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformRotateX()
        : type(Rml::TransformPrimitive::Type::ROTATEX)
    {
    }

    RmlUiTransformRotateX(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
        : type(Rml::TransformPrimitive::Type::ROTATEX)
        , rotate_x(angle, (Rml::Property::Unit)unit)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::RotateX rotate_x;

        /// <inheritdoc />
        API_FIELD(Private) float x;
    };
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformRotateY
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformRotateY);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformRotateY()
        : type(Rml::TransformPrimitive::Type::ROTATEY)
    {
    }

    RmlUiTransformRotateY(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
        : type(Rml::TransformPrimitive::Type::ROTATEY)
        , rotate_y(angle, (Rml::Property::Unit)unit)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::RotateY rotate_y;

        /// <inheritdoc />
        API_FIELD(Private) float y;
    };
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformRotateZ
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformRotateZ);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformRotateZ()
        : type(Rml::TransformPrimitive::Type::ROTATEZ)
    {
    }

    RmlUiTransformRotateZ(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
        : type(Rml::TransformPrimitive::Type::ROTATEZ)
        , rotate_z(angle, (Rml::Property::Unit)unit)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::RotateZ rotate_z;

        /// <inheritdoc />
        API_FIELD(Private) float z;
    };
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformRotate2D
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformRotate2D);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformRotate2D()
        : type(Rml::TransformPrimitive::Type::ROTATE2D)
    {
    }

    RmlUiTransformRotate2D(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
        : type(Rml::TransformPrimitive::Type::ROTATE2D)
        , rotate_2d(angle, (Rml::Property::Unit)unit)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::Rotate2D rotate_2d;

        /// <inheritdoc />
        API_FIELD(Private) float angle;
    };
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformRotate3D
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformRotate3D);

    friend struct RmlUiTransformPrimitive;
    
    RmlUiTransformRotate3D()
        : type(Rml::TransformPrimitive::Type::ROTATE3D)
    {
    }
    
    RmlUiTransformRotate3D(float x, float y, float z, float angle, RmlUiUnit angle_unit = RmlUiUnit::Deg)
        : type(Rml::TransformPrimitive::Type::ROTATE3D)
        , rotate_3d(x, y, z, angle, (Rml::Property::Unit)angle_unit)
    {
    }
    
private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::Rotate3D rotate_3d;

        /// <inheritdoc />
        API_FIELD(Private) float x;

        /// <inheritdoc />
        API_FIELD(Private) float y;

        /// <inheritdoc />
        API_FIELD(Private) float z;

        /// <inheritdoc />
        API_FIELD(Private) float angle;
    };
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformSkewX
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformSkewX);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformSkewX()
        : type(Rml::TransformPrimitive::Type::SKEWX)
    {
    }

    RmlUiTransformSkewX(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
        : type(Rml::TransformPrimitive::Type::SKEWX)
        , skew_x(angle, (Rml::Property::Unit)unit)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::SkewX skew_x;

        /// <inheritdoc />
        API_FIELD(Private) float x;
    };
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformSkewY
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformSkewY);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformSkewY()
        : type(Rml::TransformPrimitive::Type::SKEWY)
    {
    }

    RmlUiTransformSkewY(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
        : type(Rml::TransformPrimitive::Type::SKEWY)
        , skew_y(angle, (Rml::Property::Unit)unit)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::SkewY skew_y;

        /// <inheritdoc />
        API_FIELD(Private) float y;
    };
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformSkew2D
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformSkew2D);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformSkew2D()
        : type(Rml::TransformPrimitive::Type::SKEW2D)
    {
    }

    RmlUiTransformSkew2D(float x, float y, RmlUiUnit angle_unit = RmlUiUnit::Deg)
        : type(Rml::TransformPrimitive::Type::SKEW2D)
        , skew_2d(x, y, (Rml::Property::Unit)angle_unit)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::Skew2D skew_2d;

        /// <inheritdoc />
        API_FIELD(Private) float x;

        /// <inheritdoc />
        API_FIELD(Private) float y;
    };
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformPerspective
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformPerspective);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformPerspective()
        : type(Rml::TransformPrimitive::Type::PERSPECTIVE)
    {
    }

    RmlUiTransformPerspective(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
        : type(Rml::TransformPrimitive::Type::PERSPECTIVE)
    {
        perspective.values.at(0).number = angle;
        perspective.values.at(0).unit = (Rml::Property::Unit)unit;
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::Perspective perspective;

        /// <inheritdoc />
        API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat value0;
    };
};

/// <inheritdoc />
API_STRUCT(Namespace = "RmlUi") struct RMLUI_API RmlUiTransformDecomposedMatrix4
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformDecomposedMatrix4);

    friend struct RmlUiTransformPrimitive;

    RmlUiTransformDecomposedMatrix4()
        : type(Rml::TransformPrimitive::Type::DECOMPOSEDMATRIX4)
    {
    }

    RmlUiTransformDecomposedMatrix4(Float4 perspective, Float4 quaternion, Float3 translation, Float3 scale, Float3 skew)
        : type(Rml::TransformPrimitive::Type::DECOMPOSEDMATRIX4)
        , perspective(perspective), quaternion(quaternion), translation(translation), scale(scale), skew(skew)
    {
    }

private:
    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private) Float4 perspective;

    /// <inheritdoc />
    API_FIELD(Private) Float4 quaternion;

    /// <inheritdoc />
    API_FIELD(Private) Float3 translation;

    /// <inheritdoc />
    API_FIELD(Private) Float3 scale;

    /// <inheritdoc />
    API_FIELD(Private) Float3 skew;
};
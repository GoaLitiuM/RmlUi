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


/// <inheritdoc />
API_STRUCT(NoDefault, Namespace = "RmlUi") struct RMLUI_API RmlUiUnresolvedPrimitiveFloat
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiUnresolvedPrimitiveFloat);

    RmlUiUnresolvedPrimitiveFloat() {}

    RmlUiUnresolvedPrimitiveFloat(RmlUiUnit unit, float number)
        : unit(unit), number(number)
    {
    }

    RmlUiUnresolvedPrimitiveFloat(Rml::Property::Unit unit, float number)
        : unit((RmlUiUnit)unit), number(number)
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

    RmlUiTransformMatrix2D(Matrix matrix)
        : type(Rml::TransformPrimitive::Type::MATRIX2D)
        , value0(matrix)
        //, matrix_3d(ToMatrix4f(matrix))
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::Matrix2D matrix_2d;

        /// <inheritdoc />
        API_FIELD(Private) Matrix value0;
    };
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
        , value0(matrix)
        //, matrix_3d(ToMatrix4f(matrix))
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::Matrix3D matrix_3d;

        /// <inheritdoc />
        API_FIELD(Private) Matrix value0;
    };
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
        , translate_x(value, (Rml::Property::Unit)unit)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::TranslateX translate_x;

        /// <inheritdoc />
        API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat value0;
    };
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
        , translate_y(value, (Rml::Property::Unit)unit)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::TranslateY translate_y;

        /// <inheritdoc />
        API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat value0;
    };
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
        , translate_z(value, (Rml::Property::Unit)unit)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::TranslateZ translate_z;

        /// <inheritdoc />
        API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat value0;
    };
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
        , translate_2d(x, y, (Rml::Property::Unit)unit)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::Translate2D translate_2d;

        /// <inheritdoc />
        API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat value0;
        /// <inheritdoc />
        API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat value1;
    };
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
        , translate_3d(x, y, z, (Rml::Property::Unit)unit)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::Translate3D translate_3d;

        /// <inheritdoc />
        API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat value0;
        /// <inheritdoc />
        API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat value1;
        /// <inheritdoc />
        API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat value2;
        /// <inheritdoc />
        API_FIELD(Private) RmlUiUnresolvedPrimitiveFloat value3;
    };
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
        , scale_x(value)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::ScaleX scale_x;

        /// <inheritdoc />
        API_FIELD(Private) float value0;
    };
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
        , scale_y(value)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::ScaleY scale_y;

        /// <inheritdoc />
        API_FIELD(Private) float value0;
    };
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
        , scale_z(value)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::ScaleZ scale_z;

        /// <inheritdoc />
        API_FIELD(Private) float value0;
    };
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
        , scale_2d(x, y)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::Scale2D scale_2d;

        /// <inheritdoc />
        API_FIELD(Private) float value0;
        /// <inheritdoc />
        API_FIELD(Private) float value1;
    };
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
        , scale_3d(x, y, z)
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::Scale3D scale_3d;

        /// <inheritdoc />
        API_FIELD(Private) float value0;
        /// <inheritdoc />
        API_FIELD(Private) float value1;
        /// <inheritdoc />
        API_FIELD(Private) float value2;
        /// <inheritdoc />
        API_FIELD(Private) float value3;
    };
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
        API_FIELD(Private) float value0;
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
        API_FIELD(Private) float value0;
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
        API_FIELD(Private) float value0;
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
        API_FIELD(Private) float value0;
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
        API_FIELD(Private) float value0;
        /// <inheritdoc />
        API_FIELD(Private) float value1;
        /// <inheritdoc />
        API_FIELD(Private) float value2;
        /// <inheritdoc />
        API_FIELD(Private) float value3;
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
        API_FIELD(Private) float value0;
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
        API_FIELD(Private) float value0;
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
        API_FIELD(Private) float value0;
        /// <inheritdoc />
        API_FIELD(Private) float value1;
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
        , decomposed_matrix_4({ ToVector4f(perspective), ToVector4f(quaternion), ToVector3f(translation), ToVector3f(scale), ToVector3f(skew) })
    {
    }

private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    // [Rml::TransformPrimitive]
    /// <inheritdoc />
    API_FIELD(Private) int32 type;
    union
    {
        Rml::Transforms::DecomposedMatrix4 decomposed_matrix_4;

        /// <inheritdoc />
        API_FIELD(Private) Float4 value0;
        /// <inheritdoc />
        API_FIELD(Private) Float4 value1;
        /// <inheritdoc />
        API_FIELD(Private) Float3 value2;
        /// <inheritdoc />
        API_FIELD(Private) Float3 value3;
        /// <inheritdoc />
        API_FIELD(Private) Float3 value4;
    };
};

#pragma once

#include "RmlUiProperty.h"
#include "RmlUiTransforms.h"

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


API_STRUCT(Namespace="RmlUi") struct RMLUI_API RmlUiTransformPrimitive
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformPrimitive);

    RmlUiTransformPrimitive() {};

    RmlUiTransformPrimitive(Rml::Transforms::Matrix2D          p) : type(Rml::TransformPrimitive::Type::MATRIX2D) { matrix_2d = p; }
    RmlUiTransformPrimitive(Rml::Transforms::Matrix3D          p) : type(Rml::TransformPrimitive::Type::MATRIX3D) { matrix_3d = p; }
    RmlUiTransformPrimitive(Rml::Transforms::TranslateX        p) : type(Rml::TransformPrimitive::Type::TRANSLATEX) { translate_x = p; }
    RmlUiTransformPrimitive(Rml::Transforms::TranslateY        p) : type(Rml::TransformPrimitive::Type::TRANSLATEY) { translate_y = p; }
    RmlUiTransformPrimitive(Rml::Transforms::TranslateZ        p) : type(Rml::TransformPrimitive::Type::TRANSLATEZ) { translate_z = p; }
    RmlUiTransformPrimitive(Rml::Transforms::Translate2D       p) : type(Rml::TransformPrimitive::Type::TRANSLATE2D) { translate_2d = p; }
    RmlUiTransformPrimitive(Rml::Transforms::Translate3D       p) : type(Rml::TransformPrimitive::Type::TRANSLATE3D) { translate_3d = p; }
    RmlUiTransformPrimitive(Rml::Transforms::ScaleX            p) : type(Rml::TransformPrimitive::Type::SCALEX) { scale_x = p; }
    RmlUiTransformPrimitive(Rml::Transforms::ScaleY            p) : type(Rml::TransformPrimitive::Type::SCALEY) { scale_y = p; }
    RmlUiTransformPrimitive(Rml::Transforms::ScaleZ            p) : type(Rml::TransformPrimitive::Type::SCALEZ) { scale_z = p; }
    RmlUiTransformPrimitive(Rml::Transforms::Scale2D           p) : type(Rml::TransformPrimitive::Type::SCALE2D) { scale_2d = p; }
    RmlUiTransformPrimitive(Rml::Transforms::Scale3D           p) : type(Rml::TransformPrimitive::Type::SCALE3D) { scale_3d = p; }
    RmlUiTransformPrimitive(Rml::Transforms::RotateX           p) : type(Rml::TransformPrimitive::Type::ROTATEX) { rotate_x = p; }
    RmlUiTransformPrimitive(Rml::Transforms::RotateY           p) : type(Rml::TransformPrimitive::Type::ROTATEY) { rotate_y = p; }
    RmlUiTransformPrimitive(Rml::Transforms::RotateZ           p) : type(Rml::TransformPrimitive::Type::ROTATEZ) { rotate_z = p; }
    RmlUiTransformPrimitive(Rml::Transforms::Rotate2D          p) : type(Rml::TransformPrimitive::Type::ROTATE2D) { rotate_2d = p; }
    RmlUiTransformPrimitive(Rml::Transforms::Rotate3D          p) : type(Rml::TransformPrimitive::Type::ROTATE3D) { rotate_3d = p; }
    RmlUiTransformPrimitive(Rml::Transforms::SkewX             p) : type(Rml::TransformPrimitive::Type::SKEWX) { skew_x = p; }
    RmlUiTransformPrimitive(Rml::Transforms::SkewY             p) : type(Rml::TransformPrimitive::Type::SKEWY) { skew_y = p; }
    RmlUiTransformPrimitive(Rml::Transforms::Skew2D            p) : type(Rml::TransformPrimitive::Type::SKEW2D) { skew_2d = p; }
    RmlUiTransformPrimitive(Rml::Transforms::Perspective       p) : type(Rml::TransformPrimitive::Type::PERSPECTIVE) { perspective = p; }
    RmlUiTransformPrimitive(Rml::Transforms::DecomposedMatrix4 p) : type(Rml::TransformPrimitive::Type::DECOMPOSEDMATRIX4) { decomposed_matrix_4 = p; }

    RmlUiTransformPrimitive(RmlUiTransformMatrix2D p) : type(Rml::TransformPrimitive::Type::MATRIX2D) { matrix_2d = p.matrix_2d; }
    RmlUiTransformPrimitive(RmlUiTransformMatrix3D p) : type(Rml::TransformPrimitive::Type::MATRIX3D) { matrix_3d = p.matrix_3d; }
    RmlUiTransformPrimitive(RmlUiTransformTranslateX p) : type(Rml::TransformPrimitive::Type::TRANSLATEX) { translate_x = p.translate_x; }
    RmlUiTransformPrimitive(RmlUiTransformTranslateY p) : type(Rml::TransformPrimitive::Type::TRANSLATEY) { translate_y = p.translate_y; }
    RmlUiTransformPrimitive(RmlUiTransformTranslateZ p) : type(Rml::TransformPrimitive::Type::TRANSLATEZ) { translate_z = p.translate_z; }
    RmlUiTransformPrimitive(RmlUiTransformTranslate2D p) : type(Rml::TransformPrimitive::Type::TRANSLATE2D) { translate_2d = p.translate_2d; }
    RmlUiTransformPrimitive(RmlUiTransformTranslate3D p) : type(Rml::TransformPrimitive::Type::TRANSLATE3D) { translate_3d = p.translate_3d; }
    RmlUiTransformPrimitive(RmlUiTransformScaleX p) : type(Rml::TransformPrimitive::Type::SCALEX) { scale_x = p.scale_x; }
    RmlUiTransformPrimitive(RmlUiTransformScaleY p) : type(Rml::TransformPrimitive::Type::SCALEY) { scale_y = p.scale_y; }
    RmlUiTransformPrimitive(RmlUiTransformScaleZ p) : type(Rml::TransformPrimitive::Type::SCALEZ) { scale_z = p.scale_z; }
    RmlUiTransformPrimitive(RmlUiTransformScale2D p) : type(Rml::TransformPrimitive::Type::SCALE2D) { scale_2d = p.scale_2d; }
    RmlUiTransformPrimitive(RmlUiTransformScale3D p) : type(Rml::TransformPrimitive::Type::SCALE3D) { scale_3d = p.scale_3d; }
    RmlUiTransformPrimitive(RmlUiTransformRotateX p) : type(Rml::TransformPrimitive::Type::ROTATEX) { rotate_x = p.rotate_x; }
    RmlUiTransformPrimitive(RmlUiTransformRotateY p) : type(Rml::TransformPrimitive::Type::ROTATEY) { rotate_y = p.rotate_y; }
    RmlUiTransformPrimitive(RmlUiTransformRotateZ p) : type(Rml::TransformPrimitive::Type::ROTATEZ) { rotate_z = p.rotate_z; }
    RmlUiTransformPrimitive(RmlUiTransformRotate2D p) : type(Rml::TransformPrimitive::Type::ROTATE2D) { rotate_2d = p.rotate_2d; }
    RmlUiTransformPrimitive(RmlUiTransformRotate3D p) : type(Rml::TransformPrimitive::Type::ROTATE3D) { rotate_3d = p.rotate_3d; }
    RmlUiTransformPrimitive(RmlUiTransformSkewX p) : type(Rml::TransformPrimitive::Type::SKEWX) { skew_x = p.skew_x; }
    RmlUiTransformPrimitive(RmlUiTransformSkewY p) : type(Rml::TransformPrimitive::Type::SKEWY) { skew_y = p.skew_y; }
    RmlUiTransformPrimitive(RmlUiTransformSkew2D p) : type(Rml::TransformPrimitive::Type::SKEW2D) { skew_2d = p.skew_2d; }
    RmlUiTransformPrimitive(RmlUiTransformPerspective p) : type(Rml::TransformPrimitive::Type::PERSPECTIVE) { perspective = p.perspective; }
    RmlUiTransformPrimitive(RmlUiTransformDecomposedMatrix4 p) : type(Rml::TransformPrimitive::Type::DECOMPOSEDMATRIX4) { decomposed_matrix_4 = p.decomposed_matrix_4; }
    

    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    /// <inheritdoc />
    API_FIELD(Private) byte type;

    union
    {
        Rml::Transforms::Matrix2D matrix_2d;
        Rml::Transforms::Matrix3D matrix_3d;
        Rml::Transforms::TranslateX translate_x;
        Rml::Transforms::TranslateY translate_y;
        Rml::Transforms::TranslateZ translate_z;
        Rml::Transforms::Translate2D translate_2d;
        Rml::Transforms::Translate3D translate_3d;
        Rml::Transforms::ScaleX scale_x;
        Rml::Transforms::ScaleY scale_y;
        Rml::Transforms::ScaleZ scale_z;
        Rml::Transforms::Scale2D scale_2d;
        Rml::Transforms::Scale3D scale_3d;
        Rml::Transforms::RotateX rotate_x;
        Rml::Transforms::RotateY rotate_y;
        Rml::Transforms::RotateZ rotate_z;
        Rml::Transforms::Rotate2D rotate_2d;
        Rml::Transforms::Rotate3D rotate_3d;
        Rml::Transforms::SkewX skew_x;
        Rml::Transforms::SkewY skew_y;
        Rml::Transforms::Skew2D skew_2d;
        Rml::Transforms::Perspective perspective;
        Rml::Transforms::DecomposedMatrix4 decomposed_matrix_4;

        /// <inheritdoc />
        API_FIELD(Private) Float4 perspective_;

        /// <inheritdoc />
        API_FIELD(Private) Float4 quaternion_;

        /// <inheritdoc />
        API_FIELD(Private) Float3 translation_;

        /// <inheritdoc />
        API_FIELD(Private) Float3 scale_;

        /// <inheritdoc />
        API_FIELD(Private) Float3 skew_;
    };
};

API_CLASS(Namespace="RmlUi", NoSpawn) class RMLUI_API RmlUiTransform : public ScriptingObject
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransform);

    RmlUiTransform()
        : ScriptingObject(SpawnParams(Guid::New(), TypeInitializer))
    {
    }

    API_FUNCTION() static RmlUiProperty* MakeProperty(API_PARAM(Params) Span<RmlUiTransformPrimitive> primitives)
    {
        std::vector<Rml::TransformPrimitive> prims;
        for (int i = 0; i < primitives.Length(); i++)
            prims.push_back(*reinterpret_cast<Rml::TransformPrimitive*>(&primitives[i]));

        return New<RmlUiProperty>(Rml::Transform::MakeProperty(prims));
    }

public:

};

API_CLASS(Namespace="RmlUi", NoSpawn) class RMLUI_API RmlUiTransforms : public ScriptingObject
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransforms);

    RmlUiTransforms()
        : ScriptingObject(SpawnParams(Guid::New(), TypeInitializer))
    {
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformMatrix2D Matrix2D(Matrix matrix)
    {
        return RmlUiTransformMatrix2D(matrix);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformMatrix3D Matrix3D(Matrix matrix)
    {
        return RmlUiTransformMatrix3D(matrix);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformTranslateX TranslateX(float value, RmlUiUnit unit = RmlUiUnit::Px)
    {
        return RmlUiTransformTranslateX(value, unit);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformTranslateY TranslateY(float value, RmlUiUnit unit = RmlUiUnit::Px)
    {
        return RmlUiTransformTranslateY(value, unit);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformTranslateZ TranslateZ(float value, RmlUiUnit unit = RmlUiUnit::Px)
    {
        return RmlUiTransformTranslateZ(value, unit);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformTranslate2D Translate2D(float x, float y, RmlUiUnit unit = RmlUiUnit::Px)
    {
        return RmlUiTransformTranslate2D(x, y, unit);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformTranslate3D Translate3D(float x, float y, float z, RmlUiUnit unit = RmlUiUnit::Px)
    {
        return RmlUiTransformTranslate3D(x, y, z, unit);
    }
    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScaleX ScaleX(float value)
    {
        return RmlUiTransformScaleX(value);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScaleY ScaleY(float value)
    {
        return RmlUiTransformScaleY(value);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScaleZ ScaleZ(float value)
    {
        return RmlUiTransformScaleZ(value);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScale2D Scale2D(float xy)
    {
        return RmlUiTransformScale2D(xy, xy);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScale2D Scale2D(float x, float y)
    {
        return RmlUiTransformScale2D(x, y);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScale3D Scale3D(float xyz)
    {
        return RmlUiTransformScale3D(xyz, xyz, xyz);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScale3D Scale3D(float x, float y, float z)
    {
        return RmlUiTransformScale3D(x, y, z);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformRotateX RotateX(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return RmlUiTransformRotateX(angle, unit);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformRotateY RotateY(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return RmlUiTransformRotateY(angle, unit);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformRotateZ RotateZ(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return RmlUiTransformRotateZ(angle, unit);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformRotate2D Rotate2D(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return RmlUiTransformRotate2D(angle, unit);
    }
    
    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformRotate3D Rotate3D(float x, float y, float z, float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return RmlUiTransformRotate3D(x, y, z, angle, unit);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformSkewX SkewX(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return RmlUiTransformSkewX(angle, unit);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformSkewY SkewY(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return RmlUiTransformSkewY(angle, unit);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformSkew2D Skew2D(float x, float y, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return RmlUiTransformSkew2D(x, y, unit);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformPerspective Perspective(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return RmlUiTransformPerspective(angle, unit);
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformDecomposedMatrix4 DecomposedMatrix4(Float4 perspective, Float4 quaternion, Float3 translation, Float3 scale, Float3 skew)
    {
        return RmlUiTransformDecomposedMatrix4(perspective, quaternion, translation, scale, skew);
    }
};
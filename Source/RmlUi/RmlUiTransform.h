#pragma once

#include "RmlUiProperty.h"
#include "RmlUiTransforms.h"

// Conflicts with both Flax and RmlUi Math.h
#undef RadiansToDegrees
#undef DegreesToRadians
#undef NormaliseAngle

#include <ThirdParty/RmlUi/Core/Element.h>
#include <ThirdParty/RmlUi/Core/TransformPrimitive.h>

#include <Engine/Core/Math/Vector2.h>
#include <Engine/Core/Collections/Array.h>
#include <Engine/Core/Collections/Dictionary.h>
#include <Engine/Core/Types/Span.h>

#include <Engine/Core/Math/Vector3.h>
#include <Engine/Core/Math/Vector4.h>

/// <inheritdoc />
API_STRUCT(NoDefault, Namespace="RmlUi") struct RMLUI_API RmlUiTransformPrimitive
{
    // The size of this structure should match the size of Rml::TransformPrimitive
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransformPrimitive);

    /// <inheritdoc />
    API_FIELD(Private) int32 type;

    /// <inheritdoc />
    API_FIELD(Private, NoArray) float value[17];
};

/// <inheritdoc />
API_CLASS(Namespace="RmlUi", NoSpawn) class RMLUI_API RmlUiTransform : public ScriptingObject
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTransform);

    RmlUiTransform()
        : ScriptingObject(SpawnParams(Guid::New(), TypeInitializer))
    {
    }
    
    RmlUiTransform(Rml::TransformPtr& transform)
        : ScriptingObject(SpawnParams(Guid::New(), TypeInitializer))
    {
        this->transform.swap(transform);
    }

    ~RmlUiTransform() {}
    
    API_FUNCTION() static RmlUiProperty* MakeProperty(API_PARAM(Params) Span<RmlUiTransformPrimitive> primitives)
    {
        std::vector<Rml::TransformPrimitive> prims;
        for (int i = 0; i < primitives.Length(); i++)
        {
            RmlUiTransformPrimitive poo = primitives[i];
            Rml::TransformPrimitive p = *reinterpret_cast<Rml::TransformPrimitive*>(&poo);
            prims.push_back(p);
        }

        auto prop = Rml::Transform::MakeProperty(prims);
        return New<RmlUiProperty>(prop);
    }

    API_FUNCTION() Span<RmlUiTransformPrimitive> GetPrimitives()
    {
        std::vector<Rml::TransformPrimitive> prims = transform.get()->GetPrimitives();
        Span<RmlUiTransformPrimitive> arr(reinterpret_cast<RmlUiTransformPrimitive*>(&prims[0]), (int32)prims.size());
        return arr;
    }
    
    union
    {
        Rml::TransformPtr transform = nullptr;

        API_FIELD(Private) int64 nativePtr;
    };
public:
};

/// <inheritdoc />
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
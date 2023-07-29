#pragma once

#include "RmlUiProperty.h"
#include "RmlUiTransforms.h"

// Conflicts with both Flax and RmlUi Math.h
#undef RadiansToDegrees
#undef DegreesToRadians
#undef NormaliseAngle

#include <ThirdParty/RmlUi/Core/Element.h>
#include <ThirdParty/RmlUi/Core/TransformPrimitive.h>

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
        Span<RmlUiTransformPrimitive> span(reinterpret_cast<RmlUiTransformPrimitive*>(prims.data()), (int32)prims.size());
        return span;
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
    API_FUNCTION() static RmlUiTransformMatrix2D Matrix2D(RmlUiMatrix2D matrix)
    {
        return {matrix};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformMatrix3D Matrix3D(Matrix matrix)
    {
        return {matrix};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformTranslateX TranslateX(float value, RmlUiUnit unit = RmlUiUnit::Px)
    {
        return {value, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformTranslateY TranslateY(float value, RmlUiUnit unit = RmlUiUnit::Px)
    {
        return {value, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformTranslateZ TranslateZ(float value, RmlUiUnit unit = RmlUiUnit::Px)
    {
        return {value, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformTranslate2D Translate2D(float x, float y, RmlUiUnit unit = RmlUiUnit::Px)
    {
        return {x, y, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformTranslate3D Translate3D(float x, float y, float z, RmlUiUnit unit = RmlUiUnit::Px)
    {
        return {x, y, z, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScaleX ScaleX(float value)
    {
        return {value};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScaleY ScaleY(float value)
    {
        return {value};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScaleZ ScaleZ(float value)
    {
        return {value};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScale2D Scale2D(float xy)
    {
        return {xy, xy};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScale2D Scale2D(float x, float y)
    {
        return {x, y};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScale3D Scale3D(float xyz)
    {
        return {xyz, xyz, xyz};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformScale3D Scale3D(float x, float y, float z)
    {
        return {x, y, z};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformRotateX RotateX(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return {angle, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformRotateY RotateY(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return {angle, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformRotateZ RotateZ(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return {angle, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformRotate2D Rotate2D(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return {angle, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformRotate3D Rotate3D(float x, float y, float z, float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return {x, y, z, angle, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformSkewX SkewX(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return {angle, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformSkewY SkewY(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return {angle, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformSkew2D Skew2D(float x, float y, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return {x, y, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformPerspective Perspective(float angle, RmlUiUnit unit = RmlUiUnit::Deg)
    {
        return {angle, unit};
    }

    /// <inheritdoc />
    API_FUNCTION() static RmlUiTransformDecomposedMatrix4 DecomposedMatrix4(Float4 perspective, Float4 quaternion, Float3 translation, Float3 scale, Float3 skew)
    {
        return {perspective, quaternion, translation, scale, skew};
    }
};
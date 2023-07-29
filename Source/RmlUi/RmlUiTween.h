#pragma once

#include <Engine/Core/Config.h>
#include <Engine/Core/Types/BaseTypes.h>

#include <ThirdParty/RmlUi/Core/Property.h>
#include <ThirdParty/RmlUi/Core/Tween.h>

#include <Engine/Core/Types/String.h>

#include "Engine/Scripting/ScriptingObject.h"

/// <inheritdoc />
API_ENUM(Namespace = "RmlUi") enum class RmlUiTweenType
{
    /// <inheritdoc />
    None,
    /// <inheritdoc />
    Back,
    /// <inheritdoc />
    Bounce,
    /// <inheritdoc />
    Circular,
    /// <inheritdoc />
    Cubic,
    /// <inheritdoc />
    Elastic,
    /// <inheritdoc />
    Exponential,
    /// <inheritdoc />
    Linear,
    /// <inheritdoc />
    Quadratic,
    /// <inheritdoc />
    Quartic,
    /// <inheritdoc />
    Quintic,
    /// <inheritdoc />
    Sine,
    /// <inheritdoc />
    Callback,
    /// <inheritdoc />
    Count,
};

/// <inheritdoc />
API_ENUM(Namespace = "RmlUi") enum class RmlUiTweenDirection
{
    /// <inheritdoc />
    In = 1,
    /// <inheritdoc />
    Out = 2,
    /// <inheritdoc />
    InOut = 3,
};

/// <inheritdoc />
API_STRUCT(NoDefault, Namespace = "RmlUi") struct RMLUI_API RmlUiTween
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(RmlUiTween);
private:

public:
    friend class RmlUiElement;
    using CallbackFnc = float(*)(float);

    RmlUiTween() {}

    RmlUiTween(const RmlUiTween* tween)
    {
        this->tween = tween->tween;
    }

    RmlUiTween(const RmlUiTween& tween)
    {
        this->tween = tween.tween;
    }

    RmlUiTween(RmlUiTweenType type, RmlUiTweenDirection direction)
        : tween((Rml::Tween::Type)type, (Rml::Tween::Direction)direction)
    {
    }

    RmlUiTween(RmlUiTweenType type_in, RmlUiTweenType type_out)
        : tween((Rml::Tween::Type)type_in, (Rml::Tween::Type)type_out)
    {
    }

    RmlUiTween(CallbackFnc callback, RmlUiTweenDirection direction = RmlUiTweenDirection::In)
        : tween(callback, (Rml::Tween::Direction)direction)
    {
    }

    ~RmlUiTween() {}

    operator Rml::Tween() const
    {
        return tween;
    }

/*
    // Evaluate the Tweening function at point t in [0, 1].
    float operator()(float t) const;

    // Reverse direction of the tweening function.
    void reverse();

    bool operator==(const Tween& other) const;
    bool operator!=(const Tween& other) const;

    String to_string() const;

*/
private:
    // HACK: Expose private fields to scripting to match with the memory layout of this structure

    union
    {
        Rml::Tween tween;

        /// <inheritdoc />
        API_FIELD() RmlUiTweenType TypeIn;

        /// <inheritdoc />
        API_FIELD() RmlUiTweenType TypeOut;

        /// <inheritdoc />
        API_FIELD(Private) void* callback;

        //CallbackFnc callback = nullptr;
    };
};
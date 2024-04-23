#pragma once

// Conflicts with both Flax and RmlUi Math.h
#undef RadiansToDegrees
#undef DegreesToRadians
#undef NormaliseAngle

#include <ThirdParty/RmlUi/Core/Input.h>
#include <ThirdParty/RmlUi/Core/Types.h>
#include <ThirdParty/RmlUi/Core/Unit.h>

// Conflicts with both Flax and RmlUi Math.h
#undef RadiansToDegrees
#undef DegreesToRadians
#undef NormaliseAngle

#include <Engine/Input/Input.h>
#include <Engine/Core/Types/String.h>
#include <Engine/Core/Math/Vector2.h>
#include <Engine/Core/Math/Vector3.h>
#include <Engine/Core/Math/Vector4.h>
#include <Engine/Core/Math/Matrix.h>

KeyboardKeys TranslateRmlUiKey(Rml::Input::KeyIdentifier keyIdentifier);
Rml::Input::KeyIdentifier TranslateFlaxKey(KeyboardKeys key);
int TranslateFlaxMouseButton(MouseButton button);
Window* GetEditorGameWindow();
bool HasEditorGameViewportFocus();

FORCE_INLINE Rml::String ToRmlString(const String& str)
{
    StringAnsi ansi(str.Get(), str.Length());
    Rml::String rstr(ansi.Get(), ansi.Length());
    return rstr;
}

FORCE_INLINE Rml::String ToRmlString(const StringAnsi& str)
{
    Rml::String rstr(str.Get(), str.Length());
    return rstr;
}

FORCE_INLINE String ToFlaxString(const Rml::String& str)
{
    String fstr(str.c_str(), (int32)str.length());
    return fstr;
}

FORCE_INLINE StringAnsi ToFlaxStringAnsi(const Rml::String& str)
{
    StringAnsi fstr(str.c_str(), (int32)str.length());
    return fstr;
}

FORCE_INLINE Float2 ToFloat2(const Rml::Vector2f& vec)
{
    return { vec.x, vec.y };
}

FORCE_INLINE Rml::Vector2f ToVector2f(const Float2& vec)
{
    return { vec.X, vec.Y };
}

FORCE_INLINE Float3 ToFloat3(const Rml::Vector3f& vec)
{
    return { vec.x, vec.y, vec.z };
}

FORCE_INLINE Rml::Vector3f ToVector3f(const Float3& vec)
{
    return { vec.X, vec.Y, vec.Z };
}

FORCE_INLINE Float4 ToFloat4(const Rml::Vector4f& vec)
{
    return { vec.x, vec.y, vec.z, vec.w };
}

FORCE_INLINE Rml::Vector4f ToVector4f(const Float4& vec)
{
    return { vec.X, vec.Y, vec.Z, vec.W };
}

FORCE_INLINE Matrix ToMatrix(const Rml::Matrix4f& vec)
{
    const float* values = vec.data();
    return Matrix(reinterpret_cast<float(&)[16]>(values));
}

FORCE_INLINE Rml::Matrix4f ToMatrix4f(const Matrix& vec)
{
    return *reinterpret_cast<const Rml::Matrix4f*>(&vec);
}
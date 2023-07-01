#include "RmlUiCanvas.h"
#include "RmlUiPlugin.h"
#include "RmlUiHelpers.h"

// Conflicts with both Flax and RmlUi Math.h
#undef RadiansToDegrees
#undef DegreesToRadians
#undef NormaliseAngle

#include <ThirdParty/RmlUi/Core/Context.h>
#include <ThirdParty/RmlUi/Core/Core.h>
#include <ThirdParty/RmlUi/Core/FontEngineInterface.h>
#include <ThirdParty/RmlUi/Debugger.h>

#include <Engine/Engine/Screen.h>
#include <Engine/Profiler/ProfilerCPU.h>

RmlUiCanvas::RmlUiCanvas(const SpawnParams& params)
    : Actor(params)
{
}

Rml::Context* RmlUiCanvas::GetContext() const
{
    return context;
}

bool RmlUiCanvas::HasFocus() const
{
    return RmlUiPlugin::GetFocusedCanvas() == this;
}

void RmlUiCanvas::BeginPlay(SceneBeginData* data)
{
    StringAnsi contextName = GetID().ToString().ToStringAnsi();
    Float2 screenSize = Screen::GetSize();
    context = Rml::CreateContext(contextName.Get(), Rml::Vector2i((int)screenSize.X, (int)screenSize.Y));
    if (context == nullptr)
        return;

    // Pre-load font assets
    const auto fontEngineInterface = Rml::GetFontEngineInterface();
    for (const auto& font : Fonts)
    {
        if (font.Font == nullptr || font.Font->WaitForLoaded())
            continue;

        StringAnsi fontPathAnsi = font.Font->GetPath().ToStringAnsi();
        Rml::String fontPath(fontPathAnsi.Get(), fontPathAnsi.Length());
        fontEngineInterface->LoadFontFace(fontPath, font.UseAsFallbackFont, Rml::Style::FontWeight::Auto);
    }

    if (EnableDebugger && DebuggerKey != KeyboardKeys::None)
        Rml::Debugger::Initialise(context);

    context->SetDensityIndependentPixelRatio(Platform::GetDpiScale());

    RmlUiPlugin::RegisterCanvas(this);

    Actor::BeginPlay(data);
}

void RmlUiCanvas::EndPlay()
{
    Actor::EndPlay();

    if (RmlUiPlugin::IsInitialized())
    {
        if (EnableDebugger && DebuggerKey != KeyboardKeys::None)
            Rml::Debugger::Shutdown();

        if (context != nullptr)
        {
            Rml::RemoveContext(context->GetName());
            context = nullptr;
        }
        RmlUiPlugin::UnregisterCanvas(this);
    }
}

void RmlUiCanvas::OnEnable()
{
    Actor::OnEnable();
}

void RmlUiCanvas::OnDisable()
{
    Actor::OnDisable();
}

void RmlUiCanvas::OnParentChanged()
{
    Actor::OnParentChanged();
}

void RmlUiCanvas::OnTransformChanged()
{
    Actor::OnTransformChanged();
}

int GetInputModifiers()
{
    int modifierState = 0;
    if (Input::GetKeyDown(KeyboardKeys::Capital))
        modifierState |= Rml::Input::KM_CAPSLOCK;
    if (Input::GetKeyDown(KeyboardKeys::Numlock))
        modifierState |= Rml::Input::KM_NUMLOCK;
    if (Input::GetKeyDown(KeyboardKeys::Shift))
        modifierState |= Rml::Input::KM_SHIFT;
    if (Input::GetKeyDown(KeyboardKeys::Control))
        modifierState |= Rml::Input::KM_CTRL;
    if (Input::GetKeyDown(KeyboardKeys::Alt))
        modifierState |= Rml::Input::KM_ALT;
    return modifierState;
}

void RmlUiCanvas::OnCharInput(Char c) const
{
    if (!HasFocus())
        return;

    PROFILE_CPU();

    context->ProcessTextInput((Rml::Character)c);
}

void RmlUiCanvas::OnKeyDown(KeyboardKeys key) const
{
    if (!HasFocus())
        return;

    PROFILE_CPU();

    context->ProcessKeyDown(TranslateFlaxKey(key), GetInputModifiers());
}

void RmlUiCanvas::OnKeyUp(KeyboardKeys key) const
{
    if (!HasFocus())
        return;

    PROFILE_CPU();

    if (EnableDebugger && key == DebuggerKey)
        Rml::Debugger::SetVisible(!Rml::Debugger::IsVisible());

    context->ProcessKeyUp(TranslateFlaxKey(key), GetInputModifiers());
}

void RmlUiCanvas::OnMouseDown(const Float2& mousePosition, MouseButton button) const
{
    if (!HasFocus())
        return;

    if (button == MouseButton::None)
        return;

    PROFILE_CPU();

    context->ProcessMouseButtonDown(TranslateFlaxMouseButton(button), GetInputModifiers());
}

void RmlUiCanvas::OnMouseUp(const Float2& mousePosition, MouseButton button) const
{
    if (!HasFocus())
        return;

    if (button == MouseButton::None)
        return;

    PROFILE_CPU();

    context->ProcessMouseButtonUp(TranslateFlaxMouseButton(button), GetInputModifiers());
}

void RmlUiCanvas::OnMouseWheel(const Float2& mousePosition, float delta) const
{
    if (!HasFocus())
        return;

    PROFILE_CPU();

    context->ProcessMouseWheel(Rml::Vector2f(0.0f, delta), GetInputModifiers());
}

void RmlUiCanvas::OnMouseMove(const Float2& mousePosition) const
{
    if (!HasFocus())
        return;

    PROFILE_CPU();

    context->ProcessMouseMove((int)mousePosition.X, (int)mousePosition.Y, GetInputModifiers());
}

void RmlUiCanvas::OnMouseLeave() const
{
    if (!HasFocus())
        return;

    PROFILE_CPU();

    context->ProcessMouseLeave();
}

void RmlUiCanvas::OnTouchDown(const Float2& pointerPosition, int32 pointerIndex) const
{
    if (!HasFocus())
        return;

    PROFILE_CPU();

    context->ProcessMouseButtonDown(TranslateFlaxMouseButton(MouseButton::Left), GetInputModifiers());
}

void RmlUiCanvas::OnTouchMove(const Float2& pointerPosition, int32 pointerIndex) const
{
    if (!HasFocus())
        return;

    PROFILE_CPU();

    context->ProcessMouseMove((int)pointerPosition.X, (int)pointerPosition.Y, GetInputModifiers());
}

void RmlUiCanvas::OnTouchUp(const Float2& pointerPosition, int32 pointerIndex) const
{
    if (!HasFocus())
        return;

    PROFILE_CPU();

    context->ProcessMouseButtonUp(TranslateFlaxMouseButton(MouseButton::Left), GetInputModifiers());
}
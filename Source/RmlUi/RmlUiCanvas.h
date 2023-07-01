#pragma once

#include "RmlUiFont.h"

#include <Engine/Input/Input.h>
#include <Engine/Input/KeyboardKeys.h>
#include <Engine/Level/Actor.h>
#include <Engine/Render2D/FontAsset.h>

namespace Rml
{
    class Context;
}

/// <summary>
/// The canvas (context) for RmlUi documents.
/// </summary>
API_CLASS(Sealed, NoConstructor, Attributes="ActorContextMenu(\"New/UI/RmlUi Canvas\"), ActorToolbox(\"GUI\")")
class RMLUI_API RmlUiCanvas : public Actor
{
    friend class RmlUiPlugin;

    API_AUTO_SERIALIZATION();
    DECLARE_SCENE_OBJECT(RmlUiCanvas);

private:
    Rml::Context* context = nullptr;

public:
    /// <summary>
    /// Fonts to be loaded.
    /// </summary>
    API_FIELD() Array<RmlUiFont> Fonts;

    /// <summary>
    /// Turns on the RmlUi debugger plugin for this context when enabled.
    /// </summary>
    API_FIELD(Attributes="EditorDisplay(\"Debugger\"), DefaultValue(false)") bool EnableDebugger = false;

    /// <summary>
    /// The key to toggle visibility of the debugger.
    /// </summary>
    API_FIELD(Attributes="EditorDisplay(\"Debugger\"), DefaultValue(KeyboardKeys.F8), VisibleIf(nameof(EnableDebugger))") KeyboardKeys DebuggerKey = KeyboardKeys::F8;
public:
    /// <summary>
    /// The context for hosting RmlUi documents.
    /// </summary>
    Rml::Context* GetContext() const;

    /// <summary>
    /// Returns true if this context has input focus.
    /// </summary>
    bool HasFocus() const;

protected:
    // [Actor]
    void BeginPlay(SceneBeginData* data) final override;
    void EndPlay() final override;
    void OnEnable() override;
    void OnDisable() override;
    void OnParentChanged() override;
    void OnTransformChanged() final override;

private:
    void OnCharInput(Char c) const;
    void OnKeyDown(KeyboardKeys key) const;
    void OnKeyUp(KeyboardKeys key) const;
    void OnMouseDown(const Float2& mousePosition, MouseButton button) const;
    void OnMouseUp(const Float2& mousePosition, MouseButton button) const;
    void OnMouseWheel(const Float2& mousePosition, float delta) const;
    void OnMouseMove(const Float2& mousePosition) const;
    void OnMouseLeave() const;
    void OnTouchDown(const Float2& pointerPosition, int32 pointerIndex) const;
    void OnTouchMove(const Float2& pointerPosition, int32 pointerIndex) const;
    void OnTouchUp(const Float2& pointerPosition, int32 pointerIndex) const;
};

#pragma once

#include <Engine/Core/Config/Settings.h>
#include <Engine/Input/Input.h>
#include <Engine/Scripting/Plugins/GamePlugin.h>
#include <Engine/Graphics/Textures/GPUTexture.h>
#if USE_EDITOR
#include <Engine/Scripting/Plugins/EditorPlugin.h>
#endif

static_assert(FLAX_1_6_OR_NEWER, "Flax 1.6 or later is required for RmlUi plugin");

#define RMLUI_PLUGIN_VERSION Version(0, 1, 0)
#define RMLUI_PLUGIN_BASIC_SHADER "6c6a53224d6768a5a91640ac4e34520d"

class RmlUiCanvas;
class GPUContext;
struct RenderContext;

/// <summary>
/// The settings for RmlUi plugin.
/// </summary>
API_CLASS() class RmlUiSettings : public SettingsBase
{
    API_AUTO_SERIALIZATION();
    DECLARE_SCRIPTING_TYPE_NO_SPAWN(RmlUiSettings);
    DECLARE_SETTINGS_GETTER(RmlUiSettings);
};

/// <summary>
/// RmlUi plugin.
/// </summary>
API_CLASS() class RMLUI_API RmlUiPlugin : public GamePlugin
{
    DECLARE_SCRIPTING_TYPE(RmlUiPlugin);

public:
    // [GamePlugin]
    /// <inheritdoc />
    void Initialize() override;

    /// <inheritdoc />
    void Deinitialize() override;

#if USE_EDITOR
    /// <inheritdoc />
    Array<Guid> GetReferences() const override;
#endif

public:
    /// <summary>
    /// Returns true if RmlUi is currently initialized.
    /// </summary>
    static bool IsInitialized();

    /// <summary>
    /// Initializes RmlUi and all custom interfaces.
    /// </summary>
    static void InitializeRmlUi();

    /// <summary>
    /// Deinitializes RmlUi and all custom interfaces.
    /// </summary>
    static void DeinitializeRmlUi();

    /// <summary>
    /// Callback from FlaxRenderInterface in order to support custom texture loading. Return nullptr for default behaviour.
    /// </summary>
    /// <param name="uintptr">Unique texture handle that would be assigned to this texture</param>
    /// <param name="Float2">Texture dimensions (unused on texture restoration after multiple runs in editor)</param>
    /// <param name="String">Texture path that was requested for loading</param>
    /// <returns>The created or loaded texture, return nullptr if we want to fallback to default behaviour.</returns>
    static Function<GPUTexture*(uintptr_t, Float2&, const String&)> OnLoadTexture;

    /// <summary>
    /// Callback from FlaxRenderInterface in order to support custom texture unloading. Return false for default behaviour.
    /// </summary>
    /// <param name="uintptr">Unique texture handle that would be assigned to this texture</param>
    /// <returns>True if successfully released a texture, false if we want to fallback to default behaviour.</returns>
    static Function<bool(uintptr_t)> OnReleaseTexture;

    /// <summary>
    /// Disposes of all custom textures used internally in the FlaxRenderInterface.
    /// </summary>
    API_FUNCTION() static void DisposeCustomTextures();

    /// <summary>
    /// Register RmlUiCanvas for updates and rendering.
    /// </summary>
    static void RegisterCanvas(RmlUiCanvas* canvas);

    /// <summary>
    /// Unregister RmlUiCanvas for updates and rendering.
    /// </summary>
    static void UnregisterCanvas(RmlUiCanvas* canvas);

    /// <summary>
    /// Returns the currently focused canvas.
    /// </summary>
    static RmlUiCanvas* GetFocusedCanvas();

    /// <summary>
    /// Enables focus on the specified canvas for receiving input.
    /// </summary>
    static void FocusCanvas(RmlUiCanvas* canvas);

    /// <summary>
    /// Disables focus on the specified canvas for receiving input.
    /// </summary>
    static void DefocusCanvas(RmlUiCanvas* canvas);

    /// <summary>
    /// Registers input events for current window
    /// </summary>
    API_FUNCTION() static void RegisterWindowEvents();

    /// <summary>
    /// Unregisters input events for current window
    /// </summary>
    API_FUNCTION() static void UnregisterWindowEvents();

private:
    static void OnRegisterWindowEvents();
    static void RegisterEvents();
    static void OnCharInput(Char c);
    static void OnKeyDown(KeyboardKeys key);
    static void OnKeyUp(KeyboardKeys key);
    static void OnMouseDown(const Float2& mousePosition, MouseButton button);
    static void OnMouseUp(const Float2& mousePosition, MouseButton button);
    static void OnMouseDoubleClick(const Float2& mousePosition, MouseButton button);
    static void OnMouseWheel(const Float2& mousePosition, float delta);
    static void OnMouseMove(const Float2& mousePosition);
    static void OnMouseLeave();
    static void OnTouchDown(const Float2& pointerPosition, int32 pointerIndex);
    static void OnTouchMove(const Float2& pointerPosition, int32 pointerIndex);
    static void OnTouchUp(const Float2& pointerPosition, int32 pointerIndex);
#if USE_EDITOR
    static void OnCharInputGameWindow(Char c);
    static void OnKeyDownGameWindow(KeyboardKeys key);
    static void OnKeyUpGameWindow(KeyboardKeys key);
    static void OnMouseDownGameWindow(const Float2& mousePosition, MouseButton button);
    static void OnMouseUpGameWindow(const Float2& mousePosition, MouseButton button);
    static void OnMouseDoubleClickGameWindow(const Float2& mousePosition, MouseButton button);
    static void OnMouseWheelGameWindow(const Float2& mousePosition, float delta);
    static void OnMouseMoveGameWindow(const Float2& mousePosition);
    static void OnMouseLeaveGameWindow();
    static void OnTouchDownGameWindow(const Float2& pointerPosition, int32 pointerIndex);
    static void OnTouchMoveGameWindow(const Float2& pointerPosition, int32 pointerIndex);
    static void OnTouchUpGameWindow(const Float2& pointerPosition, int32 pointerIndex);
#endif
    static void Update();
    static void Render(GPUContext* gpuContext, RenderContext& renderContext);
};

#if USE_EDITOR
/// <summary>
/// RmlUi plugin (Editor).
/// </summary>
API_CLASS() class RMLUI_API RmlUiEditorPlugin : public EditorPlugin
{
    DECLARE_SCRIPTING_TYPE(RmlUiEditorPlugin);

public:
    // [EditorPlugin]
    /// <inheritdoc />
    void Initialize() override;

    /// <inheritdoc />
    void Deinitialize() override;
};
#endif
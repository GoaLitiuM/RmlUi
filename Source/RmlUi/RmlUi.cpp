#include "RmlUi.h"

// Conflicts with both Flax and RmlUi Math.h
#undef RadiansToDegrees
#undef DegreesToRadians
#undef NormaliseAngle

#include "RmlUiCanvas.h"
#include "RmlUiImport.h"
#include "RmlUiHelpers.h"
#include "FlaxSystemInterface.h"
#include "FlaxFileInterface.h"
#include "FlaxRenderInterface.h"
#include "FlaxFontEngineInterface.h"

#include <ThirdParty/RmlUi/Core/Context.h>
#include <ThirdParty/RmlUi/Core/ElementDocument.h>

#include <Engine/Content/Content.h>
#include <Engine/Content/JsonAsset.h>
#include <Engine/Core/Config/GameSettings.h>
#include <Engine/Engine/Engine.h>
#include <Engine/Graphics/GPUDevice.h>
#include <Engine/Graphics/RenderTask.h>
#include <Engine/Profiler/Profiler.h>

#include <Engine/Platform/Window.h>
#include <Engine/Engine/Screen.h>

namespace
{
    bool RmlUiInitialized = false;
    Array<RmlUiCanvas*> Canvases;
    RmlUiCanvas* FocusedCanvas = nullptr;
    FlaxSystemInterface* FlaxSystemInterfaceInstance = nullptr;
    FlaxRenderInterface* FlaxRenderInterfaceInstance = nullptr;
    FlaxFontEngineInterface* FlaxFontEngineInterfaceInstance = nullptr;
    FlaxFileInterface* FlaxFileInterfaceInstance = nullptr;
}

IMPLEMENT_GAME_SETTINGS_GETTER(RmlUiSettings, "RmlUi");

PluginDescription GetPluginDescription()
{
    PluginDescription description;
    description.Name = TEXT("RmlUi");
    description.Version = RMLUI_PLUGIN_VERSION;
    description.IsAlpha = true;
    description.Category = TEXT("GUI");
    description.Description = TEXT("RmlUi is a user interface library based on HTML and CSS standards.");
    description.Author = TEXT("Michael R. P. Ragazzon");
    description.AuthorUrl = TEXT("https://github.com/mikke89/RmlUi");
	description.HomepageUrl = TEXT("https://github.com/mikke89/RmlUi");
    description.RepositoryUrl = TEXT("https://github.com/GoaLitiuM/RmlUi");
    return description;
}

RmlUi::RmlUi(const SpawnParams& params)
    : GamePlugin(params)
{
    _description = GetPluginDescription();
}

void RmlUi::Initialize()
{
#if !USE_EDITOR
    RmlUi::InitializeRmlUi();
#endif
    GamePlugin::Initialize();
}

void RmlUi::Deinitialize()
{
#if !USE_EDITOR
    RmlUi::DeinitializeRmlUi();
#endif
    GamePlugin::Deinitialize();
}

#if USE_EDITOR
Array<Guid> RmlUi::GetReferences() const
{
    Array<Guid> references;

    Guid basicShaderGuid;
    Guid::Parse(StringAnsiView(RMLUI_PLUGIN_BASIC_SHADER), basicShaderGuid);
    references.Add(basicShaderGuid);

    return references;
}
#endif

bool RmlUi::IsInitialized()
{
    return RmlUiInitialized;
}

#if USE_EDITOR
RmlUiEditorPlugin::RmlUiEditorPlugin(const SpawnParams& params)
    : EditorPlugin(params)
{
    _description = GetPluginDescription();
}

void RmlUiEditorPlugin::Initialize()
{
    RegisterRmlUiImporters();

    RmlUi::InitializeRmlUi();
    EditorPlugin::Initialize();
}

void RmlUiEditorPlugin::Deinitialize()
{
    RmlUi::DeinitializeRmlUi();
    EditorPlugin::Deinitialize();
}
#endif

void RmlUi::InitializeRmlUi()
{
    if (RmlUiInitialized)
        return;

    PROFILE_CPU();

    RmlUiInitialized = true;
    FocusedCanvas = nullptr;

    // Setup Flax Engine interfaces
    FlaxSystemInterfaceInstance = New<FlaxSystemInterface>();
    FlaxRenderInterfaceInstance = New<FlaxRenderInterface>();
    FlaxFontEngineInterfaceInstance = New<FlaxFontEngineInterface>();
    FlaxFileInterfaceInstance = New<FlaxFileInterface>();
    Rml::SetSystemInterface(FlaxSystemInterfaceInstance);
    Rml::SetRenderInterface(FlaxRenderInterfaceInstance);
    Rml::SetFontEngineInterface(FlaxFontEngineInterfaceInstance);
    Rml::SetFileInterface(FlaxFileInterfaceInstance);

    Rml::Initialise();

    RegisterEvents();
}

void RmlUi::DeinitializeRmlUi()
{
    if (!RmlUiInitialized)
        return;

    RmlUiInitialized = false;

    UnregisterEvents();

    FlaxFontEngineInterfaceInstance->ReleaseFontResources();

    Rml::Shutdown();

    FlaxRenderInterfaceInstance->ReleaseResources();

    Delete(FlaxSystemInterfaceInstance);
    Delete(FlaxRenderInterfaceInstance);
    Delete(FlaxFontEngineInterfaceInstance);
    Delete(FlaxFileInterfaceInstance);

    Canvases.Clear();
}

void RmlUi::RegisterCanvas(RmlUiCanvas* canvas)
{
    Canvases.Add(canvas);
}

void RmlUi::UnregisterCanvas(RmlUiCanvas* canvas)
{
    Canvases.Remove(canvas);
    if (FocusedCanvas == canvas)
        DefocusCanvas(canvas);
}

RmlUiCanvas* RmlUi::GetFocusedCanvas()
{
    return FocusedCanvas;
}

void RmlUi::FocusCanvas(RmlUiCanvas* canvas)
{
    FocusedCanvas = canvas;
}

void RmlUi::DefocusCanvas(RmlUiCanvas* canvas)
{
    if (FocusedCanvas == canvas)
        FocusedCanvas = nullptr;
}

void RmlUi::RegisterEvents()
{
    Engine::LateUpdate.Bind(&RmlUi::Update);
    MainRenderTask::Instance->PostRender.Bind(&RmlUi::Render);

    if (Engine::MainWindow != nullptr)
        RegisterWindowEvents();
    else
    {
        // Editor plugins are initialized before the main window is created, handle registration during next frame
        Engine::Update.Bind(&RmlUi::RegisterWindowEvents);
    }
}

void RmlUi::RegisterWindowEvents()
{
    Engine::Update.Unbind(&RmlUi::RegisterWindowEvents);

#if USE_EDITOR
    // Register events for floating game window
    // TODO: Bind/Unbind events when window focus is lost/gained
    auto gameWindow = GetEditorGameWindow();
    if (gameWindow != nullptr)
    {
        gameWindow->CharInput.Bind(RmlUi::OnCharInputGameWindow);
        gameWindow->KeyDown.Bind(RmlUi::OnKeyDownGameWindow);
        gameWindow->KeyUp.Bind(RmlUi::OnKeyUpGameWindow);
        gameWindow->MouseDown.Bind(RmlUi::OnMouseDownGameWindow);
        gameWindow->MouseUp.Bind(RmlUi::OnMouseUpGameWindow);
        gameWindow->MouseDoubleClick.Bind(RmlUi::OnMouseDoubleClickGameWindow);
        gameWindow->MouseWheel.Bind(RmlUi::OnMouseWheelGameWindow);
        gameWindow->MouseMove.Bind(RmlUi::OnMouseMoveGameWindow);
        gameWindow->MouseLeave.Bind(RmlUi::OnMouseLeaveGameWindow);
        gameWindow->TouchDown.Bind(RmlUi::OnTouchDownGameWindow);
        gameWindow->TouchMove.Bind(RmlUi::OnTouchMoveGameWindow);
        gameWindow->TouchUp.Bind(RmlUi::OnTouchUpGameWindow);
    }
#endif
    {
        Engine::MainWindow->CharInput.Bind(RmlUi::OnCharInput);
        Engine::MainWindow->KeyDown.Bind(RmlUi::OnKeyDown);
        Engine::MainWindow->KeyUp.Bind(RmlUi::OnKeyUp);
        Engine::MainWindow->MouseDown.Bind(RmlUi::OnMouseDown);
        Engine::MainWindow->MouseUp.Bind(RmlUi::OnMouseUp);
        Engine::MainWindow->MouseDoubleClick.Bind(RmlUi::OnMouseDoubleClick);
        Engine::MainWindow->MouseWheel.Bind(RmlUi::OnMouseWheel);
        Engine::MainWindow->MouseMove.Bind(RmlUi::OnMouseMove);
        Engine::MainWindow->MouseLeave.Bind(RmlUi::OnMouseLeave);
        Engine::MainWindow->TouchDown.Bind(RmlUi::OnTouchDown);
        Engine::MainWindow->TouchMove.Bind(RmlUi::OnTouchMove);
        Engine::MainWindow->TouchUp.Bind(RmlUi::OnTouchUp);
    }
}

void RmlUi::UnregisterEvents()
{
    Engine::LateUpdate.Unbind(&RmlUi::Update);
    if (MainRenderTask::Instance != nullptr)
        MainRenderTask::Instance->PostRender.Unbind(&RmlUi::Render);

#if USE_EDITOR
    // Register events for floating game window
    // TODO: Bind/Unbind events when window focus is lost/gained
    auto gameWindow = GetEditorGameWindow();
    if (gameWindow != nullptr)
    {
        gameWindow->CharInput.Unbind(RmlUi::OnCharInputGameWindow);
        gameWindow->KeyDown.Unbind(RmlUi::OnKeyDownGameWindow);
        gameWindow->KeyUp.Unbind(RmlUi::OnKeyUpGameWindow);
        gameWindow->MouseDown.Unbind(RmlUi::OnMouseDownGameWindow);
        gameWindow->MouseUp.Unbind(RmlUi::OnMouseUpGameWindow);
        gameWindow->MouseDoubleClick.Unbind(RmlUi::OnMouseDoubleClickGameWindow);
        gameWindow->MouseWheel.Unbind(RmlUi::OnMouseWheelGameWindow);
        gameWindow->MouseMove.Unbind(RmlUi::OnMouseMoveGameWindow);
        gameWindow->MouseLeave.Unbind(RmlUi::OnMouseLeaveGameWindow);
        gameWindow->TouchDown.Unbind(RmlUi::OnTouchDownGameWindow);
        gameWindow->TouchMove.Unbind(RmlUi::OnTouchMoveGameWindow);
        gameWindow->TouchUp.Unbind(RmlUi::OnTouchUpGameWindow);
    }
#endif
    if (Engine::MainWindow != nullptr)
    {
        Engine::MainWindow->CharInput.Unbind(RmlUi::OnCharInput);
        Engine::MainWindow->KeyDown.Unbind(RmlUi::OnKeyDown);
        Engine::MainWindow->KeyUp.Unbind(RmlUi::OnKeyUp);
        Engine::MainWindow->MouseDown.Unbind(RmlUi::OnMouseDown);
        Engine::MainWindow->MouseUp.Unbind(RmlUi::OnMouseUp);
        Engine::MainWindow->MouseDoubleClick.Unbind(RmlUi::OnMouseDoubleClick);
        Engine::MainWindow->MouseWheel.Unbind(RmlUi::OnMouseWheel);
        Engine::MainWindow->MouseMove.Unbind(RmlUi::OnMouseMove);
        Engine::MainWindow->MouseLeave.Unbind(RmlUi::OnMouseLeave);
        Engine::MainWindow->TouchDown.Unbind(RmlUi::OnTouchDown);
        Engine::MainWindow->TouchMove.Unbind(RmlUi::OnTouchMove);
        Engine::MainWindow->TouchUp.Unbind(RmlUi::OnTouchUp);
    }
}

void RmlUi::OnCharInput(Char c)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnCharInput(c);
}

void RmlUi::OnKeyDown(KeyboardKeys key)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnKeyDown(key);
}

void RmlUi::OnKeyUp(KeyboardKeys key)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnKeyUp(key);
}

void RmlUi::OnMouseDown(const Float2& mousePosition, MouseButton button)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

#if USE_EDITOR
    Float2 realPosition = Screen::ScreenToGameViewport(mousePosition);
    Rectangle bounds(Float2::Zero, Screen::GetSize());
    if (!bounds.Contains(realPosition))
        return;
#else
    Float2 realPosition = mousePosition;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseDown(realPosition, button);
}

void RmlUi::OnMouseUp(const Float2& mousePosition, MouseButton button)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

#if USE_EDITOR
    Float2 realPosition = Screen::ScreenToGameViewport(mousePosition);
    Rectangle bounds(Float2::Zero, Screen::GetSize());
    if (!bounds.Contains(realPosition))
        return;
#else
    Float2 realPosition = mousePosition;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseUp(realPosition, button);
}

void RmlUi::OnMouseDoubleClick(const Float2& mousePosition, MouseButton button)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

#if USE_EDITOR
    Float2 realPosition = Screen::ScreenToGameViewport(mousePosition);
    Rectangle bounds(Float2::Zero, Screen::GetSize());
    if (!bounds.Contains(realPosition))
        return;
#else
    Float2 realPosition = mousePosition;
#endif

    //if (focusedCanvas != nullptr)
    //    focusedCanvas->OnMouseDown(realPosition, button);
}

void RmlUi::OnMouseWheel(const Float2& mousePosition, float delta)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

#if USE_EDITOR
    Float2 realPosition = Screen::ScreenToGameViewport(mousePosition);
    Rectangle bounds(Float2::Zero, Screen::GetSize());
    if (!bounds.Contains(realPosition))
        return;
#else
    Float2 realPosition = mousePosition;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseWheel(realPosition, -delta);
}

void RmlUi::OnMouseMove(const Float2& mousePosition)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

#if USE_EDITOR
    Float2 realPosition = Screen::ScreenToGameViewport(mousePosition);
    Rectangle bounds(Float2::Zero, Screen::GetSize());
    if (!bounds.Contains(realPosition))
        return;
#else
    Float2 realPosition = mousePosition;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseMove(realPosition);
}

void RmlUi::OnMouseLeave()
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseLeave();
}

void RmlUi::OnTouchDown(const Float2& pointerPosition, int32 pointerIndex)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

#if USE_EDITOR
    Float2 realPosition = Screen::ScreenToGameViewport(pointerPosition);
    Rectangle bounds(Float2::Zero, Screen::GetSize());
    if (!bounds.Contains(realPosition))
        return;
#else
    Float2 realPosition = pointerPosition;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnTouchDown(realPosition, pointerIndex);
}

void RmlUi::OnTouchMove(const Float2& pointerPosition, int32 pointerIndex)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

#if USE_EDITOR
    Float2 realPosition = Screen::ScreenToGameViewport(pointerPosition);
    Rectangle bounds(Float2::Zero, Screen::GetSize());
    if (!bounds.Contains(realPosition))
        return;
#else
    Float2 realPosition = pointerPosition;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnTouchMove(realPosition, pointerIndex);
}

void RmlUi::OnTouchUp(const Float2& pointerPosition, int32 pointerIndex)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

#if USE_EDITOR
    Float2 realPosition = Screen::ScreenToGameViewport(pointerPosition);
    Rectangle bounds(Float2::Zero, Screen::GetSize());
    if (!bounds.Contains(realPosition))
        return;
#else
    Float2 realPosition = pointerPosition;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnTouchUp(realPosition, pointerIndex);
}

#if USE_EDITOR
void RmlUi::OnCharInputGameWindow(Char c)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnCharInput(c);
}

void RmlUi::OnKeyDownGameWindow(KeyboardKeys key)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnKeyDown(key);
}

void RmlUi::OnKeyUpGameWindow(KeyboardKeys key)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnKeyUp(key);
}

void RmlUi::OnMouseDownGameWindow(const Float2& mousePosition, MouseButton button)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    // FIXME: Offset by the height of the game window title bar
    Float2 realPosition = mousePosition - Float2(0, 25);

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseDown(realPosition, button);
}

void RmlUi::OnMouseUpGameWindow(const Float2& mousePosition, MouseButton button)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    // FIXME: Offset by the height of the game window title bar
    Float2 realPosition = mousePosition - Float2(0, 25);

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseUp(realPosition, button);
}

void RmlUi::OnMouseDoubleClickGameWindow(const Float2& mousePosition, MouseButton button)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    // FIXME: Offset by the height of the game window title bar
    //Float2 realPosition = pointerPosition - Float2(0, 25);

    //if (focusedCanvas != nullptr)
    //    focusedCanvas->OnMouseDown(pointerPosition, button);
}

void RmlUi::OnMouseWheelGameWindow(const Float2& mousePosition, float delta)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseWheel(mousePosition, -delta);
}

void RmlUi::OnMouseMoveGameWindow(const Float2& mousePosition)
{
    PROFILE_CPU();

    //auto gameWindow = GetEditorGameWindow();
    //if (gameWindow == nullptr || !gameWindow->IsFocused())
    //    return;

    if (!HasEditorGameViewportFocus())
        return;

    // FIXME: Offset by the height of the game window title bar
    Float2 realPosition = mousePosition - Float2(0, 25);

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseMove(realPosition);
}

void RmlUi::OnMouseLeaveGameWindow()
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseLeave();
}

void RmlUi::OnTouchDownGameWindow(const Float2& pointerPosition, int32 pointerIndex)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    // FIXME: Offset by the height of the game window title bar
    Float2 realPosition = pointerPosition - Float2(0, 25);

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnTouchDown(realPosition, pointerIndex);
}

void RmlUi::OnTouchMoveGameWindow(const Float2& pointerPosition, int32 pointerIndex)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    // FIXME: Offset by the height of the game window title bar
    Float2 realPosition = pointerPosition - Float2(0, 25);

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnTouchMove(pointerPosition, pointerIndex);
}

void RmlUi::OnTouchUpGameWindow(const Float2& pointerPosition, int32 pointerIndex)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    // FIXME: Offset by the height of the game window title bar
    Float2 realPosition = pointerPosition - Float2(0, 25);

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnTouchUp(realPosition, pointerIndex);
}
#endif

void RmlUi::Update()
{
    PROFILE_CPU_NAMED("RmlUi.Update");

    for (auto canvas : Canvases)
    {
        auto context = canvas->GetContext();
        context->Update();
    }
}

void RmlUi::Render(GPUContext* gpuContext, RenderContext& renderContext)
{
    PROFILE_GPU_CPU_NAMED("RmlUi.Render");

    for (auto canvas : Canvases)
    {
        PROFILE_GPU_CPU_NAMED("RmlUiCanvas");

        Rml::Context* context = canvas->GetContext();

        FlaxRenderInterfaceInstance->Begin(&renderContext, gpuContext, renderContext.Task->GetViewport());
        Viewport viewport = FlaxRenderInterfaceInstance->GetViewport();
        context->SetDimensions(Rml::Vector2i((int)viewport.Width, (int)viewport.Height));
        context->Render();
        FlaxRenderInterfaceInstance->End();
    }
}
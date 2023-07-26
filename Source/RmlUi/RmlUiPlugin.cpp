#include "RmlUiPlugin.h"

// Conflicts with both Flax and RmlUi Math.h
#undef RadiansToDegrees
#undef DegreesToRadians
#undef NormaliseAngle

#include "RmlUiCanvas.h"
#include "RmlUiImport.h"
#include "RmlUiHelpers.h"
#include "Flax/FlaxSystemInterface.h"
#include "Flax/FlaxFileInterface.h"
#include "Flax/FlaxRenderInterface.h"
#include "Flax/FlaxFontEngineInterface.h"

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

PluginDescription GetPluginDescription(bool isEditorPlugin)
{
    PluginDescription description;
    description.Name = String::Format(TEXT("RmlUi{0}"), isEditorPlugin ? TEXT(" (Editor Plugin)") : TEXT(""));
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

RmlUiPlugin::RmlUiPlugin(const SpawnParams& params)
    : GamePlugin(params)
{
    _description = GetPluginDescription(false);
}

void RmlUiPlugin::Initialize()
{
#if !USE_EDITOR
    InitializeRmlUi();
#endif
    GamePlugin::Initialize();
}

void RmlUiPlugin::Deinitialize()
{
#if !USE_EDITOR
    DeinitializeRmlUi();
#endif
    GamePlugin::Deinitialize();
}

#if USE_EDITOR
Array<Guid> RmlUiPlugin::GetReferences() const
{
    Array<Guid> references;

    Guid basicShaderGuid;
    Guid::Parse(StringAnsiView(RMLUI_PLUGIN_BASIC_SHADER), basicShaderGuid);
    references.Add(basicShaderGuid);

    return references;
}
#endif

bool RmlUiPlugin::IsInitialized()
{
    return RmlUiInitialized;
}

#if USE_EDITOR
RmlUiEditorPlugin::RmlUiEditorPlugin(const SpawnParams& params)
    : EditorPlugin(params)
{
    _description = GetPluginDescription(true);
}

void RmlUiEditorPlugin::Initialize()
{
    RegisterRmlUiImporters();

    RmlUiPlugin::InitializeRmlUi();
    EditorPlugin::Initialize();
}

void RmlUiEditorPlugin::Deinitialize()
{
    RmlUiPlugin::DeinitializeRmlUi();
    EditorPlugin::Deinitialize();
}
#endif

void RmlUiPlugin::InitializeRmlUi()
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

void RmlUiPlugin::DeinitializeRmlUi()
{
    if (!RmlUiInitialized)
        return;

    RmlUiInitialized = false;

    Engine::LateUpdate.Unbind(&RmlUiPlugin::Update);
    if (MainRenderTask::Instance != nullptr)
        MainRenderTask::Instance->PostRender.Unbind(&RmlUiPlugin::Render);
    UnregisterWindowEvents();
    UnregisterPlayEvents();

    FlaxFontEngineInterfaceInstance->ReleaseFontResources();

    Rml::Shutdown();

    FlaxRenderInterfaceInstance->ReleaseResources();

    Delete(FlaxSystemInterfaceInstance);
    Delete(FlaxRenderInterfaceInstance);
    Delete(FlaxFontEngineInterfaceInstance);
    Delete(FlaxFileInterfaceInstance);

    Canvases.Clear();
}

void RmlUiPlugin::RegisterCanvas(RmlUiCanvas* canvas)
{
    Canvases.Add(canvas);
}

void RmlUiPlugin::UnregisterCanvas(RmlUiCanvas* canvas)
{
    Canvases.Remove(canvas);
    if (FocusedCanvas == canvas)
        DefocusCanvas(canvas);
}

RmlUiCanvas* RmlUiPlugin::GetFocusedCanvas()
{
    return FocusedCanvas;
}

void RmlUiPlugin::FocusCanvas(RmlUiCanvas* canvas)
{
    FocusedCanvas = canvas;
}

void RmlUiPlugin::DefocusCanvas(RmlUiCanvas* canvas)
{
    if (FocusedCanvas == canvas)
        FocusedCanvas = nullptr;
}

void RmlUiPlugin::RegisterEvents()
{
    Engine::LateUpdate.Bind(&RmlUiPlugin::Update);
    MainRenderTask::Instance->PostRender.Bind(&RmlUiPlugin::Render);

    RegisterPlayEvents();
    RegisterWindowEvents();
}

void RmlUiPlugin::RegisterWindowEvents()
{
    Engine::Update.Bind(&RmlUiPlugin::OnRegisterWindowEvents);
}

void RmlUiPlugin::OnRegisterWindowEvents()
{
    Engine::Update.Unbind(&RmlUiPlugin::OnRegisterWindowEvents);

#if USE_EDITOR
    // Register events for floating game window
    // TODO: Bind/Unbind events when window focus is lost/gained
    if (GetEditorGameWindow() != nullptr)
    {
        auto gameWindow = GetEditorGameWindow();
        gameWindow->CharInput.Bind(RmlUiPlugin::OnCharInputGameWindow);
        gameWindow->KeyDown.Bind(RmlUiPlugin::OnKeyDownGameWindow);
        gameWindow->KeyUp.Bind(RmlUiPlugin::OnKeyUpGameWindow);
        gameWindow->MouseDown.Bind(RmlUiPlugin::OnMouseDownGameWindow);
        gameWindow->MouseUp.Bind(RmlUiPlugin::OnMouseUpGameWindow);
        gameWindow->MouseDoubleClick.Bind(RmlUiPlugin::OnMouseDoubleClickGameWindow);
        gameWindow->MouseWheel.Bind(RmlUiPlugin::OnMouseWheelGameWindow);
        gameWindow->MouseMove.Bind(RmlUiPlugin::OnMouseMoveGameWindow);
        gameWindow->MouseLeave.Bind(RmlUiPlugin::OnMouseLeaveGameWindow);
        gameWindow->TouchDown.Bind(RmlUiPlugin::OnTouchDownGameWindow);
        gameWindow->TouchMove.Bind(RmlUiPlugin::OnTouchMoveGameWindow);
        gameWindow->TouchUp.Bind(RmlUiPlugin::OnTouchUpGameWindow);
        if (Engine::MainWindow != nullptr)
        {
            Engine::MainWindow->MouseMove.Bind(RmlUiPlugin::OnMouseMove);
            Engine::MainWindow->TouchMove.Bind(RmlUiPlugin::OnTouchMove);
        }
    }
    else
#endif
    {
        if (Engine::MainWindow != nullptr)
        {
            Engine::MainWindow->CharInput.Bind(RmlUiPlugin::OnCharInput);
            Engine::MainWindow->KeyDown.Bind(RmlUiPlugin::OnKeyDown);
            Engine::MainWindow->KeyUp.Bind(RmlUiPlugin::OnKeyUp);
            Engine::MainWindow->MouseDown.Bind(RmlUiPlugin::OnMouseDown);
            Engine::MainWindow->MouseUp.Bind(RmlUiPlugin::OnMouseUp);
            Engine::MainWindow->MouseDoubleClick.Bind(RmlUiPlugin::OnMouseDoubleClick);
            Engine::MainWindow->MouseWheel.Bind(RmlUiPlugin::OnMouseWheel);
            Engine::MainWindow->MouseMove.Bind(RmlUiPlugin::OnMouseMove);
            Engine::MainWindow->MouseLeave.Bind(RmlUiPlugin::OnMouseLeave);
            Engine::MainWindow->TouchDown.Bind(RmlUiPlugin::OnTouchDown);
            Engine::MainWindow->TouchMove.Bind(RmlUiPlugin::OnTouchMove);
            Engine::MainWindow->TouchUp.Bind(RmlUiPlugin::OnTouchUp);
        }
    }
}

void RmlUiPlugin::UnregisterWindowEvents()
{
#if USE_EDITOR
    // Register events for floating game window
    // TODO: Bind/Unbind events when window focus is lost/gained
    if (GetEditorGameWindow() != nullptr)
    {
        auto gameWindow = GetEditorGameWindow();
        gameWindow->CharInput.Unbind(RmlUiPlugin::OnCharInputGameWindow);
        gameWindow->KeyDown.Unbind(RmlUiPlugin::OnKeyDownGameWindow);
        gameWindow->KeyUp.Unbind(RmlUiPlugin::OnKeyUpGameWindow);
        gameWindow->MouseDown.Unbind(RmlUiPlugin::OnMouseDownGameWindow);
        gameWindow->MouseUp.Unbind(RmlUiPlugin::OnMouseUpGameWindow);
        gameWindow->MouseDoubleClick.Unbind(RmlUiPlugin::OnMouseDoubleClickGameWindow);
        gameWindow->MouseWheel.Unbind(RmlUiPlugin::OnMouseWheelGameWindow);
        gameWindow->MouseMove.Unbind(RmlUiPlugin::OnMouseMoveGameWindow);
        gameWindow->MouseLeave.Unbind(RmlUiPlugin::OnMouseLeaveGameWindow);
        gameWindow->TouchDown.Unbind(RmlUiPlugin::OnTouchDownGameWindow);
        gameWindow->TouchMove.Unbind(RmlUiPlugin::OnTouchMoveGameWindow);
        gameWindow->TouchUp.Unbind(RmlUiPlugin::OnTouchUpGameWindow);
    }
#endif
    if (Engine::MainWindow != nullptr)
    {
        Engine::MainWindow->CharInput.Unbind(RmlUiPlugin::OnCharInput);
        Engine::MainWindow->KeyDown.Unbind(RmlUiPlugin::OnKeyDown);
        Engine::MainWindow->KeyUp.Unbind(RmlUiPlugin::OnKeyUp);
        Engine::MainWindow->MouseDown.Unbind(RmlUiPlugin::OnMouseDown);
        Engine::MainWindow->MouseUp.Unbind(RmlUiPlugin::OnMouseUp);
        Engine::MainWindow->MouseDoubleClick.Unbind(RmlUiPlugin::OnMouseDoubleClick);
        Engine::MainWindow->MouseWheel.Unbind(RmlUiPlugin::OnMouseWheel);
        Engine::MainWindow->MouseMove.Unbind(RmlUiPlugin::OnMouseMove);
        Engine::MainWindow->MouseLeave.Unbind(RmlUiPlugin::OnMouseLeave);
        Engine::MainWindow->TouchDown.Unbind(RmlUiPlugin::OnTouchDown);
        Engine::MainWindow->TouchMove.Unbind(RmlUiPlugin::OnTouchMove);
        Engine::MainWindow->TouchUp.Unbind(RmlUiPlugin::OnTouchUp);
    }
}

void RmlUiPlugin::OnCharInput(Char c)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnCharInput(c);
}

void RmlUiPlugin::OnKeyDown(KeyboardKeys key)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnKeyDown(key);
}

void RmlUiPlugin::OnKeyUp(KeyboardKeys key)
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnKeyUp(key);
}

void RmlUiPlugin::OnMouseDown(const Float2& mousePosition, MouseButton button)
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

void RmlUiPlugin::OnMouseUp(const Float2& mousePosition, MouseButton button)
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

void RmlUiPlugin::OnMouseDoubleClick(const Float2& mousePosition, MouseButton button)
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

void RmlUiPlugin::OnMouseWheel(const Float2& mousePosition, float delta)
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

void RmlUiPlugin::OnMouseMove(const Float2& mousePosition)
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

void RmlUiPlugin::OnMouseLeave()
{
    PROFILE_CPU();

#if USE_EDITOR
    if (!HasEditorGameViewportFocus())
        return;
#endif

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseLeave();
}

void RmlUiPlugin::OnTouchDown(const Float2& pointerPosition, int32 pointerIndex)
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

void RmlUiPlugin::OnTouchMove(const Float2& pointerPosition, int32 pointerIndex)
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

void RmlUiPlugin::OnTouchUp(const Float2& pointerPosition, int32 pointerIndex)
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
void RmlUiPlugin::OnCharInputGameWindow(Char c)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnCharInput(c);
}

void RmlUiPlugin::OnKeyDownGameWindow(KeyboardKeys key)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnKeyDown(key);
}

void RmlUiPlugin::OnKeyUpGameWindow(KeyboardKeys key)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnKeyUp(key);
}

void RmlUiPlugin::OnMouseDownGameWindow(const Float2& mousePosition, MouseButton button)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    // FIXME: Offset by the height of the game window title bar
    Float2 realPosition = mousePosition - Float2(0, 25);

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseDown(realPosition, button);
}

void RmlUiPlugin::OnMouseUpGameWindow(const Float2& mousePosition, MouseButton button)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    // FIXME: Offset by the height of the game window title bar
    Float2 realPosition = mousePosition - Float2(0, 25);

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseUp(realPosition, button);
}

void RmlUiPlugin::OnMouseDoubleClickGameWindow(const Float2& mousePosition, MouseButton button)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    // FIXME: Offset by the height of the game window title bar
    //Float2 realPosition = pointerPosition - Float2(0, 25);

    //if (focusedCanvas != nullptr)
    //    focusedCanvas->OnMouseDown(pointerPosition, button);
}

void RmlUiPlugin::OnMouseWheelGameWindow(const Float2& mousePosition, float delta)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseWheel(mousePosition, -delta);
}

void RmlUiPlugin::OnMouseMoveGameWindow(const Float2& mousePosition)
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

void RmlUiPlugin::OnMouseLeaveGameWindow()
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnMouseLeave();
}

void RmlUiPlugin::OnTouchDownGameWindow(const Float2& pointerPosition, int32 pointerIndex)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    // FIXME: Offset by the height of the game window title bar
    Float2 realPosition = pointerPosition - Float2(0, 25);

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnTouchDown(realPosition, pointerIndex);
}

void RmlUiPlugin::OnTouchMoveGameWindow(const Float2& pointerPosition, int32 pointerIndex)
{
    PROFILE_CPU();

    if (!HasEditorGameViewportFocus())
        return;

    // FIXME: Offset by the height of the game window title bar
    Float2 realPosition = pointerPosition - Float2(0, 25);

    if (FocusedCanvas != nullptr)
        FocusedCanvas->OnTouchMove(pointerPosition, pointerIndex);
}

void RmlUiPlugin::OnTouchUpGameWindow(const Float2& pointerPosition, int32 pointerIndex)
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

void RmlUiPlugin::Update()
{
    PROFILE_CPU_NAMED("RmlUi.Update");

    for (auto canvas : Canvases)
    {
        auto context = canvas->GetContext();
        context->Update();
    }
}

void RmlUiPlugin::Render(GPUContext* gpuContext, RenderContext& renderContext)
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

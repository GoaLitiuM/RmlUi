using FlaxEngine;
using FlaxEngine.GUI;
using System;
using FlaxEngine.Utilities;
#if FLAX_EDITOR
using FlaxEditor.States;
using FlaxEditor;
using FlaxEditor.Windows;
#endif

namespace RmlUi;

/// <summary>
/// Helper class for managing RmlUi custom assets.
/// </summary>
[Unmanaged]
public static class RmlUiHelpers
{
#if FLAX_EDITOR
    /// <summary>
    /// Returns the GameWindow of Editor.
    /// </summary>
    public static IntPtr GetEditorGameWindow()
    {
        GameWindow gameWindow = Editor.Instance?.Windows?.GameWin;
        if (gameWindow != null)
        {
            var win = gameWindow.Root as WindowRootControl;
            if (win != null)
                return FlaxEngine.Object.GetUnmanagedPtr(win.Window);
        }
        return IntPtr.Zero;
    }

    /// <summary>
    /// Returns true if the GameWindow is focused.
    /// </summary>
    public static bool HasEditorGameViewportFocus()
    {
        GameWindow gameWindow = Editor.Instance?.Windows?.GameWin;
        if (gameWindow != null && gameWindow.ContainsFocus)
        {
            var win = gameWindow.Root;
            if (win?.RootWindow is WindowRootControl root && root.Window && root.Window.IsFocused)
            {
                if (Editor.Instance.StateMachine.IsPlayMode && Editor.Instance.StateMachine.PlayingState.IsPaused)
                    return false;
                return true;
            }
        }
        return false;
    }

    /// <summary>
    /// Registers for editor events for start/end of the simulation
    /// </summary>
    public static void RegisterPlayEvents()
    {
        PlayingState playingState = (PlayingState)Editor.Instance?.StateMachine?.GetState<PlayingState>();
        if(playingState != null)
        {
            playingState.SceneDuplicating += OnStartPlay;
            playingState.SceneRestored += OnStopPlay;
        }
    }

    /// <summary>
    /// Unregisters from editor events for start/end of the simulation
    /// </summary>
    public static void UnregisterPlayEvents()
    {
        PlayingState playingState = (PlayingState)Editor.Instance?.StateMachine?.GetState<PlayingState>();
        if(playingState != null)
        {
            playingState.SceneDuplicating -= OnStartPlay;
            playingState.SceneRestored -= OnStopPlay;
        }
    }

    /// <summary>
    /// Fires registartion code for when the editor simulation starts
    /// </summary>
    public static void OnStartPlay()
    {
        RmlUiPlugin.UnregisterWindowEvents();
        RmlUiPlugin.RegisterWindowEvents();
    }

    /// <summary>
    /// Fires registartion code for when the editor simulation starts
    /// </summary>
    public static void OnStopPlay()
    {
        RmlUiPlugin.UnregisterWindowEvents();
        RmlUiPlugin.RegisterWindowEvents();
    }

#endif
}

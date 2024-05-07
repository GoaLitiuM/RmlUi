#pragma once

#include <ThirdParty/RmlUi/Core/Input.h>

#include <Engine/Input/Input.h>

KeyboardKeys TranslateRmlUiKey(Rml::Input::KeyIdentifier keyIdentifier);
Rml::Input::KeyIdentifier TranslateFlaxKey(KeyboardKeys key);
int TranslateFlaxMouseButton(MouseButton button);
Window* GetEditorGameWindow();
bool HasEditorGameViewportFocus();
void RegisterPlayEvents();
void UnregisterPlayEvents();

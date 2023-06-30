#include "FlaxSystemInterface.h"

#include <ThirdParty/RmlUi/Core.h>
#include <ThirdParty/RmlUi/Core/SystemInterface.h>

#include <Engine/Engine/Time.h>
#include <Engine/Core/Log.h>

#include <Engine/Core/Config/GameSettings.h>
#include <Engine/Platform/Clipboard.h>
#include <Engine/Engine/Engine.h>
#include <Engine/Platform/Window.h>

double FlaxSystemInterface::GetElapsedTime()
{
    return (double)Time::GetTimeSinceStartup();
}

int FlaxSystemInterface::TranslateString(Rml::String& translated, const Rml::String& input)
{
    // TODO: Implement
    translated = input;
    return 0;
}

bool FlaxSystemInterface::LogMessage(Rml::Log::Type type, const Rml::String& message)
{
    LogType logType;
    switch (type)
    {
        case Rml::Log::Type::LT_ASSERT:
        case Rml::Log::Type::LT_ERROR:
            logType = LogType::Error;
            break;
        case Rml::Log::Type::LT_WARNING:
            logType = LogType::Warning;
            break;
        default:
            logType = LogType::Info;
    }
    Log::Logger::Write(logType, String::Format(TEXT("RmlUi: {0}"), String(message.c_str())));
    return true;
}

void FlaxSystemInterface::SetMouseCursor(const Rml::String& cursor_name)
{
    StringAnsi cursorName(cursor_name.c_str(), (int)cursor_name.length());
    CursorType cursor;
    if (cursorName.IsEmpty() || cursor_name == "arrow")
        cursor = CursorType::Default;
    else if (cursorName == "move")
        cursor = CursorType::SizeAll;
    else if (cursorName == "pointer")
        cursor = CursorType::Hand;
    else if (cursorName == "resize")
        cursor = CursorType::SizeNWSE;
    else if (cursorName == "cross")
        cursor = CursorType::Cross;
    else if (cursorName == "text")
        cursor = CursorType::IBeam;
    else if (cursorName == "unavailable")
        cursor = CursorType::No;
    else if (cursorName.StartsWith("rmlui-scroll"))
        cursor = CursorType::SizeAll;
    else
        cursor = CursorType::Default;
    Engine::MainWindow->SetCursor(cursor);
}

void FlaxSystemInterface::SetClipboardText(const Rml::String& text)
{
    String clipboardText = StringAnsiView(text.c_str(), (int)text.length()).ToString();
    Clipboard::SetText(clipboardText);
}

void FlaxSystemInterface::GetClipboardText(Rml::String& text)
{
    StringAnsi clipboardText = Clipboard::GetText().ToStringAnsi();
    text.assign(clipboardText.Get(), clipboardText.Length());
}
#pragma once

#include <ThirdParty/RmlUi/Core/SystemInterface.h>

/// <summary>
/// The SystemInterface implementation for Flax Engine.
/// </summary>
class FlaxSystemInterface : public Rml::SystemInterface
{
public:
    double GetElapsedTime() override;
    int TranslateString(Rml::String& translated, const Rml::String& input) override;
    bool LogMessage(Rml::Log::Type type, const Rml::String& message) override;
    void SetMouseCursor(const Rml::String& cursor_name) override;
    void SetClipboardText(const Rml::String& text) override;
    void GetClipboardText(Rml::String& text) override;
};

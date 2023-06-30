#include "RmlUiHelpers.h"

#include <Engine/Scripting/Scripting.h>
#include <Engine/Scripting/ManagedCLR/MClass.h>
#include <Engine/Scripting/ManagedCLR/MMethod.h>
#include <Engine/Scripting/ManagedCLR/MUtils.h>

KeyboardKeys TranslateRmlUiKey(Rml::Input::KeyIdentifier keyIdentifier)
{
    switch (keyIdentifier)
    {
        case Rml::Input::KeyIdentifier::KI_UNKNOWN: return KeyboardKeys::None;
        case Rml::Input::KeyIdentifier::KI_SPACE: return KeyboardKeys::Spacebar;
        case Rml::Input::KeyIdentifier::KI_0: return KeyboardKeys::Alpha0;
        case Rml::Input::KeyIdentifier::KI_1: return KeyboardKeys::Alpha1;
        case Rml::Input::KeyIdentifier::KI_2: return KeyboardKeys::Alpha2;
        case Rml::Input::KeyIdentifier::KI_3: return KeyboardKeys::Alpha3;
        case Rml::Input::KeyIdentifier::KI_4: return KeyboardKeys::Alpha4;
        case Rml::Input::KeyIdentifier::KI_5: return KeyboardKeys::Alpha5;
        case Rml::Input::KeyIdentifier::KI_6: return KeyboardKeys::Alpha6;
        case Rml::Input::KeyIdentifier::KI_7: return KeyboardKeys::Alpha7;
        case Rml::Input::KeyIdentifier::KI_8: return KeyboardKeys::Alpha8;
        case Rml::Input::KeyIdentifier::KI_9: return KeyboardKeys::Alpha9;
        case Rml::Input::KeyIdentifier::KI_A: return KeyboardKeys::A;
        case Rml::Input::KeyIdentifier::KI_B: return KeyboardKeys::B;
        case Rml::Input::KeyIdentifier::KI_C: return KeyboardKeys::C;
        case Rml::Input::KeyIdentifier::KI_D: return KeyboardKeys::D;
        case Rml::Input::KeyIdentifier::KI_E: return KeyboardKeys::E;
        case Rml::Input::KeyIdentifier::KI_F: return KeyboardKeys::F;
        case Rml::Input::KeyIdentifier::KI_G: return KeyboardKeys::G;
        case Rml::Input::KeyIdentifier::KI_H: return KeyboardKeys::H;
        case Rml::Input::KeyIdentifier::KI_I: return KeyboardKeys::I;
        case Rml::Input::KeyIdentifier::KI_J: return KeyboardKeys::J;
        case Rml::Input::KeyIdentifier::KI_K: return KeyboardKeys::K;
        case Rml::Input::KeyIdentifier::KI_L: return KeyboardKeys::L;
        case Rml::Input::KeyIdentifier::KI_M: return KeyboardKeys::M;
        case Rml::Input::KeyIdentifier::KI_N: return KeyboardKeys::N;
        case Rml::Input::KeyIdentifier::KI_O: return KeyboardKeys::O;
        case Rml::Input::KeyIdentifier::KI_P: return KeyboardKeys::P;
        case Rml::Input::KeyIdentifier::KI_Q: return KeyboardKeys::Q;
        case Rml::Input::KeyIdentifier::KI_R: return KeyboardKeys::R;
        case Rml::Input::KeyIdentifier::KI_S: return KeyboardKeys::S;
        case Rml::Input::KeyIdentifier::KI_T: return KeyboardKeys::T;
        case Rml::Input::KeyIdentifier::KI_U: return KeyboardKeys::U;
        case Rml::Input::KeyIdentifier::KI_V: return KeyboardKeys::V;
        case Rml::Input::KeyIdentifier::KI_W: return KeyboardKeys::W;
        case Rml::Input::KeyIdentifier::KI_X: return KeyboardKeys::X;
        case Rml::Input::KeyIdentifier::KI_Y: return KeyboardKeys::Y;
        case Rml::Input::KeyIdentifier::KI_Z: return KeyboardKeys::Z;
        //case Rml::Input::KeyIdentifier::KI_OEM_1: return KeyboardKeys::OEM_1;
        //case Rml::Input::KeyIdentifier::KI_OEM_PLUS: return KeyboardKeys::OEM_PLUS;
        //case Rml::Input::KeyIdentifier::KI_OEM_COMMA: return KeyboardKeys::OEM_COMMA;
        //case Rml::Input::KeyIdentifier::KI_OEM_MINUS: return KeyboardKeys::OEM_MINUS;
        //case Rml::Input::KeyIdentifier::KI_OEM_PERIOD: return KeyboardKeys::OEM_PERIOD;
        //case Rml::Input::KeyIdentifier::KI_OEM_2: return KeyboardKeys::OEM_2;
        //case Rml::Input::KeyIdentifier::KI_OEM_3: return KeyboardKeys::OEM_3;
        //case Rml::Input::KeyIdentifier::KI_OEM_4: return KeyboardKeys::OEM_4;
        //case Rml::Input::KeyIdentifier::KI_OEM_5: return KeyboardKeys::OEM_5;
        //case Rml::Input::KeyIdentifier::KI_OEM_6: return KeyboardKeys::OEM_6;
        //case Rml::Input::KeyIdentifier::KI_OEM_7: return KeyboardKeys::OEM_7;
        case Rml::Input::KeyIdentifier::KI_OEM_8: return KeyboardKeys::Oem8;
        case Rml::Input::KeyIdentifier::KI_OEM_102: return KeyboardKeys::Oem102;
        case Rml::Input::KeyIdentifier::KI_NUMPAD0: return KeyboardKeys::Numpad0;
        case Rml::Input::KeyIdentifier::KI_NUMPAD1: return KeyboardKeys::Numpad1;
        case Rml::Input::KeyIdentifier::KI_NUMPAD2: return KeyboardKeys::Numpad2;
        case Rml::Input::KeyIdentifier::KI_NUMPAD3: return KeyboardKeys::Numpad3;
        case Rml::Input::KeyIdentifier::KI_NUMPAD4: return KeyboardKeys::Numpad4;
        case Rml::Input::KeyIdentifier::KI_NUMPAD5: return KeyboardKeys::Numpad5;
        case Rml::Input::KeyIdentifier::KI_NUMPAD6: return KeyboardKeys::Numpad6;
        case Rml::Input::KeyIdentifier::KI_NUMPAD7: return KeyboardKeys::Numpad7;
        case Rml::Input::KeyIdentifier::KI_NUMPAD8: return KeyboardKeys::Numpad8;
        case Rml::Input::KeyIdentifier::KI_NUMPAD9: return KeyboardKeys::Numpad9;
        //case Rml::Input::KeyIdentifier::KI_NUMPADENTER: return KeyboardKeys::NumpadReturn;
        case Rml::Input::KeyIdentifier::KI_MULTIPLY: return KeyboardKeys::NumpadMultiply;
        case Rml::Input::KeyIdentifier::KI_ADD: return KeyboardKeys::NumpadAdd;
        case Rml::Input::KeyIdentifier::KI_SEPARATOR: return KeyboardKeys::NumpadSeparator;
        case Rml::Input::KeyIdentifier::KI_SUBTRACT: return KeyboardKeys::NumpadSubtract;
        case Rml::Input::KeyIdentifier::KI_DECIMAL: return KeyboardKeys::NumpadDecimal;
        case Rml::Input::KeyIdentifier::KI_DIVIDE: return KeyboardKeys::NumpadDivide;
        //case Rml::Input::KeyIdentifier::KI_OEM_NEC_EQUAL: return KeyboardKeys::numpadeq;
        case Rml::Input::KeyIdentifier::KI_BACK: return KeyboardKeys::Backspace;
        case Rml::Input::KeyIdentifier::KI_TAB: return KeyboardKeys::Tab;
        case Rml::Input::KeyIdentifier::KI_CLEAR: return KeyboardKeys::Clear;
        case Rml::Input::KeyIdentifier::KI_RETURN: return KeyboardKeys::Return;
        case Rml::Input::KeyIdentifier::KI_PAUSE: return KeyboardKeys::Pause;
        case Rml::Input::KeyIdentifier::KI_CAPITAL: return KeyboardKeys::Capital;
        case Rml::Input::KeyIdentifier::KI_KANA: return KeyboardKeys::Kana;
        case Rml::Input::KeyIdentifier::KI_HANGUL: return KeyboardKeys::Hangul;
        case Rml::Input::KeyIdentifier::KI_JUNJA: return KeyboardKeys::Junja;
        case Rml::Input::KeyIdentifier::KI_FINAL: return KeyboardKeys::Final;
        case Rml::Input::KeyIdentifier::KI_HANJA: return KeyboardKeys::Hanja;
        case Rml::Input::KeyIdentifier::KI_KANJI: return KeyboardKeys::Kanji;
        case Rml::Input::KeyIdentifier::KI_ESCAPE: return KeyboardKeys::Escape;
        case Rml::Input::KeyIdentifier::KI_CONVERT: return KeyboardKeys::Convert;
        case Rml::Input::KeyIdentifier::KI_NONCONVERT: return KeyboardKeys::Nonconvert;
        case Rml::Input::KeyIdentifier::KI_ACCEPT: return KeyboardKeys::Accept;
        case Rml::Input::KeyIdentifier::KI_MODECHANGE: return KeyboardKeys::Modechange;
        case Rml::Input::KeyIdentifier::KI_PRIOR: return KeyboardKeys::PageUp;
        case Rml::Input::KeyIdentifier::KI_NEXT: return KeyboardKeys::PageDown;
        case Rml::Input::KeyIdentifier::KI_END: return KeyboardKeys::End;
        case Rml::Input::KeyIdentifier::KI_HOME: return KeyboardKeys::Home;
        case Rml::Input::KeyIdentifier::KI_LEFT: return KeyboardKeys::ArrowLeft;
        case Rml::Input::KeyIdentifier::KI_UP: return KeyboardKeys::ArrowUp;
        case Rml::Input::KeyIdentifier::KI_RIGHT: return KeyboardKeys::ArrowRight;
        case Rml::Input::KeyIdentifier::KI_DOWN: return KeyboardKeys::ArrowDown;
        case Rml::Input::KeyIdentifier::KI_SELECT: return KeyboardKeys::Select;
        case Rml::Input::KeyIdentifier::KI_PRINT: return KeyboardKeys::Print;
        case Rml::Input::KeyIdentifier::KI_EXECUTE: return KeyboardKeys::Execute;
        case Rml::Input::KeyIdentifier::KI_SNAPSHOT: return KeyboardKeys::PrintScreen;
        case Rml::Input::KeyIdentifier::KI_INSERT: return KeyboardKeys::Insert;
        case Rml::Input::KeyIdentifier::KI_DELETE: return KeyboardKeys::Delete;
        case Rml::Input::KeyIdentifier::KI_HELP: return KeyboardKeys::Help;
        case Rml::Input::KeyIdentifier::KI_LWIN: return KeyboardKeys::LeftWindows;
        case Rml::Input::KeyIdentifier::KI_RWIN: return KeyboardKeys::RightWindows;
        case Rml::Input::KeyIdentifier::KI_APPS: return KeyboardKeys::Applications;
        //case Rml::Input::KeyIdentifier::KI_POWER: return KeyboardKeys::POWER;
        case Rml::Input::KeyIdentifier::KI_SLEEP: return KeyboardKeys::Sleep;
        //case Rml::Input::KeyIdentifier::KI_WAKE: return KeyboardKeys::WAKE;
        case Rml::Input::KeyIdentifier::KI_F1: return KeyboardKeys::F1;
        case Rml::Input::KeyIdentifier::KI_F2: return KeyboardKeys::F2;
        case Rml::Input::KeyIdentifier::KI_F3: return KeyboardKeys::F3;
        case Rml::Input::KeyIdentifier::KI_F4: return KeyboardKeys::F4;
        case Rml::Input::KeyIdentifier::KI_F5: return KeyboardKeys::F5;
        case Rml::Input::KeyIdentifier::KI_F6: return KeyboardKeys::F6;
        case Rml::Input::KeyIdentifier::KI_F7: return KeyboardKeys::F7;
        case Rml::Input::KeyIdentifier::KI_F8: return KeyboardKeys::F8;
        case Rml::Input::KeyIdentifier::KI_F9: return KeyboardKeys::F9;
        case Rml::Input::KeyIdentifier::KI_F10: return KeyboardKeys::F10;
        case Rml::Input::KeyIdentifier::KI_F11: return KeyboardKeys::F11;
        case Rml::Input::KeyIdentifier::KI_F12: return KeyboardKeys::F12;
        case Rml::Input::KeyIdentifier::KI_F13: return KeyboardKeys::F13;
        case Rml::Input::KeyIdentifier::KI_F14: return KeyboardKeys::F14;
        case Rml::Input::KeyIdentifier::KI_F15: return KeyboardKeys::F15;
        case Rml::Input::KeyIdentifier::KI_F16: return KeyboardKeys::F16;
        case Rml::Input::KeyIdentifier::KI_F17: return KeyboardKeys::F17;
        case Rml::Input::KeyIdentifier::KI_F18: return KeyboardKeys::F18;
        case Rml::Input::KeyIdentifier::KI_F19: return KeyboardKeys::F19;
        case Rml::Input::KeyIdentifier::KI_F20: return KeyboardKeys::F20;
        case Rml::Input::KeyIdentifier::KI_F21: return KeyboardKeys::F21;
        case Rml::Input::KeyIdentifier::KI_F22: return KeyboardKeys::F22;
        case Rml::Input::KeyIdentifier::KI_F23: return KeyboardKeys::F23;
        case Rml::Input::KeyIdentifier::KI_F24: return KeyboardKeys::F24;
        case Rml::Input::KeyIdentifier::KI_NUMLOCK: return KeyboardKeys::Numlock;
        case Rml::Input::KeyIdentifier::KI_SCROLL: return KeyboardKeys::Scroll;
        //case Rml::Input::KeyIdentifier::KI_OEM_FJ_JISHO: return KeyboardKeys::OEM_FJ_JISHO;
        //case Rml::Input::KeyIdentifier::KI_OEM_FJ_MASSHOU: return KeyboardKeys::OEM_FJ_MASSHOU;
        //case Rml::Input::KeyIdentifier::KI_OEM_FJ_TOUROKU: return KeyboardKeys::OEM_FJ_TOUROKU;
        //case Rml::Input::KeyIdentifier::KI_OEM_FJ_LOYA: return KeyboardKeys::OEM_FJ_LOYA;
        //case Rml::Input::KeyIdentifier::KI_OEM_FJ_ROYA: return KeyboardKeys::OEM_FJ_ROYA;
        case Rml::Input::KeyIdentifier::KI_LSHIFT: return KeyboardKeys::Shift;
        //case Rml::Input::KeyIdentifier::KI_RSHIFT: return KeyboardKeys::RSHIFT;
        case Rml::Input::KeyIdentifier::KI_LCONTROL: return KeyboardKeys::Control;
        //case Rml::Input::KeyIdentifier::KI_RCONTROL: return KeyboardKeys::RCONTROL;
        case Rml::Input::KeyIdentifier::KI_LMENU: return KeyboardKeys::LeftMenu;
        case Rml::Input::KeyIdentifier::KI_RMENU: return KeyboardKeys::RightMenu;
        case Rml::Input::KeyIdentifier::KI_BROWSER_BACK: return KeyboardKeys::BrowserBack;
        case Rml::Input::KeyIdentifier::KI_BROWSER_FORWARD: return KeyboardKeys::BrowserForward;
        case Rml::Input::KeyIdentifier::KI_BROWSER_REFRESH: return KeyboardKeys::BrowserRefresh;
        case Rml::Input::KeyIdentifier::KI_BROWSER_STOP: return KeyboardKeys::BrowserStop;
        case Rml::Input::KeyIdentifier::KI_BROWSER_SEARCH: return KeyboardKeys::BrowserSearch;
        case Rml::Input::KeyIdentifier::KI_BROWSER_FAVORITES: return KeyboardKeys::BrowserFavorites;
        case Rml::Input::KeyIdentifier::KI_BROWSER_HOME: return KeyboardKeys::BrowserHome;
        case Rml::Input::KeyIdentifier::KI_VOLUME_MUTE: return KeyboardKeys::VolumeMute;
        case Rml::Input::KeyIdentifier::KI_VOLUME_DOWN: return KeyboardKeys::VolumeDown;
        case Rml::Input::KeyIdentifier::KI_VOLUME_UP: return KeyboardKeys::VolumeUp;
        case Rml::Input::KeyIdentifier::KI_MEDIA_NEXT_TRACK: return KeyboardKeys::MediaNextTrack;
        case Rml::Input::KeyIdentifier::KI_MEDIA_PREV_TRACK: return KeyboardKeys::MediaPrevTrack;
        case Rml::Input::KeyIdentifier::KI_MEDIA_STOP: return KeyboardKeys::MediaStop;
        case Rml::Input::KeyIdentifier::KI_MEDIA_PLAY_PAUSE: return KeyboardKeys::MediaPlayPause;
        case Rml::Input::KeyIdentifier::KI_LAUNCH_MAIL: return KeyboardKeys::LaunchMail;
        case Rml::Input::KeyIdentifier::KI_LAUNCH_MEDIA_SELECT: return KeyboardKeys::LaunchMediaSelect;
        case Rml::Input::KeyIdentifier::KI_LAUNCH_APP1: return KeyboardKeys::LaunchApp1;
        case Rml::Input::KeyIdentifier::KI_LAUNCH_APP2: return KeyboardKeys::LaunchApp2;
        //case Rml::Input::KeyIdentifier::KI_OEM_AX: return KeyboardKeys::OEM_AX;
        //case Rml::Input::KeyIdentifier::KI_ICO_HELP: return KeyboardKeys::ICO_HELP;
        //case Rml::Input::KeyIdentifier::KI_ICO_00: return KeyboardKeys::ICO_00;
        case Rml::Input::KeyIdentifier::KI_PROCESSKEY: return KeyboardKeys::Processkey;
        //case Rml::Input::KeyIdentifier::KI_ICO_CLEAR: return KeyboardKeys::ICO_CLEAR;
        case Rml::Input::KeyIdentifier::KI_ATTN: return KeyboardKeys::Attn;
        case Rml::Input::KeyIdentifier::KI_CRSEL: return KeyboardKeys::Crsel;
        case Rml::Input::KeyIdentifier::KI_EXSEL: return KeyboardKeys::Exsel;
        case Rml::Input::KeyIdentifier::KI_EREOF: return KeyboardKeys::Ereof;
        case Rml::Input::KeyIdentifier::KI_PLAY: return KeyboardKeys::Play;
        case Rml::Input::KeyIdentifier::KI_ZOOM: return KeyboardKeys::Zoom;
        case Rml::Input::KeyIdentifier::KI_PA1: return KeyboardKeys::Pa1;
        case Rml::Input::KeyIdentifier::KI_OEM_CLEAR: return KeyboardKeys::OemClear;
        //case Rml::Input::KeyIdentifier::KI_LMETA: return KeyboardKeys::LMETA;
        //case Rml::Input::KeyIdentifier::KI_RMETA: return KeyboardKeys::RMETA;
        default: return KeyboardKeys::None;
    }
}

Rml::Input::KeyIdentifier TranslateFlaxKey(KeyboardKeys key)
{
    switch (key)
    {
        case KeyboardKeys::None: return Rml::Input::KeyIdentifier::KI_UNKNOWN;
        case KeyboardKeys::Spacebar: return Rml::Input::KeyIdentifier::KI_SPACE;
        case KeyboardKeys::Alpha0: return Rml::Input::KeyIdentifier::KI_0;
        case KeyboardKeys::Alpha1: return Rml::Input::KeyIdentifier::KI_1;
        case KeyboardKeys::Alpha2: return Rml::Input::KeyIdentifier::KI_2;
        case KeyboardKeys::Alpha3: return Rml::Input::KeyIdentifier::KI_3;
        case KeyboardKeys::Alpha4: return Rml::Input::KeyIdentifier::KI_4;
        case KeyboardKeys::Alpha5: return Rml::Input::KeyIdentifier::KI_5;
        case KeyboardKeys::Alpha6: return Rml::Input::KeyIdentifier::KI_6;
        case KeyboardKeys::Alpha7: return Rml::Input::KeyIdentifier::KI_7;
        case KeyboardKeys::Alpha8: return Rml::Input::KeyIdentifier::KI_8;
        case KeyboardKeys::Alpha9: return Rml::Input::KeyIdentifier::KI_9;
        case KeyboardKeys::A: return Rml::Input::KeyIdentifier::KI_A;
        case KeyboardKeys::B: return Rml::Input::KeyIdentifier::KI_B;
        case KeyboardKeys::C: return Rml::Input::KeyIdentifier::KI_C;
        case KeyboardKeys::D: return Rml::Input::KeyIdentifier::KI_D;
        case KeyboardKeys::E: return Rml::Input::KeyIdentifier::KI_E;
        case KeyboardKeys::F: return Rml::Input::KeyIdentifier::KI_F;
        case KeyboardKeys::G: return Rml::Input::KeyIdentifier::KI_G;
        case KeyboardKeys::H: return Rml::Input::KeyIdentifier::KI_H;
        case KeyboardKeys::I: return Rml::Input::KeyIdentifier::KI_I;
        case KeyboardKeys::J: return Rml::Input::KeyIdentifier::KI_J;
        case KeyboardKeys::K: return Rml::Input::KeyIdentifier::KI_K;
        case KeyboardKeys::L: return Rml::Input::KeyIdentifier::KI_L;
        case KeyboardKeys::M: return Rml::Input::KeyIdentifier::KI_M;
        case KeyboardKeys::N: return Rml::Input::KeyIdentifier::KI_N;
        case KeyboardKeys::O: return Rml::Input::KeyIdentifier::KI_O;
        case KeyboardKeys::P: return Rml::Input::KeyIdentifier::KI_P;
        case KeyboardKeys::Q: return Rml::Input::KeyIdentifier::KI_Q;
        case KeyboardKeys::R: return Rml::Input::KeyIdentifier::KI_R;
        case KeyboardKeys::S: return Rml::Input::KeyIdentifier::KI_S;
        case KeyboardKeys::T: return Rml::Input::KeyIdentifier::KI_T;
        case KeyboardKeys::U: return Rml::Input::KeyIdentifier::KI_U;
        case KeyboardKeys::V: return Rml::Input::KeyIdentifier::KI_V;
        case KeyboardKeys::W: return Rml::Input::KeyIdentifier::KI_W;
        case KeyboardKeys::X: return Rml::Input::KeyIdentifier::KI_X;
        case KeyboardKeys::Y: return Rml::Input::KeyIdentifier::KI_Y;
        case KeyboardKeys::Z: return Rml::Input::KeyIdentifier::KI_Z;
        //case KeyboardKeys::OEM_1: return Rml::Input::KeyIdentifier::KI_OEM_1;
        //case KeyboardKeys::OEM_PLUS: return Rml::Input::KeyIdentifier::KI_OEM_PLUS;
        //case KeyboardKeys::OEM_COMMA: return Rml::Input::KeyIdentifier::KI_OEM_COMMA;
        //case KeyboardKeys::OEM_MINUS: return Rml::Input::KeyIdentifier::KI_OEM_MINUS;
        //case KeyboardKeys::OEM_PERIOD: return Rml::Input::KeyIdentifier::KI_OEM_PERIOD;
        //case KeyboardKeys::OEM_2: return Rml::Input::KeyIdentifier::KI_OEM_2;
        //case KeyboardKeys::OEM_3: return Rml::Input::KeyIdentifier::KI_OEM_3;
        //case KeyboardKeys::OEM_4: return Rml::Input::KeyIdentifier::KI_OEM_4;
        //case KeyboardKeys::OEM_5: return Rml::Input::KeyIdentifier::KI_OEM_5;
        //case KeyboardKeys::OEM_6: return Rml::Input::KeyIdentifier::KI_OEM_6;
        //case KeyboardKeys::OEM_7: return Rml::Input::KeyIdentifier::KI_OEM_7;
        case KeyboardKeys::Oem8: return Rml::Input::KeyIdentifier::KI_OEM_8;
        case KeyboardKeys::Oem102: return Rml::Input::KeyIdentifier::KI_OEM_102;
        case KeyboardKeys::Numpad0: return Rml::Input::KeyIdentifier::KI_NUMPAD0;
        case KeyboardKeys::Numpad1: return Rml::Input::KeyIdentifier::KI_NUMPAD1;
        case KeyboardKeys::Numpad2: return Rml::Input::KeyIdentifier::KI_NUMPAD2;
        case KeyboardKeys::Numpad3: return Rml::Input::KeyIdentifier::KI_NUMPAD3;
        case KeyboardKeys::Numpad4: return Rml::Input::KeyIdentifier::KI_NUMPAD4;
        case KeyboardKeys::Numpad5: return Rml::Input::KeyIdentifier::KI_NUMPAD5;
        case KeyboardKeys::Numpad6: return Rml::Input::KeyIdentifier::KI_NUMPAD6;
        case KeyboardKeys::Numpad7: return Rml::Input::KeyIdentifier::KI_NUMPAD7;
        case KeyboardKeys::Numpad8: return Rml::Input::KeyIdentifier::KI_NUMPAD8;
        case KeyboardKeys::Numpad9: return Rml::Input::KeyIdentifier::KI_NUMPAD9;
        //case KeyboardKeys::NumpadReturn: return Rml::Input::KeyIdentifier::KI_NUMPADENTER;
        case KeyboardKeys::NumpadMultiply: return Rml::Input::KeyIdentifier::KI_MULTIPLY;
        case KeyboardKeys::NumpadAdd: return Rml::Input::KeyIdentifier::KI_ADD;
        case KeyboardKeys::NumpadSeparator: return Rml::Input::KeyIdentifier::KI_SEPARATOR;
        case KeyboardKeys::NumpadSubtract: return Rml::Input::KeyIdentifier::KI_SUBTRACT;
        case KeyboardKeys::NumpadDecimal: return Rml::Input::KeyIdentifier::KI_DECIMAL;
        case KeyboardKeys::NumpadDivide: return Rml::Input::KeyIdentifier::KI_DIVIDE;
        //case KeyboardKeys::numpadeq: return Rml::Input::KeyIdentifier::KI_OEM_NEC_EQUAL;
        case KeyboardKeys::Backspace: return Rml::Input::KeyIdentifier::KI_BACK;
        case KeyboardKeys::Tab: return Rml::Input::KeyIdentifier::KI_TAB;
        case KeyboardKeys::Clear: return Rml::Input::KeyIdentifier::KI_CLEAR;
        case KeyboardKeys::Return: return Rml::Input::KeyIdentifier::KI_RETURN;
        case KeyboardKeys::Pause: return Rml::Input::KeyIdentifier::KI_PAUSE;
        case KeyboardKeys::Capital: return Rml::Input::KeyIdentifier::KI_CAPITAL;
        case KeyboardKeys::Kana: return Rml::Input::KeyIdentifier::KI_KANA;
        //case KeyboardKeys::Hangul: return Rml::Input::KeyIdentifier::KI_HANGUL;
        case KeyboardKeys::Junja: return Rml::Input::KeyIdentifier::KI_JUNJA;
        case KeyboardKeys::Final: return Rml::Input::KeyIdentifier::KI_FINAL;
        case KeyboardKeys::Hanja: return Rml::Input::KeyIdentifier::KI_HANJA;
        //case KeyboardKeys::Kanji: return Rml::Input::KeyIdentifier::KI_KANJI;
        case KeyboardKeys::Escape: return Rml::Input::KeyIdentifier::KI_ESCAPE;
        case KeyboardKeys::Convert: return Rml::Input::KeyIdentifier::KI_CONVERT;
        case KeyboardKeys::Nonconvert: return Rml::Input::KeyIdentifier::KI_NONCONVERT;
        case KeyboardKeys::Accept: return Rml::Input::KeyIdentifier::KI_ACCEPT;
        case KeyboardKeys::Modechange: return Rml::Input::KeyIdentifier::KI_MODECHANGE;
        case KeyboardKeys::PageUp: return Rml::Input::KeyIdentifier::KI_PRIOR;
        case KeyboardKeys::PageDown: return Rml::Input::KeyIdentifier::KI_NEXT;
        case KeyboardKeys::End: return Rml::Input::KeyIdentifier::KI_END;
        case KeyboardKeys::Home: return Rml::Input::KeyIdentifier::KI_HOME;
        case KeyboardKeys::ArrowLeft: return Rml::Input::KeyIdentifier::KI_LEFT;
        case KeyboardKeys::ArrowUp: return Rml::Input::KeyIdentifier::KI_UP;
        case KeyboardKeys::ArrowRight: return Rml::Input::KeyIdentifier::KI_RIGHT;
        case KeyboardKeys::ArrowDown: return Rml::Input::KeyIdentifier::KI_DOWN;
        case KeyboardKeys::Select: return Rml::Input::KeyIdentifier::KI_SELECT;
        case KeyboardKeys::Print: return Rml::Input::KeyIdentifier::KI_PRINT;
        case KeyboardKeys::Execute: return Rml::Input::KeyIdentifier::KI_EXECUTE;
        case KeyboardKeys::PrintScreen: return Rml::Input::KeyIdentifier::KI_SNAPSHOT;
        case KeyboardKeys::Insert: return Rml::Input::KeyIdentifier::KI_INSERT;
        case KeyboardKeys::Delete: return Rml::Input::KeyIdentifier::KI_DELETE;
        case KeyboardKeys::Help: return Rml::Input::KeyIdentifier::KI_HELP;
        case KeyboardKeys::LeftWindows: return Rml::Input::KeyIdentifier::KI_LWIN;
        case KeyboardKeys::RightWindows: return Rml::Input::KeyIdentifier::KI_RWIN;
        case KeyboardKeys::Applications: return Rml::Input::KeyIdentifier::KI_APPS;
            //case KeyboardKeys::POWER: return Rml::Input::KeyIdentifier::KI_POWER;
        case KeyboardKeys::Sleep: return Rml::Input::KeyIdentifier::KI_SLEEP;
            //case KeyboardKeys::WAKE: return Rml::Input::KeyIdentifier::KI_WAKE;
        case KeyboardKeys::F1: return Rml::Input::KeyIdentifier::KI_F1;
        case KeyboardKeys::F2: return Rml::Input::KeyIdentifier::KI_F2;
        case KeyboardKeys::F3: return Rml::Input::KeyIdentifier::KI_F3;
        case KeyboardKeys::F4: return Rml::Input::KeyIdentifier::KI_F4;
        case KeyboardKeys::F5: return Rml::Input::KeyIdentifier::KI_F5;
        case KeyboardKeys::F6: return Rml::Input::KeyIdentifier::KI_F6;
        case KeyboardKeys::F7: return Rml::Input::KeyIdentifier::KI_F7;
        case KeyboardKeys::F8: return Rml::Input::KeyIdentifier::KI_F8;
        case KeyboardKeys::F9: return Rml::Input::KeyIdentifier::KI_F9;
        case KeyboardKeys::F10: return Rml::Input::KeyIdentifier::KI_F10;
        case KeyboardKeys::F11: return Rml::Input::KeyIdentifier::KI_F11;
        case KeyboardKeys::F12: return Rml::Input::KeyIdentifier::KI_F12;
        case KeyboardKeys::F13: return Rml::Input::KeyIdentifier::KI_F13;
        case KeyboardKeys::F14: return Rml::Input::KeyIdentifier::KI_F14;
        case KeyboardKeys::F15: return Rml::Input::KeyIdentifier::KI_F15;
        case KeyboardKeys::F16: return Rml::Input::KeyIdentifier::KI_F16;
        case KeyboardKeys::F17: return Rml::Input::KeyIdentifier::KI_F17;
        case KeyboardKeys::F18: return Rml::Input::KeyIdentifier::KI_F18;
        case KeyboardKeys::F19: return Rml::Input::KeyIdentifier::KI_F19;
        case KeyboardKeys::F20: return Rml::Input::KeyIdentifier::KI_F20;
        case KeyboardKeys::F21: return Rml::Input::KeyIdentifier::KI_F21;
        case KeyboardKeys::F22: return Rml::Input::KeyIdentifier::KI_F22;
        case KeyboardKeys::F23: return Rml::Input::KeyIdentifier::KI_F23;
        case KeyboardKeys::F24: return Rml::Input::KeyIdentifier::KI_F24;
        case KeyboardKeys::Numlock: return Rml::Input::KeyIdentifier::KI_NUMLOCK;
        case KeyboardKeys::Scroll: return Rml::Input::KeyIdentifier::KI_SCROLL;
            //case KeyboardKeys::OEM_FJ_JISHO: return Rml::Input::KeyIdentifier::KI_OEM_FJ_JISHO;
            //case KeyboardKeys::OEM_FJ_MASSHOU: return Rml::Input::KeyIdentifier::KI_OEM_FJ_MASSHOU;
            //case KeyboardKeys::OEM_FJ_TOUROKU: return Rml::Input::KeyIdentifier::KI_OEM_FJ_TOUROKU;
            //case KeyboardKeys::OEM_FJ_LOYA: return Rml::Input::KeyIdentifier::KI_OEM_FJ_LOYA;
            //case KeyboardKeys::OEM_FJ_ROYA: return Rml::Input::KeyIdentifier::KI_OEM_FJ_ROYA;
        case KeyboardKeys::Shift: return Rml::Input::KeyIdentifier::KI_LSHIFT;
            //case KeyboardKeys::RSHIFT: return Rml::Input::KeyIdentifier::KI_RSHIFT;
        case KeyboardKeys::Control: return Rml::Input::KeyIdentifier::KI_LCONTROL;
            //case KeyboardKeys::RCONTROL: return Rml::Input::KeyIdentifier::KI_RCONTROL;
        case KeyboardKeys::LeftMenu: return Rml::Input::KeyIdentifier::KI_LMENU;
        case KeyboardKeys::RightMenu: return Rml::Input::KeyIdentifier::KI_RMENU;
        case KeyboardKeys::BrowserBack: return Rml::Input::KeyIdentifier::KI_BROWSER_BACK;
        case KeyboardKeys::BrowserForward: return Rml::Input::KeyIdentifier::KI_BROWSER_FORWARD;
        case KeyboardKeys::BrowserRefresh: return Rml::Input::KeyIdentifier::KI_BROWSER_REFRESH;
        case KeyboardKeys::BrowserStop: return Rml::Input::KeyIdentifier::KI_BROWSER_STOP;
        case KeyboardKeys::BrowserSearch: return Rml::Input::KeyIdentifier::KI_BROWSER_SEARCH;
        case KeyboardKeys::BrowserFavorites: return Rml::Input::KeyIdentifier::KI_BROWSER_FAVORITES;
        case KeyboardKeys::BrowserHome: return Rml::Input::KeyIdentifier::KI_BROWSER_HOME;
        case KeyboardKeys::VolumeMute: return Rml::Input::KeyIdentifier::KI_VOLUME_MUTE;
        case KeyboardKeys::VolumeDown: return Rml::Input::KeyIdentifier::KI_VOLUME_DOWN;
        case KeyboardKeys::VolumeUp: return Rml::Input::KeyIdentifier::KI_VOLUME_UP;
        case KeyboardKeys::MediaNextTrack: return Rml::Input::KeyIdentifier::KI_MEDIA_NEXT_TRACK;
        case KeyboardKeys::MediaPrevTrack: return Rml::Input::KeyIdentifier::KI_MEDIA_PREV_TRACK;
        case KeyboardKeys::MediaStop: return Rml::Input::KeyIdentifier::KI_MEDIA_STOP;
        case KeyboardKeys::MediaPlayPause: return Rml::Input::KeyIdentifier::KI_MEDIA_PLAY_PAUSE;
        case KeyboardKeys::LaunchMail: return Rml::Input::KeyIdentifier::KI_LAUNCH_MAIL;
        case KeyboardKeys::LaunchMediaSelect: return Rml::Input::KeyIdentifier::KI_LAUNCH_MEDIA_SELECT;
        case KeyboardKeys::LaunchApp1: return Rml::Input::KeyIdentifier::KI_LAUNCH_APP1;
        case KeyboardKeys::LaunchApp2: return Rml::Input::KeyIdentifier::KI_LAUNCH_APP2;
            //case KeyboardKeys::OEM_AX: return Rml::Input::KeyIdentifier::KI_OEM_AX;
            //case KeyboardKeys::ICO_HELP: return Rml::Input::KeyIdentifier::KI_ICO_HELP;
            //case KeyboardKeys::ICO_00: return Rml::Input::KeyIdentifier::KI_ICO_00;
        case KeyboardKeys::Processkey: return Rml::Input::KeyIdentifier::KI_PROCESSKEY;
            //case KeyboardKeys::ICO_CLEAR: return Rml::Input::KeyIdentifier::KI_ICO_CLEAR;
        case KeyboardKeys::Attn: return Rml::Input::KeyIdentifier::KI_ATTN;
        case KeyboardKeys::Crsel: return Rml::Input::KeyIdentifier::KI_CRSEL;
        case KeyboardKeys::Exsel: return Rml::Input::KeyIdentifier::KI_EXSEL;
        case KeyboardKeys::Ereof: return Rml::Input::KeyIdentifier::KI_EREOF;
        case KeyboardKeys::Play: return Rml::Input::KeyIdentifier::KI_PLAY;
        case KeyboardKeys::Zoom: return Rml::Input::KeyIdentifier::KI_ZOOM;
        case KeyboardKeys::Pa1: return Rml::Input::KeyIdentifier::KI_PA1;
        case KeyboardKeys::OemClear: return Rml::Input::KeyIdentifier::KI_OEM_CLEAR;
            //case KeyboardKeys::LMETA: return Rml::Input::KeyIdentifier::KI_LMETA;
            //case KeyboardKeys::RMETA: return Rml::Input::KeyIdentifier::KI_RMETA;
        default: return Rml::Input::KeyIdentifier::KI_UNKNOWN;
    }
}

int TranslateFlaxMouseButton(MouseButton button)
{
    if (button == MouseButton::Left)
        return 0;
    if (button == MouseButton::Right)
        return 1;
    if (button == MouseButton::Middle)
        return 2;
    return ((int)button) - 1;
}

Window* GetEditorGameWindow()
{
#if USE_EDITOR
    MObject* returnValue = nullptr;
    MClass* helperClass = Scripting::FindClass("RmlUi.RmlUiHelpers");
    if (helperClass)
    {
        MMethod* method = helperClass->GetMethod("GetEditorGameWindow");
        if (method)
            returnValue = method->Invoke(nullptr, nullptr, nullptr);
    }
    return returnValue != nullptr ? (Window*)MUtils::Unbox<void*>(returnValue) : nullptr;
#else
    return nullptr;
#endif
}

bool HasEditorGameViewportFocus()
{
#if USE_EDITOR
    MClass* helperClass = Scripting::FindClass("RmlUi.RmlUiHelpers");
    if (helperClass)
    {
        MMethod* method = helperClass->GetMethod("HasEditorGameViewportFocus");
        if (method)
            return MUtils::Unbox<bool>(method->Invoke(nullptr, nullptr, nullptr));
    }
#endif
    return false;
    
}

#ifndef __GAMEPAD_BASE_PLUGIN_FIGHTING_HPP__KHISTORY
#define __GAMEPAD_BASE_PLUGIN_FIGHTING_HPP__KHISTORY

#include "Gamepad.kplugin.hpp"

namespace khistory {

class GamepadFightingGame2468 : public Gamepad {
public:
    GamepadFightingGame2468() : Gamepad() {
        _mPluginNmae += " - Fighting Game - 2468";
    }

public:
    void keyNameTableRemap() override {
        Gamepad::keyNameTableRemap(); // default init

        _mkeyNameTable[PAL::GamepadKey::DPAD_UP]        = "8";
        _mkeyNameTable[PAL::GamepadKey::DPAD_DOWN]      = "2";
        _mkeyNameTable[PAL::GamepadKey::DPAD_LEFT]      = "4";
        _mkeyNameTable[PAL::GamepadKey::DPAD_RIGHT]     = "6";
    }
};

}

#endif
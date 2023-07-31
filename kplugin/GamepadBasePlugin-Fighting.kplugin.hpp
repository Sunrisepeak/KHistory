#ifndef __GAMEPAD_BASE_PLUGIN_FIGHTING_HPP__KHISTORY
#define __GAMEPAD_BASE_PLUGIN_FIGHTING_HPP__KHISTORY

#include "GamepadBasePlugin.kplugin.hpp"

namespace khistory {

class GamepadBasePluginFighting : public GamepadBasePlugin {
public:
    GamepadBasePluginFighting() : GamepadBasePlugin() {
        _mPluginNmae = "Gamepad Base - Fighting";
    }

public:
    void gameKeyNameTableInit() override {
        GamepadBasePlugin::gameKeyNameTableInit(); // default init

        _mkeyNameTable[PAL::GamepadKey::DPAD_UP]        = "8";
        _mkeyNameTable[PAL::GamepadKey::DPAD_DOWN]      = "2";
        _mkeyNameTable[PAL::GamepadKey::DPAD_LEFT]      = "4";
        _mkeyNameTable[PAL::GamepadKey::DPAD_RIGHT]     = "6";
    }
};

}

#endif
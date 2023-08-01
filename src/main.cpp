#include <dsvisual.hpp>

#include "KeyHistory.h"

/*
Issue: https://github.com/Sunrisepeak/KHistory/issues/6

// customize plugin
KPLUGIN_REGISTER(KeyboardBasePlugin)
KPLUGIN_REGISTER(GamepadBasePlugin)

// extend plugin
KPLUGIN_REGISTER(GamepadBasePluginFighting) // base on GamepadBasePlugin
*/

int main() {
    // config window
    dsvisual::PlatformManager::setRootWindowName("Key History @ Power by DSVisual");
    dsvisual::PlatformManager::setRootWindowSize(860, 1080);

    // customize plugin
    KPLUGIN_REGISTER(KeyboardBasePlugin)
    KPLUGIN_REGISTER(GamepadBasePlugin)

    // extend plugin
    KPLUGIN_REGISTER(GamepadBasePluginFighting) // base on GamepadBasePlugin

    {// Note: auto create/destory khistory
        khistory::KeyHistory khistory;

        // windows closed check
        while (!dsvisual::PlatformManager::windowClosed()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    return 0;
}
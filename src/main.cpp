#include <dsvisual.hpp>

#include "KeyHistory.h"

KPLUGIN_REGISTER(GamepadBasePlugin)
KPLUGIN_REGISTER(GamepadBasePluginFighting)

int main() {
    
    // config window
    dsvisual::PlatformManager::setRootWindowName("Key History @ Power by DSVisual");
    dsvisual::PlatformManager::setRootWindowSize(860, 1080);

    ImGui::GetIO().IniFilename = "";

    {// Note: auto create/destory khistory
        khistory::KeyHistory khistory;

        // windows closed check
        while (!dsvisual::PlatformManager::windowClosed()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    return 0;
}
#include <iostream>

#include "PAL.h"
#include "KeyHistory.h"

int main() {
    
    // config window
    dsvisual::PlatformManager::setRootWindowName("Key History @ Power by DSVisual");
    dsvisual::PlatformManager::setRootWindowSize(860, 960);

    {// Note: auto create/destory khistory
        khistory::KeyHistory khistory;

        // windows closed check
        while (!dsvisual::PlatformManager::windowClosed()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    return 0;
}
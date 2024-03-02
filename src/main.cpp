// Use of this source code is governed by GPL3-License
// that can be found in the License file.
//
// Copyright (C) 2023 - present
//
// Author: Sunrisepeak (speakshen@163.com)
// ProjectLinks: https://github.com/Sunrisepeak/KHistory
//
// Modify History:
//        2023/8/4   sunrisepeak    add license
//
//

#include <dsvisual-core.h>

#include "KeyHistory.h"
#include "KPlugin.h"

int main() {
    // config window
    dsvisual::PlatformManager::setRootWindowName("Key History @ Power by DSVisual");
    dsvisual::PlatformManager::setRootWindowSize(860, 1100);
    
    loadKPlugin(); //load plugin

    {// Note: auto create/destory khistory
        khistory::KeyHistory khistory;

        // windows closed check
        while (!dsvisual::PlatformManager::windowClosed()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    return 0;
}
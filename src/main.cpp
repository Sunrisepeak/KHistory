#include "KeyHistory.h"

int main() {
    dsvisual::PlatformManager::setRootWindowName("Key History @ Power by DSVisual");
    dsvisual::PlatformManager::setRootWindowSize(860, 960);
    khistory::KeyHistory kh;
    while (!dsvisual::PlatformManager::windowClosed()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}
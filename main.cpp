#include "KeyHistory.h"

int main() {
    khistory::KeyHistory kr;
    while (!dsvisual::PlatformManager::windowClosed()) {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
    return 0;
}
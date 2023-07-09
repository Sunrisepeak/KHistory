#include <iostream>
#include <thread>
#include <chrono>

#include <dstruct.hpp>

#include "pal.h"
#include "TargetWindowKeyDetect.h"

namespace khistory {

TargetWindowKeyDetect::TargetWindowKeyDetect() :
    __mExitDetect { false },
    __mKeyPressMapTable { false },
    __mTargetWindowInfo { 0, "" },
    __mCurrentWindowList { },
    __mPlatformAccessMutex { } {
    __mDetectThread = std::move(std::thread(&TargetWindowKeyDetect::__detectKeyInfo, this));
}

TargetWindowKeyDetect::~TargetWindowKeyDetect() {
    __mExitDetect = true;
    if (__mDetectThread.joinable())
        __mDetectThread.join();
}

TargetWindowKeyDetect & TargetWindowKeyDetect::getInstance() {
    static TargetWindowKeyDetect kd;
    return kd;
}

dstruct::Vector<PAL::WindowInfo>
TargetWindowKeyDetect::getWindowInfoList() {
    auto now = std::chrono::system_clock::now();
    auto currentTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    static decltype(currentTimeMs) oldTimeMs = 0;
    //printf("time: %ld - %ld = %ld\n", currentTimeMs, oldTimeMs, currentTimeMs - oldTimeMs);
    if (currentTimeMs - oldTimeMs > 3 * 1000) { // update
        // TODO: reduce update freq, avoid crash
        std::lock_guard<std::mutex> _al(__mPlatformAccessMutex);
        __mCurrentWindowList = PAL::platformWindowInfos();
        oldTimeMs = currentTimeMs;
    }
    return __mCurrentWindowList;
}

void TargetWindowKeyDetect::setTargetWindow(const PAL::WindowInfo &wInfo) {
    __mTargetWindowInfo = wInfo;
}

const PAL::WindowInfo & TargetWindowKeyDetect::getTargetWindow() const {
    return __mTargetWindowInfo;
}

void TargetWindowKeyDetect::setPressedKey(int index, bool pressed) {
    __mKeyPressMapTable[index] = pressed;
}

dstruct::Vector<int> TargetWindowKeyDetect::getPressedKeyList() const {
    dstruct::Vector<int> ans;
    for (int i = 0; i < 256; i++) {
        if (__mKeyPressMapTable[i])
            ans.push(i);
    }
    return ans;
}

void TargetWindowKeyDetect::__detectKeyInfo() {
    PAL::platformInit();
    while (!__mExitDetect) {
        if (__mTargetWindowInfo.id != 0) {
            // block detect ?
            PAL::KeyData keyData = PAL::platformKeyDetect(__mTargetWindowInfo.id);
            if (keyData.key > 0 && keyData.key < 256)
                __mKeyPressMapTable[keyData.key] = keyData.pressed;
            else {
                if (keyData.key == -1) {
                    __mTargetWindowInfo.id = 0;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }
    PAL::platformDeinit();
}

}
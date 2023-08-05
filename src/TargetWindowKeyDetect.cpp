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

#include <iostream>
#include <thread>
#include <chrono>

#include <dstruct.hpp>

#include "PAL.h"
#include "TargetWindowKeyDetect.h"

namespace khistory {

TargetWindowKeyDetect::TargetWindowKeyDetect() :
    __mExitDetect { false },
    __mKeyPressMapTable { false },
    __mDetectFPS { 60 },
    __mRealDetectFPS { 0 },
    __mTargetWindowInfo { 0, "" },
    __mCurrentWindowList { },
    __mPlatformAccessMutex { }
{
    __mDetectThread = std::move(std::thread(&TargetWindowKeyDetect::__detectKeyInfoThreadFunc, this));
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

float TargetWindowKeyDetect::getRealDetectFPS() const {
    return __mRealDetectFPS;
}

void TargetWindowKeyDetect::setDetectFPS(int fps) {
    __mDetectFPS = fps;
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

dstruct::Vector<int> TargetWindowKeyDetect::getPressedKeyVec() const {
    dstruct::Vector<int> ans;
    for (int i = 0; i < KEY_NUMBERS; i++) {
        if (__mKeyPressMapTable[i])
            ans.push(i);
    }
    return ans;
}

void TargetWindowKeyDetect::__detectKeyInfoThreadFunc() {
    // 初始化计时器
    khistory::PAL::platformInit();
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        int frameCount = 0;
        int frameBalanceOffset = 0;
        while (!__mExitDetect) {
            if (__mTargetWindowInfo.id != 0) {
                // block detect ?
                auto keyEventVec = PAL::platformKeyDetect(__mTargetWindowInfo.id);
                // handle key event and update __mKeyPressMapTable
                for (auto &keyEvent : keyEventVec) {
                    //std::cout << keyEvent.key << " " << keyEvent.pressed << std::endl;
                    if (keyEvent.key >= 0 && keyEvent.key < KEY_NUMBERS) {
                        __mKeyPressMapTable[keyEvent.key] = keyEvent.pressed;
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::microseconds((1000 * 1000) / (__mDetectFPS + frameBalanceOffset)));
            { // compute detect fps
                auto currentTime = std::chrono::high_resolution_clock::now();
                float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

                frameCount++;

                if (frameTime >= 1.0f) {
                    __mRealDetectFPS = frameCount / frameTime;
                    // dynamic balance
                    frameBalanceOffset += ((__mRealDetectFPS - __mDetectFPS < -5) + (__mRealDetectFPS - __mDetectFPS > 5) * -1) * 2;
                    //std::cout << frameBalanceOffset << std::endl;
                    // reset
                    startTime = currentTime;
                    frameCount = 0;
                }
            }
        }
    }
    khistory::PAL::platformDeinit();
}

}
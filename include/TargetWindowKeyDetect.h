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

#ifndef __KEY_DETECT_H__KHISTORY
#define __KEY_DETECT_H__KHISTORY

// std
#include <mutex>
#include <thread>

// dstruct
#include <dstruct.hpp>

#include "PAL.h"

namespace khistory {

class TargetWindowKeyDetect {
private:
    TargetWindowKeyDetect();
    TargetWindowKeyDetect(TargetWindowKeyDetect const&)            = delete;
    TargetWindowKeyDetect& operator=(TargetWindowKeyDetect const&) = delete;
    TargetWindowKeyDetect(TargetWindowKeyDetect&&)                 = delete;
    TargetWindowKeyDetect& operator=(TargetWindowKeyDetect&&)      = delete;
    ~TargetWindowKeyDetect();
public:
    static TargetWindowKeyDetect & getInstance();
    float getRealDetectFPS() const;
    void setDetectFPS(int fps);
    dstruct::Vector<PAL::WindowInfo> getWindowInfoList();
    void setTargetWindow(const PAL::WindowInfo &wInfo);
    const PAL::WindowInfo & getTargetWindow() const;
    void setPressedKey(int key, bool pressed = true);
    dstruct::Vector<int> getPressedKeyVec() const;
private:
    void __detectKeyInfoThreadFunc();
private:
    bool __mExitDetect;
    bool __mKeyPressMapTable[KEY_NUMBERS]; // gamepad and keyboard key-status
    int __mDetectFPS;
    float __mRealDetectFPS;
    PAL::WindowInfo __mTargetWindowInfo;
    dstruct::Vector<PAL::WindowInfo> __mCurrentWindowList;
    mutable std::mutex __mPlatformAccessMutex;
    std::thread __mDetectThread;
};

}

#endif
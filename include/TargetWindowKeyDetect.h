#ifndef __KEY_DETECT_H__
#define __KEY_DETECT_H__

#include <mutex>
#include <thread>
#include <dstruct.hpp>

#include "pal.h"

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
    dstruct::Vector<PAL::WindowInfo> getWindowInfoList();
    void setTargetWindow(const PAL::WindowInfo &wInfo);
    const PAL::WindowInfo & getTargetWindow() const;
    void setPressedKey(int key, bool pressed = true);
    dstruct::Vector<int> getPressedKeyList() const;
private:
    void __detectKeyInfo();
private:
    bool __mExitDetect;
    bool __mKeyPressMapTable[256];
    PAL::WindowInfo __mTargetWindowInfo;
    dstruct::Vector<PAL::WindowInfo> __mCurrentWindowList;
    mutable std::mutex __mPlatformAccessMutex;
    std::thread __mDetectThread;
};

}

#endif
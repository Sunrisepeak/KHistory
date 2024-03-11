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

#include "PAL.h"

dstruct::Vector<std::string> khistory::PAL::KeyMapTable(KEY_NUMBERS, "");
bool khistory::PAL::gamepadConnected = false;
unsigned int khistory::PAL::globalDetectWinID = 0;

namespace khistory {

std::string PAL::WindowInfo::toString() const {
    if (id == 0) return "";
    std::string title = name + " " + std::to_string(w) +
        " x " + std::to_string(h)  + " " + std::to_string(id);
    return title;
}

void PAL::__gamepadKeyDefaultMap() {
    KeyMapTable[GamepadKey::DPAD_UP]        = "^";
    KeyMapTable[GamepadKey::DPAD_DOWN]      = "v";
    KeyMapTable[GamepadKey::DPAD_LEFT]      = "<";
    KeyMapTable[GamepadKey::DPAD_RIGHT]     = ">";
    KeyMapTable[GamepadKey::START]          = "START";
    KeyMapTable[GamepadKey::BACK]           = "BACK";
    KeyMapTable[GamepadKey::A]              = "A";
    KeyMapTable[GamepadKey::B]              = "B";
    KeyMapTable[GamepadKey::X]              = "X";
    KeyMapTable[GamepadKey::Y]              = "Y";

    // L/R trigger/Bumper
    KeyMapTable[GamepadKey::LEFT_BUMPER]    = "LB";
    KeyMapTable[GamepadKey::RIGHT_BUMPER]   = "RB";
    KeyMapTable[GamepadKey::LEFT_TRIGGER]   = "LT";
    KeyMapTable[GamepadKey::RIGHT_TRIGGER]  = "RT";

    // thumb
    KeyMapTable[GamepadKey::LEFT_THUMB]     = "LEFT_THUMB";
    KeyMapTable[GamepadKey::RIGHT_THUMB]    = "RIGHT_THUMB";
}

}
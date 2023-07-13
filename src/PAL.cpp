#include "PAL.h"

dstruct::Vector<std::string> khistory::PAL::KeyMapTable;
bool khistory::PAL::gamepadConnected = false;

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
    KeyMapTable[GamepadKey::LEFT_SHOULDER]  = "LS";
    KeyMapTable[GamepadKey::RIGHT_SHOULDER] = "RS";
    KeyMapTable[GamepadKey::A]              = "A";
    KeyMapTable[GamepadKey::B]              = "B";
    KeyMapTable[GamepadKey::X]              = "X";
    KeyMapTable[GamepadKey::Y]              = "Y";

    // L/R trigger
    KeyMapTable[GamepadKey::LEFT_TRIGGER]   = "LT";
    KeyMapTable[GamepadKey::RIGHT_TRIGGER]  = "RT";

    // thumb
    KeyMapTable[GamepadKey::LEFT_THUMB]     = "LEFT_THUMB";
    KeyMapTable[GamepadKey::RIGHT_THUMB]    = "RIGHT_THUMB";
}

}
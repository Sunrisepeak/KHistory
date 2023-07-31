#include "PAL.h"

dstruct::Vector<std::string> khistory::PAL::KeyMapTable(KEY_NUMBERS, "");
bool khistory::PAL::gamepadConnected = false;

namespace khistory {

std::string PAL::WindowInfo::toString() const {
    if (id == 0) return "";
    std::string title = name + " " + std::to_string(w) +
        " x " + std::to_string(h)  + " " + std::to_string(id);
    return title;
}

void PAL::__gamepadKeyDefaultMap() {
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::DPAD_UP]        = "^";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::DPAD_DOWN]      = "v";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::DPAD_LEFT]      = "<";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::DPAD_RIGHT]     = ">";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::START]          = "START";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::BACK]           = "BACK";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::A]              = "A";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::B]              = "B";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::X]              = "X";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::Y]              = "Y";

    // L/R trigger/Bumper
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::LEFT_BUMPER]    = "LB";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::RIGHT_BUMPER]   = "RB";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::LEFT_TRIGGER]   = "LT";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::RIGHT_TRIGGER]  = "RT";

    // thumb
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::LEFT_THUMB]     = "LEFT_THUMB";
    KeyMapTable[KEYBOARD_KEY_NUMBERS + GamepadKey::RIGHT_THUMB]    = "RIGHT_THUMB";
}

}
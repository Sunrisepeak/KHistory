#ifndef __PAL_H__KHISTORY
#define __PAL_H__KHISTORY

#include <string>
#include <dstruct.hpp>

namespace khistory {

#define KEYBOARD_KEY_NUMBERS 256
#define GAMEPAD_KEY_NUMBERS  0x20
#define KEY_NUMBERS (KEYBOARD_KEY_NUMBERS + GAMEPAD_KEY_NUMBERS)

class PAL {
public: // type
    enum GamepadKey : int {
        BASE           = KEYBOARD_KEY_NUMBERS,
        DPAD_LEFT      = BASE + 0x0001,
        DPAD_DOWN      = BASE + 0x0004,
        DPAD_UP        = BASE + 0x0007,
        DPAD_RIGHT     = BASE + 0x0010,

        A              = BASE + 0x0002,
        B              = BASE + 0x0005,
        X              = BASE + 0x0008,
        Y              = BASE + 0x000A,

        LEFT_BUMPER    = BASE + 0x0003,
        RIGHT_BUMPER   = BASE + 0x0006,
        LEFT_TRIGGER   = BASE + 0x0009,
        RIGHT_TRIGGER  = BASE + 0x000B,

        START          = BASE + 0x0011,
        BACK           = BASE + 0x0012,

        // thumb
        LEFT_THUMB     = BASE + 0x0013,
        RIGHT_THUMB    = BASE + 0x0014,
    };

    struct KeyData {
        int key;
        bool pressed;
    };
    struct WindowInfo {
        unsigned long id;
        std::string name;
        int w, h;
        std::string toString() const;
    };

public: // top-down interface
    static void platformInit();
    static dstruct::Vector<WindowInfo> platformWindowInfos();
    static dstruct::Vector<KeyData> platformKeyDetect(unsigned int wID);
    static void platformDeinit();
private:
    static void __gamepadKeyDefaultMap();

public:
    static bool gamepadConnected;
    static dstruct::Vector<std::string> KeyMapTable;
};

}

#endif
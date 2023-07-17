#ifndef __PAL_H__KHISTORY
#define __PAL_H__KHISTORY

#include <string>
#include <dstruct.hpp>

namespace khistory {

#define KEY_NUMBERS (256 + 0x20)

class PAL {
public: // type
    enum GamepadKey : int {
        BASE_OFFSET    = 256, // keyboard key-numbers

        DPAD_LEFT      = BASE_OFFSET + 0x0001,
        DPAD_DOWN      = BASE_OFFSET + 0x0004,
        DPAD_UP        = BASE_OFFSET + 0x0007,
        DPAD_RIGHT     = BASE_OFFSET + 0x0010,

        A              = BASE_OFFSET + 0x0002,
        B              = BASE_OFFSET + 0x0005,
        X              = BASE_OFFSET + 0x0008,
        Y              = BASE_OFFSET + 0x000A,

        LEFT_BUMPER    = BASE_OFFSET + 0x0003,
        RIGHT_BUMPER   = BASE_OFFSET + 0x0006,
        LEFT_TRIGGER   = BASE_OFFSET + 0x0009,
        RIGHT_TRIGGER  = BASE_OFFSET + 0x000B,

        START          = BASE_OFFSET + 0x0011,
        BACK           = BASE_OFFSET + 0x0012,

        // thumb
        LEFT_THUMB     = BASE_OFFSET + 0x0013,
        RIGHT_THUMB    = BASE_OFFSET + 0x0014,
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
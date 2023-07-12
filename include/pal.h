#ifndef __PAL_H__KHISTORY
#define __PAL_H__KHISTORY

#include <string>
#include <dstruct.hpp>

namespace khistory {

class PAL {
public: // type
    struct KeyData {
        int key;
        bool pressed;
    };
    struct WindowInfo {
        unsigned long id;
        std::string name;
        int w, h;
        std::string toString() const {
            if (id == 0) return "";
            std::string title = name + " " + std::to_string(w) +
                " x " + std::to_string(h)  + " " + std::to_string(id);
            return title;
        }
    };

public: // interface
    static void platformInit();
    static dstruct::Vector<WindowInfo> platformWindowInfos();
    static dstruct::Vector<KeyData> platformKeyDetect(unsigned int wID);
    static void platformDeinit();

public:
    static unsigned long gamepadConnected;
    static dstruct::Vector<std::string> KeyMapTable;
};

}

#endif
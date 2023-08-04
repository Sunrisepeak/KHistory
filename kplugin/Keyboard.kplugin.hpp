#ifndef __KEYBOARD_BASE_PLUGIN_HPP__KHISTORY
#define __KEYBOARD_BASE_PLUGIN_HPP__KHISTORY

#include "PluginBase.hpp"

namespace khistory {

class Keyboard : public PluginBase {

public:
    Keyboard() {
        _mPluginName += " - Keyboard";
    }

public: // interface impl

    /*
        +-----------------------+
        |  Q W E R T Y U I O P  |
        |   A S D F G H J K L   |
        |    Z X C V B N M      |
        |                       |
        +-----------------------+
    */
    void keyLayoutImpl(float layoutWidth, float layoutHeight) override {
        const float spacing = 2.0f;
        float buttonWidth = layoutWidth / 12;
        { // Q W E R T Y U I O P
            _drawKey(KeyCode::KEYBOARD_Q, (buttonWidth + spacing) * 1 - spacing); _SameLine();
            _drawKey(KeyCode::KEYBOARD_W, (buttonWidth + spacing) * 2 - spacing); _SameLine();
            _drawKey(KeyCode::KEYBOARD_E, (buttonWidth + spacing) * 3 - spacing); _SameLine();
            _drawKey(KeyCode::KEYBOARD_R, (buttonWidth + spacing) * 4 - spacing); _SameLine();
            _drawKey(KeyCode::KEYBOARD_T, (buttonWidth + spacing) * 5 - spacing); _SameLine();
            _drawKey(KeyCode::KEYBOARD_Y, (buttonWidth + spacing) * 6 - spacing); _SameLine();
            _drawKey(KeyCode::KEYBOARD_U, (buttonWidth + spacing) * 7 - spacing); _SameLine();
            _drawKey(KeyCode::KEYBOARD_I, (buttonWidth + spacing) * 8 - spacing); _SameLine();
            _drawKey(KeyCode::KEYBOARD_O, (buttonWidth + spacing) * 9 - spacing); _SameLine();
            _drawKey(KeyCode::KEYBOARD_P, (buttonWidth + spacing) * 10 - spacing);
        }
        { // A S D F G H J K L
            _drawKey(KeyCode::KEYBOARD_A, (buttonWidth + spacing) * 1 - spacing + buttonWidth / 3); _SameLine();
            _drawKey(KeyCode::KEYBOARD_S, (buttonWidth + spacing) * 2 - spacing + buttonWidth / 3); _SameLine();
            _drawKey(KeyCode::KEYBOARD_D, (buttonWidth + spacing) * 3 - spacing + buttonWidth / 3); _SameLine();
            _drawKey(KeyCode::KEYBOARD_F, (buttonWidth + spacing) * 4 - spacing + buttonWidth / 3); _SameLine();
            _drawKey(KeyCode::KEYBOARD_G, (buttonWidth + spacing) * 5 - spacing + buttonWidth / 3); _SameLine();
            _drawKey(KeyCode::KEYBOARD_H, (buttonWidth + spacing) * 6 - spacing + buttonWidth / 3); _SameLine();
            _drawKey(KeyCode::KEYBOARD_J, (buttonWidth + spacing) * 7 - spacing + buttonWidth / 3); _SameLine();
            _drawKey(KeyCode::KEYBOARD_K, (buttonWidth + spacing) * 8 - spacing + buttonWidth / 3); _SameLine();
            _drawKey(KeyCode::KEYBOARD_L, (buttonWidth + spacing) * 9 - spacing + buttonWidth / 3);
        }
        { // Z X C V B N M
            _drawKey(KeyCode::KEYBOARD_Z, (buttonWidth + spacing) * 1 - spacing + buttonWidth); _SameLine();
            _drawKey(KeyCode::KEYBOARD_X, (buttonWidth + spacing) * 2 - spacing + buttonWidth); _SameLine();
            _drawKey(KeyCode::KEYBOARD_C, (buttonWidth + spacing) * 3 - spacing + buttonWidth); _SameLine();
            _drawKey(KeyCode::KEYBOARD_V, (buttonWidth + spacing) * 4 - spacing + buttonWidth); _SameLine();
            _drawKey(KeyCode::KEYBOARD_B, (buttonWidth + spacing) * 5 - spacing + buttonWidth); _SameLine();
            _drawKey(KeyCode::KEYBOARD_N, (buttonWidth + spacing) * 6 - spacing + buttonWidth); _SameLine();
            _drawKey(KeyCode::KEYBOARD_M, (buttonWidth + spacing) * 7 - spacing + buttonWidth);
        }
        {
            _drawKey(KeyCode::KEYBOARD_SPACE, buttonWidth * 2.5, -1, buttonWidth * 6);
        }
    }
};

}

#endif
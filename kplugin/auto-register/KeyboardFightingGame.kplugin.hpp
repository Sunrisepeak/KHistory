// Use of this source code is governed by GPL3-License
// that can be found in the License file.
//
// Copyright (C) 2023 - present
//
// Author: Sunrisepeak/SPeak/言峰 (speakshen@163.com)
// ProjectLinks: https://github.com/Sunrisepeak/KHistory
//
// Modify History:
//        2023/8/4   sunrisepeak    add license
//
//

#ifndef __KEYBOARD_FIGHTING_GAME_HPP__KHISTORY
#define __KEYBOARD_FIGHTING_GAME_HPP__KHISTORY

#include "PluginBase.hpp"

namespace khistory {

class KeyboardFightingGame : public PluginBase {

public:
    KeyboardFightingGame() {
        _mPluginName += " - Keyboard Fighting Game";
    }

public: // interface impl

    virtual void keyNameTableRemap() override {
        PluginBase::keyNameTableRemap();
        _mkeyNameTable[KeyCode::KEYBOARD_SPACE] = "Keyboard - Fighting Game";
    }

    virtual void keyColorTableRemap() override {
        // gamepad key-color init
        _mkeyColorTable[KeyCode::KEYBOARD_W] = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
        _mkeyColorTable[KeyCode::KEYBOARD_A] = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
        _mkeyColorTable[KeyCode::KEYBOARD_S] = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
        _mkeyColorTable[KeyCode::KEYBOARD_D] = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);

        _mkeyColorTable[KeyCode::KEYBOARD_Y] = ImVec4(0.0f, 0.0f, 0.5f, 0.5f);
        _mkeyColorTable[KeyCode::KEYBOARD_U] = ImVec4(0.5f, 0.0f, 0.5f, 0.5f);
        _mkeyColorTable[KeyCode::KEYBOARD_I] = ImVec4(0.8f, 0.5f, 0.5f, 0.5f);
        _mkeyColorTable[KeyCode::KEYBOARD_O] = ImVec4(0.5f, 0.5f, 0.8f, 0.5f);

        _mkeyColorTable[KeyCode::KEYBOARD_H] = ImVec4(178 / 255.0f, 1.0f, 102 / 255.0f, 0.5f);
        _mkeyColorTable[KeyCode::KEYBOARD_J] = ImVec4(255 / 255.0f, 102 / 255.0f, 102 / 255.0f, 0.5f);
        _mkeyColorTable[KeyCode::KEYBOARD_K] = ImVec4(0.0f, 1.0f, 1.0f, 0.5f);
        _mkeyColorTable[KeyCode::KEYBOARD_L] = ImVec4(1.0f, 1.0f, 0.0f, 0.5f);

        _mkeyColorTable[KeyCode::KEYBOARD_SPACE] = ImVec4(0.6f, 0.7f, 0.8f, 0.5f);
    }

    /*
        +-----------------------------+
        |    W    |        | Y U I O  |
        |  A S D  |        | H J K L  |
        |                             |
        +-----------------------------+
    */
    void keyLayoutImpl(float, float) override {
        const float spacing = 2.0f;
        { // W | Y U I O
            _drawKey('W', _mButtonWidth * 2); _SameLine();
            _drawKey('Y', _mButtonWidth * (5 + 1) + spacing * 2); _SameLine();
            _drawKey('U', _mButtonWidth * (5 + 2) + spacing * 3); _SameLine();
            _drawKey('I', _mButtonWidth * (5 + 3) + spacing * 4); _SameLine();
            _drawKey('O', _mButtonWidth * (5 + 4) + spacing * 5);
        }
        { // A S D | H J K L
            _drawKey('A', _mButtonWidth * 1 - spacing); _SameLine();
            _drawKey('S', _mButtonWidth * 2); _SameLine();
            _drawKey('D', _mButtonWidth * 3 + spacing * 1); _SameLine();
            _drawKey('H', _mButtonWidth * (5 + 1) + spacing * 2); _SameLine();
            _drawKey('J', _mButtonWidth * (5 + 2) + spacing * 3); _SameLine();
            _drawKey('K', _mButtonWidth * (5 + 3) + spacing * 4); _SameLine();
            _drawKey('L', _mButtonWidth * (5 + 4) + spacing * 5);
        }
        {
            _drawKey(' ', _mButtonWidth * 3, -1, _mButtonWidth * 5);
        }
    }
};

}

#endif
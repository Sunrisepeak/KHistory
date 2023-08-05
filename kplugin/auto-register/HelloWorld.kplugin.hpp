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

#ifndef __HELLO_WORLD_HPP__KHISTORY
#define __HELLO_WORLD_HPP__KHISTORY

#include "PluginBase.hpp"

namespace khistory {

class HelloWorld : public PluginBase {

public:
    HelloWorld() {
        _mPluginName += " - HelloWorld";
    }

public: // interface impl

    virtual void keyNameTableRemap() override {
        PluginBase::keyNameTableRemap(); // use default map
        // remap keyboard space
        _mkeyNameTable[KeyCode::KEYBOARD_SPACE] = "Hello World!";
    }

    virtual void keyColorTableRemap() override {
        PluginBase::keyColorTableRemap(); // use default map
        // reset keyboard space highlight color       R     G     B     T
        _mkeyColorTable[KeyCode::KEYBOARD_SPACE] = { 1.0f, 0.0f, 0.0f, 0.5f };
    }

    /*
            +---------------> layoutWidth
            |
            |  Hello World!
            |
            V
        layoutHeight
    */
    void keyLayoutImpl(float layoutWidth, float layoutHeight) override {

        float buttonWidth = layoutWidth / 2;
        float buttonHeight = buttonWidth / 6;
        float startPosX = layoutWidth / 4;
        float startPosY = 0;

        // _drawKey(int keycode, float cursorPosX = -1, float cursorPosY = -1, float width = 0, float height = 0, float fontScale = 0)
        _drawKey(
            KeyCode::KEYBOARD_SPACE,    // keycode
            startPosX, startPosY,       // cursorPosX, cursorPosY
            buttonWidth, buttonHeight,   // key/button width, height
            0.8                         // font scale
        );
    }
};

}

#endif
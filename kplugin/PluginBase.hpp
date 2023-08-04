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

#ifndef __PLUGIN_BASE_HPP__KHISTORY
#define __PLUGIN_BASE_HPP__KHISTORY

#include "KPluginInterface.h"
#include "PAL.h"

namespace khistory {

class PluginBase : public KPluginInterface {
public:
    using KeyColor = ImVec4;

    enum KeyCode : int {
        KEYBOARD_A = 'A',
        KEYBOARD_B = 'B',
        KEYBOARD_C = 'C',
        KEYBOARD_D = 'D',
        KEYBOARD_E = 'E',
        KEYBOARD_F = 'F',
        KEYBOARD_G = 'G',
        KEYBOARD_H = 'H',
        KEYBOARD_I = 'I',
        KEYBOARD_J = 'J',
        KEYBOARD_K = 'K',
        KEYBOARD_L = 'L',
        KEYBOARD_M = 'M',
        KEYBOARD_N = 'N',
        KEYBOARD_O = 'O',
        KEYBOARD_P = 'P',
        KEYBOARD_Q = 'Q',
        KEYBOARD_R = 'R',
        KEYBOARD_S = 'S',
        KEYBOARD_T = 'T',
        KEYBOARD_U = 'U',
        KEYBOARD_V = 'V',
        KEYBOARD_W = 'W',
        KEYBOARD_X = 'X',
        KEYBOARD_Y = 'Y',
        KEYBOARD_Z = 'Z',

        KEYBOARD_SPACE = ' ',

        GAMEPAD_DPAD_LEFT      = PAL::GamepadKey::DPAD_LEFT,
        GAMEPAD_DPAD_DOWN      = PAL::GamepadKey::DPAD_DOWN,
        GAMEPAD_DPAD_UP        = PAL::GamepadKey::DPAD_UP,
        GAMEPAD_DPAD_RIGHT     = PAL::GamepadKey::DPAD_RIGHT,

        GAMEPAD_A              = PAL::GamepadKey::A,
        GAMEPAD_B              = PAL::GamepadKey::B,
        GAMEPAD_X              = PAL::GamepadKey::X,
        GAMEPAD_Y              = PAL::GamepadKey::Y,

        GAMEPAD_LEFT_BUMPER    = PAL::GamepadKey::LEFT_BUMPER,
        GAMEPAD_RIGHT_BUMPER   = PAL::GamepadKey::RIGHT_BUMPER,
        GAMEPAD_LEFT_TRIGGER   = PAL::GamepadKey::LEFT_TRIGGER,
        GAMEPAD_RIGHT_TRIGGER  = PAL::GamepadKey::RIGHT_TRIGGER,

        GAMEPAD_START          = PAL::GamepadKey::START,
        GAMEPAD_BACK           = PAL::GamepadKey::BACK,

        // thumb
        GAMEPAD_LEFT_THUMB     = PAL::GamepadKey::LEFT_THUMB,
        GAMEPAD_RIGHT_THUMB    = PAL::GamepadKey::RIGHT_THUMB,
    };

public:
    PluginBase() {
        KPluginInterface::_mPluginName = "Plugin Base";
    }

public: // interface impl

    void init() final override {
        __mCursorPosYBase = _mButtonWidth = _mButtonHeight = 0;
        for (auto &kStatus : __mkeyStatusTable) kStatus = false;
        keyNameTableRemap();
        keyColorTableRemap();
    }

    void keyLayoutVisualImpl() final override {
        ImGuiStyle& style = ImGui::GetStyle();
        auto oldSpacing = style.ItemSpacing;

        style.ItemSpacing = ImVec2(2.0f, 2.0f);

        _mButtonWidth = _mButtonHeight = ImGui::GetWindowWidth() / (3 * 4);
        __mCursorPosYBase = ImGui::GetCursorPos().y;

        keyLayoutImpl(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() / 3); // impl in subclass

        style.ItemSpacing = oldSpacing;
    }

    void updateKeyStatus(const dstruct::Vector<int> &keyVec) override {
        for (auto &kStatus : __mkeyStatusTable) kStatus = false;
        for (auto keycode : keyVec) {
            if (PAL::gamepadConnected) {
                __mkeyStatusTable[keycode] = true;
            } else {
                // keyboard
                if (PAL::KeyMapTable[keycode].size() == 1) { // only detect alpha
                    __mkeyStatusTable[PAL::KeyMapTable[keycode][0]] = true;
                } else if (PAL::KeyMapTable[keycode] == "Space" || PAL::KeyMapTable[keycode] == "SPACE") {
                    __mkeyStatusTable[' '] = true;
                }
            }
        }
    }

public: // interface
    virtual void keyLayoutImpl(float layoutWidth, float layoutHeight) = 0;
public: // optional interface
    virtual void keyNameTableRemap() {
        // keyboard key-name default map
        for (int i = KeyCode::KEYBOARD_A; i <= KeyCode::KEYBOARD_Z; i++) {
            _mkeyNameTable[i] = i;
        }
        _mkeyNameTable[KeyCode::KEYBOARD_SPACE] = "KHistory";

        // gamepad key-name default map
        _mkeyNameTable[KeyCode::GAMEPAD_DPAD_UP]        = "^";
        _mkeyNameTable[KeyCode::GAMEPAD_DPAD_DOWN]      = "v";
        _mkeyNameTable[KeyCode::GAMEPAD_DPAD_LEFT]      = "<";
        _mkeyNameTable[KeyCode::GAMEPAD_DPAD_RIGHT]     = ">";
        _mkeyNameTable[KeyCode::GAMEPAD_START]          = "START";
        _mkeyNameTable[KeyCode::GAMEPAD_BACK]           = "BACK";
        _mkeyNameTable[KeyCode::GAMEPAD_A]              = "A";
        _mkeyNameTable[KeyCode::GAMEPAD_B]              = "B";
        _mkeyNameTable[KeyCode::GAMEPAD_X]              = "X";
        _mkeyNameTable[KeyCode::GAMEPAD_Y]              = "Y";
        _mkeyNameTable[KeyCode::GAMEPAD_LEFT_BUMPER]    = "LB";
        _mkeyNameTable[KeyCode::GAMEPAD_RIGHT_BUMPER]   = "RB";
        _mkeyNameTable[KeyCode::GAMEPAD_LEFT_TRIGGER]   = "LT";
        _mkeyNameTable[KeyCode::GAMEPAD_RIGHT_TRIGGER]  = "RT";
    }

    virtual void keyColorTableRemap() {
        for (auto &kColor : _mkeyColorTable) kColor = ImVec4(1, 1, 1, 0.25);
    }

protected:
    float _mButtonWidth, _mButtonHeight;
    dstruct::Array<ImVec4, KEY_NUMBERS> _mkeyColorTable;
    dstruct::Array<std::string, KEY_NUMBERS> _mkeyNameTable;

    void _drawKey(int keycode, float cursorPosX = -1, float cursorPosY = -1, float width = 0, float height = 0, float fontScale = 0) {

        if (cursorPosX >= 0) ImGui::SetCursorPosX(cursorPosX);
        if (cursorPosY >= 0) ImGui::SetCursorPosY(__mCursorPosYBase + cursorPosY);
        
        if (width <= 0) width = _mButtonWidth;
        if (height <= 0) height = _mButtonHeight;

        ImGui::PushStyleColor(ImGuiCol_Button, __mkeyStatusTable[keycode] ? _mkeyColorTable[keycode] : ImVec4(0, 0, 0, 0.25));
        {
            float oldFontSize = ImGui::GetFont()->Scale;
            ImVec2 textSize =  ImGui::CalcTextSize(_mkeyNameTable[keycode].c_str());
            if (fontScale <= 0 && (textSize.x > width || textSize.y > height)) { // scale font
                float xFontScale = (width / textSize.x - 0.05);
                float yFontScale = (height / textSize.y - 0.05);
                fontScale = xFontScale > yFontScale ? yFontScale : xFontScale;
            } else {
                fontScale = 1;
            }
            ImGui::GetFont()->Scale = oldFontSize * fontScale;
            ImGui::PushFont(ImGui::GetFont());

            ImGui::Button( _mkeyNameTable[keycode].c_str(), { width, height });

            ImGui::GetFont()->Scale = oldFontSize;
            ImGui::PopFont();
        }
        ImGui::PopStyleColor(1);
    }

    void _SameLine() { ImGui::SameLine(); }

private:
    float __mCursorPosYBase;
    dstruct::Array<bool, KEY_NUMBERS> __mkeyStatusTable;
};

}

#endif
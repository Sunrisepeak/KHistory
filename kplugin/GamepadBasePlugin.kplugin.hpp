#ifndef __GAMEPAD_BASE_PLUGIN_HPP__KHISTORY
#define __GAMEPAD_BASE_PLUGIN_HPP__KHISTORY

#include "KPlugin.h"
#include "PAL.h"

namespace khistory {

class GamepadBasePlugin : public KPluginInterface {

public:
    GamepadBasePlugin() {
        KPluginInterface::_mPluginNmae = "Gamepad Base";
        for (auto &kStatus : __mkeyStatusTable) kStatus = false;
    }

public: // interface impl
    virtual void gameKeyNameTableInit() override {
        _mkeyNameTable[PAL::GamepadKey::DPAD_UP]        = "^";
        _mkeyNameTable[PAL::GamepadKey::DPAD_DOWN]      = "v";
        _mkeyNameTable[PAL::GamepadKey::DPAD_LEFT]      = "<";
        _mkeyNameTable[PAL::GamepadKey::DPAD_RIGHT]     = ">";
        _mkeyNameTable[PAL::GamepadKey::START]          = "START";
        _mkeyNameTable[PAL::GamepadKey::BACK]           = "BACK";
        _mkeyNameTable[PAL::GamepadKey::A]              = "A";
        _mkeyNameTable[PAL::GamepadKey::B]              = "B";
        _mkeyNameTable[PAL::GamepadKey::X]              = "X";
        _mkeyNameTable[PAL::GamepadKey::Y]              = "Y";

        // L/R trigger/Bumper
        _mkeyNameTable[PAL::GamepadKey::LEFT_BUMPER]    = "LB";
        _mkeyNameTable[PAL::GamepadKey::RIGHT_BUMPER]   = "RB";
        _mkeyNameTable[PAL::GamepadKey::LEFT_TRIGGER]   = "LT";
        _mkeyNameTable[PAL::GamepadKey::RIGHT_TRIGGER]  = "RT";
    }

    virtual void gameKeyColorTableInit() override {
        // gamepad key-color init
        _mGameKeyColorTable[PAL::GamepadKey::DPAD_UP]        = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
        _mGameKeyColorTable[PAL::GamepadKey::DPAD_DOWN]      = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
        _mGameKeyColorTable[PAL::GamepadKey::DPAD_LEFT]      = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
        _mGameKeyColorTable[PAL::GamepadKey::DPAD_RIGHT]     = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);

        _mGameKeyColorTable[PAL::GamepadKey::START]          = ImVec4(0.6f, 0.7f, 0.8f, 0.5f);
        _mGameKeyColorTable[PAL::GamepadKey::BACK]           = ImVec4(0.8f, 0.7f, 0.6f, 0.5f);

        _mGameKeyColorTable[PAL::GamepadKey::A]              = ImVec4(178 / 255.0f, 1.0f, 102 / 255.0f, 0.5f);
        _mGameKeyColorTable[PAL::GamepadKey::B]              = ImVec4(255 / 255.0f, 102 / 255.0f, 102 / 255.0f, 0.5f);
        _mGameKeyColorTable[PAL::GamepadKey::X]              = ImVec4(0.0f, 1.0f, 1.0f, 0.5f);
        _mGameKeyColorTable[PAL::GamepadKey::Y]              = ImVec4(1.0f, 1.0f, 0.0f, 0.5f);

        _mGameKeyColorTable[PAL::GamepadKey::LEFT_BUMPER]    = ImVec4(128 / 255.0f, 0.0f, 128 / 255.0f, 0.5f);
        _mGameKeyColorTable[PAL::GamepadKey::RIGHT_BUMPER]   = ImVec4(128 / 255.0f, 0.0f, 128 / 255.0f, 0.5f);
        _mGameKeyColorTable[PAL::GamepadKey::LEFT_TRIGGER]   = ImVec4(0.3f, 0.3f, 0.3f, 0.8f);
        _mGameKeyColorTable[PAL::GamepadKey::RIGHT_TRIGGER]  = ImVec4(0.3f, 0.3f, 0.3f, 0.8f);
    }

    /*
           [ LT ]              [ RT ]
           [ LB ]              [ RB ]
        +-----------------------------+
        |    ^    |          |    Y    |
        |  <   >  |back start|  X   B  |
        |    v    |          |    A    |
        +-----------------------------+
    */
    void gameKeyLayoutVisualImpl() override {
        ImGuiStyle& style = ImGui::GetStyle();
        const float spacing = 2.0f;
        auto oldSpacing = style.ItemSpacing;

        style.ItemSpacing = ImVec2(spacing, spacing);

        float areaHeight = ImGui::GetWindowHeight() / 3;
        float areaWidth = ImGui::GetWindowWidth() / 3;

        __mButtonWidth = __mButtonHeight = areaWidth / 4;

        {
            float oldFontSize = ImGui::GetFont()->Scale;
            if (__mButtonHeight < 50) ImGui::GetFont()->Scale /= 1.5;
            ImGui::PushFont(ImGui::GetFont());
            { // LT/RT
                __drawKeyButton(PAL::GamepadKey::LEFT_TRIGGER, __mButtonWidth, 2 * __mButtonWidth, __mButtonHeight / 2); ImGui::SameLine();
                __drawKeyButton(PAL::GamepadKey::RIGHT_TRIGGER, 2 * areaWidth + __mButtonWidth, 2 * __mButtonWidth, __mButtonHeight / 2);
            }
            { // LB/RB
                __drawKeyButton(PAL::GamepadKey::LEFT_BUMPER,__mButtonWidth, 2 * __mButtonWidth, __mButtonHeight / 2); ImGui::SameLine();
                __drawKeyButton(PAL::GamepadKey::RIGHT_BUMPER, 2 * areaWidth + __mButtonHeight, 2 * __mButtonWidth, __mButtonHeight / 2);
            }
            ImGui::GetFont()->Scale = oldFontSize;
            ImGui::PopFont();
        }

        {
            int firstLineAreaStart = areaWidth / 2 - __mButtonWidth / 2;
            __drawKeyButton(PAL::GamepadKey::DPAD_UP, firstLineAreaStart); ImGui::SameLine();
            __drawKeyButton(PAL::GamepadKey::Y, 2 * areaWidth + firstLineAreaStart);
        }
        {
            int secondLineAreaStart = __mButtonWidth / 2;
            {
                __drawKeyButton(PAL::GamepadKey::DPAD_LEFT, secondLineAreaStart); ImGui::SameLine();
                __drawKeyButton(PAL::GamepadKey::DPAD_RIGHT, secondLineAreaStart + __mButtonWidth * 2); ImGui::SameLine();
            }
            { // back / start
                float oldFontSize = ImGui::GetFont()->Scale;
                ImGui::GetFont()->Scale /= 1.5;
                if (__mButtonHeight < 50) ImGui::GetFont()->Scale /= 1.6;
                ImGui::PushFont(ImGui::GetFont());
                __drawKeyButton(PAL::GamepadKey::BACK, areaWidth + secondLineAreaStart, __mButtonWidth, __mButtonHeight / 2); ImGui::SameLine();
                __drawKeyButton(PAL::GamepadKey::START, areaWidth + secondLineAreaStart + __mButtonWidth * 2, __mButtonWidth, __mButtonHeight / 2); ImGui::SameLine();
                ImGui::GetFont()->Scale = oldFontSize;
                ImGui::PopFont();
            }
            {
                __drawKeyButton(PAL::GamepadKey::X, 2 * areaWidth + secondLineAreaStart); ImGui::SameLine();
                __drawKeyButton(PAL::GamepadKey::B, 2 * areaWidth + secondLineAreaStart + __mButtonWidth * 2);
            }
        }
        {
            int thirdLineAreaStart = areaWidth / 2 - __mButtonWidth / 2;
            __drawKeyButton(PAL::GamepadKey::DPAD_DOWN, thirdLineAreaStart); ImGui::SameLine();
            __drawKeyButton(PAL::GamepadKey::A, 2 * areaWidth + thirdLineAreaStart);
        }

        style.ItemSpacing = oldSpacing;
    }

    void updateKeyStatus(const dstruct::Vector<int> &keyVec) override {
        for (auto &kStatus : __mkeyStatusTable) kStatus = false;
        for (auto keycode : keyVec) {
            int gamepadKeycode = keycode - KEYBOARD_KEY_NUMBERS;
            if (gamepadKeycode < __mkeyStatusTable.size() && gamepadKeycode >= 0) {
                __mkeyStatusTable[gamepadKeycode] = true;
            }
        }
    }

protected:
    dstruct::Array<ImVec4, GAMEPAD_KEY_NUMBERS> _mGameKeyColorTable;
    dstruct::Array<std::string, GAMEPAD_KEY_NUMBERS> _mkeyNameTable;

private:
    float __mButtonWidth, __mButtonHeight;
    dstruct::Array<bool, GAMEPAD_KEY_NUMBERS> __mkeyStatusTable;
    
    void __drawKeyButton(int keycode, float cursorPosX = 0, float width = 0, float height = 0) {
        ImGui::SetCursorPosX(cursorPosX);
        ImGui::PushStyleColor(ImGuiCol_Button, __mkeyStatusTable[keycode] ? _mGameKeyColorTable[keycode] : ImVec4(0, 0, 0, 0.25));
        ImGui::Button(_mkeyNameTable[keycode].c_str(), {width ? width : __mButtonWidth, height ? height : __mButtonHeight});
        ImGui::PopStyleColor(1);
    }
};

}

#endif
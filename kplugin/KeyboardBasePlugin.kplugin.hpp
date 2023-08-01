#ifndef __KEYBOARD_BASE_PLUGIN_HPP__KHISTORY
#define __KEYBOARD_BASE_PLUGIN_HPP__KHISTORY

#include "KPlugin.h"

#include "PAL.h"

namespace khistory {

class KeyboardBasePlugin : public KPluginInterface {

public:
    KeyboardBasePlugin() {
        KPluginInterface::_mPluginNmae = "Keyboard Base";
        for (auto &kStatus : __mkeyStatusTable) kStatus = false;
    }

public: // interface impl

    virtual void gameKeyColorTableInit() override {
        // gamepad key-color init
        _mGameKeyColorTable['W'] = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
        _mGameKeyColorTable['A'] = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
        _mGameKeyColorTable['S'] = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
        _mGameKeyColorTable['D'] = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);

        _mGameKeyColorTable['Y'] = ImVec4(0.0f, 0.0f, 0.5f, 0.5f);
        _mGameKeyColorTable['U'] = ImVec4(0.5f, 0.0f, 0.5f, 0.5f);
        _mGameKeyColorTable['I'] = ImVec4(0.8f, 0.5f, 0.5f, 0.5f);
        _mGameKeyColorTable['O'] = ImVec4(0.5f, 0.5f, 0.8f, 0.5f);

        _mGameKeyColorTable['H'] = ImVec4(178 / 255.0f, 1.0f, 102 / 255.0f, 0.5f);
        _mGameKeyColorTable['J'] = ImVec4(255 / 255.0f, 102 / 255.0f, 102 / 255.0f, 0.5f);
        _mGameKeyColorTable['K'] = ImVec4(0.0f, 1.0f, 1.0f, 0.5f);
        _mGameKeyColorTable['L'] = ImVec4(1.0f, 1.0f, 0.0f, 0.5f);

        _mGameKeyColorTable[' '] = ImVec4(0.6f, 0.7f, 0.8f, 0.5f);
    }

    /*
        +-----------------------------+
        |    W    |        | Y U I O  |
        |  A S D  |        | H J K L  |
        |                             |
        +-----------------------------+
    */
    void gameKeyLayoutVisualImpl() override {
        ImGuiStyle& style = ImGui::GetStyle();
        const float spacing = 2.0f;
        auto oldSpacing = style.ItemSpacing;

        style.ItemSpacing = ImVec2(spacing, spacing);

        __mButtonWidth = __mButtonHeight = ImGui::GetWindowWidth() / 11; // 5 + 6

        { // W | Y U I O
            __drawKeyButton('W', __mButtonWidth * 2); ImGui::SameLine();
            __drawKeyButton('Y', __mButtonWidth * (5 + 1) + spacing * 2); ImGui::SameLine();
            __drawKeyButton('U', __mButtonWidth * (5 + 2) + spacing * 3); ImGui::SameLine();
            __drawKeyButton('I', __mButtonWidth * (5 + 3) + spacing * 4); ImGui::SameLine();
            __drawKeyButton('O', __mButtonWidth * (5 + 4) + spacing * 5);
        }
        { // A S D | H J K L
            __drawKeyButton('A', __mButtonWidth * 1 - spacing); ImGui::SameLine();
            __drawKeyButton('S', __mButtonWidth * 2); ImGui::SameLine();
            __drawKeyButton('D', __mButtonWidth * 3 + spacing * 1); ImGui::SameLine();
            __drawKeyButton('H', __mButtonWidth * (5 + 1) + spacing * 2); ImGui::SameLine();
            __drawKeyButton('J', __mButtonWidth * (5 + 2) + spacing * 3); ImGui::SameLine();
            __drawKeyButton('K', __mButtonWidth * (5 + 3) + spacing * 4); ImGui::SameLine();
            __drawKeyButton('L', __mButtonWidth * (5 + 4) + spacing * 5);
        }
        {
            __drawKeyButton(' ', __mButtonWidth * 3, __mButtonWidth * 5);
        }

        style.ItemSpacing = oldSpacing;
    }

    void updateKeyStatus(const dstruct::Vector<int> &keyVec) override {
        for (auto &kStatus : __mkeyStatusTable) kStatus = false;
        for (auto keycode : keyVec) {
            // keyboard
            if (PAL::KeyMapTable[keycode].size() == 1) { // only detect alpha
                __mkeyStatusTable[PAL::KeyMapTable[keycode][0]] = true;
            } else if (PAL::KeyMapTable[keycode] == "Space") {
                __mkeyStatusTable[' '] = true;
            }
        }
    }

protected:
    dstruct::Array<ImVec4, KEYBOARD_KEY_NUMBERS> _mGameKeyColorTable;

private:
    float __mButtonWidth, __mButtonHeight;
    dstruct::Array<bool, KEYBOARD_KEY_NUMBERS> __mkeyStatusTable;

    void __drawKeyButton(char keycode, float cursorPosX = 0, float width = 0, float height = 0) {
        std::string buttonName;
        buttonName.push_back(keycode);

        ImGui::SetCursorPosX(cursorPosX);
        ImGui::PushStyleColor(ImGuiCol_Button, __mkeyStatusTable[keycode] ? _mGameKeyColorTable[keycode] : ImVec4(0, 0, 0, 0.25));
        ImGui::Button(buttonName.c_str(), {width ? width : __mButtonWidth, height ? height : __mButtonHeight});
        ImGui::PopStyleColor(1);
    }

};

}

#endif
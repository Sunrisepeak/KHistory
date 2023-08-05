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

#include "KeyHistory.h"
#include "TargetWindowKeyDetect.h"

namespace khistory {

dstruct::Vector<ImVec4> KeyHistory::_mKeyColorMapTable;
dstruct::Vector<KPluginInterface *> KeyHistory::_mPluginVec;

KeyHistory::KeyHistory() : _mCurrentPluginIndex { 0 } {
    _mName = "KeyHistory";
    _mHistoryNums = 5;
    _mKeyDetectFPS = 60;
    _mTransparency = 80;
    _mFullScreen = true;
    // init History Q
    for (int i = 0; i < _mHistoryNums; i++) {
        _mKeyHistoryQueue.push({{}, 0});
    }
    // generator: key color table
    _mKeyColorMapTable.resize(KEY_NUMBERS, ImVec4(0, 0, 0, 0.5));

    // keyboard key-color init
    int colorIndex = 0;
    for (int r = 0; r < 16; r += 2) { // 8
        for (int g = 0; g < 16; g += 2) {  // 8
            for (int b = 0; b < 16; b += 4) { // 4
                _mKeyColorMapTable[colorIndex++] = ImVec4(r / 15.0f, g / 15.0f, b / 15.0f, 0.8f);
            }
        }
    }

    // gamepad key-color init
    _mKeyColorMapTable[PAL::GamepadKey::DPAD_UP]        = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
    _mKeyColorMapTable[PAL::GamepadKey::DPAD_DOWN]      = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
    _mKeyColorMapTable[PAL::GamepadKey::DPAD_LEFT]      = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
    _mKeyColorMapTable[PAL::GamepadKey::DPAD_RIGHT]     = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);

    _mKeyColorMapTable[PAL::GamepadKey::START]          = ImVec4(0.6f, 0.7f, 0.8f, 0.5f);
    _mKeyColorMapTable[PAL::GamepadKey::BACK]           = ImVec4(0.6f, 0.7f, 0.8f, 0.5f);

    _mKeyColorMapTable[PAL::GamepadKey::A]              = ImVec4(178 / 255.0f, 1.0f, 102 / 255.0f, 0.5f);
    _mKeyColorMapTable[PAL::GamepadKey::B]              = ImVec4(255 / 255.0f, 102 / 255.0f, 102 / 255.0f, 0.5f);
    _mKeyColorMapTable[PAL::GamepadKey::X]              = ImVec4(0.0f, 1.0f, 1.0f, 0.5f);
    _mKeyColorMapTable[PAL::GamepadKey::Y]              = ImVec4(1.0f, 1.0f, 0.0f, 0.5f);

    _mKeyColorMapTable[PAL::GamepadKey::LEFT_BUMPER]    = ImVec4(0.0f, 0.0f, 1.0f, 0.5f);
    _mKeyColorMapTable[PAL::GamepadKey::RIGHT_BUMPER]   = ImVec4(0.0f, 0.0f, 1.0f, 0.5f);
    _mKeyColorMapTable[PAL::GamepadKey::LEFT_TRIGGER]   = ImVec4(1.0f, 0.0f, 0.0f, 0.5f);
    _mKeyColorMapTable[PAL::GamepadKey::RIGHT_TRIGGER]  = ImVec4(1.0f, 0.0f, 0.0f, 0.5f);

    DSTRUCT_ASSERT(_mPluginVec.empty() != true);
}

void KeyHistory::setTransparency(int transparency) {
    _mTransparency = transparency % 101;
}

int KeyHistory::_registerPlugin(KPluginInterface *plugin) {
    plugin->init();
    _mPluginVec.push_back(plugin);
    return 0; // Note: don't delete the return
}

void KeyHistory::_drawBasicInfoImpl() {
    ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NavEnableGamepad; // disable gamepad input
    ImGui::Text("Window FPS: %.2f", ImGui::GetIO().Framerate);
    ImGui::Text("Real Key-Detect FPS: %.2f", TargetWindowKeyDetect::getInstance().getRealDetectFPS());
    ImGui::Separator();
    auto current_time = std::chrono::system_clock::now();
    std::time_t current_time_t = std::chrono::system_clock::to_time_t(current_time);
    std::tm* local_time = std::localtime(&current_time_t);
    ImGui::Text("Date: %s", std::asctime(local_time));
}

void KeyHistory::_drawVisualImpl() {

    _mPluginVec[_mCurrentPluginIndex]->keyLayoutVisualImpl();

    ImGui::Separator();
    {
        __KeyData kd;
        auto keyVec = TargetWindowKeyDetect::getInstance().getPressedKeyVec();

        if (!_mKeyHistoryQueue.empty()) {
            bool needUpdate = false;
            kd = _mKeyHistoryQueue.back();
            if (kd.keyVec.size() == keyVec.size()) {
                for (int i = 0; i < kd.keyVec.size(); i++) {
                    if (kd.keyVec[i] != keyVec[i]) {
                        needUpdate = true;
                        break;
                    }
                }
            } else needUpdate = true;

            if (needUpdate) {
                kd.keyVec = keyVec;
                kd.time = 1;
                _mPluginVec[_mCurrentPluginIndex]->updateKeyStatus(keyVec);
            } else { 
                _mKeyHistoryQueue.pop_back();
                kd.time += 1;
            }
        }

        _mKeyHistoryQueue.push(kd);

        while (_mKeyHistoryQueue.size() > _mHistoryNums) _mKeyHistoryQueue.pop();
        for (auto keyData : _mKeyHistoryQueue) {
            ImGui::Text(" %2d -> ", keyData.time > 99 ? 99 : keyData.time);
            if (keyData.keyVec.empty()) {
                ImGui::SameLine(); ImGui::Button("NULL");
            } else {
                for (auto k : keyData.keyVec) {
                    ImGui::SameLine();
                    ImGui::PushStyleColor(ImGuiCol_Button, _mKeyColorMapTable[k]);
                    ImGui::Button((" " + PAL::KeyMapTable[k] + " ").c_str());
                    ImGui::PopStyleColor(1);
                }
            }
            ImGui::Separator();
        }
    }
}

void KeyHistory::_drawControlImpl() {
    {
        ImGui::SetNextItemWidth(ImGui::GetWindowWidth());
        ImGui::SliderInt("Key Detect FPS", &_mKeyDetectFPS, 30, 240, "Set Key Detect FPS %d");
        TargetWindowKeyDetect::getInstance().setDetectFPS(_mKeyDetectFPS);
    }
    ImGui::Separator();
    {
        ImGui::SetNextItemWidth(ImGui::GetWindowWidth());
        ImGui::SliderInt("History Numbers", &_mHistoryNums, 5, 25, "History Numbers %d");
    }
    ImGui::Separator();
    {
        int transparency = _mTransparency;
        ImGui::SetNextItemWidth(ImGui::GetWindowWidth());
        ImGui::SliderInt("Transparency", &transparency, 0, 100, "Transparency %d%");
        if (transparency != _mTransparency) {
            static bool fontColorFlip = !(_mTransparency < 30);
            static auto fontColor = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
            _mTransparency = transparency;
            ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = _mTransparency / 100.f;
            if ((_mTransparency < 30) == fontColorFlip) {
                fontColorFlip = !(_mTransparency < 30);
                std::swap(ImGui::GetStyle().Colors[ImGuiCol_Text], fontColor);
            }
        }
    }
    ImGui::Separator();
    {  
        std::string windowName = "select a target window";
        auto highlight = ImVec4(1.f, 0.f, 0.f, 0.4f);
        static bool isListening = false;
        auto oldTargetWindowName = TargetWindowKeyDetect::getInstance().getTargetWindow().toString();
        
        if (oldTargetWindowName != "") windowName = oldTargetWindowName;
        if (isListening) highlight = ImVec4(0.f, 1.0f, 0.f, .6f);
        ImGui::PushStyleColor(ImGuiCol_Button, highlight);
        if (ImGui::Button("Listen")) {
            TargetWindowKeyDetect::getInstance().setTargetWindow({0, ""});
            isListening = false;
        }
        ImGui::PopStyleColor(1);
        ImGui::SameLine();

        if (ImGui::BeginCombo(" <- window", windowName.c_str(), 0)) {
            auto currentWindowList = TargetWindowKeyDetect::getInstance().getWindowInfoList();
            TargetWindowKeyDetect::getInstance().setTargetWindow({0, ""});
            isListening = false;
            for (int n = 0; n < currentWindowList.size(); n++) {
                const bool is_selected = (windowName == currentWindowList[n].toString());
                if (ImGui::Selectable(currentWindowList[n].toString().c_str(), is_selected)) {
                    TargetWindowKeyDetect::getInstance().setTargetWindow(currentWindowList[n]);
                    isListening = true;
                }
                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }
    ImGui::Separator();
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.5f, 1.0f, 0.5f));
        if (ImGui::Button(" Next ")) {
            if (!_mPluginVec.empty())
                _mCurrentPluginIndex = (_mCurrentPluginIndex + 1) % _mPluginVec.size();
        }
        ImGui::PopStyleColor(1);
        ImGui::SameLine();

        auto oldPluginName = _mPluginVec[_mCurrentPluginIndex]->getPluginName();
        if (ImGui::BeginCombo(" <- plugin", oldPluginName.c_str(), 0)) {
            for (int i = 0; i < _mPluginVec.size(); i++) {
                const bool is_selected = (oldPluginName == _mPluginVec[i]->getPluginName());
                if (ImGui::Selectable(_mPluginVec[i]->getPluginName().c_str(), is_selected)) {
                    _mCurrentPluginIndex = i;
                }
                if (is_selected) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }
}

/*
 Note:
    Please don't modify or delete the about section of software
    If you are a developer and have done secondary development(example: add a plugin) of the software,
    you can add your info
*/
void KeyHistory::_drawAboutImpl() {
    {
        ImGui::Text("Author: Sunrisepeak");
        ImGui::Text("Desc: this is an opensource/cross-platform and free software");
        ImGui::Text("OS: support WIN/Linux/MAC");
        ImGui::Text("Github ID: Sunrisepeak");
        ImGui::Text("Bilibili ID: sunrisepeak");
        ImGui::Separator();
        {
            ImGui::PushID("xxx");
            char input[256] = "ProjectLinks/MoreDetials: https://github.com/Sunrisepeak/KeyHistory";
            ImGui::PushItemWidth(ImGui::GetWindowSize().x);
            ImGui::InputText("", input, 256, ImGuiInputTextFlags_ReadOnly);
            ImGui::PopItemWidth();
            ImGui::PopID();
        }
    }
    ImGui::Separator();
    if (ImGui::TreeNode("Contributor")) {
        ImGui::Text("Sunrisepeak: author / maintainer");
        //ImGui::Text("Your ID: Your Work about the software");
        //ImGui::Text("Your ID: bugfix / ... ");
        //ImGui::Text("Your ID: add xxx plugin / ...");
        ImGui::TreePop();
    }
}

}
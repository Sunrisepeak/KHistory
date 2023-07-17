#include "KeyHistory.h"
#include "TargetWindowKeyDetect.h"

namespace khistory {

dstruct::Vector<ImVec4> KeyHistory::_mKeyColorMapTable;

KeyHistory::KeyHistory() {
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

    _mGameKeyHighlightTable.resize(KEY_NUMBERS, ImVec4(0, 0, 0, 0.25));
}

void KeyHistory::setTransparency(int transparency) {
    _mTransparency = transparency % 101;
}

/*
    +-----------------------------+
    |    ^    |    W    |    Y    |
    |  <   >  |  A   D  |  X   B  |
    |    v    |    S    |    A    |
    +-----------------------------+
*/
void KeyHistory::__gameKeyVisualImpl() {
    ImGuiStyle& style = ImGui::GetStyle();
    const float spacing = 2.0f;
    auto oldSpacing = style.ItemSpacing;

    style.ItemSpacing = ImVec2(spacing, spacing);

    float areaHeight = ImGui::GetWindowHeight() / 3;
    float areaWidth = ImGui::GetWindowWidth() / 3;
    float bWidth = areaWidth / 4, bHeight = bWidth;

    {
        int firstLineAreaStart = areaWidth / 2 - bWidth / 2;

        ImGui::SetCursorPosX(firstLineAreaStart);
        ImGui::PushStyleColor(ImGuiCol_Button, _mGameKeyHighlightTable['^']); ImGui::Button("^", {bWidth, bHeight}); ImGui::PopStyleColor(1);
        ImGui::SameLine();

        ImGui::SetCursorPosX(areaWidth + firstLineAreaStart);
        ImGui::PushStyleColor(ImGuiCol_Button, _mGameKeyHighlightTable['W']); ImGui::Button("W", {bWidth, bHeight}); ImGui::PopStyleColor(1);
        ImGui::SameLine();

        ImGui::SetCursorPosX(2 * areaWidth + firstLineAreaStart);
        ImGui::PushStyleColor(ImGuiCol_Button, _mGameKeyHighlightTable['y']); ImGui::Button("Y", {bWidth, bHeight}); ImGui::PopStyleColor(1);
    }
    {
        int secondLineAreaStart = bWidth / 2;
        {
            ImGui::SetCursorPosX(secondLineAreaStart);
            ImGui::PushStyleColor(ImGuiCol_Button, _mGameKeyHighlightTable['<']); ImGui::Button("<", {bWidth, bHeight}); ImGui::PopStyleColor(1);
            ImGui::SameLine();
            ImGui::SetCursorPosX(secondLineAreaStart + bWidth * 2);
            ImGui::PushStyleColor(ImGuiCol_Button, _mGameKeyHighlightTable['>']); ImGui::Button(">", {bWidth, bHeight}); ImGui::PopStyleColor(1);
            ImGui::SameLine();
        }
        {
            ImGui::SetCursorPosX(areaWidth + bWidth / 2 - spacing);
            ImGui::PushStyleColor(ImGuiCol_Button, _mGameKeyHighlightTable['A']); ImGui::Button("A", {bWidth, bHeight}); ImGui::PopStyleColor(1);
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, _mGameKeyHighlightTable['S']); ImGui::Button("S", {bWidth, bHeight}); ImGui::PopStyleColor(1);
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, _mGameKeyHighlightTable['D']); ImGui::Button("D", {bWidth, bHeight}); ImGui::PopStyleColor(1);
            ImGui::SameLine();
        }
        {
            ImGui::SetCursorPosX(2 * areaWidth + secondLineAreaStart);
            ImGui::PushStyleColor(ImGuiCol_Button, _mGameKeyHighlightTable['x']); ImGui::Button("X", {bWidth, bHeight}); ImGui::PopStyleColor(1);
            ImGui::SameLine();
            ImGui::SetCursorPosX(2 * areaWidth + secondLineAreaStart + bWidth * 2);
            ImGui::PushStyleColor(ImGuiCol_Button, _mGameKeyHighlightTable['b']); ImGui::Button("B", {bWidth, bHeight}); ImGui::PopStyleColor(1);
        }
    }
    {
        int thirdLineAreaStart = areaWidth / 2 - bWidth / 2;
        ImGui::SetCursorPosX(thirdLineAreaStart);
        ImGui::PushStyleColor(ImGuiCol_Button, _mGameKeyHighlightTable['v']); ImGui::Button("v", {bWidth, bHeight}); ImGui::PopStyleColor(1);
        ImGui::SameLine();
        ImGui::SetCursorPosX(2 * areaWidth + thirdLineAreaStart);
        ImGui::PushStyleColor(ImGuiCol_Button, _mGameKeyHighlightTable['a']); ImGui::Button("A", {bWidth, bHeight}); ImGui::PopStyleColor(1);
    }

    style.ItemSpacing = oldSpacing;
}

void KeyHistory::__updateGameKeyHighlightVec(const __KeyData &kd) {
    _mGameKeyHighlightTable.resize(KEY_NUMBERS, ImVec4(0, 0, 0, 0.25));
    // keyboard
    for (auto key : kd.keyVec) {
        if (PAL::gamepadConnected) { // use lowercase for gamepad
            if (PAL::KeyMapTable[key] == "<") _mGameKeyHighlightTable['<'] = _mKeyColorMapTable[key];
            else if (PAL::KeyMapTable[key] == ">") _mGameKeyHighlightTable['>'] = _mKeyColorMapTable[key];
            else if (PAL::KeyMapTable[key] == "^") _mGameKeyHighlightTable['^'] = _mKeyColorMapTable[key];
            else if (PAL::KeyMapTable[key] == "v") _mGameKeyHighlightTable['v'] = _mKeyColorMapTable[key];
            else if (PAL::KeyMapTable[key] == "X") _mGameKeyHighlightTable['x'] = _mKeyColorMapTable[key];
            else if (PAL::KeyMapTable[key] == "A") _mGameKeyHighlightTable['a'] = _mKeyColorMapTable[key];
            else if (PAL::KeyMapTable[key] == "B") _mGameKeyHighlightTable['b'] = _mKeyColorMapTable[key];
            else if (PAL::KeyMapTable[key] == "Y") _mGameKeyHighlightTable['y'] = _mKeyColorMapTable[key];
        } else {
            // keyboard
            if (PAL::KeyMapTable[key] == "W") _mGameKeyHighlightTable['W'] = _mKeyColorMapTable[key];
            else if (PAL::KeyMapTable[key] == "A") _mGameKeyHighlightTable['A'] = _mKeyColorMapTable[key];
            else if (PAL::KeyMapTable[key] == "S") _mGameKeyHighlightTable['S'] = _mKeyColorMapTable[key];
            else if (PAL::KeyMapTable[key] == "D") _mGameKeyHighlightTable['D'] = _mKeyColorMapTable[key];
        }
    }
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

    __gameKeyVisualImpl();

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
                __updateGameKeyHighlightVec(kd);
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
        auto oldTargetWindow = TargetWindowKeyDetect::getInstance().getTargetWindow();
        auto highlight = ImVec4(1.f, 0.f, 0.f, 0.4f);
        static bool isListening = false;
        if (isListening) highlight = ImVec4(0.f, 1.0f, 0.f, .6f);
        ImGui::PushStyleColor(ImGuiCol_Button, highlight);
        if (ImGui::Button("Listen")) {
            TargetWindowKeyDetect::getInstance().setTargetWindow({0, ""});
            isListening = false;
        }
        ImGui::PopStyleColor(1);
        ImGui::SameLine();
        if (ImGui::BeginCombo(" <- select", oldTargetWindow.toString().c_str(), 0)) {
            auto currentWindowList = TargetWindowKeyDetect::getInstance().getWindowInfoList();
            TargetWindowKeyDetect::getInstance().setTargetWindow({0, ""});
            isListening = false;
            for (int n = 0; n < currentWindowList.size(); n++) {
                const bool is_selected = (oldTargetWindow.name == currentWindowList[n].name);
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
}

void KeyHistory::_drawAboutImpl() {
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

}
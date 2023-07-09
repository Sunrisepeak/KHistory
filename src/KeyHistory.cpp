#include "KeyHistory.h"
#include "TargetWindowKeyDetect.h"

namespace khistory {

KeyHistory::KeyHistory() {
    _mName = "KeyHistory";
    _mHistoryNums = 10;
    for (int i = 0; i < 10; i++)
        _mKeyHistoryQueue.push({"", 0});
}

void KeyHistory::_drawBasicInfoImpl() {
    ImGui::Text(" "); ImGui::SameLine(); ImGui::Button("W");
    ImGui::Button("A"); ImGui::SameLine(); ImGui::Button("S"); ImGui::SameLine(); ImGui::Button("D");
}

void KeyHistory::_drawVisualImpl() {
    __KeyData kd { " ", 1 };

    auto keyVec = TargetWindowKeyDetect::getInstance().getPressedKeyList();

    for (auto k : keyVec) {
        kd.keyName += PAL::KeyMapTable[k] + " ";
    }

    if (!_mKeyHistoryQueue.empty() && _mKeyHistoryQueue.back().keyName == kd.keyName) {
        kd.time = _mKeyHistoryQueue.back().time + 1;
        _mKeyHistoryQueue.pop_back();
    }

    _mKeyHistoryQueue.push(kd);

    while (_mKeyHistoryQueue.size() > _mHistoryNums) _mKeyHistoryQueue.pop();
    for (auto keyData : _mKeyHistoryQueue) {
        ImGui::Text(" %2d -> ", keyData.time > 99 ? 99 : keyData.time); ImGui::SameLine();
        ImGui::Button(keyData.keyName.c_str());
        ImGui::Separator();
    }
}

void KeyHistory::_drawControlImpl() {
    {
        ImGui::SetNextItemWidth(ImGui::GetWindowWidth());
        ImGui::SliderInt("", &_mHistoryNums, 5, 25, "History Numbers %d");
    }
    ImGui::Separator();
    {  
        auto oldTargetWindow = TargetWindowKeyDetect::getInstance().getTargetWindow();
        auto highlight = ImVec4(1.f, 0.f, 0.f, 0.4f);
        static bool isListening = false;
        if (isListening) highlight = ImVec4(0.f, 1.0f, 0.f, .6f);
        ImGui::PushStyleColor(ImGuiCol_Button, highlight);
        ImGui::Button("Listen");
        ImGui::PopStyleColor(1);
        ImGui::SameLine();
        if (ImGui::BeginCombo("X", oldTargetWindow.toString().c_str(), 0)) {
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

}
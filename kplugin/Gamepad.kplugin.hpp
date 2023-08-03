#ifndef __GAMEPAD_BASE_PLUGIN_HPP__KHISTORY
#define __GAMEPAD_BASE_PLUGIN_HPP__KHISTORY

#include "PluginBase.hpp"

namespace khistory {

class Gamepad : public PluginBase {

public:
    Gamepad() {
        KPluginInterface::_mPluginNmae += " - Gamepad";
    }

public: // interface impl
    virtual void keyColorTableRemap() override {
        // gamepad key-color init
        _mGameKeyColorTable[KeyCode::GAMEPAD_DPAD_UP]        = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
        _mGameKeyColorTable[KeyCode::GAMEPAD_DPAD_DOWN]      = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
        _mGameKeyColorTable[KeyCode::GAMEPAD_DPAD_LEFT]      = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);
        _mGameKeyColorTable[KeyCode::GAMEPAD_DPAD_RIGHT]     = ImVec4(229 / 255.0f, 153 / 255.0f, 1.0f, 0.5f);

        _mGameKeyColorTable[KeyCode::GAMEPAD_START]          = ImVec4(0.6f, 0.7f, 0.8f, 0.5f);
        _mGameKeyColorTable[KeyCode::GAMEPAD_BACK]           = ImVec4(0.8f, 0.7f, 0.6f, 0.5f);

        _mGameKeyColorTable[KeyCode::GAMEPAD_A]              = ImVec4(178 / 255.0f, 1.0f, 102 / 255.0f, 0.5f);
        _mGameKeyColorTable[KeyCode::GAMEPAD_B]              = ImVec4(255 / 255.0f, 102 / 255.0f, 102 / 255.0f, 0.5f);
        _mGameKeyColorTable[KeyCode::GAMEPAD_X]              = ImVec4(0.0f, 1.0f, 1.0f, 0.5f);
        _mGameKeyColorTable[KeyCode::GAMEPAD_Y]              = ImVec4(1.0f, 1.0f, 0.0f, 0.5f);

        _mGameKeyColorTable[KeyCode::GAMEPAD_LEFT_BUMPER]    = ImVec4(128 / 255.0f, 0.0f, 128 / 255.0f, 0.5f);
        _mGameKeyColorTable[KeyCode::GAMEPAD_RIGHT_BUMPER]   = ImVec4(128 / 255.0f, 0.0f, 128 / 255.0f, 0.5f);
        _mGameKeyColorTable[KeyCode::GAMEPAD_LEFT_TRIGGER]   = ImVec4(0.3f, 0.3f, 0.3f, 0.8f);
        _mGameKeyColorTable[KeyCode::GAMEPAD_RIGHT_TRIGGER]  = ImVec4(0.3f, 0.3f, 0.3f, 0.8f);
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
    virtual void keyLayoutImpl(float layoutWidth, float layoutHeight) override {

        float areaWidth = layoutWidth / 3;

        {
            float fontScale = _mButtonHeight < 50 ? 0.65 : 1;
            { // LT/RT
                _drawKey(KeyCode::GAMEPAD_LEFT_TRIGGER,
                    _mButtonWidth, -1, // cursor x / y
                    2 * _mButtonWidth, _mButtonHeight / 2,
                    fontScale
                ); _SameLine();
                _drawKey(KeyCode::GAMEPAD_RIGHT_TRIGGER, 2 * areaWidth + _mButtonWidth, -1, 2 * _mButtonWidth, _mButtonHeight / 2, fontScale);
            }
            { // LB/RB
                _drawKey(KeyCode::GAMEPAD_LEFT_BUMPER, _mButtonWidth, -1, 2 * _mButtonWidth, _mButtonHeight / 2, fontScale); _SameLine();
                _drawKey(KeyCode::GAMEPAD_RIGHT_BUMPER, 2 * areaWidth + _mButtonHeight, -1, 2 * _mButtonWidth, _mButtonHeight / 2, fontScale);
            }
        }
        {
            int firstLineAreaStart = areaWidth / 2 - _mButtonWidth / 2;
            _drawKey(KeyCode::GAMEPAD_DPAD_UP, firstLineAreaStart); _SameLine();
            _drawKey(KeyCode::GAMEPAD_Y, 2 * areaWidth + firstLineAreaStart);
        }
        {
            int secondLineAreaStart = _mButtonWidth / 2;
            {
                _drawKey(KeyCode::GAMEPAD_DPAD_LEFT, secondLineAreaStart); _SameLine();
                _drawKey(KeyCode::GAMEPAD_DPAD_RIGHT, secondLineAreaStart + _mButtonWidth * 2); _SameLine();
            }
            { // back / start
                float fontScale = _mButtonHeight / 2 < 25 ? 0.45 : 0.7;
                _drawKey(
                    KeyCode::GAMEPAD_BACK,
                    areaWidth + secondLineAreaStart, -1,
                    _mButtonWidth, _mButtonHeight / 2,
                    fontScale
                ); _SameLine();
                _drawKey(KeyCode::GAMEPAD_START, areaWidth + secondLineAreaStart + _mButtonWidth * 2, -1, _mButtonWidth, _mButtonHeight / 2, fontScale); _SameLine();
            }
            {
                _drawKey(KeyCode::GAMEPAD_X, 2 * areaWidth + secondLineAreaStart); _SameLine();
                _drawKey(KeyCode::GAMEPAD_B, 2 * areaWidth + secondLineAreaStart + _mButtonWidth * 2);
            }
        }
        {
            int thirdLineAreaStart = areaWidth / 2 - _mButtonWidth / 2;
            _drawKey(KeyCode::GAMEPAD_DPAD_DOWN, thirdLineAreaStart); _SameLine();
            _drawKey(KeyCode::GAMEPAD_A, 2 * areaWidth + thirdLineAreaStart);
        }
    }
};

}

#endif
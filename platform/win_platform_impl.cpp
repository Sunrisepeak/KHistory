#include "PAL.h"

// std
#include <cstdio>
#include <string>
#include <codecvt>
#include <locale>
#include <mutex>

// dstruct
#include <dstruct.hpp>

// win api
#include <Windows.h>
#include <XInput.h> // gamepad
#pragma comment(lib, "Xinput.lib")

namespace khistory {

static HHOOK gKeyboardHook;
static unsigned int gTargetWindowID;
std::mutex gKeyEventMutex;
dstruct::Queue<PAL::KeyData> gKeyEventQ;

std::string tcharToString(const TCHAR* tcharArray);
LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam); // keyboard hook

void PAL::platformInit() {
    PAL::gamepadConnected = false;
    gTargetWindowID = 0;
    gKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);
    DSTRUCT_ASSERT(gKeyboardHook != NULL);
    // init KeyMapTable
    KeyMapTable.resize(256, "");
    TCHAR  keyName[256] = { 0 };
    for (int i = 0; i < 256; i++) {
        int result = GetKeyNameText(i << 16, keyName, sizeof(keyName));
        if (result > 0) {
            KeyMapTable[i] = tcharToString(keyName);
        }
    }

    PAL::__gamepadKeyDefaultMap();

}

dstruct::Vector<PAL::WindowInfo> PAL::platformWindowInfos() {
    dstruct::Vector<PAL::WindowInfo> infos;
    PAL::WindowInfo info;

    // query window
    HWND hwnd = GetTopWindow(nullptr);
    while (hwnd != nullptr) {
        char buf[256];
        RECT rect;
        if (IsWindowVisible(hwnd)) { // check window
            // get title and size
            GetWindowTextA(hwnd, buf, sizeof(buf));
            GetWindowRect(hwnd, &rect);

            info.id = reinterpret_cast<unsigned long>(hwnd); // TODO: Verify GetDlgCtrlID?
            info.name = buf;
            info.w = rect.right - rect.left;
            info.h = rect.bottom - rect.top;
            if (info.w > 100 && info.h > 100 && info.name != "")
                infos.push_back(info);
        }
        hwnd = GetNextWindow(hwnd, GW_HWNDNEXT);
    }

    return infos;
}

dstruct::Vector<PAL::KeyData> PAL::platformKeyDetect(unsigned int wID) {
    dstruct::Vector<PAL::KeyData> keyDatas;

    if (gTargetWindowID != wID) {
        printf("target window from %d %d", gTargetWindowID, wID);
        gTargetWindowID = wID;
    }

    { // gamepad
        bool connected = false;
        DWORD dwResult;
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        DWORD numControllers = XUSER_MAX_COUNT;

        HWND hWnd = GetForegroundWindow();

        // gamepad connect check
        for (DWORD i = 0; i < numControllers && reinterpret_cast<unsigned int>(hWnd) == gTargetWindowID; ++i) {
            dwResult = XInputGetState(i, &state);
            if (dwResult == ERROR_SUCCESS) {
                connected = true;
                keyDatas.push({GamepadKey::DPAD_UP, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)});
                keyDatas.push({GamepadKey::DPAD_DOWN, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)});
                keyDatas.push({GamepadKey::DPAD_LEFT, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)});
                keyDatas.push({GamepadKey::DPAD_RIGHT, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)});
                keyDatas.push({GamepadKey::START, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)});
                keyDatas.push({GamepadKey::BACK, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)});
                keyDatas.push({GamepadKey::LEFT_SHOULDER, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)});
                keyDatas.push({GamepadKey::RIGHT_SHOULDER, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)});
                keyDatas.push({GamepadKey::A, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)});
                keyDatas.push({GamepadKey::B, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)});
                keyDatas.push({GamepadKey::X, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)});
                keyDatas.push({GamepadKey::Y, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)});

                // Check if R/L trigger is pressed
                keyDatas.push({GamepadKey::LEFT_TRIGGER, state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD});
                keyDatas.push({GamepadKey::RIGHT_TRIGGER, state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD});

                // thumb
                keyDatas.push({GamepadKey::LEFT_THUMB, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)});
                keyDatas.push({GamepadKey::RIGHT_THUMB, 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)});
            }
            //printf("gamepad-id %d, connect: %d\n", i, connected);
        }
        PAL::gamepadConnected = connected;
    }

    if (!PAL::gamepadConnected) {   // keyboard
        MSG msg; // translate msg to hook func
        int msgLimit = 10;
        if (PeekMessage(&msg, reinterpret_cast<HWND>(gTargetWindowID), 0, 0, PM_REMOVE) > 0 && msgLimit--) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        {
            std::lock_guard<std::mutex> _al(gKeyEventMutex);
            while (!gKeyEventQ.empty()) {
                keyDatas.push(gKeyEventQ.front());
                gKeyEventQ.pop();
            }
        }
    }

    return keyDatas;
}

void PAL::platformDeinit() {
    UnhookWindowsHookEx(gKeyboardHook);
}

std::string tcharToString(const TCHAR* tcharArray) { // TODO: Verify
#ifdef UNICODE
    int length = WideCharToMultiByte(CP_UTF8, 0, tcharArray, -1, NULL, 0, NULL, NULL);
    char* charArray = new char[length];
    WideCharToMultiByte(CP_UTF8, 0, tcharArray, -1, charArray, length, NULL, NULL);
#else
    int length = lstrlen(tcharArray) + 1;
    char* charArray = new char[length];
    strcpy_s(charArray, length, tcharArray);
#endif
    std::string result(charArray);
    delete[] charArray;
    return result;
}

LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && !PAL::gamepadConnected) {
        KBDLLHOOKSTRUCT* pKbdStruct = (KBDLLHOOKSTRUCT*)lParam;
        HWND hWnd = GetForegroundWindow();
#if 0
        char buf[256];
        printf("%d %d\n", pKbdStruct->scanCode, wParam);
        GetWindowTextA(hWnd, buf, sizeof(buf));
        printf("%d %d, %s\n", reinterpret_cast<unsigned int>(hWnd), gTargetWindowID, buf);
#endif
        // verify window id & test, is it other programe injected?
        if (reinterpret_cast<unsigned int>(hWnd) == gTargetWindowID /* && (pKbdStruct->flags & LLKHF_INJECTED) == 0 */) {
            PAL::KeyData kd;
            kd.key = pKbdStruct->scanCode;
            if (wParam == WM_KEYDOWN) {
                kd.pressed = true;
            } else if (wParam == WM_KEYUP) {
                kd.pressed = false;
            }
            std::lock_guard<std::mutex> _al(gKeyEventMutex);
            gKeyEventQ.push(kd);
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

}
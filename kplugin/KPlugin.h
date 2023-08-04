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

#ifndef __KPLUGIN_H__KHISTORY
#define __KPLUGIN_H__KHISTORY

// Basic/Demo Plugin
#include "Keyboard.kplugin.hpp"
#include "Gamepad.kplugin.hpp"

#define KPLUGIN_REGISTER(PLUGIN_TYPE) \
    static khistory::PLUGIN_TYPE __gPlugin##PLUGIN_TYPE; \
    auto __gUnused##PLUGIN_TYPE = khistory::KeyHistory::_registerPlugin(&__gPlugin##PLUGIN_TYPE);

// Note: it is auto-generate by script
#include "plugin-auto-register-info.kplugin"

static void loadKPlugin() {
    KPLUGIN_REGISTER(Keyboard);
    KPLUGIN_REGISTER(Gamepad);
    loadAutoRegisterPlugin();
}

#endif
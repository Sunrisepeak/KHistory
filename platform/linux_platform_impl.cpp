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

#include "PAL.h"

// std
#include <cstdio>

// dstruct
#include <dstruct.hpp>

// X11
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XInput2.h> // libxi-dev

namespace khistory {

static Display* display = nullptr;
static Window gCurrentWindowId = 0;
static int gExtensionOpcode = 0;

static void list_windows(Display *display, Window root, int depth, dstruct::Vector<PAL::WindowInfo> &wInfos) {
    Window parent;
    Window *children = nullptr;
    unsigned int nchildren;
    PAL::WindowInfo wInfo;

    if (depth > 3 || XQueryTree(display, root, &root, &parent, &children, &nchildren) == 0) return;

    for (unsigned int i = 0; i < nchildren; i++) {
        char *window_name = NULL;
        XTextProperty prop;
        XWindowAttributes attrs;
        XGetWindowAttributes(display, children[i], &attrs);
        if (attrs.width > 200 || attrs.height > 200) { // remove small window

            wInfo.id = children[i];
            wInfo.w = attrs.width;
            wInfo.h = attrs.height;

            // get window name
            if (XFetchName(display, children[i], &window_name) && window_name != NULL) {
                wInfo.name = window_name;
                XFree(window_name);
            } else if (XGetWMName(display, children[i], &prop) != 0 && prop.value != NULL) {
                char **list; int num;
                if (Xutf8TextPropertyToTextList(display, &prop, &list, &num) == Success && num > 0) {
                    //printf("Window name: %s\n", list[0]);
                    wInfo.name = list[0];
                    XFreeStringList(list);
                }
                XFree(prop.value);
            }

            if (wInfo.name != "/" && wInfo.name != "") // remove root and no name window
                wInfos.push(wInfo);
        }
        list_windows(display, children[i], depth + 1, wInfos);
    }

    if (children) XFree(children);
}

void PAL::platformInit() {

    if (display != nullptr) return;

    // 打开 X11 连接
    display = XOpenDisplay(NULL);

    DSTRUCT_ASSERT(display != nullptr);

    PAL::globalDetectWinID = DefaultRootWindow(display);

    // init key map table
    for (int keycode = 0; keycode < 256; keycode++) {
        char *keyName = XKeysymToString(XKeycodeToKeysym(display, keycode, 0));
        if (keyName) PAL::KeyMapTable[keycode] = keyName;
        for (char& c : PAL::KeyMapTable[keycode]) c = std::toupper(c);
    }

    // Check for XInput 2 extension
    int event, error;
    if (!XQueryExtension(display, "XInputExtension", &gExtensionOpcode, &event, &error)) {
        printf("X Input extension not available. (tips: sudo apt install libxi-dev)\n");
    }

    // Check the version of XInput
    int major = 2, minor = 0;
    if (XIQueryVersion(display, &major, &minor) == BadRequest) {
        printf("XInput2 not available. Server supports version %d.%d\n", major, minor);
    }

}

dstruct::Vector<PAL::WindowInfo> PAL::platformWindowInfos() {
    dstruct::Vector<PAL::WindowInfo> wInfos;

    platformInit();
    DSTRUCT_ASSERT(display != nullptr);
    // recursive get window list
    list_windows(display, DefaultRootWindow(display), 0, wInfos);

    return wInfos;
}

dstruct::Vector<PAL::KeyData> PAL::platformKeyDetect(unsigned int wID) {
    dstruct::Vector<PAL::KeyData> keyEventVec;
    PAL::KeyData kd { 0, false };
    XEvent event;

    //printf ("platformKeyDetect\n");
    
    if (gCurrentWindowId != wID) {
        //printf ("platformKeyDetect: window id, from %ld to %ld\n", gCurrentWindowId, wID);

        // Listen for XI_KeyPress events
        XIEventMask evmasks[1];
        unsigned char mask[(XI_LASTEVENT + 7)/8] = { 0 };

        evmasks[0].deviceid = XIAllDevices;
        evmasks[0].mask_len = sizeof(mask);
        evmasks[0].mask = mask;

        XISetMask(evmasks[0].mask, XI_KeyPress);
        XISetMask(evmasks[0].mask, XI_KeyRelease);

        XISelectEvents(display, wID, evmasks, 1);
        XSync(display, false); // sync event set

        gCurrentWindowId = wID;
    }

    while(XEventsQueued(display, QueuedAfterFlush) > 0) {
        XNextEvent(display, &event);
        if (event.xcookie.type == GenericEvent && event.xcookie.extension == gExtensionOpcode) {
            XGetEventData(display, &event.xcookie);
            XIDeviceEvent* xideviceevent = reinterpret_cast<XIDeviceEvent*>(event.xcookie.data);
            kd.key = xideviceevent->detail; // event.xkey.keycode;
            if (event.xcookie.evtype == XI_KeyPress) {
                kd.pressed = true;
            } else if (event.xcookie.evtype == XI_KeyRelease) {
                kd.pressed = false;
            }
            //printf("key %ld-%d: %d\n", event.xkey.keycode, kd.pressed, xideviceevent->detail);
            XFreeEventData(display, &event.xcookie);
        }
        keyEventVec.push(kd);
    }

    //printf ("platformKeyDetect end");
    return keyEventVec;
}

void PAL::platformDeinit() {
    //if (gCurrentWindowId == PAL::globalDetectWinID)
    //    XUngrabKeyboard(display, CurrentTime);
    // 关闭 X11 连接
    XCloseDisplay(display);
    display = nullptr;
}

}
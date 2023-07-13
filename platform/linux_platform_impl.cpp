#include <iostream>
#include <cstdio>
#include <dstruct.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "PAL.h"

namespace khistory {

static Display* display = nullptr;

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

    // init key map table
    PAL::KeyMapTable.resize(256, "");
    for (int keycode = 0; keycode < 256; keycode++) {
        char *keyName = XKeysymToString(XKeycodeToKeysym(display, keycode, 0));
        if (keyName) PAL::KeyMapTable[keycode] = keyName;
        for (char& c : PAL::KeyMapTable[keycode]) c = std::toupper(c);
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
    static Window currentWindowId = DefaultRootWindow(display);
    dstruct::Vector<PAL::KeyData> keyEventVec;
    PAL::KeyData kd { 0, false };
    XEvent event;

    //printf ("platformKeyDetect\n");

    if (currentWindowId != wID) {
        XSelectInput(display, currentWindowId, 0);
        currentWindowId = wID;
        XSelectInput(display, currentWindowId, KeyPressMask | KeyReleaseMask);
        //printf ("platformKeyDetect: window id, from %ld to %ld\n", currentWindowId, wID);
    }

    while(XEventsQueued(display, QueuedAfterFlush) > 0) {
        XNextEvent(display, &event);
        kd.key = event.xkey.keycode;
        switch (event.type) {
            case KeyPress:
                kd.pressed = true;
                break;
            case KeyRelease:
                kd.pressed = false;
                break;
            default: {
                //printf ("Other Event...!\n");
                //DSTRUCT_ASSERT(false);
            }
        }
        keyEventVec.push(kd);
    }

    //printf ("platformKeyDetect end");
    return keyEventVec;
}

void PAL::platformDeinit() {
    //XUngrabKeyboard(display, CurrentTime);
    // 关闭 X11 连接
    XCloseDisplay(display);
    display = nullptr;
}

}
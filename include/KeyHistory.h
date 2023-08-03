#ifndef __KEY_HISTORY_H__KHISTORY
#define __KEY_HISTORY_H__KHISTORY

// std
#include <string>
// dstruct
#include <dstruct.hpp>
// dsvisual
#include <dsvisual.hpp>

#include "KPluginInterface.h"

namespace khistory {

class KeyHistory : public dsvisual::Widget {
private:
    struct __KeyData {
        dstruct::Vector<int> keyVec;
        int time;
    };
public:
    KeyHistory();
public:
    void setTransparency(int transparency = 50);
    // Note: if you haven't use KPLUGIN_REGISTER, then plugin's lifetime need greater than KeyHistory-Obj
    static int _registerPlugin(KPluginInterface *plugin);
protected: // interface impl
    void _drawBasicInfoImpl() override;
    void _drawVisualImpl() override;
    void _drawControlImpl() override;
    void _drawAboutImpl() override;
protected:
    int _mHistoryNums;
    int _mKeyDetectFPS;
    int _mTransparency;
    dstruct::Deque<__KeyData> _mKeyHistoryQueue;
    static dstruct::Vector<ImVec4> _mKeyColorMapTable;
    int _mCurrentPluginIndex;
    static dstruct::Vector<KPluginInterface *> _mPluginVec;
};

}
#endif
#ifndef __KEY_RECORDER_H__
#define __KEY_RECORDER_H__

// std
#include <string>
// dstruct
#include <dstruct.hpp>
// dsvisual
#include <dsvisual.hpp>


namespace khistory {

class KeyHistory : public dsvisual::Widget {
private:
    struct __KeyData {
        std::string keyName;
        int time;
    };
public:
    KeyHistory();
protected:
    void _drawBasicInfoImpl() override;
    void _drawVisualImpl() override;
    void _drawControlImpl() override;
protected:
    int _mHistoryNums;
    dstruct::Deque<__KeyData> _mKeyHistoryQueue;
};

}
#endif
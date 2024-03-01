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

#ifndef __KPLUGIN_INTERFACE_H__KHISTORY
#define __KPLUGIN_INTERFACE_H__KHISTORY

#include <dstruct.hpp>
#include <dsvisual-core.h>

namespace khistory {

class KPluginInterface {
public: // interface
    virtual void keyLayoutVisualImpl() = 0;
    virtual void updateKeyStatus(const dstruct::Vector<int> &keyVec /* key's press-info */) = 0;
public: // optional interface 
    virtual void init() {  }
public:
    std::string getPluginName() const { return _mPluginName; }
protected:
    std::string _mPluginName;
};

} // namespace khistory end

#endif
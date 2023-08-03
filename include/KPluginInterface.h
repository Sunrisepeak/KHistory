#ifndef __KPLUGIN_INTERFACE_H__KHISTORY
#define __KPLUGIN_INTERFACE_H__KHISTORY

#include <dstruct.hpp>
#include <dsvisual.hpp>

namespace khistory {

class KPluginInterface {
public: // interface
    virtual void keyLayoutVisualImpl() = 0;
    virtual void updateKeyStatus(const dstruct::Vector<int> &keyVec /* key's press-info */) = 0;
public: // optional interface 
    virtual void init() {  }
public:
    std::string getPluginName() const { return _mPluginNmae; }
protected:
    std::string _mPluginNmae;
};

} // namespace khistory end

#endif
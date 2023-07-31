#ifndef __KPLUGIN_H__KHISTORY
#define __KPLUGIN_H__KHISTORY

#include <dstruct.hpp>
#include <dsvisual.hpp>

namespace khistory {

class KPluginInterface {
public: // interface
    virtual void gameKeyLayoutVisualImpl() = 0;
    virtual void updateKeyStatus(const dstruct::Vector<int> &keyVec /* key's press-info */) = 0;
public: // optional interface
    virtual void gameKeyNameTableInit() { }
    virtual void gameKeyColorTableInit() { }
public:
    std::string getPluginName() const { return _mPluginNmae; }
protected:
    std::string _mPluginNmae;
};

} // namespace khistory end

#define KPLUGIN_REGISTER(PLUGIN_TYPE) \
    extern class khistory::##PLUGIN_TYPE; \
    static khistory::##PLUGIN_TYPE __gPlugin##PLUGIN_TYPE; \
    auto __gUnused##PLUGIN_TYPE = khistory::KeyHistory::_registerPlugin(&__gPlugin##PLUGIN_TYPE);

#include "GamepadBasePlugin.kplugin.hpp"
#include "GamepadBasePlugin-Fighting.kplugin.hpp"

#endif
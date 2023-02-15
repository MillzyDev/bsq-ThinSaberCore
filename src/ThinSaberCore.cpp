#include "ThinSaberCore.hpp"
#include "Config.hpp"
#include "Hooks.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"

namespace ThinSaberCore {
    void Setup() {
        Config::loadConfig();
        Config::setupConfig();
    }

    void Load() {
        il2cpp_functions::Init();
        Hooks::InstallAllHooks();
    }
}
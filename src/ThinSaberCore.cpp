#include "ThinSaberCore.hpp"
#include "Config.hpp"
#include "Hooks.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"

void ThinSaberCore::Setup() {
    getConfig().Load();
}

void ThinSaberCore::Load() {
    il2cpp_functions::Init();
    Hooks::InstallAllHooks();
}
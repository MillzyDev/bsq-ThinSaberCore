#include "main.hpp"
#include "ThinSaberCore.hpp"

extern "C" void setup(ModInfo &info) {
    info = modInfo;
    ThinSaberCore::Setup();
}

extern "C" void load() {
    ThinSaberCore::Load();
}
#include "main.hpp"
#include "ThinSaberCore.hpp"

extern "C" [[maybe_unused]] void setup(ModInfo &info) {
    info = modInfo;
    ThinSaberCore::Setup();
}

extern "C" [[maybe_unused]] void load() {
    ThinSaberCore::Load();
}
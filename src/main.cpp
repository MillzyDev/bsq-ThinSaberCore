#include "main.hpp"
#include "ThinSaberCore.hpp"

extern "C"  [[maybe_unused]] void setup(CModInfo* info) {
  info->id = modInfo.id.c_str();
  info->version = modInfo.version.c_str();
  ThinSaberCore::Setup();
}

extern "C" [[maybe_unused]] void load() {
    ThinSaberCore::Load();
}
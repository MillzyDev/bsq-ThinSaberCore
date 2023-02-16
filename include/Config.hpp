#pragma once

#include "beatsaber-hook/shared/config/config-utils.hpp"

namespace ThinSaberCore {
    class Config {
    public:
        static Configuration& getConfig();
        static void loadConfig();
        static void setupConfig();

        static float getThickness();
        static void setThickness(float value);

        static float getLength();
        static void setLength(float value);

        static bool getLawEnforcement();
        static void setLawEnforcement(bool value);
    };
}
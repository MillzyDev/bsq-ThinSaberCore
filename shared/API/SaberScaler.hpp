#pragma once

#include "CustomTypes/Vector3.hpp"

namespace ThinSaberCore {
    class SaberScaler {
    public:
        static float getSaberThickness();
        static void setSaberThickness(float value);

        static float getSaberLength();
        static void setSaberLength(float value);

        static float getLegalisedSaberThickness();
        static float getLegalisedSaberLength();

        static CustomTypes::Vector3 getSaberScale();
        static CustomTypes::Vector3 getGlowScale();

        static CustomTypes::Vector3 getLegalisedSaberScale();
        static CustomTypes::Vector3 getLegalisedGlowScale();
    };
}
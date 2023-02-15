#include "API/SaberScaler.hpp"
#include "Config.hpp"

namespace ThinSaberCore {
    float SaberScaler::getSaberThickness() {
        return Config::getThickness();
    }

    void SaberScaler::setSaberThickness(float value) {
        Config::setThickness(value);
        // TODO: Update Saber when changed in-song
    }

    float SaberScaler::getSaberLength() {
        return Config::getLength();
    }

    void SaberScaler::setSaberLength(float value) {
        Config::setLength(value);
        // TODO " "
    }
}
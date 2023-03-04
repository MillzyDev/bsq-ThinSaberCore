#include "API/SaberScaler.hpp"
#include "API/SaberJudge.hpp"
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

    float SaberScaler::getLegalisedSaberThickness() {
        return SaberJudge::isThicknessLegal() ? getSaberThickness() : 1.0f;
    }

    float SaberScaler::getLegalisedSaberLength() {
        return SaberJudge::isLengthLegal() ? getSaberLength() : 1.0f;;
    }

    CustomTypes::Vector3 SaberScaler::getSaberScale() {
        float thickness = getSaberThickness();
        float length = getSaberLength();
        return { thickness, thickness, length};
    }

    CustomTypes::Vector3 SaberScaler::getGlowScale() {
        float thickness = getSaberThickness();
        float length = getSaberLength();
        return { thickness, length, thickness};
    }

    CustomTypes::Vector3 SaberScaler::getLegalisedSaberScale() {
        float thickness = getLegalisedSaberThickness();
        float length = getLegalisedSaberLength();
        return { thickness, thickness, length};
    }

    CustomTypes::Vector3 SaberScaler::getLegalisedGlowScale() {
        float thickness = getLegalisedSaberThickness();
        float length = getLegalisedSaberLength();
        return { thickness, length, thickness};
    }

    void SaberScaler::setCoreScalerDisabled(bool value) {
        coreScalerDisabled = value;
    }

    bool SaberScaler::getCoreScalerDisabled() {
        return coreScalerDisabled;
    }


}
#include "API/SaberJudge.hpp"
#include "Config.hpp"

namespace ThinSaberCore {
    bool SaberJudge::isSaberScaleLegal() {
        return isThicknessLegal() && isLengthLegal();
    }

    bool SaberJudge::isThicknessLegal() {
        float thickness = Config::getThickness();
        return thickness > 0.0f && thickness < 1.0f;
    }

    bool SaberJudge::isLengthLegal() {
        return Config::getLength() == 1.0f;
    }

    bool SaberJudge::getLawEnforcement() {
        return Config::getLawEnforcement();
    }

    void SaberJudge::setLawEnforcement(bool value) {
        Config::setLawEnforcement(value);
    }
}
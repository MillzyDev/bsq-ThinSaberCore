#include "API/SaberJudge.hpp"
#include "Config.hpp"

namespace ThinSaberCore {
    bool SaberJudge::isSaberScaleLegal() {
        float thickness = Config::getThickness();
        float length = Config::getLength();
        bool legal = thickness > 0.0f && thickness < 1.0f && length == 1.0f;
        return legal;
    }
}
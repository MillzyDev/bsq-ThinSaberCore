#pragma once

namespace ThinSaberCore {
    class SaberJudge {
    public:
        static bool isSaberScaleLegal();
        static bool isThicknessLegal();
        static bool isLengthLegal();

        static bool getLawEnforcement();
        static void setLawEnforcement(bool value);
    };
}
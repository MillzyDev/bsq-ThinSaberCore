/*
#include "ScoreSubmission.hpp"

#include <stdlib.h>
#include <string.h>

#define SCORE_SUBMISSION_DISABLED "disable_ss_upload"

namespace ThinSaberCore {
    void ScoreSubmission::Disable() {
        if (!strcmp(getenv(SCORE_SUBMISSION_DISABLED), "1")) {
            setenv(SCORE_SUBMISSION_DISABLED, "1", true);
        }
    }
}
*/
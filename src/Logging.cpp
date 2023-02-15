#include "Logging.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "main.hpp"

Logger& getLogger() {
    static auto* logger = new Logger(modInfo, {false, true});
    return *logger;
}
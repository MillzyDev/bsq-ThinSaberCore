#include "Hooks.hpp"
#include "Logging.hpp"

namespace ThinSaberCore {
    std::vector<void (*)(Logger &logger)> Hooks::installFuncs;

    void Hooks::AddInstallFunc(void (*installFunc)(Logger &)) {
        installFuncs.push_back(installFunc);
    }

    void Hooks::InstallAllHooks() {
        Logger &logger = Logging::getLogger();
        for (auto installFunc : installFuncs) {
            installFunc(logger);
        }
    }
}
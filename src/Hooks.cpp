#include "Hooks.hpp"
#include "Logging.hpp"

std::vector<void (*)(Logger &logger)> Hooks::installFuncs;

void Hooks::AddInstallFunc(void (*installFunc)(Logger &)) {
    installFuncs.push_back(installFunc);
}

void Hooks::InstallAllHooks() {
    Logger &logger = getLogger();
    for (auto installFunc : installFuncs) {
        installFunc(logger);
    }
}
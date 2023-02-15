#pragma once

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include <vector>

class Hooks {
private:
    static std::vector<void (*)(Logger &logger)> installFuncs;
public:
    static void AddInstallFunc(void (*installFunc)(Logger &logger));
    static void InstallAllHooks();
};

#define InstallHooks(func) \
struct __HookRegister##func {  \
    __HookRegister##func() {   \
        Hooking::AddInstallFunc(func); \
    }                  \
}; \
static __HookRegister##func __HookRegisterInstance##func;
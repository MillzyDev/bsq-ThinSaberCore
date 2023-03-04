#include "Hooks.hpp"
#include "Il2CppMethods/Component.hpp"
#include "Il2CppMethods/Transform.hpp"
//#include "API/SaberJudge.hpp"
#include "API/SaberScaler.hpp"

using namespace ThinSaberCore::Il2CppMethods;

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(SaberModelController_Init, "", "SaberModelController", "Init",
    void, Il2CppObject *self, Il2CppObject *parent, Il2CppObject *saber
) {
    SaberModelController_Init(self, parent, saber);

    if (SaberScaler::getCoreScalerDisabled()) return;

    CustomTypes::Vector3 saberScale = SaberScaler::getSaberScale();
    CustomTypes::Vector3 glowScale = SaberScaler::getGlowScale();
    // TODO: Legalise scales if the hitbox changes (i forgor)

    Il2CppObject *transform = Component::get_transform(self);

    Il2CppObject *basicSaberTransform = Transform::Find(transform, "BasicSaber");
    if (!basicSaberTransform) return;
    Transform::set_localScale(basicSaberTransform, saberScale);

    Il2CppObject *fakeGlow0Transform = Transform::Find(transform, "FakeFlow0");
    if (!fakeGlow0Transform) return;
    Transform::set_localScale(fakeGlow0Transform, glowScale);

    Il2CppObject *fakeFlow1Transform = Transform::Find(transform, "FakeFlow1");
    if (!fakeFlow1Transform) return;
    Transform::set_localScale(fakeFlow1Transform, glowScale);
}

void SaberModelController(Logger &logger) {
    INSTALL_HOOK(logger, SaberModelController_Init)
}

InstallHooks(SaberModelController)
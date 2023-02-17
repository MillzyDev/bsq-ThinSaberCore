#pragma once

#include "beatsaber-hook/shared/utils/il2cpp-type-check.hpp"

namespace ThinSaberCore::CustomTypes {
    typedef struct Vector3 {
        float x, y, z;
    } Vector3;
}

DEFINE_IL2CPP_ARG_TYPE(ThinSaberCore::CustomTypes::Vector3, "UnityEngine", "Vector3");
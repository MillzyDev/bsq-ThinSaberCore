#pragma once

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "CustomTypes/Vector3.hpp"

namespace ThinSaberCore::Il2CppMethods {
    using namespace ThinSaberCore;

    class Transform {
        static void set_localScale(Il2CppObject *obj, CustomTypes::Vector3 value);

        static Il2CppObject *Find(Il2CppObject *obj, std::string_view str);
    };
}
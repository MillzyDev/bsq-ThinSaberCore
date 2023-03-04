#include "Il2CppMethods/Component.hpp"

namespace ThinSaberCore::Il2CppMethods {

    Il2CppObject *Component::get_transform(Il2CppObject *obj) {
        return CRASH_UNLESS(il2cpp_utils::GetPropertyValue(obj, "transform"));
    }
}
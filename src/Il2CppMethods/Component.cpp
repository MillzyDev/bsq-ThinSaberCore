#include "Il2CppMethods/Component.hpp"
#include "Il2CppUtils.hpp"

namespace ThinSaberCore::Il2CppMethods {
    Il2CppObject *Component::get_transform(Il2CppObject *obj) {
        return Il2CppUtils::GetPropertyValue(obj, Il2CppUtils::GetProperty(obj, "transform"));
    }
}
#include "Il2CppMethods/Transform.hpp"
#include "Il2CppUtils.hpp"

#define STRING(str) il2cpp_utils::newcsstr(str)

namespace ThinSaberCore::Il2CppMethods {
    void Transform::set_localScale(Il2CppObject *obj, CustomTypes::Vector3 value) {
        Il2CppUtils::SetPropertyValue(obj, Il2CppUtils::GetProperty(obj, "localScale"), value);
    }

    Il2CppObject *Transform::Find(Il2CppObject *obj, std::string_view str) {
        return Il2CppUtils::InvokeMethodUnsafe(obj, Il2CppUtils::GetMethodInfoUnsafe(obj, "Find", 1), STRING(str));
    }
}
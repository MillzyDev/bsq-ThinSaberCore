#include "Il2CppMethods/Transform.hpp"

#define STRING(str) il2cpp_utils::newcsstr(str)

namespace ThinSaberCore::Il2CppMethods {
    void Transform::set_localScale(Il2CppObject *obj, CustomTypes::Vector3 value) {
        CRASH_UNLESS(il2cpp_utils::SetPropertyValue(obj, "localScale", value));
    }

    Il2CppObject *Transform::Find(Il2CppObject *obj, std::string_view str) {
        return CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe(obj, "Find", il2cpp_utils::newcsstr(str)));
    }
}
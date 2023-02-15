#include "Il2CppUtils.hpp"

namespace ThinSaberCore {

    template<class T>
    PropertyInfo *Il2CppUtils::GetProperty(T &&obj, ::std::string_view propertyName) {
        return CRASH_UNLESS(il2cpp_utils::FindProperty<T>(obj, propertyName));
    }

    template<class TOut, bool checkTypes, class T>
    TOut Il2CppUtils::GetPropertyValue(T &&obj, const PropertyInfo *propertyInfo) {
        return CRASH_UNLESS(il2cpp_utils::GetPropertyValue<TOut, checkTypes, T>(obj, propertyInfo));
    }

    template<bool checkTypes, class T, class TArg>
    bool Il2CppUtils::SetPropertyValue(T &obj, const PropertyInfo *propertyInfo, TArg &&value) {
        return CRASH_UNLESS(il2cpp_utils::SetPropertyValue<checkTypes, T, TArg>(obj, propertyInfo, value));
    }

    MethodInfo *Il2CppUtils::GetMethodInfoUnsafe(Il2CppObject *obj, ::std::string_view methodName, int argCount) {
        return CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(obj, methodName, argCount));
    }

    template<class TOut, class T, class... TArgs>
    TOut Il2CppUtils::InvokeMethodUnsafe(T &&obj, MethodInfo *methodInfo, TArgs &&...params) {
        return CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe<TOut, T, TArgs...>(obj, methodInfo, params...));
    }
}
#pragma once

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include <map>
#include <optional>

namespace ThinSaberCore {
    class Il2CppUtils {
    public:
        template<class T>
        static PropertyInfo *GetProperty(T &&obj, ::std::string_view propertyName);

        template<class TOut = Il2CppObject*, bool checkTypes = true, class T>
        static TOut GetPropertyValue(T &&obj, const PropertyInfo *propertyInfo);

        template<bool checkTypes = true, class T, class TArg>
        static bool SetPropertyValue(T &obj, const PropertyInfo *propertyInfo, TArg &&value);

        static MethodInfo *GetMethodInfoUnsafe(Il2CppObject *obj, ::std::string_view methodName, int argCount);

        template<class TOut = Il2CppObject *, class T, class... TArgs>
        static TOut InvokeMethodUnsafe(T &&obj, MethodInfo *methodInfo, TArgs &&...params);
    };
}
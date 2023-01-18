#include "main.hpp"

#define THICKNESS_VALUE "thickness"
#define TRICKSABER_SAFE_MODE_VALUE "tricksaberSafeMode"

#define CONFIG_VALUE_EXISTS(value) getConfig().config.HasMember(value)
#define DEFINE_CONFIG_ALLOCATOR() rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator()
#define CONFIG_ALLOCATOR allocator
#define ADD_CONFIG_VALUE(value, setValue, allocator) getConfig().config.AddMember(value, rapidjson::Value(0).setValue, allocator)
#define WRITE_CONFIG() getConfig().Write()
#define GET_CONFIG_VALUE(value, getValue) getConfig().config[value].getValue

#define IS_MOD_LOADED(id) mods.find(id) != mods.end()

#pragma region Vector3
typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

DEFINE_IL2CPP_ARG_TYPE(Vector3, "UnityEngine", "Vector3");
#pragma endregion

static ModInfo modInfo;

Vector3 saberScale;

Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

Logger& getLogger() {
    static auto* logger = new Logger(modInfo);
    return *logger;
}

extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;

#pragma region Config
    getConfig().Load();
    DEFINE_CONFIG_ALLOCATOR();
    if (!CONFIG_VALUE_EXISTS(THICKNESS_VALUE)) {
        ADD_CONFIG_VALUE(THICKNESS_VALUE, SetFloat(0.5f), CONFIG_ALLOCATOR);
        WRITE_CONFIG();
    }
    if (!CONFIG_VALUE_EXISTS(TRICKSABER_SAFE_MODE_VALUE)) {
        ADD_CONFIG_VALUE(TRICKSABER_SAFE_MODE_VALUE, SetBool(true), CONFIG_ALLOCATOR);
        WRITE_CONFIG();
    }
#pragma endregion
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(SaberModelController_Init, "", "SaberModelController", "Init", void, Il2CppObject *self,
                                     Il2CppObject *parent, // UnityEngine.Transform
                                     Il2CppObject *saber // global::Saber
                                     ) {
    SaberModelController_Init(self, parent, saber);

    Il2CppObject *transform = CRASH_UNLESS(il2cpp_utils::GetPropertyValue(self, "transform")); // get the UnityEngine.Transform of host GameObject
    static auto *findMethodInfo = CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(transform, "Find", 1)); // get method info for Transform.Find(String) - returns UnityEngine.Transform
    Il2CppObject *basicSaberTransform = CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe(transform, findMethodInfo, il2cpp_utils::newcsstr("BasicSaber"))); // Invoke Transform.Find for "BasicSaber"
    CRASH_UNLESS(il2cpp_utils::SetPropertyValue(basicSaberTransform, "localScale", saberScale)); // Set the localScale of BasicSaber's Transform
}

extern "C" void load() {
    il2cpp_functions::Init();

    auto mods = ::Modloader::getMods();

    if (IS_MOD_LOADED("ShortSaber") || IS_MOD_LOADED("thinsabers")) {
        getLogger().info("ShortSaber or ThinSabers is installed. Not continuing with hook installs.");
        return;
    }

    if (IS_MOD_LOADED("tricksaber") && GET_CONFIG_VALUE(TRICKSABER_SAFE_MODE_VALUE, GetBool())) {
        getLogger().info("TrickSaber is installed with TrickSaber Safe Mode on. Not continuing with hook installs.");
        return;
    }

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), SaberModelController_Init);
    getLogger().info("Installed all hooks!");

    getLogger().info("Applying thickness...");
    float thickness = GET_CONFIG_VALUE(THICKNESS_VALUE, GetFloat());
    float decidedThickness = thickness > 1.0f || thickness < 0.0f ? 1.0f : thickness;
    saberScale.x = decidedThickness;
    saberScale.y = decidedThickness;
    saberScale.z = 1.0f;
}
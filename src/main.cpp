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

int shouldUpdate = 2;
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

MAKE_HOOK_FIND_CLASS_UNSAFE_STATIC(SceneManager_Internal_ActiveSceneChanged, "UnityEngine.SceneManagement", "SceneManager",
                                   "Internal_ActiveSceneChanged", void, Il2CppObject *previousActiveScene,
                                   Il2CppObject *newActiveScene) {
    SceneManager_Internal_ActiveSceneChanged(previousActiveScene, newActiveScene);
    shouldUpdate = 2;
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(Saber_ManualUpdate, "", "Saber", "ManualUpdate", void,
                                     Il2CppObject *self) {
    Saber_ManualUpdate(self);

    if (shouldUpdate) {
        auto transform = CRASH_UNLESS(il2cpp_utils::GetPropertyValue<Il2CppObject *>(self, "transform"));
        CRASH_UNLESS(il2cpp_utils::SetPropertyValue(transform, "localScale", saberScale));
        shouldUpdate--;
    }
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
    INSTALL_HOOK(getLogger(), SceneManager_Internal_ActiveSceneChanged);
    INSTALL_HOOK(getLogger(), Saber_ManualUpdate);
    getLogger().info("Installed all hooks!");

    getLogger().info("Applying thickness...");
    float thickness = GET_CONFIG_VALUE(THICKNESS_VALUE, GetFloat());
    float decidedThickness = thickness > 1.0f ? 1.0f : thickness;
    saberScale.x = decidedThickness;
    saberScale.y = decidedThickness;
    saberScale.z = 1.0f;
}
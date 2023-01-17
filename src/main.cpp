#include "main.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
// other config tools such as config-utils don't use this config, so it can be removed if those are in use
Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load();
    getLogger().info("Completed setup!");
}

struct Vector3 {
    float x, y, z;
};
DEFINE_IL2CPP_ARG_TYPE(Vector3, "UnityEngine", "Vector3");

int shouldUpdate = 2;

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
        auto localScale = CRASH_UNLESS(il2cpp_utils::GetPropertyValue<Vector3>(transform, "localScale"));
        localScale.x = 0.5f;
        localScale.y = 0.5f;
        CRASH_UNLESS(il2cpp_utils::SetPropertyValue(transform, "localScale", localScale));
        shouldUpdate--;
    }
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), SceneManager_Internal_ActiveSceneChanged);
    INSTALL_HOOK(getLogger(), Saber_ManualUpdate);
    getLogger().info("Installed all hooks!");
}
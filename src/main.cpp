#include "main.hpp"

#define THICKNESS_VALUE "thickness"

#define CONFIG_VALUE_EXISTS(value) getConfig().config.HasMember(value)
#define DEFINE_CONFIG_ALLOCATOR() rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator()
#define CONFIG_ALLOCATOR allocator
#define ADD_CONFIG_VALUE(value, setValue, allocator) getConfig().config.AddMember(value, rapidjson::Value(0).setValue, allocator)
#define WRITE_CONFIG() getConfig().Write()
#define GET_CONFIG_VALUE(value, getValue) getConfig().config[value].getValue

#define IS_MOD_LOADED(id) mods.find(id) != mods.end()

#define STRING(str) il2cpp_utils::newcsstr(str)

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
Vector3 fakeGlowScale;

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
#pragma endregion
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(SaberModelController_Init, "", "SaberModelController", "Init", void, Il2CppObject *self,
                                     Il2CppObject *parent, // UnityEngine.Transform
                                     Il2CppObject *saber // global::Saber
                                     ) {
    SaberModelController_Init(self, parent, saber);

    // Get Transform of SaberModelContainer(Clone)
    Il2CppObject *transform = CRASH_UNLESS(il2cpp_utils::GetPropertyValue(self, "transform"));
    static auto *findMethodInfo = CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(transform, "Find", 1));

    // Scale BasicSaber
    Il2CppObject *basicSaberTransform = CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe(transform, findMethodInfo, STRING("BasicSaber")));
    if (!basicSaberTransform) return; // Stop if nullptr
    CRASH_UNLESS(il2cpp_utils::SetPropertyValue(basicSaberTransform, "localScale", saberScale));

    // Scale FakeGlow0
    Il2CppObject *fakeGlow0Transform = CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe(transform, findMethodInfo, STRING("FakeGlow0")));
    if (!fakeGlow0Transform) return; // Stop if nullptr
    CRASH_UNLESS(il2cpp_utils::SetPropertyValue(fakeGlow0Transform, "localScale", fakeGlowScale));

    // Scale FakeGlow1
    Il2CppObject *fakeGlow1Transform = CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe(transform, findMethodInfo, STRING("FakeFlow1")));
    if (!fakeGlow1Transform) return; // Stop if nullptr
    CRASH_UNLESS(il2cpp_utils::SetPropertyValue(fakeGlow1Transform, "localScale", fakeGlowScale));
}

extern "C" void load() {
    il2cpp_functions::Init();

    auto mods = ::Modloader::getMods();

    if (IS_MOD_LOADED("ShortSaber") || IS_MOD_LOADED("thinsabers")) {
        getLogger().info("ShortSaber or ThinSabers is installed. Not continuing with hook installs.");
        return;
    }

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), SaberModelController_Init);
    getLogger().info("Installed all hooks!");

    getLogger().info("Applying thickness...");
    float thickness = GET_CONFIG_VALUE(THICKNESS_VALUE, GetFloat());
    [[maybe_unused]] float decidedThickness = thickness > 1.0f || thickness < 0.0f ? 1.0f : thickness;
    saberScale = {decidedThickness, decidedThickness, 1.0f};
    fakeGlowScale = {decidedThickness, 1.0f, decidedThickness};
}
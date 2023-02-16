#include "Config.hpp"
#include "main.hpp"

#define CONFIG_VALUE_EXISTS(value) getConfig().config.HasMember(value)
#define GET_CONFIG_ALLOCATOR getConfig().config.GetAllocator()

#define THICKNESS "thickness"
#define LENGTH "length"
#define LAW_ENFORCEMENT "law_enforcement"

namespace ThinSaberCore {
    Configuration& Config::getConfig() {
        static Configuration config(modInfo);
        return config;
    }

    void Config::loadConfig() {
        getConfig().Load();
    }

    void Config::setupConfig() {
        getConfig().Load();

        auto &allocator = GET_CONFIG_ALLOCATOR;

        if (!CONFIG_VALUE_EXISTS(THICKNESS)) {
            getConfig().config.AddMember(THICKNESS, rapidjson::Value(0).SetFloat(0.5f), allocator);
            getConfig().Write();
        }

        if (!CONFIG_VALUE_EXISTS(LENGTH)) {
            getConfig().config.AddMember(LENGTH, rapidjson::Value(0).SetFloat(1.0f), allocator);
            getConfig().Write();
        }

        if (!CONFIG_VALUE_EXISTS(LAW_ENFORCEMENT)) {
            getConfig().config.AddMember(LAW_ENFORCEMENT, rapidjson::Value(0).SetFloat(1.0f), allocator);
            getConfig().Write();
        }
    }

    float Config::getThickness() {
        return getConfig().config[THICKNESS].GetFloat();
    }

    void Config::setThickness(float value) {
        getConfig().config[THICKNESS].SetFloat(value);
    }

    float Config::getLength() {
        return getConfig().config[LENGTH].GetFloat();
    }

    void Config::setLength(float value) {
        getConfig().config[LENGTH].SetFloat(value);
    }

    bool Config::getLawEnforcement() {
        return getConfig().config[LAW_ENFORCEMENT].GetBool();
    }

    void Config::setLawEnforcement(bool value) {
        getConfig().config[LAW_ENFORCEMENT].SetBool(value);
    }
}

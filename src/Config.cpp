#include "Config.hpp"
#include "main.hpp"

Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}
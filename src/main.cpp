// Standard library headers
#include "logger.hpp"
#include "backup.hpp"
#include <fstream>
#include <filesystem>
#include <string>

// Third-party headers
#include "json.hpp"

// TO-DO: folders copied in one folder
// folder zipping
// deletes n + 1 backup that is oldest
namespace fs = std::filesystem;
using json = nlohmann::json;
using str = std::string;

constexpr const char* CONFIG_FILE = "config.json";
constexpr const char* SECTION_WORLDS = "worlds";
constexpr const char* SECTION_PATHS = "paths";

int main() {
    log(INFO, "==========================");
    log(INFO, "Starting world backup");
    log(INFO, "==========================");

    std::ifstream configFile(CONFIG_FILE);
    if (!configFile) {
        log(ERROR, "Failed to load config.json");
        return 1;
    }

    json config;
    configFile >> config;

    if (!config.contains(SECTION_WORLDS) || !config.contains(SECTION_PATHS)
        || !config[SECTION_PATHS].contains("source") || !config[SECTION_PATHS].contains("destination")) {
        log(ERROR, "Invalid config structure");
        return 1;
    }

    log(INFO, "Copying worlds");
    for (auto& [_, worldName] : config[SECTION_WORLDS].items()) {
        copyWorld(worldName.get<std::string>(), fs::path(config[SECTION_PATHS]["source"].get<str>()), fs::path(config[SECTION_PATHS]["destination"].get<str>()));
    }

    closeLog();
    return 0;
}

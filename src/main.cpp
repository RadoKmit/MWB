// Standard library headers
#include <fstream>
#include <filesystem>
#include <string>

// Third-party headers
#include "backup.hpp"
#include "backupRemoval.hpp"
#include "json.hpp"
#include "logger.hpp"
#include "timeInfo.hpp"

// TO-DO: folders copied in one folder
// folder zipping
// deletes n + 1 backup that is oldest
namespace fs = std::filesystem;
using json = nlohmann::json;
using str = std::string;

constexpr const char* CONFIG_FILE = "config.json";
constexpr const char* SECTION_WORLDS = "worlds";
constexpr const char* SECTION_PATHS = "paths";
constexpr const char* SAVED_BACKUPS = "backupsbackupsToKeep";

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

    log(INFO, "Creating folder");
    str folderName = GetDate() + "worldsBackup";
    fs::path backupFolderPath = config[SECTION_PATHS]["destination"] / fs::path(folderName);
    if(!fs::exists(backupFolderPath)){
        if(fs::create_directory(backupFolderPath)){
            log(INFO, "Folder created");
        } else {
            log(ERROR, "Failed to create folder");
            return 1;
        }
    }

    log(INFO, "Copying worlds");
    for (auto& [_, worldName] : config[SECTION_WORLDS].items()) {
        copyWorld(worldName.get<std::string>(), fs::path(config[SECTION_PATHS]["source"].get<str>()), backupFolderPath);
    }

    log(INFO, "Deleting excess backups in:" + config[SECTION_PATHS]["destination"].get<str>());
    if(!config.contains(SAVED_BACKUPS)){
        log(ERROR, "Backups amount not specified!");
    }
    removeBackups(fs::path(config[SECTION_PATHS]["destination"].get<str>()), config[SAVED_BACKUPS].get<int>());

    closeLog();
    return 0;
}

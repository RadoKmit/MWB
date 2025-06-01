// Standard library headers
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// Third-party headers
#include "json.hpp"

namespace fs = std::filesystem;
using str = std::string;
using json = nlohmann::json;

constexpr const char* CONFIG_FILE = "config.json";

std::string GetDate(){
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&now_time);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << local_time->tm_mday << "-" << std::setw(2) << local_time->tm_mon + 1 << "-" << local_time->tm_year + 1900;
    return oss.str();
}

fs::path BuildBackupPath(const str& basePath, const str& worldName) {
    return fs::path(basePath) / (GetDate() + "_" + worldName);
}

int copyWorld(const json& config, const str worldName){
    if (!config.contains("path") || !config["path"].contains("source") || !config["path"].contains("destination")) {
        std::cerr << "Invalid config format.\n";
        return 1;
    }

    fs::path source = fs::path(config["path"]["source"]) / worldName;
    str backupName = GetDate() + "_" + worldName;
    fs::path destination = BuildBackupPath(config["path"]["destination"], backupName);

    try {
        fs::copy(source, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        std::cout << "World copied from " << source << " to " << destination << std::endl;
    } catch (fs::filesystem_error& e){
        std::cerr << "Error copying file: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

// TODO: zip folder

int main() {
    std::ifstream configFile(CONFIG_FILE);
    if(!configFile){
        std::cerr << "Failed to load config.json L" << std::endl;
        return 1;
    }

    json config;
    configFile >> config;
    if (!config.contains("worlds")) {
        std::cerr << "Config missing 'worlds' section" << std::endl;
        return 1;
    }

    for (auto& [key, worldName] : config["worlds"].items()) {
        copyWorld(config, worldName.get<str>());
    }
    return 0;
}

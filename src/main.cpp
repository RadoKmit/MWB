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

enum LogLevel { INFO, WARNING, ERROR };

std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

str getLogFileName(){
    std::ostringstream logFileName;
    logFileName << getCurrentTime() << "log.txt";
    return logFileName.str();
}

std::ofstream logFile(getLogFileName());

void log(LogLevel level, const str& message){
    str prefix;
    switch(level){
        case INFO:    prefix = "[INFO] "; break;
        case WARNING: prefix = "[WARNING] "; break;
        case ERROR:   prefix = "[ERROR] "; break;
    }
    logFile << getCurrentTime() << " " << prefix << message << std::endl;
}

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
    fs::path source = fs::path(config["path"]["source"]) / worldName;
    fs::path destination = BuildBackupPath(config["path"]["destination"], worldName);
    std::ostringstream info;
    info << "Copying " << worldName << " in to " << destination;
    log(INFO, info.str());
    try {
        fs::copy(source, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        std::ostringstream info2;
        info2 << "world copied from " << source << " to " << destination;
        log(INFO, info2.str());
    } catch (fs::filesystem_error& e){
        std::ostringstream error;
        error << "Error copying files: " << e.what();
        log(ERROR, error.str());
        return 1;
    }
    return 0;
}

int main() {
    log(INFO, "==========================");
    log(INFO, "Starting world backup");
    log(INFO, "==========================");
    
    log(INFO, "Loading config.json");
    std::ifstream configFile(CONFIG_FILE);
    if(!configFile){
        log(ERROR, "Failed to load config.josn");
        return 1;
    }

    json config;
    configFile >> config;
    if (!config.contains("worlds")) {
        log(ERROR, "Config missing 'worlds' section");
        return 1;
    }

    if (!config.contains("path") || !config["path"].contains("source") || !config["path"].contains("destination")) {
        log(ERROR, "Config missing paths");
        return 1;
    }

    log(INFO, "Copying worlds");
    for (auto& [key, worldName] : config["worlds"].items()) {
        copyWorld(config, worldName.get<str>());
    }

    logFile.close();
    return 0;
}

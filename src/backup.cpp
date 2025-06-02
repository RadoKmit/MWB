#include "backup.hpp"
#include "logger.hpp"
#include <filesystem>
#include <sstream>
#include <iomanip>
#include <ctime>

namespace fs = std::filesystem;
using str = std::string;

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

int copyWorld(const std::string& worldName, const fs::path source, const fs::path destination){   
    log(INFO, "Copying " + worldName + " in to " + destination.string());

    try {
        fs::copy(source / worldName, BuildBackupPath(destination, worldName), fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        
        log(INFO, "world copied from " + source.string() + " to " + destination.string());
    } catch (fs::filesystem_error& e){
        log(ERROR, std::string("Error copying files: ") + e.what());
        return 1;
    }
    return 0;
}
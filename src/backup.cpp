#include <filesystem>

#include "backup.hpp"
#include "logger.hpp"
#include "timeInfo.hpp"

namespace fs = std::filesystem;
using str = std::string;

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
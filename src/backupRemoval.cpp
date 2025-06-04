#include <algorithm>
#include <iostream>
#include <filesystem>
#include <vector>

#include "logger.hpp"

namespace fs = std::filesystem;

void removeBackups(fs::path foldersPath, int backupsToKeep) {
    if (!fs::exists(foldersPath) || !fs::is_directory(foldersPath)) {
        log(ERROR, "Folder does not exist: " + foldersPath.string());
        return;
    }

    std::vector<fs::directory_entry> backup;
    for (const auto& entry : fs::directory_iterator(foldersPath)) {
        if (entry.is_directory()) {
            backup.push_back(entry);
        }
    }

    std::sort(backup.begin(), backup.end(),
        [](const fs::directory_entry& a, const fs::directory_entry& b) {
            return fs::last_write_time(a) > fs::last_write_time(b);
        });

    if (static_cast<int>(backup.size()) > backupsToKeep) {
        for (size_t i = backupsToKeep
        
        ; i < backup.size(); ++i) {
            log(INFO, "Deleting: " + backup[i].path().string());
            fs::remove_all(backup[i].path());
        }
    } else {
        log(INFO, "Number of backups is within limit (" + std::to_string(backup.size()) + " ≤ " + std::to_string(backupsToKeep
        
    ) + ")");
    }
}
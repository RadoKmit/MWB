#include <fstream>
#include <sstream>

#include "logger.hpp"
#include "timeInfo.hpp"

std::string getLogFileName() {
    std::ostringstream logFileName;
    logFileName << GetDate() << "_log.txt";
    return logFileName.str();
}

static std::ofstream logFile(getLogFileName());

void log(LogLevel level, const std::string& message) {
    std::string prefix;
    switch (level) {
        case INFO:    prefix = "[INFO] "; break;
        case WARNING: prefix = "[WARNING] "; break;
        case ERROR:   prefix = "[ERROR] "; break;
    }

    logFile << getCurrentTime() << " " << prefix << message << std::endl;
}

void closeLog() {
    logFile.close();
}

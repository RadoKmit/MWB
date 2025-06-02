#include "logger.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>

std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string getLogFileName() {
    std::ostringstream logFileName;
    logFileName << getCurrentTime() << "_log.txt";
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

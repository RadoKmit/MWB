#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "timeInfo.hpp"

std::string GetDate(){
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&now_time);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << local_time->tm_mday << "-" << std::setw(2) << local_time->tm_mon + 1 << "-" << local_time->tm_year + 1900;
    return oss.str();
}

std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

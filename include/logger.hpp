#pragma once

#include <string>

enum LogLevel { INFO, WARNING, ERROR };

void log(LogLevel level, const std::string& message);
void closeLog();
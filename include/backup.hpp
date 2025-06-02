#pragma once
#include <string>
#include <filesystem>
#include "json.hpp"

namespace fs = std::filesystem;

int copyWorld(const std::string& worldName, const fs::path source, const fs::path destination);
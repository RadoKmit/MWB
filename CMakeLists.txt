cmake_minimum_required(VERSION 3.16)
project(MWB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: show compile warnings
add_compile_options(-Wall -Wextra -Wpedantic)

# Add source files
add_executable(MWB
src/backup.cpp
src/backupRemoval.cpp
src/logger.cpp
src/main.cpp
src/timeInfo.cpp
)

# Include directories
target_include_directories(MWB PRIVATE include)

# Set installation target
install(TARGETS MWB DESTINATION bin)
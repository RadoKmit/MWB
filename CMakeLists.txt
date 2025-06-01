cmake_minimum_required(VERSION 3.16)
project(MWB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: show compile warnings
add_compile_options(-Wall -Wextra -Wpedantic)

# Include directories
include_directories(include)

# Add source files
add_executable(MWB
src/main.cpp
)
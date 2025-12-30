cmake_minimum_required(VERSION 3.30)
project(TEMPLATE LANGUAGES CXX)

# Initial Settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

# Shared Directories
include_directories(
    "include"
    "include/core"
    "libs"
)

# Main Program
add_executable(main
    src/main.cpp
)

# Name Changer
set_target_properties(main PROPERTIES OUTPUT_NAME "Center Texture")

target_link_libraries(main PRIVATE 
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
)
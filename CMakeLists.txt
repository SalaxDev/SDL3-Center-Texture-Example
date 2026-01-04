cmake_minimum_required(VERSION 3.10)
project(TEMPLATE LANGUAGES CXX)

# Initial Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

# Shared Directories
include_directories(
    "include"
    "include/core"
    "include/utils"
    "libs"
)

# Main Program
add_executable(main
    src/main.cpp
    src/core/wcWindow.cpp
    src/utils/msg_helper.cpp
)

# Name Changer
set_target_properties(main PROPERTIES OUTPUT_NAME "Center Texture")

target_link_libraries(main PRIVATE 
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
)

# Hides Console for windows users
if(WIN32)
    target_link_options(main PRIVATE
        -mwindows
    )
endif()

# Moving Data Directory to bin
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Data
        $<TARGET_FILE_DIR:main>/Data
    COMMENT "Copying Data directory to build folder"
)
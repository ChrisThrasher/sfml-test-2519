cmake_minimum_required(VERSION 3.16)
project(sfml-test-2519 LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(SFML_BUILD_NETWORK OFF)
set(SFML_BUILD_AUDIO OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/dogunbound/SFML.git
    GIT_TAG min_max_window_size)
FetchContent_MakeAvailable(SFML)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE SFML::Graphics)

add_custom_target(run COMMAND main WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

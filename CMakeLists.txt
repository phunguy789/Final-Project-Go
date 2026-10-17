cmake_minimum_required(VERSION 3.28)
project(GoGame LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)
add_executable(GoGame
    src/main.cpp
    src/Board.cpp
    src/Game.cpp
    src/AI.cpp
    src/UI.cpp
)
target_include_directories(GoGame PRIVATE include)
target_compile_features(GoGame PRIVATE cxx_std_17)
target_link_libraries(GoGame PRIVATE SFML::Graphics)
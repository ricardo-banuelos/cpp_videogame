cmake_minimum_required(VERSION 3.28)
project(cpp_videogame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- Fetch SFML ---
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# --- Collect all .cpp from src except main.cpp ---
file(GLOB LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# --- Your library (everything except main.cpp) ---
add_library(mylib ${LIB_SOURCES})
target_include_directories(mylib PUBLIC inc)
target_link_libraries(mylib PUBLIC SFML::Graphics)
target_compile_features(mylib PUBLIC cxx_std_17)

# --- Your executable (just main.cpp) ---
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE mylib)
target_compile_features(main PRIVATE cxx_std_17)

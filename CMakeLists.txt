cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Release)
project(Memoris)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(EXECUTABLE Memoris)

add_compile_options(-std=c++11 -Wall -Werror)

file(
    GLOB
    sources
    src/*
)

include_directories(includes)

add_executable(
    ${EXECUTABLE}
    src/main.cpp
    ${sources}
)

# bad I guess, only target one module, should point to all the modules...
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")
find_package(SFML 2.1 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE} ${SFML_LIBRARIES})

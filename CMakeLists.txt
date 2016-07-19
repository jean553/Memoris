cmake_minimum_required(VERSION 2.8)
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

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SFML 2.1 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE} ${SFML_LIBRARIES})

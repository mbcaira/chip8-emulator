cmake_minimum_required(VERSION 3.29)
project(chip8_emulator)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(SDL)

add_executable(chip8_emulator main.cpp
        chip8.h
        chip8.cc)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(chip8_emulator ${SDL2_LIBRARIES})


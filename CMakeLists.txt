cmake_minimum_required(VERSION 3.29)
project(chip8_emulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(chip8_emulator main.cpp
        chip8.h
        chip8.cc)

cmake_minimum_required(VERSION 3.23)

project(GameBoy_Emulator)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(GameBoy_Emulator src/gameboy_emulator.cpp)

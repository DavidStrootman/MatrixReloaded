cmake_minimum_required(VERSION 3.13)
project(MatrixReloaded)
set(CMAKE_CXX_STANDARD 17)

add_library(hwlib include/hwlib/library/hwlib.hpp include/hwlib/library/hwlib.cpp)
add_library(Reloaded lib/Reloaded/Reloaded.h lib/Reloaded/Reloaded.cpp)

set(SOURCE_FILES src/main.cpp)
add_executable(MatrixReloaded ${SOURCE_FILES})
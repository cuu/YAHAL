cmake_minimum_required(VERSION 3.16)

project(png2cpp CXX)

add_executable(png2cpp
    png2cpp.cpp
    lodepng.cpp
)

target_include_directories(png2cpp
    PRIVATE .
)

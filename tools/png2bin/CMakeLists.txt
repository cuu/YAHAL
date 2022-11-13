cmake_minimum_required(VERSION 3.16)

project(png2bin CXX)

add_executable(png2bin
    png2bin.cpp
    lodepng.cpp
)

target_include_directories(png2bin
    PRIVATE .
)

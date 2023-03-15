cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)

project(elf2uf2 CXX)

add_executable(elf2uf2
    main.cpp
)

include_directories(../../include/MCU/rp2040)

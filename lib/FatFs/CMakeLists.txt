cmake_minimum_required(VERSION 3.16)

project(FatFs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Ofast")

add_library(FatFs
    ff.cpp
    ffsystem.cpp
    ffunicode.cpp
)

target_include_directories(FatFs
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${YAHAL_DIR}/include/interface
)

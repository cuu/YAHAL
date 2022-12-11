cmake_minimum_required(VERSION 3.16)

project(mad)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Ofast")

add_library(mad
    bit.c
    fixed.c
    huffman.c
    layer3.c
    synth.c
    version.c
    decoder.c
    frame.c
    layer12.c
    stream.c
    timer.c
)

target_include_directories(mad
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

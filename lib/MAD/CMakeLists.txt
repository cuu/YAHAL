cmake_minimum_required(VERSION 3.16)

project(MAD_${PROJECT_NAME})

add_compile_options(-Ofast)
add_compile_options(-Wno-stringop-overflow)

add_library(${PROJECT_NAME}
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

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

cmake_minimum_required(VERSION 3.16)

set(MAD_TARGET MAD_${PROJECT_NAME})

add_library(${MAD_TARGET}
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

target_compile_options(${MAD_TARGET}
        PRIVATE -Ofast -Wno-stringop-overflow)

target_include_directories(${MAD_TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

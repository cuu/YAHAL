cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE DSP_SRC  Source/*.c Source/*.S)

add_library(ARM_DSP
    ${DSP_SRC}
)

target_include_directories(ARM_DSP PUBLIC
    Include
    ../../../../include/platform/msp432/CMSIS
)


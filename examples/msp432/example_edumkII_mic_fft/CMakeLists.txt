cmake_minimum_required(VERSION 3.16)

#set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(mic_fft C CXX ASM)

# Pull in YAHAL as subdirectory
yahal_add_me()

add_executable(mic_fft
    main.cpp
    startup_msp432p401r_gcc.c
    system_msp432p401r.c
)
target_link_libraries(mic_fft YAHAL ARM_DSP)

yahal_add_custom_targets(mic_fft)
yahal_add_extra_outputs(mic_fft)


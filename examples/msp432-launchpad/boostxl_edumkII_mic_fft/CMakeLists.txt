cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Place each function or data item into its own section in the output file.
# The linker can perform optimizations to improve locality of reference in the instruction space.
# This leads to smaller executables (after stripping).
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(boostxl_edumkII_mic_fft)

add_executable(boostxl_edumkII_mic_fft
    boostxl_edumkII_mic_fft.cpp
)

# Add YAHAL, uGUI and ARM DSP libraries
yahal_add_me(boostxl_edumkII_mic_fft)
yahal_add_library(boostxl_edumkII_mic_fft uGUI)
yahal_add_library(boostxl_edumkII_mic_fft CMSISDSP)

yahal_add_custom_targets(boostxl_edumkII_mic_fft)
yahal_add_extra_outputs(boostxl_edumkII_mic_fft)

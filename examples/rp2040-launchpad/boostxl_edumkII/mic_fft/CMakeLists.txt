cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")
set(YAHAL_OPT_FLAGS -Ofast)

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(mic_fft)

add_executable(mic_fft
    mic_fft.cpp
)

# Add YAHAL, uGUI and ARM DSP libraries
yahal_add_me(mic_fft)
yahal_add_library(mic_fft uGUI)
yahal_add_library(mic_fft CMSISDSP)

yahal_add_custom_targets(mic_fft)
yahal_add_extra_outputs(mic_fft)

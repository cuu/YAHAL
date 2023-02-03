cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(edumkII_mic_fft)

add_executable(edumkII_mic_fft
    edumkII_mic_fft.cpp
)

# Add YAHAL, uGUI and ARM DSP libraries
yahal_add_me(edumkII_mic_fft)
yahal_add_library(edumkII_mic_fft uGUI)
yahal_add_library(edumkII_mic_fft CMSISDSP)

yahal_add_custom_targets(edumkII_mic_fft)
yahal_add_extra_outputs(edumkII_mic_fft)

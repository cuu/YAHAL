cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(boostxl_audio_sin_wave)

add_executable(boostxl_audio_sin_wave
    boostxl_audio_sin_wave.cpp
    audio_output.cpp
)

# Add YAHAL
yahal_add_me(boostxl_audio_sin_wave)

yahal_add_custom_targets(boostxl_audio_sin_wave)
yahal_add_extra_outputs(boostxl_audio_sin_wave)


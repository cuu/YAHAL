cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(boostxl_audio_mp3_bird_sound)

add_executable(boostxl_audio_mp3_bird_sound
    gen/birds.cpp
)

add_subdirectory(src)

# Add YAHAL and MAD libraries
yahal_add_me(boostxl_audio_mp3_bird_sound)
yahal_add_library(boostxl_audio_mp3_bird_sound MAD)

# Generate cpp-file from mp3 file
file_to_cpp(boostxl_audio_mp3_bird_sound
                mp3/birds.mp3
    OUTPUT_FILE gen/birds.cpp
)

yahal_add_custom_targets(boostxl_audio_mp3_bird_sound)
yahal_add_extra_outputs(boostxl_audio_mp3_bird_sound)


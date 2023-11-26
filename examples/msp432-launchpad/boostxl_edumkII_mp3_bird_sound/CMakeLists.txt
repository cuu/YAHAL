cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(boostxl_edumkII_mp3_bird_sound)

add_executable(boostxl_edumkII_mp3_bird_sound
    gen/birds.cpp
)

add_subdirectory(src)

# Add YAHAL and MAD libraries
yahal_add_me(boostxl_edumkII_mp3_bird_sound)
yahal_add_library(boostxl_edumkII_mp3_bird_sound MAD)

# Generate cpp-file from mp3 file
file_to_cpp(boostxl_edumkII_mp3_bird_sound
    mp3/birds.mp3
    OUTPUT_DIR gen
)

yahal_add_custom_targets(boostxl_edumkII_mp3_bird_sound)
yahal_add_extra_outputs(boostxl_edumkII_mp3_bird_sound)

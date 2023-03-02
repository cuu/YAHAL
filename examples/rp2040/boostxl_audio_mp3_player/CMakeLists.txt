cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(boostxl_audio_mp3_player)

add_executable(boostxl_audio_mp3_player)
add_subdirectory(src)

# Add YAHAL, MAD and FatFs libraries
yahal_add_me(boostxl_audio_mp3_player)
yahal_add_library(boostxl_audio_mp3_player MAD)
yahal_add_library(boostxl_audio_mp3_player FatFs)

# generate the PIO header file
generate_pio_header(boostxl_audio_mp3_player
                    ${CMAKE_CURRENT_LIST_DIR}/pio/dac8311.pio
                    OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/pio)

yahal_add_custom_targets(boostxl_audio_mp3_player)
yahal_add_extra_outputs(boostxl_audio_mp3_player)


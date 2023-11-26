cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(mp3_player)

add_executable(mp3_player
    mp3_player.cpp
    sd_reader_task.cpp
    mp3_decoder_task.cpp
)

# Add YAHAL, MAD and FatFs libraries
yahal_add_me(mp3_player)
yahal_add_library(mp3_player MAD)
yahal_add_library(mp3_player FatFs)

yahal_add_custom_targets(mp3_player)
yahal_add_extra_outputs(mp3_player)

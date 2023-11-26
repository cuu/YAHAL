cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(mp3_song_edu)

add_executable(mp3_song_edu
    mp3_song.cpp
    mp3_decoder_task.cpp
    gen/song.cpp
)

# Add YAHAL and MAD libraries
yahal_add_me(mp3_song_edu)
yahal_add_library(mp3_song_edu MAD)

# Generate cpp-file from mp3 file
file_to_cpp(mp3_song_edu
    mp3/song.mp3
    OUTPUT_DIR gen
)

yahal_add_custom_targets(mp3_song_edu)
yahal_add_extra_outputs(mp3_song_edu)

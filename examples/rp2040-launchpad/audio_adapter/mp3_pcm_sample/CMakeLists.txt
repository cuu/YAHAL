cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(mp3_pcm_sample)

add_executable(mp3_pcm_sample
    mp3_pcm_sample.cpp
    gen/surprise.cpp
)

# Add YAHAL and MAD libraries
yahal_add_me(mp3_pcm_sample)

# Generate cpp-file from mp3 file
mp3pcm_to_cpp(mp3_pcm_sample
    mp3/surprise.mp3
    MODE left
    OUTPUT_DIR gen
)

yahal_add_custom_targets(mp3_pcm_sample)
yahal_add_extra_outputs(mp3_pcm_sample)

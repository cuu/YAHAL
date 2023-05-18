cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(web_radio_msp432)

add_compile_options(-Ofast)

add_executable(web_radio_msp432
    web_radio_msp432.cpp
    audio_output.cpp
    mp3_decoder_task.cpp
    stream_reader_task.cpp
    WifiTick.cpp
)

# Add YAHAL and MAD libraries
yahal_add_me(web_radio_msp432)
yahal_add_library(web_radio_msp432 MAD)

yahal_add_custom_targets(web_radio_msp432)
yahal_add_extra_outputs(web_radio_msp432)


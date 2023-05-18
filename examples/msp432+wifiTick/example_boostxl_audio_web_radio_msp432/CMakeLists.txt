cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(web_radio)

add_compile_options(-Ofast)

add_executable(web_radio
    audio_output.cpp
    main.cpp
    mp3_decoder_task.cpp
    stream_reader_task.cpp
    WifiTick.cpp
)

# Add YAHAL and MAD libraries
yahal_add_me(web_radio)
yahal_add_library(web_radio MAD)

yahal_add_custom_targets(web_radio)
yahal_add_extra_outputs(web_radio)


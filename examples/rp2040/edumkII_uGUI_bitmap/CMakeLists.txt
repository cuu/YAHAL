cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(uGUI_bitmap)

add_executable(uGUI_bitmap
    main.cpp
    gen/angry-bird.cpp
)

# Add YAHAL
yahal_add_me(uGUI_bitmap)

# Add the uGUI library
yahal_add_library(uGUI_bitmap uGUI)

# Generate cpp-file from png
png_to_cpp(uGUI_bitmap
    png/angry-bird.png
    BG_COLOR    0x808000 
    OUTPUT_FILE gen/angry-bird.cpp)

yahal_add_custom_targets(uGUI_bitmap)
yahal_add_extra_outputs(uGUI_bitmap)


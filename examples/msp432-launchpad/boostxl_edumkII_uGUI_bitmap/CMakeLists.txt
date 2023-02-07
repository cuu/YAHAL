cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(boostxl_edumkII_uGUI_bitmap)

add_executable(boostxl_edumkII_uGUI_bitmap
    boostxl_edumkII_uGUI_bitmap.cpp
    gen/angry-bird.cpp
)

# Add YAHAL
yahal_add_me(boostxl_edumkII_uGUI_bitmap)

# Add the uGUI library
yahal_add_library(boostxl_edumkII_uGUI_bitmap uGUI)

# Generate cpp-file from png
png_to_cpp(boostxl_edumkII_uGUI_bitmap
           png/angry-bird.png 
           BG_COLOR    0x808000 
           OUTPUT_FILE gen/angry-bird.cpp)

yahal_add_custom_targets(boostxl_edumkII_uGUI_bitmap)
yahal_add_extra_outputs(boostxl_edumkII_uGUI_bitmap)

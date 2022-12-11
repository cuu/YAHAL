cmake_minimum_required(VERSION 3.16)

#set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")
#set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(uGUI_bitmap)

add_executable(uGUI_bitmap
    main.cpp
    angry-bird.cpp
)

# Add YAHAL
yahal_add_me(uGUI_bitmap)

# Add the uGUI library
yahal_add_library(uGUI_bitmap uGUI)

# Generate cpp-file from png
png_to_cpp(uGUI_bitmap angry-bird.png 0x008000)

yahal_add_custom_targets(uGUI_bitmap)
yahal_add_extra_outputs(uGUI_bitmap)


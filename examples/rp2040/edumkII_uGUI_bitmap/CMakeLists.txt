cmake_minimum_required(VERSION 3.16)

#set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
#set(YAHAL_BOARD "rp2040-launchpad")
#set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(uGUI_bitmap C CXX ASM)

# Pull in YAHAL
yahal_add_me()

add_executable(uGUI_bitmap
    main.cpp
    angry-bird.cpp
)

# Generate cpp-file from png
png_to_cpp(uGUI_bitmap angry-bird.png 0x40a040)

target_link_libraries(uGUI_bitmap YAHAL)

yahal_add_custom_targets(uGUI_bitmap)
yahal_add_extra_outputs(uGUI_bitmap)


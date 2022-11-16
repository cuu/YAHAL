cmake_minimum_required(VERSION 3.16)

#set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(edumkII_uGUI_bitmap C CXX ASM)

# Pull in YAHAL as subdirectory
yahal_add_me()

add_executable(edumkII_uGUI_bitmap
    main.cpp
    angry-bird.cpp
)

# Generate cpp-file from png
png_to_cpp(edumkII_uGUI_bitmap angry-bird.png 0x002040)

target_link_libraries(edumkII_uGUI_bitmap YAHAL)

yahal_add_custom_targets(edumkII_uGUI_bitmap)
yahal_add_extra_outputs(edumkII_uGUI_bitmap)


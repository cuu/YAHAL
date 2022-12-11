cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(blink_simple C CXX ASM)

add_executable(blink_simple
    blink_simple.cpp
)

# Add YAHAL to target
yahal_add_me(blink_simple)

yahal_add_custom_targets(blink_simple)
yahal_add_extra_outputs(blink_simple)


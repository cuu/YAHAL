cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2350-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(blink_multicore)

add_executable(blink_multicore
    blink_multicore.cpp
)

# Add YAHAL to target
yahal_add_me(blink_multicore)

yahal_add_custom_targets(blink_multicore)
yahal_add_extra_outputs(blink_multicore)


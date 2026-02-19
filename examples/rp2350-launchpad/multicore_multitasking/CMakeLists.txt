cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2350-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(multicore_multitasking)

add_executable(multicore_multitasking
    multicore_multitasking.cpp
)

# Add YAHAL to target
yahal_add_me(multicore_multitasking)

yahal_add_custom_targets(multicore_multitasking)
yahal_add_extra_outputs(multicore_multitasking)


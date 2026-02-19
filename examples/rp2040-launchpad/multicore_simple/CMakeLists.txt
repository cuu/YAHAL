cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(multicore_simple)

add_executable(multicore_simple
    multicore_simple.cpp
)

# Add YAHAL to target
yahal_add_me(multicore_simple)

yahal_add_custom_targets(multicore_simple)
yahal_add_extra_outputs(multicore_simple)


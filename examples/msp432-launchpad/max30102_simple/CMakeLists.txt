cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(max30102_simple)

add_executable(max30102_simple
    max30102_simple.cpp
)

# Add YAHAL
yahal_add_me(max30102_simple)

yahal_add_custom_targets(max30102_simple)
yahal_add_extra_outputs(max30102_simple)

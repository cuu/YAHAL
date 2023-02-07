cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(multitasking_simple)

add_executable(multitasking_simple
    multitasking_simple.cpp
    OS.cpp
)

# Add YAHAL
yahal_add_me(multitasking_simple)

yahal_add_custom_targets(multitasking_simple)
yahal_add_extra_outputs(multitasking_simple)

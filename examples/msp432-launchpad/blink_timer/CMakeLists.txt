cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(blink_timer)

add_executable(blink_timer
    blink_timer.cpp
)

# Add YAHAL
yahal_add_me(blink_timer)

yahal_add_custom_targets(blink_timer)
yahal_add_extra_outputs(blink_timer)

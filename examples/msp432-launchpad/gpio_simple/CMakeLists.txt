cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(gpio_simple)

add_executable(gpio_simple
    gpio_simple.cpp
)

# Add YAHAL
yahal_add_me(gpio_simple)

yahal_add_custom_targets(gpio_simple)
yahal_add_extra_outputs(gpio_simple)

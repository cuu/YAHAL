cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(gpio_interrupt)

add_executable(gpio_interrupt
    gpio_interrupt.cpp
)

# Add YAHAL
yahal_add_me(gpio_interrupt)

yahal_add_custom_targets(gpio_interrupt)
yahal_add_extra_outputs(gpio_interrupt)

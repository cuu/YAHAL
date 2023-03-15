cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

# Set clocks to MCU defaults (all 3MHz)
add_compile_options(-DMCLK_SELECT=DCO  -DMCLK_DIV=DIV1)
add_compile_options(-DSMCLK_SELECT=DCO -DSMCLK_DIV=DIV1)

project(blink_register)

add_executable(blink_register
    blink_register.cpp
)

# Add YAHAL
yahal_add_me(blink_register)

yahal_add_custom_targets(blink_register)
yahal_add_extra_outputs(blink_register)

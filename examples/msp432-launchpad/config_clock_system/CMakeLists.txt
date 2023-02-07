cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

# Set clocks to MCU defaults (all 3MHz)
#add_compile_options(-DMCLK_SELECT=DCO  -DMCLK_DIV=DIV1)
#add_compile_options(-DSMCLK_SELECT=DCO -DSMCLK_DIV=DIV1)

project(config_clock_system)

add_executable(config_clock_system
    config_clock_system.cpp
)

# Add YAHAL
yahal_add_me(config_clock_system)

yahal_add_custom_targets(config_clock_system)
yahal_add_extra_outputs(config_clock_system)

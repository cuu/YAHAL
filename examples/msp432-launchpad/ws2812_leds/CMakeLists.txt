cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(ws2812_leds)

add_executable(ws2812_leds
    ws2812_leds.cpp
)

# Add YAHAL
yahal_add_me(ws2812_leds)

yahal_add_custom_targets(ws2812_leds)
yahal_add_extra_outputs(ws2812_leds)

cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(ws2812_test)

add_executable(ws2812_test
    ws2812_test.cpp
)

# Add YAHAL to target
yahal_add_me(ws2812_test)

yahal_add_custom_targets(ws2812_test)
yahal_add_extra_outputs(ws2812_test)

cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2350-launchpad")

set(YAHAL_USE_NANO_SPECS 0)

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(battery_status C CXX ASM)

add_executable(battery_status
    battery_status.cpp
)

# Add YAHAL to target
yahal_add_me(battery_status)
yahal_add_library(battery_status uGUI)

yahal_add_custom_targets(battery_status)
yahal_add_extra_outputs(battery_status)


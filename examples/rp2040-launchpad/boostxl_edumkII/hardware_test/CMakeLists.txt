cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(hardware_test)

add_executable(hardware_test
    hardware_test.cpp
    HW.cpp
)

# Add YAHAL and uGUI
yahal_add_me(hardware_test)
yahal_add_library(hardware_test uGUI)

yahal_add_custom_targets(hardware_test)
yahal_add_extra_outputs(hardware_test)

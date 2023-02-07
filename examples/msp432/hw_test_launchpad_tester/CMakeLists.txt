cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(hw_test_launchpad_tester)

add_executable(hw_test_launchpad_tester
    hw_test_launchpad_tester.cpp
)

# Add YAHAL
yahal_add_me(hw_test_launchpad_tester)

yahal_add_custom_targets(hw_test_launchpad_tester)
yahal_add_extra_outputs(hw_test_launchpad_tester)

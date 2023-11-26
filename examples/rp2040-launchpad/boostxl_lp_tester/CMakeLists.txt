cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(lp_tester)

add_executable(lp_tester
    lp_tester.cpp
)

# Add YAHAL
yahal_add_me(lp_tester)

yahal_add_custom_targets(lp_tester)
yahal_add_extra_outputs(lp_tester)

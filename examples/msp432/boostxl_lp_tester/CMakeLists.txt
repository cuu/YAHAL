cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(boostxl_lp_tester)

add_executable(boostxl_lp_tester
    boostxl_lp_tester.cpp
)

# Add YAHAL
yahal_add_me(boostxl_lp_tester)

yahal_add_custom_targets(boostxl_lp_tester)
yahal_add_extra_outputs(boostxl_lp_tester)

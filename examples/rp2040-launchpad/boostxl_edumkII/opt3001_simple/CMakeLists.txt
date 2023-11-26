cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(opt3001_simple)

add_executable(opt3001_simple
    opt3001_simple.cpp
)

# Add YAHAL
yahal_add_me(opt3001_simple)

yahal_add_custom_targets(opt3001_simple)
yahal_add_extra_outputs(opt3001_simple)

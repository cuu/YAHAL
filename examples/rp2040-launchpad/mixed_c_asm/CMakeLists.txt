cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(mixed_c_asm)

add_executable(mixed_c_asm
    mixed_c_asm.cpp
)

# Add YAHAL
yahal_add_me(mixed_c_asm)

yahal_add_custom_targets(mixed_c_asm)
yahal_add_extra_outputs(mixed_c_asm)

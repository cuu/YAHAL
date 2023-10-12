cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(blink_asm C CXX ASM)

add_executable(blink_asm
    blink_asm.S
)

# Add YAHAL
yahal_add_me(blink_asm)

yahal_add_custom_targets(blink_asm)
yahal_add_extra_outputs(blink_asm)

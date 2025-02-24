cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2350-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

project(multitasking_simple C CXX ASM)

add_executable(multitasking_simple
    multitasking_simple.cpp
    OS.cpp
)

# Add YAHAL to target
yahal_add_me(multitasking_simple)

target_include_directories(multitasking_simple
    PRIVATE .
)

yahal_add_custom_targets(multitasking_simple)
yahal_add_extra_outputs(multitasking_simple)


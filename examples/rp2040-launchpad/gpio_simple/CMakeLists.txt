cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(gpio_simple C CXX ASM)

add_executable(gpio_simple
    gpio_simple.cpp
)

# Add YAHAL to target
yahal_add_me(gpio_simple)

yahal_add_custom_targets(gpio_simple)
yahal_add_extra_outputs(gpio_simple)


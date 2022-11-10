cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(gpio_interrupt C CXX ASM)

# Pull in YAHAL as subdirectory
yahal_add_me()

add_executable(gpio_interrupt
    gpio_interrupt.cpp
)
target_link_libraries(gpio_interrupt YAHAL)

yahal_add_custom_targets(gpio_interrupt)
yahal_add_extra_outputs(gpio_interrupt)


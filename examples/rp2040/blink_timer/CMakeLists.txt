cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(blink_timer C CXX ASM)

# Pull in YAHAL as subdirectory
yahal_add_me()

add_executable(blink_timer
    blink_timer.cpp
)
target_link_libraries(blink_timer YAHAL)

yahal_add_custom_targets(blink_timer)
yahal_add_extra_outputs(blink_timer)


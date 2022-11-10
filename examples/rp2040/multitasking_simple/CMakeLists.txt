cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(multitasking_simple C CXX ASM)

# Pull in YAHAL as subdirectory
yahal_add_me()

add_executable(multitasking_simple
    multitasking_simple.cpp
    OS.cpp
)

target_include_directories(multitasking_simple
    PRIVATE .
)

target_link_libraries(multitasking_simple YAHAL)

yahal_add_custom_targets(multitasking_simple)
yahal_add_extra_outputs(multitasking_simple)


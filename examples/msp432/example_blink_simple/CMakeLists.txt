cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD  "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(example_blink_simple C CXX ASM)

# Pull in YAHAL as subdirectory
YAHAL_init()

add_executable(blink
    main.cpp
    startup_msp432p401r_gcc.c
    system_msp432p401r.c
)

target_link_libraries(blink YAHAL)


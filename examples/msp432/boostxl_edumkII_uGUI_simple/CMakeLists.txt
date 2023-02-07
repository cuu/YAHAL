cmake_minimum_required(VERSION 3.16)

#set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(example_edumkII_uGUI_simple C CXX ASM)

# Pull in YAHAL as subdirectory
yahal_add_me()

add_executable(uGUI_simple
    main.cpp
    startup_msp432p401r_gcc.c
    system_msp432p401r.c
)
target_link_libraries(uGUI_simple YAHAL)

yahal_add_custom_targets(uGUI_simple)
yahal_add_extra_outputs(uGUI_simple)



cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(sd_card C CXX ASM)

# Pull in YAHAL as subdirectory
yahal_add_me()

add_executable(sd_card
    main.cpp
)

target_link_libraries(sd_card YAHAL)

yahal_add_custom_targets(sd_card)
yahal_add_extra_outputs(sd_card)


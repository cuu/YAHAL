cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(sd_card)

add_executable(sd_card
    main.cpp
)

# Add YAHAL and FatFS libraries
yahal_add_me(sd_card)
yahal_add_library(sd_card FatFs)

yahal_add_custom_targets(sd_card)
yahal_add_extra_outputs(sd_card)


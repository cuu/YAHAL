cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(retro_PDP8_Focal)

add_executable(retro_PDP8_Focal)
add_subdirectory(src)

# Add YAHAL, MAD and FatFs libraries
yahal_add_me(retro_PDP8_Focal)

yahal_add_custom_targets(retro_PDP8_Focal)
yahal_add_extra_outputs(retro_PDP8_Focal)

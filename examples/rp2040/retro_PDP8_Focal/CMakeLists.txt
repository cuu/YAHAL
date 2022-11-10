cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(retro_PDP8_Focal C CXX ASM)

# Pull in YAHAL as subdirectory
yahal_add_me()

add_executable(retro_PDP8_Focal)

add_subdirectory(src)

target_link_libraries(retro_PDP8_Focal YAHAL)

yahal_add_custom_targets(retro_PDP8_Focal)
yahal_add_extra_outputs(retro_PDP8_Focal)


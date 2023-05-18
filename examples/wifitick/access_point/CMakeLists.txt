cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "wifitick")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(access_point)

add_executable(access_point
    access_point.cpp
)

# Add YAHAL library
yahal_add_me(access_point)

# Add Arduino libraries
target_link_arduino_libraries(access_point PRIVATE core)

# This upload target
target_enable_arduino_upload(access_point)


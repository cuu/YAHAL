cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "wifitick")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(WebServer)

add_executable(WebServer
    WebServer.cpp
)

# Add Arduino libraries
target_link_arduino_libraries(WebServer PRIVATE core)

# This upload target
target_enable_arduino_upload(WebServer)


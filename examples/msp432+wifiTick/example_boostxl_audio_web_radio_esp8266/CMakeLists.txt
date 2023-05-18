cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "wifitick")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(WebRadio)

add_executable(WebRadio
    i2c_device.cpp
    main.cpp
    WEB_Radio.cpp
)
# Add YAHAL library
yahal_add_me(WebRadio)

# Add Arduino libraries
target_link_arduino_libraries(WebRadio PRIVATE core)

# This upload target
target_enable_arduino_upload(WebRadio)


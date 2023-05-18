cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "wifitick")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(web_radio_esp8266)

add_executable(web_radio_esp8266
    web_radio_esp8266.cpp
    i2c_device.cpp
    WEB_Radio.cpp
)
# Add YAHAL library
yahal_add_me(web_radio_esp8266)

# Add Arduino libraries
target_link_arduino_libraries(web_radio_esp8266 PRIVATE core)

# This upload target
target_enable_arduino_upload(web_radio_esp8266)


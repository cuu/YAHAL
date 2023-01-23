cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(led_ws2812)

add_executable(led_ws2812
    led_ws2812.cpp
)

# Add YAHAL to target
yahal_add_me(led_ws2812)

# generate the header file into the source tree as it is included in the RP2040 datasheet
generate_pio_header(led_ws2812 
                    ${CMAKE_CURRENT_LIST_DIR}/pio/led_ws2812.pio
                    OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/pio)

yahal_add_custom_targets(led_ws2812)
yahal_add_extra_outputs(led_ws2812)

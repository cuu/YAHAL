cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2350-launchpad")
# set(YAHAL_OPT_FLAGS -Ofast)
# set(CMAKE_BUILD_TYPE RELEASE)

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(usb_acm_dev_pdp8)

add_executable(usb_acm_dev_pdp8
        usb_acm_dev_pdp8.cpp
        usb_uart.cpp
)
add_subdirectory(src)

# Add YAHAL to target
yahal_add_me(usb_acm_dev_pdp8)
yahal_add_library(usb_acm_dev_pdp8 tinyUSB++)

yahal_add_custom_targets(usb_acm_dev_pdp8)
yahal_add_extra_outputs(usb_acm_dev_pdp8)


cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")
# set(YAHAL_OPT_FLAGS -Ofast)

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(usb_dev_lowlevel)

add_executable(usb_dev_lowlevel
    main.cpp
)
 
# Add YAHAL to target
yahal_add_me(usb_dev_lowlevel)
yahal_add_library(usb_dev_lowlevel tinyUSB++)

yahal_add_custom_targets(usb_dev_lowlevel)
yahal_add_extra_outputs(usb_dev_lowlevel)


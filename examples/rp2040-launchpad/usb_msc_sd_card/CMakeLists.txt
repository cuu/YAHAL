cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")
set(YAHAL_OPT_FLAGS -Ofast)
# set(CMAKE_BUILD_TYPE RELEASE)

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(usb_msc_sd_card)

add_executable(usb_msc_sd_card
    usb_msc_sd_card.cpp
)
 
# Add YAHAL to target
yahal_add_me(usb_msc_sd_card)
yahal_add_library(usb_msc_sd_card tinyUSB++)

yahal_add_custom_targets(usb_msc_sd_card)
yahal_add_extra_outputs(usb_msc_sd_card)


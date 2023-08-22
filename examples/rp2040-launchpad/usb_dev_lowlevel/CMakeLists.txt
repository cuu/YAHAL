cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")
set(YAHAL_OPT_FLAGS -Ofast)

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(usb_dev_lowlevel)

add_executable(usb_dev_lowlevel
#     dev_lowlevel.cpp
    usb_strings.cpp
    usb_interface.cpp
    usb_configuration.cpp
    usb_device.cpp
    usb_dcd_rp2040.cpp
    usb_endpoint_rp2040.cpp
    usb_device_controller.cpp
    usb_interface_association.cpp
    main.cpp
    usb_fd_header.cpp
    usb_fd_call_mgmt.cpp
    usb_fd_acm.cpp
    usb_fd_acm.h
    usb_fd_union.cpp
    usb_fd_union.h
    usb_dcd_rp2040.cpp
    usb_dcd_rp2040.h
    usb_endpoint_base.cpp
    usb_cdc_acm_device.cpp
)
 
# Add YAHAL to target
yahal_add_me(usb_dev_lowlevel)

yahal_add_custom_targets(usb_dev_lowlevel)
yahal_add_extra_outputs(usb_dev_lowlevel)


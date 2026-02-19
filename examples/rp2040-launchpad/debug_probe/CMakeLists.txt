cmake_minimum_required(VERSION 3.20)

# Set the target board
set(YAHAL_BOARD "rp2xxx-launchpad-probe")
#set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(debug_probe)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Ofast")

add_executable(debug_probe
        debug_probe.cpp
)

target_compile_options    (debug_probe PRIVATE -Ofast)
target_include_directories(debug_probe PRIVATE .)

# Add YAHAL and libs to target
yahal_add_me(debug_probe)
yahal_add_library(debug_probe tinyUSB++)
yahal_add_library(debug_probe openDAP++)

yahal_add_custom_targets(debug_probe)
yahal_add_extra_outputs(debug_probe)

add_subdirectory(config)
add_subdirectory(led_interface)
add_subdirectory(usb_dap_device)
add_subdirectory(usb_uart_device)

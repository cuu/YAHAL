cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2350-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(uart_rp2350)

add_executable(uart_rp2350
    uart_rp2350.cpp
)

# Add YAHAL library
yahal_add_me(uart_rp2350)

yahal_add_custom_targets(uart_rp2350)
yahal_add_extra_outputs(uart_rp2350)


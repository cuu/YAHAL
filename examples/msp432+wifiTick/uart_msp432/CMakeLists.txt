cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(uart_msp432)

add_executable(uart_msp432
    uart_msp432.cpp
)

# Add YAHAL library
yahal_add_me(uart_msp432)

yahal_add_custom_targets(uart_msp432)
yahal_add_extra_outputs(uart_msp432)


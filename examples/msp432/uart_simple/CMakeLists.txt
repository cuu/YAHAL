cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(uart_simple)

add_executable(uart_simple
    uart_simple.cpp
)

# Add YAHAL
yahal_add_me(uart_simple)

yahal_add_custom_targets(uart_simple)
yahal_add_extra_outputs(uart_simple)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(uart_interrupt C CXX ASM)

# Pull in YAHAL as subdirectory
yahal_add_me()

add_executable(uart_interrupt
    uart_interrupt.cpp
)
target_link_libraries(uart_interrupt YAHAL)

yahal_add_custom_targets(uart_interrupt)
yahal_add_extra_outputs(uart_interrupt)


cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(spi_rp2040)

add_executable(spi_rp2040
    spi_rp2040.cpp
)

# Add YAHAL library
yahal_add_me(spi_rp2040)

yahal_add_custom_targets(spi_rp2040)
yahal_add_extra_outputs(spi_rp2040)

cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(adc_simple)

add_executable(adc_simple
    adc_simple.cpp
)

# Add YAHAL
yahal_add_me(adc_simple)

yahal_add_custom_targets(adc_simple)
yahal_add_extra_outputs(adc_simple)

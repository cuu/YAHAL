cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(edumkII_adc_simple)

add_executable(edumkII_adc_simple
    edumkII_adc_simple.cpp
)

# Add YAHAL
yahal_add_me(edumkII_adc_simple)

yahal_add_custom_targets(edumkII_adc_simple)
yahal_add_extra_outputs(edumkII_adc_simple)

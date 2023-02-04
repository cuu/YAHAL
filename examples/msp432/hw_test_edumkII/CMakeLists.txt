cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Set all clocks to maximum frequency
add_compile_options(-DMCLK_SELECT=HFXT  -DMCLK_DIV=DIV1)
add_compile_options(-DSMCLK_SELECT=HFXT -DSMCLK_DIV=DIV1)

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(hw_test_edumkII)

add_executable(hw_test_edumkII
    hw_test_edumkII.cpp
    HW.cpp
)

# Add YAHAL
yahal_add_me(hw_test_edumkII)
yahal_add_library(hw_test_edumkII uGUI)

yahal_add_custom_targets(hw_test_edumkII)
yahal_add_extra_outputs(hw_test_edumkII)

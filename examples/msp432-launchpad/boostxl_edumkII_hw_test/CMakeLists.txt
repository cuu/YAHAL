cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Set all clocks to maximum frequency
add_compile_options(-DMCLK_SELECT=HFXT  -DMCLK_DIV=DIV1)
add_compile_options(-DSMCLK_SELECT=HFXT -DSMCLK_DIV=DIV1)

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(boostxl_edumkII_hw_test)

add_executable(boostxl_edumkII_hw_test
    boostxl_edumkII_hw_test.cpp
    HW.cpp
)

# Add YAHAL and uGUI
yahal_add_me(boostxl_edumkII_hw_test)
yahal_add_library(boostxl_edumkII_hw_test uGUI)

yahal_add_custom_targets(boostxl_edumkII_hw_test)
yahal_add_extra_outputs(boostxl_edumkII_hw_test)

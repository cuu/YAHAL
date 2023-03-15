cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

# Set clocks to MCU defaults (all 3MHz)
add_compile_options(-DMCLK_SELECT=DCO  -DMCLK_DIV=DIV1)
add_compile_options(-DSMCLK_SELECT=DCO -DSMCLK_DIV=DIV1)

project(boostxl_edumkII_opt3001_simple)

add_executable(boostxl_edumkII_opt3001_simple
    boostxl_edumkII_opt3001_simple.cpp
)

# Add YAHAL
yahal_add_me(boostxl_edumkII_opt3001_simple)

yahal_add_custom_targets(boostxl_edumkII_opt3001_simple)
yahal_add_extra_outputs(boostxl_edumkII_opt3001_simple)

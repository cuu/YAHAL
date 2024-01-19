cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

# Set clocks to MCU defaults (all 3MHz)
#add_compile_options(-DMCLK_SELECT=HFXT  -DMCLK_DIV=DIV4)
#add_compile_options(-DSMCLK_SELECT=HFXT -DSMCLK_DIV=DIV8)

project(boostxl_k350qvg)

add_executable(boostxl_k350qvg
    boostxl_k350qvg.cpp
)

# Add YAHAL
yahal_add_me(boostxl_k350qvg)
yahal_add_library(boostxl_k350qvg uGUI)

yahal_add_custom_targets(boostxl_k350qvg)
yahal_add_extra_outputs(boostxl_k350qvg)

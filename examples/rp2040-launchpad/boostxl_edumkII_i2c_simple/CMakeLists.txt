cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(boostxl_edumkII_i2c_simple)

add_executable(boostxl_edumkII_i2c_simple
    boostxl_edumkII_i2c_simple.cpp
)

# Add YAHAL
yahal_add_me(boostxl_edumkII_i2c_simple)

yahal_add_custom_targets(boostxl_edumkII_i2c_simple)
yahal_add_extra_outputs(boostxl_edumkII_i2c_simple)

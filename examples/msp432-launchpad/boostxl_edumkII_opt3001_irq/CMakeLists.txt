cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(boostxl_edumkII_opt3001_irq)

add_executable(boostxl_edumkII_opt3001_irq
    boostxl_edumkII_opt3001_irq.cpp
)

# Add YAHAL
yahal_add_me(boostxl_edumkII_opt3001_irq)

yahal_add_custom_targets(boostxl_edumkII_opt3001_irq)
yahal_add_extra_outputs(boostxl_edumkII_opt3001_irq)

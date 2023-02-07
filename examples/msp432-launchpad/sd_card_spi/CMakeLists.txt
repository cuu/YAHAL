cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(sd_card_spi)

add_executable(sd_card_spi
    sd_card_spi.cpp
)

# Add YAHAL and FatFS
yahal_add_me(sd_card_spi)
yahal_add_library(sd_card_spi FatFs)

yahal_add_custom_targets(sd_card_spi)
yahal_add_extra_outputs(sd_card_spi)

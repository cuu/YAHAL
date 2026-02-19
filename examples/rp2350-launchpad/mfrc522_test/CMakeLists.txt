cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2350-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(mfrc522_test)

add_executable(mfrc522_test
    mfrc522_test.cpp
)

# Add YAHAL to target
yahal_add_me(mfrc522_test)

yahal_add_custom_targets(mfrc522_test)
yahal_add_extra_outputs(mfrc522_test)


cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(blink_pwm)

add_executable(blink_pwm
    blink_pwm.cpp
)

# Add YAHAL to target
yahal_add_me(blink_pwm)

yahal_add_custom_targets(blink_pwm)
yahal_add_extra_outputs(blink_pwm)


cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(stepper_motor)

add_executable(stepper_motor
    stepper_motor.cpp
)

# Add YAHAL
yahal_add_me(stepper_motor)

yahal_add_custom_targets(stepper_motor)
yahal_add_extra_outputs(stepper_motor)

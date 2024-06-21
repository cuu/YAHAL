cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(mpu6050_example)

set(YAHAL_USE_NANO_SPECS 0)

add_executable(mpu6050_example
    mpu6050_example.cpp
        mpu6050.cpp
)

# Add YAHAL
yahal_add_me(mpu6050_example)

yahal_add_custom_targets(mpu6050_example)
yahal_add_extra_outputs(mpu6050_example)

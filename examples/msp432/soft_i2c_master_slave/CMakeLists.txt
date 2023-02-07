cmake_minimum_required(VERSION 3.16)

# Set the target board
set(YAHAL_BOARD "msp432-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(soft_i2c_master_slave)

add_executable(soft_i2c_master_slave
    soft_i2c_master_slave.cpp
    i2c_device.cpp
)

#target_include_directories(soft_i2c_master_slave
#    ${CMAKE_CURRENT_SOURCE_DIR}
#)

# Add YAHAL to target
yahal_add_me(soft_i2c_master_slave)

yahal_add_custom_targets(soft_i2c_master_slave)
yahal_add_extra_outputs(soft_i2c_master_slave)

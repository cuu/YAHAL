cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(soft_i2c_master_client)

add_executable(soft_i2c_master_client
    soft_i2c_master_client.cpp
    i2c_device.cpp
)

target_include_directories(soft_i2c_master_client
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add YAHAL to target
yahal_add_me(soft_i2c_master_client)

yahal_add_custom_targets(soft_i2c_master_client)
yahal_add_extra_outputs(soft_i2c_master_client)


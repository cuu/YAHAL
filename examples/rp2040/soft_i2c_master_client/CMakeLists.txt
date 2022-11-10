cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(soft_i2c_master_client C CXX ASM)

# Pull in YAHAL as subdirectory
yahal_add_me()

add_executable(soft_i2c_master_client
    soft_i2c_master_client.cpp
    i2c_device.cpp
)

target_include_directories(soft_i2c_master_client
    PRIVATE .
)

target_link_libraries(soft_i2c_master_client YAHAL)

yahal_add_custom_targets(soft_i2c_master_client)
yahal_add_extra_outputs(soft_i2c_master_client)


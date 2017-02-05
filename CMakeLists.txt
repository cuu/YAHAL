cmake_minimum_required(VERSION 3.7)

project(YAHAL CXX)

include_directories(include/interface)
include_directories(src/driver)
include_directories(src/util)
include_directories(${YAHAL_TARGET_INCLUDES})

add_library(YAHAL STATIC
	src/driver/cy8x95xxa_drv.cpp
	src/driver/gp2y1010au0f_drv.cpp
	src/driver/mcp23s17_drv.cpp
	src/driver/soft_i2c_master.cpp
	src/driver/st7735s_drv.cpp
	src/util/byte_bitstream.cpp
	src/util/std_io.cpp
	${YAHAL_TARGET_SOURCES})


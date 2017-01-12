#####################################
# Configuration for TI MSP432 devices
#####################################
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR msp432)

# Toolchain configuration
#########################
set(toolchain_path   /usr/local/gcc-arm-none-eabi-6_2-2016q4)
set(toolchain_prefix arm-none-eabi)

set(CMAKE_C_COMPILER   ${toolchain_path}/bin/${toolchain_prefix}-gcc)
set(CMAKE_CXX_COMPILER ${toolchain_path}/bin/${toolchain_prefix}-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# TI include files
##################
include_directories(build/msp432/include)
include_directories(build/msp432/include/CMSIS)

# Compiler and Linker flags
###########################

set(GCC_ARCH_FLAGS  "-mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(GCC_DEBUG_FLAGS "-g -gdwarf-3 -gstrict-dwarf")
set(GCC_MISC_FLAGS  "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_ARCH_FLAGS} ${GCC_DEBUG_FLAGS} ${GCC_MISC_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs")

add_definitions(-D__MSP432P401R__ -DTARGET_IS_FALCON -Dgcc)

# Platform sources
##################
set(YAHAL_TARGET_DIR      src/platform/msp432)
set(YAHAL_TARGET_INCLUDES ${YAHAL_TARGET_DIR})
set(YAHAL_TARGET_SOURCES
	${YAHAL_TARGET_DIR}/adc14_msp432.cpp
	${YAHAL_TARGET_DIR}/gpio_msp432.cpp
	${YAHAL_TARGET_DIR}/spi_msp432.cpp
	${YAHAL_TARGET_DIR}/clock_msp432.cpp
	${YAHAL_TARGET_DIR}/i2c_msp432.cpp
	${YAHAL_TARGET_DIR}/uart_msp432.cpp)


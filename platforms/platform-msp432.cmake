#####################################
# Configuration for TI MSP432 devices
#####################################
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR msp432)

# Toolchain configuration
#########################
set(toolchain_path   /usr/local/gcc-arm-none-eabi-6_2-2016q4)
#set(toolchain_path   /usr/local/gcc-arm-none-eabi-4_7-2013q3)
#set(toolchain_path   /usr/local/ccsv7/tools/compiler/gcc-arm-none-eabi-4_9-2015q3)
#set(toolchain_path   $ENV{HOME}/.energia15/packages/energia/tools/arm-none-eabi-gcc/4.8.4-20140725)

set(toolchain_prefix arm-none-eabi)

set(CMAKE_C_COMPILER   ${toolchain_path}/bin/${toolchain_prefix}-gcc)
set(CMAKE_CXX_COMPILER ${toolchain_path}/bin/${toolchain_prefix}-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Compiler configuration
########################
include_directories(include/platform/msp432)
include_directories(include/platform/msp432/CMSIS)

set(GCC_ARCH_FLAGS  "-mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs")
set(GCC_F_FLAGS     "-ffunction-sections -fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables")
set(GCC_CXX_F_FLAGS "-fno-threadsafe-statics -fno-rtti -fno-exceptions")
set(GCC_DEBUG_FLAGS "-g -gdwarf-3 -gstrict-dwarf")
set(GCC_WARN_FLAGS  "-Wall -Wextra")
#set(GCC_OPT_FLAGS   "-Os")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_ARCH_FLAGS} ${GCC_F_FLAGS} ${GCC_CXX_F_FLAGS} ${GCC_DEBUG_FLAGS} ${GCC_WARN_FLAGS} ${GCC_OPT_FLAGS}")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   ${GCC_ARCH_FLAGS} ${GCC_F_FLAGS} ${GCC_DEBUG_FLAGS} ${GCC_WARN_FLAGS} ${GCC_OPT_FLAGS}")

add_definitions(-D__MSP432P401R__ -DTARGET_IS_MSP432P4XX)
#add_definitions(-DNDEBUG)

# Linker configuration
######################
set(GCC_LINK_FLAGS  "-Wl,-Map,main.map -Wl,-T${CMAKE_SOURCE_DIR}/include/platform/msp432/msp432p401r.lds")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")

set(CMAKE_C_STANDARD_LIBRARIES   "-lgcc -lc_nano -lm -lnosys")
set(CMAKE_CXX_STANDARD_LIBRARIES "-lstdc++_nano ${CMAKE_C_STANDARD_LIBRARIES}")

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


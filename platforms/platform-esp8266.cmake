###################################
# Configuration for ESP8266 devices
###################################
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR esp8266)

# Toolchain configuration
#########################
set(TOOLCHAIN_PATH   /home/aterstegge/git/esp-open-sdk/xtensa-lx106-elf)
set(TOOLCHAIN_PREFIX xtensa-lx106-elf)
set(SDK_PATH         /home/aterstegge/git/foo/ESP8266_NONOS_SDK_V2.0.0_16_08_10)

set(CMAKE_C_COMPILER   ${TOOLCHAIN_PATH}/bin/${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/${TOOLCHAIN_PREFIX}-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# SDK include files
###################
include_directories(${SDK_PATH}/include)
#include_directories(${SDK_PATH}/lwip/include)

# Compiler and Linker flags
###########################
add_definitions(-D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ )
add_definitions(-DF_CPU=80000000L -DLWIP_OPEN_SRC -DESP8266)

set(GCC_DEBUG_FLAGS "-g")
set(GCC_MISC_FLAGS  "-Wall -std=c++11")
set(GCC_OPTI_FLAGS  "-Os")
set(GCC_M_FLAGS     "-mlongcalls -mtext-section-literals")
set(GCC_F_FLAGS     "-fno-exceptions -fno-rtti -falign-functions=4 -ffunction-sections -fdata-sections")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_M_FLAGS}    ${GCC_F_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_OPTI_FLAGS} ${GCC_DEBUG_FLAGS} ${GCC_MISC_FLAGS}")

set(LN_SCRIPT_FLASH "eagle.app.v6.new.1024.app1.ld")
set(LN_SCRIPT_ROM   "eagle.rom.addr.v6.ld")

set(GCC_LINK_FLAGS  "-nostdlib -T${LN_SCRIPT_FLASH} -T${LN_SCRIPT_ROM}")
set(GCC_LINK_LIBS   "-lmain -lphy -llwip  -lnet80211 -lwpa -lpp -lnet80211 -lgcc -lc /home/aterstegge/git/YAHAL/platforms/dummy_user_init.o")

link_directories(${SDK_PATH}/lib ${SDK_PATH}/ld)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS} ${GCC_LINK_LIBS}")


# Platform sources
##################
set(YAHAL_TARGET_SRC_DIR      src/platform/esp8266)
set(YAHAL_TARGET_INC_DIR  include/platform/esp8266)

set(YAHAL_TARGET_INCLUDES ${YAHAL_TARGET_SRC_DIR} ${YAHAL_TARGET_INC_DIR} )
set(YAHAL_TARGET_SOURCES 
	${YAHAL_TARGET_SRC_DIR}/timer_esp8266.cpp
	${YAHAL_TARGET_SRC_DIR}/gpio_esp8266.cpp
)


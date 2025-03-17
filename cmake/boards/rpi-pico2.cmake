###############################
# Configuration for RPi pico2 #
###############################

message("Using board RP2350 Lauchpad") 

# Toolchain and MCU configuration
set(CMAKE_TOOLCHAIN_FILE toolchains/arm-gcc)
include(MCU/rp2350)

# Linker script
set(LINKER_SCRIPT_PATH     "${CMAKE_CURRENT_LIST_DIR}/rpi-pico2.ld" 
    CACHE FILEPATH "Linker Script")
set(LINKER_SCRIPT_FLAGS    "-Wl,-T \"${LINKER_SCRIPT_PATH}\"")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_SCRIPT_FLAGS}")

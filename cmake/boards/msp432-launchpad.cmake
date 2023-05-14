#########################################
# Configuration for TI MSP432 launchpad #
#########################################

message("Using board TI MSP432 Lauchpad") 

# Toolchain and MCU configuration
set(CMAKE_TOOLCHAIN_FILE toolchains/arm-gcc)
include(MCU/msp432p401r)

# Linker script
set(LINKER_SCRIPT_PATH     "${CMAKE_CURRENT_LIST_DIR}/msp432-launchpad.ld" CACHE FILEPATH "Linker Script")
set(LINKER_SCRIPT_FLAGS    "-Wl,-T \"${LINKER_SCRIPT_PATH}\"")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_SCRIPT_FLAGS}")

# Debug interface: The MSP432 LP has a
# buildin XDS110 debug probe, which is
# supported by OpenOCD.
set(OPENOCD_CONFIG 
    "-f" "board/ti_msp432_launchpad.cfg" 
    CACHE STRING "OpenOCD configuration")

######################################
# Configuration for RP2040 launchpad #
######################################

message("Using board RP2040 Lauchpad") 

# Toolchain and MCU configuration
include(toolchains/arm-gcc)
include(MCU/rp2040)

# Linker script
set(LINKER_SCRIPT_PATH     "${CMAKE_CURRENT_LIST_DIR}/rp2040-launchpad.ld" CACHE FILEPATH "Linker Script")
set(LINKER_SCRIPT_FLAGS    "-Wl,-T \"${LINKER_SCRIPT_PATH}\" ${YAHAL_DIR}/src/MCU/${YAHAL_MCU}/boot/bs2_default.S")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_SCRIPT_FLAGS}")

# Debug interface: The RP2040 LP has a
# buildin picoprobe debug probe, which
# is supported by OpenOCD.
set(OPENOCD_CONFIG 
    "-f" "interface/picoprobe.cfg" "-f" "target/rp2040.cfg"
    CACHE STRING "OpenOCD configuration")

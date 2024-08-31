######################################
# Configuration for RP2350 launchpad #
######################################

message("Using board RP2350 Lauchpad") 

# Toolchain and MCU configuration
set(CMAKE_TOOLCHAIN_FILE toolchains/arm-gcc)
include(MCU/rp2350)

# Linker script
set(LINKER_SCRIPT_PATH     "${CMAKE_CURRENT_LIST_DIR}/rp2350-launchpad.ld" CACHE FILEPATH "Linker Script")
set(LINKER_SCRIPT_FLAGS    "-Wl,-T \"${LINKER_SCRIPT_PATH}\" ${YAHAL_DIR}/src/MCU/${YAHAL_MCU}/boot/bs2_default.S")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_SCRIPT_FLAGS}")

# Debug interface: The RP2350 LP has a
# buildin picoprobe debug probe, which
# is supported by OpenOCD.
#
set(OPENOCD_CONFIG 
    "-d1" "-f" "interface/cmsis-dap.cfg" "-c" "adapter speed 5000" "-f" "target/rp2350b.cfg"
    CACHE STRING "OpenOCD configuration")

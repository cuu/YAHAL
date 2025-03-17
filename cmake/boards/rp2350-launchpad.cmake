######################################
# Configuration for RP2350 launchpad #
######################################

message("Using board RP2350 Lauchpad") 

# Toolchain and MCU configuration
set(CMAKE_TOOLCHAIN_FILE toolchains/arm-gcc)
include(MCU/rp2350)

# Linker script
if (YAHAL_LOAD_INTO_RAM)
    set(LINKER_SCRIPT_PATH "${CMAKE_CURRENT_LIST_DIR}/rp2350-launchpad_load_into_ram.ld"
        CACHE FILEPATH "Linker Script")
elseif(YAHAL_LOAD_INTO_PSRAM)
    set(LINKER_SCRIPT_PATH "${CMAKE_CURRENT_LIST_DIR}/rp2350-launchpad_load_into_psram.ld"
        CACHE FILEPATH "Linker Script")
elseif(YAHAL_COPY_TO_RAM)
    set(LINKER_SCRIPT_PATH "${CMAKE_CURRENT_LIST_DIR}/rp2350-launchpad_copy_to_ram.ld"
        CACHE FILEPATH "Linker Script")
elseif(YAHAL_COPY_TO_PSRAM)
    set(LINKER_SCRIPT_PATH "${CMAKE_CURRENT_LIST_DIR}/rp2350-launchpad_copy_to_psram.ld"
            CACHE FILEPATH "Linker Script")
else()
    set(LINKER_SCRIPT_PATH "${CMAKE_CURRENT_LIST_DIR}/rp2350-launchpad.ld"
        CACHE FILEPATH "Linker Script")
endif()

set(LINKER_SCRIPT_FLAGS    "-Wl,-T \"${LINKER_SCRIPT_PATH}\"")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_SCRIPT_FLAGS}")

# Debug interface: The RP2350 LP has a
# buildin picoprobe debug probe, which
# is supported by OpenOCD.
set(OPENOCD_CONFIG 
    "-f" "interface/cmsis-dap.cfg" "-c" "adapter speed 5000" "-f" "target/rp2350.cfg"
    CACHE STRING "OpenOCD configuration")

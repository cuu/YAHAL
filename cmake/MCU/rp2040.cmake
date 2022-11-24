################################
# Configuration for RP2040 MCU #
################################
message("Using MCU RP2040")

# Set MCU name
set(YAHAL_MCU "rp2040")

# MSP432 has a cortex M4F
include(CPU/cortex-m0+)

# Linker script
set(LINKER_SCRIPT_FLAGS    "-Wl,-T ${CMAKE_CURRENT_LIST_DIR}/rp2040.ld ${CMAKE_CURRENT_LIST_DIR}/bs2_default_padded_checksummed.S")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_SCRIPT_FLAGS}")


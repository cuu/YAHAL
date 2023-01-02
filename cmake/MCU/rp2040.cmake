################################
# Configuration for RP2040 MCU #
################################
message("Using MCU RP2040")

# Set MCU name
set(YAHAL_MCU "rp2040")

# MSP432 has a cortex M4F
include(CPU/cortex-m0plus)

# Linker script
set(LINKER_SCRIPT_PATH     "${CMAKE_CURRENT_LIST_DIR}/rp2040.ld" CACHE FILEPATH "Linker Script")
set(LINKER_SCRIPT_FLAGS    "-Wl,-T \"${LINKER_SCRIPT_PATH}\" ${YAHAL_DIR}/src/MCU/${YAHAL_MCU}/boot/bs2_default.S")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_SCRIPT_FLAGS}")


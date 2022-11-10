########################################
# Configuration for TI MSP432P401R MCU #
########################################

message("Using MCU TI MSP432P401R")

# MSP432 has a cortex M4F
include(CPUs/cortex-m0+)

# Linker script
set(LINKER_SCRIPT_FLAGS    "-Wl,-T ${CMAKE_CURRENT_LIST_DIR}/rp2040.ld ${CMAKE_CURRENT_LIST_DIR}/bs2_default_padded_checksummed.S")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_SCRIPT_FLAGS}")


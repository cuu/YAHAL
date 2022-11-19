########################################
# Configuration for TI MSP432P401R MCU #
########################################

message("Using MCU TI MSP432P401R")

# MSP432 has a cortex M4F
include(CPUs/cortex-m4f)

# For msp.h
add_compile_definitions(__MSP432P401R__)

# Linker script
set(LINKER_SCRIPT_PATH     "${CMAKE_CURRENT_LIST_DIR}/msp432p401r.ld" CACHE FILEPATH "Linker Script")
set(LINKER_SCRIPT_FLAGS    "-Wl,-T ${LINKER_SCRIPT_PATH}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_SCRIPT_FLAGS}")


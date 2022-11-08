########################################
# Configuration for TI MSP432P401R MCU #
########################################

message("Using MCU TI MSP432P401R")

# MSP432 has a cortex M4F
include(CPUs/cortex-m4f)

# For msp.h
add_compile_definitions(__MSP432P401R__)

# Linker script
set(LINKER_SCRIPT_FLAGS    "-Wl,-T ${CMAKE_CURRENT_LIST_DIR}/msp432p401r.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_SCRIPT_FLAGS}")


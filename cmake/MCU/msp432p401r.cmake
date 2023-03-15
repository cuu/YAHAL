########################################
# Configuration for TI MSP432P401R MCU #
########################################
message("Using MCU TI MSP432P401R")

# Set MCU name
set(YAHAL_MCU "msp432p401r")

# MSP432 has a cortex M4F
include(CPU/cortex-m4f)

# For msp.h
add_compile_definitions(__MSP432P401R__)

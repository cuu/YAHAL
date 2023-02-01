################################
# Configuration for RP2040 MCU #
################################
message("Using MCU RP2040")

# Set MCU name
set(YAHAL_MCU "rp2040")

# MSP432 has a cortex M4F
include(CPU/cortex-m0plus)

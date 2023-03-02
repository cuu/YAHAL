################################
# Configuration for RP2040 MCU #
################################
message("Using MCU RP2040")

# Set MCU name
set(YAHAL_MCU "rp2040")

# RP2040 has a cortex M0+
include(CPU/cortex-m0plus)

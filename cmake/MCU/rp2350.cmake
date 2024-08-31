################################
# Configuration for RP2350 MCU #
################################
message("Using MCU RP2350")

# Set MCU name
set(YAHAL_MCU "rp2350")

# RP2350 has a cortex M33 with FPU and DSP
include(CPU/cortex-m33fd)

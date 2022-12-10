######################################
# Configuration for RP2040 launchpad #
######################################

message("Using board RP2040 Lauchpad") 

# Toolchain and MCU configuration
include(toolchains/arm-gcc)
include(MCU/rp2040)

# Debug interface: The RP2040 LP has a
# buildin picoprobe debug probe, which
# is supported by OpenOCD.
set(OPENOCD_CONFIG 
    "-f" "interface/picoprobe.cfg" "-f" "target/rp2040.cfg"
    CACHE STRING "OpenOCD configuration")

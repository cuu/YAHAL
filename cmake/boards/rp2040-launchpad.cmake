#########################################
# Configuration for TI MSP432 launchpad #
#########################################

message("Using board RP2040 Lauchpad") 

# Toolchain and MCU configuration
include(toolchains/arm-gcc)
include(MCUs/rp2040)

# Debug interface: The MSP432 LP has a
# build-in XDS110 debug probe, which is
# supported by OpenOCD.
set(OPENOCD_CONFIG 
    "-f" "interface/picoprobe.cfg" "-f" "target/rp2040.cfg"
    CACHE STRING "OpenOCD configuration")

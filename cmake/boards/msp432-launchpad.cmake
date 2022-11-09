#########################################
# Configuration for TI MSP432 launchpad #
#########################################

message("Using board TI MSP432 Lauchpad") 

# Toolchain and MCU configuration
include(toolchains/arm-gcc)
include(MCUs/msp432p401r)

# Debug interface: The MSP432 LP has a
# build-in XDS110 debug probe, which is
# supported by OpenOCD.
set(OPENOCD_CONFIG 
    "-f" "board/ti_msp432_launchpad.cfg" 
    CACHE STRING "OpenOCD configuration")


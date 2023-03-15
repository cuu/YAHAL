######################################
# Configuration for RP2040 launchpad #
######################################

message("Using board WiFiTick") 

# Toolchain and MCU configuration
include(toolchains/xtensa-lx106-gcc)
include(MCU/esp8266)

# Debug interface: The RP2040 LP has a
# buildin picoprobe debug probe, which
# is supported by OpenOCD.
#set(OPENOCD_CONFIG 
#    "-f" "interface/picoprobe.cfg" "-f" "target/rp2040.cfg"
#    CACHE STRING "OpenOCD configuration")

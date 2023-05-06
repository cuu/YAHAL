######################################
# Configuration for RP2040 launchpad #
######################################

message("Using board WiFiTick") 

# Toolchain and MCU configuration
include(toolchains/xtensa-lx106-gcc)
include(MCU/esp8266)

# Linker script stuff to be added

######################################
# Configuration for RP2040 launchpad #
######################################

message("Using board WiFiTick") 

# set(ARDUINO_INSTALL_PATH "/usr/local/arduino-1.8.16")
set(ARDUINO_BOARD "Generic ESP8266 Module [esp8266.generic]")

# Toolchain and MCU configuration
set(CMAKE_TOOLCHAIN_FILE toolchains/Arduino-toolchain)
include(MCU/esp8266)

# Linker script stuff to be added

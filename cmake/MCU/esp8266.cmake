#################################
# Configuration for ESP8266 MCU #
#################################
message("Using MCU ESP8266")

# Set MCU name
set(YAHAL_MCU "esp8266")

# ESP8266 has a xtensa lx106 CPU
include(CPU/xtensa-lx106)

# Linker script
#set(LINKER_SCRIPT_PATH     "${CMAKE_CURRENT_LIST_DIR}/rp2040.ld" CACHE FILEPATH "Linker Script")
#set(LINKER_SCRIPT_FLAGS    "-Wl,-T \"${LINKER_SCRIPT_PATH}\" ${YAHAL_DIR}/src/MCU/${YAHAL_MCU}/boot/bs2_default.S")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_SCRIPT_FLAGS}")


set(CMAKE_SYSTEM_NAME Generic)

# Path and Prefix of toolchain
##############################
set(toolchain_path   /usr/local/eclipse-c++-arduino/arduinoPlugin/tools/esp8266/xtensa-lx106-elf-gcc/1.20.0-26-gb404fb9-2)
set(toolchain_prefix xtensa-lx106-elf)
set(sdk_path         /usr/local/eclipse-c++-arduino/arduinoPlugin/packages/esp8266/hardware/esp8266/2.3.0/tools/sdk)


# Set the C and C++ compiler
############################
set(CMAKE_C_COMPILER   ${toolchain_path}/bin/${toolchain_prefix}-gcc)
set(CMAKE_CXX_COMPILER ${toolchain_path}/bin/${toolchain_prefix}-g++)

# Linker flags
##############
link_directories(${sdk_path}/lib)
link_directories(${sdk_path}/ld)
set(CMAKE_EXE_LINKER_FLAGS "-g -Os -nostdlib -Wl,--no-check-sections -u call_user_start -Wl,-static -Teagle.flash.4m1m.ld -Wl,--gc-sections -Wl,-wrap,system_restart_local -Wl,-wrap,register_chipv6_phy" ${CMAKE_EXE_LINKER_FLAGS})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


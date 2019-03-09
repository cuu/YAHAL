# ---------------------------------------------
#           This file is part of
#      _  _   __    _   _    __    __
#     ( \/ ) /__\  ( )_( )  /__\  (  )
#      \  / /(__)\  ) _ (  /(__)\  )(__
#      (__)(__)(__)(_) (_)(__)(__)(____)
#
#    YAHAL,  Another HW Abstraction Library
#     Copyright (C) 2017 Andreas Terstegge
#     BSD Licensed (see file LICENSE)
#
# ---------------------------------------------
#
YAHAL_DIR = ../../..
# fixed target platform: esp8266
PLATFORM = esp8266

# name of final target
TARGET = WebServer_esp8266.out

# folder for build artifacts
BUILD_DIR = build

# all source folders of our project
SRC_DIRS  = src

# all include folders of our project
INC_DIRS  = $(ESP_CORE_DIR)
INC_DIRS += $(ESP_CORE_DIR)/libb64
INC_DIRS += $(ESP_CORE_DIR)/spiffs
INC_DIRS += $(ESP_CORE_DIR)/umm_malloc
# ESP8266WebServer
INC_DIRS += $(ESP_LIB_DIR)/ESP8266WebServer/src
INC_DIRS += $(ESP_LIB_DIR)/ESP8266WebServer/src/detail
# ESP8266WiFi
INC_DIRS += $(ESP_LIB_DIR)/ESP8266WiFi/src
INC_DIRS += $(ESP_LIB_DIR)/ESP8266WiFi/src/include
# ESP8266mDNS
INC_DIRS += $(ESP_LIB_DIR)/ESP8266mDNS/src

# all linked-in libraries
LINK_LIBS  = ../libarduino_esp8266/libarduino_esp8266.a
LINK_LIBS += ../libextra_esp8266/libextra_esp8266.a

# serial port configuration
ESP_PORT = /dev/ttyACM0
# Serial Port baudrate
ESP_BAUD = 115200
# Reset-Mode: none|ck|nodemcu
ESP_RESET_MODE = none
# Flash-frequency: 40|80
ESP_FLASH_FREQ = 40
# Flash-Mode: dio|qio|dout|qout
ESP_FLASH_MODE = qio
# Flash size 512K|256K|1M|2M|4M|8M|16M|32M
ESP_FLASH_SIZE = 4M
# Linker script
# eagle.flash.1m64.ld
# eagle.flash.1m128.ld
# eagle.flash.1m144.ld
# eagle.flash.1m160.ld
# eagle.flash.1m192.ld
# eagle.flash.1m256.ld
# eagle.flash.1m512.ld
# eagle.flash.2m.ld
# eagle.flash.512k0.ld
# eagle.flash.512k64.ld
# eagle.flash.512k128.ld
# eagle.flash.4m1m.ld
# eagle.flash.4m.ld
# eagle.flash.8m.ld
# eagle.flash.16m.ld
ESP_FLASH_SCRIPT = eagle.flash.4m.ld

# spiffs data folder
SPIFFS_DIR = data
# spiffs pagesize (usually fixed to 256)
SPIFFS_PAGESIZE = 256
# spiffs blocksize:
# 4096 with spiffs sizes <  512k
# 8192 with spiffs sizes >= 512k
SPIFFS_BLOCKSIZE = 4096
# spiffs size in flash
SPIFFS_SIZE = 131072
# spiffs start addr in flash, immediately after code
SPIFFS_START = 0x100000
 
include $(YAHAL_DIR)/makefiles/common.mk

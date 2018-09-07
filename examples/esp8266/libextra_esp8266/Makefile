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
TARGET = libextra_esp8266.a

# folder for build artifacts
BUILD_DIR = build

# all include folders of our project
INC_DIRS  = $(ESP_CORE_DIR)
INC_DIRS += $(ESP_CORE_DIR)/libb64
INC_DIRS += $(ESP_CORE_DIR)/spiffs
INC_DIRS += $(ESP_CORE_DIR)/umm_malloc

# additional libraries

# ESP8266WebServer
SRC_DIRS += $(ESP_LIB_DIR)/ESP8266WebServer/src
SRC_DIRS += $(ESP_LIB_DIR)/ESP8266WebServer/src/detail
INC_DIRS += $(ESP_LIB_DIR)/ESP8266WebServer/src
INC_DIRS += $(ESP_LIB_DIR)/ESP8266WebServer/src/detail

# ESP8266WiFi
SRC_DIRS += $(ESP_LIB_DIR)/ESP8266WiFi/src
INC_DIRS += $(ESP_LIB_DIR)/ESP8266WiFi/src
INC_DIRS += $(ESP_LIB_DIR)/ESP8266WiFi/src/include

# ESP8266mDNS
SRC_DIRS += $(ESP_LIB_DIR)/ESP8266mDNS
INC_DIRS += $(ESP_LIB_DIR)/ESP8266mDNS

# SPI
SRC_DIRS += $(ESP_LIB_DIR)/SPI
INC_DIRS += $(ESP_LIB_DIR)/SPI

include $(YAHAL_DIR)/makefiles/common.mk


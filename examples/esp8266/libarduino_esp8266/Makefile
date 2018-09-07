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
TARGET = libarduino_esp8266.a

# folder for build artifacts
BUILD_DIR = build

# all source folders of our project
SRC_DIRS  = $(ESP_CORE_DIR)
SRC_DIRS += $(ESP_CORE_DIR)/libb64
SRC_DIRS += $(ESP_CORE_DIR)/spiffs
SRC_DIRS += $(ESP_CORE_DIR)/umm_malloc

# all include folders of our project
INC_DIRS  = $(SRC_DIRS)

# all flags for linked-in libraries
USERLIBS =

include $(YAHAL_DIR)/makefiles/common.mk


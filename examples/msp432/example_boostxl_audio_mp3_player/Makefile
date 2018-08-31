# ---------------------------------------------
#           This file is part of
#      _  _   __    _   _    __    __
#     ( \/ ) /__\  ( )_( )  /__\  (  )
#      \  / /(__)\  ) _ (  /(__)\  )(__
#      (__)(__)(__)(_) (_)(__)(__)(____)
#
#     Yet Another HW Abstraction Library
#      Copyright (C) Andreas Terstegge
#      BSD Licensed (see file LICENSE)
#
# ---------------------------------------------

# platform and YAHAL location
PLATFORM  = msp432
YAHAL_DIR = ../../..

# name of final target
TARGET = example_boostxl_audio_mp3_player.out

# folder for build artifacts
# (same as eclipse build folder)
BUILD_DIR = Debug

# all source folders of our project
SRC_DIRS  = .
SRC_DIRS += src

# The MP3 player has to be fast...
# Best is to compile YAHAL also with -Ofast
FLAGS_OPT = -Ofast

# include dirs
INC_DIRS += $(SRC_DIRS)
INC_DIRS += $(YAHAL_DIR)/src/platform/$(PLATFORM)
INC_DIRS += $(YAHAL_DIR)/include/interface
INC_DIRS += $(YAHAL_DIR)/src/driver
INC_DIRS += $(YAHAL_DIR)/src/util
INC_DIRS += $(YAHAL_DIR)/src/task
INC_DIRS += $(YAHAL_DIR)/src/FatFs
INC_DIRS += $(YAHAL_DIR)/src/libmad

# linked in libraries
LINK_LIBS = $(YAHAL_DIR)/libYAHAL_msp432.a 

include $(YAHAL_DIR)/makefiles/common.mk


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
#
# Platform configuration file for Beaglebone Black
#

# Flag helper variables
#FLAGS_F        += -ffunction-sections -fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables
#FLAGS_F	+= -fno-strict-aliasing
#FLAGS_M        += -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs
#FLAGS_DEBUG    += -g -gdwarf-3 -gstrict-dwarf
#FLAGS_WARN     += -Wall -Wextra
#FLAGS_OPT      += # -Ofast

FLAGS_CXX       = -std=c++11
#FLAGS_C         =
#FLAGS_ASM       =

#LN_SCRIPT_FLASH = msp432p401r.lds
#FLAGS_LD        = -Wl,-T$(MSP_INC_DIR)/$(LN_SCRIPT_FLASH)
#FLAGS_LD       += -Wl,-Map,$(basename $(TARGET)).map
#FLAGS_LD       += -Wl,--gc-sections
FLAGS_LD += -pthread

#################################################
# The following variables are used by common.mk #
#################################################

# Cross-tools
#############
CC      = gcc
CXX     = g++
LD      = g++
AR      = ar
RANLIB  = ranlib

# Compiler/Linker flags ans libraries
#####################################
CXXFLAGS = $(FLAGS_F) $(FLAGS_M) $(FLAGS_DEBUG) $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_CXX)
CFLAGS   = $(FLAGS_F) $(FLAGS_M) $(FLAGS_DEBUG) $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_C)
ASMFLAGS = $(FLAGS_M) $(FLAGS_DEBUG) $(FLAGS_ASM)
LDFLAGS  = $(CXXFLAGS) $(FLAGS_LD) $(LIBS)
#LIBS     = -lstdc++ -lgcc -lc -lm -lnosys
LIBS     = -lstdc++ -lgcc -lc -lm


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
# Platform configuration file for MSP432
#
# This file depends on a gcc-arm-none-eabi C/C++
# compiler intallation. Currently the toolchain 
# from the Code Composer Studio is used, but it
# can be replaced by any another version. 

# Toolchain location
TOOLCHAIN_PATH   = /usr/local/gcc-arm-none-eabi-10.3-2021.10
TOOLCHAIN_PREFIX = arm-none-eabi

# Various path variables
MSP_INC_DIR = $(YAHAL_DIR)/include/platform/$(PLATFORM)

# Various MSP tools
OPENOCD = /usr/local/bin/openocd

# Flag helper variables
FLAGS_F        += -ffunction-sections -fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables
FLAGS_F		   += -fno-strict-aliasing
FLAGS_M        += -mcpu=cortex-m0plus -march=armv6s-m -mthumb 
# -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs
FLAGS_DEBUG    += -g -gdwarf-3 -gstrict-dwarf
FLAGS_WARN     += -Wall -Wextra
FLAGS_OPT      += # -Ofast

FLAGS_CXX       = -fno-threadsafe-statics -fno-exceptions -std=c++17
FLAGS_C         =
FLAGS_ASM       =

LN_SCRIPT_FLASH = RP2040.ld
FLAGS_LD        = -Wl,-T$(MSP_INC_DIR)/$(LN_SCRIPT_FLASH)
FLAGS_LD       +=  $(MSP_INC_DIR)/bs2_default_padded_checksummed.S
FLAGS_LD       += -Wl,-Map,$(basename $(TARGET)).map
FLAGS_LD       += -Wl,--gc-sections

#################################################
# The following variables are used by common.mk #
#################################################

# Cross-tools
#############
CC      = $(QUOTE)$(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-gcc$(QUOTE)
CXX     = $(QUOTE)$(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-g++$(QUOTE)
LD      = $(QUOTE)$(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-g++$(QUOTE)
AR      = $(QUOTE)$(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-ar$(QUOTE)
RANLIB  = $(QUOTE)$(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-ranlib$(QUOTE)

# Compiler/Linker flags ans libraries
#####################################
CXXFLAGS = $(FLAGS_F) $(FLAGS_M) $(FLAGS_DEBUG) $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_CXX)
CFLAGS   = $(FLAGS_F) $(FLAGS_M) $(FLAGS_DEBUG) $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_C)
ASMFLAGS = $(FLAGS_M) $(FLAGS_DEBUG) $(FLAGS_ASM)
LDFLAGS  = $(CXXFLAGS) $(FLAGS_LD) $(LIBS)
#LIBS     = -lstdc++ -lgcc -lc -lm -lnosys
LIBS     = -lstdc++_nano -lgcc -lc_nano -lm -lnosys

# Compiler defines
##################
# DEFINES   = -D__MSP432P401R__ -DTARGET_IS_MSP432P4XX
# DEFINES  += -DARM_MATH_CM4 -D__FPU_PRESENT=1
#DEFINES += -DNDEBUG

# Platform includes
###################
PLATFORM_INC_DIRS  = $(QUOTE)$(MSP_INC_DIR)$(QUOTE)
PLATFORM_INC_DIRS += $(QUOTE)$(MSP_INC_DIR)/CMSIS$(QUOTE)

# Additional rules (e.g. for upload)
####################################
define PLATFORM_RULES
.PHONY: upload
upload: all
	$(OPENOCD) -f interface/picoprobe.cfg -f target/rp2040.cfg -c "program $(TARGET) verify reset exit"
endef


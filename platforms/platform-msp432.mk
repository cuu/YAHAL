######################################
# Toolchain configuration for MSP432 #
######################################

# This file has to define:
# ------------------------
#
#  CC                 : full path to gcc cross compiler
#  CXX                : full path to g++ cross compiler
#  LD                 : full path to ld  cross linker
#  AR                 : full path to ar  cross archiver
#  RANLIB             : full path to ranlib
#
#  PLATFORM_INCLUDES  : all specific include flags for this platform
#
#  CFLAGS             : all specific C-flags
#  CXXFLAGS           : all specific C++-flags (including C-flags)!
#  DEFINES            : all necessary defines


TOOLCHAIN_PATH   = /usr/local/gcc-arm-none-eabi-6_2-2016q4
TOOLCHAIN_PREFIX = arm-none-eabi

CC      = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-gcc
CXX     = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-g++
LD      = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-g++
AR      = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-ar
RANLIB  = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-ranlib

PLATFORM_INC_DIR   = include/platform/$(PLATFORM)
PLATFORM_INCLUDES  = -I$(PLATFORM_INC_DIR)
PLATFORM_INCLUDES += -I$(PLATFORM_INC_DIR)/CMSIS

FLAGS_ARCH     = -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs
FLAGS_F        = -ffunction-sections -fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables
FLAGS_DEBUG    = -g -gdwarf-3 -gstrict-dwarf
FLAGS_WARN     = -Wall -Wextra
FLAGS_OPT      = -Os
FLAGS_CXX      = -fno-threadsafe-statics -fno-rtti -fno-exceptions -std=c++11

CFLAGS         = $(FLAGS_ARCH) $(FLAGS_F) $(FLAGS_DEBUG) $(FLAGS_WARN) $(FLAGS_OPT)
CXXFLAGS       = $(FLAGS_ARCH) $(FLAGS_F) $(FLAGS_DEBUG) $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_CXX)

FLAGS_LD       = -Wl,-Map,$(basename $(TARGET)).map -Wl,-T$(PLATFORM_INC_DIR)/msp432p401r.lds
LIBS           = -lstdc++_nano -lgcc -lc_nano -lm -lnosys

LDFLAGS        = $(CXXFLAGS) $(FLAGS_LD) $(LIBS)

DEFINES        = -D__MSP432P401R__ -DTARGET_IS_MSP432P4XX
#DEFINES       += -DNDEBUG



#######################################
# Toolchain configuration for ESP8266 #
#######################################

# This file has to define:
# ------------------------
#
#  CC                 : full path to gcc cross compiler
#  CXX                : full path to g++ cross compiler
#  LD                 : full path to ld  cross linker
#  AR                 : full path to ar  cross archiver
#  RANLIB             : full path to ranlib
#
#  PLATFORM_SRC_DIR   : all specific source dirs for this platform 
#  PLATFORM_INCLUDES  : all specific include flags for this platform
#
#  CFLAGS             : all specific C-flags
#  CXXFLAGS           : all specific C++-flags (including C-flags)!
#  DEFINES            : all necessary defines


TOOLCHAIN_PATH   = /home/aterstegge/git/esp-open-sdk/xtensa-lx106-elf
TOOLCHAIN_PREFIX = xtensa-lx106-elf
SDK_PATH         = /home/aterstegge/git/foo/ESP8266_NONOS_SDK_V2.0.0_16_08_10

CC      = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-gcc
CXX     = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-g++
LD      = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-ld
AR      = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-ar
RANLIB  = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-ranlib

PLATFORM_SRC_DIR  = src/platform/$(PLATFORM)
PLATFORM_INC_DIR  = include/platform/$(PLATFORM)
PLATFORM_INCLUDES = -I$(PLATFORM_INC_DIR) -I$(SDK_PATH)/include -I$(SDK_PATH)/lwip/include

FLAGS_F        = -fno-exceptions -fno-rtti -falign-functions=4 -ffunction-sections -fdata-sections
FLAGS_M        = -mlongcalls -mtext-section-literals
FLAGS_DEBUG    = -g
FLAGS_WARN     = -Wall -Wextra
FLAGS_OPT      = -Os
FLAGS_CXX      = -fno-threadsafe-statics -fno-rtti -fno-exceptions -std=c++11

LN_SCRIPT_FLASH = eagle.app.v6.new.1024.app1.ld
LN_SCRIPT_ROM   = eagle.rom.addr.v6.ld

FLAGS_LD       = -nostdlib -T$(LN_SCRIPT_FLASH) -T$(LN_SCRIPT_ROM) -L$(SDK_PATH)/lib -L $(SDK_PATH)/ld
FLAGS_C_LIBS   = -lmain -lphy -llwip  -lnet80211 -lwpa -lpp -lnet80211 -lgcc -lc $(CURDIR)/platforms/dummy_user_init.o
FLAGS_CXX_LIBS = -lmain -lphy -llwip  -lnet80211 -lwpa -lpp -lnet80211 -lgcc -lc /home/aterstegge/git/YAHAL/platforms/dummy_user_init.o

CFLAGS      = $(FLAGS_F) $(FLAGS_M) $(FLAGS_DEBUG) $(FLAGS_WARN) $(FLAGS_OPT)
CXXFLAGS    = $(FLAGS_F) $(FLAGS_M) $(FLAGS_DEBUG) $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_CXX)

DEFINES     = -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ -DF_CPU=80000000L  -DESP8266
# Taken out because of errors
# -DLWIP_OPEN_SRC

#DEFINES     = $(DEFINES) -DNDEBUG


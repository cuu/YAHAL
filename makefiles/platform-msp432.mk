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

# Root folder CCS installation
ifeq ($(FILE_UNIX_STYLE),1)
CCS_ROOT = /opt/ti/ccsv7
else
CCS_ROOT = C:/ti/ccsv7
endif

DSP_LIB_DIR = $(YAHAL_DIR)/src/platform/$(PLATFORM)/DSP
# DSP source folders
SRC_DIRS += $(DSP_LIB_DIR)/Source/BasicMathFunctions
SRC_DIRS += $(DSP_LIB_DIR)/Source/CommonTables
SRC_DIRS += $(DSP_LIB_DIR)/Source/ComplexMathFunctions
SRC_DIRS += $(DSP_LIB_DIR)/Source/ControllerFunctions
SRC_DIRS += $(DSP_LIB_DIR)/Source/FastMathFunctions
SRC_DIRS += $(DSP_LIB_DIR)/Source/FilteringFunctions
SRC_DIRS += $(DSP_LIB_DIR)/Source/MatrixFunctions
SRC_DIRS += $(DSP_LIB_DIR)/Source/StatisticsFunctions
SRC_DIRS += $(DSP_LIB_DIR)/Source/SupportFunctions
SRC_DIRS += $(DSP_LIB_DIR)/Source/TransformFunctions
# DSP include folders
INC_DIRS += $(DSP_LIB_DIR)/Include

# Toolchain location
# TOOLCHAIN_PATH   = $(CCS_ROOT)/tools/compiler/gcc-arm-none-eabi-4_9-2015q3
TOOLCHAIN_PATH   = $(CCS_ROOT)/tools/compiler/gcc-arm-none-eabi-6-2017-q1-update
TOOLCHAIN_PREFIX = arm-none-eabi

# Various path variables
MSP_INC_DIR = $(YAHAL_DIR)/include/platform/$(PLATFORM)

# Various MSP tools
DSLITE = $(CCS_ROOT)/ccs_base/DebugServer/bin/DSLite

# Flag helper variables
FLAGS_F         = -ffunction-sections -fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables
FLAGS_M         = -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs
FLAGS_DEBUG     = -g -gdwarf-3 -gstrict-dwarf
FLAGS_WARN      = -Wall -Wextra
FLAGS_OPT       = # -Os

FLAGS_CXX       = -fno-threadsafe-statics -fno-exceptions -std=c++11
FLAGS_C         =
FLAGS_ASM       =

LN_SCRIPT_FLASH = msp432p401r.lds
FLAGS_LD        = -Wl,-T$(MSP_INC_DIR)/$(LN_SCRIPT_FLASH)
FLAGS_LD       += -Wl,-Map,$(basename $(TARGET)).map

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
DEFINES   = -D__MSP432P401R__ -DTARGET_IS_MSP432P4XX
DEFINES  += -DARM_MATH_CM4 -D__FPU_PRESENT=1
#DEFINES += -DNDEBUG

# Platform includes
###################
PLATFORM_INC_DIRS  = $(QUOTE)$(MSP_INC_DIR)$(QUOTE)
PLATFORM_INC_DIRS += $(QUOTE)$(MSP_INC_DIR)/CMSIS$(QUOTE)

# Additional rules (e.g. for upload)
####################################
define PLATFORM_RULES
.PHONY: upload
upload: $(TARGET)
	$(DSLITE) load -c $(MSP_INC_DIR)/MSP432P401R.ccxml -f $$^
endef


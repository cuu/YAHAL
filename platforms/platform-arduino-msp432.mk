#####################################
# Platform configuration for MSP432 #
#####################################

# Root folder of MSP432 package (installed by Energia IDE)
ifeq ($(FILE_UNIX_STYLE),1)
MSP432_PACKAGE  = $(HOME_DIR)/.energia15/packages/energia
else
MSP432_PACKAGE  = $(HOME_DIR)/AppData/Local/Energia15/packages/energia
endif

# Toolchain helpers
TOOLCHAIN_PATH   = $(MSP432_PACKAGE)/tools/arm-none-eabi-gcc/4.8.4-20140725
TOOLCHAIN_PREFIX = arm-none-eabi

# Various path variables
MSP_SRC_DIR    = $(MSP432_PACKAGE)/hardware/msp432/3.8.0
MSP_DSLITE_DIR = $(MSP432_PACKAGE)/tools/dslite/6.2.1.1624
# We use our own files here ...
MSP_INC_DIR    = ../YAHAL/platforms/$(PLATFORM)
#MSP_INC_DIR    = $(MSP_SRC_DIR)/system/inc

# Various MSP tools
DSLITE = $(MSP_DSLITE_DIR)/DebugServer/bin/DSLite

# Flag helper variables
FLAGS_F         = -ffunction-sections -fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables
FLAGS_M         = -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs
FLAGS_DEBUG     = -g -gdwarf-3 -gstrict-dwarf
FLAGS_WARN      = -Wall -Wextra
FLAGS_OPT       = -Os

FLAGS_CXX       = -fno-threadsafe-statics -fno-rtti -fno-exceptions -std=c++11
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
LIBS     = -lstdc++ -lgcc -lc -lm -lnosys
#LIBS     = -lstdc++_nano -lgcc -lc_nano -lm -lnosys

# Compiler defines
##################
DEFINES   = -D__MSP432P401R__ -DTARGET_IS_MSP432P4XX
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
	$(DSLITE) load -c $(MSP_DSLITE_DIR)/MSP_EXP432P401R.ccxml -f $$^
endef

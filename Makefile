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

# name of final target
TARGET = libYAHAL_$(PLATFORM).a

# folder for build artifacts
BUILD_DIR = build_$(PLATFORM)

# all source folders of our project
SRC_DIRS  = src/platform/$(PLATFORM)
SRC_DIRS += src/driver
SRC_DIRS += src/FatFs
SRC_DIRS += src/libmad
SRC_DIRS += src/task
SRC_DIRS += src/uGUI
SRC_DIRS += src/uGUI/fonts
SRC_DIRS += src/util

# all include folders
INC_DIRS  = include/platform/$(PLATFORM)
INC_DIRS += include/interface
INC_DIRS += src/platform/$(PLATFORM)
INC_DIRS += src/driver
INC_DIRS += src/FatFs
INC_DIRS += src/libmad
INC_DIRS += src/task
INC_DIRS += src/uGUI
INC_DIRS += src/uGUI/fonts
INC_DIRS += src/util

# msp432 has the additional CMSIS DSP library
ifeq ($(PLATFORM), msp432)
DSP_LIB_DIR = $(YAHAL_DIR)/src/platform/$(PLATFORM)/DSP
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
INC_DIRS += $(DSP_LIB_DIR)/Include
endif

# Optimization settings 
# FLAGS_OPT = -Ofast

include makefiles/common.mk

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

# name of final target
TARGET = libYAHAL_$(PLATFORM).a

# folder for build artifacts
BUILD_DIR = build_$(PLATFORM)

# all source folders of our project
SRC_DIRS  = src/platform/$(PLATFORM)
SRC_DIRS += src/driver
SRC_DIRS += src/util

# all include folders
INC_DIRS  = include/platform/$(PLATFORM)
INC_DIRS += include/interface
INC_DIRS += $(SRC_DIRS)


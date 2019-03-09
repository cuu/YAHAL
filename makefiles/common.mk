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
# This is the main makefile for YAHAL projects.
# It works with Linux and Windows, and can easily
# be integrated into IDEs like eclipse.
#

#############################
# OS specific configuration #
#############################

# Get the OS name (will not work for Windows)
OSNAME = $(shell uname -o 2>NUL; rm -f NUL)

# All kinds of Windows OS
ifeq ($(OS),Windows_NT)
    FILE_UNIX_STYLE = 0
    CMD_UNIX_STYLE  = 0
endif

# All typical Linux installations
ifeq ($(OSNAME),GNU/Linux)
    FILE_UNIX_STYLE = 1
    CMD_UNIX_STYLE  = 1
endif

# Cygwin uses Linux commands
# but Windows file names
ifeq ($(OSNAME),Cygwin)
    FILE_UNIX_STYLE = 0
    CMD_UNIX_STYLE  = 1
endif

ifndef FILE_UNIX_STYLE
    $(error Error: Could not detect OS.)
endif


ifeq ($(FILE_UNIX_STYLE),1)
    # Unix files and paths
    HOME_DIR  = $(HOME)
    QUOTE     = 
else
    # Windows files and paths
    HOME_DIR  = $(USERPROFILE)
    QUOTE     = "
    # " pair the quotes ... :)
endif

ifeq ($(CMD_UNIX_STYLE),1)
    # Unix commands
    RM        = rm -f
    RMDIR     = rm -rf
    MKDIR     = mkdir -p
    MAKE      = make
    ERRIGNORE = 2>/dev/null
else
    # Windows commands
    RM        =  del /F /Q
    RMDIR     = -rmdir /S /Q 
    MKDIR     = -mkdir
    MAKE      = "$(YAHAL_DIR)/tools/make.exe"
    ERRIGNORE = 2>NUL || exit 0
endif

##########################
# Platform configuration #
##########################

ifndef PLATFORM
  $(error Error: No platform specified.)
endif

PLATFORM_FILE = $(YAHAL_DIR)/makefiles/platform-$(PLATFORM).mk
ifneq ("$(wildcard $(PLATFORM_FILE))","")
  include $(PLATFORM_FILE)
else
  $(error Platform file makefiles/platform-$(PLATFORM).mk not existing!)
endif

#####################
## GENERIC SECTION ##
#####################

# Utility to control output (detailed if VERBOSE defined).
ifdef VERBOSE
HIDE :=
else
HIDE := @
endif

# all source files
SOURCES += $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
SOURCES += $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c  ))
SOURCES += $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.S  ))
# all objects files
OBJECTS  = $(foreach obj, $(SOURCES), $(BUILD_DIR)/$(notdir $(obj)).o)
# all dependency files
DEPS     = $(OBJECTS:.o=.d)
# all include flags
INCLUDES += $(foreach dir, $(INC_DIRS), -I$(QUOTE)$(dir)$(QUOTE)) 
INCLUDES += $(foreach dir, $(PLATFORM_INC_DIRS), -I$(QUOTE)$(dir)$(QUOTE))

#####################
### RULES section ###
#####################

# Indicate to make which targets are not files
.PHONY: all clean directories

all: directories $(TARGET)

# rule for executable targets
%.out : $(OBJECTS) $(LINK_LIBS) $(LINK_DEPS)
	@echo "LD  $@"
	$(HIDE) $(LD) $(LDFLAGS) -Wl,--start-group $(OBJECTS) $(LINK_LIBS) $(LIBS) -Wl,--end-group -o $@

# rule for library targets
%.a :   $(OBJECTS)
	@echo "AR  $@"
	$(HIDE) $(AR) cru $@ $^
	$(HIDE) $(RANLIB) $@

# compiler rules
define compileRules
$(BUILD_DIR)/%.cpp.o : $(1)/%.cpp
	@echo "C++ $$(notdir $$<)"
	$$(eval EXTRA_FLAGS := $$(shell cat $$(dir $$<)CPPFLAGS 2>/dev/null))
	$(HIDE) $$(CXX) $$(DEFINES) $$(INCLUDES) $$(CXXFLAGS) $$(EXTRA_FLAGS) -c -o $$@ $(QUOTE)$$<$(QUOTE) -MMD

$(BUILD_DIR)/%.c.o : $(1)/%.c
	@echo "C   $$(notdir $$<)"
	$$(eval EXTRA_FLAGS := $$(shell cat $$(dir $$<)CFLAGS 2>/dev/null))
	$(HIDE) $$(CC)  $$(DEFINES) $$(INCLUDES) $$(CFLAGS) $$(EXTRA_FLAGS) -c -o $$@ $(QUOTE)$$<$(QUOTE) -MMD

$(BUILD_DIR)/%.S.o : $(1)/%.S
	@echo "ASM $$(notdir $$<)"
	$$(eval EXTRA_FLAGS := $$(shell cat $$(dir $$<)ASMFLAGS 2>/dev/null))
	$(HIDE) $$(CC)  $$(DEFINES) $$(INCLUDES) $$(ASMFLAGS) $$(EXTRA_FLAGS) -c -o $$@ $(QUOTE)$$<$(QUOTE) -MMD
endef
$(foreach srcdir, $(SRC_DIRS), $(eval $(call compileRules, $(srcdir))))

# rules for link-in libraries
define libraryRule
$(1):
	@echo "Building $$(notdir $(1))"
	$(HIDE) $(MAKE) PLATFORM=$(PLATFORM) -C $$(dir $(1)) all
endef
$(foreach lib, $(LINK_LIBS), $(eval $(call libraryRule, $(lib))))

# create needed directories
directories:
	$(HIDE) $(MKDIR) $(BUILD_DIR) $(ERRIGNORE)

# 'clean up'-rule
clean:
	@echo "Cleaning files ..."
	$(HIDE) $(RM) $(basename $(TARGET)).* $(ERRIGNORE)
	$(HIDE) $(RMDIR) $(BUILD_DIR) $(ERRIGNORE)

# include the platform-specific rules
$(eval $(PLATFORM_RULES))

# include the dependency files
-include $(DEPS)


##########################
# Platform configuration #
##########################

ifndef PLATFORM
  $(error Error: No platform specified.)
endif

PLATFORM_FILE = platforms/platform-$(PLATFORM).mk
ifneq ("$(wildcard $(PLATFORM_FILE))","")
  include $(PLATFORM_FILE)
else
  $(error Platform file platform/platform-$(PLATFORM).mk not existing!)
endif

#####################
## GENERIC SECTION ##
#####################

# name of final target
TARGET = libYAHAL.a

# folder for build artifacts
BUILD_DIR = build

# OS specific part
RM    = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p

# Utility to control output (detailed if VERBOSE defined).
ifdef VERBOSE
HIDE :=
myecho := @true
else
HIDE := @
myecho := @echo
endif

# all source folders of our project
SRC_DIRS = src/driver src/util ${PLATFORM_SRC_DIR}
# all source files
SOURCES  = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
# all objects files
OBJECTS  = $(foreach obj, $(SOURCES:.cpp=.o), $(BUILD_DIR)/$(notdir $(obj)))  
# all dependency files
DEPS     = $(OBJECTS:.o=.d)

#OBJECTS   = $(SOURCES:.cpp=.o)
#OBJECTS   = $(foreach obj, $(SOURCES), $(BUILD_DIR)/$(notdir $(obj)):.cpp=.o)

INCLUDES  = -Iinclude/interface $(foreach dir, $(SRC_DIRS), -I$(dir)) 
INCLUDES += $(PLATFORM_INCLUDES)

#####################
### RULES section ###
#####################

all: directories $(TARGET)

# rule for the main target: Link the library
$(TARGET) : $(OBJECTS)
	$(myecho) "AR  $@"
	$(HIDE) $(AR) qc  $@ $^
	$(HIDE) $(RANLIB) $@

# compiler rules
define compileRules
$(BUILD_DIR)/%.o : $(1)/%.cpp
	$(myecho) "C++ $$<"
	$(HIDE) $$(CXX) $$(DEFINES) $$(INCLUDES) $$(CXXFLAGS) -c -o $$@ $$< -MMD

$(BUILD_DIR)/%.o : $(1)/%.c
	$(myecho) "C   $$<"
	$(HIDE) $$(CC)  $$(DEFINES) $$(INCLUDES) $$(CFLAGS) -c -o $$@ $$< -MMD
endef
$(foreach srcdir, $(SRC_DIRS), $(eval $(call compileRules, $(srcdir))))

# create needed directories
directories:
	$(HIDE) $(MKDIR) $(BUILD_DIR)

# 'clean up'-rule
clean:
	$(myecho) "Cleaning files ..."
	$(HIDE) $(RM) $(TARGET)
	$(HIDE) $(RMDIR) $(BUILD_DIR)

# include the dependency files
-include $(DEPS)


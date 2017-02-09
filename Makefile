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

#########################
# Configuration section #
#########################

# name of final target
TARGET = libYAHAL.a

# folder for build artifacts
BUILD_DIR = build

# all source folders of our project
SRC_DIRS = src/driver src/util src/platform/$(PLATFORM)

# include dirs, all src dirs are automatically added
INCLUDES  = -Iinclude/interface


#####################
## GENERIC SECTION ##
#####################

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

# all source files
SOURCES  = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
SOURCES += $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c  ))
# all objects files
OBJECTS1 = $(SOURCES:.cpp=.o)
OBJECTS  = $(foreach obj, $(OBJECTS1:.c=.o), $(BUILD_DIR)/$(notdir $(obj)))  
# all dependency files
DEPS     = $(OBJECTS:.o=.d)


INCLUDES += $(foreach dir, $(SRC_DIRS), -I$(dir)) 
INCLUDES += $(PLATFORM_INCLUDES)

#####################
### RULES section ###
#####################

# Indicate to make which targets are not files
.PHONY: all clean directories

all: directories $(TARGET)

# rule for executable targets
%.out : $(OBJECTS)
	$(myecho) "LD  $@"
	$(HIDE) $(LD) $(DEFINES) $(LDFLAGS) -o $@ $^

# rule for library targets
%.a : $(OBJECTS)
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
	$(HIDE) $(RM) $(basename $(TARGET)).*
	$(HIDE) $(RMDIR) $(BUILD_DIR)


################################
# Rules for specific platform  #
################################
ifeq ("$(PLATFORM)", "msp432")
DSLITE_DIR = $(HOME)/.ti/TICloudAgent/loaders/ccs_base/DebugServer/bin
.PHONY: upload
upload: $(TARGET)
	$(DSLITE_DIR)/DSLite load -c $(CURDIR)/platforms/MSP432P401R.ccxml -f $^
endif


# include the dependency files
-include $(DEPS)


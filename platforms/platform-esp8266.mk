######################################
# Platform configuration for ESP8266 #
######################################

# Root folder of ESP8266 package (installed by Arduino IDE)
ifeq ($(FILE_UNIX_STYLE),1)
ESP8266_PACKAGE  = $(HOME_DIR)/.arduino15/packages/esp8266
else
ESP8266_PACKAGE  = $(HOME_DIR)/AppData/Local/Arduino15/packages/esp8266
endif

# Toolchain helpers
TOOLCHAIN_PATH   = $(ESP8266_PACKAGE)/tools/xtensa-lx106-elf-gcc/1.20.0-26-gb404fb9-2
TOOLCHAIN_PREFIX = xtensa-lx106-elf

# Various path variables
ESP_SRC_DIR     = $(ESP8266_PACKAGE)/hardware/esp8266/2.3.0
ESP_CORE_DIR    = $(ESP_SRC_DIR)/cores/esp8266
ESP_LIB_DIR     = $(ESP_SRC_DIR)/libraries
ESP_VARIANTS_DIR= $(ESP_SRC_DIR)/variants
ESP_SDK_DIR     = $(ESP_SRC_DIR)/tools/sdk

# Various ESP tools 
ESP_TOOL        = $(ESP8266_PACKAGE)/tools/esptool/0.4.9/esptool
MKSPIFFS        = $(ESP8266_PACKAGE)/tools/mkspiffs/0.1.2/mkspiffs
ESP_BOOTLOADER  = $(ESP_SRC_DIR)/bootloaders/eboot/eboot.elf

# Flag helper variables
FLAGS_F         = -falign-functions=4 -ffunction-sections -fdata-sections
FLAGS_M         = -mlongcalls -mtext-section-literals
FLAGS_DEBUG     = -g
FLAGS_WARN      = -w
# -Wall -Wextra
FLAGS_OPT       = -Os

FLAGS_CXX       = -fno-exceptions -fno-rtti -std=c++11
FLAGS_C         = -Wpointer-arith -Wno-implicit-function-declaration 
FLAGS_C        += -Wl,-EL -fno-inline-functions -nostdlib -std=gnu99
FLAGS_ASM       = -x assembler-with-cpp

FLAGS_LD        = -nostdlib -Wl,--no-check-sections -Wl,-static -Wl,--gc-sections 
FLAGS_LD       += -Wl,-wrap,system_restart_local -Wl,-wrap,register_chipv6_phy -u call_user_start
FLAGS_LD       += -T$(ESP_FLASH_SCRIPT)
FLAGS_LD       += -Wl,-Map,$(basename $(TARGET)).map
FLAGS_LD       += -L$(QUOTE)$(ESP_SDK_DIR)/lib$(QUOTE)
FLAGS_LD       += -L$(QUOTE)$(ESP_SDK_DIR)/ld$(QUOTE)

# spiffs stuff
SPIFFS_FILES    = $(wildcard $(SPIFFS_DIR)/*)
SPIFFS_BIN      = $(BUILD_DIR)/spiffs.bin


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
LDFLAGS  = $(FLAGS_DEBUG) $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_LD)
LIBS     = -lm -lgcc -lhal -lphy -lpp -lnet80211 -lwpa -lcrypto -lmain \
           -lwps -laxtls -lsmartconfig -lmesh -lwpa2 -llwip_gcc -lstdc++

# Compiler defines
##################
DEFINES  = -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ -DF_CPU=80000000L -DLWIP_OPEN_SRC -DARDUINO=10609
DEFINES += -DARDUINO_ESP8266_ESP01 -DARDUINO_ARCH_ESP8266 -DARDUINO_BOARD=\"ESP8266_ESP01\" -DESP8266 
#DEFINES += -DNDEBUG

# Platform includes
###################
PLATFORM_INC_DIRS  = $(ESP_SDK_DIR)/include
PLATFORM_INC_DIRS += $(ESP_SDK_DIR)/lwip/include
PLATFORM_INC_DIRS += $(ESP_VARIANTS_DIR)/generic

# Additional rules (e.g. for upload)
####################################
define PLATFORM_RULES
.PHONY: upload
upload: $$(TARGET)
	@echo "Uploading program"
	$(HIDE) $(ESP_TOOL) -eo $(ESP_BOOTLOADER) \
			    -bo $$(TARGET).bin \
			    -bm $(ESP_FLASH_MODE) -bf $(ESP_FLASH_FREQ) -bz $(ESP_FLASH_SIZE) \
			    -bs .text -bp 4096 -ec -eo $$(TARGET) \
			    -bs .irom0.text -bs .text -bs .data -bs .rodata -bc -ec
	$(HIDE) $(ESP_TOOL) -v -cd $(ESP_RESET_MODE) -cp $(ESP_PORT) -cb $(ESP_BAUD) \
			       -ca 0x000000 -cf $$(TARGET).bin

$(SPIFFS_BIN): $(SPIFFS_FILES)
	@echo "Creating SPIFFS image $(SPIFFS_BIN)"
	$(HIDE) $(MKDIR) $(BUILD_DIR) $(ERRIGNORE)
	$(HIDE) $(MKSPIFFS) -c $(SPIFFS_DIR) \
			    -b $(SPIFFS_BLOCKSIZE) -p $(SPIFFS_PAGESIZE) \
			    -s $(SPIFFS_SIZE) $(SPIFFS_BIN)

.PHONY: spiffs_upload
spiffs_upload: $(SPIFFS_BIN)
	@echo "Uploading SPIFFS image $(SPIFFS_BIN)"
	$(HIDE) $(ESP_TOOL) -v -cd $(ESP_RESET_MODE) -cp $(ESP_PORT) -cb $(ESP_BAUD) \
			       -ca $(SPIFFS_START)  -cf $(SPIFFS_BIN)
endef

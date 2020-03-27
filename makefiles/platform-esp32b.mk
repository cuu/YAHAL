####################################
# Platform configuration for ESP32 #
####################################

# Root folder of esp-idf package and toolchain
ifeq ($(FILE_UNIX_STYLE),1)
ESP_IDF_DIR    = $(HOME_DIR)/git/esp-idf
TOOLCHAIN_PATH = /usr/local/gcc-xtensa-esp32-elf
else
ESP_IDF_DIR    = $(HOME_DIR)/git/esp-idf
TOOLCHAIN_PATH = /usr/local/gcc-xtensa-esp32-elf
endif

# Toolchain helpers
TOOLCHAIN_PREFIX = xtensa-esp32-elf

# Various path variables
ESP_COMP_DIR     = $(ESP_IDF_DIR)/components
LD_SCRIPT_DIR	 = $(ESP_COMP_DIR)/esp32/ld
ESP_LIB_DIR	 	 = $(ESP_COMP_DIR)/esp32/lib

#ESP_CORE_DIR    = $(ESP_SRC_DIR)/cores/esp8266
#ESP_LIB_DIR     = $(ESP_SRC_DIR)/libraries
#ESP_VARIANTS_DIR= $(ESP_SRC_DIR)/variants
#ESP_SDK_DIR     = $(ESP_SRC_DIR)/tools/sdk

# Various ESP tools
ESP_TOOL		 = $(ESP_COMP_DIR)/esptool_py/esptool/esptool.py 
#ESP_TOOL        = $(ESP8266_PACKAGE)/tools/esptool/0.4.13/esptool
#MKSPIFFS        = $(ESP8266_PACKAGE)/tools/mkspiffs/0.1.2/mkspiffs
#ESP_BOOTLOADER  = $(ESP_SRC_DIR)/bootloaders/eboot/eboot.elf

# Flag helper variables
FLAGS_F         = -ffunction-sections -fdata-sections -fstrict-volatile-bitfields 
FLAGS_M         = -mlongcalls
FLAGS_DEBUG     = -ggdb
FLAGS_WARN      = -w -Wall -Werror=all -Wextra
# -Wall -Wextra
FLAGS_OPT       = -Og
FLAGS_CXX       = -fno-exceptions -fno-rtti -std=c++11
FLAGS_C         = -Wall -Werror=all -Wextra
FLAGS_C        += -Wno-error=unused-function
FLAGS_C        += -Wno-error=unused-but-set-variable
FLAGS_C        += -Wno-error=unused-variable 
FLAGS_C        += -Wno-error=deprecated-declarations 
FLAGS_C        += -Wno-unused-parameter 
FLAGS_C        += -Wno-sign-compare
FLAGS_C        += -nostdlib
FLAGS_ASM       = -x assembler-with-cpp

FLAGS_LD       += -nostdlib -u call_user_start_cpu0 -Wl,--gc-sections -Wl,-static 
FLAGS_LD       += -Wl,-Map,$(basename $(TARGET)).map

# spiffs stuff
#SPIFFS_FILES    = $(wildcard $(SPIFFS_DIR)/*)
#SPIFFS_BIN      = $(BUILD_DIR)/spiffs.bin

# Linker script stuff
FLAGS_LD		+= -L $(LD_SCRIPT_DIR) 
FLAGS_LD		+= -T esp32_out.ld -u ld_include_panic_highint_hdl
FLAGS_LD		+= -T esp32.common.ld
FLAGS_LD		+= -T esp32.rom.ld 
FLAGS_LD		+= -T esp32.peripherals.ld 
FLAGS_LD		+= -T esp32.rom.spiram_incompatible_fns.ld 

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

# Component Libraries
##################### 
FLAGS_LD 	+= -L$(YAHAL_DIR)/../esp32/libesp32_idf/build
#LIBS		+= -lapp_trace 
LIBS		+= -lapp_update 
#LIBS		+= -lbootloader_support 
#LIBS		+= -lbt 
#LIBS		+= -lconsole 
#LIBS		+= -lcoap 
#LIBS		+= -lcxx -u __cxa_guard_dummy -u __cxx_fatal_exception 
LIBS		+= -ldriver 
LIBS		+= -lesp32 
#LIBS		+= -lesp_adc_cal 
#LIBS		+= -lesp-tls 
#LIBS		+= -lethernet 
#LIBS		+= -lexpat 
#LIBS		+= -lfatfs 
LIBS		+= -lfreertos -Wl,--undefined=uxTopUsedPriority 
LIBS		+= -lheap 
#LIBS		+= -lidf_test 
#LIBS		+= -ljsmn 
#LIBS		+= -ljson 
#LIBS		+= -llibsodium
LIBS		+= -llog 
#LIBS		+= -llwip 
#LIBS		+= -lmbedtls
#LIBS		+= -lmdns 
#LIBS		+= -lmicro-ecc 
LIBS		+= -lnewlib 
#LIBS		+= -lnghttp 
#LIBS		+= -lnvs_flash 
#LIBS		+= -lopenssl 
LIBS		+= -lpthread 
#LIBS		+= -lsdmmc 
LIBS		+= -lsoc 
#LIBS		+= -lspiffs 
LIBS		+= -lspi_flash 
#LIBS		+= -ltcpip_adapter
#LIBS		+= -lulp 
LIBS		+= -lvfs 
#LIBS		+= -lwear_levelling 
#LIBS		+= -lwpa_supplicant 
#LIBS		+= -lxtensa-debug-module 
 	
# Binary libraries
##################
FLAGS_LD 	+= -L$(ESP_LIB_DIR) -L$(ESP_LIB_DIR)/..
LIBS		+= -lcore -lrtc -lnet80211 -lpp -lwpa -lsmartconfig
LIBS		+= -lcoexist -lwps -lwpa2 -lespnow -lphy -lmesh -lhal 

# Standard Libraries (get libc/libm from own newlib!
####################################################
FLAGS_LD 	+= -L $(ESP_COMP_DIR)/newlib/lib
LIBS		+= -lgcc -lstdc++ -lgcov -lc -lm

# Compiler defines
##################
DEFINES  	+= -DESP_PLATFORM -DIDF_VER=\"v3.1-dev-802-g5d3b26e-dirty\"
DEFINES 	+= -DWITH_POSIX   -DMBEDTLS_CONFIG_FILE='"mbedtls/esp_config.h"' 
DEFINES 	+= -DHAVE_CONFIG_H
#DEFINES 	+= -DNDEBUG

# Platform includes
###################
#PLATFORM_INC_DIRS  = $(ESP_SDK_DIR)/include
#PLATFORM_INC_DIRS += $(ESP_SDK_DIR)/lwip2/include
#PLATFORM_INC_DIRS += $(ESP_VARIANTS_DIR)/generic

# Additional rules (e.g. for upload)
####################################
define PLATFORM_RULES
.PHONY: flash
flash: $$(TARGET)
	@echo "Generating binary..."
	$(HIDE) python $(ESP_TOOL) \
		--chip esp32 elf2image --flash_mode "dio" \
		--flash_freq "40m" --flash_size "2MB" \
		-o $$(TARGET).bin $$(TARGET)
	@echo "Uploading program..."
	$(HIDE) python $(ESP_TOOL) \
		--chip esp32 \
		--port /dev/ttyUSB0 --baud 921600 \
		--before default_reset --after hard_reset write_flash -z \
		--flash_mode dio --flash_freq 40m --flash_size detect \
		0x1000 bootloader.bin 0x10000 $$(TARGET).bin 0x8000 partitions_singleapp.bin 

#$(SPIFFS_BIN): $(SPIFFS_FILES)
#	@echo "Creating SPIFFS image $(SPIFFS_BIN)"
#	$(HIDE) $(MKDIR) $(BUILD_DIR) $(ERRIGNORE)
#	$(HIDE) $(MKSPIFFS) -c $(SPIFFS_DIR) \
#			    -b $(SPIFFS_BLOCKSIZE) -p $(SPIFFS_PAGESIZE) \
#			    -s $(SPIFFS_SIZE) $(SPIFFS_BIN)

#.PHONY: spiffs_upload
#spiffs_upload: $(SPIFFS_BIN)
#	@echo "Uploading SPIFFS image $(SPIFFS_BIN)"
#	$(HIDE) $(ESP_TOOL) -v -cd $(ESP_RESET_MODE) -cp $(ESP_PORT) -cb $(ESP_BAUD) \
#			       -ca $(SPIFFS_START)  -cf $(SPIFFS_BIN)
endef


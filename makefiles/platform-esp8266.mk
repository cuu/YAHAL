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
TOOLCHAIN_PATH   = $(ESP8266_PACKAGE)/tools/xtensa-lx106-elf-gcc/2.5.0-4-b40a506
TOOLCHAIN_PREFIX = xtensa-lx106-elf

# Various path variables
ESP_SRC_DIR     = $(ESP8266_PACKAGE)/hardware/esp8266/2.7.4
ESP_CORE_DIR    = $(ESP_SRC_DIR)/cores/esp8266
ESP_LIB_DIR     = $(ESP_SRC_DIR)/libraries
ESP_VARIANTS_DIR= $(ESP_SRC_DIR)/variants
ESP_SDK_DIR     = $(ESP_SRC_DIR)/tools/sdk

# Various ESP tools 
PYTHON          = $(ESP8266_PACKAGE)/tools/python3/3.7.2-post1/python3
MKSPIFFS        = $(ESP8266_PACKAGE)/tools/mkspiffs/2.5.0-4-b40a506/mkspiffs
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
FLAGS_LD       += -Wl,-wrap,system_restart_local -Wl,-wrap,spi_flash_read 
FLAGS_LD       += -u call_user_start -u _printf_float -u _scanf_float
FLAGS_LD       += -T$(ESP_FLASH_SCRIPT)
FLAGS_LD       += -Wl,-Map,$(basename $(TARGET)).map
FLAGS_LD       += -L$(QUOTE)$(ESP_SDK_DIR)/lib$(QUOTE)  
FLAGS_LD       += -L$(QUOTE)$(ESP_SDK_DIR)/lib/NONOSDK22x_190703$(QUOTE)  
FLAGS_LD       += -L$(QUOTE)$(ESP_SDK_DIR)/ld$(QUOTE)
FLAGS_LD       += -L$(BUILD_DIR)
FLAGS_LD       += -L$(QUOTE)$(ESP_SDK_DIR)/libc/xtensa-lx106-elf/lib$(QUOTE)

# Compiler defines
##################
DEFINES  = -D__ets__
DEFINES += -DICACHE_FLASH
DEFINES += -U__STRICT_ANSI__
DEFINES += -DNONOSDK22x_190703=1
DEFINES += -DF_CPU=80000000L
DEFINES += -DLWIP_OPEN_SRC -DTCP_MSS=536 -DLWIP_FEATURES=1 -DLWIP_IPV6=0 
DEFINES += -DARDUINO=10808
DEFINES += -DARDUINO_ESP8266_GENERIC
DEFINES += -DARDUINO_ARCH_ESP8266
DEFINES += -DARDUINO_BOARD=\"ESP8266_GENERIC\"
DEFINES += -DESP8266
#DEFINES += -DNDEBUG

# Platform includes
###################
PLATFORM_INC_DIRS  = $(ESP_SDK_DIR)/include
PLATFORM_INC_DIRS += $(ESP_SDK_DIR)/lwip2/include
PLATFORM_INC_DIRS += $(ESP_VARIANTS_DIR)/generic
PLATFORM_INC_DIRS += $(ESP_SDK_DIR)/libc/xtensa-lx106-elf/include 

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
LIBS     = -lhal -lphy -lpp -lnet80211 -llwip2-536-feat -lwpa -lcrypto -lmain -lwps \
           -lbearssl -laxtls -lespnow -lsmartconfig -lairkiss -lwpa2 -lstdc++ -lm -lc -lgcc

# Add linker script source file
LINK_DEPS += $(BUILD_DIR)/local.eagle.app.v6.common.ld

# Additional rules (e.g. for upload)
####################################
define PLATFORM_RULES

# Generate ld script
$(BUILD_DIR)/local.eagle.app.v6.common.ld : $(ESP_SDK_DIR)/ld/eagle.app.v6.common.ld.h
	@echo "LDS $$(notdir $$<)"
	$(HIDE) $(CC) -CC -E -P -DVTABLES_IN_FLASH $$< -o $$@

# Generate SPIFFS binary
$(BUILD_DIR)/spiffs.bin: $(wildcard $(SPIFFS_DIR)/*) 
	@echo "Creating SPIFFS image $(SPIFFS_BIN)"
	$(HIDE) $(MKDIR) $(BUILD_DIR) $(ERRIGNORE)
	$(HIDE) $(MKSPIFFS) -c $(SPIFFS_DIR)      -b $(SPIFFS_BLOCKSIZE) \
	                    -p $(SPIFFS_PAGESIZE) -s $(SPIFFS_SIZE) $$@

.PHONY: upload
upload: $$(TARGET)
	@echo "Uploading programmer"
	$(HIDE) make -C ../../msp432+wifiTick/WifiTick-Programmer upload
	@echo "Uploading program"
	$(HIDE) $(PYTHON) $(ESP_SRC_DIR)/tools/elf2bin.py --eboot $(ESP_BOOTLOADER) \
	--app $$(TARGET) --flash_mode dout --flash_freq 40 --flash_size 4M          \
	--path $(TOOLCHAIN_PATH)/bin --out $$(TARGET).bin
	$(HIDE) $(PYTHON) $(ESP_SRC_DIR)/tools/upload.py     \
	--chip esp8266 --port $(ESP_PORT) --baud $(ESP_BAUD) --after no_reset\
	write_flash 0x0 $$(TARGET).bin

.PHONY: spiffs_upload
spiffs_upload: $(SPIFFS_BIN)
	$(HIDE) $(PYTHON) $(ESP_SRC_DIR)/tools/upload.py     \
	--chip esp8266 --port $(ESP_PORT) --baud $(ESP_BAUD) --after no_reset \
	write_flash $(SPIFFS_START) $(BUILD_DIR)/spiffs.bin --end 

.PHONY: erase_flash
erase_flash: $(SPIFFS_BIN)
	$(HIDE) $(PYTHON) $(ESP_SRC_DIR)/tools/upload.py     \
	--chip esp8266 --port $(ESP_PORT) --baud $(ESP_BAUD) --after no_reset \
	erase_flash --end 

endef

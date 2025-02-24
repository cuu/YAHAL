//
// Created by andreas on 22.02.25.
//

#ifndef RP2350_LAUNCHPAD_BOARD_H
#define RP2350_LAUNCHPAD_BOARD_H

#define S1_GPIO 28
#define S2_GPIO 29
#define LED_RED_GPIO 38
#define LED_RGB_GPIO 39
#define LED_RGB_COUNT 8

#define PS_RAM_CS_GPIO 0

// Use PSRAM without copying code/data or zeroing
#define PSRAM __attribute__((section(".ps_noload")))

// Use PSRAM and initialize with zeros
#define PSRAM_BSS __attribute__((section(".ps_bss")))

// Use PSRAM and copy code/data
#define PSRAM_LOAD __attribute__((section(".ps_data")))

#endif // RP2350_LAUNCHPAD_BOARD_H

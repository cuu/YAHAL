#ifndef _YAHAL_CONFIG_RP2350_H_
#define _YAHAL_CONFIG_RP2350_H_

#include <cstdint>

//////////////////////////////////////////
// YAHAL Parameters for RP2350 platform //
//////////////////////////////////////////

// task configuration
/////////////////////

// Number of cores
#define NUMBER_OF_CORES 2
// Tick frequency in Hz
#define TICK_FREQUENCY 1000
// Default stack size in bytes
#define DEFAULT_STACK_SIZE 1024
// Default task priority (1..N, 1 lowest)
#define DEFAULT_PRIORITY 100
// Default magic number in stack area
#define STACK_MAGIC 0xA5
// Define to check stack overflow
#define CHECK_STACK_OVERFLOW
// Define to use simple round-robin without priorities
#undef SIMPLE_ROUND_ROBIN

#endif // _YAHAL_CONFIG_RP2350_H_

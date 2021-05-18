// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
// This is a simulator for a PDP-8, a minicomputer
// build by Digital Equipment Corporation in the
// 1960s. It was a 12-bit computer with 4k-words
// core memory (every bit was stored in a small
// magnetic core) and a compact instruction set.
// The core memory is pre-loaded with FOCAL-69,
// a simple interpreter language. A manual of this
// language can be found in the doc folder.
//
// Use a terminal on the back-channel UART to
// program a PDP-8 in FOCAL-69!

#include "Memory.h"
#include "CPU.h"
#include "Devices.h"
#include "Device_TTI.h"
#include "Device_TTO.h"

#include "gpio_msp432.h"
#include "uart_msp432.h"

int main() {

    // Use the YAHAL UART class to initialize
    // our back-channel UART. Note that the UART
    // parameters will not be set up until some
    // characters have been sent.
    uart_msp432 uart;
    uart.puts("\r\n\r\n***** DEC PDP-8 Simulator *****\r\n\r\n");

    // The PDP-8 CPU writes the AC register to P2 so
    // that we can 'see' the PDP-8 CPU working. So
    // initialize the RGB-LEDs as outputs.
    gpio_msp432::inst.gpioMode(PORT_PIN(2,0), GPIO::OUTPUT);
    gpio_msp432::inst.gpioMode(PORT_PIN(2,1), GPIO::OUTPUT);
    gpio_msp432::inst.gpioMode(PORT_PIN(2,2), GPIO::OUTPUT);

    // Add some PDP devices (Teletype input/output)
    Devices devices;
    devices.addDevice(new Device_TTI(uart)); // Add a Keyboard Device
    devices.addDevice(new Device_TTO(uart)); // Add a Teletype Device

    Memory m;
    CPU cpu(m, devices);
    cpu.run();
}


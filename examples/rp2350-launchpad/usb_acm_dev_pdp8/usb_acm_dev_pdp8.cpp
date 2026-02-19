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
// The core memory is preloaded with FOCAL-69,
// a simple interpreter language. A manual of this
// language can be found in the doc folder.
//
// Use a terminal on the CDC ACM device to program
// a PDP-8 in FOCAL-69 :)
// You have to use the lower USB-C target interface
// and power the RP2350 lauchpad from there!
//
#include <usb_configuration.h>
#include <usb_device.h>
#include <usb_device_controller.h>
#include <usb_ms_compat_descriptor.h>
#include <usb_dcd.h>

#include "Memory.h"
#include "CPU.h"
#include "Devices.h"
#include "Device_TTI.h"
#include "Device_TTO.h"
#include "task.h"

int main() {

    // USB device: Root object of USB descriptor tree
    usb_device device;
    device.set_bcdUSB         (0x0210);
    device.set_bMaxPacketSize0(64);
    device.set_idVendor       (0x04A0);
    device.set_idProduct      (0x008E);
    device.set_Manufacturer   ("Digital Equipment Corp.");
    device.set_Product        ("PDP8 Demo");

    // Put generic USB Device Controller on top
    usb_device_controller controller {usb_dcd::inst(), device};

    // Add USB BOS descriptor
    usb_ms_compat_descriptor ms_compat {controller, device};

    // USB configuration descriptor
    usb_configuration config {device};
    config.set_bConfigurationValue(1);
    config.set_bmAttributes( { .remote_wakeup = 0,
                               .self_powered  = 0,
                               .bus_powered   = 1 } );
    config.set_bMaxPower_mA(100);

    usb_cdc_acm_device acm_device(controller, config);

    // Enable USB device and wait for USB enumeration
    usb_dcd::inst().pullup_enable(true);
    while (!controller.active_configuration) ;

    // Add some PDP devices (Teletype input/output)
    Devices devices;
    devices.addDevice(new Device_TTI(acm_device)); // Add a Keyboard Device
    devices.addDevice(new Device_TTO(acm_device)); // Add a Teletype Device

    // Wait for keypress...
    while(!acm_device.available()) task::sleep_ms(100);

    uint8_t message[] = "\r\n\r\n***** DEC PDP-8 Simulator *****\r\n\r\n";
    acm_device.write(message, sizeof(message));

    Memory m;
    CPU cpu(m, devices);
    cpu.run(); // will not return
}

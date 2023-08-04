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
//  This file defines a generic and abstract C++
//  interface ...

#ifndef _USB_DEVICE_INTERFACE_H_
#define _USB_DEVICE_INTERFACE_H_

#include <stdint.h>
#include <functional>
#include <cassert>
using std::function;

#include "usb_common.h"
#include "usb_configuration.h"

class usb_device_interface {
public:
    // The Device descriptor
    usb_device_descriptor descriptor;

    usb_device_interface(const usb_device_descriptor & desc) : _configurations{ nullptr} {
        descriptor = desc;
    }

    virtual void init() = 0;
    virtual void pullup_enable() = 0;
    virtual void pullup_disable() = 0;
    virtual void irq_enable() = 0;
    virtual void irq_disable() = 0;
    virtual void set_address(uint8_t addr) = 0;

    static function<void(usb_setup_packet * packet)> handle_setup_received;        
    static function<void()> handle_bus_reset;

    void add_configuration(usb_configuration & config) {
        int i=0;
        for (i=0; i < 5; ++i) {
            if (!_configurations[i]) {
                _configurations[i] = &config;
                break;
            }
        }
        assert(i != 5);
        descriptor.bNumConfigurations = i+1;
    }

private:
    usb_configuration * _configurations[5];
    
protected:
    virtual ~usb_device_interface() = default;

};

#endif // _USB_DEVICE_INTERFACE_H_


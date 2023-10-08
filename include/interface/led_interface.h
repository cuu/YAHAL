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
//  interfaces for different kinds of LEDs

#ifndef _LED_INTERFACE_H_
#define _LED_INTERFACE_H_

#include <cstdint>

// Plain one-color LED, typically connected to a GPIO pin
class led_interface {
public:
    // Switch LED on and off
    virtual void on()  = 0;
    virtual void off() = 0;
    virtual void toggle() = 0;

    // Assignment operator for easier access
    inline void operator = (bool v) {
        if (v) on(); else off();
    }
    
protected:
    virtual ~led_interface() = default;
};

// Plain one-color LED with brigthness control
class led_dim_interface : public led_interface {
public:
    // Set LED brightness (0 min, 255 max) 
    virtual void set_brightness(uint8_t b) = 0;

    // Use the pre-defined bool assignment operator
    using led_interface::operator= ;

protected:
    virtual ~led_dim_interface() = default;
};

// RGB LED
class led_rgb_interface : public led_interface {
public:
    // Set color of LED (24-bit RGB value)
    virtual void set_color(uint32_t rgb) = 0;
    
    // Set the color of the LED if it is used as
    // a plain on/off LED (24-bit RGB value)
    virtual void set_on_color(uint32_t rgb) = 0;

    // Use the pre-defined bool assignment operator
    using led_interface::operator= ;

    // RGB Assignment operator for easier access. We
    // use int as parameter type, so we don't need
    // a cast when writing rgb_led = 0x121212;
    inline void operator = (int rgb) {
        set_color(rgb);
    }

protected:
    virtual ~led_rgb_interface() = default;
};

#endif // _LED_INTERFACE_H_

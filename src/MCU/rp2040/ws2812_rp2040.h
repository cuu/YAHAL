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
// Driver class for WS2812-based LED strips
//
#ifndef _WS2812_RP2040_H_
#define _WS2812_RP2040_H_

#include <cstdint>
#include <cassert>
#include "led_interface.h"
#include "gpio_rp2040.h"
#include "pio_rp2040.h"

class ws2812_rp2040 {
public:
    // Nested LED class to control a single LED
    class LED : public led_rgb_interface {
      friend class ws2812_rp2040;
      public:
        void on() override;
        void off() override;
        void toggle() override;
        bool is_on() override;
        void set_color(uint32_t rgb) override;
        void set_on_color(uint32_t rgb) override;

      private:
        ws2812_rp2040 * _ws2812_rp2040 {nullptr};
        uint16_t _index    {0};
        uint32_t _color    {0};
        uint32_t _on_color {0x080000}; // Default dark red
    };

    // CTOR takes the GPIO number connected to the
    // WS2812 LEDs and the size of the LED array
    ws2812_rp2040(gpio_pin_t led_pin, uint16_t size);

    virtual ~ws2812_rp2040();

    // Index operator to access a single LEDs
    inline led_rgb_interface & operator[](uint16_t i) {
        assert(i < _size);
        return _leds[i];
    }

    // Set multiple LEDs at once
    void set_colors(uint32_t * values, uint16_t size);
    
private:
    bool            _init {false};
    gpio_rp2040_pin _gpio;
    LED *           _leds;
    uint16_t        _size;
    SM *            _sm {nullptr};

    void            init();
    uint32_t        xRGB_to_GRBx(uint32_t rgb);
    void            update(uint16_t index);
};

#endif // _WS2812_RP2040_H_

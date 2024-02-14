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
        LED();
        void on() override;
        void off() override;
        void toggle() override;
        bool is_on() override;
        void set_color(uint32_t rgb) override;
        void set_on_color(uint32_t rgb) override;

      private:
        ws2812_rp2040 * _ws2812_rp2040;
        uint16_t _index;
        uint32_t _color;
        uint32_t _on_color;
    };

    // CTOR takes the GPIO number connected to the
    // WS2812 LEDs and the size of the LED array
    ws2812_rp2040(gpio_pin_t  led_pin,
                  uint16_t    size);

    virtual ~ws2812_rp2040();

    // Index operator to access a single LEDs
    inline led_rgb_interface & operator[](uint16_t i) {
        assert(i < _size);
        return _leds[i];
    }

    // Set multiple LEDs at once
    void set_colors(uint32_t * values, uint16_t size);
    
private:
    bool            _init;
    gpio_rp2040_pin _gpio;
    LED *           _leds;
    uint16_t        _size;
    SM *            _sm;
    uint64_t        _last;
    
    void            init();
    uint32_t        xRGB_to_GRBx(uint32_t rgb);
    void            update(uint16_t index);
    uint64_t        time_us();
};

#endif // _WS2812_RP2040_H_

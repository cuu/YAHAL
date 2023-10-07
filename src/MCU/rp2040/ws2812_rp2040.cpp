#include "ws2812_rp2040.h"
#include "pio/ws2812.pio.h"
#include "RP2040.h"
#include "task.h"
#include <cassert>

using namespace _TIMER_;

// LED implementation
/////////////////////
ws2812_rp2040::LED::LED() {
    _color = 0;
    // Default for on is a dark red
    set_on_color(0x080000);
}

void ws2812_rp2040::LED::on() {
    _color = _on_color;
    _ws2812_rp2040->update(_index);
}

void ws2812_rp2040::LED::off() {
    _color = 0;
    _ws2812_rp2040->update(_index);
}

void ws2812_rp2040::LED::toggle() {
    _color = _color ? 0 : _on_color;
    _ws2812_rp2040->update(_index);
}

void ws2812_rp2040::LED::set_color(uint32_t rgb) {
    _color = _ws2812_rp2040->xRGB_to_GRBx(rgb);
    _ws2812_rp2040->update(_index);
}

void ws2812_rp2040::LED::set_on_color(uint32_t rgb) {
    _on_color = _ws2812_rp2040->xRGB_to_GRBx(rgb);
}

// ws2812_rp2040 implementation
///////////////////////////////
ws2812_rp2040::ws2812_rp2040(gpio_pin_t pin,
                             uint16_t   size)
: _init(false), _gpio(pin), _size(size), _last(0) {
    // Allocate LED array and set base class pointers
    _leds = new LED[_size];
    for(uint16_t i=0; i < _size; ++i) {
        _leds[i]._ws2812_rp2040 = this;
        _leds[i]._index = i;
    }
}

ws2812_rp2040::~ws2812_rp2040() {
    if (_leds) delete [] _leds;
    _leds = nullptr;
    _gpio.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__sio);
}

void ws2812_rp2040::init() {
    // configure GPIO pin
    _gpio.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);
    // Set up the PIO state machine
    _sm = pio_rp2040::pio0.loadProgram(ws2812_program);
    configure_SM(_sm, _gpio.getGpio() );
    _sm->enable();
    // set flag
    _init = true;
    // initialize LEDs
    update(_size-1);
}

void ws2812_rp2040::set_colors(uint32_t * values, uint16_t size) {
    assert(size <= _size);
    for(uint16_t i=0; i < size; ++i) {
        _leds[i]._color = xRGB_to_GRBx(values[i]);
    }
    update(size-1);
}

uint32_t ws2812_rp2040::xRGB_to_GRBx(uint32_t rgb) {
    // WS2812 needs colors in GRB, and PIO 
    // expects the upper 24 bits to be set
    // Shift green to MSB
    rgb |= (rgb & 0x0000ff00) << 16;
    // Zero-out blue
    rgb &= 0xffff00ff;
    // Shift blue one byte up
    rgb |= (rgb & 0x000000ff) <<  8;
    return rgb;
}

void ws2812_rp2040::update(uint16_t index) {
    if (!_init) init();
    // The PIO buffers the data in the FIFO (8 entries).
    // Sending the whole FIFO takes 80us. The reset time
    // for a WS2812 is at least 280us, so we wait approx.
    // 400us before sending a new packet.
    while ((time_us() - _last) < 400) { }
    // Update the LEDs. A mutex will not help here because
    // the critical section could still be interrupted. But
    // WS2812 timing is critical...
    __disable_irq();
    for(uint16_t i=0; i <= index; ++i) {
        _sm->writeTxFifo(_leds[i]._color);
    }
    __enable_irq();
    // Store timer value
    _last = time_us();
}

uint64_t ws2812_rp2040::time_us() {
    uint32_t hi = TIMER.TIMERAWH;
    uint32_t lo;
    while (true) {
        lo = TIMER.TIMERAWL;
        uint32_t next_hi = TIMER.TIMERAWH;
        if (hi == next_hi) break;
        hi = next_hi;
    }
    return (uint64_t(hi) << 32) | lo;
}

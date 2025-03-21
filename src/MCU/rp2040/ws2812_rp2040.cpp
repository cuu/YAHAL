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
#include "ws2812_rp2040.h"
#include "pio/ws2812.pio.h"
#include "RP2040.h"
#include "task.h"
#include <cassert>

using namespace _IO_BANK0_;

// LED implementation
/////////////////////

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

bool ws2812_rp2040::LED::is_on() {
    return _color;
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
: _gpio(pin), _size(size) {
    // Allocate LED array and set base class pointers
    _leds = new LED[_size];
    for(uint16_t i=0; i < _size; ++i) {
        _leds[i]._ws2812_rp2040 = this;
        _leds[i]._index = i;
    }
}

ws2812_rp2040::~ws2812_rp2040() {
    delete [] _leds;
    _leds = nullptr;
    _gpio.setSEL(GPIO_CTRL_FUNCSEL__null);
}

void ws2812_rp2040::init() {
    // configure GPIO pin to use PIO0 output
    _gpio.setSEL(GPIO_CTRL_FUNCSEL__pio0);
    // Set up the PIO state machine
    _sm = pio_rp2040::pio0.loadProgram(ws2812_program);
    configure_SM(_sm, _gpio.getGpio() );
    _sm->enable();
    // set flag
    _init = true;
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
    task::sleep_ms(1);
    // Make sure that setting the GPIO18 and writing
    // the WS2812 data is atomic
    task::enterCritical();
    // Override GPIO18 to output a high level
    IO_BANK0_SET.GPIO18_CTRL.OEOVER  <<= GPIO_CTRL_OEOVER__ENABLE;
    IO_BANK0_SET.GPIO18_CTRL.OUTOVER <<= GPIO_CTRL_OUTOVER__HIGH;
    // Write WS2812 data
    for(uint16_t i=0; i <= index; ++i) {
        _sm->writeTxFifo(_leds[i]._color);
    }
    // Leave the critical section
    task::leaveCritical();
    // Sleep again to ensure a reset on the WS2812 LEDs
    task::sleep_ms(1);
    // Restore GPIO18 signal
    IO_BANK0_CLR.GPIO18_CTRL.OEOVER  <<= GPIO_CTRL_OEOVER__ENABLE;
    IO_BANK0_CLR.GPIO18_CTRL.OUTOVER <<= GPIO_CTRL_OUTOVER__HIGH;
}

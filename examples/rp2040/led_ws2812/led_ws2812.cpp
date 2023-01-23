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
// A simple blink example using the red LED on
// Port 1 pin 0. The delay is implemented with
// a simple for-loop.

#include "gpio_rp2040.h"
#include "pio/led_ws2812.pio.h"
#include "task.h"

using namespace std;

const uint32_t WS2812_GPIO = 29;

uint32_t leds[8];

void setLED(SM & sm, int index, uint32_t rgb) {
    rgb |= (rgb & 0x0000ff00) << 16;
    rgb &= 0xffff00ff;
    rgb |= (rgb & 0x000000ff) <<  8;
    leds[index] = rgb;
    for (int i=0; i <= index; ++i) {
        sm.writeTxFifo(leds[i]);
    }
}

int main(void) {
    gpio_rp2040_pin led( WS2812_GPIO );
    led.setSEL(_IO_BANK0_::GPIO_CTRL_FUNCSEL__pio0);

    // Set up the PIO state machine
    SM sm  = pio_rp2040::pio0.loadProgram(led_ws2812_program);
    configure_SM(sm, WS2812_GPIO);
    sm.enable();

    setLED(sm, 7, 0x00000000);
    task::sleep(300);
    setLED(sm, 3, 0x00050000);
    task::sleep(300);
    setLED(sm, 4, 0x00000500);
    task::sleep(300);
    setLED(sm, 5, 0x0000000a);
    task::sleep(300);

    while (1) {
        setLED(sm, 0, 0x00050000);
        task::sleep(300);
        setLED(sm, 0, 0x00000500);
        task::sleep(300);
        setLED(sm, 0, 0x00000005);
        task::sleep(300);
        setLED(sm, 0, 0x00000005);
        task::sleep(10);
        setLED(sm, 1, rand() & 0x000f0f0f);
        task::sleep(10);
    }
}


#if 0
/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#define IS_RGBW false
#define NUM_PIXELS 8

//#ifdef PICO_DEFAULT_WS2812_PIN
//#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
//#else
// default to pin 2 if the board doesn't have a default WS2812 pin defined
#define WS2812_PIN 29
//#endif

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

void pattern_snakes(uint len, uint t) {
    for (uint i = 0; i < len; ++i) {
        uint x = (i + (t >> 1)) % 64;
        if (x < 10)
            put_pixel(urgb_u32(0xff, 0, 0));
        else if (x >= 15 && x < 25)
            put_pixel(urgb_u32(0, 0xff, 0));
        else if (x >= 30 && x < 40)
            put_pixel(urgb_u32(0, 0, 0xff));
        else
            put_pixel(0);
    }
}

void pattern_random(uint len, uint t) {
    if (t % 8)
        return;
    for (int i = 0; i < len; ++i)
        put_pixel(rand());
}

void pattern_sparkle(uint len, uint t) {
    if (t % 8)
        return;
    for (int i = 0; i < len; ++i)
        put_pixel(rand() % 16 ? 0 : 0xffffffff);
}

void pattern_greys(uint len, uint t) {
    int max = 100; // let's not draw too much current!
    t %= max;
    for (int i = 0; i < len; ++i) {
        put_pixel(t * 0x10101);
        if (++t >= max) t = 0;
    }
}

typedef void (*pattern)(uint len, uint t);
const struct {
    pattern pat;
    const char *name;
} pattern_table[] = {
        {pattern_snakes,  "Snakes!"},
        {pattern_random,  "Random data"},
        {pattern_sparkle, "Sparkles"},
        {pattern_greys,   "Greys"},
};

int main() {
    //set_sys_clock_48();
    stdio_init_all();
    printf("WS2812 Smoke Test, using pin %d", WS2812_PIN);

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    int t = 0;
    while (1) {
        int pat = rand() % count_of(pattern_table);
        int dir = (rand() >> 30) & 1 ? 1 : -1;
        puts(pattern_table[pat].name);
        puts(dir == 1 ? "(forward)" : "(backward)");
        for (int i = 0; i < 1000; ++i) {
            pattern_table[pat].pat(NUM_PIXELS, t);
            sleep_ms(10);
            t += dir;
        }
    }
}

#endif

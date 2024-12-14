/*
 * boostxleduMKII.cpp
 *
 *  Created on: 23.11.2022
 *      Author: andreas
 */

#include "boostxl_eduMKII.h"
#include "gpio_rp2040.h"
#include "spi_rp2040.h"

boostxl_eduMKII::boostxl_eduMKII() {
}

void boostxl_eduMKII::inject() {
    if (need_buttons) {
        _button1 = new gpio_rp2040(BUTTON1);
        _button2 = new gpio_rp2040(BUTTON2);
    }
    if (need_led_rgb) {
        _led_red   = new gpio_rp2040(RGB_LED_RED);
        _led_green = new gpio_rp2040(RGB_LED_GREEN);
        _led_blue  = new gpio_rp2040(RGB_LED_BLUE);
    }
    if (need_buzzer) {
        _buzzer = new gpio_rp2040(BUZZER);
    }
    if (need_gator) {
        _gator = new gpio_rp2040(GATOR);
    }
    if (need_servo) {
        _servo = new gpio_rp2040(SERVO);
    }
    if (need_lcd) {
        _lcd_cs  = new gpio_rp2040(LCD_CS);
        _lcd_rst = new gpio_rp2040(LCD_RST);
        _lcd_dc  = new gpio_rp2040(LCD_DC);
        _lcd_spi = new spi_rp2040(0, LCD_MISO, LCD_MOSI, LCD_SCLK, lcd_cs());
    }
    if (need_i2c) {
        _opt3001_int = new gpio_rp2040(OPT3001_INT);
        _tmp006_int  = new gpio_rp2040(TMP006_INT);
    }
    if (need_joystick) {

    }
    if (need_microphone) {

    }
    if (need_accelerometer) {

    }
}

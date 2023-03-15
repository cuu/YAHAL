/*
 * boostxleduMKII.cpp
 *
 *  Created on: 23.11.2022
 *      Author: andreas
 */

#include "boostxl_eduMKII.h"
#include "gpio_msp432.h"
#include "spi_msp432.h"

boostxl_eduMKII::boostxl_eduMKII() {
}

void boostxl_eduMKII::inject() {
    if (need_buttons) {
        _button1 = new gpio_msp432_pin(BUTTON1);
        _button2 = new gpio_msp432_pin(BUTTON2);
    }
    if (need_led_rgb) {
        _led_red   = new gpio_msp432_pin(RGB_LED_RED);
        _led_green = new gpio_msp432_pin(RGB_LED_GREEN);
        _led_blue  = new gpio_msp432_pin(RGB_LED_BLUE);
    }
    if (need_buzzer) {
        _buzzer = new gpio_msp432_pin(BUZZER);
    }
    if (need_gator) {
        _gator = new gpio_msp432_pin(GATOR);
    }
    if (need_servo) {
        _servo = new gpio_msp432_pin(SERVO);
    }
    if (need_lcd) {
        _lcd_cs  = new gpio_msp432_pin(LCD_CS);
        _lcd_rst = new gpio_msp432_pin(LCD_RST);
        _lcd_dc  = new gpio_msp432_pin(LCD_DC);
        _lcd_spi = new spi_msp432(EUSCI_B0_SPI, lcd_cs());
    }
    if (need_i2c) {
        _opt3001_int = new gpio_msp432_pin(OPT3001_INT);
        _tmp006_int  = new gpio_msp432_pin(TMP006_INT);
    }
    if (need_joystick) {

    }
    if (need_microphone) {

    }
    if (need_accelerometer) {

    }
}

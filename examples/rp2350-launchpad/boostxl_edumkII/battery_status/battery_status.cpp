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
// A simple example for displaying text, lines and
// circles on the LCD using the uGUI library.
// See the doc folder in YAHAL/src/uGUI for more
// information on the uGUI API.

#include "adc_rp2350.h"
#include "gpio_rp2350.h"
#include "spi_rp2350.h"
#include "st7735s_drv.h"
#include "ws2812_rp2350.h"
#include "uGUI.h"
#include "uGUI_colors.h"
#include "font_8x12.h"
#include "yahal_String.h"
#include "task.h"

#include "board.h"
#include "boostxl_eduMKII.h"
#include <cstdio>

class battery_status {
public:
    battery_status(uGUI & ugui, uint16_t x, uint16_t y)
    : _x(x), _y(y), _ugui(ugui) {
        // Draw battery outline
        _ugui.DrawFrame(_x, _y, _x+20, _y+7, C_WHITE);
        _ugui.DrawFrame(_x+21, y+2, _x+22, _y+5, C_WHITE);
    }

    void draw_level(uint16_t percent) {
        if (percent >= 100) percent = 99;
        UG_COLOR colors[5] ={C_RED, C_SANDY_BROWN, C_YELLOW, C_YELLOW_GREEN, C_GREEN};
        // Clear drawing area
        _ugui.FillFrame(_x+1, _y+1, _x+19, _y+6, C_BLACK);
        // Calculate battery status color
        UG_COLOR color = colors[percent / 20];
        // Draw battery level
        for(uint16_t i=0, x=_x+1; i < (percent/20)+1; ++i, x+=4) {
            _ugui.FillFrame(x, _y+1, x+2, _y+6, color);
        }
    }
private:
    uint16_t _x;
    uint16_t _y;
    uGUI &  _ugui;
};

int main()
{
    // Set up RGB LEDs
    ws2812_rp2350 rgb(LED_RGB_GPIO, LED_RGB_COUNT);
    for(int i=0; i < LED_RGB_COUNT; ++i) rgb[i].set_color(0);

    // Setup SPI interface
    gpio_rp2350 lcd_cs (EDU_LCD_CS);
    spi_rp2350  spi(EDU_LCD_MISO, EDU_LCD_MOSI, EDU_LCD_SCLK, lcd_cs);
    spi.setSpeed(30000000);

    // Setup LCD driver
    gpio_rp2350 lcd_rst(EDU_LCD_RST);
    gpio_rp2350 lcd_dc (EDU_LCD_DC);
    st7735s_drv lcd(spi, lcd_rst, lcd_dc, st7735s_drv::Crystalfontz_128x128);
    gpio_rp2350 lcd_bl (EDU_LCD_BL);
    lcd_bl.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);

    // Setup uGUI
    uGUI gui(lcd);
    lcd.clearScreen(0x0);

    // The ADC with half the battery voltage
    adc_rp2350_channel voltage(BATT_ADC);
    voltage.adcMode(ADC::ADC_12_BIT);

    String voltage_str;
    char buffer1[100];
    char buffer2[100];

    battery_status bs(gui, 50,10);

    while(true) {
        float u = voltage.adcReadVoltage();
        u *= 2.0;

        // Simple linear scale between 3V and 4V
        int16_t percent = u * 100;
        percent -= 300;
        if (percent < 0)   percent = 0;
        if (percent > 100) percent = 100;

        sprintf(buffer1, "Ub: %2.2fV ", u);
        sprintf(buffer2, "RAW: %d", voltage.adcReadRaw());

        gui.SetForecolor(C_WHITE);
        gui.FontSelect(&FONT_8X12);
        gui.PutString(4, 32, buffer2);
        gui.PutString(4, 64, buffer1);
        bs.draw_level(percent);
        task::sleep_ms(2000);
    }
}

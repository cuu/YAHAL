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

#include "gpio_msp432.h"
#include "spi_msp432.h"
#include "sharp96_drv.h"
#include "timer_msp432.h"
#include "uGUI.h"
#include "uGUI_colors.h"
#include "font_4x6.h"
#include "font_5x8.h"
#include "font_5x12.h"
#include "font_6x8.h"
#include "font_6x10.h"
#include "font_7x12.h"
#include "font_8x12.h"

#include <cstdlib>

int main(void)
{
    // Setup SPI interface
    gpio_msp432_pin lcd_cs (PORT_PIN(4, 3));
    spi_msp432  spi(EUSCI_B0_SPI, lcd_cs);
    spi.setSpeed(1000000);

    // Setup LCD driver
    gpio_msp432_pin lcd_disp(PORT_PIN(4, 1));
    gpio_msp432_pin lcd_pwr (PORT_PIN(6, 0));
    timer_msp432 timer;
    sharp96_drv lcd(spi, lcd_disp, lcd_pwr, timer);

    // Setup uGUI
    uGUI gui(lcd);

    //lcd.clearScreen(0x0);

    gui.SetForecolor(C_BLACK);
    gui.SetBackcolor(C_WHITE);
    gui.FontSelect(&FONT_4X6);
    gui.PutString(4, 3, "Hallo MATSE", false);

    gui.SetForecolor(C_BLACK);
    gui.FontSelect(&FONT_5X8);
    gui.PutString(4, 9, "Hallo MATSE", false);

    gui.SetForecolor(C_BLACK);
    gui.FontSelect(&FONT_5X12);
    gui.PutString(4, 18, "Hallo MATSE", false);

#if 0
    gui.SetForecolor(C_RED);
    gui.FontSelect(&FONT_6X8);
    gui.PutString(4, 31, "Hallo MATSE");

    gui.SetForecolor(C_WHITE);
    gui.FontSelect(&FONT_6X10);
    gui.PutString(4, 40, "Hallo MATSE");

    gui.SetForecolor(C_MAGENTA);
    gui.FontSelect(&FONT_7X12);
    gui.PutString(4, 51, "Hallo MATSE");

    gui.SetForecolor(C_ORANGE);
    gui.FontSelect(&FONT_8X12);
    gui.PutString(4, 64, "Hallo MATSE");
#endif

    // Draw some lines and circles
    gui.FillCircle(30, 75, 15, C_BLACK);
    gui.FillCircle(30, 75,  5, C_WHITE);

    gui.DrawLine( 0,  0, 95,  0, C_BLACK);
    gui.DrawLine(95,  0, 95, 95, C_BLACK);
    gui.DrawLine(95, 95,  0, 95, C_BLACK);
    gui.DrawLine( 0, 95,  0,  0, C_BLACK);

    // Draw some random-colored pixels
    int count = 0;
    bool color = true;
    while(1) {
        count++;
        color ^= true;
        for (uint16_t x=50; x < 95; x++) {
            for (uint16_t y=60; y < 95; y++) {
                gui.DrawPixel(x, y, color);
            }
        }
//        __WFE();
    }

    while(true) ;
}

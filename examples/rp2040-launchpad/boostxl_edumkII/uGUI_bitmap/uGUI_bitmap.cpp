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
// A simple example for displaying bitmap images
// with uGUI. Starting point was a 128x128 PNG
// image (angry-bird.png), which was converted with
// the png2cpp tool (see /home/student/bin folder).
// This PNG image has a alpha-channel for displaying
// transparent areas, like for example the background.
// So the png2cpp tool was given a background color,
// in this case 0x00ff00 (green). The generated file
// is angry-bird.cpp.
//
// The image data declaration has to be copied to the
// file where the data is accessed/needed (see below).
//
// After that, the SPI interface to the LCD display is
// set up, and the LCD Driver and uGUI are started on
// top. See the doc folder in YAHAL/src/uGUI for more
// information on the uGUI API.

// Board includes
#include "boostxl_eduMKII.h"
// Driver includes
#include "st7735s_drv.h"
#include "uGUI.h"
#include "task.h"

extern const uint16_t angry_bird[16384];

int main(void) {

    // Inject dependencies
    boostxl_eduMKII edu;
    edu.need_led_rgb = true;
    edu.need_lcd     = true;
    edu.inject();
    
    // Switch on backlight
    edu.led_red().gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);
    // Setup SPI interface
    edu.lcd_spi().setSpeed(30000000);

    // Setup LCD driver
    st7735s_drv lcd(edu.lcd_spi(), edu.lcd_rst(), edu.lcd_dc(),
                    st7735s_drv::Crystalfontz_128x128);

    // Setup uGUI
    uGUI gui(lcd);

    // Setup bitmap object
    uGUI::BMP bmp;
    bmp.height = 128;
    bmp.width  = 128;
    bmp.p      = angry_bird;
    bmp.bpp    = 16;
    bmp.colors = BMP_RGB565;

    // Show bitmap image
    gui.DrawBMP(0, 0, &bmp);

    // uGUI does not support scrolling, because it
    // has no image buffer to access the current
    // image data. But the LCD driver has a method
    // for HW-scrolling...
    while (1) {
        lcd.scroll(-1);
        task::sleep_ms(10);
    }
}

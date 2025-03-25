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
// This file defines the hardware components
// on the Educational Booterpack MKII from TI,
// when used with a RP2350 Launchpad.
//
#ifndef _RP2350_LAUNCHPAD_BOOSTXL_EDUMKII_H_
#define _RP2350_LAUNCHPAD_BOOSTXL_EDUMKII_H_

// Big Buttons
#define EDU_BUTTON1     15
#define EDU_BUTTON2     17

// 3 color LED
#define EDU_RGB_RED     24
#define EDU_RGB_GREEN   22
#define EDU_RGB_BLUE    20

// Buzzer
#define EDU_BUZZER      25

// Gator holes
#define EDU_GATOR       16

// Servo PWM signal
#define EDU_SERVO       23

// LCD
#define EDU_LCD_MISO    12
#define EDU_LCD_MOSI    11
#define EDU_LCD_SCLK    30
#define EDU_LCD_CS      13
#define EDU_LCD_RST     19
#define EDU_LCD_DC       9
#define EDU_LCD_BL      24

// I2C sensors
#define EDU_I2C_SDA     34
#define EDU_I2C_SCL     35
#define EDU_OPT3001_INT 36
#define EDU_TMP006_INT   1

// Joystick button
#define EDU_JOY_BUTTON  31

// Joystick ADC channels
#define EDU_JOY_X        0
#define EDU_JOY_Y        5

// Microphone ADC channel
#define EDU_MIC          4

// Accelerometer ADC channels
#define EDU_ACC_X        1
#define EDU_ACC_Y        2
#define EDU_ACC_Z        3

#endif // _RP2350_LAUNCHPAD_BOOSTXL_EDUMKII_H_

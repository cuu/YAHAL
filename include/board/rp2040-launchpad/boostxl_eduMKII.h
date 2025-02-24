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
// when used with a RP2040 Launchpad.
//
#ifndef _RP2040_LAUNCHPAD_BOOSTXL_EDUMKII_H_
#define _RP2040_LAUNCHPAD_BOOSTXL_EDUMKII_H_

// Big Buttons
#define EDU_BUTTON1     16
#define EDU_BUTTON2     17

// 3 color LED
#define EDU_RGB_RED     13
#define EDU_RGB_GREEN   10
#define EDU_RGB_BLUE     8

// Buzzer
#define EDU_BUZZER      14

// Gator holes
#define EDU_GATOR        6

// Servo PWM signal
#define EDU_SERVO       12

// LCD
#define EDU_LCD_MISO     4
#define EDU_LCD_MOSI     7
#define EDU_LCD_SCLK    22
#define EDU_LCD_CS       5
#define EDU_LCD_RST      9
#define EDU_LCD_DC       2
#define EDU_LCD_BL      13

// I2C sensors
#define EDU_I2C_SDA     24
#define EDU_I2C_SCL     25
#define EDU_OPT3001_INT 23
#define EDU_TMP006_INT   3

// Joystick button
#define EDU_JOY_BUTTON  19

// Joystick ADC channels
#define EDU_JOY_X        1
#define EDU_JOY_Y        3

// Microphone ADC channel
#define EDU_MIC          6

// Accelerometer ADC channels
#define EDU_ACC_X        0
#define EDU_ACC_Y        2
#define EDU_ACC_Z        4

#endif // _RP2040_LAUNCHPAD_BOOSTXL_EDUMKII_H_

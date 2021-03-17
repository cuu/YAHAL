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
// A simple example using the CMSIS DSP library,
// which is included in YAHAL for the MSP432.
// The microphone signal on the EDU-MKII board
// is read in via channel 10 of the ADC14.
// It is sampled with 8kHz, which means a sample
// is taken every 125us. Using Nyquists theorem,
// we can generate a spectrum of up to 4kHz.
// The TIMER32 is used to periodically sample the
// ADC. When 512 samples are taken, the TIMER32
// is stopped. The ADC raw data is multiplied with
// a Hann window, and processed by a 512 point real
// FFT. The magnitudes of the resulting complex
// values are shown on the LCD display. The 4kHz
// spectrum has 512 values, so we have a frequency
// resolution of 7.8Hz.
//
// For more details on the CMSIS DSP library, visit
// http://www.keil.com/pack/doc/CMSIS/DSP/html/index.html

#include <stdio.h>
#include <arm_math.h>
#include <arm_const_structs.h>
#include <algorithm>

#include "adc14_msp432.h"
#include "gpio_msp432.h"
#include "spi_msp432.h"
#include "st7735s_drv.h"
#include "timer_msp432.h"
#include "uGUI.h"
#include "uGUI_colors.h"
#include "font_6x8.h"

// Size of FFT = Number of samples per FFT
const int FFT_SIZE = 512;

// Sample frequency
const int SAMPLE_FREQUENCY = 8000;

// Buffers for data processing.
// There are two ADC buffers: One which
// is filled by the sampling process, and
// a second one which is processed by
// the FFT and shown on the display!
q15_t data_hann  [FFT_SIZE];     // Hanning window function
q15_t data_adc0  [FFT_SIZE];     // ADC data 0
q15_t data_adc1  [FFT_SIZE];     // ADC data 1
q15_t data_fft   [FFT_SIZE * 2]; // complex FFT result
q15_t data_result[FFT_SIZE];     // magnitudes of FFT result

// Flag which controls which
// buffers gets filled by the ADC
bool fill_data_adc0 = true;


int main(void)
{
    // Setup LCD backlight
    gpio_msp432_pin bl( PORT_PIN(2,6) );
    bl.gpioMode(GPIO::OUTPUT | GPIO::INIT_HIGH);

    // Setup ADC channel for mic
    adc14_msp432::inst.adcSetupScan(ADC::ADC_14_BIT);
    adc14_msp432::inst.adcStartScan(10, 10);

    // Setup timer for measurements
    // T[us] = 1E6[us] / f (result is 125us for f=8kHz)
    timer_msp432 timer;
    timer.setPeriod(1000000/SAMPLE_FREQUENCY, TIMER::PERIODIC);
    timer.setCallback([&]() {
        static int index = 0;
        // Read in ADC value
        uint16_t val = adc14_msp432::inst.adcReadScan(10);
        // Copy value to correct buffer
        q15_t * data_adc = fill_data_adc0 ? data_adc0 : data_adc1;
        data_adc[index++] = (val - 8192) << 2;
        // Check if all samples have been recorded
        if (index == FFT_SIZE) {
            timer.stop();
            index = 0;
        }
    });

    // Setup SPI interface
    gpio_msp432_pin lcd_cs (PORT_PIN(5, 0));
    spi_msp432  spi(EUSCI_B0_SPI, lcd_cs);
    spi.setSpeed(24000000);
    spi.generateCS(false);
    spi.setCS(LOW);

    // Setup LCD driver
    gpio_msp432_pin lcd_rst(PORT_PIN(5, 7));
    gpio_msp432_pin lcd_dc (PORT_PIN(3, 7));
    st7735s_drv lcd(spi, lcd_rst, lcd_dc, st7735s_drv::Crystalfontz_128x128);

    // Setup uGUI
    uGUI gui(lcd);

    gui.SetForecolor(C_WHITE);
    gui.SetBackcolor(C_BLACK);
    gui.FontSelect(&FONT_6X8);
    gui.FontSetHSpace(0);

    // Draw frequency scale
    lcd.clearScreen(C_BLACK);
    gui.DrawLine(  0, 115, 127, 115, C_WHITE);
    gui.DrawLine(  0, 115,   0, 117, C_WHITE);
    gui.DrawLine( 16, 115,  16, 116, C_WHITE);
    gui.DrawLine( 31, 115,  31, 117, C_WHITE);
    gui.DrawLine( 32, 115,  32, 117, C_WHITE);
    gui.DrawLine( 48, 115,  48, 116, C_WHITE);
    gui.DrawLine( 63, 115,  63, 117, C_WHITE);
    gui.DrawLine( 64, 115,  64, 117, C_WHITE);
    gui.DrawLine( 80, 115,  80, 116, C_WHITE);
    gui.DrawLine( 95, 115,  95, 117, C_WHITE);
    gui.DrawLine( 96, 115,  96, 117, C_WHITE);
    gui.DrawLine(112, 115, 112, 116, C_WHITE);
    gui.DrawLine(127, 115, 127, 117, C_WHITE);

    gui.PutString( 23,   3, "512-Point FFT");
    gui.PutString(  0, 119, "0");
    gui.PutString( 29, 119, "1");
    gui.PutString( 60, 119, "2");
    gui.PutString( 92, 119, "3");
    gui.PutString(121, 119, "4");
    gui.SetForecolor(C_YELLOW);
    gui.PutString(102, 119, "kHz");

    // Initialize Hann Window (see Wikipedia)
    // The float value is multiplied by 32768 so we get a q15_t result!
    for(int i = 0; i < FFT_SIZE; i++) {
        data_hann[i] = 16384.0 * (1.0 - cosf((2 * PI * i) / (FFT_SIZE-1)));
    }

    // FFT instance to be used in main loop
    arm_rfft_instance_q15 instance;
    arm_rfft_init_q15(&instance, FFT_SIZE, 0, 1);

    while(1) {
        // Wait until ADC sampling has finished
        // (usually it should be finished already)
        while(timer.isRunning());

        // Switch buffers and start the ADC sampling,
        // while we are working on the other buffer...
        fill_data_adc0 ^= true; // toggle boolean
        timer.start();

        // Get the buffer which is NOT filled by the ADC
        q15_t * data_adc = fill_data_adc0 ? data_adc1 : data_adc0;

        // Multiply raw data with Hann window
        arm_mult_q15(data_adc, data_hann, data_adc, FFT_SIZE);

        // Compute real FFT using the completed data buffer
        // FFT result is in 9.7 format, so we have to shift
        arm_rfft_q15 (&instance, data_adc, data_fft);
        arm_shift_q15(data_fft, 8, data_fft, FFT_SIZE * 2);

        // Calculate magnitude of FFT output
        arm_cmplx_mag_q15(data_fft, data_result, FFT_SIZE);

        // Draw frequency bin graph
        for(int i = 0; i < 256; i += 2)
        {
            // Calculate mean value of 2 bins, using only the upper 8 bits
            int y = std::min(100, (int)((data_result[i] + data_result[i + 1]) >> 9));
            int16_t x = i/2;
            gui.DrawLine(x, 14,    x, 114-y-1, C_BLACK);
            gui.DrawLine(x, 114-y, x, 114,     C_GREEN);
        }
    }
}


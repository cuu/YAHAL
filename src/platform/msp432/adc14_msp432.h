/*
 * adc14_msp432.h
 *
 *  Created on: 10.04.2016
 *      Author: Andreas Terstegge
 */

#ifndef _ADC14_MSP432_H_
#define _ADC14_MSP432_H_

#include "adc_interface.h"

extern "C" {
void ADC14_IRQHandler(void);
}

namespace ADC {
  // ADC14 window irq modes
  const uint16_t  BELOW_LOW   = 0x0001;
  const uint16_t  ABOVE_HIGH  = 0x0002;
  const uint16_t  WITHIN_WIN  = 0x0004;
}

class adc14_msp432 : public adc_interface {
  public:
	static adc14_msp432 inst;

    // Basic ADC functions
    virtual void     adcMode(uint8_t channel, uint16_t mode);
    virtual uint16_t adcReadRaw(uint8_t channel);
    virtual float    adcReadVoltage(uint8_t channel);
    virtual float    rawToVoltage(uint8_t channel, uint16_t raw);

    // Additional ADC methods for ADC14
    void adcSetupScan (uint16_t res);
    void attachScanIrq(uint8_t channel,
                       void (*handler)(uint16_t chan, uint16_t val) );
    void adcStartScan (uint8_t start_channel, uint8_t end_channel);
    void adcStopScan  ();
    uint16_t adcReadScan(uint8_t channel);

    // The following method must only be used with ONE channel!
    // After calling the handler, the irq is disabled!
    void attachWinIrq (uint8_t channel,
                      void (*handler)(uint16_t val, uint16_t mode),
                      uint16_t low, uint16_t high,
                      uint16_t mode);

    // IRQ handlers are our best friends
    friend void ADC14_IRQHandler(void);

  private:

    adc14_msp432();
    void set_resolution (uint16_t mode);

    void handleIrq(uint32_t iv);

    void  (* _irqHandlers[24])(uint16_t, uint16_t);
    void  (* _irqWinHandler)  (uint16_t, uint16_t);
    uint16_t _irqWinMode;
    uint8_t  _irqWinChannel;

    uint16_t _resolution [24];
};


// This small wrapper class provides ADC
// functionality for a single channel.

class adc14_msp432_channel : public adc_channel {
  public:
    adc14_msp432_channel()
     : adc_channel(adc14_msp432::inst) { }

    adc14_msp432_channel(uint16_t c)
     : adc_channel(adc14_msp432::inst, c) { }

};

#endif // _ADC14_MSP432_H_


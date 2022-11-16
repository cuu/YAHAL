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
    void       adcMode       (uint8_t channel, uint16_t mode) override;
    adc_mode_t getMode       (uint8_t channel) override;
    uint16_t   adcReadRaw    (uint8_t channel) override;
    float      adcReadVoltage(uint8_t channel) override;
    float      rawToVoltage  (uint8_t channel, uint16_t raw) override;

    // Additional ADC methods for ADC14
    void adcSetupScan (uint16_t res);
    void attachScanIrq(uint8_t channel,
                       void (*handler)(uint16_t chan, uint16_t value) );
    void adcStartScan (uint8_t start_channel, uint8_t end_channel);
    void adcStopScan  ();
    uint16_t adcReadScan(uint8_t channel);

    // The following method must only be used with ONE channel!
    // After calling the handler, the irq is disabled!
    void attachWinIrq (uint8_t channel,
                      void (*handler)(uint16_t val, uint16_t irq_mode),
                      uint16_t low, uint16_t high,
                      uint16_t irq_mode);

    // IRQ handlers are our best friends
    friend void ADC14_IRQHandler(void);

  private:

    adc14_msp432();

    void set_resolution (uint16_t res);

    void handleIrq(uint32_t iv);

    void  (* _irqHandlers[24])(uint16_t, uint16_t);
    void  (* _irqWinHandler)  (uint16_t, uint16_t);
    uint16_t _irqWinMode;
    uint8_t  _irqWinChannel;

    uint16_t _modes[24];
    uint16_t _current_mode;
};


// This small wrapper class provides ADC
// functionality for a single channel.

class adc14_msp432_channel : public adc_channel {
  public:
    adc14_msp432_channel()
     : adc_channel(adc14_msp432::inst) { }

    adc14_msp432_channel(uint16_t c)
     : adc_channel(adc14_msp432::inst, c) { }

    void attachScanIrq(void (*handler)(uint16_t chan, uint16_t value)) {
        adc14_msp432::inst.attachScanIrq(_channel, handler);
    }
    uint16_t adcReadScan() {
        return adc14_msp432::inst.adcReadScan(_channel);
    }
    void attachWinIrq(void (*handler)(uint16_t val, uint16_t irq_mode),
                      uint16_t low, uint16_t high,
                      uint16_t irq_mode) {
        adc14_msp432::inst.attachWinIrq(_channel, handler, low, high, irq_mode);
    }
};

#endif // _ADC14_MSP432_H_


#ifndef _ADC_ESP8266_H_
#define _ADC_ESP8266_H_
#include "adc_interface.h"

namespace ADC {
  // additional ADC modes
  const uint16_t  FAST = 0x1000;
}

class adc_esp8266 : public adc_interface {
  public:
	static adc_esp8266 inst;
	virtual ~adc_esp8266();

    void       adcMode	     (uint8_t channel, uint16_t mode);
    adc_mode_t getResolution (uint8_t channel);
    uint16_t   adcReadRaw    (uint8_t channel);
    float      adcReadVoltage(uint8_t channel);
    float      rawToVoltage  (uint8_t channel, uint16_t raw);

  private:
    adc_esp8266();

    uint16_t	_mode;
};

#endif // _GPIO_ESP8266_H_

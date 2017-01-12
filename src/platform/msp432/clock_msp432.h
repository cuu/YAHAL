/*
 * clockmsp432.h
 *
 *  Created on: 17.04.2016
 *      Author: Andreas Terstegge
 */

#ifndef _CLOCK_MSP432_H_
#define _CLOCK_MSP432_H_

#include <stdint.h>

namespace CLKSYS {
  enum OSC {
	LFXT,		// Low Frequency XTAL
	HFXT,		// High Frequency XTAL
	DCO,		// Digital-Conrolles Oscillator
	VLO,
	REFO,
	MODOSC
  };

  enum CLK {
	ACLK,
	MCLK,
	HSMCLK,
	SMCLK,
	BCLK
  };

}

class clock_msp432 {
public:
	clock_msp432();
	virtual ~clock_msp432();

    void     setOscFrequency(CLKSYS::OSC osc, uint32_t hz);
    uint32_t getOscFrequency(CLKSYS::OSC osc);
	uint32_t getClockFrequency(CLKSYS::CLK clk);

    void     setCLockSource(CLKSYS::CLK clk, CLKSYS::OSC, uint8_t div);

private:
    float kalib04;
    float kalib5;
    uint32_t getDcoFrequency();
};

#endif /* _CLOCK_MSP432_H_ */

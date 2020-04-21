/*
 * clockmsp432.h
 *
 *  Created on: 17.04.2016
 *      Author: Andreas Terstegge
 */

#ifndef _CLOCK_MSP432_H_
#define _CLOCK_MSP432_H_

#if 0
#include <stdint.h>

namespace CLKSYS {

enum DCO_CENTER {
    DCO_1500kHz = 0,
    DCO_3MHz,
    DCO_6MHz,
    DCO_12MHz,
    DCO_24MHz,
    DCO_48MHz
};

enum OSC {
    LFXT = 0,
    VLO,
    REFO,
    DCO,
    MOD,
    HFXT
};

enum DIVIDER {
    DIV1 = 0,
    DIV2,
    DIV4,
    DIV8,
    DIV16,
    DIV32,
    DIV64,
    DIV128
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
#endif

#endif /* _CLOCK_MSP432_H_ */

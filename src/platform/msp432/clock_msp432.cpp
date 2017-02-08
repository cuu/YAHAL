/*
 * clockmsp432.cpp
 *
 *  Created on: 17.04.2016
 *      Author: Andreas Terstegge
 */

#include "msp.h"
#include "yahal_assert.h"
#include <clock_msp432.h>

#if 0

clock_msp432::clock_msp432() {
	// Initialize calibration factors
	kalib04  = (768 - TLV->DCOIR_FCAL_RSEL04);
	kalib04 += 1.0f / *((float *)(&TLV->DCOIR_CONSTK_RSEL04));
	kalib04 *= 8.00f;
	kalib5   = (768 - TLV->DCOIR_FCAL_RSEL04); // DCOIR_FCAL_RSEL5 not set!
	kalib5  += 1.0f / *((float *)(&TLV->DCOIR_CONSTK_RSEL5));
	kalib5  *= 8.00f;
	// initialize PJ so that the LFXT and HFXT are usable
	PJ->SEL0 |=  0x0F;
	PJ->SEL1 &= ~0x0F;

	// Set power mode so 48MHz can be used

}

clock_msp432::~clock_msp432() {
}

void clock_msp432::setOscFrequency(CLKSYS::OSC clk, uint32_t hz) {
	// Unlock the clock system
	CS->KEY = CS_KEY_VAL;
	switch(clk) {
		///////////////////////
		// DCO Configuration //
		///////////////////////
		case CLKSYS::DCO: {
			yahal_assert(hz>=1000000 && hz<=64000000);

			int16_t maxtune04 = (int16_t)(TLV->DCOIR_MAXPOSTUNE_RSEL04);
			int16_t mintune04 = (int16_t)(TLV->DCOIR_MAXNEGTUNE_RSEL04 | 0xffffe000);
			int16_t maxtune5  = (int16_t)(TLV->DCOIR_MAXPOSTUNE_RSEL5);
			int16_t mintune5  = (int16_t)(TLV->DCOIR_MAXNEGTUNE_RSEL5 | 0xffffe000);
			float f_center = 1500000;
			float tune;
			uint8_t rsel;
			for (rsel=0; rsel <= 5; ++rsel) {
				tune = 1.0f - (f_center / (float)hz);
				if (rsel <= 4) {
					tune *= kalib04;
					if ((tune <= maxtune04) && (tune >= mintune04))
						break;
					f_center *= 2;
				} else {
					tune *= kalib5;
					if ((tune <= maxtune5) && (tune >= mintune5))
						break;
					f_center *= 2;
				}
			}
			yahal_assert(rsel < 6);
			// Mostly default values for DCO (internal resistor)
			int16_t tune_int = (int16_t)(tune + 0.5f);
			CS->CTL0 = (rsel << CS_CTL0_DCORSEL_OFS) | (tune_int & 0x1fff);
			break;
		}
		////////////////////////
		// REFO Configuration //
		////////////////////////
		case CLKSYS::REFO: {
			yahal_assert(hz==32768 || hz==128000);
			if (hz==32768) {
				CS->CLKEN &= ~CS_CLKEN_REFOFSEL;
			} else {
				CS->CLKEN |=  CS_CLKEN_REFOFSEL;
			}
			break;
		}
		default: yahal_assert(false);
	}
	// lock clock system (prevent unintended access)
	CS->KEY = 0;
}

uint32_t clock_msp432::getOscFrequency(CLKSYS::OSC osc) {
	switch(osc) {
		case CLKSYS::LFXT:   return 32768;
		case CLKSYS::HFXT:   return 48000000;
		case CLKSYS::DCO:    return getDcoFrequency();
		case CLKSYS::VLO:    return 10000;
		case CLKSYS::REFO:   return (CS->CLKEN & CS_CLKEN_REFOFSEL) ? 128000 : 32768;
		case CLKSYS::MODOSC: return 24000000;
    };
	return 0;
}

uint32_t clock_msp432::getClockFrequency(CLKSYS::CLK clk) {
	uint8_t oscsel;
	uint32_t f;
	uint8_t  shift = 0;
	switch(clk) {
	  case CLKSYS::ACLK: {
		  oscsel = (CS->CTL1 & CS_CTL1_SELA_MASK) >> CS_CTL1_SELA_OFS;
		  shift  = (CS->CTL1 & CS_CTL1_DIVA_MASK) >> CS_CTL1_DIVA_OFS;
		  break;
	  }
	  case CLKSYS::MCLK: {
		  oscsel = (CS->CTL1 & CS_CTL1_SELM_MASK) >> CS_CTL1_SELM_OFS;
		  shift  = (CS->CTL1 & CS_CTL1_DIVM_MASK) >> CS_CTL1_DIVM_OFS;
		  break;
	  }
	  case CLKSYS::HSMCLK: {
		  oscsel = (CS->CTL1 & CS_CTL1_SELS_MASK)  >> CS_CTL1_SELS_OFS;
		  shift  = (CS->CTL1 & CS_CTL1_DIVHS_MASK) >> CS_CTL1_DIVHS_OFS;
		  break;
	  }
	  case CLKSYS::SMCLK: {
		  oscsel = (CS->CTL1 & CS_CTL1_SELS_MASK) >> CS_CTL1_SELS_OFS;
		  shift  = (CS->CTL1 & CS_CTL1_DIVS_MASK) >> CS_CTL1_DIVS_OFS;
		  break;
	  }
	  case CLKSYS::BCLK: {
		  oscsel = (CS->CTL1 & CS_CTL1_SELB) >> (CS_CTL1_SELB_OFS-1);
		  shift  = 0;
		  break;
	  }
	}
	switch(oscsel) {
	  case 0: f=getOscFrequency(CLKSYS::LFXT);   break;
	  case 1: f=getOscFrequency(CLKSYS::VLO);    break;
	  case 2: f=getOscFrequency(CLKSYS::REFO);   break;
	  case 3: f=getOscFrequency(CLKSYS::DCO);    break;
	  case 4: f=getOscFrequency(CLKSYS::MODOSC); break;
	  case 5: f=getOscFrequency(CLKSYS::HFXT);   break;
	  default: yahal_assert(false);
	  }
	return f >> shift;
}


void clock_msp432::setCLockSource(CLKSYS::CLK clk, CLKSYS::OSC osc, uint8_t div) {
	yahal_assert ((div > 0) && (div < 129) && !(div & (div-1)));
	// Unlock the clock system
	CS->KEY = CS_KEY_VAL;
	// Calculate the div value (0...7) representing dividing
	// factors of 1,2,4,8,16,32,64 and 128
	uint8_t div_val   = 0;
	uint8_t osc_shift = 0;
	uint8_t div_shift = 0;
	while (!(div & 0x01)) {
		div >>= 1;
		div_val++;
	}
	switch(clk) {
	  case CLKSYS::ACLK: {
		  yahal_assert(osc == CLKSYS::LFXT ||
				 osc == CLKSYS::VLO  ||
				 osc == CLKSYS::REFO);
		  osc_shift = CS_CTL1_SELA_OFS;
		  div_shift = CS_CTL1_DIVA_OFS;
		  break;
	  }
	  case CLKSYS::MCLK: {
		  osc_shift = CS_CTL1_SELM_OFS;
		  div_shift = CS_CTL1_DIVM_OFS;
		  break;
	  }
	  case CLKSYS::HSMCLK: {
		  osc_shift = CS_CTL1_SELS_OFS;
		  div_shift = CS_CTL1_DIVHS_OFS;
		  break;
	  }
	  case CLKSYS::SMCLK: {
		  osc_shift = CS_CTL1_SELS_OFS;
		  div_shift = CS_CTL1_DIVS_OFS;
		  break;
	  }
	  case CLKSYS::BCLK: {
		  yahal_assert(div == 1);
		  switch(osc) {
		    case CLKSYS::LFXT: CS->CTL1 &= ~CS_CTL1_SELB; break;
		    case CLKSYS::REFO: CS->CTL1 |=  CS_CTL1_SELB; break;
		    default: yahal_assert(false);
		  }
		  break;
	  }
	}

	if (clk != CLKSYS::BCLK) {
		CS->CTL1 &= ~ (0x07 << osc_shift);
		switch(osc) {
		  case CLKSYS::LFXT:   CS->CTL1 |= 0x00 << osc_shift; break;
		  case CLKSYS::VLO:    CS->CTL1 |= 0x01 << osc_shift;  break;
		  case CLKSYS::REFO:   CS->CTL1 |= 0x02 << osc_shift; break;
		  case CLKSYS::DCO:    CS->CTL1 |= 0x03 << osc_shift;  break;
		  case CLKSYS::MODOSC: CS->CTL1 |= 0x04 << osc_shift;  break;
		  case CLKSYS::HFXT:   CS->CTL1 |= 0x05 << osc_shift; break;
		}
		CS->CTL1 &= ~ (0x07 << div_shift);
		CS->CTL1 |= div_val << div_shift;
	}

	// lock clock system (prevent unintended access)
	CS->KEY = 0;
}

uint32_t clock_msp432::getDcoFrequency() {
	uint8_t  rsel = ((CS->CTL0 & CS_CTL0_DCORSEL_MASK) >> CS_CTL0_DCORSEL_OFS);
	float    kalib = (rsel <= 4) ? kalib04 : kalib5;
	uint32_t f_center = 1500000 << rsel;
	int16_t  tune = (CS->CTL0 & 0x1fff);
	if (tune & 0x1000) tune |= 0xe000; // extend sign
	float    f = (float)f_center / (kalib - (float)tune) * kalib;
	return   (uint32_t)(f + 0.5f);
}

#endif


enum dcofrequency{
  DCO1_5MHz = 0x00000000,
  DCO3MHz = 0x00010000,
  DCO6MHz = 0x00020000,
  DCO12MHz = 0x00030000
};

//------------Clock_Init------------
// Configure for SMCLK = MCLK = speed, ACLK = REFOCLK.
// Input: 1.5, 3, 6, or 12 MHz
// Output: none   12 MHz is the max speed for SMCLK
void Clock_Init(enum dcofrequency speed);

//------------Clock_Init48MHz------------
// Configure for MCLK = HFXTCLK, HSMCLK = HFXTCLK/2,
// SMCLK = HFXTCLK/4, ACLK = REFOCLK.
// On the LaunchPad, the high-frequency crystal
// oscillator has a 48 MHz crystal attached, which will
// make the bus (master) clock run at 48 MHz.  The sub-
// system master clock (HSMCLK) runs at its maximum of
// 24 MHz.  The low-speed subsystem master clock (SMCLK)
// runs at its maximum of 12 MHz.  In other words, this
// function is similar to Clock_Init(), except instead
// of the variable frequency DCO this uses the fixed
// high-frequency crystal.
// Input: none
// Output: none
void Clock_Init48MHz(void);

//------------Clock_Init32kHz------------
// Configure for HSMCLK = MCLK = LFXTCLK,
// SMCLK = LFXTCLK/2, ACLK = REFOCLK.
// On the LaunchPad, the low-frequency crystal
// oscillator has a 32 kHz crystal attached, which will
// make the high speed subsystem master clock and the
// bus (master) clock run at 32 kHz.  The low speed
// subsystem master clock has a maximum frequency of
// 16,384 Hz in LPM3 and LPM3.5, so this function sets
// the SMCLK divider to /2.  This is slower than
// necessary for active mode.  In other words, this
// function is similar to Clock_Init(), except instead
// of the variable frequency DCO this uses the fixed
// low-frequency crystal.
// Input: none
// Output: none
void Clock_Init32kHz(void);

//------------Clock_InitLowPower------------
// Configure for HSMCLK = MCLK = ACLK = REFOCLK,
// SMCLK = REFOCLK/2.
// On the LaunchPad, the low-frequency, low-power
// oscillator has a 32 kHz reference clock, which will
// make the high speed subsystem master clock and the
// bus (master) clock run at 32 kHz.  The low speed
// subsystem master clock has a maximum frequency of
// 16,384 Hz in LPM3 and LPM3.5, so this function sets
// the SMCLK divider to /2.  This is slower than
// necessary for active mode.  In other words, this
// function is similar to Clock_Init32kHz(), except
// instead it should be lower power and slightly less
// accurate.
// Input: none
// Output: none
void Clock_InitLowPower(void);

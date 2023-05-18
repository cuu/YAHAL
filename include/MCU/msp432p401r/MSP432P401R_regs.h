///////////////////////////////////////////////////////////////////////////
// This file was generated with svd2cpp, source file was MSP432P401R.svd
// DO NOT EDIT - CHANGES MIGHT BE OVERWRITTEN !!
///////////////////////////////////////////////////////////////////////////
//
#include "bitfield_defs.h"

// vendor: Texas Instruments
// vendorID: ti.com
// name: MSP432P401R
// version: 3.220
// description: ARM Cortex-M4 MSP432P4xx Device
// 
// Copyright (C) 2012-2017 Texas Instruments Incorporated - http://www.ti.com/
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// 
// Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the
// distribution.
// 
// Neither the name of Texas Instruments Incorporated nor the names of
// its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// 
// addressUnitBits: 8
// width: 32
// size: 32
// resetValue: 0x00000000
// resetMask: 0xffffffff

// TLV
namespace _TLV_  {

    // TLV Checksum
    // Reset value: 0x00000000
    typedef uint32_t TLV_CHECKSUM_t;

    // Device Info Tag
    // Reset value: 0x0000000b
    typedef uint32_t DEVICE_INFO_TAG_t;

    // Device Info Length
    // Reset value: 0x00000000
    typedef uint32_t DEVICE_INFO_LEN_t;

    // Device ID
    // Reset value: 0x00000000
    typedef uint32_t DEVICE_ID_t;

    // HW Revision
    // Reset value: 0x00000000
    typedef uint32_t HWREV_t;

    // Boot Code Revision
    // Reset value: 0x00000000
    typedef uint32_t BCREV_t;

    // ROM Driver Library Revision
    // Reset value: 0x00000000
    typedef uint32_t ROM_DRVLIB_REV_t;

    // Die Record Tag
    // Reset value: 0x0000000c
    typedef uint32_t DIE_REC_TAG_t;

    // Die Record Length
    // Reset value: 0x00000000
    typedef uint32_t DIE_REC_LEN_t;

    // Die X-Position
    // Reset value: 0x00000000
    typedef uint32_t DIE_XPOS_t;

    // Die Y-Position
    // Reset value: 0x00000000
    typedef uint32_t DIE_YPOS_t;

    // Wafer ID
    // Reset value: 0x00000000
    typedef uint32_t WAFER_ID_t;

    // Lot ID
    // Reset value: 0x00000000
    typedef uint32_t LOT_ID_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED0_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED1_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED2_t;

    // Test Results
    // Reset value: 0x00000000
    typedef uint32_t TEST_RESULTS_t;

    // Clock System Calibration Tag
    // Reset value: 0x00000003
    typedef uint32_t CS_CAL_TAG_t;

    // Clock System Calibration Length
    // Reset value: 0x00000000
    typedef uint32_t CS_CAL_LEN_t;

    // DCO IR mode: Frequency calibration for DCORSEL 0 to 4
    // Reset value: 0x00000000
    typedef uint32_t DCOIR_FCAL_RSEL04_t;

    // DCO IR mode: Frequency calibration for DCORSEL 5
    // Reset value: 0x00000000
    typedef uint32_t DCOIR_FCAL_RSEL5_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED3_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED4_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED5_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED6_t;

    // DCO IR mode: DCO Constant (K) for DCORSEL 0 to 4
    // Reset value: 0x00000000
    typedef uint32_t DCOIR_CONSTK_RSEL04_t;

    // DCO IR mode: DCO Constant (K) for DCORSEL 5
    // Reset value: 0x00000000
    typedef uint32_t DCOIR_CONSTK_RSEL5_t;

    // DCO ER mode: Frequency calibration for DCORSEL 0 to 4
    // Reset value: 0x00000000
    typedef uint32_t DCOER_FCAL_RSEL04_t;

    // DCO ER mode: Frequency calibration for DCORSEL 5
    // Reset value: 0x00000000
    typedef uint32_t DCOER_FCAL_RSEL5_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED7_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED8_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED9_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED10_t;

    // DCO ER mode: DCO Constant (K) for DCORSEL 0 to 4
    // Reset value: 0x00000000
    typedef uint32_t DCOER_CONSTK_RSEL04_t;

    // DCO ER mode: DCO Constant (K) for DCORSEL 5
    // Reset value: 0x00000000
    typedef uint32_t DCOER_CONSTK_RSEL5_t;

    // ADC14 Calibration Tag
    // Reset value: 0x00000005
    typedef uint32_t ADC14_CAL_TAG_t;

    // ADC14 Calibration Length
    // Reset value: 0x00000000
    typedef uint32_t ADC14_CAL_LEN_t;

    // ADC Gain Factor
    // Reset value: 0x00000000
    typedef uint32_t ADC_GAIN_FACTOR_t;

    // ADC Offset
    // Reset value: 0x00000000
    typedef uint32_t ADC_OFFSET_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED11_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED12_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED13_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED14_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED15_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED16_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED17_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED18_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED19_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED20_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED21_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED22_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED23_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED24_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED25_t;

    // Reserved
    // Reset value: 0x00000000
    typedef uint32_t RESERVED26_t;

    // ADC14 1.2V Reference Temp. Sensor 30C
    // Reset value: 0x00000000
    typedef uint32_t ADC14_REF1P2V_TS30C_t;

    // ADC14 1.2V Reference Temp. Sensor 85C
    // Reset value: 0x00000000
    typedef uint32_t ADC14_REF1P2V_TS85C_t;

    // ADC14 1.45V Reference Temp. Sensor 30C
    // Reset value: 0x00000000
    typedef uint32_t ADC14_REF1P45V_TS30C_t;

    // ADC14 1.45V Reference Temp. Sensor 85C
    // Reset value: 0x00000000
    typedef uint32_t ADC14_REF1P45V_TS85C_t;

    // ADC14 2.5V Reference Temp. Sensor 30C
    // Reset value: 0x00000000
    typedef uint32_t ADC14_REF2P5V_TS30C_t;

    // ADC14 2.5V Reference Temp. Sensor 85C
    // Reset value: 0x00000000
    typedef uint32_t ADC14_REF2P5V_TS85C_t;

    // REF Calibration Tag
    // Reset value: 0x00000008
    typedef uint32_t REF_CAL_TAG_t;

    // REF Calibration Length
    // Reset value: 0x00000000
    typedef uint32_t REF_CAL_LEN_t;

    // REF 1.2V Reference
    // Reset value: 0x00000000
    typedef uint32_t REF_1P2V_t;

    // REF 1.45V Reference
    // Reset value: 0x00000000
    typedef uint32_t REF_1P45V_t;

    // REF 2.5V Reference
    // Reset value: 0x00000000
    typedef uint32_t REF_2P5V_t;

    // Flash Info Tag
    // Reset value: 0x00000004
    typedef uint32_t FLASH_INFO_TAG_t;

    // Flash Info Length
    // Reset value: 0x00000000
    typedef uint32_t FLASH_INFO_LEN_t;

    // Flash Maximum Programming Pulses
    // Reset value: 0x00000000
    typedef uint32_t FLASH_MAX_PROG_PULSES_t;

    // Flash Maximum Erase Pulses
    // Reset value: 0x00000000
    typedef uint32_t FLASH_MAX_ERASE_PULSES_t;

    // 128-bit Random Number Tag
    // Reset value: 0x0000000d
    typedef uint32_t RANDOM_NUM_TAG_t;

    // 128-bit Random Number Length
    // Reset value: 0x00000000
    typedef uint32_t RANDOM_NUM_LEN_t;

    // 32-bit Random Number 1
    // Reset value: 0x00000000
    typedef uint32_t RANDOM_NUM_1_t;

    // 32-bit Random Number 2
    // Reset value: 0x00000000
    typedef uint32_t RANDOM_NUM_2_t;

    // 32-bit Random Number 3
    // Reset value: 0x00000000
    typedef uint32_t RANDOM_NUM_3_t;

    // 32-bit Random Number 4
    // Reset value: 0x00000000
    typedef uint32_t RANDOM_NUM_4_t;

    // BSL Configuration Tag
    // Reset value: 0x0000000f
    typedef uint32_t BSL_CFG_TAG_t;

    // BSL Configuration Length
    // Reset value: 0x00000000
    typedef uint32_t BSL_CFG_LEN_t;

    // BSL Peripheral Interface Selection
    // Reset value: 0x00000000
    typedef uint32_t BSL_PERIPHIF_SEL_t;

    // BSL Port Interface Configuration for UART
    // Reset value: 0x00000000
    typedef uint32_t BSL_PORTIF_CFG_UART_t;

    // BSL Port Interface Configuration for SPI
    // Reset value: 0x00000000
    typedef uint32_t BSL_PORTIF_CFG_SPI_t;

    // BSL Port Interface Configuration for I2C
    // Reset value: 0x00000000
    typedef uint32_t BSL_PORTIF_CFG_I2C_t;

    // TLV End Word
    // Reset value: 0x0bd0e11d
    typedef uint32_t TLV_END_t;

    struct TLV_t {
        TLV_CHECKSUM_t                TLV_CHECKSUM;
        DEVICE_INFO_TAG_t             DEVICE_INFO_TAG;
        DEVICE_INFO_LEN_t             DEVICE_INFO_LEN;
        DEVICE_ID_t                   DEVICE_ID;
        HWREV_t                       HWREV;
        BCREV_t                       BCREV;
        ROM_DRVLIB_REV_t              ROM_DRVLIB_REV;
        DIE_REC_TAG_t                 DIE_REC_TAG;
        DIE_REC_LEN_t                 DIE_REC_LEN;
        DIE_XPOS_t                    DIE_XPOS;
        DIE_YPOS_t                    DIE_YPOS;
        WAFER_ID_t                    WAFER_ID;
        LOT_ID_t                      LOT_ID;
        RESERVED0_t                   RESERVED0;
        RESERVED1_t                   RESERVED1;
        RESERVED2_t                   RESERVED2;
        TEST_RESULTS_t                TEST_RESULTS;
        CS_CAL_TAG_t                  CS_CAL_TAG;
        CS_CAL_LEN_t                  CS_CAL_LEN;
        DCOIR_FCAL_RSEL04_t           DCOIR_FCAL_RSEL04;
        DCOIR_FCAL_RSEL5_t            DCOIR_FCAL_RSEL5;
        RESERVED3_t                   RESERVED3;
        RESERVED4_t                   RESERVED4;
        RESERVED5_t                   RESERVED5;
        RESERVED6_t                   RESERVED6;
        DCOIR_CONSTK_RSEL04_t         DCOIR_CONSTK_RSEL04;
        DCOIR_CONSTK_RSEL5_t          DCOIR_CONSTK_RSEL5;
        DCOER_FCAL_RSEL04_t           DCOER_FCAL_RSEL04;
        DCOER_FCAL_RSEL5_t            DCOER_FCAL_RSEL5;
        RESERVED7_t                   RESERVED7;
        RESERVED8_t                   RESERVED8;
        RESERVED9_t                   RESERVED9;
        RESERVED10_t                  RESERVED10;
        DCOER_CONSTK_RSEL04_t         DCOER_CONSTK_RSEL04;
        DCOER_CONSTK_RSEL5_t          DCOER_CONSTK_RSEL5;
        ADC14_CAL_TAG_t               ADC14_CAL_TAG;
        ADC14_CAL_LEN_t               ADC14_CAL_LEN;
        ADC_GAIN_FACTOR_t             ADC_GAIN_FACTOR;
        ADC_OFFSET_t                  ADC_OFFSET;
        RESERVED11_t                  RESERVED11;
        RESERVED12_t                  RESERVED12;
        RESERVED13_t                  RESERVED13;
        RESERVED14_t                  RESERVED14;
        RESERVED15_t                  RESERVED15;
        RESERVED16_t                  RESERVED16;
        RESERVED17_t                  RESERVED17;
        RESERVED18_t                  RESERVED18;
        RESERVED19_t                  RESERVED19;
        RESERVED20_t                  RESERVED20;
        RESERVED21_t                  RESERVED21;
        RESERVED22_t                  RESERVED22;
        RESERVED23_t                  RESERVED23;
        RESERVED24_t                  RESERVED24;
        RESERVED25_t                  RESERVED25;
        RESERVED26_t                  RESERVED26;
        ADC14_REF1P2V_TS30C_t         ADC14_REF1P2V_TS30C;
        ADC14_REF1P2V_TS85C_t         ADC14_REF1P2V_TS85C;
        ADC14_REF1P45V_TS30C_t        ADC14_REF1P45V_TS30C;
        ADC14_REF1P45V_TS85C_t        ADC14_REF1P45V_TS85C;
        ADC14_REF2P5V_TS30C_t         ADC14_REF2P5V_TS30C;
        ADC14_REF2P5V_TS85C_t         ADC14_REF2P5V_TS85C;
        REF_CAL_TAG_t                 REF_CAL_TAG;
        REF_CAL_LEN_t                 REF_CAL_LEN;
        REF_1P2V_t                    REF_1P2V;
        REF_1P45V_t                   REF_1P45V;
        REF_2P5V_t                    REF_2P5V;
        FLASH_INFO_TAG_t              FLASH_INFO_TAG;
        FLASH_INFO_LEN_t              FLASH_INFO_LEN;
        FLASH_MAX_PROG_PULSES_t       FLASH_MAX_PROG_PULSES;
        FLASH_MAX_ERASE_PULSES_t      FLASH_MAX_ERASE_PULSES;
        RANDOM_NUM_TAG_t              RANDOM_NUM_TAG;
        RANDOM_NUM_LEN_t              RANDOM_NUM_LEN;
        RANDOM_NUM_1_t                RANDOM_NUM_1;
        RANDOM_NUM_2_t                RANDOM_NUM_2;
        RANDOM_NUM_3_t                RANDOM_NUM_3;
        RANDOM_NUM_4_t                RANDOM_NUM_4;
        BSL_CFG_TAG_t                 BSL_CFG_TAG;
        BSL_CFG_LEN_t                 BSL_CFG_LEN;
        BSL_PERIPHIF_SEL_t            BSL_PERIPHIF_SEL;
        BSL_PORTIF_CFG_UART_t         BSL_PORTIF_CFG_UART;
        BSL_PORTIF_CFG_SPI_t          BSL_PORTIF_CFG_SPI;
        BSL_PORTIF_CFG_I2C_t          BSL_PORTIF_CFG_I2C;
        TLV_END_t                     TLV_END;
    };

    static TLV_t & TLV     = (*(TLV_t *)0x201000);

} // _TLV_

// TIMER_A0
namespace _TIMER_A0_  {

    // TimerAx Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxCTL_t, uint16_t)
        // TimerA interrupt flag
        ADD_BITFIELD_RW(TAIFG, 0, 1)
        // TimerA interrupt enable
        ADD_BITFIELD_RW(TAIE, 1, 1)
        // TimerA clear
        ADD_BITFIELD_RW(TACLR, 2, 1)
        // Mode control
        ADD_BITFIELD_RW(MC, 4, 2)
        // Input divider
        ADD_BITFIELD_RW(ID, 6, 2)
        // TimerA clock source select
        ADD_BITFIELD_RW(TASSEL, 8, 2)
    END_TYPE()

    // No interrupt pending
    static const uint32_t TAxCTL_TAIFG__TAIFG_0 = 0;
    // Interrupt pending
    static const uint32_t TAxCTL_TAIFG__TAIFG_1 = 1;
    // Interrupt disabled
    static const uint32_t TAxCTL_TAIE__TAIE_0 = 0;
    // Interrupt enabled
    static const uint32_t TAxCTL_TAIE__TAIE_1 = 1;
    // Stop mode: Timer is halted
    static const uint32_t TAxCTL_MC__MC_0 = 0;
    // Up mode: Timer counts up to TAxCCR0
    static const uint32_t TAxCTL_MC__MC_1 = 1;
    // Continuous mode: Timer counts up to 0FFFFh
    static const uint32_t TAxCTL_MC__MC_2 = 2;
    // Up/down mode: Timer counts up to TAxCCR0 then down to 0000h
    static const uint32_t TAxCTL_MC__MC_3 = 3;
    // /1
    static const uint32_t TAxCTL_ID__ID_0 = 0;
    // /2
    static const uint32_t TAxCTL_ID__ID_1 = 1;
    // /4
    static const uint32_t TAxCTL_ID__ID_2 = 2;
    // /8
    static const uint32_t TAxCTL_ID__ID_3 = 3;
    // TAxCLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_0 = 0;
    // ACLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_1 = 1;
    // SMCLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_2 = 2;
    // INCLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_3 = 3;

    // Timer_A Capture/Compare Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxCCTL_t, uint16_t)
        // Capture/compare interrupt flag
        ADD_BITFIELD_RW(CCIFG, 0, 1)
        // Capture overflow
        ADD_BITFIELD_RW(COV, 1, 1)
        // Output
        ADD_BITFIELD_RW(OUT, 2, 1)
        // Capture/compare input
        ADD_BITFIELD_RO(CCI, 3, 1)
        // Capture/compare interrupt enable
        ADD_BITFIELD_RW(CCIE, 4, 1)
        // Output mode
        ADD_BITFIELD_RW(OUTMOD, 5, 3)
        // Capture mode
        ADD_BITFIELD_RW(CAP, 8, 1)
        // Synchronized capture/compare input
        ADD_BITFIELD_RW(SCCI, 10, 1)
        // Synchronize capture source
        ADD_BITFIELD_RW(SCS, 11, 1)
        // Capture/compare input select
        ADD_BITFIELD_RW(CCIS, 12, 2)
        // Capture mode
        ADD_BITFIELD_RW(CM, 14, 2)
    END_TYPE()

    // No interrupt pending
    static const uint32_t TAxCCTL_CCIFG__CCIFG_0 = 0;
    // Interrupt pending
    static const uint32_t TAxCCTL_CCIFG__CCIFG_1 = 1;
    // No capture overflow occurred
    static const uint32_t TAxCCTL_COV__COV_0 = 0;
    // Capture overflow occurred
    static const uint32_t TAxCCTL_COV__COV_1 = 1;
    // Output low
    static const uint32_t TAxCCTL_OUT__OUT_0 = 0;
    // Output high
    static const uint32_t TAxCCTL_OUT__OUT_1 = 1;
    // Interrupt disabled
    static const uint32_t TAxCCTL_CCIE__CCIE_0 = 0;
    // Interrupt enabled
    static const uint32_t TAxCCTL_CCIE__CCIE_1 = 1;
    // OUT bit value
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_0 = 0;
    // Set
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_1 = 1;
    // Toggle/reset
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_2 = 2;
    // Set/reset
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_3 = 3;
    // Toggle
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_4 = 4;
    // Reset
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_5 = 5;
    // Toggle/set
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_6 = 6;
    // Reset/set
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_7 = 7;
    // Compare mode
    static const uint32_t TAxCCTL_CAP__CAP_0 = 0;
    // Capture mode
    static const uint32_t TAxCCTL_CAP__CAP_1 = 1;
    // Asynchronous capture
    static const uint32_t TAxCCTL_SCS__SCS_0 = 0;
    // Synchronous capture
    static const uint32_t TAxCCTL_SCS__SCS_1 = 1;
    // CCIxA
    static const uint32_t TAxCCTL_CCIS__CCIS_0 = 0;
    // CCIxB
    static const uint32_t TAxCCTL_CCIS__CCIS_1 = 1;
    // GND
    static const uint32_t TAxCCTL_CCIS__CCIS_2 = 2;
    // VCC
    static const uint32_t TAxCCTL_CCIS__CCIS_3 = 3;
    // No capture
    static const uint32_t TAxCCTL_CM__CM_0 = 0;
    // Capture on rising edge
    static const uint32_t TAxCCTL_CM__CM_1 = 1;
    // Capture on falling edge
    static const uint32_t TAxCCTL_CM__CM_2 = 2;
    // Capture on both rising and falling edges
    static const uint32_t TAxCCTL_CM__CM_3 = 3;

    // TimerA register
    // Reset value: 0x00000000
    typedef uint16_t TAxR_t;

    // Timer_A Capture/Compare  Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxCCR_t, uint16_t)
        // TimerA register
        ADD_BITFIELD_RW(TAxR, 0, 16)
    END_TYPE()

    // TimerAx Expansion 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxEX0_t, uint16_t)
        // Input divider expansion
        ADD_BITFIELD_RW(TAIDEX, 0, 3)
    END_TYPE()

    // Divide by 1
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_0 = 0;
    // Divide by 2
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_1 = 1;
    // Divide by 3
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_2 = 2;
    // Divide by 4
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_3 = 3;
    // Divide by 5
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_4 = 4;
    // Divide by 6
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_5 = 5;
    // Divide by 7
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_6 = 6;
    // Divide by 8
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_7 = 7;

    // TimerAx Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxIV_t, uint16_t)
        // TimerA interrupt vector value
        ADD_BITFIELD_RO(TAIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t TAxIV_TAIV__TAIV_0 = 0;
    // Interrupt Source: Capture/compare 1; Interrupt Flag: TAxCCR1 CCIFG; Interrupt Priority: Highest
    static const uint32_t TAxIV_TAIV__TAIV_2 = 2;
    // Interrupt Source: Capture/compare 2; Interrupt Flag: TAxCCR2 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_4 = 4;
    // Interrupt Source: Capture/compare 3; Interrupt Flag: TAxCCR3 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_6 = 6;
    // Interrupt Source: Capture/compare 4; Interrupt Flag: TAxCCR4 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_8 = 8;
    // Interrupt Source: Capture/compare 5; Interrupt Flag: TAxCCR5 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_10 = 10;
    // Interrupt Source: Capture/compare 6; Interrupt Flag: TAxCCR6 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_12 = 12;
    // Interrupt Source: Timer overflow; Interrupt Flag: TAxCTL TAIFG; Interrupt Priority: Lowest
    static const uint32_t TAxIV_TAIV__TAIV_14 = 14;

    struct TIMER_A0_t {
        TAxCTL_t                      TAxCTL;
        TAxCCTL_t                     TAxCCTL0;
        TAxCCTL_t                     TAxCCTL1;
        TAxCCTL_t                     TAxCCTL2;
        TAxCCTL_t                     TAxCCTL3;
        TAxCCTL_t                     TAxCCTL4;
        uint16_t                      reserved0[2];
        TAxR_t                        TAxR;
        TAxCCR_t                      TAxCCR0;
        TAxCCR_t                      TAxCCR1;
        TAxCCR_t                      TAxCCR2;
        TAxCCR_t                      TAxCCR3;
        TAxCCR_t                      TAxCCR4;
        uint16_t                      reserved1[2];
        TAxEX0_t                      TAxEX0;
        uint16_t                      reserved2[6];
        TAxIV_t                       TAxIV;
    };

    static TIMER_A0_t & TIMER_A0     = (*(TIMER_A0_t *)0x40000000);

} // _TIMER_A0_

// TIMER_A1
namespace _TIMER_A1_  {

    // TimerAx Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxCTL_t, uint16_t)
        // TimerA interrupt flag
        ADD_BITFIELD_RW(TAIFG, 0, 1)
        // TimerA interrupt enable
        ADD_BITFIELD_RW(TAIE, 1, 1)
        // TimerA clear
        ADD_BITFIELD_RW(TACLR, 2, 1)
        // Mode control
        ADD_BITFIELD_RW(MC, 4, 2)
        // Input divider
        ADD_BITFIELD_RW(ID, 6, 2)
        // TimerA clock source select
        ADD_BITFIELD_RW(TASSEL, 8, 2)
    END_TYPE()

    // No interrupt pending
    static const uint32_t TAxCTL_TAIFG__TAIFG_0 = 0;
    // Interrupt pending
    static const uint32_t TAxCTL_TAIFG__TAIFG_1 = 1;
    // Interrupt disabled
    static const uint32_t TAxCTL_TAIE__TAIE_0 = 0;
    // Interrupt enabled
    static const uint32_t TAxCTL_TAIE__TAIE_1 = 1;
    // Stop mode: Timer is halted
    static const uint32_t TAxCTL_MC__MC_0 = 0;
    // Up mode: Timer counts up to TAxCCR0
    static const uint32_t TAxCTL_MC__MC_1 = 1;
    // Continuous mode: Timer counts up to 0FFFFh
    static const uint32_t TAxCTL_MC__MC_2 = 2;
    // Up/down mode: Timer counts up to TAxCCR0 then down to 0000h
    static const uint32_t TAxCTL_MC__MC_3 = 3;
    // /1
    static const uint32_t TAxCTL_ID__ID_0 = 0;
    // /2
    static const uint32_t TAxCTL_ID__ID_1 = 1;
    // /4
    static const uint32_t TAxCTL_ID__ID_2 = 2;
    // /8
    static const uint32_t TAxCTL_ID__ID_3 = 3;
    // TAxCLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_0 = 0;
    // ACLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_1 = 1;
    // SMCLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_2 = 2;
    // INCLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_3 = 3;

    // Timer_A Capture/Compare Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxCCTL_t, uint16_t)
        // Capture/compare interrupt flag
        ADD_BITFIELD_RW(CCIFG, 0, 1)
        // Capture overflow
        ADD_BITFIELD_RW(COV, 1, 1)
        // Output
        ADD_BITFIELD_RW(OUT, 2, 1)
        // Capture/compare input
        ADD_BITFIELD_RO(CCI, 3, 1)
        // Capture/compare interrupt enable
        ADD_BITFIELD_RW(CCIE, 4, 1)
        // Output mode
        ADD_BITFIELD_RW(OUTMOD, 5, 3)
        // Capture mode
        ADD_BITFIELD_RW(CAP, 8, 1)
        // Synchronized capture/compare input
        ADD_BITFIELD_RW(SCCI, 10, 1)
        // Synchronize capture source
        ADD_BITFIELD_RW(SCS, 11, 1)
        // Capture/compare input select
        ADD_BITFIELD_RW(CCIS, 12, 2)
        // Capture mode
        ADD_BITFIELD_RW(CM, 14, 2)
    END_TYPE()

    // No interrupt pending
    static const uint32_t TAxCCTL_CCIFG__CCIFG_0 = 0;
    // Interrupt pending
    static const uint32_t TAxCCTL_CCIFG__CCIFG_1 = 1;
    // No capture overflow occurred
    static const uint32_t TAxCCTL_COV__COV_0 = 0;
    // Capture overflow occurred
    static const uint32_t TAxCCTL_COV__COV_1 = 1;
    // Output low
    static const uint32_t TAxCCTL_OUT__OUT_0 = 0;
    // Output high
    static const uint32_t TAxCCTL_OUT__OUT_1 = 1;
    // Interrupt disabled
    static const uint32_t TAxCCTL_CCIE__CCIE_0 = 0;
    // Interrupt enabled
    static const uint32_t TAxCCTL_CCIE__CCIE_1 = 1;
    // OUT bit value
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_0 = 0;
    // Set
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_1 = 1;
    // Toggle/reset
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_2 = 2;
    // Set/reset
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_3 = 3;
    // Toggle
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_4 = 4;
    // Reset
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_5 = 5;
    // Toggle/set
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_6 = 6;
    // Reset/set
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_7 = 7;
    // Compare mode
    static const uint32_t TAxCCTL_CAP__CAP_0 = 0;
    // Capture mode
    static const uint32_t TAxCCTL_CAP__CAP_1 = 1;
    // Asynchronous capture
    static const uint32_t TAxCCTL_SCS__SCS_0 = 0;
    // Synchronous capture
    static const uint32_t TAxCCTL_SCS__SCS_1 = 1;
    // CCIxA
    static const uint32_t TAxCCTL_CCIS__CCIS_0 = 0;
    // CCIxB
    static const uint32_t TAxCCTL_CCIS__CCIS_1 = 1;
    // GND
    static const uint32_t TAxCCTL_CCIS__CCIS_2 = 2;
    // VCC
    static const uint32_t TAxCCTL_CCIS__CCIS_3 = 3;
    // No capture
    static const uint32_t TAxCCTL_CM__CM_0 = 0;
    // Capture on rising edge
    static const uint32_t TAxCCTL_CM__CM_1 = 1;
    // Capture on falling edge
    static const uint32_t TAxCCTL_CM__CM_2 = 2;
    // Capture on both rising and falling edges
    static const uint32_t TAxCCTL_CM__CM_3 = 3;

    // TimerA register
    // Reset value: 0x00000000
    typedef uint16_t TAxR_t;

    // Timer_A Capture/Compare  Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxCCR_t, uint16_t)
        // TimerA register
        ADD_BITFIELD_RW(TAxR, 0, 16)
    END_TYPE()

    // TimerAx Expansion 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxEX0_t, uint16_t)
        // Input divider expansion
        ADD_BITFIELD_RW(TAIDEX, 0, 3)
    END_TYPE()

    // Divide by 1
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_0 = 0;
    // Divide by 2
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_1 = 1;
    // Divide by 3
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_2 = 2;
    // Divide by 4
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_3 = 3;
    // Divide by 5
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_4 = 4;
    // Divide by 6
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_5 = 5;
    // Divide by 7
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_6 = 6;
    // Divide by 8
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_7 = 7;

    // TimerAx Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxIV_t, uint16_t)
        // TimerA interrupt vector value
        ADD_BITFIELD_RO(TAIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t TAxIV_TAIV__TAIV_0 = 0;
    // Interrupt Source: Capture/compare 1; Interrupt Flag: TAxCCR1 CCIFG; Interrupt Priority: Highest
    static const uint32_t TAxIV_TAIV__TAIV_2 = 2;
    // Interrupt Source: Capture/compare 2; Interrupt Flag: TAxCCR2 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_4 = 4;
    // Interrupt Source: Capture/compare 3; Interrupt Flag: TAxCCR3 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_6 = 6;
    // Interrupt Source: Capture/compare 4; Interrupt Flag: TAxCCR4 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_8 = 8;
    // Interrupt Source: Capture/compare 5; Interrupt Flag: TAxCCR5 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_10 = 10;
    // Interrupt Source: Capture/compare 6; Interrupt Flag: TAxCCR6 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_12 = 12;
    // Interrupt Source: Timer overflow; Interrupt Flag: TAxCTL TAIFG; Interrupt Priority: Lowest
    static const uint32_t TAxIV_TAIV__TAIV_14 = 14;

    struct TIMER_A1_t {
        TAxCTL_t                      TAxCTL;
        TAxCCTL_t                     TAxCCTL0;
        TAxCCTL_t                     TAxCCTL1;
        TAxCCTL_t                     TAxCCTL2;
        TAxCCTL_t                     TAxCCTL3;
        TAxCCTL_t                     TAxCCTL4;
        uint16_t                      reserved0[2];
        TAxR_t                        TAxR;
        TAxCCR_t                      TAxCCR0;
        TAxCCR_t                      TAxCCR1;
        TAxCCR_t                      TAxCCR2;
        TAxCCR_t                      TAxCCR3;
        TAxCCR_t                      TAxCCR4;
        uint16_t                      reserved1[2];
        TAxEX0_t                      TAxEX0;
        uint16_t                      reserved2[6];
        TAxIV_t                       TAxIV;
    };

    static TIMER_A1_t & TIMER_A1     = (*(TIMER_A1_t *)0x40000400);

} // _TIMER_A1_

// TIMER_A2
namespace _TIMER_A2_  {

    // TimerAx Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxCTL_t, uint16_t)
        // TimerA interrupt flag
        ADD_BITFIELD_RW(TAIFG, 0, 1)
        // TimerA interrupt enable
        ADD_BITFIELD_RW(TAIE, 1, 1)
        // TimerA clear
        ADD_BITFIELD_RW(TACLR, 2, 1)
        // Mode control
        ADD_BITFIELD_RW(MC, 4, 2)
        // Input divider
        ADD_BITFIELD_RW(ID, 6, 2)
        // TimerA clock source select
        ADD_BITFIELD_RW(TASSEL, 8, 2)
    END_TYPE()

    // No interrupt pending
    static const uint32_t TAxCTL_TAIFG__TAIFG_0 = 0;
    // Interrupt pending
    static const uint32_t TAxCTL_TAIFG__TAIFG_1 = 1;
    // Interrupt disabled
    static const uint32_t TAxCTL_TAIE__TAIE_0 = 0;
    // Interrupt enabled
    static const uint32_t TAxCTL_TAIE__TAIE_1 = 1;
    // Stop mode: Timer is halted
    static const uint32_t TAxCTL_MC__MC_0 = 0;
    // Up mode: Timer counts up to TAxCCR0
    static const uint32_t TAxCTL_MC__MC_1 = 1;
    // Continuous mode: Timer counts up to 0FFFFh
    static const uint32_t TAxCTL_MC__MC_2 = 2;
    // Up/down mode: Timer counts up to TAxCCR0 then down to 0000h
    static const uint32_t TAxCTL_MC__MC_3 = 3;
    // /1
    static const uint32_t TAxCTL_ID__ID_0 = 0;
    // /2
    static const uint32_t TAxCTL_ID__ID_1 = 1;
    // /4
    static const uint32_t TAxCTL_ID__ID_2 = 2;
    // /8
    static const uint32_t TAxCTL_ID__ID_3 = 3;
    // TAxCLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_0 = 0;
    // ACLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_1 = 1;
    // SMCLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_2 = 2;
    // INCLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_3 = 3;

    // Timer_A Capture/Compare Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxCCTL_t, uint16_t)
        // Capture/compare interrupt flag
        ADD_BITFIELD_RW(CCIFG, 0, 1)
        // Capture overflow
        ADD_BITFIELD_RW(COV, 1, 1)
        // Output
        ADD_BITFIELD_RW(OUT, 2, 1)
        // Capture/compare input
        ADD_BITFIELD_RO(CCI, 3, 1)
        // Capture/compare interrupt enable
        ADD_BITFIELD_RW(CCIE, 4, 1)
        // Output mode
        ADD_BITFIELD_RW(OUTMOD, 5, 3)
        // Capture mode
        ADD_BITFIELD_RW(CAP, 8, 1)
        // Synchronized capture/compare input
        ADD_BITFIELD_RW(SCCI, 10, 1)
        // Synchronize capture source
        ADD_BITFIELD_RW(SCS, 11, 1)
        // Capture/compare input select
        ADD_BITFIELD_RW(CCIS, 12, 2)
        // Capture mode
        ADD_BITFIELD_RW(CM, 14, 2)
    END_TYPE()

    // No interrupt pending
    static const uint32_t TAxCCTL_CCIFG__CCIFG_0 = 0;
    // Interrupt pending
    static const uint32_t TAxCCTL_CCIFG__CCIFG_1 = 1;
    // No capture overflow occurred
    static const uint32_t TAxCCTL_COV__COV_0 = 0;
    // Capture overflow occurred
    static const uint32_t TAxCCTL_COV__COV_1 = 1;
    // Output low
    static const uint32_t TAxCCTL_OUT__OUT_0 = 0;
    // Output high
    static const uint32_t TAxCCTL_OUT__OUT_1 = 1;
    // Interrupt disabled
    static const uint32_t TAxCCTL_CCIE__CCIE_0 = 0;
    // Interrupt enabled
    static const uint32_t TAxCCTL_CCIE__CCIE_1 = 1;
    // OUT bit value
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_0 = 0;
    // Set
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_1 = 1;
    // Toggle/reset
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_2 = 2;
    // Set/reset
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_3 = 3;
    // Toggle
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_4 = 4;
    // Reset
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_5 = 5;
    // Toggle/set
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_6 = 6;
    // Reset/set
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_7 = 7;
    // Compare mode
    static const uint32_t TAxCCTL_CAP__CAP_0 = 0;
    // Capture mode
    static const uint32_t TAxCCTL_CAP__CAP_1 = 1;
    // Asynchronous capture
    static const uint32_t TAxCCTL_SCS__SCS_0 = 0;
    // Synchronous capture
    static const uint32_t TAxCCTL_SCS__SCS_1 = 1;
    // CCIxA
    static const uint32_t TAxCCTL_CCIS__CCIS_0 = 0;
    // CCIxB
    static const uint32_t TAxCCTL_CCIS__CCIS_1 = 1;
    // GND
    static const uint32_t TAxCCTL_CCIS__CCIS_2 = 2;
    // VCC
    static const uint32_t TAxCCTL_CCIS__CCIS_3 = 3;
    // No capture
    static const uint32_t TAxCCTL_CM__CM_0 = 0;
    // Capture on rising edge
    static const uint32_t TAxCCTL_CM__CM_1 = 1;
    // Capture on falling edge
    static const uint32_t TAxCCTL_CM__CM_2 = 2;
    // Capture on both rising and falling edges
    static const uint32_t TAxCCTL_CM__CM_3 = 3;

    // TimerA register
    // Reset value: 0x00000000
    typedef uint16_t TAxR_t;

    // Timer_A Capture/Compare  Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxCCR_t, uint16_t)
        // TimerA register
        ADD_BITFIELD_RW(TAxR, 0, 16)
    END_TYPE()

    // TimerAx Expansion 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxEX0_t, uint16_t)
        // Input divider expansion
        ADD_BITFIELD_RW(TAIDEX, 0, 3)
    END_TYPE()

    // Divide by 1
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_0 = 0;
    // Divide by 2
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_1 = 1;
    // Divide by 3
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_2 = 2;
    // Divide by 4
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_3 = 3;
    // Divide by 5
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_4 = 4;
    // Divide by 6
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_5 = 5;
    // Divide by 7
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_6 = 6;
    // Divide by 8
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_7 = 7;

    // TimerAx Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxIV_t, uint16_t)
        // TimerA interrupt vector value
        ADD_BITFIELD_RO(TAIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t TAxIV_TAIV__TAIV_0 = 0;
    // Interrupt Source: Capture/compare 1; Interrupt Flag: TAxCCR1 CCIFG; Interrupt Priority: Highest
    static const uint32_t TAxIV_TAIV__TAIV_2 = 2;
    // Interrupt Source: Capture/compare 2; Interrupt Flag: TAxCCR2 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_4 = 4;
    // Interrupt Source: Capture/compare 3; Interrupt Flag: TAxCCR3 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_6 = 6;
    // Interrupt Source: Capture/compare 4; Interrupt Flag: TAxCCR4 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_8 = 8;
    // Interrupt Source: Capture/compare 5; Interrupt Flag: TAxCCR5 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_10 = 10;
    // Interrupt Source: Capture/compare 6; Interrupt Flag: TAxCCR6 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_12 = 12;
    // Interrupt Source: Timer overflow; Interrupt Flag: TAxCTL TAIFG; Interrupt Priority: Lowest
    static const uint32_t TAxIV_TAIV__TAIV_14 = 14;

    struct TIMER_A2_t {
        TAxCTL_t                      TAxCTL;
        TAxCCTL_t                     TAxCCTL0;
        TAxCCTL_t                     TAxCCTL1;
        TAxCCTL_t                     TAxCCTL2;
        TAxCCTL_t                     TAxCCTL3;
        TAxCCTL_t                     TAxCCTL4;
        uint16_t                      reserved0[2];
        TAxR_t                        TAxR;
        TAxCCR_t                      TAxCCR0;
        TAxCCR_t                      TAxCCR1;
        TAxCCR_t                      TAxCCR2;
        TAxCCR_t                      TAxCCR3;
        TAxCCR_t                      TAxCCR4;
        uint16_t                      reserved1[2];
        TAxEX0_t                      TAxEX0;
        uint16_t                      reserved2[6];
        TAxIV_t                       TAxIV;
    };

    static TIMER_A2_t & TIMER_A2     = (*(TIMER_A2_t *)0x40000800);

} // _TIMER_A2_

// TIMER_A3
namespace _TIMER_A3_  {

    // TimerAx Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxCTL_t, uint16_t)
        // TimerA interrupt flag
        ADD_BITFIELD_RW(TAIFG, 0, 1)
        // TimerA interrupt enable
        ADD_BITFIELD_RW(TAIE, 1, 1)
        // TimerA clear
        ADD_BITFIELD_RW(TACLR, 2, 1)
        // Mode control
        ADD_BITFIELD_RW(MC, 4, 2)
        // Input divider
        ADD_BITFIELD_RW(ID, 6, 2)
        // TimerA clock source select
        ADD_BITFIELD_RW(TASSEL, 8, 2)
    END_TYPE()

    // No interrupt pending
    static const uint32_t TAxCTL_TAIFG__TAIFG_0 = 0;
    // Interrupt pending
    static const uint32_t TAxCTL_TAIFG__TAIFG_1 = 1;
    // Interrupt disabled
    static const uint32_t TAxCTL_TAIE__TAIE_0 = 0;
    // Interrupt enabled
    static const uint32_t TAxCTL_TAIE__TAIE_1 = 1;
    // Stop mode: Timer is halted
    static const uint32_t TAxCTL_MC__MC_0 = 0;
    // Up mode: Timer counts up to TAxCCR0
    static const uint32_t TAxCTL_MC__MC_1 = 1;
    // Continuous mode: Timer counts up to 0FFFFh
    static const uint32_t TAxCTL_MC__MC_2 = 2;
    // Up/down mode: Timer counts up to TAxCCR0 then down to 0000h
    static const uint32_t TAxCTL_MC__MC_3 = 3;
    // /1
    static const uint32_t TAxCTL_ID__ID_0 = 0;
    // /2
    static const uint32_t TAxCTL_ID__ID_1 = 1;
    // /4
    static const uint32_t TAxCTL_ID__ID_2 = 2;
    // /8
    static const uint32_t TAxCTL_ID__ID_3 = 3;
    // TAxCLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_0 = 0;
    // ACLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_1 = 1;
    // SMCLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_2 = 2;
    // INCLK
    static const uint32_t TAxCTL_TASSEL__TASSEL_3 = 3;

    // Timer_A Capture/Compare Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxCCTL_t, uint16_t)
        // Capture/compare interrupt flag
        ADD_BITFIELD_RW(CCIFG, 0, 1)
        // Capture overflow
        ADD_BITFIELD_RW(COV, 1, 1)
        // Output
        ADD_BITFIELD_RW(OUT, 2, 1)
        // Capture/compare input
        ADD_BITFIELD_RO(CCI, 3, 1)
        // Capture/compare interrupt enable
        ADD_BITFIELD_RW(CCIE, 4, 1)
        // Output mode
        ADD_BITFIELD_RW(OUTMOD, 5, 3)
        // Capture mode
        ADD_BITFIELD_RW(CAP, 8, 1)
        // Synchronized capture/compare input
        ADD_BITFIELD_RW(SCCI, 10, 1)
        // Synchronize capture source
        ADD_BITFIELD_RW(SCS, 11, 1)
        // Capture/compare input select
        ADD_BITFIELD_RW(CCIS, 12, 2)
        // Capture mode
        ADD_BITFIELD_RW(CM, 14, 2)
    END_TYPE()

    // No interrupt pending
    static const uint32_t TAxCCTL_CCIFG__CCIFG_0 = 0;
    // Interrupt pending
    static const uint32_t TAxCCTL_CCIFG__CCIFG_1 = 1;
    // No capture overflow occurred
    static const uint32_t TAxCCTL_COV__COV_0 = 0;
    // Capture overflow occurred
    static const uint32_t TAxCCTL_COV__COV_1 = 1;
    // Output low
    static const uint32_t TAxCCTL_OUT__OUT_0 = 0;
    // Output high
    static const uint32_t TAxCCTL_OUT__OUT_1 = 1;
    // Interrupt disabled
    static const uint32_t TAxCCTL_CCIE__CCIE_0 = 0;
    // Interrupt enabled
    static const uint32_t TAxCCTL_CCIE__CCIE_1 = 1;
    // OUT bit value
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_0 = 0;
    // Set
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_1 = 1;
    // Toggle/reset
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_2 = 2;
    // Set/reset
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_3 = 3;
    // Toggle
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_4 = 4;
    // Reset
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_5 = 5;
    // Toggle/set
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_6 = 6;
    // Reset/set
    static const uint32_t TAxCCTL_OUTMOD__OUTMOD_7 = 7;
    // Compare mode
    static const uint32_t TAxCCTL_CAP__CAP_0 = 0;
    // Capture mode
    static const uint32_t TAxCCTL_CAP__CAP_1 = 1;
    // Asynchronous capture
    static const uint32_t TAxCCTL_SCS__SCS_0 = 0;
    // Synchronous capture
    static const uint32_t TAxCCTL_SCS__SCS_1 = 1;
    // CCIxA
    static const uint32_t TAxCCTL_CCIS__CCIS_0 = 0;
    // CCIxB
    static const uint32_t TAxCCTL_CCIS__CCIS_1 = 1;
    // GND
    static const uint32_t TAxCCTL_CCIS__CCIS_2 = 2;
    // VCC
    static const uint32_t TAxCCTL_CCIS__CCIS_3 = 3;
    // No capture
    static const uint32_t TAxCCTL_CM__CM_0 = 0;
    // Capture on rising edge
    static const uint32_t TAxCCTL_CM__CM_1 = 1;
    // Capture on falling edge
    static const uint32_t TAxCCTL_CM__CM_2 = 2;
    // Capture on both rising and falling edges
    static const uint32_t TAxCCTL_CM__CM_3 = 3;

    // TimerA register
    // Reset value: 0x00000000
    typedef uint16_t TAxR_t;

    // Timer_A Capture/Compare  Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxCCR_t, uint16_t)
        // TimerA register
        ADD_BITFIELD_RW(TAxR, 0, 16)
    END_TYPE()

    // TimerAx Expansion 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxEX0_t, uint16_t)
        // Input divider expansion
        ADD_BITFIELD_RW(TAIDEX, 0, 3)
    END_TYPE()

    // Divide by 1
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_0 = 0;
    // Divide by 2
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_1 = 1;
    // Divide by 3
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_2 = 2;
    // Divide by 4
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_3 = 3;
    // Divide by 5
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_4 = 4;
    // Divide by 6
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_5 = 5;
    // Divide by 7
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_6 = 6;
    // Divide by 8
    static const uint32_t TAxEX0_TAIDEX__TAIDEX_7 = 7;

    // TimerAx Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(TAxIV_t, uint16_t)
        // TimerA interrupt vector value
        ADD_BITFIELD_RO(TAIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t TAxIV_TAIV__TAIV_0 = 0;
    // Interrupt Source: Capture/compare 1; Interrupt Flag: TAxCCR1 CCIFG; Interrupt Priority: Highest
    static const uint32_t TAxIV_TAIV__TAIV_2 = 2;
    // Interrupt Source: Capture/compare 2; Interrupt Flag: TAxCCR2 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_4 = 4;
    // Interrupt Source: Capture/compare 3; Interrupt Flag: TAxCCR3 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_6 = 6;
    // Interrupt Source: Capture/compare 4; Interrupt Flag: TAxCCR4 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_8 = 8;
    // Interrupt Source: Capture/compare 5; Interrupt Flag: TAxCCR5 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_10 = 10;
    // Interrupt Source: Capture/compare 6; Interrupt Flag: TAxCCR6 CCIFG
    static const uint32_t TAxIV_TAIV__TAIV_12 = 12;
    // Interrupt Source: Timer overflow; Interrupt Flag: TAxCTL TAIFG; Interrupt Priority: Lowest
    static const uint32_t TAxIV_TAIV__TAIV_14 = 14;

    struct TIMER_A3_t {
        TAxCTL_t                      TAxCTL;
        TAxCCTL_t                     TAxCCTL0;
        TAxCCTL_t                     TAxCCTL1;
        TAxCCTL_t                     TAxCCTL2;
        TAxCCTL_t                     TAxCCTL3;
        TAxCCTL_t                     TAxCCTL4;
        uint16_t                      reserved0[2];
        TAxR_t                        TAxR;
        TAxCCR_t                      TAxCCR0;
        TAxCCR_t                      TAxCCR1;
        TAxCCR_t                      TAxCCR2;
        TAxCCR_t                      TAxCCR3;
        TAxCCR_t                      TAxCCR4;
        uint16_t                      reserved1[2];
        TAxEX0_t                      TAxEX0;
        uint16_t                      reserved2[6];
        TAxIV_t                       TAxIV;
    };

    static TIMER_A3_t & TIMER_A3     = (*(TIMER_A3_t *)0x40000c00);

} // _TIMER_A3_

// EUSCI_A0
namespace _EUSCI_A0_  {

    // eUSCI_Ax Control Word Register 0
    // Reset value: 0x00000001
    BEGIN_TYPE(UCAxCTLW0_t, uint16_t)
        // Software reset enable
        ADD_BITFIELD_RW(UCSWRST, 0, 1)
        // Transmit break
        ADD_BITFIELD_RW(UCTXBRK, 1, 1)
        // Transmit address
        ADD_BITFIELD_RW(UCTXADDR, 2, 1)
        // Dormant
        ADD_BITFIELD_RW(UCDORM, 3, 1)
        // Receive break character interrupt enable
        ADD_BITFIELD_RW(UCBRKIE, 4, 1)
        // Receive erroneous-character interrupt enable
        ADD_BITFIELD_RW(UCRXEIE, 5, 1)
        // eUSCI_A clock source select
        ADD_BITFIELD_RW(UCSSEL, 6, 2)
        // Synchronous mode enable
        ADD_BITFIELD_RW(UCSYNC, 8, 1)
        // eUSCI_A mode
        ADD_BITFIELD_RW(UCMODE, 9, 2)
        // Stop bit select
        ADD_BITFIELD_RW(UCSPB, 11, 1)
        // Character length
        ADD_BITFIELD_RW(UC7BIT, 12, 1)
        // MSB first select
        ADD_BITFIELD_RW(UCMSB, 13, 1)
        // Parity select
        ADD_BITFIELD_RW(UCPAR, 14, 1)
        // Parity enable
        ADD_BITFIELD_RW(UCPEN, 15, 1)
    END_TYPE()

    // Disabled. eUSCI_A reset released for operation
    static const uint32_t UCAxCTLW0_UCSWRST__UCSWRST_0 = 0;
    // Enabled. eUSCI_A logic held in reset state
    static const uint32_t UCAxCTLW0_UCSWRST__UCSWRST_1 = 1;
    // Next frame transmitted is not a break
    static const uint32_t UCAxCTLW0_UCTXBRK__UCTXBRK_0 = 0;
    // Next frame transmitted is a break or a break/synch
    static const uint32_t UCAxCTLW0_UCTXBRK__UCTXBRK_1 = 1;
    // Next frame transmitted is data
    static const uint32_t UCAxCTLW0_UCTXADDR__UCTXADDR_0 = 0;
    // Next frame transmitted is an address
    static const uint32_t UCAxCTLW0_UCTXADDR__UCTXADDR_1 = 1;
    // Not dormant. All received characters set UCRXIFG.
    static const uint32_t UCAxCTLW0_UCDORM__UCDORM_0 = 0;
    // Dormant. Only characters that are preceded by an idle-line or with address bit set UCRXIFG. In UART mode with automatic baud-rate detection, only the combination of a break and synch field sets UCRXIFG.
    static const uint32_t UCAxCTLW0_UCDORM__UCDORM_1 = 1;
    // Received break characters do not set UCRXIFG
    static const uint32_t UCAxCTLW0_UCBRKIE__UCBRKIE_0 = 0;
    // Received break characters set UCRXIFG
    static const uint32_t UCAxCTLW0_UCBRKIE__UCBRKIE_1 = 1;
    // Erroneous characters rejected and UCRXIFG is not set
    static const uint32_t UCAxCTLW0_UCRXEIE__UCRXEIE_0 = 0;
    // Erroneous characters received set UCRXIFG
    static const uint32_t UCAxCTLW0_UCRXEIE__UCRXEIE_1 = 1;
    // UCLK
    static const uint32_t UCAxCTLW0_UCSSEL__UCSSEL_0 = 0;
    // ACLK
    static const uint32_t UCAxCTLW0_UCSSEL__UCSSEL_1 = 1;
    // SMCLK
    static const uint32_t UCAxCTLW0_UCSSEL__UCSSEL_2 = 2;
    // Asynchronous mode
    static const uint32_t UCAxCTLW0_UCSYNC__UCSYNC_0 = 0;
    // Synchronous mode
    static const uint32_t UCAxCTLW0_UCSYNC__UCSYNC_1 = 1;
    // UART mode
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_0 = 0;
    // Idle-line multiprocessor mode
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_1 = 1;
    // Address-bit multiprocessor mode
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_2 = 2;
    // UART mode with automatic baud-rate detection
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_3 = 3;
    // One stop bit
    static const uint32_t UCAxCTLW0_UCSPB__UCSPB_0 = 0;
    // Two stop bits
    static const uint32_t UCAxCTLW0_UCSPB__UCSPB_1 = 1;
    // 8-bit data
    static const uint32_t UCAxCTLW0_UC7BIT__UC7BIT_0 = 0;
    // 7-bit data
    static const uint32_t UCAxCTLW0_UC7BIT__UC7BIT_1 = 1;
    // LSB first
    static const uint32_t UCAxCTLW0_UCMSB__UCMSB_0 = 0;
    // MSB first
    static const uint32_t UCAxCTLW0_UCMSB__UCMSB_1 = 1;
    // Odd parity
    static const uint32_t UCAxCTLW0_UCPAR__UCPAR_0 = 0;
    // Even parity
    static const uint32_t UCAxCTLW0_UCPAR__UCPAR_1 = 1;
    // Parity disabled
    static const uint32_t UCAxCTLW0_UCPEN__UCPEN_0 = 0;
    // Parity enabled. Parity bit is generated (UCAxTXD) and expected (UCAxRXD). In address-bit multiprocessor mode, the address bit is included in the parity calculation.
    static const uint32_t UCAxCTLW0_UCPEN__UCPEN_1 = 1;

    // eUSCI_Ax Control Word Register 1
    // Reset value: 0x00000003
    BEGIN_TYPE(UCAxCTLW1_t, uint16_t)
        // Deglitch time
        ADD_BITFIELD_RW(UCGLIT, 0, 2)
    END_TYPE()

    // Approximately 2 ns (equivalent of 1 delay element)
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_0 = 0;
    // Approximately 50 ns
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_1 = 1;
    // Approximately 100 ns
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_2 = 2;
    // Approximately 200 ns
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_3 = 3;

    // eUSCI_Ax Baud Rate Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxBRW_t, uint16_t)
        // Clock prescaler setting of the Baud rate generator
        ADD_BITFIELD_RW(UCBR, 0, 16)
    END_TYPE()

    // eUSCI_Ax Modulation Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxMCTLW_t, uint16_t)
        // Oversampling mode enabled
        ADD_BITFIELD_RW(UCOS16, 0, 1)
        // First modulation stage select
        ADD_BITFIELD_RW(UCBRF, 4, 4)
        // Second modulation stage select
        ADD_BITFIELD_RW(UCBRS, 8, 8)
    END_TYPE()

    // Disabled
    static const uint32_t UCAxMCTLW_UCOS16__UCOS16_0 = 0;
    // Enabled
    static const uint32_t UCAxMCTLW_UCOS16__UCOS16_1 = 1;

    // eUSCI_Ax Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxSTATW_t, uint16_t)
        // eUSCI_A busy
        ADD_BITFIELD_RO(UCBUSY, 0, 1)
        // Address received / Idle line detected
        ADD_BITFIELD_RW(UCADDR_UCIDLE, 1, 1)
        // Receive error flag
        ADD_BITFIELD_RW(UCRXERR, 2, 1)
        // Break detect flag
        ADD_BITFIELD_RW(UCBRK, 3, 1)
        // Parity error flag. When UCPEN = 0, UCPE is read as 0. UCPE is cleared when UCAxRXBUF is read.
        ADD_BITFIELD_RW(UCPE, 4, 1)
        // Overrun error flag
        ADD_BITFIELD_RW(UCOE, 5, 1)
        // Framing error flag
        ADD_BITFIELD_RW(UCFE, 6, 1)
        // Listen enable
        ADD_BITFIELD_RW(UCLISTEN, 7, 1)
    END_TYPE()

    // eUSCI_A inactive
    static const uint32_t UCAxSTATW_UCBUSY__UCBUSY_0 = 0;
    // eUSCI_A transmitting or receiving
    static const uint32_t UCAxSTATW_UCBUSY__UCBUSY_1 = 1;
    // No receive errors detected
    static const uint32_t UCAxSTATW_UCRXERR__UCRXERR_0 = 0;
    // Receive error detected
    static const uint32_t UCAxSTATW_UCRXERR__UCRXERR_1 = 1;
    // No break condition
    static const uint32_t UCAxSTATW_UCBRK__UCBRK_0 = 0;
    // Break condition occurred
    static const uint32_t UCAxSTATW_UCBRK__UCBRK_1 = 1;
    // No error
    static const uint32_t UCAxSTATW_UCPE__UCPE_0 = 0;
    // Character received with parity error
    static const uint32_t UCAxSTATW_UCPE__UCPE_1 = 1;
    // No error
    static const uint32_t UCAxSTATW_UCOE__UCOE_0 = 0;
    // Overrun error occurred
    static const uint32_t UCAxSTATW_UCOE__UCOE_1 = 1;
    // No error
    static const uint32_t UCAxSTATW_UCFE__UCFE_0 = 0;
    // Character received with low stop bit
    static const uint32_t UCAxSTATW_UCFE__UCFE_1 = 1;
    // Disabled
    static const uint32_t UCAxSTATW_UCLISTEN__UCLISTEN_0 = 0;
    // Enabled. UCAxTXD is internally fed back to the receiver
    static const uint32_t UCAxSTATW_UCLISTEN__UCLISTEN_1 = 1;

    // eUSCI_Ax Receive Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxRXBUF_t, uint16_t)
        // Receive data buffer
        ADD_BITFIELD_RO(UCRXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Ax Transmit Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxTXBUF_t, uint16_t)
        // Transmit data buffer
        ADD_BITFIELD_RW(UCTXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Ax Auto Baud Rate Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxABCTL_t, uint16_t)
        // Automatic baud-rate detect enable
        ADD_BITFIELD_RW(UCABDEN, 0, 1)
        // Break time out error
        ADD_BITFIELD_RW(UCBTOE, 2, 1)
        // Synch field time out error
        ADD_BITFIELD_RW(UCSTOE, 3, 1)
        // Break/synch delimiter length
        ADD_BITFIELD_RW(UCDELIM, 4, 2)
    END_TYPE()

    // Baud-rate detection disabled. Length of break and synch field is not measured.
    static const uint32_t UCAxABCTL_UCABDEN__UCABDEN_0 = 0;
    // Baud-rate detection enabled. Length of break and synch field is measured and baud-rate settings are changed accordingly.
    static const uint32_t UCAxABCTL_UCABDEN__UCABDEN_1 = 1;
    // No error
    static const uint32_t UCAxABCTL_UCBTOE__UCBTOE_0 = 0;
    // Length of break field exceeded 22 bit times
    static const uint32_t UCAxABCTL_UCBTOE__UCBTOE_1 = 1;
    // No error
    static const uint32_t UCAxABCTL_UCSTOE__UCSTOE_0 = 0;
    // Length of synch field exceeded measurable time
    static const uint32_t UCAxABCTL_UCSTOE__UCSTOE_1 = 1;
    // 1 bit time
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_0 = 0;
    // 2 bit times
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_1 = 1;
    // 3 bit times
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_2 = 2;
    // 4 bit times
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_3 = 3;

    // eUSCI_Ax IrDA Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxIRCTL_t, uint16_t)
        // IrDA encoder/decoder enable
        ADD_BITFIELD_RW(UCIREN, 0, 1)
        // IrDA transmit pulse clock select
        ADD_BITFIELD_RW(UCIRTXCLK, 1, 1)
        // Transmit pulse length
        ADD_BITFIELD_RW(UCIRTXPL, 2, 6)
        // IrDA receive filter enabled
        ADD_BITFIELD_RW(UCIRRXFE, 8, 1)
        // IrDA receive input UCAxRXD polarity
        ADD_BITFIELD_RW(UCIRRXPL, 9, 1)
        // Receive filter length
        ADD_BITFIELD_RW(UCIRRXFL, 10, 4)
    END_TYPE()

    // IrDA encoder/decoder disabled
    static const uint32_t UCAxIRCTL_UCIREN__UCIREN_0 = 0;
    // IrDA encoder/decoder enabled
    static const uint32_t UCAxIRCTL_UCIREN__UCIREN_1 = 1;
    // BRCLK
    static const uint32_t UCAxIRCTL_UCIRTXCLK__UCIRTXCLK_0 = 0;
    // BITCLK16 when UCOS16 = 1. Otherwise, BRCLK.
    static const uint32_t UCAxIRCTL_UCIRTXCLK__UCIRTXCLK_1 = 1;
    // Receive filter disabled
    static const uint32_t UCAxIRCTL_UCIRRXFE__UCIRRXFE_0 = 0;
    // Receive filter enabled
    static const uint32_t UCAxIRCTL_UCIRRXFE__UCIRRXFE_1 = 1;
    // IrDA transceiver delivers a high pulse when a light pulse is seen
    static const uint32_t UCAxIRCTL_UCIRRXPL__UCIRRXPL_0 = 0;
    // IrDA transceiver delivers a low pulse when a light pulse is seen
    static const uint32_t UCAxIRCTL_UCIRRXPL__UCIRRXPL_1 = 1;

    // eUSCI_Ax Interrupt Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxIE_t, uint16_t)
        // Receive interrupt enable
        ADD_BITFIELD_RW(UCRXIE, 0, 1)
        // Transmit interrupt enable
        ADD_BITFIELD_RW(UCTXIE, 1, 1)
        // Start bit interrupt enable
        ADD_BITFIELD_RW(UCSTTIE, 2, 1)
        // Transmit complete interrupt enable
        ADD_BITFIELD_RW(UCTXCPTIE, 3, 1)
    END_TYPE()

    // Interrupt disabled
    static const uint32_t UCAxIE_UCRXIE__UCRXIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCRXIE__UCRXIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCAxIE_UCTXIE__UCTXIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCTXIE__UCTXIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCAxIE_UCSTTIE__UCSTTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCSTTIE__UCSTTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCAxIE_UCTXCPTIE__UCTXCPTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCTXCPTIE__UCTXCPTIE_1 = 1;

    // eUSCI_Ax Interrupt Flag Register
    // Reset value: 0x00000002
    BEGIN_TYPE(UCAxIFG_t, uint16_t)
        // Receive interrupt flag
        ADD_BITFIELD_RW(UCRXIFG, 0, 1)
        // Transmit interrupt flag
        ADD_BITFIELD_RW(UCTXIFG, 1, 1)
        // Start bit interrupt flag
        ADD_BITFIELD_RW(UCSTTIFG, 2, 1)
        // Transmit ready interrupt enable
        ADD_BITFIELD_RW(UCTXCPTIFG, 3, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCAxIFG_UCRXIFG__UCRXIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCRXIFG__UCRXIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCAxIFG_UCTXIFG__UCTXIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCTXIFG__UCTXIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCAxIFG_UCSTTIFG__UCSTTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCSTTIFG__UCSTTIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCAxIFG_UCTXCPTIFG__UCTXCPTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCTXCPTIFG__UCTXCPTIFG_1 = 1;

    // eUSCI_Ax Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxIV_t, uint16_t)
        // eUSCI_A interrupt vector value
        ADD_BITFIELD_RO(UCIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCAxIV_UCIV__UCIV_0 = 0;
    // Interrupt Source: Receive buffer full; Interrupt Flag: UCRXIFG; Interrupt Priority: Highest
    static const uint32_t UCAxIV_UCIV__UCIV_2 = 2;
    // Interrupt Source: Transmit buffer empty; Interrupt Flag: UCTXIFG
    static const uint32_t UCAxIV_UCIV__UCIV_4 = 4;
    // Interrupt Source: Start bit received; Interrupt Flag: UCSTTIFG
    static const uint32_t UCAxIV_UCIV__UCIV_6 = 6;
    // Interrupt Source: Transmit complete; Interrupt Flag: UCTXCPTIFG; Interrupt Priority: Lowest
    static const uint32_t UCAxIV_UCIV__UCIV_8 = 8;

    struct EUSCI_A0_t {
        UCAxCTLW0_t                   UCAxCTLW0;
        UCAxCTLW1_t                   UCAxCTLW1;
        uint16_t                      reserved0;
        UCAxBRW_t                     UCAxBRW;
        UCAxMCTLW_t                   UCAxMCTLW;
        UCAxSTATW_t                   UCAxSTATW;
        UCAxRXBUF_t                   UCAxRXBUF;
        UCAxTXBUF_t                   UCAxTXBUF;
        UCAxABCTL_t                   UCAxABCTL;
        UCAxIRCTL_t                   UCAxIRCTL;
        uint16_t                      reserved1[3];
        UCAxIE_t                      UCAxIE;
        UCAxIFG_t                     UCAxIFG;
        UCAxIV_t                      UCAxIV;
    };

    static EUSCI_A0_t & EUSCI_A0     = (*(EUSCI_A0_t *)0x40001000);

} // _EUSCI_A0_

// EUSCI_A1
namespace _EUSCI_A1_  {

    // eUSCI_Ax Control Word Register 0
    // Reset value: 0x00000001
    BEGIN_TYPE(UCAxCTLW0_t, uint16_t)
        // Software reset enable
        ADD_BITFIELD_RW(UCSWRST, 0, 1)
        // Transmit break
        ADD_BITFIELD_RW(UCTXBRK, 1, 1)
        // Transmit address
        ADD_BITFIELD_RW(UCTXADDR, 2, 1)
        // Dormant
        ADD_BITFIELD_RW(UCDORM, 3, 1)
        // Receive break character interrupt enable
        ADD_BITFIELD_RW(UCBRKIE, 4, 1)
        // Receive erroneous-character interrupt enable
        ADD_BITFIELD_RW(UCRXEIE, 5, 1)
        // eUSCI_A clock source select
        ADD_BITFIELD_RW(UCSSEL, 6, 2)
        // Synchronous mode enable
        ADD_BITFIELD_RW(UCSYNC, 8, 1)
        // eUSCI_A mode
        ADD_BITFIELD_RW(UCMODE, 9, 2)
        // Stop bit select
        ADD_BITFIELD_RW(UCSPB, 11, 1)
        // Character length
        ADD_BITFIELD_RW(UC7BIT, 12, 1)
        // MSB first select
        ADD_BITFIELD_RW(UCMSB, 13, 1)
        // Parity select
        ADD_BITFIELD_RW(UCPAR, 14, 1)
        // Parity enable
        ADD_BITFIELD_RW(UCPEN, 15, 1)
    END_TYPE()

    // Disabled. eUSCI_A reset released for operation
    static const uint32_t UCAxCTLW0_UCSWRST__UCSWRST_0 = 0;
    // Enabled. eUSCI_A logic held in reset state
    static const uint32_t UCAxCTLW0_UCSWRST__UCSWRST_1 = 1;
    // Next frame transmitted is not a break
    static const uint32_t UCAxCTLW0_UCTXBRK__UCTXBRK_0 = 0;
    // Next frame transmitted is a break or a break/synch
    static const uint32_t UCAxCTLW0_UCTXBRK__UCTXBRK_1 = 1;
    // Next frame transmitted is data
    static const uint32_t UCAxCTLW0_UCTXADDR__UCTXADDR_0 = 0;
    // Next frame transmitted is an address
    static const uint32_t UCAxCTLW0_UCTXADDR__UCTXADDR_1 = 1;
    // Not dormant. All received characters set UCRXIFG.
    static const uint32_t UCAxCTLW0_UCDORM__UCDORM_0 = 0;
    // Dormant. Only characters that are preceded by an idle-line or with address bit set UCRXIFG. In UART mode with automatic baud-rate detection, only the combination of a break and synch field sets UCRXIFG.
    static const uint32_t UCAxCTLW0_UCDORM__UCDORM_1 = 1;
    // Received break characters do not set UCRXIFG
    static const uint32_t UCAxCTLW0_UCBRKIE__UCBRKIE_0 = 0;
    // Received break characters set UCRXIFG
    static const uint32_t UCAxCTLW0_UCBRKIE__UCBRKIE_1 = 1;
    // Erroneous characters rejected and UCRXIFG is not set
    static const uint32_t UCAxCTLW0_UCRXEIE__UCRXEIE_0 = 0;
    // Erroneous characters received set UCRXIFG
    static const uint32_t UCAxCTLW0_UCRXEIE__UCRXEIE_1 = 1;
    // UCLK
    static const uint32_t UCAxCTLW0_UCSSEL__UCSSEL_0 = 0;
    // ACLK
    static const uint32_t UCAxCTLW0_UCSSEL__UCSSEL_1 = 1;
    // SMCLK
    static const uint32_t UCAxCTLW0_UCSSEL__UCSSEL_2 = 2;
    // Asynchronous mode
    static const uint32_t UCAxCTLW0_UCSYNC__UCSYNC_0 = 0;
    // Synchronous mode
    static const uint32_t UCAxCTLW0_UCSYNC__UCSYNC_1 = 1;
    // UART mode
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_0 = 0;
    // Idle-line multiprocessor mode
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_1 = 1;
    // Address-bit multiprocessor mode
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_2 = 2;
    // UART mode with automatic baud-rate detection
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_3 = 3;
    // One stop bit
    static const uint32_t UCAxCTLW0_UCSPB__UCSPB_0 = 0;
    // Two stop bits
    static const uint32_t UCAxCTLW0_UCSPB__UCSPB_1 = 1;
    // 8-bit data
    static const uint32_t UCAxCTLW0_UC7BIT__UC7BIT_0 = 0;
    // 7-bit data
    static const uint32_t UCAxCTLW0_UC7BIT__UC7BIT_1 = 1;
    // LSB first
    static const uint32_t UCAxCTLW0_UCMSB__UCMSB_0 = 0;
    // MSB first
    static const uint32_t UCAxCTLW0_UCMSB__UCMSB_1 = 1;
    // Odd parity
    static const uint32_t UCAxCTLW0_UCPAR__UCPAR_0 = 0;
    // Even parity
    static const uint32_t UCAxCTLW0_UCPAR__UCPAR_1 = 1;
    // Parity disabled
    static const uint32_t UCAxCTLW0_UCPEN__UCPEN_0 = 0;
    // Parity enabled. Parity bit is generated (UCAxTXD) and expected (UCAxRXD). In address-bit multiprocessor mode, the address bit is included in the parity calculation.
    static const uint32_t UCAxCTLW0_UCPEN__UCPEN_1 = 1;

    // eUSCI_Ax Control Word Register 1
    // Reset value: 0x00000003
    BEGIN_TYPE(UCAxCTLW1_t, uint16_t)
        // Deglitch time
        ADD_BITFIELD_RW(UCGLIT, 0, 2)
    END_TYPE()

    // Approximately 2 ns (equivalent of 1 delay element)
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_0 = 0;
    // Approximately 50 ns
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_1 = 1;
    // Approximately 100 ns
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_2 = 2;
    // Approximately 200 ns
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_3 = 3;

    // eUSCI_Ax Baud Rate Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxBRW_t, uint16_t)
        // Clock prescaler setting of the Baud rate generator
        ADD_BITFIELD_RW(UCBR, 0, 16)
    END_TYPE()

    // eUSCI_Ax Modulation Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxMCTLW_t, uint16_t)
        // Oversampling mode enabled
        ADD_BITFIELD_RW(UCOS16, 0, 1)
        // First modulation stage select
        ADD_BITFIELD_RW(UCBRF, 4, 4)
        // Second modulation stage select
        ADD_BITFIELD_RW(UCBRS, 8, 8)
    END_TYPE()

    // Disabled
    static const uint32_t UCAxMCTLW_UCOS16__UCOS16_0 = 0;
    // Enabled
    static const uint32_t UCAxMCTLW_UCOS16__UCOS16_1 = 1;

    // eUSCI_Ax Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxSTATW_t, uint16_t)
        // eUSCI_A busy
        ADD_BITFIELD_RO(UCBUSY, 0, 1)
        // Address received / Idle line detected
        ADD_BITFIELD_RW(UCADDR_UCIDLE, 1, 1)
        // Receive error flag
        ADD_BITFIELD_RW(UCRXERR, 2, 1)
        // Break detect flag
        ADD_BITFIELD_RW(UCBRK, 3, 1)
        // Parity error flag. When UCPEN = 0, UCPE is read as 0. UCPE is cleared when UCAxRXBUF is read.
        ADD_BITFIELD_RW(UCPE, 4, 1)
        // Overrun error flag
        ADD_BITFIELD_RW(UCOE, 5, 1)
        // Framing error flag
        ADD_BITFIELD_RW(UCFE, 6, 1)
        // Listen enable
        ADD_BITFIELD_RW(UCLISTEN, 7, 1)
    END_TYPE()

    // eUSCI_A inactive
    static const uint32_t UCAxSTATW_UCBUSY__UCBUSY_0 = 0;
    // eUSCI_A transmitting or receiving
    static const uint32_t UCAxSTATW_UCBUSY__UCBUSY_1 = 1;
    // No receive errors detected
    static const uint32_t UCAxSTATW_UCRXERR__UCRXERR_0 = 0;
    // Receive error detected
    static const uint32_t UCAxSTATW_UCRXERR__UCRXERR_1 = 1;
    // No break condition
    static const uint32_t UCAxSTATW_UCBRK__UCBRK_0 = 0;
    // Break condition occurred
    static const uint32_t UCAxSTATW_UCBRK__UCBRK_1 = 1;
    // No error
    static const uint32_t UCAxSTATW_UCPE__UCPE_0 = 0;
    // Character received with parity error
    static const uint32_t UCAxSTATW_UCPE__UCPE_1 = 1;
    // No error
    static const uint32_t UCAxSTATW_UCOE__UCOE_0 = 0;
    // Overrun error occurred
    static const uint32_t UCAxSTATW_UCOE__UCOE_1 = 1;
    // No error
    static const uint32_t UCAxSTATW_UCFE__UCFE_0 = 0;
    // Character received with low stop bit
    static const uint32_t UCAxSTATW_UCFE__UCFE_1 = 1;
    // Disabled
    static const uint32_t UCAxSTATW_UCLISTEN__UCLISTEN_0 = 0;
    // Enabled. UCAxTXD is internally fed back to the receiver
    static const uint32_t UCAxSTATW_UCLISTEN__UCLISTEN_1 = 1;

    // eUSCI_Ax Receive Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxRXBUF_t, uint16_t)
        // Receive data buffer
        ADD_BITFIELD_RO(UCRXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Ax Transmit Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxTXBUF_t, uint16_t)
        // Transmit data buffer
        ADD_BITFIELD_RW(UCTXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Ax Auto Baud Rate Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxABCTL_t, uint16_t)
        // Automatic baud-rate detect enable
        ADD_BITFIELD_RW(UCABDEN, 0, 1)
        // Break time out error
        ADD_BITFIELD_RW(UCBTOE, 2, 1)
        // Synch field time out error
        ADD_BITFIELD_RW(UCSTOE, 3, 1)
        // Break/synch delimiter length
        ADD_BITFIELD_RW(UCDELIM, 4, 2)
    END_TYPE()

    // Baud-rate detection disabled. Length of break and synch field is not measured.
    static const uint32_t UCAxABCTL_UCABDEN__UCABDEN_0 = 0;
    // Baud-rate detection enabled. Length of break and synch field is measured and baud-rate settings are changed accordingly.
    static const uint32_t UCAxABCTL_UCABDEN__UCABDEN_1 = 1;
    // No error
    static const uint32_t UCAxABCTL_UCBTOE__UCBTOE_0 = 0;
    // Length of break field exceeded 22 bit times
    static const uint32_t UCAxABCTL_UCBTOE__UCBTOE_1 = 1;
    // No error
    static const uint32_t UCAxABCTL_UCSTOE__UCSTOE_0 = 0;
    // Length of synch field exceeded measurable time
    static const uint32_t UCAxABCTL_UCSTOE__UCSTOE_1 = 1;
    // 1 bit time
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_0 = 0;
    // 2 bit times
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_1 = 1;
    // 3 bit times
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_2 = 2;
    // 4 bit times
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_3 = 3;

    // eUSCI_Ax IrDA Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxIRCTL_t, uint16_t)
        // IrDA encoder/decoder enable
        ADD_BITFIELD_RW(UCIREN, 0, 1)
        // IrDA transmit pulse clock select
        ADD_BITFIELD_RW(UCIRTXCLK, 1, 1)
        // Transmit pulse length
        ADD_BITFIELD_RW(UCIRTXPL, 2, 6)
        // IrDA receive filter enabled
        ADD_BITFIELD_RW(UCIRRXFE, 8, 1)
        // IrDA receive input UCAxRXD polarity
        ADD_BITFIELD_RW(UCIRRXPL, 9, 1)
        // Receive filter length
        ADD_BITFIELD_RW(UCIRRXFL, 10, 4)
    END_TYPE()

    // IrDA encoder/decoder disabled
    static const uint32_t UCAxIRCTL_UCIREN__UCIREN_0 = 0;
    // IrDA encoder/decoder enabled
    static const uint32_t UCAxIRCTL_UCIREN__UCIREN_1 = 1;
    // BRCLK
    static const uint32_t UCAxIRCTL_UCIRTXCLK__UCIRTXCLK_0 = 0;
    // BITCLK16 when UCOS16 = 1. Otherwise, BRCLK.
    static const uint32_t UCAxIRCTL_UCIRTXCLK__UCIRTXCLK_1 = 1;
    // Receive filter disabled
    static const uint32_t UCAxIRCTL_UCIRRXFE__UCIRRXFE_0 = 0;
    // Receive filter enabled
    static const uint32_t UCAxIRCTL_UCIRRXFE__UCIRRXFE_1 = 1;
    // IrDA transceiver delivers a high pulse when a light pulse is seen
    static const uint32_t UCAxIRCTL_UCIRRXPL__UCIRRXPL_0 = 0;
    // IrDA transceiver delivers a low pulse when a light pulse is seen
    static const uint32_t UCAxIRCTL_UCIRRXPL__UCIRRXPL_1 = 1;

    // eUSCI_Ax Interrupt Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxIE_t, uint16_t)
        // Receive interrupt enable
        ADD_BITFIELD_RW(UCRXIE, 0, 1)
        // Transmit interrupt enable
        ADD_BITFIELD_RW(UCTXIE, 1, 1)
        // Start bit interrupt enable
        ADD_BITFIELD_RW(UCSTTIE, 2, 1)
        // Transmit complete interrupt enable
        ADD_BITFIELD_RW(UCTXCPTIE, 3, 1)
    END_TYPE()

    // Interrupt disabled
    static const uint32_t UCAxIE_UCRXIE__UCRXIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCRXIE__UCRXIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCAxIE_UCTXIE__UCTXIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCTXIE__UCTXIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCAxIE_UCSTTIE__UCSTTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCSTTIE__UCSTTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCAxIE_UCTXCPTIE__UCTXCPTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCTXCPTIE__UCTXCPTIE_1 = 1;

    // eUSCI_Ax Interrupt Flag Register
    // Reset value: 0x00000002
    BEGIN_TYPE(UCAxIFG_t, uint16_t)
        // Receive interrupt flag
        ADD_BITFIELD_RW(UCRXIFG, 0, 1)
        // Transmit interrupt flag
        ADD_BITFIELD_RW(UCTXIFG, 1, 1)
        // Start bit interrupt flag
        ADD_BITFIELD_RW(UCSTTIFG, 2, 1)
        // Transmit ready interrupt enable
        ADD_BITFIELD_RW(UCTXCPTIFG, 3, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCAxIFG_UCRXIFG__UCRXIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCRXIFG__UCRXIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCAxIFG_UCTXIFG__UCTXIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCTXIFG__UCTXIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCAxIFG_UCSTTIFG__UCSTTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCSTTIFG__UCSTTIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCAxIFG_UCTXCPTIFG__UCTXCPTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCTXCPTIFG__UCTXCPTIFG_1 = 1;

    // eUSCI_Ax Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxIV_t, uint16_t)
        // eUSCI_A interrupt vector value
        ADD_BITFIELD_RO(UCIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCAxIV_UCIV__UCIV_0 = 0;
    // Interrupt Source: Receive buffer full; Interrupt Flag: UCRXIFG; Interrupt Priority: Highest
    static const uint32_t UCAxIV_UCIV__UCIV_2 = 2;
    // Interrupt Source: Transmit buffer empty; Interrupt Flag: UCTXIFG
    static const uint32_t UCAxIV_UCIV__UCIV_4 = 4;
    // Interrupt Source: Start bit received; Interrupt Flag: UCSTTIFG
    static const uint32_t UCAxIV_UCIV__UCIV_6 = 6;
    // Interrupt Source: Transmit complete; Interrupt Flag: UCTXCPTIFG; Interrupt Priority: Lowest
    static const uint32_t UCAxIV_UCIV__UCIV_8 = 8;

    struct EUSCI_A1_t {
        UCAxCTLW0_t                   UCAxCTLW0;
        UCAxCTLW1_t                   UCAxCTLW1;
        uint16_t                      reserved0;
        UCAxBRW_t                     UCAxBRW;
        UCAxMCTLW_t                   UCAxMCTLW;
        UCAxSTATW_t                   UCAxSTATW;
        UCAxRXBUF_t                   UCAxRXBUF;
        UCAxTXBUF_t                   UCAxTXBUF;
        UCAxABCTL_t                   UCAxABCTL;
        UCAxIRCTL_t                   UCAxIRCTL;
        uint16_t                      reserved1[3];
        UCAxIE_t                      UCAxIE;
        UCAxIFG_t                     UCAxIFG;
        UCAxIV_t                      UCAxIV;
    };

    static EUSCI_A1_t & EUSCI_A1     = (*(EUSCI_A1_t *)0x40001400);

} // _EUSCI_A1_

// EUSCI_A2
namespace _EUSCI_A2_  {

    // eUSCI_Ax Control Word Register 0
    // Reset value: 0x00000001
    BEGIN_TYPE(UCAxCTLW0_t, uint16_t)
        // Software reset enable
        ADD_BITFIELD_RW(UCSWRST, 0, 1)
        // Transmit break
        ADD_BITFIELD_RW(UCTXBRK, 1, 1)
        // Transmit address
        ADD_BITFIELD_RW(UCTXADDR, 2, 1)
        // Dormant
        ADD_BITFIELD_RW(UCDORM, 3, 1)
        // Receive break character interrupt enable
        ADD_BITFIELD_RW(UCBRKIE, 4, 1)
        // Receive erroneous-character interrupt enable
        ADD_BITFIELD_RW(UCRXEIE, 5, 1)
        // eUSCI_A clock source select
        ADD_BITFIELD_RW(UCSSEL, 6, 2)
        // Synchronous mode enable
        ADD_BITFIELD_RW(UCSYNC, 8, 1)
        // eUSCI_A mode
        ADD_BITFIELD_RW(UCMODE, 9, 2)
        // Stop bit select
        ADD_BITFIELD_RW(UCSPB, 11, 1)
        // Character length
        ADD_BITFIELD_RW(UC7BIT, 12, 1)
        // MSB first select
        ADD_BITFIELD_RW(UCMSB, 13, 1)
        // Parity select
        ADD_BITFIELD_RW(UCPAR, 14, 1)
        // Parity enable
        ADD_BITFIELD_RW(UCPEN, 15, 1)
    END_TYPE()

    // Disabled. eUSCI_A reset released for operation
    static const uint32_t UCAxCTLW0_UCSWRST__UCSWRST_0 = 0;
    // Enabled. eUSCI_A logic held in reset state
    static const uint32_t UCAxCTLW0_UCSWRST__UCSWRST_1 = 1;
    // Next frame transmitted is not a break
    static const uint32_t UCAxCTLW0_UCTXBRK__UCTXBRK_0 = 0;
    // Next frame transmitted is a break or a break/synch
    static const uint32_t UCAxCTLW0_UCTXBRK__UCTXBRK_1 = 1;
    // Next frame transmitted is data
    static const uint32_t UCAxCTLW0_UCTXADDR__UCTXADDR_0 = 0;
    // Next frame transmitted is an address
    static const uint32_t UCAxCTLW0_UCTXADDR__UCTXADDR_1 = 1;
    // Not dormant. All received characters set UCRXIFG.
    static const uint32_t UCAxCTLW0_UCDORM__UCDORM_0 = 0;
    // Dormant. Only characters that are preceded by an idle-line or with address bit set UCRXIFG. In UART mode with automatic baud-rate detection, only the combination of a break and synch field sets UCRXIFG.
    static const uint32_t UCAxCTLW0_UCDORM__UCDORM_1 = 1;
    // Received break characters do not set UCRXIFG
    static const uint32_t UCAxCTLW0_UCBRKIE__UCBRKIE_0 = 0;
    // Received break characters set UCRXIFG
    static const uint32_t UCAxCTLW0_UCBRKIE__UCBRKIE_1 = 1;
    // Erroneous characters rejected and UCRXIFG is not set
    static const uint32_t UCAxCTLW0_UCRXEIE__UCRXEIE_0 = 0;
    // Erroneous characters received set UCRXIFG
    static const uint32_t UCAxCTLW0_UCRXEIE__UCRXEIE_1 = 1;
    // UCLK
    static const uint32_t UCAxCTLW0_UCSSEL__UCSSEL_0 = 0;
    // ACLK
    static const uint32_t UCAxCTLW0_UCSSEL__UCSSEL_1 = 1;
    // SMCLK
    static const uint32_t UCAxCTLW0_UCSSEL__UCSSEL_2 = 2;
    // Asynchronous mode
    static const uint32_t UCAxCTLW0_UCSYNC__UCSYNC_0 = 0;
    // Synchronous mode
    static const uint32_t UCAxCTLW0_UCSYNC__UCSYNC_1 = 1;
    // UART mode
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_0 = 0;
    // Idle-line multiprocessor mode
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_1 = 1;
    // Address-bit multiprocessor mode
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_2 = 2;
    // UART mode with automatic baud-rate detection
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_3 = 3;
    // One stop bit
    static const uint32_t UCAxCTLW0_UCSPB__UCSPB_0 = 0;
    // Two stop bits
    static const uint32_t UCAxCTLW0_UCSPB__UCSPB_1 = 1;
    // 8-bit data
    static const uint32_t UCAxCTLW0_UC7BIT__UC7BIT_0 = 0;
    // 7-bit data
    static const uint32_t UCAxCTLW0_UC7BIT__UC7BIT_1 = 1;
    // LSB first
    static const uint32_t UCAxCTLW0_UCMSB__UCMSB_0 = 0;
    // MSB first
    static const uint32_t UCAxCTLW0_UCMSB__UCMSB_1 = 1;
    // Odd parity
    static const uint32_t UCAxCTLW0_UCPAR__UCPAR_0 = 0;
    // Even parity
    static const uint32_t UCAxCTLW0_UCPAR__UCPAR_1 = 1;
    // Parity disabled
    static const uint32_t UCAxCTLW0_UCPEN__UCPEN_0 = 0;
    // Parity enabled. Parity bit is generated (UCAxTXD) and expected (UCAxRXD). In address-bit multiprocessor mode, the address bit is included in the parity calculation.
    static const uint32_t UCAxCTLW0_UCPEN__UCPEN_1 = 1;

    // eUSCI_Ax Control Word Register 1
    // Reset value: 0x00000003
    BEGIN_TYPE(UCAxCTLW1_t, uint16_t)
        // Deglitch time
        ADD_BITFIELD_RW(UCGLIT, 0, 2)
    END_TYPE()

    // Approximately 2 ns (equivalent of 1 delay element)
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_0 = 0;
    // Approximately 50 ns
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_1 = 1;
    // Approximately 100 ns
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_2 = 2;
    // Approximately 200 ns
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_3 = 3;

    // eUSCI_Ax Baud Rate Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxBRW_t, uint16_t)
        // Clock prescaler setting of the Baud rate generator
        ADD_BITFIELD_RW(UCBR, 0, 16)
    END_TYPE()

    // eUSCI_Ax Modulation Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxMCTLW_t, uint16_t)
        // Oversampling mode enabled
        ADD_BITFIELD_RW(UCOS16, 0, 1)
        // First modulation stage select
        ADD_BITFIELD_RW(UCBRF, 4, 4)
        // Second modulation stage select
        ADD_BITFIELD_RW(UCBRS, 8, 8)
    END_TYPE()

    // Disabled
    static const uint32_t UCAxMCTLW_UCOS16__UCOS16_0 = 0;
    // Enabled
    static const uint32_t UCAxMCTLW_UCOS16__UCOS16_1 = 1;

    // eUSCI_Ax Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxSTATW_t, uint16_t)
        // eUSCI_A busy
        ADD_BITFIELD_RO(UCBUSY, 0, 1)
        // Address received / Idle line detected
        ADD_BITFIELD_RW(UCADDR_UCIDLE, 1, 1)
        // Receive error flag
        ADD_BITFIELD_RW(UCRXERR, 2, 1)
        // Break detect flag
        ADD_BITFIELD_RW(UCBRK, 3, 1)
        // Parity error flag. When UCPEN = 0, UCPE is read as 0. UCPE is cleared when UCAxRXBUF is read.
        ADD_BITFIELD_RW(UCPE, 4, 1)
        // Overrun error flag
        ADD_BITFIELD_RW(UCOE, 5, 1)
        // Framing error flag
        ADD_BITFIELD_RW(UCFE, 6, 1)
        // Listen enable
        ADD_BITFIELD_RW(UCLISTEN, 7, 1)
    END_TYPE()

    // eUSCI_A inactive
    static const uint32_t UCAxSTATW_UCBUSY__UCBUSY_0 = 0;
    // eUSCI_A transmitting or receiving
    static const uint32_t UCAxSTATW_UCBUSY__UCBUSY_1 = 1;
    // No receive errors detected
    static const uint32_t UCAxSTATW_UCRXERR__UCRXERR_0 = 0;
    // Receive error detected
    static const uint32_t UCAxSTATW_UCRXERR__UCRXERR_1 = 1;
    // No break condition
    static const uint32_t UCAxSTATW_UCBRK__UCBRK_0 = 0;
    // Break condition occurred
    static const uint32_t UCAxSTATW_UCBRK__UCBRK_1 = 1;
    // No error
    static const uint32_t UCAxSTATW_UCPE__UCPE_0 = 0;
    // Character received with parity error
    static const uint32_t UCAxSTATW_UCPE__UCPE_1 = 1;
    // No error
    static const uint32_t UCAxSTATW_UCOE__UCOE_0 = 0;
    // Overrun error occurred
    static const uint32_t UCAxSTATW_UCOE__UCOE_1 = 1;
    // No error
    static const uint32_t UCAxSTATW_UCFE__UCFE_0 = 0;
    // Character received with low stop bit
    static const uint32_t UCAxSTATW_UCFE__UCFE_1 = 1;
    // Disabled
    static const uint32_t UCAxSTATW_UCLISTEN__UCLISTEN_0 = 0;
    // Enabled. UCAxTXD is internally fed back to the receiver
    static const uint32_t UCAxSTATW_UCLISTEN__UCLISTEN_1 = 1;

    // eUSCI_Ax Receive Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxRXBUF_t, uint16_t)
        // Receive data buffer
        ADD_BITFIELD_RO(UCRXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Ax Transmit Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxTXBUF_t, uint16_t)
        // Transmit data buffer
        ADD_BITFIELD_RW(UCTXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Ax Auto Baud Rate Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxABCTL_t, uint16_t)
        // Automatic baud-rate detect enable
        ADD_BITFIELD_RW(UCABDEN, 0, 1)
        // Break time out error
        ADD_BITFIELD_RW(UCBTOE, 2, 1)
        // Synch field time out error
        ADD_BITFIELD_RW(UCSTOE, 3, 1)
        // Break/synch delimiter length
        ADD_BITFIELD_RW(UCDELIM, 4, 2)
    END_TYPE()

    // Baud-rate detection disabled. Length of break and synch field is not measured.
    static const uint32_t UCAxABCTL_UCABDEN__UCABDEN_0 = 0;
    // Baud-rate detection enabled. Length of break and synch field is measured and baud-rate settings are changed accordingly.
    static const uint32_t UCAxABCTL_UCABDEN__UCABDEN_1 = 1;
    // No error
    static const uint32_t UCAxABCTL_UCBTOE__UCBTOE_0 = 0;
    // Length of break field exceeded 22 bit times
    static const uint32_t UCAxABCTL_UCBTOE__UCBTOE_1 = 1;
    // No error
    static const uint32_t UCAxABCTL_UCSTOE__UCSTOE_0 = 0;
    // Length of synch field exceeded measurable time
    static const uint32_t UCAxABCTL_UCSTOE__UCSTOE_1 = 1;
    // 1 bit time
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_0 = 0;
    // 2 bit times
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_1 = 1;
    // 3 bit times
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_2 = 2;
    // 4 bit times
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_3 = 3;

    // eUSCI_Ax IrDA Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxIRCTL_t, uint16_t)
        // IrDA encoder/decoder enable
        ADD_BITFIELD_RW(UCIREN, 0, 1)
        // IrDA transmit pulse clock select
        ADD_BITFIELD_RW(UCIRTXCLK, 1, 1)
        // Transmit pulse length
        ADD_BITFIELD_RW(UCIRTXPL, 2, 6)
        // IrDA receive filter enabled
        ADD_BITFIELD_RW(UCIRRXFE, 8, 1)
        // IrDA receive input UCAxRXD polarity
        ADD_BITFIELD_RW(UCIRRXPL, 9, 1)
        // Receive filter length
        ADD_BITFIELD_RW(UCIRRXFL, 10, 4)
    END_TYPE()

    // IrDA encoder/decoder disabled
    static const uint32_t UCAxIRCTL_UCIREN__UCIREN_0 = 0;
    // IrDA encoder/decoder enabled
    static const uint32_t UCAxIRCTL_UCIREN__UCIREN_1 = 1;
    // BRCLK
    static const uint32_t UCAxIRCTL_UCIRTXCLK__UCIRTXCLK_0 = 0;
    // BITCLK16 when UCOS16 = 1. Otherwise, BRCLK.
    static const uint32_t UCAxIRCTL_UCIRTXCLK__UCIRTXCLK_1 = 1;
    // Receive filter disabled
    static const uint32_t UCAxIRCTL_UCIRRXFE__UCIRRXFE_0 = 0;
    // Receive filter enabled
    static const uint32_t UCAxIRCTL_UCIRRXFE__UCIRRXFE_1 = 1;
    // IrDA transceiver delivers a high pulse when a light pulse is seen
    static const uint32_t UCAxIRCTL_UCIRRXPL__UCIRRXPL_0 = 0;
    // IrDA transceiver delivers a low pulse when a light pulse is seen
    static const uint32_t UCAxIRCTL_UCIRRXPL__UCIRRXPL_1 = 1;

    // eUSCI_Ax Interrupt Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxIE_t, uint16_t)
        // Receive interrupt enable
        ADD_BITFIELD_RW(UCRXIE, 0, 1)
        // Transmit interrupt enable
        ADD_BITFIELD_RW(UCTXIE, 1, 1)
        // Start bit interrupt enable
        ADD_BITFIELD_RW(UCSTTIE, 2, 1)
        // Transmit complete interrupt enable
        ADD_BITFIELD_RW(UCTXCPTIE, 3, 1)
    END_TYPE()

    // Interrupt disabled
    static const uint32_t UCAxIE_UCRXIE__UCRXIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCRXIE__UCRXIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCAxIE_UCTXIE__UCTXIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCTXIE__UCTXIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCAxIE_UCSTTIE__UCSTTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCSTTIE__UCSTTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCAxIE_UCTXCPTIE__UCTXCPTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCTXCPTIE__UCTXCPTIE_1 = 1;

    // eUSCI_Ax Interrupt Flag Register
    // Reset value: 0x00000002
    BEGIN_TYPE(UCAxIFG_t, uint16_t)
        // Receive interrupt flag
        ADD_BITFIELD_RW(UCRXIFG, 0, 1)
        // Transmit interrupt flag
        ADD_BITFIELD_RW(UCTXIFG, 1, 1)
        // Start bit interrupt flag
        ADD_BITFIELD_RW(UCSTTIFG, 2, 1)
        // Transmit ready interrupt enable
        ADD_BITFIELD_RW(UCTXCPTIFG, 3, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCAxIFG_UCRXIFG__UCRXIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCRXIFG__UCRXIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCAxIFG_UCTXIFG__UCTXIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCTXIFG__UCTXIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCAxIFG_UCSTTIFG__UCSTTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCSTTIFG__UCSTTIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCAxIFG_UCTXCPTIFG__UCTXCPTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCTXCPTIFG__UCTXCPTIFG_1 = 1;

    // eUSCI_Ax Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxIV_t, uint16_t)
        // eUSCI_A interrupt vector value
        ADD_BITFIELD_RO(UCIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCAxIV_UCIV__UCIV_0 = 0;
    // Interrupt Source: Receive buffer full; Interrupt Flag: UCRXIFG; Interrupt Priority: Highest
    static const uint32_t UCAxIV_UCIV__UCIV_2 = 2;
    // Interrupt Source: Transmit buffer empty; Interrupt Flag: UCTXIFG
    static const uint32_t UCAxIV_UCIV__UCIV_4 = 4;
    // Interrupt Source: Start bit received; Interrupt Flag: UCSTTIFG
    static const uint32_t UCAxIV_UCIV__UCIV_6 = 6;
    // Interrupt Source: Transmit complete; Interrupt Flag: UCTXCPTIFG; Interrupt Priority: Lowest
    static const uint32_t UCAxIV_UCIV__UCIV_8 = 8;

    struct EUSCI_A2_t {
        UCAxCTLW0_t                   UCAxCTLW0;
        UCAxCTLW1_t                   UCAxCTLW1;
        uint16_t                      reserved0;
        UCAxBRW_t                     UCAxBRW;
        UCAxMCTLW_t                   UCAxMCTLW;
        UCAxSTATW_t                   UCAxSTATW;
        UCAxRXBUF_t                   UCAxRXBUF;
        UCAxTXBUF_t                   UCAxTXBUF;
        UCAxABCTL_t                   UCAxABCTL;
        UCAxIRCTL_t                   UCAxIRCTL;
        uint16_t                      reserved1[3];
        UCAxIE_t                      UCAxIE;
        UCAxIFG_t                     UCAxIFG;
        UCAxIV_t                      UCAxIV;
    };

    static EUSCI_A2_t & EUSCI_A2     = (*(EUSCI_A2_t *)0x40001800);

} // _EUSCI_A2_

// EUSCI_A3
namespace _EUSCI_A3_  {

    // eUSCI_Ax Control Word Register 0
    // Reset value: 0x00000001
    BEGIN_TYPE(UCAxCTLW0_t, uint16_t)
        // Software reset enable
        ADD_BITFIELD_RW(UCSWRST, 0, 1)
        // Transmit break
        ADD_BITFIELD_RW(UCTXBRK, 1, 1)
        // Transmit address
        ADD_BITFIELD_RW(UCTXADDR, 2, 1)
        // Dormant
        ADD_BITFIELD_RW(UCDORM, 3, 1)
        // Receive break character interrupt enable
        ADD_BITFIELD_RW(UCBRKIE, 4, 1)
        // Receive erroneous-character interrupt enable
        ADD_BITFIELD_RW(UCRXEIE, 5, 1)
        // eUSCI_A clock source select
        ADD_BITFIELD_RW(UCSSEL, 6, 2)
        // Synchronous mode enable
        ADD_BITFIELD_RW(UCSYNC, 8, 1)
        // eUSCI_A mode
        ADD_BITFIELD_RW(UCMODE, 9, 2)
        // Stop bit select
        ADD_BITFIELD_RW(UCSPB, 11, 1)
        // Character length
        ADD_BITFIELD_RW(UC7BIT, 12, 1)
        // MSB first select
        ADD_BITFIELD_RW(UCMSB, 13, 1)
        // Parity select
        ADD_BITFIELD_RW(UCPAR, 14, 1)
        // Parity enable
        ADD_BITFIELD_RW(UCPEN, 15, 1)
    END_TYPE()

    // Disabled. eUSCI_A reset released for operation
    static const uint32_t UCAxCTLW0_UCSWRST__UCSWRST_0 = 0;
    // Enabled. eUSCI_A logic held in reset state
    static const uint32_t UCAxCTLW0_UCSWRST__UCSWRST_1 = 1;
    // Next frame transmitted is not a break
    static const uint32_t UCAxCTLW0_UCTXBRK__UCTXBRK_0 = 0;
    // Next frame transmitted is a break or a break/synch
    static const uint32_t UCAxCTLW0_UCTXBRK__UCTXBRK_1 = 1;
    // Next frame transmitted is data
    static const uint32_t UCAxCTLW0_UCTXADDR__UCTXADDR_0 = 0;
    // Next frame transmitted is an address
    static const uint32_t UCAxCTLW0_UCTXADDR__UCTXADDR_1 = 1;
    // Not dormant. All received characters set UCRXIFG.
    static const uint32_t UCAxCTLW0_UCDORM__UCDORM_0 = 0;
    // Dormant. Only characters that are preceded by an idle-line or with address bit set UCRXIFG. In UART mode with automatic baud-rate detection, only the combination of a break and synch field sets UCRXIFG.
    static const uint32_t UCAxCTLW0_UCDORM__UCDORM_1 = 1;
    // Received break characters do not set UCRXIFG
    static const uint32_t UCAxCTLW0_UCBRKIE__UCBRKIE_0 = 0;
    // Received break characters set UCRXIFG
    static const uint32_t UCAxCTLW0_UCBRKIE__UCBRKIE_1 = 1;
    // Erroneous characters rejected and UCRXIFG is not set
    static const uint32_t UCAxCTLW0_UCRXEIE__UCRXEIE_0 = 0;
    // Erroneous characters received set UCRXIFG
    static const uint32_t UCAxCTLW0_UCRXEIE__UCRXEIE_1 = 1;
    // UCLK
    static const uint32_t UCAxCTLW0_UCSSEL__UCSSEL_0 = 0;
    // ACLK
    static const uint32_t UCAxCTLW0_UCSSEL__UCSSEL_1 = 1;
    // SMCLK
    static const uint32_t UCAxCTLW0_UCSSEL__UCSSEL_2 = 2;
    // Asynchronous mode
    static const uint32_t UCAxCTLW0_UCSYNC__UCSYNC_0 = 0;
    // Synchronous mode
    static const uint32_t UCAxCTLW0_UCSYNC__UCSYNC_1 = 1;
    // UART mode
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_0 = 0;
    // Idle-line multiprocessor mode
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_1 = 1;
    // Address-bit multiprocessor mode
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_2 = 2;
    // UART mode with automatic baud-rate detection
    static const uint32_t UCAxCTLW0_UCMODE__UCMODE_3 = 3;
    // One stop bit
    static const uint32_t UCAxCTLW0_UCSPB__UCSPB_0 = 0;
    // Two stop bits
    static const uint32_t UCAxCTLW0_UCSPB__UCSPB_1 = 1;
    // 8-bit data
    static const uint32_t UCAxCTLW0_UC7BIT__UC7BIT_0 = 0;
    // 7-bit data
    static const uint32_t UCAxCTLW0_UC7BIT__UC7BIT_1 = 1;
    // LSB first
    static const uint32_t UCAxCTLW0_UCMSB__UCMSB_0 = 0;
    // MSB first
    static const uint32_t UCAxCTLW0_UCMSB__UCMSB_1 = 1;
    // Odd parity
    static const uint32_t UCAxCTLW0_UCPAR__UCPAR_0 = 0;
    // Even parity
    static const uint32_t UCAxCTLW0_UCPAR__UCPAR_1 = 1;
    // Parity disabled
    static const uint32_t UCAxCTLW0_UCPEN__UCPEN_0 = 0;
    // Parity enabled. Parity bit is generated (UCAxTXD) and expected (UCAxRXD). In address-bit multiprocessor mode, the address bit is included in the parity calculation.
    static const uint32_t UCAxCTLW0_UCPEN__UCPEN_1 = 1;

    // eUSCI_Ax Control Word Register 1
    // Reset value: 0x00000003
    BEGIN_TYPE(UCAxCTLW1_t, uint16_t)
        // Deglitch time
        ADD_BITFIELD_RW(UCGLIT, 0, 2)
    END_TYPE()

    // Approximately 2 ns (equivalent of 1 delay element)
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_0 = 0;
    // Approximately 50 ns
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_1 = 1;
    // Approximately 100 ns
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_2 = 2;
    // Approximately 200 ns
    static const uint32_t UCAxCTLW1_UCGLIT__UCGLIT_3 = 3;

    // eUSCI_Ax Baud Rate Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxBRW_t, uint16_t)
        // Clock prescaler setting of the Baud rate generator
        ADD_BITFIELD_RW(UCBR, 0, 16)
    END_TYPE()

    // eUSCI_Ax Modulation Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxMCTLW_t, uint16_t)
        // Oversampling mode enabled
        ADD_BITFIELD_RW(UCOS16, 0, 1)
        // First modulation stage select
        ADD_BITFIELD_RW(UCBRF, 4, 4)
        // Second modulation stage select
        ADD_BITFIELD_RW(UCBRS, 8, 8)
    END_TYPE()

    // Disabled
    static const uint32_t UCAxMCTLW_UCOS16__UCOS16_0 = 0;
    // Enabled
    static const uint32_t UCAxMCTLW_UCOS16__UCOS16_1 = 1;

    // eUSCI_Ax Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxSTATW_t, uint16_t)
        // eUSCI_A busy
        ADD_BITFIELD_RO(UCBUSY, 0, 1)
        // Address received / Idle line detected
        ADD_BITFIELD_RW(UCADDR_UCIDLE, 1, 1)
        // Receive error flag
        ADD_BITFIELD_RW(UCRXERR, 2, 1)
        // Break detect flag
        ADD_BITFIELD_RW(UCBRK, 3, 1)
        // Parity error flag. When UCPEN = 0, UCPE is read as 0. UCPE is cleared when UCAxRXBUF is read.
        ADD_BITFIELD_RW(UCPE, 4, 1)
        // Overrun error flag
        ADD_BITFIELD_RW(UCOE, 5, 1)
        // Framing error flag
        ADD_BITFIELD_RW(UCFE, 6, 1)
        // Listen enable
        ADD_BITFIELD_RW(UCLISTEN, 7, 1)
    END_TYPE()

    // eUSCI_A inactive
    static const uint32_t UCAxSTATW_UCBUSY__UCBUSY_0 = 0;
    // eUSCI_A transmitting or receiving
    static const uint32_t UCAxSTATW_UCBUSY__UCBUSY_1 = 1;
    // No receive errors detected
    static const uint32_t UCAxSTATW_UCRXERR__UCRXERR_0 = 0;
    // Receive error detected
    static const uint32_t UCAxSTATW_UCRXERR__UCRXERR_1 = 1;
    // No break condition
    static const uint32_t UCAxSTATW_UCBRK__UCBRK_0 = 0;
    // Break condition occurred
    static const uint32_t UCAxSTATW_UCBRK__UCBRK_1 = 1;
    // No error
    static const uint32_t UCAxSTATW_UCPE__UCPE_0 = 0;
    // Character received with parity error
    static const uint32_t UCAxSTATW_UCPE__UCPE_1 = 1;
    // No error
    static const uint32_t UCAxSTATW_UCOE__UCOE_0 = 0;
    // Overrun error occurred
    static const uint32_t UCAxSTATW_UCOE__UCOE_1 = 1;
    // No error
    static const uint32_t UCAxSTATW_UCFE__UCFE_0 = 0;
    // Character received with low stop bit
    static const uint32_t UCAxSTATW_UCFE__UCFE_1 = 1;
    // Disabled
    static const uint32_t UCAxSTATW_UCLISTEN__UCLISTEN_0 = 0;
    // Enabled. UCAxTXD is internally fed back to the receiver
    static const uint32_t UCAxSTATW_UCLISTEN__UCLISTEN_1 = 1;

    // eUSCI_Ax Receive Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxRXBUF_t, uint16_t)
        // Receive data buffer
        ADD_BITFIELD_RO(UCRXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Ax Transmit Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxTXBUF_t, uint16_t)
        // Transmit data buffer
        ADD_BITFIELD_RW(UCTXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Ax Auto Baud Rate Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxABCTL_t, uint16_t)
        // Automatic baud-rate detect enable
        ADD_BITFIELD_RW(UCABDEN, 0, 1)
        // Break time out error
        ADD_BITFIELD_RW(UCBTOE, 2, 1)
        // Synch field time out error
        ADD_BITFIELD_RW(UCSTOE, 3, 1)
        // Break/synch delimiter length
        ADD_BITFIELD_RW(UCDELIM, 4, 2)
    END_TYPE()

    // Baud-rate detection disabled. Length of break and synch field is not measured.
    static const uint32_t UCAxABCTL_UCABDEN__UCABDEN_0 = 0;
    // Baud-rate detection enabled. Length of break and synch field is measured and baud-rate settings are changed accordingly.
    static const uint32_t UCAxABCTL_UCABDEN__UCABDEN_1 = 1;
    // No error
    static const uint32_t UCAxABCTL_UCBTOE__UCBTOE_0 = 0;
    // Length of break field exceeded 22 bit times
    static const uint32_t UCAxABCTL_UCBTOE__UCBTOE_1 = 1;
    // No error
    static const uint32_t UCAxABCTL_UCSTOE__UCSTOE_0 = 0;
    // Length of synch field exceeded measurable time
    static const uint32_t UCAxABCTL_UCSTOE__UCSTOE_1 = 1;
    // 1 bit time
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_0 = 0;
    // 2 bit times
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_1 = 1;
    // 3 bit times
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_2 = 2;
    // 4 bit times
    static const uint32_t UCAxABCTL_UCDELIM__UCDELIM_3 = 3;

    // eUSCI_Ax IrDA Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxIRCTL_t, uint16_t)
        // IrDA encoder/decoder enable
        ADD_BITFIELD_RW(UCIREN, 0, 1)
        // IrDA transmit pulse clock select
        ADD_BITFIELD_RW(UCIRTXCLK, 1, 1)
        // Transmit pulse length
        ADD_BITFIELD_RW(UCIRTXPL, 2, 6)
        // IrDA receive filter enabled
        ADD_BITFIELD_RW(UCIRRXFE, 8, 1)
        // IrDA receive input UCAxRXD polarity
        ADD_BITFIELD_RW(UCIRRXPL, 9, 1)
        // Receive filter length
        ADD_BITFIELD_RW(UCIRRXFL, 10, 4)
    END_TYPE()

    // IrDA encoder/decoder disabled
    static const uint32_t UCAxIRCTL_UCIREN__UCIREN_0 = 0;
    // IrDA encoder/decoder enabled
    static const uint32_t UCAxIRCTL_UCIREN__UCIREN_1 = 1;
    // BRCLK
    static const uint32_t UCAxIRCTL_UCIRTXCLK__UCIRTXCLK_0 = 0;
    // BITCLK16 when UCOS16 = 1. Otherwise, BRCLK.
    static const uint32_t UCAxIRCTL_UCIRTXCLK__UCIRTXCLK_1 = 1;
    // Receive filter disabled
    static const uint32_t UCAxIRCTL_UCIRRXFE__UCIRRXFE_0 = 0;
    // Receive filter enabled
    static const uint32_t UCAxIRCTL_UCIRRXFE__UCIRRXFE_1 = 1;
    // IrDA transceiver delivers a high pulse when a light pulse is seen
    static const uint32_t UCAxIRCTL_UCIRRXPL__UCIRRXPL_0 = 0;
    // IrDA transceiver delivers a low pulse when a light pulse is seen
    static const uint32_t UCAxIRCTL_UCIRRXPL__UCIRRXPL_1 = 1;

    // eUSCI_Ax Interrupt Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxIE_t, uint16_t)
        // Receive interrupt enable
        ADD_BITFIELD_RW(UCRXIE, 0, 1)
        // Transmit interrupt enable
        ADD_BITFIELD_RW(UCTXIE, 1, 1)
        // Start bit interrupt enable
        ADD_BITFIELD_RW(UCSTTIE, 2, 1)
        // Transmit complete interrupt enable
        ADD_BITFIELD_RW(UCTXCPTIE, 3, 1)
    END_TYPE()

    // Interrupt disabled
    static const uint32_t UCAxIE_UCRXIE__UCRXIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCRXIE__UCRXIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCAxIE_UCTXIE__UCTXIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCTXIE__UCTXIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCAxIE_UCSTTIE__UCSTTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCSTTIE__UCSTTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCAxIE_UCTXCPTIE__UCTXCPTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCAxIE_UCTXCPTIE__UCTXCPTIE_1 = 1;

    // eUSCI_Ax Interrupt Flag Register
    // Reset value: 0x00000002
    BEGIN_TYPE(UCAxIFG_t, uint16_t)
        // Receive interrupt flag
        ADD_BITFIELD_RW(UCRXIFG, 0, 1)
        // Transmit interrupt flag
        ADD_BITFIELD_RW(UCTXIFG, 1, 1)
        // Start bit interrupt flag
        ADD_BITFIELD_RW(UCSTTIFG, 2, 1)
        // Transmit ready interrupt enable
        ADD_BITFIELD_RW(UCTXCPTIFG, 3, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCAxIFG_UCRXIFG__UCRXIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCRXIFG__UCRXIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCAxIFG_UCTXIFG__UCTXIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCTXIFG__UCTXIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCAxIFG_UCSTTIFG__UCSTTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCSTTIFG__UCSTTIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCAxIFG_UCTXCPTIFG__UCTXCPTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCAxIFG_UCTXCPTIFG__UCTXCPTIFG_1 = 1;

    // eUSCI_Ax Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCAxIV_t, uint16_t)
        // eUSCI_A interrupt vector value
        ADD_BITFIELD_RO(UCIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCAxIV_UCIV__UCIV_0 = 0;
    // Interrupt Source: Receive buffer full; Interrupt Flag: UCRXIFG; Interrupt Priority: Highest
    static const uint32_t UCAxIV_UCIV__UCIV_2 = 2;
    // Interrupt Source: Transmit buffer empty; Interrupt Flag: UCTXIFG
    static const uint32_t UCAxIV_UCIV__UCIV_4 = 4;
    // Interrupt Source: Start bit received; Interrupt Flag: UCSTTIFG
    static const uint32_t UCAxIV_UCIV__UCIV_6 = 6;
    // Interrupt Source: Transmit complete; Interrupt Flag: UCTXCPTIFG; Interrupt Priority: Lowest
    static const uint32_t UCAxIV_UCIV__UCIV_8 = 8;

    struct EUSCI_A3_t {
        UCAxCTLW0_t                   UCAxCTLW0;
        UCAxCTLW1_t                   UCAxCTLW1;
        uint16_t                      reserved0;
        UCAxBRW_t                     UCAxBRW;
        UCAxMCTLW_t                   UCAxMCTLW;
        UCAxSTATW_t                   UCAxSTATW;
        UCAxRXBUF_t                   UCAxRXBUF;
        UCAxTXBUF_t                   UCAxTXBUF;
        UCAxABCTL_t                   UCAxABCTL;
        UCAxIRCTL_t                   UCAxIRCTL;
        uint16_t                      reserved1[3];
        UCAxIE_t                      UCAxIE;
        UCAxIFG_t                     UCAxIFG;
        UCAxIV_t                      UCAxIV;
    };

    static EUSCI_A3_t & EUSCI_A3     = (*(EUSCI_A3_t *)0x40001c00);

} // _EUSCI_A3_

// EUSCI_B0
namespace _EUSCI_B0_  {

    // eUSCI_Bx Control Word Register 0
    // Reset value: 0x000001c1
    BEGIN_TYPE(UCBxCTLW0_t, uint16_t)
        // Software reset enable
        ADD_BITFIELD_RW(UCSWRST, 0, 1)
        // Transmit START condition in master mode
        ADD_BITFIELD_RW(UCTXSTT, 1, 1)
        // Transmit STOP condition in master mode
        ADD_BITFIELD_RW(UCTXSTP, 2, 1)
        // Transmit a NACK
        ADD_BITFIELD_RW(UCTXNACK, 3, 1)
        // Transmitter/receiver
        ADD_BITFIELD_RW(UCTR, 4, 1)
        // Transmit ACK condition in slave mode
        ADD_BITFIELD_RW(UCTXACK, 5, 1)
        // eUSCI_B clock source select
        ADD_BITFIELD_RW(UCSSEL, 6, 2)
        // Synchronous mode enable
        ADD_BITFIELD_RW(UCSYNC, 8, 1)
        // eUSCI_B mode
        ADD_BITFIELD_RW(UCMODE, 9, 2)
        // Master mode select
        ADD_BITFIELD_RW(UCMST, 11, 1)
        // Multi-master environment select
        ADD_BITFIELD_RW(UCMM, 13, 1)
        // Slave addressing mode select
        ADD_BITFIELD_RW(UCSLA10, 14, 1)
        // Own addressing mode select
        ADD_BITFIELD_RW(UCA10, 15, 1)
    END_TYPE()

    // Disabled. eUSCI_B reset released for operation
    static const uint32_t UCBxCTLW0_UCSWRST__UCSWRST_0 = 0;
    // Enabled. eUSCI_B logic held in reset state
    static const uint32_t UCBxCTLW0_UCSWRST__UCSWRST_1 = 1;
    // Do not generate START condition
    static const uint32_t UCBxCTLW0_UCTXSTT__UCTXSTT_0 = 0;
    // Generate START condition
    static const uint32_t UCBxCTLW0_UCTXSTT__UCTXSTT_1 = 1;
    // No STOP generated
    static const uint32_t UCBxCTLW0_UCTXSTP__UCTXSTP_0 = 0;
    // Generate STOP
    static const uint32_t UCBxCTLW0_UCTXSTP__UCTXSTP_1 = 1;
    // Acknowledge normally
    static const uint32_t UCBxCTLW0_UCTXNACK__UCTXNACK_0 = 0;
    // Generate NACK
    static const uint32_t UCBxCTLW0_UCTXNACK__UCTXNACK_1 = 1;
    // Receiver
    static const uint32_t UCBxCTLW0_UCTR__UCTR_0 = 0;
    // Transmitter
    static const uint32_t UCBxCTLW0_UCTR__UCTR_1 = 1;
    // Do not acknowledge the slave address
    static const uint32_t UCBxCTLW0_UCTXACK__UCTXACK_0 = 0;
    // Acknowledge the slave address
    static const uint32_t UCBxCTLW0_UCTXACK__UCTXACK_1 = 1;
    // UCLKI
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_0 = 0;
    // ACLK
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_1 = 1;
    // SMCLK
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_2 = 2;
    // SMCLK
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_3 = 3;
    // Asynchronous mode
    static const uint32_t UCBxCTLW0_UCSYNC__UCSYNC_0 = 0;
    // Synchronous mode
    static const uint32_t UCBxCTLW0_UCSYNC__UCSYNC_1 = 1;
    // 3-pin SPI
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_0 = 0;
    // 4-pin SPI (master or slave enabled if STE = 1)
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_1 = 1;
    // 4-pin SPI (master or slave enabled if STE = 0)
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_2 = 2;
    // I2C mode
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_3 = 3;
    // Slave mode
    static const uint32_t UCBxCTLW0_UCMST__UCMST_0 = 0;
    // Master mode
    static const uint32_t UCBxCTLW0_UCMST__UCMST_1 = 1;
    // Single master environment. There is no other master in the system. The address compare unit is disabled.
    static const uint32_t UCBxCTLW0_UCMM__UCMM_0 = 0;
    // Multi-master environment
    static const uint32_t UCBxCTLW0_UCMM__UCMM_1 = 1;
    // Address slave with 7-bit address
    static const uint32_t UCBxCTLW0_UCSLA10__UCSLA10_0 = 0;
    // Address slave with 10-bit address
    static const uint32_t UCBxCTLW0_UCSLA10__UCSLA10_1 = 1;
    // Own address is a 7-bit address
    static const uint32_t UCBxCTLW0_UCA10__UCA10_0 = 0;
    // Own address is a 10-bit address
    static const uint32_t UCBxCTLW0_UCA10__UCA10_1 = 1;

    // eUSCI_Bx Control Word Register 1
    // Reset value: 0x00000003
    BEGIN_TYPE(UCBxCTLW1_t, uint16_t)
        // Deglitch time
        ADD_BITFIELD_RW(UCGLIT, 0, 2)
        // Automatic STOP condition generation
        ADD_BITFIELD_RW(UCASTP, 2, 2)
        // SW or HW ACK control
        ADD_BITFIELD_RW(UCSWACK, 4, 1)
        // ACK all master bytes
        ADD_BITFIELD_RW(UCSTPNACK, 5, 1)
        // Clock low timeout select
        ADD_BITFIELD_RW(UCCLTO, 6, 2)
        // Early UCTXIFG0
        ADD_BITFIELD_RW(UCETXINT, 8, 1)
    END_TYPE()

    // 50 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_0 = 0;
    // 25 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_1 = 1;
    // 12.5 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_2 = 2;
    // 6.25 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_3 = 3;
    // No automatic STOP generation. The STOP condition is generated after the user sets the UCTXSTP bit. The value in UCBxTBCNT is a don't care.
    static const uint32_t UCBxCTLW1_UCASTP__UCASTP_0 = 0;
    // UCBCNTIFG is set with the byte counter reaches the threshold defined in UCBxTBCNT
    static const uint32_t UCBxCTLW1_UCASTP__UCASTP_1 = 1;
    // A STOP condition is generated automatically after the byte counter value reached UCBxTBCNT. UCBCNTIFG is set with the byte counter reaching the threshold
    static const uint32_t UCBxCTLW1_UCASTP__UCASTP_2 = 2;
    // The address acknowledge of the slave is controlled by the eUSCI_B module
    static const uint32_t UCBxCTLW1_UCSWACK__UCSWACK_0 = 0;
    // The user needs to trigger the sending of the address ACK by issuing UCTXACK
    static const uint32_t UCBxCTLW1_UCSWACK__UCSWACK_1 = 1;
    // Send a non-acknowledge before the STOP condition as a master receiver (conform to I2C standard)
    static const uint32_t UCBxCTLW1_UCSTPNACK__UCSTPNACK_0 = 0;
    // All bytes are acknowledged by the eUSCI_B when configured as master receiver
    static const uint32_t UCBxCTLW1_UCSTPNACK__UCSTPNACK_1 = 1;
    // Disable clock low timeout counter
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_0 = 0;
    // 135 000 SYSCLK cycles (approximately 28 ms)
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_1 = 1;
    // 150 000 SYSCLK cycles (approximately 31 ms)
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_2 = 2;
    // 165 000 SYSCLK cycles (approximately 34 ms)
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_3 = 3;
    // UCTXIFGx is set after an address match with UCxI2COAx and the direction bit indicating slave transmit
    static const uint32_t UCBxCTLW1_UCETXINT__UCETXINT_0 = 0;
    // UCTXIFG0 is set for each START condition
    static const uint32_t UCBxCTLW1_UCETXINT__UCETXINT_1 = 1;

    // eUSCI_Bx Baud Rate Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxBRW_t, uint16_t)
        // Bit clock prescaler
        ADD_BITFIELD_RW(UCBR, 0, 16)
    END_TYPE()

    // eUSCI_Bx Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxSTATW_t, uint16_t)
        // Bus busy
        ADD_BITFIELD_RO(UCBBUSY, 4, 1)
        // General call address received
        ADD_BITFIELD_RO(UCGC, 5, 1)
        // SCL low
        ADD_BITFIELD_RO(UCSCLLOW, 6, 1)
        // Hardware byte counter value
        ADD_BITFIELD_RO(UCBCNT, 8, 8)
    END_TYPE()

    // Bus inactive
    static const uint32_t UCBxSTATW_UCBBUSY__UCBBUSY_0 = 0;
    // Bus busy
    static const uint32_t UCBxSTATW_UCBBUSY__UCBBUSY_1 = 1;
    // No general call address received
    static const uint32_t UCBxSTATW_UCGC__UCGC_0 = 0;
    // General call address received
    static const uint32_t UCBxSTATW_UCGC__UCGC_1 = 1;
    // SCL is not held low
    static const uint32_t UCBxSTATW_UCSCLLOW__UCSCLLOW_0 = 0;
    // SCL is held low
    static const uint32_t UCBxSTATW_UCSCLLOW__UCSCLLOW_1 = 1;

    // eUSCI_Bx Byte Counter Threshold Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxTBCNT_t, uint16_t)
        // Byte counter threshold value
        ADD_BITFIELD_RW(UCTBCNT, 0, 8)
    END_TYPE()

    // eUSCI_Bx Receive Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxRXBUF_t, uint16_t)
        // Receive data buffer
        ADD_BITFIELD_RO(UCRXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Bx Transmit Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxTXBUF_t, uint16_t)
        // Transmit data buffer
        ADD_BITFIELD_RW(UCTXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Bx I2C Own Address 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA0_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA0, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
        // General call response enable
        ADD_BITFIELD_RW(UCGCEN, 15, 1)
    END_TYPE()

    // The slave address defined in I2COA0 is disabled
    static const uint32_t UCBxI2COA0_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA0 is enabled
    static const uint32_t UCBxI2COA0_UCOAEN__UCOAEN_1 = 1;
    // Do not respond to a general call
    static const uint32_t UCBxI2COA0_UCGCEN__UCGCEN_0 = 0;
    // Respond to a general call
    static const uint32_t UCBxI2COA0_UCGCEN__UCGCEN_1 = 1;

    // eUSCI_Bx I2C Own Address 1 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA1_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA1, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
    END_TYPE()

    // The slave address defined in I2COA1 is disabled
    static const uint32_t UCBxI2COA1_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA1 is enabled
    static const uint32_t UCBxI2COA1_UCOAEN__UCOAEN_1 = 1;

    // eUSCI_Bx I2C Own Address 2 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA2_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA2, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
    END_TYPE()

    // The slave address defined in I2COA2 is disabled
    static const uint32_t UCBxI2COA2_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA2 is enabled
    static const uint32_t UCBxI2COA2_UCOAEN__UCOAEN_1 = 1;

    // eUSCI_Bx I2C Own Address 3 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA3_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA3, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
    END_TYPE()

    // The slave address defined in I2COA3 is disabled
    static const uint32_t UCBxI2COA3_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA3 is enabled
    static const uint32_t UCBxI2COA3_UCOAEN__UCOAEN_1 = 1;

    // eUSCI_Bx I2C Received Address Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxADDRX_t, uint16_t)
        // Received Address Register
        ADD_BITFIELD_RO(ADDRX, 0, 10)
    END_TYPE()

    // eUSCI_Bx I2C Address Mask Register
    // Reset value: 0x000003ff
    BEGIN_TYPE(UCBxADDMASK_t, uint16_t)
        // Address Mask Register. By clearing the corresponding bit of the own address, this bit is a don't care when comparing the address on the bus to the own address. Using this method, it is possible to react on more than one slave address. When all bits of ADDMASKx are set, the address mask feature is deactivated. Modify only when UCSWRST = 1.
        ADD_BITFIELD_RW(ADDMASK, 0, 10)
    END_TYPE()

    // eUSCI_Bx I2C Slave Address Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2CSA_t, uint16_t)
        // I2C slave address
        ADD_BITFIELD_RW(I2CSA, 0, 10)
    END_TYPE()

    // eUSCI_Bx Interrupt Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxIE_t, uint16_t)
        // Receive interrupt enable 0
        ADD_BITFIELD_RW(UCRXIE0, 0, 1)
        // Transmit interrupt enable 0
        ADD_BITFIELD_RW(UCTXIE0, 1, 1)
        // START condition interrupt enable
        ADD_BITFIELD_RW(UCSTTIE, 2, 1)
        // STOP condition interrupt enable
        ADD_BITFIELD_RW(UCSTPIE, 3, 1)
        // Arbitration lost interrupt enable
        ADD_BITFIELD_RW(UCALIE, 4, 1)
        // Not-acknowledge interrupt enable
        ADD_BITFIELD_RW(UCNACKIE, 5, 1)
        // Byte counter interrupt enable
        ADD_BITFIELD_RW(UCBCNTIE, 6, 1)
        // Clock low timeout interrupt enable
        ADD_BITFIELD_RW(UCCLTOIE, 7, 1)
        // Receive interrupt enable 1
        ADD_BITFIELD_RW(UCRXIE1, 8, 1)
        // Transmit interrupt enable 1
        ADD_BITFIELD_RW(UCTXIE1, 9, 1)
        // Receive interrupt enable 2
        ADD_BITFIELD_RW(UCRXIE2, 10, 1)
        // Transmit interrupt enable 2
        ADD_BITFIELD_RW(UCTXIE2, 11, 1)
        // Receive interrupt enable 3
        ADD_BITFIELD_RW(UCRXIE3, 12, 1)
        // Transmit interrupt enable 3
        ADD_BITFIELD_RW(UCTXIE3, 13, 1)
        // Bit position 9 interrupt enable
        ADD_BITFIELD_RW(UCBIT9IE, 14, 1)
    END_TYPE()

    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE0__UCRXIE0_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE0__UCRXIE0_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE0__UCTXIE0_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE0__UCTXIE0_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCSTTIE__UCSTTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCSTTIE__UCSTTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCSTPIE__UCSTPIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCSTPIE__UCSTPIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCALIE__UCALIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCALIE__UCALIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCNACKIE__UCNACKIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCNACKIE__UCNACKIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCBCNTIE__UCBCNTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCBCNTIE__UCBCNTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCCLTOIE__UCCLTOIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCCLTOIE__UCCLTOIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE1__UCRXIE1_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE1__UCRXIE1_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE1__UCTXIE1_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE1__UCTXIE1_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE2__UCRXIE2_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE2__UCRXIE2_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE2__UCTXIE2_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE2__UCTXIE2_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE3__UCRXIE3_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE3__UCRXIE3_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE3__UCTXIE3_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE3__UCTXIE3_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCBIT9IE__UCBIT9IE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCBIT9IE__UCBIT9IE_1 = 1;

    // eUSCI_Bx Interrupt Flag Register
    // Reset value: 0x00000002
    BEGIN_TYPE(UCBxIFG_t, uint16_t)
        // eUSCI_B receive interrupt flag 0
        ADD_BITFIELD_RW(UCRXIFG0, 0, 1)
        // eUSCI_B transmit interrupt flag 0
        ADD_BITFIELD_RW(UCTXIFG0, 1, 1)
        // START condition interrupt flag
        ADD_BITFIELD_RW(UCSTTIFG, 2, 1)
        // STOP condition interrupt flag
        ADD_BITFIELD_RW(UCSTPIFG, 3, 1)
        // Arbitration lost interrupt flag
        ADD_BITFIELD_RW(UCALIFG, 4, 1)
        // Not-acknowledge received interrupt flag
        ADD_BITFIELD_RW(UCNACKIFG, 5, 1)
        // Byte counter interrupt flag
        ADD_BITFIELD_RW(UCBCNTIFG, 6, 1)
        // Clock low timeout interrupt flag
        ADD_BITFIELD_RW(UCCLTOIFG, 7, 1)
        // eUSCI_B receive interrupt flag 1
        ADD_BITFIELD_RW(UCRXIFG1, 8, 1)
        // eUSCI_B transmit interrupt flag 1
        ADD_BITFIELD_RW(UCTXIFG1, 9, 1)
        // eUSCI_B receive interrupt flag 2
        ADD_BITFIELD_RW(UCRXIFG2, 10, 1)
        // eUSCI_B transmit interrupt flag 2
        ADD_BITFIELD_RW(UCTXIFG2, 11, 1)
        // eUSCI_B receive interrupt flag 3
        ADD_BITFIELD_RW(UCRXIFG3, 12, 1)
        // eUSCI_B transmit interrupt flag 3
        ADD_BITFIELD_RW(UCTXIFG3, 13, 1)
        // Bit position 9 interrupt flag
        ADD_BITFIELD_RW(UCBIT9IFG, 14, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG0__UCRXIFG0_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG0__UCRXIFG0_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG0__UCTXIFG0_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG0__UCTXIFG0_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCSTTIFG__UCSTTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCSTTIFG__UCSTTIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCSTPIFG__UCSTPIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCSTPIFG__UCSTPIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCALIFG__UCALIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCALIFG__UCALIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCNACKIFG__UCNACKIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCNACKIFG__UCNACKIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCBCNTIFG__UCBCNTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCBCNTIFG__UCBCNTIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCCLTOIFG__UCCLTOIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCCLTOIFG__UCCLTOIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG1__UCRXIFG1_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG1__UCRXIFG1_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG1__UCTXIFG1_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG1__UCTXIFG1_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG2__UCRXIFG2_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG2__UCRXIFG2_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG2__UCTXIFG2_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG2__UCTXIFG2_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG3__UCRXIFG3_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG3__UCRXIFG3_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG3__UCTXIFG3_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG3__UCTXIFG3_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCBIT9IFG__UCBIT9IFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCBIT9IFG__UCBIT9IFG_1 = 1;

    // eUSCI_Bx Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxIV_t, uint16_t)
        // eUSCI_B interrupt vector value
        ADD_BITFIELD_RO(UCIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCBxIV_UCIV__UCIV_0 = 0;
    // Interrupt Source: Arbitration lost; Interrupt Flag: UCALIFG; Interrupt Priority: Highest
    static const uint32_t UCBxIV_UCIV__UCIV_2 = 2;
    // Interrupt Source: Not acknowledgment; Interrupt Flag: UCNACKIFG
    static const uint32_t UCBxIV_UCIV__UCIV_4 = 4;
    // Interrupt Source: Start condition received; Interrupt Flag: UCSTTIFG
    static const uint32_t UCBxIV_UCIV__UCIV_6 = 6;
    // Interrupt Source: Stop condition received; Interrupt Flag: UCSTPIFG
    static const uint32_t UCBxIV_UCIV__UCIV_8 = 8;
    // Interrupt Source: Slave 3 Data received; Interrupt Flag: UCRXIFG3
    static const uint32_t UCBxIV_UCIV__UCIV_10 = 10;
    // Interrupt Source: Slave 3 Transmit buffer empty; Interrupt Flag: UCTXIFG3
    static const uint32_t UCBxIV_UCIV__UCIV_12 = 12;
    // Interrupt Source: Slave 2 Data received; Interrupt Flag: UCRXIFG2
    static const uint32_t UCBxIV_UCIV__UCIV_14 = 14;
    // Interrupt Source: Slave 2 Transmit buffer empty; Interrupt Flag: UCTXIFG2
    static const uint32_t UCBxIV_UCIV__UCIV_16 = 16;
    // Interrupt Source: Slave 1 Data received; Interrupt Flag: UCRXIFG1
    static const uint32_t UCBxIV_UCIV__UCIV_18 = 18;
    // Interrupt Source: Slave 1 Transmit buffer empty; Interrupt Flag: UCTXIFG1
    static const uint32_t UCBxIV_UCIV__UCIV_20 = 20;
    // Interrupt Source: Data received; Interrupt Flag: UCRXIFG0
    static const uint32_t UCBxIV_UCIV__UCIV_22 = 22;
    // Interrupt Source: Transmit buffer empty; Interrupt Flag: UCTXIFG0
    static const uint32_t UCBxIV_UCIV__UCIV_24 = 24;
    // Interrupt Source: Byte counter zero; Interrupt Flag: UCBCNTIFG
    static const uint32_t UCBxIV_UCIV__UCIV_26 = 26;
    // Interrupt Source: Clock low timeout; Interrupt Flag: UCCLTOIFG
    static const uint32_t UCBxIV_UCIV__UCIV_28 = 28;
    // Interrupt Source: Nineth bit position; Interrupt Flag: UCBIT9IFG; Priority: Lowest
    static const uint32_t UCBxIV_UCIV__UCIV_30 = 30;

    struct EUSCI_B0_t {
        UCBxCTLW0_t                   UCBxCTLW0;
        UCBxCTLW1_t                   UCBxCTLW1;
        uint16_t                      reserved0;
        UCBxBRW_t                     UCBxBRW;
        UCBxSTATW_t                   UCBxSTATW;
        UCBxTBCNT_t                   UCBxTBCNT;
        UCBxRXBUF_t                   UCBxRXBUF;
        UCBxTXBUF_t                   UCBxTXBUF;
        uint16_t                      reserved1[2];
        UCBxI2COA0_t                  UCBxI2COA0;
        UCBxI2COA1_t                  UCBxI2COA1;
        UCBxI2COA2_t                  UCBxI2COA2;
        UCBxI2COA3_t                  UCBxI2COA3;
        UCBxADDRX_t                   UCBxADDRX;
        UCBxADDMASK_t                 UCBxADDMASK;
        UCBxI2CSA_t                   UCBxI2CSA;
        uint16_t                      reserved2[4];
        UCBxIE_t                      UCBxIE;
        UCBxIFG_t                     UCBxIFG;
        UCBxIV_t                      UCBxIV;
    };

    static EUSCI_B0_t & EUSCI_B0     = (*(EUSCI_B0_t *)0x40002000);

} // _EUSCI_B0_

// EUSCI_B1
namespace _EUSCI_B1_  {

    // eUSCI_Bx Control Word Register 0
    // Reset value: 0x000001c1
    BEGIN_TYPE(UCBxCTLW0_t, uint16_t)
        // Software reset enable
        ADD_BITFIELD_RW(UCSWRST, 0, 1)
        // Transmit START condition in master mode
        ADD_BITFIELD_RW(UCTXSTT, 1, 1)
        // Transmit STOP condition in master mode
        ADD_BITFIELD_RW(UCTXSTP, 2, 1)
        // Transmit a NACK
        ADD_BITFIELD_RW(UCTXNACK, 3, 1)
        // Transmitter/receiver
        ADD_BITFIELD_RW(UCTR, 4, 1)
        // Transmit ACK condition in slave mode
        ADD_BITFIELD_RW(UCTXACK, 5, 1)
        // eUSCI_B clock source select
        ADD_BITFIELD_RW(UCSSEL, 6, 2)
        // Synchronous mode enable
        ADD_BITFIELD_RW(UCSYNC, 8, 1)
        // eUSCI_B mode
        ADD_BITFIELD_RW(UCMODE, 9, 2)
        // Master mode select
        ADD_BITFIELD_RW(UCMST, 11, 1)
        // Multi-master environment select
        ADD_BITFIELD_RW(UCMM, 13, 1)
        // Slave addressing mode select
        ADD_BITFIELD_RW(UCSLA10, 14, 1)
        // Own addressing mode select
        ADD_BITFIELD_RW(UCA10, 15, 1)
    END_TYPE()

    // Disabled. eUSCI_B reset released for operation
    static const uint32_t UCBxCTLW0_UCSWRST__UCSWRST_0 = 0;
    // Enabled. eUSCI_B logic held in reset state
    static const uint32_t UCBxCTLW0_UCSWRST__UCSWRST_1 = 1;
    // Do not generate START condition
    static const uint32_t UCBxCTLW0_UCTXSTT__UCTXSTT_0 = 0;
    // Generate START condition
    static const uint32_t UCBxCTLW0_UCTXSTT__UCTXSTT_1 = 1;
    // No STOP generated
    static const uint32_t UCBxCTLW0_UCTXSTP__UCTXSTP_0 = 0;
    // Generate STOP
    static const uint32_t UCBxCTLW0_UCTXSTP__UCTXSTP_1 = 1;
    // Acknowledge normally
    static const uint32_t UCBxCTLW0_UCTXNACK__UCTXNACK_0 = 0;
    // Generate NACK
    static const uint32_t UCBxCTLW0_UCTXNACK__UCTXNACK_1 = 1;
    // Receiver
    static const uint32_t UCBxCTLW0_UCTR__UCTR_0 = 0;
    // Transmitter
    static const uint32_t UCBxCTLW0_UCTR__UCTR_1 = 1;
    // Do not acknowledge the slave address
    static const uint32_t UCBxCTLW0_UCTXACK__UCTXACK_0 = 0;
    // Acknowledge the slave address
    static const uint32_t UCBxCTLW0_UCTXACK__UCTXACK_1 = 1;
    // UCLKI
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_0 = 0;
    // ACLK
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_1 = 1;
    // SMCLK
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_2 = 2;
    // SMCLK
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_3 = 3;
    // Asynchronous mode
    static const uint32_t UCBxCTLW0_UCSYNC__UCSYNC_0 = 0;
    // Synchronous mode
    static const uint32_t UCBxCTLW0_UCSYNC__UCSYNC_1 = 1;
    // 3-pin SPI
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_0 = 0;
    // 4-pin SPI (master or slave enabled if STE = 1)
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_1 = 1;
    // 4-pin SPI (master or slave enabled if STE = 0)
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_2 = 2;
    // I2C mode
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_3 = 3;
    // Slave mode
    static const uint32_t UCBxCTLW0_UCMST__UCMST_0 = 0;
    // Master mode
    static const uint32_t UCBxCTLW0_UCMST__UCMST_1 = 1;
    // Single master environment. There is no other master in the system. The address compare unit is disabled.
    static const uint32_t UCBxCTLW0_UCMM__UCMM_0 = 0;
    // Multi-master environment
    static const uint32_t UCBxCTLW0_UCMM__UCMM_1 = 1;
    // Address slave with 7-bit address
    static const uint32_t UCBxCTLW0_UCSLA10__UCSLA10_0 = 0;
    // Address slave with 10-bit address
    static const uint32_t UCBxCTLW0_UCSLA10__UCSLA10_1 = 1;
    // Own address is a 7-bit address
    static const uint32_t UCBxCTLW0_UCA10__UCA10_0 = 0;
    // Own address is a 10-bit address
    static const uint32_t UCBxCTLW0_UCA10__UCA10_1 = 1;

    // eUSCI_Bx Control Word Register 1
    // Reset value: 0x00000003
    BEGIN_TYPE(UCBxCTLW1_t, uint16_t)
        // Deglitch time
        ADD_BITFIELD_RW(UCGLIT, 0, 2)
        // Automatic STOP condition generation
        ADD_BITFIELD_RW(UCASTP, 2, 2)
        // SW or HW ACK control
        ADD_BITFIELD_RW(UCSWACK, 4, 1)
        // ACK all master bytes
        ADD_BITFIELD_RW(UCSTPNACK, 5, 1)
        // Clock low timeout select
        ADD_BITFIELD_RW(UCCLTO, 6, 2)
        // Early UCTXIFG0
        ADD_BITFIELD_RW(UCETXINT, 8, 1)
    END_TYPE()

    // 50 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_0 = 0;
    // 25 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_1 = 1;
    // 12.5 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_2 = 2;
    // 6.25 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_3 = 3;
    // No automatic STOP generation. The STOP condition is generated after the user sets the UCTXSTP bit. The value in UCBxTBCNT is a don't care.
    static const uint32_t UCBxCTLW1_UCASTP__UCASTP_0 = 0;
    // UCBCNTIFG is set with the byte counter reaches the threshold defined in UCBxTBCNT
    static const uint32_t UCBxCTLW1_UCASTP__UCASTP_1 = 1;
    // A STOP condition is generated automatically after the byte counter value reached UCBxTBCNT. UCBCNTIFG is set with the byte counter reaching the threshold
    static const uint32_t UCBxCTLW1_UCASTP__UCASTP_2 = 2;
    // The address acknowledge of the slave is controlled by the eUSCI_B module
    static const uint32_t UCBxCTLW1_UCSWACK__UCSWACK_0 = 0;
    // The user needs to trigger the sending of the address ACK by issuing UCTXACK
    static const uint32_t UCBxCTLW1_UCSWACK__UCSWACK_1 = 1;
    // Send a non-acknowledge before the STOP condition as a master receiver (conform to I2C standard)
    static const uint32_t UCBxCTLW1_UCSTPNACK__UCSTPNACK_0 = 0;
    // All bytes are acknowledged by the eUSCI_B when configured as master receiver
    static const uint32_t UCBxCTLW1_UCSTPNACK__UCSTPNACK_1 = 1;
    // Disable clock low timeout counter
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_0 = 0;
    // 135 000 SYSCLK cycles (approximately 28 ms)
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_1 = 1;
    // 150 000 SYSCLK cycles (approximately 31 ms)
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_2 = 2;
    // 165 000 SYSCLK cycles (approximately 34 ms)
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_3 = 3;
    // UCTXIFGx is set after an address match with UCxI2COAx and the direction bit indicating slave transmit
    static const uint32_t UCBxCTLW1_UCETXINT__UCETXINT_0 = 0;
    // UCTXIFG0 is set for each START condition
    static const uint32_t UCBxCTLW1_UCETXINT__UCETXINT_1 = 1;

    // eUSCI_Bx Baud Rate Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxBRW_t, uint16_t)
        // Bit clock prescaler
        ADD_BITFIELD_RW(UCBR, 0, 16)
    END_TYPE()

    // eUSCI_Bx Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxSTATW_t, uint16_t)
        // Bus busy
        ADD_BITFIELD_RO(UCBBUSY, 4, 1)
        // General call address received
        ADD_BITFIELD_RO(UCGC, 5, 1)
        // SCL low
        ADD_BITFIELD_RO(UCSCLLOW, 6, 1)
        // Hardware byte counter value
        ADD_BITFIELD_RO(UCBCNT, 8, 8)
    END_TYPE()

    // Bus inactive
    static const uint32_t UCBxSTATW_UCBBUSY__UCBBUSY_0 = 0;
    // Bus busy
    static const uint32_t UCBxSTATW_UCBBUSY__UCBBUSY_1 = 1;
    // No general call address received
    static const uint32_t UCBxSTATW_UCGC__UCGC_0 = 0;
    // General call address received
    static const uint32_t UCBxSTATW_UCGC__UCGC_1 = 1;
    // SCL is not held low
    static const uint32_t UCBxSTATW_UCSCLLOW__UCSCLLOW_0 = 0;
    // SCL is held low
    static const uint32_t UCBxSTATW_UCSCLLOW__UCSCLLOW_1 = 1;

    // eUSCI_Bx Byte Counter Threshold Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxTBCNT_t, uint16_t)
        // Byte counter threshold value
        ADD_BITFIELD_RW(UCTBCNT, 0, 8)
    END_TYPE()

    // eUSCI_Bx Receive Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxRXBUF_t, uint16_t)
        // Receive data buffer
        ADD_BITFIELD_RO(UCRXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Bx Transmit Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxTXBUF_t, uint16_t)
        // Transmit data buffer
        ADD_BITFIELD_RW(UCTXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Bx I2C Own Address 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA0_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA0, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
        // General call response enable
        ADD_BITFIELD_RW(UCGCEN, 15, 1)
    END_TYPE()

    // The slave address defined in I2COA0 is disabled
    static const uint32_t UCBxI2COA0_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA0 is enabled
    static const uint32_t UCBxI2COA0_UCOAEN__UCOAEN_1 = 1;
    // Do not respond to a general call
    static const uint32_t UCBxI2COA0_UCGCEN__UCGCEN_0 = 0;
    // Respond to a general call
    static const uint32_t UCBxI2COA0_UCGCEN__UCGCEN_1 = 1;

    // eUSCI_Bx I2C Own Address 1 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA1_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA1, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
    END_TYPE()

    // The slave address defined in I2COA1 is disabled
    static const uint32_t UCBxI2COA1_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA1 is enabled
    static const uint32_t UCBxI2COA1_UCOAEN__UCOAEN_1 = 1;

    // eUSCI_Bx I2C Own Address 2 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA2_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA2, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
    END_TYPE()

    // The slave address defined in I2COA2 is disabled
    static const uint32_t UCBxI2COA2_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA2 is enabled
    static const uint32_t UCBxI2COA2_UCOAEN__UCOAEN_1 = 1;

    // eUSCI_Bx I2C Own Address 3 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA3_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA3, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
    END_TYPE()

    // The slave address defined in I2COA3 is disabled
    static const uint32_t UCBxI2COA3_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA3 is enabled
    static const uint32_t UCBxI2COA3_UCOAEN__UCOAEN_1 = 1;

    // eUSCI_Bx I2C Received Address Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxADDRX_t, uint16_t)
        // Received Address Register
        ADD_BITFIELD_RO(ADDRX, 0, 10)
    END_TYPE()

    // eUSCI_Bx I2C Address Mask Register
    // Reset value: 0x000003ff
    BEGIN_TYPE(UCBxADDMASK_t, uint16_t)
        // Address Mask Register. By clearing the corresponding bit of the own address, this bit is a don't care when comparing the address on the bus to the own address. Using this method, it is possible to react on more than one slave address. When all bits of ADDMASKx are set, the address mask feature is deactivated. Modify only when UCSWRST = 1.
        ADD_BITFIELD_RW(ADDMASK, 0, 10)
    END_TYPE()

    // eUSCI_Bx I2C Slave Address Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2CSA_t, uint16_t)
        // I2C slave address
        ADD_BITFIELD_RW(I2CSA, 0, 10)
    END_TYPE()

    // eUSCI_Bx Interrupt Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxIE_t, uint16_t)
        // Receive interrupt enable 0
        ADD_BITFIELD_RW(UCRXIE0, 0, 1)
        // Transmit interrupt enable 0
        ADD_BITFIELD_RW(UCTXIE0, 1, 1)
        // START condition interrupt enable
        ADD_BITFIELD_RW(UCSTTIE, 2, 1)
        // STOP condition interrupt enable
        ADD_BITFIELD_RW(UCSTPIE, 3, 1)
        // Arbitration lost interrupt enable
        ADD_BITFIELD_RW(UCALIE, 4, 1)
        // Not-acknowledge interrupt enable
        ADD_BITFIELD_RW(UCNACKIE, 5, 1)
        // Byte counter interrupt enable
        ADD_BITFIELD_RW(UCBCNTIE, 6, 1)
        // Clock low timeout interrupt enable
        ADD_BITFIELD_RW(UCCLTOIE, 7, 1)
        // Receive interrupt enable 1
        ADD_BITFIELD_RW(UCRXIE1, 8, 1)
        // Transmit interrupt enable 1
        ADD_BITFIELD_RW(UCTXIE1, 9, 1)
        // Receive interrupt enable 2
        ADD_BITFIELD_RW(UCRXIE2, 10, 1)
        // Transmit interrupt enable 2
        ADD_BITFIELD_RW(UCTXIE2, 11, 1)
        // Receive interrupt enable 3
        ADD_BITFIELD_RW(UCRXIE3, 12, 1)
        // Transmit interrupt enable 3
        ADD_BITFIELD_RW(UCTXIE3, 13, 1)
        // Bit position 9 interrupt enable
        ADD_BITFIELD_RW(UCBIT9IE, 14, 1)
    END_TYPE()

    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE0__UCRXIE0_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE0__UCRXIE0_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE0__UCTXIE0_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE0__UCTXIE0_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCSTTIE__UCSTTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCSTTIE__UCSTTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCSTPIE__UCSTPIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCSTPIE__UCSTPIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCALIE__UCALIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCALIE__UCALIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCNACKIE__UCNACKIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCNACKIE__UCNACKIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCBCNTIE__UCBCNTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCBCNTIE__UCBCNTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCCLTOIE__UCCLTOIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCCLTOIE__UCCLTOIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE1__UCRXIE1_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE1__UCRXIE1_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE1__UCTXIE1_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE1__UCTXIE1_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE2__UCRXIE2_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE2__UCRXIE2_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE2__UCTXIE2_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE2__UCTXIE2_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE3__UCRXIE3_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE3__UCRXIE3_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE3__UCTXIE3_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE3__UCTXIE3_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCBIT9IE__UCBIT9IE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCBIT9IE__UCBIT9IE_1 = 1;

    // eUSCI_Bx Interrupt Flag Register
    // Reset value: 0x00000002
    BEGIN_TYPE(UCBxIFG_t, uint16_t)
        // eUSCI_B receive interrupt flag 0
        ADD_BITFIELD_RW(UCRXIFG0, 0, 1)
        // eUSCI_B transmit interrupt flag 0
        ADD_BITFIELD_RW(UCTXIFG0, 1, 1)
        // START condition interrupt flag
        ADD_BITFIELD_RW(UCSTTIFG, 2, 1)
        // STOP condition interrupt flag
        ADD_BITFIELD_RW(UCSTPIFG, 3, 1)
        // Arbitration lost interrupt flag
        ADD_BITFIELD_RW(UCALIFG, 4, 1)
        // Not-acknowledge received interrupt flag
        ADD_BITFIELD_RW(UCNACKIFG, 5, 1)
        // Byte counter interrupt flag
        ADD_BITFIELD_RW(UCBCNTIFG, 6, 1)
        // Clock low timeout interrupt flag
        ADD_BITFIELD_RW(UCCLTOIFG, 7, 1)
        // eUSCI_B receive interrupt flag 1
        ADD_BITFIELD_RW(UCRXIFG1, 8, 1)
        // eUSCI_B transmit interrupt flag 1
        ADD_BITFIELD_RW(UCTXIFG1, 9, 1)
        // eUSCI_B receive interrupt flag 2
        ADD_BITFIELD_RW(UCRXIFG2, 10, 1)
        // eUSCI_B transmit interrupt flag 2
        ADD_BITFIELD_RW(UCTXIFG2, 11, 1)
        // eUSCI_B receive interrupt flag 3
        ADD_BITFIELD_RW(UCRXIFG3, 12, 1)
        // eUSCI_B transmit interrupt flag 3
        ADD_BITFIELD_RW(UCTXIFG3, 13, 1)
        // Bit position 9 interrupt flag
        ADD_BITFIELD_RW(UCBIT9IFG, 14, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG0__UCRXIFG0_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG0__UCRXIFG0_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG0__UCTXIFG0_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG0__UCTXIFG0_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCSTTIFG__UCSTTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCSTTIFG__UCSTTIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCSTPIFG__UCSTPIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCSTPIFG__UCSTPIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCALIFG__UCALIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCALIFG__UCALIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCNACKIFG__UCNACKIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCNACKIFG__UCNACKIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCBCNTIFG__UCBCNTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCBCNTIFG__UCBCNTIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCCLTOIFG__UCCLTOIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCCLTOIFG__UCCLTOIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG1__UCRXIFG1_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG1__UCRXIFG1_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG1__UCTXIFG1_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG1__UCTXIFG1_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG2__UCRXIFG2_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG2__UCRXIFG2_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG2__UCTXIFG2_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG2__UCTXIFG2_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG3__UCRXIFG3_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG3__UCRXIFG3_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG3__UCTXIFG3_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG3__UCTXIFG3_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCBIT9IFG__UCBIT9IFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCBIT9IFG__UCBIT9IFG_1 = 1;

    // eUSCI_Bx Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxIV_t, uint16_t)
        // eUSCI_B interrupt vector value
        ADD_BITFIELD_RO(UCIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCBxIV_UCIV__UCIV_0 = 0;
    // Interrupt Source: Arbitration lost; Interrupt Flag: UCALIFG; Interrupt Priority: Highest
    static const uint32_t UCBxIV_UCIV__UCIV_2 = 2;
    // Interrupt Source: Not acknowledgment; Interrupt Flag: UCNACKIFG
    static const uint32_t UCBxIV_UCIV__UCIV_4 = 4;
    // Interrupt Source: Start condition received; Interrupt Flag: UCSTTIFG
    static const uint32_t UCBxIV_UCIV__UCIV_6 = 6;
    // Interrupt Source: Stop condition received; Interrupt Flag: UCSTPIFG
    static const uint32_t UCBxIV_UCIV__UCIV_8 = 8;
    // Interrupt Source: Slave 3 Data received; Interrupt Flag: UCRXIFG3
    static const uint32_t UCBxIV_UCIV__UCIV_10 = 10;
    // Interrupt Source: Slave 3 Transmit buffer empty; Interrupt Flag: UCTXIFG3
    static const uint32_t UCBxIV_UCIV__UCIV_12 = 12;
    // Interrupt Source: Slave 2 Data received; Interrupt Flag: UCRXIFG2
    static const uint32_t UCBxIV_UCIV__UCIV_14 = 14;
    // Interrupt Source: Slave 2 Transmit buffer empty; Interrupt Flag: UCTXIFG2
    static const uint32_t UCBxIV_UCIV__UCIV_16 = 16;
    // Interrupt Source: Slave 1 Data received; Interrupt Flag: UCRXIFG1
    static const uint32_t UCBxIV_UCIV__UCIV_18 = 18;
    // Interrupt Source: Slave 1 Transmit buffer empty; Interrupt Flag: UCTXIFG1
    static const uint32_t UCBxIV_UCIV__UCIV_20 = 20;
    // Interrupt Source: Data received; Interrupt Flag: UCRXIFG0
    static const uint32_t UCBxIV_UCIV__UCIV_22 = 22;
    // Interrupt Source: Transmit buffer empty; Interrupt Flag: UCTXIFG0
    static const uint32_t UCBxIV_UCIV__UCIV_24 = 24;
    // Interrupt Source: Byte counter zero; Interrupt Flag: UCBCNTIFG
    static const uint32_t UCBxIV_UCIV__UCIV_26 = 26;
    // Interrupt Source: Clock low timeout; Interrupt Flag: UCCLTOIFG
    static const uint32_t UCBxIV_UCIV__UCIV_28 = 28;
    // Interrupt Source: Nineth bit position; Interrupt Flag: UCBIT9IFG; Priority: Lowest
    static const uint32_t UCBxIV_UCIV__UCIV_30 = 30;

    struct EUSCI_B1_t {
        UCBxCTLW0_t                   UCBxCTLW0;
        UCBxCTLW1_t                   UCBxCTLW1;
        uint16_t                      reserved0;
        UCBxBRW_t                     UCBxBRW;
        UCBxSTATW_t                   UCBxSTATW;
        UCBxTBCNT_t                   UCBxTBCNT;
        UCBxRXBUF_t                   UCBxRXBUF;
        UCBxTXBUF_t                   UCBxTXBUF;
        uint16_t                      reserved1[2];
        UCBxI2COA0_t                  UCBxI2COA0;
        UCBxI2COA1_t                  UCBxI2COA1;
        UCBxI2COA2_t                  UCBxI2COA2;
        UCBxI2COA3_t                  UCBxI2COA3;
        UCBxADDRX_t                   UCBxADDRX;
        UCBxADDMASK_t                 UCBxADDMASK;
        UCBxI2CSA_t                   UCBxI2CSA;
        uint16_t                      reserved2[4];
        UCBxIE_t                      UCBxIE;
        UCBxIFG_t                     UCBxIFG;
        UCBxIV_t                      UCBxIV;
    };

    static EUSCI_B1_t & EUSCI_B1     = (*(EUSCI_B1_t *)0x40002400);

} // _EUSCI_B1_

// EUSCI_B2
namespace _EUSCI_B2_  {

    // eUSCI_Bx Control Word Register 0
    // Reset value: 0x000001c1
    BEGIN_TYPE(UCBxCTLW0_t, uint16_t)
        // Software reset enable
        ADD_BITFIELD_RW(UCSWRST, 0, 1)
        // Transmit START condition in master mode
        ADD_BITFIELD_RW(UCTXSTT, 1, 1)
        // Transmit STOP condition in master mode
        ADD_BITFIELD_RW(UCTXSTP, 2, 1)
        // Transmit a NACK
        ADD_BITFIELD_RW(UCTXNACK, 3, 1)
        // Transmitter/receiver
        ADD_BITFIELD_RW(UCTR, 4, 1)
        // Transmit ACK condition in slave mode
        ADD_BITFIELD_RW(UCTXACK, 5, 1)
        // eUSCI_B clock source select
        ADD_BITFIELD_RW(UCSSEL, 6, 2)
        // Synchronous mode enable
        ADD_BITFIELD_RW(UCSYNC, 8, 1)
        // eUSCI_B mode
        ADD_BITFIELD_RW(UCMODE, 9, 2)
        // Master mode select
        ADD_BITFIELD_RW(UCMST, 11, 1)
        // Multi-master environment select
        ADD_BITFIELD_RW(UCMM, 13, 1)
        // Slave addressing mode select
        ADD_BITFIELD_RW(UCSLA10, 14, 1)
        // Own addressing mode select
        ADD_BITFIELD_RW(UCA10, 15, 1)
    END_TYPE()

    // Disabled. eUSCI_B reset released for operation
    static const uint32_t UCBxCTLW0_UCSWRST__UCSWRST_0 = 0;
    // Enabled. eUSCI_B logic held in reset state
    static const uint32_t UCBxCTLW0_UCSWRST__UCSWRST_1 = 1;
    // Do not generate START condition
    static const uint32_t UCBxCTLW0_UCTXSTT__UCTXSTT_0 = 0;
    // Generate START condition
    static const uint32_t UCBxCTLW0_UCTXSTT__UCTXSTT_1 = 1;
    // No STOP generated
    static const uint32_t UCBxCTLW0_UCTXSTP__UCTXSTP_0 = 0;
    // Generate STOP
    static const uint32_t UCBxCTLW0_UCTXSTP__UCTXSTP_1 = 1;
    // Acknowledge normally
    static const uint32_t UCBxCTLW0_UCTXNACK__UCTXNACK_0 = 0;
    // Generate NACK
    static const uint32_t UCBxCTLW0_UCTXNACK__UCTXNACK_1 = 1;
    // Receiver
    static const uint32_t UCBxCTLW0_UCTR__UCTR_0 = 0;
    // Transmitter
    static const uint32_t UCBxCTLW0_UCTR__UCTR_1 = 1;
    // Do not acknowledge the slave address
    static const uint32_t UCBxCTLW0_UCTXACK__UCTXACK_0 = 0;
    // Acknowledge the slave address
    static const uint32_t UCBxCTLW0_UCTXACK__UCTXACK_1 = 1;
    // UCLKI
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_0 = 0;
    // ACLK
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_1 = 1;
    // SMCLK
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_2 = 2;
    // SMCLK
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_3 = 3;
    // Asynchronous mode
    static const uint32_t UCBxCTLW0_UCSYNC__UCSYNC_0 = 0;
    // Synchronous mode
    static const uint32_t UCBxCTLW0_UCSYNC__UCSYNC_1 = 1;
    // 3-pin SPI
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_0 = 0;
    // 4-pin SPI (master or slave enabled if STE = 1)
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_1 = 1;
    // 4-pin SPI (master or slave enabled if STE = 0)
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_2 = 2;
    // I2C mode
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_3 = 3;
    // Slave mode
    static const uint32_t UCBxCTLW0_UCMST__UCMST_0 = 0;
    // Master mode
    static const uint32_t UCBxCTLW0_UCMST__UCMST_1 = 1;
    // Single master environment. There is no other master in the system. The address compare unit is disabled.
    static const uint32_t UCBxCTLW0_UCMM__UCMM_0 = 0;
    // Multi-master environment
    static const uint32_t UCBxCTLW0_UCMM__UCMM_1 = 1;
    // Address slave with 7-bit address
    static const uint32_t UCBxCTLW0_UCSLA10__UCSLA10_0 = 0;
    // Address slave with 10-bit address
    static const uint32_t UCBxCTLW0_UCSLA10__UCSLA10_1 = 1;
    // Own address is a 7-bit address
    static const uint32_t UCBxCTLW0_UCA10__UCA10_0 = 0;
    // Own address is a 10-bit address
    static const uint32_t UCBxCTLW0_UCA10__UCA10_1 = 1;

    // eUSCI_Bx Control Word Register 1
    // Reset value: 0x00000003
    BEGIN_TYPE(UCBxCTLW1_t, uint16_t)
        // Deglitch time
        ADD_BITFIELD_RW(UCGLIT, 0, 2)
        // Automatic STOP condition generation
        ADD_BITFIELD_RW(UCASTP, 2, 2)
        // SW or HW ACK control
        ADD_BITFIELD_RW(UCSWACK, 4, 1)
        // ACK all master bytes
        ADD_BITFIELD_RW(UCSTPNACK, 5, 1)
        // Clock low timeout select
        ADD_BITFIELD_RW(UCCLTO, 6, 2)
        // Early UCTXIFG0
        ADD_BITFIELD_RW(UCETXINT, 8, 1)
    END_TYPE()

    // 50 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_0 = 0;
    // 25 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_1 = 1;
    // 12.5 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_2 = 2;
    // 6.25 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_3 = 3;
    // No automatic STOP generation. The STOP condition is generated after the user sets the UCTXSTP bit. The value in UCBxTBCNT is a don't care.
    static const uint32_t UCBxCTLW1_UCASTP__UCASTP_0 = 0;
    // UCBCNTIFG is set with the byte counter reaches the threshold defined in UCBxTBCNT
    static const uint32_t UCBxCTLW1_UCASTP__UCASTP_1 = 1;
    // A STOP condition is generated automatically after the byte counter value reached UCBxTBCNT. UCBCNTIFG is set with the byte counter reaching the threshold
    static const uint32_t UCBxCTLW1_UCASTP__UCASTP_2 = 2;
    // The address acknowledge of the slave is controlled by the eUSCI_B module
    static const uint32_t UCBxCTLW1_UCSWACK__UCSWACK_0 = 0;
    // The user needs to trigger the sending of the address ACK by issuing UCTXACK
    static const uint32_t UCBxCTLW1_UCSWACK__UCSWACK_1 = 1;
    // Send a non-acknowledge before the STOP condition as a master receiver (conform to I2C standard)
    static const uint32_t UCBxCTLW1_UCSTPNACK__UCSTPNACK_0 = 0;
    // All bytes are acknowledged by the eUSCI_B when configured as master receiver
    static const uint32_t UCBxCTLW1_UCSTPNACK__UCSTPNACK_1 = 1;
    // Disable clock low timeout counter
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_0 = 0;
    // 135 000 SYSCLK cycles (approximately 28 ms)
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_1 = 1;
    // 150 000 SYSCLK cycles (approximately 31 ms)
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_2 = 2;
    // 165 000 SYSCLK cycles (approximately 34 ms)
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_3 = 3;
    // UCTXIFGx is set after an address match with UCxI2COAx and the direction bit indicating slave transmit
    static const uint32_t UCBxCTLW1_UCETXINT__UCETXINT_0 = 0;
    // UCTXIFG0 is set for each START condition
    static const uint32_t UCBxCTLW1_UCETXINT__UCETXINT_1 = 1;

    // eUSCI_Bx Baud Rate Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxBRW_t, uint16_t)
        // Bit clock prescaler
        ADD_BITFIELD_RW(UCBR, 0, 16)
    END_TYPE()

    // eUSCI_Bx Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxSTATW_t, uint16_t)
        // Bus busy
        ADD_BITFIELD_RO(UCBBUSY, 4, 1)
        // General call address received
        ADD_BITFIELD_RO(UCGC, 5, 1)
        // SCL low
        ADD_BITFIELD_RO(UCSCLLOW, 6, 1)
        // Hardware byte counter value
        ADD_BITFIELD_RO(UCBCNT, 8, 8)
    END_TYPE()

    // Bus inactive
    static const uint32_t UCBxSTATW_UCBBUSY__UCBBUSY_0 = 0;
    // Bus busy
    static const uint32_t UCBxSTATW_UCBBUSY__UCBBUSY_1 = 1;
    // No general call address received
    static const uint32_t UCBxSTATW_UCGC__UCGC_0 = 0;
    // General call address received
    static const uint32_t UCBxSTATW_UCGC__UCGC_1 = 1;
    // SCL is not held low
    static const uint32_t UCBxSTATW_UCSCLLOW__UCSCLLOW_0 = 0;
    // SCL is held low
    static const uint32_t UCBxSTATW_UCSCLLOW__UCSCLLOW_1 = 1;

    // eUSCI_Bx Byte Counter Threshold Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxTBCNT_t, uint16_t)
        // Byte counter threshold value
        ADD_BITFIELD_RW(UCTBCNT, 0, 8)
    END_TYPE()

    // eUSCI_Bx Receive Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxRXBUF_t, uint16_t)
        // Receive data buffer
        ADD_BITFIELD_RO(UCRXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Bx Transmit Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxTXBUF_t, uint16_t)
        // Transmit data buffer
        ADD_BITFIELD_RW(UCTXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Bx I2C Own Address 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA0_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA0, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
        // General call response enable
        ADD_BITFIELD_RW(UCGCEN, 15, 1)
    END_TYPE()

    // The slave address defined in I2COA0 is disabled
    static const uint32_t UCBxI2COA0_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA0 is enabled
    static const uint32_t UCBxI2COA0_UCOAEN__UCOAEN_1 = 1;
    // Do not respond to a general call
    static const uint32_t UCBxI2COA0_UCGCEN__UCGCEN_0 = 0;
    // Respond to a general call
    static const uint32_t UCBxI2COA0_UCGCEN__UCGCEN_1 = 1;

    // eUSCI_Bx I2C Own Address 1 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA1_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA1, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
    END_TYPE()

    // The slave address defined in I2COA1 is disabled
    static const uint32_t UCBxI2COA1_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA1 is enabled
    static const uint32_t UCBxI2COA1_UCOAEN__UCOAEN_1 = 1;

    // eUSCI_Bx I2C Own Address 2 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA2_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA2, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
    END_TYPE()

    // The slave address defined in I2COA2 is disabled
    static const uint32_t UCBxI2COA2_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA2 is enabled
    static const uint32_t UCBxI2COA2_UCOAEN__UCOAEN_1 = 1;

    // eUSCI_Bx I2C Own Address 3 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA3_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA3, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
    END_TYPE()

    // The slave address defined in I2COA3 is disabled
    static const uint32_t UCBxI2COA3_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA3 is enabled
    static const uint32_t UCBxI2COA3_UCOAEN__UCOAEN_1 = 1;

    // eUSCI_Bx I2C Received Address Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxADDRX_t, uint16_t)
        // Received Address Register
        ADD_BITFIELD_RO(ADDRX, 0, 10)
    END_TYPE()

    // eUSCI_Bx I2C Address Mask Register
    // Reset value: 0x000003ff
    BEGIN_TYPE(UCBxADDMASK_t, uint16_t)
        // Address Mask Register. By clearing the corresponding bit of the own address, this bit is a don't care when comparing the address on the bus to the own address. Using this method, it is possible to react on more than one slave address. When all bits of ADDMASKx are set, the address mask feature is deactivated. Modify only when UCSWRST = 1.
        ADD_BITFIELD_RW(ADDMASK, 0, 10)
    END_TYPE()

    // eUSCI_Bx I2C Slave Address Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2CSA_t, uint16_t)
        // I2C slave address
        ADD_BITFIELD_RW(I2CSA, 0, 10)
    END_TYPE()

    // eUSCI_Bx Interrupt Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxIE_t, uint16_t)
        // Receive interrupt enable 0
        ADD_BITFIELD_RW(UCRXIE0, 0, 1)
        // Transmit interrupt enable 0
        ADD_BITFIELD_RW(UCTXIE0, 1, 1)
        // START condition interrupt enable
        ADD_BITFIELD_RW(UCSTTIE, 2, 1)
        // STOP condition interrupt enable
        ADD_BITFIELD_RW(UCSTPIE, 3, 1)
        // Arbitration lost interrupt enable
        ADD_BITFIELD_RW(UCALIE, 4, 1)
        // Not-acknowledge interrupt enable
        ADD_BITFIELD_RW(UCNACKIE, 5, 1)
        // Byte counter interrupt enable
        ADD_BITFIELD_RW(UCBCNTIE, 6, 1)
        // Clock low timeout interrupt enable
        ADD_BITFIELD_RW(UCCLTOIE, 7, 1)
        // Receive interrupt enable 1
        ADD_BITFIELD_RW(UCRXIE1, 8, 1)
        // Transmit interrupt enable 1
        ADD_BITFIELD_RW(UCTXIE1, 9, 1)
        // Receive interrupt enable 2
        ADD_BITFIELD_RW(UCRXIE2, 10, 1)
        // Transmit interrupt enable 2
        ADD_BITFIELD_RW(UCTXIE2, 11, 1)
        // Receive interrupt enable 3
        ADD_BITFIELD_RW(UCRXIE3, 12, 1)
        // Transmit interrupt enable 3
        ADD_BITFIELD_RW(UCTXIE3, 13, 1)
        // Bit position 9 interrupt enable
        ADD_BITFIELD_RW(UCBIT9IE, 14, 1)
    END_TYPE()

    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE0__UCRXIE0_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE0__UCRXIE0_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE0__UCTXIE0_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE0__UCTXIE0_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCSTTIE__UCSTTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCSTTIE__UCSTTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCSTPIE__UCSTPIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCSTPIE__UCSTPIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCALIE__UCALIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCALIE__UCALIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCNACKIE__UCNACKIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCNACKIE__UCNACKIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCBCNTIE__UCBCNTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCBCNTIE__UCBCNTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCCLTOIE__UCCLTOIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCCLTOIE__UCCLTOIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE1__UCRXIE1_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE1__UCRXIE1_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE1__UCTXIE1_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE1__UCTXIE1_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE2__UCRXIE2_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE2__UCRXIE2_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE2__UCTXIE2_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE2__UCTXIE2_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE3__UCRXIE3_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE3__UCRXIE3_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE3__UCTXIE3_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE3__UCTXIE3_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCBIT9IE__UCBIT9IE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCBIT9IE__UCBIT9IE_1 = 1;

    // eUSCI_Bx Interrupt Flag Register
    // Reset value: 0x00000002
    BEGIN_TYPE(UCBxIFG_t, uint16_t)
        // eUSCI_B receive interrupt flag 0
        ADD_BITFIELD_RW(UCRXIFG0, 0, 1)
        // eUSCI_B transmit interrupt flag 0
        ADD_BITFIELD_RW(UCTXIFG0, 1, 1)
        // START condition interrupt flag
        ADD_BITFIELD_RW(UCSTTIFG, 2, 1)
        // STOP condition interrupt flag
        ADD_BITFIELD_RW(UCSTPIFG, 3, 1)
        // Arbitration lost interrupt flag
        ADD_BITFIELD_RW(UCALIFG, 4, 1)
        // Not-acknowledge received interrupt flag
        ADD_BITFIELD_RW(UCNACKIFG, 5, 1)
        // Byte counter interrupt flag
        ADD_BITFIELD_RW(UCBCNTIFG, 6, 1)
        // Clock low timeout interrupt flag
        ADD_BITFIELD_RW(UCCLTOIFG, 7, 1)
        // eUSCI_B receive interrupt flag 1
        ADD_BITFIELD_RW(UCRXIFG1, 8, 1)
        // eUSCI_B transmit interrupt flag 1
        ADD_BITFIELD_RW(UCTXIFG1, 9, 1)
        // eUSCI_B receive interrupt flag 2
        ADD_BITFIELD_RW(UCRXIFG2, 10, 1)
        // eUSCI_B transmit interrupt flag 2
        ADD_BITFIELD_RW(UCTXIFG2, 11, 1)
        // eUSCI_B receive interrupt flag 3
        ADD_BITFIELD_RW(UCRXIFG3, 12, 1)
        // eUSCI_B transmit interrupt flag 3
        ADD_BITFIELD_RW(UCTXIFG3, 13, 1)
        // Bit position 9 interrupt flag
        ADD_BITFIELD_RW(UCBIT9IFG, 14, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG0__UCRXIFG0_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG0__UCRXIFG0_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG0__UCTXIFG0_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG0__UCTXIFG0_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCSTTIFG__UCSTTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCSTTIFG__UCSTTIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCSTPIFG__UCSTPIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCSTPIFG__UCSTPIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCALIFG__UCALIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCALIFG__UCALIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCNACKIFG__UCNACKIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCNACKIFG__UCNACKIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCBCNTIFG__UCBCNTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCBCNTIFG__UCBCNTIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCCLTOIFG__UCCLTOIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCCLTOIFG__UCCLTOIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG1__UCRXIFG1_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG1__UCRXIFG1_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG1__UCTXIFG1_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG1__UCTXIFG1_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG2__UCRXIFG2_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG2__UCRXIFG2_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG2__UCTXIFG2_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG2__UCTXIFG2_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG3__UCRXIFG3_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG3__UCRXIFG3_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG3__UCTXIFG3_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG3__UCTXIFG3_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCBIT9IFG__UCBIT9IFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCBIT9IFG__UCBIT9IFG_1 = 1;

    // eUSCI_Bx Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxIV_t, uint16_t)
        // eUSCI_B interrupt vector value
        ADD_BITFIELD_RO(UCIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCBxIV_UCIV__UCIV_0 = 0;
    // Interrupt Source: Arbitration lost; Interrupt Flag: UCALIFG; Interrupt Priority: Highest
    static const uint32_t UCBxIV_UCIV__UCIV_2 = 2;
    // Interrupt Source: Not acknowledgment; Interrupt Flag: UCNACKIFG
    static const uint32_t UCBxIV_UCIV__UCIV_4 = 4;
    // Interrupt Source: Start condition received; Interrupt Flag: UCSTTIFG
    static const uint32_t UCBxIV_UCIV__UCIV_6 = 6;
    // Interrupt Source: Stop condition received; Interrupt Flag: UCSTPIFG
    static const uint32_t UCBxIV_UCIV__UCIV_8 = 8;
    // Interrupt Source: Slave 3 Data received; Interrupt Flag: UCRXIFG3
    static const uint32_t UCBxIV_UCIV__UCIV_10 = 10;
    // Interrupt Source: Slave 3 Transmit buffer empty; Interrupt Flag: UCTXIFG3
    static const uint32_t UCBxIV_UCIV__UCIV_12 = 12;
    // Interrupt Source: Slave 2 Data received; Interrupt Flag: UCRXIFG2
    static const uint32_t UCBxIV_UCIV__UCIV_14 = 14;
    // Interrupt Source: Slave 2 Transmit buffer empty; Interrupt Flag: UCTXIFG2
    static const uint32_t UCBxIV_UCIV__UCIV_16 = 16;
    // Interrupt Source: Slave 1 Data received; Interrupt Flag: UCRXIFG1
    static const uint32_t UCBxIV_UCIV__UCIV_18 = 18;
    // Interrupt Source: Slave 1 Transmit buffer empty; Interrupt Flag: UCTXIFG1
    static const uint32_t UCBxIV_UCIV__UCIV_20 = 20;
    // Interrupt Source: Data received; Interrupt Flag: UCRXIFG0
    static const uint32_t UCBxIV_UCIV__UCIV_22 = 22;
    // Interrupt Source: Transmit buffer empty; Interrupt Flag: UCTXIFG0
    static const uint32_t UCBxIV_UCIV__UCIV_24 = 24;
    // Interrupt Source: Byte counter zero; Interrupt Flag: UCBCNTIFG
    static const uint32_t UCBxIV_UCIV__UCIV_26 = 26;
    // Interrupt Source: Clock low timeout; Interrupt Flag: UCCLTOIFG
    static const uint32_t UCBxIV_UCIV__UCIV_28 = 28;
    // Interrupt Source: Nineth bit position; Interrupt Flag: UCBIT9IFG; Priority: Lowest
    static const uint32_t UCBxIV_UCIV__UCIV_30 = 30;

    struct EUSCI_B2_t {
        UCBxCTLW0_t                   UCBxCTLW0;
        UCBxCTLW1_t                   UCBxCTLW1;
        uint16_t                      reserved0;
        UCBxBRW_t                     UCBxBRW;
        UCBxSTATW_t                   UCBxSTATW;
        UCBxTBCNT_t                   UCBxTBCNT;
        UCBxRXBUF_t                   UCBxRXBUF;
        UCBxTXBUF_t                   UCBxTXBUF;
        uint16_t                      reserved1[2];
        UCBxI2COA0_t                  UCBxI2COA0;
        UCBxI2COA1_t                  UCBxI2COA1;
        UCBxI2COA2_t                  UCBxI2COA2;
        UCBxI2COA3_t                  UCBxI2COA3;
        UCBxADDRX_t                   UCBxADDRX;
        UCBxADDMASK_t                 UCBxADDMASK;
        UCBxI2CSA_t                   UCBxI2CSA;
        uint16_t                      reserved2[4];
        UCBxIE_t                      UCBxIE;
        UCBxIFG_t                     UCBxIFG;
        UCBxIV_t                      UCBxIV;
    };

    static EUSCI_B2_t & EUSCI_B2     = (*(EUSCI_B2_t *)0x40002800);

} // _EUSCI_B2_

// EUSCI_B3
namespace _EUSCI_B3_  {

    // eUSCI_Bx Control Word Register 0
    // Reset value: 0x000001c1
    BEGIN_TYPE(UCBxCTLW0_t, uint16_t)
        // Software reset enable
        ADD_BITFIELD_RW(UCSWRST, 0, 1)
        // Transmit START condition in master mode
        ADD_BITFIELD_RW(UCTXSTT, 1, 1)
        // Transmit STOP condition in master mode
        ADD_BITFIELD_RW(UCTXSTP, 2, 1)
        // Transmit a NACK
        ADD_BITFIELD_RW(UCTXNACK, 3, 1)
        // Transmitter/receiver
        ADD_BITFIELD_RW(UCTR, 4, 1)
        // Transmit ACK condition in slave mode
        ADD_BITFIELD_RW(UCTXACK, 5, 1)
        // eUSCI_B clock source select
        ADD_BITFIELD_RW(UCSSEL, 6, 2)
        // Synchronous mode enable
        ADD_BITFIELD_RW(UCSYNC, 8, 1)
        // eUSCI_B mode
        ADD_BITFIELD_RW(UCMODE, 9, 2)
        // Master mode select
        ADD_BITFIELD_RW(UCMST, 11, 1)
        // Multi-master environment select
        ADD_BITFIELD_RW(UCMM, 13, 1)
        // Slave addressing mode select
        ADD_BITFIELD_RW(UCSLA10, 14, 1)
        // Own addressing mode select
        ADD_BITFIELD_RW(UCA10, 15, 1)
    END_TYPE()

    // Disabled. eUSCI_B reset released for operation
    static const uint32_t UCBxCTLW0_UCSWRST__UCSWRST_0 = 0;
    // Enabled. eUSCI_B logic held in reset state
    static const uint32_t UCBxCTLW0_UCSWRST__UCSWRST_1 = 1;
    // Do not generate START condition
    static const uint32_t UCBxCTLW0_UCTXSTT__UCTXSTT_0 = 0;
    // Generate START condition
    static const uint32_t UCBxCTLW0_UCTXSTT__UCTXSTT_1 = 1;
    // No STOP generated
    static const uint32_t UCBxCTLW0_UCTXSTP__UCTXSTP_0 = 0;
    // Generate STOP
    static const uint32_t UCBxCTLW0_UCTXSTP__UCTXSTP_1 = 1;
    // Acknowledge normally
    static const uint32_t UCBxCTLW0_UCTXNACK__UCTXNACK_0 = 0;
    // Generate NACK
    static const uint32_t UCBxCTLW0_UCTXNACK__UCTXNACK_1 = 1;
    // Receiver
    static const uint32_t UCBxCTLW0_UCTR__UCTR_0 = 0;
    // Transmitter
    static const uint32_t UCBxCTLW0_UCTR__UCTR_1 = 1;
    // Do not acknowledge the slave address
    static const uint32_t UCBxCTLW0_UCTXACK__UCTXACK_0 = 0;
    // Acknowledge the slave address
    static const uint32_t UCBxCTLW0_UCTXACK__UCTXACK_1 = 1;
    // UCLKI
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_0 = 0;
    // ACLK
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_1 = 1;
    // SMCLK
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_2 = 2;
    // SMCLK
    static const uint32_t UCBxCTLW0_UCSSEL__UCSSEL_3 = 3;
    // Asynchronous mode
    static const uint32_t UCBxCTLW0_UCSYNC__UCSYNC_0 = 0;
    // Synchronous mode
    static const uint32_t UCBxCTLW0_UCSYNC__UCSYNC_1 = 1;
    // 3-pin SPI
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_0 = 0;
    // 4-pin SPI (master or slave enabled if STE = 1)
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_1 = 1;
    // 4-pin SPI (master or slave enabled if STE = 0)
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_2 = 2;
    // I2C mode
    static const uint32_t UCBxCTLW0_UCMODE__UCMODE_3 = 3;
    // Slave mode
    static const uint32_t UCBxCTLW0_UCMST__UCMST_0 = 0;
    // Master mode
    static const uint32_t UCBxCTLW0_UCMST__UCMST_1 = 1;
    // Single master environment. There is no other master in the system. The address compare unit is disabled.
    static const uint32_t UCBxCTLW0_UCMM__UCMM_0 = 0;
    // Multi-master environment
    static const uint32_t UCBxCTLW0_UCMM__UCMM_1 = 1;
    // Address slave with 7-bit address
    static const uint32_t UCBxCTLW0_UCSLA10__UCSLA10_0 = 0;
    // Address slave with 10-bit address
    static const uint32_t UCBxCTLW0_UCSLA10__UCSLA10_1 = 1;
    // Own address is a 7-bit address
    static const uint32_t UCBxCTLW0_UCA10__UCA10_0 = 0;
    // Own address is a 10-bit address
    static const uint32_t UCBxCTLW0_UCA10__UCA10_1 = 1;

    // eUSCI_Bx Control Word Register 1
    // Reset value: 0x00000003
    BEGIN_TYPE(UCBxCTLW1_t, uint16_t)
        // Deglitch time
        ADD_BITFIELD_RW(UCGLIT, 0, 2)
        // Automatic STOP condition generation
        ADD_BITFIELD_RW(UCASTP, 2, 2)
        // SW or HW ACK control
        ADD_BITFIELD_RW(UCSWACK, 4, 1)
        // ACK all master bytes
        ADD_BITFIELD_RW(UCSTPNACK, 5, 1)
        // Clock low timeout select
        ADD_BITFIELD_RW(UCCLTO, 6, 2)
        // Early UCTXIFG0
        ADD_BITFIELD_RW(UCETXINT, 8, 1)
    END_TYPE()

    // 50 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_0 = 0;
    // 25 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_1 = 1;
    // 12.5 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_2 = 2;
    // 6.25 ns
    static const uint32_t UCBxCTLW1_UCGLIT__UCGLIT_3 = 3;
    // No automatic STOP generation. The STOP condition is generated after the user sets the UCTXSTP bit. The value in UCBxTBCNT is a don't care.
    static const uint32_t UCBxCTLW1_UCASTP__UCASTP_0 = 0;
    // UCBCNTIFG is set with the byte counter reaches the threshold defined in UCBxTBCNT
    static const uint32_t UCBxCTLW1_UCASTP__UCASTP_1 = 1;
    // A STOP condition is generated automatically after the byte counter value reached UCBxTBCNT. UCBCNTIFG is set with the byte counter reaching the threshold
    static const uint32_t UCBxCTLW1_UCASTP__UCASTP_2 = 2;
    // The address acknowledge of the slave is controlled by the eUSCI_B module
    static const uint32_t UCBxCTLW1_UCSWACK__UCSWACK_0 = 0;
    // The user needs to trigger the sending of the address ACK by issuing UCTXACK
    static const uint32_t UCBxCTLW1_UCSWACK__UCSWACK_1 = 1;
    // Send a non-acknowledge before the STOP condition as a master receiver (conform to I2C standard)
    static const uint32_t UCBxCTLW1_UCSTPNACK__UCSTPNACK_0 = 0;
    // All bytes are acknowledged by the eUSCI_B when configured as master receiver
    static const uint32_t UCBxCTLW1_UCSTPNACK__UCSTPNACK_1 = 1;
    // Disable clock low timeout counter
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_0 = 0;
    // 135 000 SYSCLK cycles (approximately 28 ms)
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_1 = 1;
    // 150 000 SYSCLK cycles (approximately 31 ms)
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_2 = 2;
    // 165 000 SYSCLK cycles (approximately 34 ms)
    static const uint32_t UCBxCTLW1_UCCLTO__UCCLTO_3 = 3;
    // UCTXIFGx is set after an address match with UCxI2COAx and the direction bit indicating slave transmit
    static const uint32_t UCBxCTLW1_UCETXINT__UCETXINT_0 = 0;
    // UCTXIFG0 is set for each START condition
    static const uint32_t UCBxCTLW1_UCETXINT__UCETXINT_1 = 1;

    // eUSCI_Bx Baud Rate Control Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxBRW_t, uint16_t)
        // Bit clock prescaler
        ADD_BITFIELD_RW(UCBR, 0, 16)
    END_TYPE()

    // eUSCI_Bx Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxSTATW_t, uint16_t)
        // Bus busy
        ADD_BITFIELD_RO(UCBBUSY, 4, 1)
        // General call address received
        ADD_BITFIELD_RO(UCGC, 5, 1)
        // SCL low
        ADD_BITFIELD_RO(UCSCLLOW, 6, 1)
        // Hardware byte counter value
        ADD_BITFIELD_RO(UCBCNT, 8, 8)
    END_TYPE()

    // Bus inactive
    static const uint32_t UCBxSTATW_UCBBUSY__UCBBUSY_0 = 0;
    // Bus busy
    static const uint32_t UCBxSTATW_UCBBUSY__UCBBUSY_1 = 1;
    // No general call address received
    static const uint32_t UCBxSTATW_UCGC__UCGC_0 = 0;
    // General call address received
    static const uint32_t UCBxSTATW_UCGC__UCGC_1 = 1;
    // SCL is not held low
    static const uint32_t UCBxSTATW_UCSCLLOW__UCSCLLOW_0 = 0;
    // SCL is held low
    static const uint32_t UCBxSTATW_UCSCLLOW__UCSCLLOW_1 = 1;

    // eUSCI_Bx Byte Counter Threshold Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxTBCNT_t, uint16_t)
        // Byte counter threshold value
        ADD_BITFIELD_RW(UCTBCNT, 0, 8)
    END_TYPE()

    // eUSCI_Bx Receive Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxRXBUF_t, uint16_t)
        // Receive data buffer
        ADD_BITFIELD_RO(UCRXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Bx Transmit Buffer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxTXBUF_t, uint16_t)
        // Transmit data buffer
        ADD_BITFIELD_RW(UCTXBUF, 0, 8)
    END_TYPE()

    // eUSCI_Bx I2C Own Address 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA0_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA0, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
        // General call response enable
        ADD_BITFIELD_RW(UCGCEN, 15, 1)
    END_TYPE()

    // The slave address defined in I2COA0 is disabled
    static const uint32_t UCBxI2COA0_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA0 is enabled
    static const uint32_t UCBxI2COA0_UCOAEN__UCOAEN_1 = 1;
    // Do not respond to a general call
    static const uint32_t UCBxI2COA0_UCGCEN__UCGCEN_0 = 0;
    // Respond to a general call
    static const uint32_t UCBxI2COA0_UCGCEN__UCGCEN_1 = 1;

    // eUSCI_Bx I2C Own Address 1 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA1_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA1, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
    END_TYPE()

    // The slave address defined in I2COA1 is disabled
    static const uint32_t UCBxI2COA1_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA1 is enabled
    static const uint32_t UCBxI2COA1_UCOAEN__UCOAEN_1 = 1;

    // eUSCI_Bx I2C Own Address 2 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA2_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA2, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
    END_TYPE()

    // The slave address defined in I2COA2 is disabled
    static const uint32_t UCBxI2COA2_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA2 is enabled
    static const uint32_t UCBxI2COA2_UCOAEN__UCOAEN_1 = 1;

    // eUSCI_Bx I2C Own Address 3 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2COA3_t, uint16_t)
        // I2C own address
        ADD_BITFIELD_RW(I2COA3, 0, 10)
        // Own Address enable register
        ADD_BITFIELD_RW(UCOAEN, 10, 1)
    END_TYPE()

    // The slave address defined in I2COA3 is disabled
    static const uint32_t UCBxI2COA3_UCOAEN__UCOAEN_0 = 0;
    // The slave address defined in I2COA3 is enabled
    static const uint32_t UCBxI2COA3_UCOAEN__UCOAEN_1 = 1;

    // eUSCI_Bx I2C Received Address Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxADDRX_t, uint16_t)
        // Received Address Register
        ADD_BITFIELD_RO(ADDRX, 0, 10)
    END_TYPE()

    // eUSCI_Bx I2C Address Mask Register
    // Reset value: 0x000003ff
    BEGIN_TYPE(UCBxADDMASK_t, uint16_t)
        // Address Mask Register. By clearing the corresponding bit of the own address, this bit is a don't care when comparing the address on the bus to the own address. Using this method, it is possible to react on more than one slave address. When all bits of ADDMASKx are set, the address mask feature is deactivated. Modify only when UCSWRST = 1.
        ADD_BITFIELD_RW(ADDMASK, 0, 10)
    END_TYPE()

    // eUSCI_Bx I2C Slave Address Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxI2CSA_t, uint16_t)
        // I2C slave address
        ADD_BITFIELD_RW(I2CSA, 0, 10)
    END_TYPE()

    // eUSCI_Bx Interrupt Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxIE_t, uint16_t)
        // Receive interrupt enable 0
        ADD_BITFIELD_RW(UCRXIE0, 0, 1)
        // Transmit interrupt enable 0
        ADD_BITFIELD_RW(UCTXIE0, 1, 1)
        // START condition interrupt enable
        ADD_BITFIELD_RW(UCSTTIE, 2, 1)
        // STOP condition interrupt enable
        ADD_BITFIELD_RW(UCSTPIE, 3, 1)
        // Arbitration lost interrupt enable
        ADD_BITFIELD_RW(UCALIE, 4, 1)
        // Not-acknowledge interrupt enable
        ADD_BITFIELD_RW(UCNACKIE, 5, 1)
        // Byte counter interrupt enable
        ADD_BITFIELD_RW(UCBCNTIE, 6, 1)
        // Clock low timeout interrupt enable
        ADD_BITFIELD_RW(UCCLTOIE, 7, 1)
        // Receive interrupt enable 1
        ADD_BITFIELD_RW(UCRXIE1, 8, 1)
        // Transmit interrupt enable 1
        ADD_BITFIELD_RW(UCTXIE1, 9, 1)
        // Receive interrupt enable 2
        ADD_BITFIELD_RW(UCRXIE2, 10, 1)
        // Transmit interrupt enable 2
        ADD_BITFIELD_RW(UCTXIE2, 11, 1)
        // Receive interrupt enable 3
        ADD_BITFIELD_RW(UCRXIE3, 12, 1)
        // Transmit interrupt enable 3
        ADD_BITFIELD_RW(UCTXIE3, 13, 1)
        // Bit position 9 interrupt enable
        ADD_BITFIELD_RW(UCBIT9IE, 14, 1)
    END_TYPE()

    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE0__UCRXIE0_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE0__UCRXIE0_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE0__UCTXIE0_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE0__UCTXIE0_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCSTTIE__UCSTTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCSTTIE__UCSTTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCSTPIE__UCSTPIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCSTPIE__UCSTPIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCALIE__UCALIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCALIE__UCALIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCNACKIE__UCNACKIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCNACKIE__UCNACKIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCBCNTIE__UCBCNTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCBCNTIE__UCBCNTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCCLTOIE__UCCLTOIE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCCLTOIE__UCCLTOIE_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE1__UCRXIE1_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE1__UCRXIE1_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE1__UCTXIE1_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE1__UCTXIE1_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE2__UCRXIE2_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE2__UCRXIE2_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE2__UCTXIE2_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE2__UCTXIE2_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCRXIE3__UCRXIE3_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCRXIE3__UCRXIE3_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCTXIE3__UCTXIE3_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCTXIE3__UCTXIE3_1 = 1;
    // Interrupt disabled
    static const uint32_t UCBxIE_UCBIT9IE__UCBIT9IE_0 = 0;
    // Interrupt enabled
    static const uint32_t UCBxIE_UCBIT9IE__UCBIT9IE_1 = 1;

    // eUSCI_Bx Interrupt Flag Register
    // Reset value: 0x00000002
    BEGIN_TYPE(UCBxIFG_t, uint16_t)
        // eUSCI_B receive interrupt flag 0
        ADD_BITFIELD_RW(UCRXIFG0, 0, 1)
        // eUSCI_B transmit interrupt flag 0
        ADD_BITFIELD_RW(UCTXIFG0, 1, 1)
        // START condition interrupt flag
        ADD_BITFIELD_RW(UCSTTIFG, 2, 1)
        // STOP condition interrupt flag
        ADD_BITFIELD_RW(UCSTPIFG, 3, 1)
        // Arbitration lost interrupt flag
        ADD_BITFIELD_RW(UCALIFG, 4, 1)
        // Not-acknowledge received interrupt flag
        ADD_BITFIELD_RW(UCNACKIFG, 5, 1)
        // Byte counter interrupt flag
        ADD_BITFIELD_RW(UCBCNTIFG, 6, 1)
        // Clock low timeout interrupt flag
        ADD_BITFIELD_RW(UCCLTOIFG, 7, 1)
        // eUSCI_B receive interrupt flag 1
        ADD_BITFIELD_RW(UCRXIFG1, 8, 1)
        // eUSCI_B transmit interrupt flag 1
        ADD_BITFIELD_RW(UCTXIFG1, 9, 1)
        // eUSCI_B receive interrupt flag 2
        ADD_BITFIELD_RW(UCRXIFG2, 10, 1)
        // eUSCI_B transmit interrupt flag 2
        ADD_BITFIELD_RW(UCTXIFG2, 11, 1)
        // eUSCI_B receive interrupt flag 3
        ADD_BITFIELD_RW(UCRXIFG3, 12, 1)
        // eUSCI_B transmit interrupt flag 3
        ADD_BITFIELD_RW(UCTXIFG3, 13, 1)
        // Bit position 9 interrupt flag
        ADD_BITFIELD_RW(UCBIT9IFG, 14, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG0__UCRXIFG0_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG0__UCRXIFG0_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG0__UCTXIFG0_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG0__UCTXIFG0_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCSTTIFG__UCSTTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCSTTIFG__UCSTTIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCSTPIFG__UCSTPIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCSTPIFG__UCSTPIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCALIFG__UCALIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCALIFG__UCALIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCNACKIFG__UCNACKIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCNACKIFG__UCNACKIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCBCNTIFG__UCBCNTIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCBCNTIFG__UCBCNTIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCCLTOIFG__UCCLTOIFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCCLTOIFG__UCCLTOIFG_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG1__UCRXIFG1_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG1__UCRXIFG1_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG1__UCTXIFG1_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG1__UCTXIFG1_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG2__UCRXIFG2_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG2__UCRXIFG2_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG2__UCTXIFG2_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG2__UCTXIFG2_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG3__UCRXIFG3_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCRXIFG3__UCRXIFG3_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG3__UCTXIFG3_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCTXIFG3__UCTXIFG3_1 = 1;
    // No interrupt pending
    static const uint32_t UCBxIFG_UCBIT9IFG__UCBIT9IFG_0 = 0;
    // Interrupt pending
    static const uint32_t UCBxIFG_UCBIT9IFG__UCBIT9IFG_1 = 1;

    // eUSCI_Bx Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UCBxIV_t, uint16_t)
        // eUSCI_B interrupt vector value
        ADD_BITFIELD_RO(UCIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t UCBxIV_UCIV__UCIV_0 = 0;
    // Interrupt Source: Arbitration lost; Interrupt Flag: UCALIFG; Interrupt Priority: Highest
    static const uint32_t UCBxIV_UCIV__UCIV_2 = 2;
    // Interrupt Source: Not acknowledgment; Interrupt Flag: UCNACKIFG
    static const uint32_t UCBxIV_UCIV__UCIV_4 = 4;
    // Interrupt Source: Start condition received; Interrupt Flag: UCSTTIFG
    static const uint32_t UCBxIV_UCIV__UCIV_6 = 6;
    // Interrupt Source: Stop condition received; Interrupt Flag: UCSTPIFG
    static const uint32_t UCBxIV_UCIV__UCIV_8 = 8;
    // Interrupt Source: Slave 3 Data received; Interrupt Flag: UCRXIFG3
    static const uint32_t UCBxIV_UCIV__UCIV_10 = 10;
    // Interrupt Source: Slave 3 Transmit buffer empty; Interrupt Flag: UCTXIFG3
    static const uint32_t UCBxIV_UCIV__UCIV_12 = 12;
    // Interrupt Source: Slave 2 Data received; Interrupt Flag: UCRXIFG2
    static const uint32_t UCBxIV_UCIV__UCIV_14 = 14;
    // Interrupt Source: Slave 2 Transmit buffer empty; Interrupt Flag: UCTXIFG2
    static const uint32_t UCBxIV_UCIV__UCIV_16 = 16;
    // Interrupt Source: Slave 1 Data received; Interrupt Flag: UCRXIFG1
    static const uint32_t UCBxIV_UCIV__UCIV_18 = 18;
    // Interrupt Source: Slave 1 Transmit buffer empty; Interrupt Flag: UCTXIFG1
    static const uint32_t UCBxIV_UCIV__UCIV_20 = 20;
    // Interrupt Source: Data received; Interrupt Flag: UCRXIFG0
    static const uint32_t UCBxIV_UCIV__UCIV_22 = 22;
    // Interrupt Source: Transmit buffer empty; Interrupt Flag: UCTXIFG0
    static const uint32_t UCBxIV_UCIV__UCIV_24 = 24;
    // Interrupt Source: Byte counter zero; Interrupt Flag: UCBCNTIFG
    static const uint32_t UCBxIV_UCIV__UCIV_26 = 26;
    // Interrupt Source: Clock low timeout; Interrupt Flag: UCCLTOIFG
    static const uint32_t UCBxIV_UCIV__UCIV_28 = 28;
    // Interrupt Source: Nineth bit position; Interrupt Flag: UCBIT9IFG; Priority: Lowest
    static const uint32_t UCBxIV_UCIV__UCIV_30 = 30;

    struct EUSCI_B3_t {
        UCBxCTLW0_t                   UCBxCTLW0;
        UCBxCTLW1_t                   UCBxCTLW1;
        uint16_t                      reserved0;
        UCBxBRW_t                     UCBxBRW;
        UCBxSTATW_t                   UCBxSTATW;
        UCBxTBCNT_t                   UCBxTBCNT;
        UCBxRXBUF_t                   UCBxRXBUF;
        UCBxTXBUF_t                   UCBxTXBUF;
        uint16_t                      reserved1[2];
        UCBxI2COA0_t                  UCBxI2COA0;
        UCBxI2COA1_t                  UCBxI2COA1;
        UCBxI2COA2_t                  UCBxI2COA2;
        UCBxI2COA3_t                  UCBxI2COA3;
        UCBxADDRX_t                   UCBxADDRX;
        UCBxADDMASK_t                 UCBxADDMASK;
        UCBxI2CSA_t                   UCBxI2CSA;
        uint16_t                      reserved2[4];
        UCBxIE_t                      UCBxIE;
        UCBxIFG_t                     UCBxIFG;
        UCBxIV_t                      UCBxIV;
    };

    static EUSCI_B3_t & EUSCI_B3     = (*(EUSCI_B3_t *)0x40002c00);

} // _EUSCI_B3_

// REF_A
namespace _REF_A_  {

    // REF Control Register 0
    BEGIN_TYPE(REFCTL0_t, uint16_t)
        // Reference enable
        ADD_BITFIELD_RW(REFON, 0, 1)
        // Reference output buffer
        ADD_BITFIELD_RW(REFOUT, 1, 1)
        // Temperature sensor disabled
        ADD_BITFIELD_RW(REFTCOFF, 3, 1)
        // Reference voltage level select
        ADD_BITFIELD_RW(REFVSEL, 4, 2)
        // Reference generator one-time trigger
        ADD_BITFIELD_RW(REFGENOT, 6, 1)
        // Bandgap and bandgap buffer one-time trigger
        ADD_BITFIELD_RW(REFBGOT, 7, 1)
        // Reference generator active
        ADD_BITFIELD_RO(REFGENACT, 8, 1)
        // Reference bandgap active
        ADD_BITFIELD_RO(REFBGACT, 9, 1)
        // Reference generator busy
        ADD_BITFIELD_RO(REFGENBUSY, 10, 1)
        // Bandgap mode
        ADD_BITFIELD_RO(BGMODE, 11, 1)
        // Variable reference voltage ready status
        ADD_BITFIELD_RO(REFGENRDY, 12, 1)
        // Buffered bandgap voltage ready status
        ADD_BITFIELD_RO(REFBGRDY, 13, 1)
    END_TYPE()

    // Disables reference if no other reference requests are pending
    static const uint32_t REFCTL0_REFON__REFON_0 = 0;
    // Enables reference in static mode
    static const uint32_t REFCTL0_REFON__REFON_1 = 1;
    // Reference output not available externally
    static const uint32_t REFCTL0_REFOUT__REFOUT_0 = 0;
    // Reference output available externally. If ADC14REFBURST = 0, output is available continuously. If ADC14REFBURST = 1, output is available only during an ADC14 conversion.
    static const uint32_t REFCTL0_REFOUT__REFOUT_1 = 1;
    // Temperature sensor enabled
    static const uint32_t REFCTL0_REFTCOFF__REFTCOFF_0 = 0;
    // Temperature sensor disabled to save power
    static const uint32_t REFCTL0_REFTCOFF__REFTCOFF_1 = 1;
    // 1.2 V available when reference requested or REFON = 1
    static const uint32_t REFCTL0_REFVSEL__REFVSEL_0 = 0;
    // 1.45 V available when reference requested or REFON = 1
    static const uint32_t REFCTL0_REFVSEL__REFVSEL_1 = 1;
    // 2.5 V available when reference requested or REFON = 1
    static const uint32_t REFCTL0_REFVSEL__REFVSEL_3 = 3;
    // No trigger
    static const uint32_t REFCTL0_REFGENOT__REFGENOT_0 = 0;
    // Generation of the reference voltage is started by writing 1 or by a hardware trigger
    static const uint32_t REFCTL0_REFGENOT__REFGENOT_1 = 1;
    // No trigger
    static const uint32_t REFCTL0_REFBGOT__REFBGOT_0 = 0;
    // Generation of the bandgap voltage is started by writing 1 or by a hardware trigger
    static const uint32_t REFCTL0_REFBGOT__REFBGOT_1 = 1;
    // Reference generator not active
    static const uint32_t REFCTL0_REFGENACT__REFGENACT_0 = 0;
    // Reference generator active
    static const uint32_t REFCTL0_REFGENACT__REFGENACT_1 = 1;
    // Reference bandgap buffer not active
    static const uint32_t REFCTL0_REFBGACT__REFBGACT_0 = 0;
    // Reference bandgap buffer active
    static const uint32_t REFCTL0_REFBGACT__REFBGACT_1 = 1;
    // Reference generator not busy
    static const uint32_t REFCTL0_REFGENBUSY__REFGENBUSY_0 = 0;
    // Reference generator busy
    static const uint32_t REFCTL0_REFGENBUSY__REFGENBUSY_1 = 1;
    // Static mode
    static const uint32_t REFCTL0_BGMODE__BGMODE_0 = 0;
    // Sampled mode
    static const uint32_t REFCTL0_BGMODE__BGMODE_1 = 1;
    // Reference voltage output is not ready to be used
    static const uint32_t REFCTL0_REFGENRDY__REFGENRDY_0 = 0;
    // Reference voltage output is ready to be used
    static const uint32_t REFCTL0_REFGENRDY__REFGENRDY_1 = 1;
    // Buffered bandgap voltage is not ready to be used
    static const uint32_t REFCTL0_REFBGRDY__REFBGRDY_0 = 0;
    // Buffered bandgap voltage is ready to be used
    static const uint32_t REFCTL0_REFBGRDY__REFBGRDY_1 = 1;

    struct REF_A_t {
        REFCTL0_t                     REFCTL0;
    };

    static REF_A_t & REF_A     = (*(REF_A_t *)0x40003000);

} // _REF_A_

// COMP_E0
namespace _COMP_E0_  {

    // Comparator Control Register 0
    // Reset value: 0x00000000
    BEGIN_TYPE(CExCTL0_t, uint16_t)
        // Channel input selected for the V+ terminal
        ADD_BITFIELD_RW(CEIPSEL, 0, 4)
        // Channel input enable for the V+ terminal
        ADD_BITFIELD_RW(CEIPEN, 7, 1)
        // Channel input selected for the - terminal
        ADD_BITFIELD_RW(CEIMSEL, 8, 4)
        // Channel input enable for the - terminal
        ADD_BITFIELD_RW(CEIMEN, 15, 1)
    END_TYPE()

    // Channel 0 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_0 = 0;
    // Channel 1 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_1 = 1;
    // Channel 2 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_2 = 2;
    // Channel 3 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_3 = 3;
    // Channel 4 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_4 = 4;
    // Channel 5 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_5 = 5;
    // Channel 6 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_6 = 6;
    // Channel 7 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_7 = 7;
    // Channel 8 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_8 = 8;
    // Channel 9 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_9 = 9;
    // Channel 10 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_10 = 10;
    // Channel 11 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_11 = 11;
    // Channel 12 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_12 = 12;
    // Channel 13 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_13 = 13;
    // Channel 14 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_14 = 14;
    // Channel 15 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_15 = 15;
    // Selected analog input channel for V+ terminal is disabled
    static const uint32_t CExCTL0_CEIPEN__CEIPEN_0 = 0;
    // Selected analog input channel for V+ terminal is enabled
    static const uint32_t CExCTL0_CEIPEN__CEIPEN_1 = 1;
    // Channel 0 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_0 = 0;
    // Channel 1 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_1 = 1;
    // Channel 2 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_2 = 2;
    // Channel 3 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_3 = 3;
    // Channel 4 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_4 = 4;
    // Channel 5 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_5 = 5;
    // Channel 6 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_6 = 6;
    // Channel 7 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_7 = 7;
    // Channel 8 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_8 = 8;
    // Channel 9 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_9 = 9;
    // Channel 10 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_10 = 10;
    // Channel 11 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_11 = 11;
    // Channel 12 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_12 = 12;
    // Channel 13 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_13 = 13;
    // Channel 14 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_14 = 14;
    // Channel 15 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_15 = 15;
    // Selected analog input channel for V- terminal is disabled
    static const uint32_t CExCTL0_CEIMEN__CEIMEN_0 = 0;
    // Selected analog input channel for V- terminal is enabled
    static const uint32_t CExCTL0_CEIMEN__CEIMEN_1 = 1;

    // Comparator Control Register 1
    // Reset value: 0x00000000
    BEGIN_TYPE(CExCTL1_t, uint16_t)
        // Comparator output value
        ADD_BITFIELD_RW(CEOUT, 0, 1)
        // Comparator output polarity
        ADD_BITFIELD_RW(CEOUTPOL, 1, 1)
        // Comparator output filter
        ADD_BITFIELD_RW(CEF, 2, 1)
        // Interrupt edge select for CEIIFG and CEIFG
        ADD_BITFIELD_RW(CEIES, 3, 1)
        // Input short
        ADD_BITFIELD_RW(CESHORT, 4, 1)
        // Exchange
        ADD_BITFIELD_RW(CEEX, 5, 1)
        // Filter delay
        ADD_BITFIELD_RW(CEFDLY, 6, 2)
        // Power Mode
        ADD_BITFIELD_RW(CEPWRMD, 8, 2)
        // Comparator On
        ADD_BITFIELD_RW(CEON, 10, 1)
        // This bit is valid of CEMRVS is set to 1
        ADD_BITFIELD_RW(CEMRVL, 11, 1)
        // This bit defines if the comparator output selects between VREF0 or VREF1 if CERS = 00, 01, or 10.
        ADD_BITFIELD_RW(CEMRVS, 12, 1)
    END_TYPE()

    // Noninverted
    static const uint32_t CExCTL1_CEOUTPOL__CEOUTPOL_0 = 0;
    // Inverted
    static const uint32_t CExCTL1_CEOUTPOL__CEOUTPOL_1 = 1;
    // Comparator output is not filtered
    static const uint32_t CExCTL1_CEF__CEF_0 = 0;
    // Comparator output is filtered
    static const uint32_t CExCTL1_CEF__CEF_1 = 1;
    // Rising edge for CEIFG, falling edge for CEIIFG
    static const uint32_t CExCTL1_CEIES__CEIES_0 = 0;
    // Falling edge for CEIFG, rising edge for CEIIFG
    static const uint32_t CExCTL1_CEIES__CEIES_1 = 1;
    // Inputs not shorted
    static const uint32_t CExCTL1_CESHORT__CESHORT_0 = 0;
    // Inputs shorted
    static const uint32_t CExCTL1_CESHORT__CESHORT_1 = 1;
    // Typical filter delay of TBD (450) ns
    static const uint32_t CExCTL1_CEFDLY__CEFDLY_0 = 0;
    // Typical filter delay of TBD (900) ns
    static const uint32_t CExCTL1_CEFDLY__CEFDLY_1 = 1;
    // Typical filter delay of TBD (1800) ns
    static const uint32_t CExCTL1_CEFDLY__CEFDLY_2 = 2;
    // Typical filter delay of TBD (3600) ns
    static const uint32_t CExCTL1_CEFDLY__CEFDLY_3 = 3;
    // High-speed mode
    static const uint32_t CExCTL1_CEPWRMD__CEPWRMD_0 = 0;
    // Normal mode
    static const uint32_t CExCTL1_CEPWRMD__CEPWRMD_1 = 1;
    // Ultra-low power mode
    static const uint32_t CExCTL1_CEPWRMD__CEPWRMD_2 = 2;
    // Off
    static const uint32_t CExCTL1_CEON__CEON_0 = 0;
    // On
    static const uint32_t CExCTL1_CEON__CEON_1 = 1;
    // VREF0 is selected if CERS = 00, 01, or 10
    static const uint32_t CExCTL1_CEMRVL__CEMRVL_0 = 0;
    // VREF1 is selected if CERS = 00, 01, or 10
    static const uint32_t CExCTL1_CEMRVL__CEMRVL_1 = 1;
    // Comparator output state selects between VREF0 or VREF1
    static const uint32_t CExCTL1_CEMRVS__CEMRVS_0 = 0;
    // CEMRVL selects between VREF0 or VREF1
    static const uint32_t CExCTL1_CEMRVS__CEMRVS_1 = 1;

    // Comparator Control Register 2
    // Reset value: 0x00000000
    BEGIN_TYPE(CExCTL2_t, uint16_t)
        // Reference resistor tap 0
        ADD_BITFIELD_RW(CEREF0, 0, 5)
        // Reference select
        ADD_BITFIELD_RW(CERSEL, 5, 1)
        // Reference source
        ADD_BITFIELD_RW(CERS, 6, 2)
        // Reference resistor tap 1
        ADD_BITFIELD_RW(CEREF1, 8, 5)
        // Reference voltage level
        ADD_BITFIELD_RW(CEREFL, 13, 2)
        // Reference accuracy
        ADD_BITFIELD_RW(CEREFACC, 15, 1)
    END_TYPE()

    // Reference resistor tap for setting 0.
    static const uint32_t CExCTL2_CEREF0__CEREF0_0 = 0;
    // Reference resistor tap for setting 1.
    static const uint32_t CExCTL2_CEREF0__CEREF0_1 = 1;
    // Reference resistor tap for setting 2.
    static const uint32_t CExCTL2_CEREF0__CEREF0_2 = 2;
    // Reference resistor tap for setting 3.
    static const uint32_t CExCTL2_CEREF0__CEREF0_3 = 3;
    // Reference resistor tap for setting 4.
    static const uint32_t CExCTL2_CEREF0__CEREF0_4 = 4;
    // Reference resistor tap for setting 5.
    static const uint32_t CExCTL2_CEREF0__CEREF0_5 = 5;
    // Reference resistor tap for setting 6.
    static const uint32_t CExCTL2_CEREF0__CEREF0_6 = 6;
    // Reference resistor tap for setting 7.
    static const uint32_t CExCTL2_CEREF0__CEREF0_7 = 7;
    // Reference resistor tap for setting 8.
    static const uint32_t CExCTL2_CEREF0__CEREF0_8 = 8;
    // Reference resistor tap for setting 9.
    static const uint32_t CExCTL2_CEREF0__CEREF0_9 = 9;
    // Reference resistor tap for setting 10.
    static const uint32_t CExCTL2_CEREF0__CEREF0_10 = 10;
    // Reference resistor tap for setting 11.
    static const uint32_t CExCTL2_CEREF0__CEREF0_11 = 11;
    // Reference resistor tap for setting 12.
    static const uint32_t CExCTL2_CEREF0__CEREF0_12 = 12;
    // Reference resistor tap for setting 13.
    static const uint32_t CExCTL2_CEREF0__CEREF0_13 = 13;
    // Reference resistor tap for setting 14.
    static const uint32_t CExCTL2_CEREF0__CEREF0_14 = 14;
    // Reference resistor tap for setting 15.
    static const uint32_t CExCTL2_CEREF0__CEREF0_15 = 15;
    // Reference resistor tap for setting 16.
    static const uint32_t CExCTL2_CEREF0__CEREF0_16 = 16;
    // Reference resistor tap for setting 17.
    static const uint32_t CExCTL2_CEREF0__CEREF0_17 = 17;
    // Reference resistor tap for setting 18.
    static const uint32_t CExCTL2_CEREF0__CEREF0_18 = 18;
    // Reference resistor tap for setting 19.
    static const uint32_t CExCTL2_CEREF0__CEREF0_19 = 19;
    // Reference resistor tap for setting 20.
    static const uint32_t CExCTL2_CEREF0__CEREF0_20 = 20;
    // Reference resistor tap for setting 21.
    static const uint32_t CExCTL2_CEREF0__CEREF0_21 = 21;
    // Reference resistor tap for setting 22.
    static const uint32_t CExCTL2_CEREF0__CEREF0_22 = 22;
    // Reference resistor tap for setting 23.
    static const uint32_t CExCTL2_CEREF0__CEREF0_23 = 23;
    // Reference resistor tap for setting 24.
    static const uint32_t CExCTL2_CEREF0__CEREF0_24 = 24;
    // Reference resistor tap for setting 25.
    static const uint32_t CExCTL2_CEREF0__CEREF0_25 = 25;
    // Reference resistor tap for setting 26.
    static const uint32_t CExCTL2_CEREF0__CEREF0_26 = 26;
    // Reference resistor tap for setting 27.
    static const uint32_t CExCTL2_CEREF0__CEREF0_27 = 27;
    // Reference resistor tap for setting 28.
    static const uint32_t CExCTL2_CEREF0__CEREF0_28 = 28;
    // Reference resistor tap for setting 29.
    static const uint32_t CExCTL2_CEREF0__CEREF0_29 = 29;
    // Reference resistor tap for setting 30.
    static const uint32_t CExCTL2_CEREF0__CEREF0_30 = 30;
    // Reference resistor tap for setting 31.
    static const uint32_t CExCTL2_CEREF0__CEREF0_31 = 31;
    // When CEEX = 0, VREF is applied to the V+ terminal; When CEEX = 1, VREF is applied to the V- terminal
    static const uint32_t CExCTL2_CERSEL__CERSEL_0 = 0;
    // When CEEX = 0, VREF is applied to the V- terminal; When CEEX = 1, VREF is applied to the V+ terminal
    static const uint32_t CExCTL2_CERSEL__CERSEL_1 = 1;
    // No current is drawn by the reference circuitry
    static const uint32_t CExCTL2_CERS__CERS_0 = 0;
    // VCC applied to the resistor ladder
    static const uint32_t CExCTL2_CERS__CERS_1 = 1;
    // Shared reference voltage applied to the resistor ladder
    static const uint32_t CExCTL2_CERS__CERS_2 = 2;
    // Shared reference voltage supplied to V(CREF). Resistor ladder is off
    static const uint32_t CExCTL2_CERS__CERS_3 = 3;
    // Reference resistor tap for setting 0.
    static const uint32_t CExCTL2_CEREF1__CEREF1_0 = 0;
    // Reference resistor tap for setting 1.
    static const uint32_t CExCTL2_CEREF1__CEREF1_1 = 1;
    // Reference resistor tap for setting 2.
    static const uint32_t CExCTL2_CEREF1__CEREF1_2 = 2;
    // Reference resistor tap for setting 3.
    static const uint32_t CExCTL2_CEREF1__CEREF1_3 = 3;
    // Reference resistor tap for setting 4.
    static const uint32_t CExCTL2_CEREF1__CEREF1_4 = 4;
    // Reference resistor tap for setting 5.
    static const uint32_t CExCTL2_CEREF1__CEREF1_5 = 5;
    // Reference resistor tap for setting 6.
    static const uint32_t CExCTL2_CEREF1__CEREF1_6 = 6;
    // Reference resistor tap for setting 7.
    static const uint32_t CExCTL2_CEREF1__CEREF1_7 = 7;
    // Reference resistor tap for setting 8.
    static const uint32_t CExCTL2_CEREF1__CEREF1_8 = 8;
    // Reference resistor tap for setting 9.
    static const uint32_t CExCTL2_CEREF1__CEREF1_9 = 9;
    // Reference resistor tap for setting 10.
    static const uint32_t CExCTL2_CEREF1__CEREF1_10 = 10;
    // Reference resistor tap for setting 11.
    static const uint32_t CExCTL2_CEREF1__CEREF1_11 = 11;
    // Reference resistor tap for setting 12.
    static const uint32_t CExCTL2_CEREF1__CEREF1_12 = 12;
    // Reference resistor tap for setting 13.
    static const uint32_t CExCTL2_CEREF1__CEREF1_13 = 13;
    // Reference resistor tap for setting 14.
    static const uint32_t CExCTL2_CEREF1__CEREF1_14 = 14;
    // Reference resistor tap for setting 15.
    static const uint32_t CExCTL2_CEREF1__CEREF1_15 = 15;
    // Reference resistor tap for setting 16.
    static const uint32_t CExCTL2_CEREF1__CEREF1_16 = 16;
    // Reference resistor tap for setting 17.
    static const uint32_t CExCTL2_CEREF1__CEREF1_17 = 17;
    // Reference resistor tap for setting 18.
    static const uint32_t CExCTL2_CEREF1__CEREF1_18 = 18;
    // Reference resistor tap for setting 19.
    static const uint32_t CExCTL2_CEREF1__CEREF1_19 = 19;
    // Reference resistor tap for setting 20.
    static const uint32_t CExCTL2_CEREF1__CEREF1_20 = 20;
    // Reference resistor tap for setting 21.
    static const uint32_t CExCTL2_CEREF1__CEREF1_21 = 21;
    // Reference resistor tap for setting 22.
    static const uint32_t CExCTL2_CEREF1__CEREF1_22 = 22;
    // Reference resistor tap for setting 23.
    static const uint32_t CExCTL2_CEREF1__CEREF1_23 = 23;
    // Reference resistor tap for setting 24.
    static const uint32_t CExCTL2_CEREF1__CEREF1_24 = 24;
    // Reference resistor tap for setting 25.
    static const uint32_t CExCTL2_CEREF1__CEREF1_25 = 25;
    // Reference resistor tap for setting 26.
    static const uint32_t CExCTL2_CEREF1__CEREF1_26 = 26;
    // Reference resistor tap for setting 27.
    static const uint32_t CExCTL2_CEREF1__CEREF1_27 = 27;
    // Reference resistor tap for setting 28.
    static const uint32_t CExCTL2_CEREF1__CEREF1_28 = 28;
    // Reference resistor tap for setting 29.
    static const uint32_t CExCTL2_CEREF1__CEREF1_29 = 29;
    // Reference resistor tap for setting 30.
    static const uint32_t CExCTL2_CEREF1__CEREF1_30 = 30;
    // Reference resistor tap for setting 31.
    static const uint32_t CExCTL2_CEREF1__CEREF1_31 = 31;
    // Reference amplifier is disabled. No reference voltage is requested
    static const uint32_t CExCTL2_CEREFL__CEREFL_0 = 0;
    // 1.2 V is selected as shared reference voltage input
    static const uint32_t CExCTL2_CEREFL__CEREFL_1 = 1;
    // 2.0 V is selected as shared reference voltage input
    static const uint32_t CExCTL2_CEREFL__CEREFL_2 = 2;
    // 2.5 V is selected as shared reference voltage input
    static const uint32_t CExCTL2_CEREFL__CEREFL_3 = 3;
    // Static mode
    static const uint32_t CExCTL2_CEREFACC__CEREFACC_0 = 0;
    // Clocked (low power, low accuracy) mode
    static const uint32_t CExCTL2_CEREFACC__CEREFACC_1 = 1;

    // Comparator Control Register 3
    // Reset value: 0x00000000
    BEGIN_TYPE(CExCTL3_t, uint16_t)
        // Port disable
        ADD_BITFIELD_RW(CEPD0, 0, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD1, 1, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD2, 2, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD3, 3, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD4, 4, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD5, 5, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD6, 6, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD7, 7, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD8, 8, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD9, 9, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD10, 10, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD11, 11, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD12, 12, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD13, 13, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD14, 14, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD15, 15, 1)
    END_TYPE()

    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD0__CEPD0_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD0__CEPD0_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD1__CEPD1_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD1__CEPD1_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD2__CEPD2_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD2__CEPD2_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD3__CEPD3_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD3__CEPD3_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD4__CEPD4_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD4__CEPD4_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD5__CEPD5_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD5__CEPD5_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD6__CEPD6_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD6__CEPD6_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD7__CEPD7_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD7__CEPD7_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD8__CEPD8_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD8__CEPD8_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD9__CEPD9_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD9__CEPD9_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD10__CEPD10_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD10__CEPD10_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD11__CEPD11_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD11__CEPD11_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD12__CEPD12_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD12__CEPD12_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD13__CEPD13_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD13__CEPD13_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD14__CEPD14_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD14__CEPD14_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD15__CEPD15_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD15__CEPD15_1 = 1;

    // Comparator Interrupt Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(CExINT_t, uint16_t)
        // Comparator output interrupt flag
        ADD_BITFIELD_RW(CEIFG, 0, 1)
        // Comparator output inverted interrupt flag
        ADD_BITFIELD_RW(CEIIFG, 1, 1)
        // Comparator ready interrupt flag
        ADD_BITFIELD_RW(CERDYIFG, 4, 1)
        // Comparator output interrupt enable
        ADD_BITFIELD_RW(CEIE, 8, 1)
        // Comparator output interrupt enable inverted polarity
        ADD_BITFIELD_RW(CEIIE, 9, 1)
        // Comparator ready interrupt enable
        ADD_BITFIELD_RW(CERDYIE, 12, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t CExINT_CEIFG__CEIFG_0 = 0;
    // Interrupt pending
    static const uint32_t CExINT_CEIFG__CEIFG_1 = 1;
    // No interrupt pending
    static const uint32_t CExINT_CEIIFG__CEIIFG_0 = 0;
    // Interrupt pending
    static const uint32_t CExINT_CEIIFG__CEIIFG_1 = 1;
    // No interrupt pending
    static const uint32_t CExINT_CERDYIFG__CERDYIFG_0 = 0;
    // Interrupt pending
    static const uint32_t CExINT_CERDYIFG__CERDYIFG_1 = 1;
    // Interrupt disabled
    static const uint32_t CExINT_CEIE__CEIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CExINT_CEIE__CEIE_1 = 1;
    // Interrupt disabled
    static const uint32_t CExINT_CEIIE__CEIIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CExINT_CEIIE__CEIIE_1 = 1;
    // Interrupt disabled
    static const uint32_t CExINT_CERDYIE__CERDYIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CExINT_CERDYIE__CERDYIE_1 = 1;

    // Comparator Interrupt Vector Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(CExIV_t, uint16_t)
        // Comparator interrupt vector word register
        ADD_BITFIELD_RO(CEIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t CExIV_CEIV__CEIV_0 = 0;
    // Interrupt Source: CEOUT interrupt; Interrupt Flag: CEIFG; Interrupt Priority: Highest
    static const uint32_t CExIV_CEIV__CEIV_2 = 2;
    // Interrupt Source: CEOUT interrupt inverted polarity; Interrupt Flag: CEIIFG
    static const uint32_t CExIV_CEIV__CEIV_4 = 4;
    // Interrupt Source: Comparator ready interrupt; Interrupt Flag: CERDYIFG; Interrupt Priority: Lowest
    static const uint32_t CExIV_CEIV__CEIV_10 = 10;

    struct COMP_E0_t {
        CExCTL0_t                     CExCTL0;
        CExCTL1_t                     CExCTL1;
        CExCTL2_t                     CExCTL2;
        CExCTL3_t                     CExCTL3;
        uint16_t                      reserved0[2];
        CExINT_t                      CExINT;
        CExIV_t                       CExIV;
    };

    static COMP_E0_t & COMP_E0     = (*(COMP_E0_t *)0x40003400);

} // _COMP_E0_

// COMP_E1
namespace _COMP_E1_  {

    // Comparator Control Register 0
    // Reset value: 0x00000000
    BEGIN_TYPE(CExCTL0_t, uint16_t)
        // Channel input selected for the V+ terminal
        ADD_BITFIELD_RW(CEIPSEL, 0, 4)
        // Channel input enable for the V+ terminal
        ADD_BITFIELD_RW(CEIPEN, 7, 1)
        // Channel input selected for the - terminal
        ADD_BITFIELD_RW(CEIMSEL, 8, 4)
        // Channel input enable for the - terminal
        ADD_BITFIELD_RW(CEIMEN, 15, 1)
    END_TYPE()

    // Channel 0 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_0 = 0;
    // Channel 1 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_1 = 1;
    // Channel 2 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_2 = 2;
    // Channel 3 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_3 = 3;
    // Channel 4 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_4 = 4;
    // Channel 5 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_5 = 5;
    // Channel 6 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_6 = 6;
    // Channel 7 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_7 = 7;
    // Channel 8 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_8 = 8;
    // Channel 9 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_9 = 9;
    // Channel 10 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_10 = 10;
    // Channel 11 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_11 = 11;
    // Channel 12 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_12 = 12;
    // Channel 13 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_13 = 13;
    // Channel 14 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_14 = 14;
    // Channel 15 selected
    static const uint32_t CExCTL0_CEIPSEL__CEIPSEL_15 = 15;
    // Selected analog input channel for V+ terminal is disabled
    static const uint32_t CExCTL0_CEIPEN__CEIPEN_0 = 0;
    // Selected analog input channel for V+ terminal is enabled
    static const uint32_t CExCTL0_CEIPEN__CEIPEN_1 = 1;
    // Channel 0 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_0 = 0;
    // Channel 1 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_1 = 1;
    // Channel 2 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_2 = 2;
    // Channel 3 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_3 = 3;
    // Channel 4 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_4 = 4;
    // Channel 5 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_5 = 5;
    // Channel 6 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_6 = 6;
    // Channel 7 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_7 = 7;
    // Channel 8 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_8 = 8;
    // Channel 9 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_9 = 9;
    // Channel 10 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_10 = 10;
    // Channel 11 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_11 = 11;
    // Channel 12 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_12 = 12;
    // Channel 13 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_13 = 13;
    // Channel 14 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_14 = 14;
    // Channel 15 selected
    static const uint32_t CExCTL0_CEIMSEL__CEIMSEL_15 = 15;
    // Selected analog input channel for V- terminal is disabled
    static const uint32_t CExCTL0_CEIMEN__CEIMEN_0 = 0;
    // Selected analog input channel for V- terminal is enabled
    static const uint32_t CExCTL0_CEIMEN__CEIMEN_1 = 1;

    // Comparator Control Register 1
    // Reset value: 0x00000000
    BEGIN_TYPE(CExCTL1_t, uint16_t)
        // Comparator output value
        ADD_BITFIELD_RW(CEOUT, 0, 1)
        // Comparator output polarity
        ADD_BITFIELD_RW(CEOUTPOL, 1, 1)
        // Comparator output filter
        ADD_BITFIELD_RW(CEF, 2, 1)
        // Interrupt edge select for CEIIFG and CEIFG
        ADD_BITFIELD_RW(CEIES, 3, 1)
        // Input short
        ADD_BITFIELD_RW(CESHORT, 4, 1)
        // Exchange
        ADD_BITFIELD_RW(CEEX, 5, 1)
        // Filter delay
        ADD_BITFIELD_RW(CEFDLY, 6, 2)
        // Power Mode
        ADD_BITFIELD_RW(CEPWRMD, 8, 2)
        // Comparator On
        ADD_BITFIELD_RW(CEON, 10, 1)
        // This bit is valid of CEMRVS is set to 1
        ADD_BITFIELD_RW(CEMRVL, 11, 1)
        // This bit defines if the comparator output selects between VREF0 or VREF1 if CERS = 00, 01, or 10.
        ADD_BITFIELD_RW(CEMRVS, 12, 1)
    END_TYPE()

    // Noninverted
    static const uint32_t CExCTL1_CEOUTPOL__CEOUTPOL_0 = 0;
    // Inverted
    static const uint32_t CExCTL1_CEOUTPOL__CEOUTPOL_1 = 1;
    // Comparator output is not filtered
    static const uint32_t CExCTL1_CEF__CEF_0 = 0;
    // Comparator output is filtered
    static const uint32_t CExCTL1_CEF__CEF_1 = 1;
    // Rising edge for CEIFG, falling edge for CEIIFG
    static const uint32_t CExCTL1_CEIES__CEIES_0 = 0;
    // Falling edge for CEIFG, rising edge for CEIIFG
    static const uint32_t CExCTL1_CEIES__CEIES_1 = 1;
    // Inputs not shorted
    static const uint32_t CExCTL1_CESHORT__CESHORT_0 = 0;
    // Inputs shorted
    static const uint32_t CExCTL1_CESHORT__CESHORT_1 = 1;
    // Typical filter delay of TBD (450) ns
    static const uint32_t CExCTL1_CEFDLY__CEFDLY_0 = 0;
    // Typical filter delay of TBD (900) ns
    static const uint32_t CExCTL1_CEFDLY__CEFDLY_1 = 1;
    // Typical filter delay of TBD (1800) ns
    static const uint32_t CExCTL1_CEFDLY__CEFDLY_2 = 2;
    // Typical filter delay of TBD (3600) ns
    static const uint32_t CExCTL1_CEFDLY__CEFDLY_3 = 3;
    // High-speed mode
    static const uint32_t CExCTL1_CEPWRMD__CEPWRMD_0 = 0;
    // Normal mode
    static const uint32_t CExCTL1_CEPWRMD__CEPWRMD_1 = 1;
    // Ultra-low power mode
    static const uint32_t CExCTL1_CEPWRMD__CEPWRMD_2 = 2;
    // Off
    static const uint32_t CExCTL1_CEON__CEON_0 = 0;
    // On
    static const uint32_t CExCTL1_CEON__CEON_1 = 1;
    // VREF0 is selected if CERS = 00, 01, or 10
    static const uint32_t CExCTL1_CEMRVL__CEMRVL_0 = 0;
    // VREF1 is selected if CERS = 00, 01, or 10
    static const uint32_t CExCTL1_CEMRVL__CEMRVL_1 = 1;
    // Comparator output state selects between VREF0 or VREF1
    static const uint32_t CExCTL1_CEMRVS__CEMRVS_0 = 0;
    // CEMRVL selects between VREF0 or VREF1
    static const uint32_t CExCTL1_CEMRVS__CEMRVS_1 = 1;

    // Comparator Control Register 2
    // Reset value: 0x00000000
    BEGIN_TYPE(CExCTL2_t, uint16_t)
        // Reference resistor tap 0
        ADD_BITFIELD_RW(CEREF0, 0, 5)
        // Reference select
        ADD_BITFIELD_RW(CERSEL, 5, 1)
        // Reference source
        ADD_BITFIELD_RW(CERS, 6, 2)
        // Reference resistor tap 1
        ADD_BITFIELD_RW(CEREF1, 8, 5)
        // Reference voltage level
        ADD_BITFIELD_RW(CEREFL, 13, 2)
        // Reference accuracy
        ADD_BITFIELD_RW(CEREFACC, 15, 1)
    END_TYPE()

    // Reference resistor tap for setting 0.
    static const uint32_t CExCTL2_CEREF0__CEREF0_0 = 0;
    // Reference resistor tap for setting 1.
    static const uint32_t CExCTL2_CEREF0__CEREF0_1 = 1;
    // Reference resistor tap for setting 2.
    static const uint32_t CExCTL2_CEREF0__CEREF0_2 = 2;
    // Reference resistor tap for setting 3.
    static const uint32_t CExCTL2_CEREF0__CEREF0_3 = 3;
    // Reference resistor tap for setting 4.
    static const uint32_t CExCTL2_CEREF0__CEREF0_4 = 4;
    // Reference resistor tap for setting 5.
    static const uint32_t CExCTL2_CEREF0__CEREF0_5 = 5;
    // Reference resistor tap for setting 6.
    static const uint32_t CExCTL2_CEREF0__CEREF0_6 = 6;
    // Reference resistor tap for setting 7.
    static const uint32_t CExCTL2_CEREF0__CEREF0_7 = 7;
    // Reference resistor tap for setting 8.
    static const uint32_t CExCTL2_CEREF0__CEREF0_8 = 8;
    // Reference resistor tap for setting 9.
    static const uint32_t CExCTL2_CEREF0__CEREF0_9 = 9;
    // Reference resistor tap for setting 10.
    static const uint32_t CExCTL2_CEREF0__CEREF0_10 = 10;
    // Reference resistor tap for setting 11.
    static const uint32_t CExCTL2_CEREF0__CEREF0_11 = 11;
    // Reference resistor tap for setting 12.
    static const uint32_t CExCTL2_CEREF0__CEREF0_12 = 12;
    // Reference resistor tap for setting 13.
    static const uint32_t CExCTL2_CEREF0__CEREF0_13 = 13;
    // Reference resistor tap for setting 14.
    static const uint32_t CExCTL2_CEREF0__CEREF0_14 = 14;
    // Reference resistor tap for setting 15.
    static const uint32_t CExCTL2_CEREF0__CEREF0_15 = 15;
    // Reference resistor tap for setting 16.
    static const uint32_t CExCTL2_CEREF0__CEREF0_16 = 16;
    // Reference resistor tap for setting 17.
    static const uint32_t CExCTL2_CEREF0__CEREF0_17 = 17;
    // Reference resistor tap for setting 18.
    static const uint32_t CExCTL2_CEREF0__CEREF0_18 = 18;
    // Reference resistor tap for setting 19.
    static const uint32_t CExCTL2_CEREF0__CEREF0_19 = 19;
    // Reference resistor tap for setting 20.
    static const uint32_t CExCTL2_CEREF0__CEREF0_20 = 20;
    // Reference resistor tap for setting 21.
    static const uint32_t CExCTL2_CEREF0__CEREF0_21 = 21;
    // Reference resistor tap for setting 22.
    static const uint32_t CExCTL2_CEREF0__CEREF0_22 = 22;
    // Reference resistor tap for setting 23.
    static const uint32_t CExCTL2_CEREF0__CEREF0_23 = 23;
    // Reference resistor tap for setting 24.
    static const uint32_t CExCTL2_CEREF0__CEREF0_24 = 24;
    // Reference resistor tap for setting 25.
    static const uint32_t CExCTL2_CEREF0__CEREF0_25 = 25;
    // Reference resistor tap for setting 26.
    static const uint32_t CExCTL2_CEREF0__CEREF0_26 = 26;
    // Reference resistor tap for setting 27.
    static const uint32_t CExCTL2_CEREF0__CEREF0_27 = 27;
    // Reference resistor tap for setting 28.
    static const uint32_t CExCTL2_CEREF0__CEREF0_28 = 28;
    // Reference resistor tap for setting 29.
    static const uint32_t CExCTL2_CEREF0__CEREF0_29 = 29;
    // Reference resistor tap for setting 30.
    static const uint32_t CExCTL2_CEREF0__CEREF0_30 = 30;
    // Reference resistor tap for setting 31.
    static const uint32_t CExCTL2_CEREF0__CEREF0_31 = 31;
    // When CEEX = 0, VREF is applied to the V+ terminal; When CEEX = 1, VREF is applied to the V- terminal
    static const uint32_t CExCTL2_CERSEL__CERSEL_0 = 0;
    // When CEEX = 0, VREF is applied to the V- terminal; When CEEX = 1, VREF is applied to the V+ terminal
    static const uint32_t CExCTL2_CERSEL__CERSEL_1 = 1;
    // No current is drawn by the reference circuitry
    static const uint32_t CExCTL2_CERS__CERS_0 = 0;
    // VCC applied to the resistor ladder
    static const uint32_t CExCTL2_CERS__CERS_1 = 1;
    // Shared reference voltage applied to the resistor ladder
    static const uint32_t CExCTL2_CERS__CERS_2 = 2;
    // Shared reference voltage supplied to V(CREF). Resistor ladder is off
    static const uint32_t CExCTL2_CERS__CERS_3 = 3;
    // Reference resistor tap for setting 0.
    static const uint32_t CExCTL2_CEREF1__CEREF1_0 = 0;
    // Reference resistor tap for setting 1.
    static const uint32_t CExCTL2_CEREF1__CEREF1_1 = 1;
    // Reference resistor tap for setting 2.
    static const uint32_t CExCTL2_CEREF1__CEREF1_2 = 2;
    // Reference resistor tap for setting 3.
    static const uint32_t CExCTL2_CEREF1__CEREF1_3 = 3;
    // Reference resistor tap for setting 4.
    static const uint32_t CExCTL2_CEREF1__CEREF1_4 = 4;
    // Reference resistor tap for setting 5.
    static const uint32_t CExCTL2_CEREF1__CEREF1_5 = 5;
    // Reference resistor tap for setting 6.
    static const uint32_t CExCTL2_CEREF1__CEREF1_6 = 6;
    // Reference resistor tap for setting 7.
    static const uint32_t CExCTL2_CEREF1__CEREF1_7 = 7;
    // Reference resistor tap for setting 8.
    static const uint32_t CExCTL2_CEREF1__CEREF1_8 = 8;
    // Reference resistor tap for setting 9.
    static const uint32_t CExCTL2_CEREF1__CEREF1_9 = 9;
    // Reference resistor tap for setting 10.
    static const uint32_t CExCTL2_CEREF1__CEREF1_10 = 10;
    // Reference resistor tap for setting 11.
    static const uint32_t CExCTL2_CEREF1__CEREF1_11 = 11;
    // Reference resistor tap for setting 12.
    static const uint32_t CExCTL2_CEREF1__CEREF1_12 = 12;
    // Reference resistor tap for setting 13.
    static const uint32_t CExCTL2_CEREF1__CEREF1_13 = 13;
    // Reference resistor tap for setting 14.
    static const uint32_t CExCTL2_CEREF1__CEREF1_14 = 14;
    // Reference resistor tap for setting 15.
    static const uint32_t CExCTL2_CEREF1__CEREF1_15 = 15;
    // Reference resistor tap for setting 16.
    static const uint32_t CExCTL2_CEREF1__CEREF1_16 = 16;
    // Reference resistor tap for setting 17.
    static const uint32_t CExCTL2_CEREF1__CEREF1_17 = 17;
    // Reference resistor tap for setting 18.
    static const uint32_t CExCTL2_CEREF1__CEREF1_18 = 18;
    // Reference resistor tap for setting 19.
    static const uint32_t CExCTL2_CEREF1__CEREF1_19 = 19;
    // Reference resistor tap for setting 20.
    static const uint32_t CExCTL2_CEREF1__CEREF1_20 = 20;
    // Reference resistor tap for setting 21.
    static const uint32_t CExCTL2_CEREF1__CEREF1_21 = 21;
    // Reference resistor tap for setting 22.
    static const uint32_t CExCTL2_CEREF1__CEREF1_22 = 22;
    // Reference resistor tap for setting 23.
    static const uint32_t CExCTL2_CEREF1__CEREF1_23 = 23;
    // Reference resistor tap for setting 24.
    static const uint32_t CExCTL2_CEREF1__CEREF1_24 = 24;
    // Reference resistor tap for setting 25.
    static const uint32_t CExCTL2_CEREF1__CEREF1_25 = 25;
    // Reference resistor tap for setting 26.
    static const uint32_t CExCTL2_CEREF1__CEREF1_26 = 26;
    // Reference resistor tap for setting 27.
    static const uint32_t CExCTL2_CEREF1__CEREF1_27 = 27;
    // Reference resistor tap for setting 28.
    static const uint32_t CExCTL2_CEREF1__CEREF1_28 = 28;
    // Reference resistor tap for setting 29.
    static const uint32_t CExCTL2_CEREF1__CEREF1_29 = 29;
    // Reference resistor tap for setting 30.
    static const uint32_t CExCTL2_CEREF1__CEREF1_30 = 30;
    // Reference resistor tap for setting 31.
    static const uint32_t CExCTL2_CEREF1__CEREF1_31 = 31;
    // Reference amplifier is disabled. No reference voltage is requested
    static const uint32_t CExCTL2_CEREFL__CEREFL_0 = 0;
    // 1.2 V is selected as shared reference voltage input
    static const uint32_t CExCTL2_CEREFL__CEREFL_1 = 1;
    // 2.0 V is selected as shared reference voltage input
    static const uint32_t CExCTL2_CEREFL__CEREFL_2 = 2;
    // 2.5 V is selected as shared reference voltage input
    static const uint32_t CExCTL2_CEREFL__CEREFL_3 = 3;
    // Static mode
    static const uint32_t CExCTL2_CEREFACC__CEREFACC_0 = 0;
    // Clocked (low power, low accuracy) mode
    static const uint32_t CExCTL2_CEREFACC__CEREFACC_1 = 1;

    // Comparator Control Register 3
    // Reset value: 0x00000000
    BEGIN_TYPE(CExCTL3_t, uint16_t)
        // Port disable
        ADD_BITFIELD_RW(CEPD0, 0, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD1, 1, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD2, 2, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD3, 3, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD4, 4, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD5, 5, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD6, 6, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD7, 7, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD8, 8, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD9, 9, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD10, 10, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD11, 11, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD12, 12, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD13, 13, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD14, 14, 1)
        // Port disable
        ADD_BITFIELD_RW(CEPD15, 15, 1)
    END_TYPE()

    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD0__CEPD0_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD0__CEPD0_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD1__CEPD1_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD1__CEPD1_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD2__CEPD2_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD2__CEPD2_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD3__CEPD3_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD3__CEPD3_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD4__CEPD4_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD4__CEPD4_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD5__CEPD5_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD5__CEPD5_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD6__CEPD6_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD6__CEPD6_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD7__CEPD7_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD7__CEPD7_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD8__CEPD8_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD8__CEPD8_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD9__CEPD9_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD9__CEPD9_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD10__CEPD10_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD10__CEPD10_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD11__CEPD11_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD11__CEPD11_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD12__CEPD12_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD12__CEPD12_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD13__CEPD13_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD13__CEPD13_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD14__CEPD14_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD14__CEPD14_1 = 1;
    // The input buffer is enabled
    static const uint32_t CExCTL3_CEPD15__CEPD15_0 = 0;
    // The input buffer is disabled
    static const uint32_t CExCTL3_CEPD15__CEPD15_1 = 1;

    // Comparator Interrupt Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(CExINT_t, uint16_t)
        // Comparator output interrupt flag
        ADD_BITFIELD_RW(CEIFG, 0, 1)
        // Comparator output inverted interrupt flag
        ADD_BITFIELD_RW(CEIIFG, 1, 1)
        // Comparator ready interrupt flag
        ADD_BITFIELD_RW(CERDYIFG, 4, 1)
        // Comparator output interrupt enable
        ADD_BITFIELD_RW(CEIE, 8, 1)
        // Comparator output interrupt enable inverted polarity
        ADD_BITFIELD_RW(CEIIE, 9, 1)
        // Comparator ready interrupt enable
        ADD_BITFIELD_RW(CERDYIE, 12, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t CExINT_CEIFG__CEIFG_0 = 0;
    // Interrupt pending
    static const uint32_t CExINT_CEIFG__CEIFG_1 = 1;
    // No interrupt pending
    static const uint32_t CExINT_CEIIFG__CEIIFG_0 = 0;
    // Interrupt pending
    static const uint32_t CExINT_CEIIFG__CEIIFG_1 = 1;
    // No interrupt pending
    static const uint32_t CExINT_CERDYIFG__CERDYIFG_0 = 0;
    // Interrupt pending
    static const uint32_t CExINT_CERDYIFG__CERDYIFG_1 = 1;
    // Interrupt disabled
    static const uint32_t CExINT_CEIE__CEIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CExINT_CEIE__CEIE_1 = 1;
    // Interrupt disabled
    static const uint32_t CExINT_CEIIE__CEIIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CExINT_CEIIE__CEIIE_1 = 1;
    // Interrupt disabled
    static const uint32_t CExINT_CERDYIE__CERDYIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CExINT_CERDYIE__CERDYIE_1 = 1;

    // Comparator Interrupt Vector Word Register
    // Reset value: 0x00000000
    BEGIN_TYPE(CExIV_t, uint16_t)
        // Comparator interrupt vector word register
        ADD_BITFIELD_RO(CEIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t CExIV_CEIV__CEIV_0 = 0;
    // Interrupt Source: CEOUT interrupt; Interrupt Flag: CEIFG; Interrupt Priority: Highest
    static const uint32_t CExIV_CEIV__CEIV_2 = 2;
    // Interrupt Source: CEOUT interrupt inverted polarity; Interrupt Flag: CEIIFG
    static const uint32_t CExIV_CEIV__CEIV_4 = 4;
    // Interrupt Source: Comparator ready interrupt; Interrupt Flag: CERDYIFG; Interrupt Priority: Lowest
    static const uint32_t CExIV_CEIV__CEIV_10 = 10;

    struct COMP_E1_t {
        CExCTL0_t                     CExCTL0;
        CExCTL1_t                     CExCTL1;
        CExCTL2_t                     CExCTL2;
        CExCTL3_t                     CExCTL3;
        uint16_t                      reserved0[2];
        CExINT_t                      CExINT;
        CExIV_t                       CExIV;
    };

    static COMP_E1_t & COMP_E1     = (*(COMP_E1_t *)0x40003800);

} // _COMP_E1_

// AES256
namespace _AES256_  {

    // AES Accelerator Control Register 0
    // Reset value: 0x00000000
    BEGIN_TYPE(AESACTL0_t, uint16_t)
        // AES operation
        ADD_BITFIELD_RW(AESOPx, 0, 2)
        // AES key length
        ADD_BITFIELD_RW(AESKLx, 2, 2)
        // AES cipher mode select
        ADD_BITFIELD_RW(AESCMx, 5, 2)
        // AES software reset
        ADD_BITFIELD_RW(AESSWRST, 7, 1)
        // AES ready interrupt flag
        ADD_BITFIELD_RW(AESRDYIFG, 8, 1)
        // AES error flag
        ADD_BITFIELD_RW(AESERRFG, 11, 1)
        // AES ready interrupt enable
        ADD_BITFIELD_RW(AESRDYIE, 12, 1)
        // AES cipher mode enable
        ADD_BITFIELD_RW(AESCMEN, 15, 1)
    END_TYPE()

    // Encryption
    static const uint32_t AESACTL0_AESOPx__AESOPx_0 = 0;
    // Decryption. The provided key is the same key used for encryption
    static const uint32_t AESACTL0_AESOPx__AESOPx_1 = 1;
    // Generate first round key required for decryption
    static const uint32_t AESACTL0_AESOPx__AESOPx_2 = 2;
    // Decryption. The provided key is the first round key required for decryption
    static const uint32_t AESACTL0_AESOPx__AESOPx_3 = 3;
    // AES128. The key size is 128 bit
    static const uint32_t AESACTL0_AESKLx__AESKLx_0 = 0;
    // AES192. The key size is 192 bit.
    static const uint32_t AESACTL0_AESKLx__AESKLx_1 = 1;
    // AES256. The key size is 256 bit
    static const uint32_t AESACTL0_AESKLx__AESKLx_2 = 2;
    // ECB
    static const uint32_t AESACTL0_AESCMx__AESCMx_0 = 0;
    // CBC
    static const uint32_t AESACTL0_AESCMx__AESCMx_1 = 1;
    // OFB
    static const uint32_t AESACTL0_AESCMx__AESCMx_2 = 2;
    // CFB
    static const uint32_t AESACTL0_AESCMx__AESCMx_3 = 3;
    // No reset
    static const uint32_t AESACTL0_AESSWRST__AESSWRST_0 = 0;
    // Reset AES accelerator module
    static const uint32_t AESACTL0_AESSWRST__AESSWRST_1 = 1;
    // No interrupt pending
    static const uint32_t AESACTL0_AESRDYIFG__AESRDYIFG_0 = 0;
    // Interrupt pending
    static const uint32_t AESACTL0_AESRDYIFG__AESRDYIFG_1 = 1;
    // No error
    static const uint32_t AESACTL0_AESERRFG__AESERRFG_0 = 0;
    // Error occurred
    static const uint32_t AESACTL0_AESERRFG__AESERRFG_1 = 1;
    // Interrupt disabled
    static const uint32_t AESACTL0_AESRDYIE__AESRDYIE_0 = 0;
    // Interrupt enabled
    static const uint32_t AESACTL0_AESRDYIE__AESRDYIE_1 = 1;
    // No DMA triggers are generated
    static const uint32_t AESACTL0_AESCMEN__AESCMEN_0 = 0;
    // DMA ciphermode support operation is enabled and the corresponding DMA triggers are generated
    static const uint32_t AESACTL0_AESCMEN__AESCMEN_1 = 1;

    // AES Accelerator Control Register 1
    // Reset value: 0x00000000
    BEGIN_TYPE(AESACTL1_t, uint16_t)
        // Cipher Block Counter
        ADD_BITFIELD_RW(AESBLKCNTx, 0, 8)
    END_TYPE()

    // AES Accelerator Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(AESASTAT_t, uint16_t)
        // AES accelerator module busy
        ADD_BITFIELD_RW(AESBUSY, 0, 1)
        // All 16 bytes written to AESAKEY
        ADD_BITFIELD_RW(AESKEYWR, 1, 1)
        // All 16 bytes written to AESADIN, AESAXDIN or AESAXIN
        ADD_BITFIELD_RW(AESDINWR, 2, 1)
        // All 16 bytes read from AESADOUT
        ADD_BITFIELD_RO(AESDOUTRD, 3, 1)
        // Bytes written via AESAKEY for AESKLx=00, half-words written via AESAKEY
        ADD_BITFIELD_RO(AESKEYCNTx, 4, 4)
        // Bytes written via AESADIN, AESAXDIN or AESAXIN
        ADD_BITFIELD_RO(AESDINCNTx, 8, 4)
        // Bytes read via AESADOUT
        ADD_BITFIELD_RO(AESDOUTCNTx, 12, 4)
    END_TYPE()

    // Not busy
    static const uint32_t AESASTAT_AESBUSY__AESBUSY_0 = 0;
    // Busy
    static const uint32_t AESASTAT_AESBUSY__AESBUSY_1 = 1;
    // Not all bytes written
    static const uint32_t AESASTAT_AESKEYWR__AESKEYWR_0 = 0;
    // All bytes written
    static const uint32_t AESASTAT_AESKEYWR__AESKEYWR_1 = 1;
    // Not all bytes written
    static const uint32_t AESASTAT_AESDINWR__AESDINWR_0 = 0;
    // All bytes written
    static const uint32_t AESASTAT_AESDINWR__AESDINWR_1 = 1;
    // Not all bytes read
    static const uint32_t AESASTAT_AESDOUTRD__AESDOUTRD_0 = 0;
    // All bytes read
    static const uint32_t AESASTAT_AESDOUTRD__AESDOUTRD_1 = 1;

    // AES Accelerator Key Register
    // Reset value: 0x00000000
    BEGIN_TYPE(AESAKEY_t, uint16_t)
        // AES key byte n when AESAKEY is written as half-word
        ADD_BITFIELD_WO(AESKEY0x, 0, 8)
        // AES key byte n+1 when AESAKEY is written as half-word
        ADD_BITFIELD_WO(AESKEY1x, 8, 8)
    END_TYPE()

    // AES Accelerator Data In Register
    // Reset value: 0x00000000
    BEGIN_TYPE(AESADIN_t, uint16_t)
        // AES data in byte n when AESADIN is written as half-word
        ADD_BITFIELD_WO(AESDIN0x, 0, 8)
        // AES data in byte n+1 when AESADIN is written as half-word
        ADD_BITFIELD_WO(AESDIN1x, 8, 8)
    END_TYPE()

    // AES Accelerator Data Out Register
    // Reset value: 0x00000000
    BEGIN_TYPE(AESADOUT_t, uint16_t)
        // AES data out byte n when AESADOUT is read as half-word
        ADD_BITFIELD_WO(AESDOUT0x, 0, 8)
        // AES data out byte n+1 when AESADOUT is read as half-word
        ADD_BITFIELD_WO(AESDOUT1x, 8, 8)
    END_TYPE()

    // AES Accelerator XORed Data In Register
    // Reset value: 0x00000000
    BEGIN_TYPE(AESAXDIN_t, uint16_t)
        // AES data in byte n when AESAXDIN is written as half-word
        ADD_BITFIELD_WO(AESXDIN0x, 0, 8)
        // AES data in byte n+1 when AESAXDIN is written as half-word
        ADD_BITFIELD_WO(AESXDIN1x, 8, 8)
    END_TYPE()

    // AES Accelerator XORed Data In Register
    // Reset value: 0x00000000
    BEGIN_TYPE(AESAXIN_t, uint16_t)
        // AES data in byte n when AESAXIN is written as half-word
        ADD_BITFIELD_WO(AESXIN0x, 0, 8)
        // AES data in byte n+1 when AESAXIN is written as half-word
        ADD_BITFIELD_WO(AESXIN1x, 8, 8)
    END_TYPE()

    struct AES256_t {
        AESACTL0_t                    AESACTL0;
        AESACTL1_t                    AESACTL1;
        AESASTAT_t                    AESASTAT;
        AESAKEY_t                     AESAKEY;
        AESADIN_t                     AESADIN;
        AESADOUT_t                    AESADOUT;
        AESAXDIN_t                    AESAXDIN;
        AESAXIN_t                     AESAXIN;
    };

    static AES256_t & AES256     = (*(AES256_t *)0x40003c00);

} // _AES256_

// CRC32
namespace _CRC32_  {

    // Data Input for CRC32 Signature Computation
    // Reset value: 0x00000000
    BEGIN_TYPE(CRC32DI_t, uint16_t)
        // Data input register
        ADD_BITFIELD_RW(CRC32DI, 0, 16)
    END_TYPE()

    // Data In Reverse for CRC32 Computation
    // Reset value: 0x00000000
    BEGIN_TYPE(CRC32DIRB_t, uint16_t)
        // Data input register reversed
        ADD_BITFIELD_RW(CRC32DIRB, 0, 16)
    END_TYPE()

    // CRC32 Initialization and Result, lower 16 bits
    // Reset value: 0x00000000
    BEGIN_TYPE(CRC32INIRES_LO_t, uint16_t)
        // CRC32 initialization and result, lower 16 bits
        ADD_BITFIELD_RW(CRC32INIRES_LO, 0, 16)
    END_TYPE()

    // CRC32 Initialization and Result, upper 16 bits
    // Reset value: 0x00000000
    BEGIN_TYPE(CRC32INIRES_HI_t, uint16_t)
        // CRC32 initialization and result, upper 16 bits
        ADD_BITFIELD_RW(CRC32INIRES_HI, 0, 16)
    END_TYPE()

    // CRC32 Result Reverse, lower 16 bits
    // Reset value: 0x0000ffff
    BEGIN_TYPE(CRC32RESR_LO_t, uint16_t)
        // CRC32 reverse result, lower 16 bits
        ADD_BITFIELD_RW(CRC32RESR_LO, 0, 16)
    END_TYPE()

    // CRC32 Result Reverse, Upper 16 bits
    // Reset value: 0x0000ffff
    BEGIN_TYPE(CRC32RESR_HI_t, uint16_t)
        // CRC32 reverse result, upper 16 bits
        ADD_BITFIELD_RW(CRC32RESR_HI, 0, 16)
    END_TYPE()

    // Data Input for CRC16 computation
    // Reset value: 0x00000000
    BEGIN_TYPE(CRC16DI_t, uint16_t)
        // CRC16 data in
        ADD_BITFIELD_RW(CRC16DI, 0, 16)
    END_TYPE()

    // CRC16 Data In Reverse
    // Reset value: 0x00000000
    BEGIN_TYPE(CRC16DIRB_t, uint16_t)
        // CRC16 data in reverse byte
        ADD_BITFIELD_RW(CRC16DIRB, 0, 16)
    END_TYPE()

    // CRC16 Initialization and Result register
    // Reset value: 0x0000ffff
    BEGIN_TYPE(CRC16INIRES_t, uint16_t)
        // CRC16 initialization and result
        ADD_BITFIELD_RW(CRC16INIRES, 0, 16)
    END_TYPE()

    // CRC16 Result Reverse
    // Reset value: 0x0000ffff
    BEGIN_TYPE(CRC16RESR_t, uint16_t)
        // CRC16 reverse result
        ADD_BITFIELD_RW(CRC16RESR, 0, 16)
    END_TYPE()

    struct CRC32_t {
        CRC32DI_t                     CRC32DI;
        uint16_t                      reserved0;
        CRC32DIRB_t                   CRC32DIRB;
        uint16_t                      reserved1;
        CRC32INIRES_LO_t              CRC32INIRES_LO;
        CRC32INIRES_HI_t              CRC32INIRES_HI;
        CRC32RESR_LO_t                CRC32RESR_LO;
        CRC32RESR_HI_t                CRC32RESR_HI;
        CRC16DI_t                     CRC16DI;
        uint16_t                      reserved2;
        CRC16DIRB_t                   CRC16DIRB;
        uint16_t                      reserved3;
        CRC16INIRES_t                 CRC16INIRES;
        uint16_t                      reserved4[2];
        CRC16RESR_t                   CRC16RESR;
    };

    static CRC32_t & CRC32     = (*(CRC32_t *)0x40004000);

} // _CRC32_

// RTC_C
namespace _RTC_C_  {

    // RTCCTL0 Register
    // Reset value: 0x00009608
    BEGIN_TYPE(RTCCTL0_t, uint16_t)
        // Real-time clock ready interrupt flag
        ADD_BITFIELD_RW(RTCRDYIFG, 0, 1)
        // Real-time clock alarm interrupt flag
        ADD_BITFIELD_RW(RTCAIFG, 1, 1)
        // Real-time clock time event interrupt flag
        ADD_BITFIELD_RW(RTCTEVIFG, 2, 1)
        // 32-kHz crystal oscillator fault interrupt flag
        ADD_BITFIELD_RW(RTCOFIFG, 3, 1)
        // Real-time clock ready interrupt enable
        ADD_BITFIELD_RW(RTCRDYIE, 4, 1)
        // Real-time clock alarm interrupt enable
        ADD_BITFIELD_RW(RTCAIE, 5, 1)
        // Real-time clock time event interrupt enable
        ADD_BITFIELD_RW(RTCTEVIE, 6, 1)
        // 32-kHz crystal oscillator fault interrupt enable
        ADD_BITFIELD_RW(RTCOFIE, 7, 1)
        // Real-time clock key
        ADD_BITFIELD_RW(RTCKEY, 8, 8)
    END_TYPE()

    // RTC cannot be read safely
    static const uint32_t RTCCTL0_RTCRDYIFG__RTCRDYIFG_0 = 0;
    // RTC can be read safely
    static const uint32_t RTCCTL0_RTCRDYIFG__RTCRDYIFG_1 = 1;
    // No time event occurred
    static const uint32_t RTCCTL0_RTCAIFG__RTCAIFG_0 = 0;
    // Time event occurred
    static const uint32_t RTCCTL0_RTCAIFG__RTCAIFG_1 = 1;
    // No time event occurred
    static const uint32_t RTCCTL0_RTCTEVIFG__RTCTEVIFG_0 = 0;
    // Time event occurred
    static const uint32_t RTCCTL0_RTCTEVIFG__RTCTEVIFG_1 = 1;
    // No interrupt pending
    static const uint32_t RTCCTL0_RTCOFIFG__RTCOFIFG_0 = 0;
    // Interrupt pending. A 32-kHz crystal oscillator fault occurred after last reset.
    static const uint32_t RTCCTL0_RTCOFIFG__RTCOFIFG_1 = 1;
    // Interrupt not enabled
    static const uint32_t RTCCTL0_RTCRDYIE__RTCRDYIE_0 = 0;
    // Interrupt enabled
    static const uint32_t RTCCTL0_RTCRDYIE__RTCRDYIE_1 = 1;
    // Interrupt not enabled
    static const uint32_t RTCCTL0_RTCAIE__RTCAIE_0 = 0;
    // Interrupt enabled (LPM3/LPM3.5 wake-up enabled)
    static const uint32_t RTCCTL0_RTCAIE__RTCAIE_1 = 1;
    // Interrupt not enabled
    static const uint32_t RTCCTL0_RTCTEVIE__RTCTEVIE_0 = 0;
    // Interrupt enabled (LPM3/LPM3.5 wake-up enabled)
    static const uint32_t RTCCTL0_RTCTEVIE__RTCTEVIE_1 = 1;
    // Interrupt not enabled
    static const uint32_t RTCCTL0_RTCOFIE__RTCOFIE_0 = 0;
    // Interrupt enabled (LPM3/LPM3.5 wake-up enabled)
    static const uint32_t RTCCTL0_RTCOFIE__RTCOFIE_1 = 1;

    // RTCCTL13 Register
    // Reset value: 0x00000070
    BEGIN_TYPE(RTCCTL13_t, uint16_t)
        // Real-time clock time event
        ADD_BITFIELD_RW(RTCTEV, 0, 2)
        // Real-time clock source select
        ADD_BITFIELD_RW(RTCSSEL, 2, 2)
        // Real-time clock ready
        ADD_BITFIELD_RO(RTCRDY, 4, 1)
        ADD_BITFIELD_RO(RTCMODE, 5, 1)
        // Real-time clock hold
        ADD_BITFIELD_RW(RTCHOLD, 6, 1)
        // Real-time clock BCD select
        ADD_BITFIELD_RW(RTCBCD, 7, 1)
        // Real-time clock calibration frequency
        ADD_BITFIELD_RW(RTCCALF, 8, 2)
    END_TYPE()

    // Minute changed
    static const uint32_t RTCCTL13_RTCTEV__RTCTEV_0 = 0;
    // Hour changed
    static const uint32_t RTCCTL13_RTCTEV__RTCTEV_1 = 1;
    // Every day at midnight (00:00)
    static const uint32_t RTCCTL13_RTCTEV__RTCTEV_2 = 2;
    // Every day at noon (12:00)
    static const uint32_t RTCCTL13_RTCTEV__RTCTEV_3 = 3;
    // BCLK
    static const uint32_t RTCCTL13_RTCSSEL__RTCSSEL_0 = 0;
    // RTC time values in transition
    static const uint32_t RTCCTL13_RTCRDY__RTCRDY_0 = 0;
    // RTC time values safe for reading. This bit indicates when the real-time clock time values are safe for reading.
    static const uint32_t RTCCTL13_RTCRDY__RTCRDY_1 = 1;
    // Calendar mode. Always reads a value of 1.
    static const uint32_t RTCCTL13_RTCMODE__RTCMODE_1 = 1;
    // Real-time clock is operational
    static const uint32_t RTCCTL13_RTCHOLD__RTCHOLD_0 = 0;
    // When set, the calendar is stopped as well as the prescale counters, RT0PS and RT1PS are don't care
    static const uint32_t RTCCTL13_RTCHOLD__RTCHOLD_1 = 1;
    // Binary (hexadecimal) code selected
    static const uint32_t RTCCTL13_RTCBCD__RTCBCD_0 = 0;
    // Binary coded decimal (BCD) code selected
    static const uint32_t RTCCTL13_RTCBCD__RTCBCD_1 = 1;
    // No frequency output to RTCCLK pin
    static const uint32_t RTCCTL13_RTCCALF__RTCCALF_0 = 0;
    // 512 Hz
    static const uint32_t RTCCTL13_RTCCALF__RTCCALF_1 = 1;
    // 256 Hz
    static const uint32_t RTCCTL13_RTCCALF__RTCCALF_2 = 2;
    // 1 Hz
    static const uint32_t RTCCTL13_RTCCALF__RTCCALF_3 = 3;

    // RTCOCAL Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCOCAL_t, uint16_t)
        // Real-time clock offset error calibration
        ADD_BITFIELD_RW(RTCOCAL, 0, 8)
        // Real-time clock offset error calibration sign
        ADD_BITFIELD_RW(RTCOCALS, 15, 1)
    END_TYPE()

    // Down calibration. Frequency adjusted down.
    static const uint32_t RTCOCAL_RTCOCALS__RTCOCALS_0 = 0;
    // Up calibration. Frequency adjusted up.
    static const uint32_t RTCOCAL_RTCOCALS__RTCOCALS_1 = 1;

    // RTCTCMP Register
    // Reset value: 0x00004000
    BEGIN_TYPE(RTCTCMP_t, uint16_t)
        // Real-time clock temperature compensation
        ADD_BITFIELD_RW(RTCTCMP, 0, 8)
        // Real-time clock temperature compensation write OK
        ADD_BITFIELD_RO(RTCTCOK, 13, 1)
        // Real-time clock temperature compensation ready
        ADD_BITFIELD_RO(RTCTCRDY, 14, 1)
        // Real-time clock temperature compensation sign
        ADD_BITFIELD_RW(RTCTCMPS, 15, 1)
    END_TYPE()

    // Write to RTCTCMPx is unsuccessful
    static const uint32_t RTCTCMP_RTCTCOK__RTCTCOK_0 = 0;
    // Write to RTCTCMPx is successful
    static const uint32_t RTCTCMP_RTCTCOK__RTCTCOK_1 = 1;
    // Down calibration. Frequency adjusted down
    static const uint32_t RTCTCMP_RTCTCMPS__RTCTCMPS_0 = 0;
    // Up calibration. Frequency adjusted up
    static const uint32_t RTCTCMP_RTCTCMPS__RTCTCMPS_1 = 1;

    // Real-Time Clock Prescale Timer 0 Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCPS0CTL_t, uint16_t)
        // Prescale timer 0 interrupt flag
        ADD_BITFIELD_RW(RT0PSIFG, 0, 1)
        // Prescale timer 0 interrupt enable
        ADD_BITFIELD_RW(RT0PSIE, 1, 1)
        // Prescale timer 0 interrupt interval
        ADD_BITFIELD_RW(RT0IP, 2, 3)
    END_TYPE()

    // No time event occurred
    static const uint32_t RTCPS0CTL_RT0PSIFG__RT0PSIFG_0 = 0;
    // Time event occurred
    static const uint32_t RTCPS0CTL_RT0PSIFG__RT0PSIFG_1 = 1;
    // Interrupt not enabled
    static const uint32_t RTCPS0CTL_RT0PSIE__RT0PSIE_0 = 0;
    // Interrupt enabled (LPM3/LPM3.5 wake-up enabled)
    static const uint32_t RTCPS0CTL_RT0PSIE__RT0PSIE_1 = 1;
    // Divide by 2
    static const uint32_t RTCPS0CTL_RT0IP__RT0IP_0 = 0;
    // Divide by 4
    static const uint32_t RTCPS0CTL_RT0IP__RT0IP_1 = 1;
    // Divide by 8
    static const uint32_t RTCPS0CTL_RT0IP__RT0IP_2 = 2;
    // Divide by 16
    static const uint32_t RTCPS0CTL_RT0IP__RT0IP_3 = 3;
    // Divide by 32
    static const uint32_t RTCPS0CTL_RT0IP__RT0IP_4 = 4;
    // Divide by 64
    static const uint32_t RTCPS0CTL_RT0IP__RT0IP_5 = 5;
    // Divide by 128
    static const uint32_t RTCPS0CTL_RT0IP__RT0IP_6 = 6;
    // Divide by 256
    static const uint32_t RTCPS0CTL_RT0IP__RT0IP_7 = 7;

    // Real-Time Clock Prescale Timer 1 Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCPS1CTL_t, uint16_t)
        // Prescale timer 1 interrupt flag
        ADD_BITFIELD_RW(RT1PSIFG, 0, 1)
        // Prescale timer 1 interrupt enable
        ADD_BITFIELD_RW(RT1PSIE, 1, 1)
        // Prescale timer 1 interrupt interval
        ADD_BITFIELD_RW(RT1IP, 2, 3)
    END_TYPE()

    // No time event occurred
    static const uint32_t RTCPS1CTL_RT1PSIFG__RT1PSIFG_0 = 0;
    // Time event occurred
    static const uint32_t RTCPS1CTL_RT1PSIFG__RT1PSIFG_1 = 1;
    // Interrupt not enabled
    static const uint32_t RTCPS1CTL_RT1PSIE__RT1PSIE_0 = 0;
    // Interrupt enabled (LPM3/LPM3.5 wake-up enabled)
    static const uint32_t RTCPS1CTL_RT1PSIE__RT1PSIE_1 = 1;
    // Divide by 2
    static const uint32_t RTCPS1CTL_RT1IP__RT1IP_0 = 0;
    // Divide by 4
    static const uint32_t RTCPS1CTL_RT1IP__RT1IP_1 = 1;
    // Divide by 8
    static const uint32_t RTCPS1CTL_RT1IP__RT1IP_2 = 2;
    // Divide by 16
    static const uint32_t RTCPS1CTL_RT1IP__RT1IP_3 = 3;
    // Divide by 32
    static const uint32_t RTCPS1CTL_RT1IP__RT1IP_4 = 4;
    // Divide by 64
    static const uint32_t RTCPS1CTL_RT1IP__RT1IP_5 = 5;
    // Divide by 128
    static const uint32_t RTCPS1CTL_RT1IP__RT1IP_6 = 6;
    // Divide by 256
    static const uint32_t RTCPS1CTL_RT1IP__RT1IP_7 = 7;

    // Real-Time Clock Prescale Timer Counter Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCPS_t, uint16_t)
        // Prescale timer 0 counter value
        ADD_BITFIELD_RW(RT0PS, 0, 8)
        // Prescale timer 1 counter value
        ADD_BITFIELD_RW(RT1PS, 8, 8)
    END_TYPE()

    // Real-Time Clock Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCIV_t, uint16_t)
        // Real-time clock interrupt vector value
        ADD_BITFIELD_RO(RTCIV, 0, 16)
    END_TYPE()

    // No interrupt pending
    static const uint32_t RTCIV_RTCIV__RTCIV_0 = 0;
    // Interrupt Source: RTC oscillator failure; Interrupt Flag: RTCOFIFG; Interrupt Priority: Highest
    static const uint32_t RTCIV_RTCIV__RTCIV_2 = 2;
    // Interrupt Source: RTC ready; Interrupt Flag: RTCRDYIFG
    static const uint32_t RTCIV_RTCIV__RTCIV_4 = 4;
    // Interrupt Source: RTC interval timer; Interrupt Flag: RTCTEVIFG
    static const uint32_t RTCIV_RTCIV__RTCIV_6 = 6;
    // Interrupt Source: RTC user alarm; Interrupt Flag: RTCAIFG
    static const uint32_t RTCIV_RTCIV__RTCIV_8 = 8;
    // Interrupt Source: RTC prescaler 0; Interrupt Flag: RT0PSIFG
    static const uint32_t RTCIV_RTCIV__RTCIV_10 = 10;
    // Interrupt Source: RTC prescaler 1; Interrupt Flag: RT1PSIFG
    static const uint32_t RTCIV_RTCIV__RTCIV_12 = 12;

    // RTCTIM0 Register  Hexadecimal Format
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCTIM0_t, uint16_t)
        // Seconds (0 to 59)
        ADD_BITFIELD_RW(Seconds, 0, 6)
        // Minutes (0 to 59)
        ADD_BITFIELD_RW(Minutes, 8, 6)
    END_TYPE()

    // Real-Time Clock Hour, Day of Week
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCTIM1_t, uint16_t)
        // Hours (0 to 23)
        ADD_BITFIELD_RW(Hours, 0, 5)
        // Day of week (0 to 6)
        ADD_BITFIELD_RW(DayofWeek, 8, 3)
    END_TYPE()

    // RTCDATE - Hexadecimal Format
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCDATE_t, uint16_t)
        // Day of month (1 to 28, 29, 30, 31)
        ADD_BITFIELD_RW(Day, 0, 5)
        // Month (1 to 12)
        ADD_BITFIELD_RW(Month, 8, 4)
    END_TYPE()

    // RTCYEAR Register  Hexadecimal Format
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCYEAR_t, uint16_t)
        // Year  low byte. Valid values for Year are 0 to 4095.
        ADD_BITFIELD_RW(YearLowByte, 0, 8)
        // Year  high byte. Valid values for Year are 0 to 4095.
        ADD_BITFIELD_RW(YearHighByte, 8, 4)
    END_TYPE()

    // RTCMINHR - Hexadecimal Format
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCAMINHR_t, uint16_t)
        // Minutes (0 to 59)
        ADD_BITFIELD_RW(Minutes, 0, 6)
        // Alarm enable
        ADD_BITFIELD_RW(MINAE, 7, 1)
        // Hours (0 to 23)
        ADD_BITFIELD_RW(Hours, 8, 5)
        // Alarm enable
        ADD_BITFIELD_RW(HOURAE, 15, 1)
    END_TYPE()

    // RTCADOWDAY - Hexadecimal Format
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCADOWDAY_t, uint16_t)
        // Day of week (0 to 6)
        ADD_BITFIELD_RW(DayofWeek, 0, 3)
        // Alarm enable
        ADD_BITFIELD_RW(DOWAE, 7, 1)
        // Day of month (1 to 28, 29, 30, 31)
        ADD_BITFIELD_RW(DayofMonth, 8, 5)
        // Alarm enable
        ADD_BITFIELD_RW(DAYAE, 15, 1)
    END_TYPE()

    // Binary-to-BCD Conversion Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCBIN2BCD_t, uint16_t)
        // bin to bcd conversion
        ADD_BITFIELD_RW(BIN2BCD, 0, 16)
    END_TYPE()

    // BCD-to-Binary Conversion Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RTCBCD2BIN_t, uint16_t)
        // bcd to bin conversion
        ADD_BITFIELD_RW(BCD2BIN, 0, 16)
    END_TYPE()

    struct RTC_C_t {
        RTCCTL0_t                     RTCCTL0;
        RTCCTL13_t                    RTCCTL13;
        RTCOCAL_t                     RTCOCAL;
        RTCTCMP_t                     RTCTCMP;
        RTCPS0CTL_t                   RTCPS0CTL;
        RTCPS1CTL_t                   RTCPS1CTL;
        RTCPS_t                       RTCPS;
        RTCIV_t                       RTCIV;
        RTCTIM0_t                     RTCTIM0;
        RTCTIM1_t                     RTCTIM1;
        RTCDATE_t                     RTCDATE;
        RTCYEAR_t                     RTCYEAR;
        RTCAMINHR_t                   RTCAMINHR;
        RTCADOWDAY_t                  RTCADOWDAY;
        RTCBIN2BCD_t                  RTCBIN2BCD;
        RTCBCD2BIN_t                  RTCBCD2BIN;
    };

    static RTC_C_t & RTC_C     = (*(RTC_C_t *)0x40004400);

} // _RTC_C_

// WDT_A
namespace _WDT_A_  {

    // Watchdog Timer Control Register
    // Reset value: 0x00006904
    BEGIN_TYPE(WDTCTL_t, uint16_t)
        // Watchdog timer interval select
        ADD_BITFIELD_RW(WDTIS, 0, 3)
        // Watchdog timer counter clear
        ADD_BITFIELD_WO(WDTCNTCL, 3, 1)
        // Watchdog timer mode select
        ADD_BITFIELD_RW(WDTTMSEL, 4, 1)
        // Watchdog timer clock source select
        ADD_BITFIELD_RW(WDTSSEL, 5, 2)
        // Watchdog timer hold
        ADD_BITFIELD_RW(WDTHOLD, 7, 1)
        // Watchdog timer password
        ADD_BITFIELD_RW(WDTPW, 8, 8)
    END_TYPE()

    // Watchdog clock source / (2^(31)) (18:12:16 at 32.768 kHz)
    static const uint32_t WDTCTL_WDTIS__WDTIS_0 = 0;
    // Watchdog clock source /(2^(27)) (01:08:16 at 32.768 kHz)
    static const uint32_t WDTCTL_WDTIS__WDTIS_1 = 1;
    // Watchdog clock source /(2^(23)) (00:04:16 at 32.768 kHz)
    static const uint32_t WDTCTL_WDTIS__WDTIS_2 = 2;
    // Watchdog clock source /(2^(19)) (00:00:16 at 32.768 kHz)
    static const uint32_t WDTCTL_WDTIS__WDTIS_3 = 3;
    // Watchdog clock source /(2^(15)) (1 s at 32.768 kHz)
    static const uint32_t WDTCTL_WDTIS__WDTIS_4 = 4;
    // Watchdog clock source / (2^(13)) (250 ms at 32.768 kHz)
    static const uint32_t WDTCTL_WDTIS__WDTIS_5 = 5;
    // Watchdog clock source / (2^(9)) (15.625 ms at 32.768 kHz)
    static const uint32_t WDTCTL_WDTIS__WDTIS_6 = 6;
    // Watchdog clock source / (2^(6)) (1.95 ms at 32.768 kHz)
    static const uint32_t WDTCTL_WDTIS__WDTIS_7 = 7;
    // No action
    static const uint32_t WDTCTL_WDTCNTCL__WDTCNTCL_0 = 0;
    // WDTCNT = 0000h
    static const uint32_t WDTCTL_WDTCNTCL__WDTCNTCL_1 = 1;
    // Watchdog mode
    static const uint32_t WDTCTL_WDTTMSEL__WDTTMSEL_0 = 0;
    // Interval timer mode
    static const uint32_t WDTCTL_WDTTMSEL__WDTTMSEL_1 = 1;
    // SMCLK
    static const uint32_t WDTCTL_WDTSSEL__WDTSSEL_0 = 0;
    // ACLK
    static const uint32_t WDTCTL_WDTSSEL__WDTSSEL_1 = 1;
    // VLOCLK
    static const uint32_t WDTCTL_WDTSSEL__WDTSSEL_2 = 2;
    // BCLK
    static const uint32_t WDTCTL_WDTSSEL__WDTSSEL_3 = 3;
    // Watchdog timer is not stopped
    static const uint32_t WDTCTL_WDTHOLD__WDTHOLD_0 = 0;
    // Watchdog timer is stopped
    static const uint32_t WDTCTL_WDTHOLD__WDTHOLD_1 = 1;

    struct WDT_A_t {
        uint16_t                      reserved0[6];
        WDTCTL_t                      WDTCTL;
    };

    static WDT_A_t & WDT_A     = (*(WDT_A_t *)0x40004800);

} // _WDT_A_

// DIO
namespace _DIO_  {

    // Port A Input
    // Reset value: 0x00000000
    BEGIN_TYPE(PAIN_t, uint16_t)
        // Port 1 Input
        ADD_BITFIELD_RO(P1IN, 0, 8)
        // Port 2 Input
        ADD_BITFIELD_RO(P2IN, 8, 8)
    END_TYPE()

    // Port A Output
    // Reset value: 0x00000000
    BEGIN_TYPE(PAOUT_t, uint16_t)
        // Port 2 Output
        ADD_BITFIELD_RW(P2OUT, 8, 8)
        // Port 1 Output
        ADD_BITFIELD_RW(P1OUT, 0, 8)
    END_TYPE()

    // Port A Direction
    // Reset value: 0x00000000
    BEGIN_TYPE(PADIR_t, uint16_t)
        // Port 1 Direction
        ADD_BITFIELD_RW(P1DIR, 0, 8)
        // Port 2 Direction
        ADD_BITFIELD_RW(P2DIR, 8, 8)
    END_TYPE()

    // Port A Resistor Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(PAREN_t, uint16_t)
        // Port 1 Resistor Enable
        ADD_BITFIELD_RW(P1REN, 0, 8)
        // Port 2 Resistor Enable
        ADD_BITFIELD_RW(P2REN, 8, 8)
    END_TYPE()

    // Port A Drive Strength
    BEGIN_TYPE(PADS_t, uint16_t)
        // Port 1 Drive Strength
        ADD_BITFIELD_RW(P1DS, 0, 8)
        // Port 2 Drive Strength
        ADD_BITFIELD_RW(P2DS, 8, 8)
    END_TYPE()

    // Port A Select 0
    // Reset value: 0x00000000
    BEGIN_TYPE(PASEL0_t, uint16_t)
        // Port 1 Select 0
        ADD_BITFIELD_RW(P1SEL0, 0, 8)
        // Port 2 Select 0
        ADD_BITFIELD_RW(P2SEL0, 8, 8)
    END_TYPE()

    // Port A Select 1
    // Reset value: 0x00000000
    BEGIN_TYPE(PASEL1_t, uint16_t)
        // Port 1 Select 1
        ADD_BITFIELD_RW(P1SEL1, 0, 8)
        // Port 2 Select 1
        ADD_BITFIELD_RW(P2SEL1, 8, 8)
    END_TYPE()

    // Port 1 Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(P1IV_t, uint16_t)
        // Port 1 interrupt vector value
        ADD_BITFIELD_RO(P1IV, 0, 5)
    END_TYPE()

    // No interrupt pending
    static const uint32_t P1IV_P1IV__P1IV_0 = 0;
    // Interrupt Source: Port 1.0 interrupt; Interrupt Flag: P1IFG0; Interrupt Priority: Highest
    static const uint32_t P1IV_P1IV__P1IV_2 = 2;
    // Interrupt Source: Port 1.1 interrupt; Interrupt Flag: P1IFG1
    static const uint32_t P1IV_P1IV__P1IV_4 = 4;
    // Interrupt Source: Port 1.2 interrupt; Interrupt Flag: P1IFG2
    static const uint32_t P1IV_P1IV__P1IV_6 = 6;
    // Interrupt Source: Port 1.3 interrupt; Interrupt Flag: P1IFG3
    static const uint32_t P1IV_P1IV__P1IV_8 = 8;
    // Interrupt Source: Port 1.4 interrupt; Interrupt Flag: P1IFG4
    static const uint32_t P1IV_P1IV__P1IV_10 = 10;
    // Interrupt Source: Port 1.5 interrupt; Interrupt Flag: P1IFG5
    static const uint32_t P1IV_P1IV__P1IV_12 = 12;
    // Interrupt Source: Port 1.6 interrupt; Interrupt Flag: P1IFG6
    static const uint32_t P1IV_P1IV__P1IV_14 = 14;
    // Interrupt Source: Port 1.7 interrupt; Interrupt Flag: P1IFG7; Interrupt Priority: Lowest
    static const uint32_t P1IV_P1IV__P1IV_16 = 16;

    // Port A Complement Select
    // Reset value: 0x00000000
    BEGIN_TYPE(PASELC_t, uint16_t)
        // Port 1 Complement Select
        ADD_BITFIELD_RW(P1SELC, 0, 8)
        // Port 2 Complement Select
        ADD_BITFIELD_RW(P2SELC, 8, 8)
    END_TYPE()

    // Port A Interrupt Edge Select
    // Reset value: 0x00000000
    BEGIN_TYPE(PAIES_t, uint16_t)
        // Port 1 Interrupt Edge Select
        ADD_BITFIELD_RW(P1IES, 0, 8)
        // Port 2 Interrupt Edge Select
        ADD_BITFIELD_RW(P2IES, 8, 8)
    END_TYPE()

    // Port A Interrupt Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(PAIE_t, uint16_t)
        // Port 1 Interrupt Enable
        ADD_BITFIELD_RW(P1IE, 0, 8)
        // Port 2 Interrupt Enable
        ADD_BITFIELD_RW(P2IE, 8, 8)
    END_TYPE()

    // Port A Interrupt Flag
    // Reset value: 0x00000000
    BEGIN_TYPE(PAIFG_t, uint16_t)
        // Port 1 Interrupt Flag
        ADD_BITFIELD_RW(P1IFG, 0, 8)
        // Port 2 Interrupt Flag
        ADD_BITFIELD_RW(P2IFG, 8, 8)
    END_TYPE()

    // Port 2 Interrupt Vector Register
    BEGIN_TYPE(P2IV_t, uint16_t)
        // Port 2 interrupt vector value
        ADD_BITFIELD_RO(P2IV, 0, 5)
    END_TYPE()

    // No interrupt pending
    static const uint32_t P2IV_P2IV__P2IV_0 = 0;
    // Interrupt Source: Port 2.0 interrupt; Interrupt Flag: P2IFG0; Interrupt Priority: Highest
    static const uint32_t P2IV_P2IV__P2IV_2 = 2;
    // Interrupt Source: Port 2.1 interrupt; Interrupt Flag: P2IFG1
    static const uint32_t P2IV_P2IV__P2IV_4 = 4;
    // Interrupt Source: Port 2.2 interrupt; Interrupt Flag: P2IFG2
    static const uint32_t P2IV_P2IV__P2IV_6 = 6;
    // Interrupt Source: Port 2.3 interrupt; Interrupt Flag: P2IFG3
    static const uint32_t P2IV_P2IV__P2IV_8 = 8;
    // Interrupt Source: Port 2.4 interrupt; Interrupt Flag: P2IFG4
    static const uint32_t P2IV_P2IV__P2IV_10 = 10;
    // Interrupt Source: Port 2.5 interrupt; Interrupt Flag: P2IFG5
    static const uint32_t P2IV_P2IV__P2IV_12 = 12;
    // Interrupt Source: Port 2.6 interrupt; Interrupt Flag: P2IFG6
    static const uint32_t P2IV_P2IV__P2IV_14 = 14;
    // Interrupt Source: Port 2.7 interrupt; Interrupt Flag: P2IFG7; Interrupt Priority: Lowest
    static const uint32_t P2IV_P2IV__P2IV_16 = 16;

    // Port B Input
    // Reset value: 0x00000000
    BEGIN_TYPE(PBIN_t, uint16_t)
        // Port 3 Input
        ADD_BITFIELD_RO(P3IN, 0, 8)
        // Port 4 Input
        ADD_BITFIELD_RO(P4IN, 8, 8)
    END_TYPE()

    // Port B Output
    // Reset value: 0x00000000
    BEGIN_TYPE(PBOUT_t, uint16_t)
        // Port 3 Output
        ADD_BITFIELD_RW(P3OUT, 0, 8)
        // Port 4 Output
        ADD_BITFIELD_RW(P4OUT, 8, 8)
    END_TYPE()

    // Port B Direction
    // Reset value: 0x00000000
    BEGIN_TYPE(PBDIR_t, uint16_t)
        // Port 3 Direction
        ADD_BITFIELD_RW(P3DIR, 0, 8)
        // Port 4 Direction
        ADD_BITFIELD_RW(P4DIR, 8, 8)
    END_TYPE()

    // Port B Resistor Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(PBREN_t, uint16_t)
        // Port 3 Resistor Enable
        ADD_BITFIELD_RW(P3REN, 0, 8)
        // Port 4 Resistor Enable
        ADD_BITFIELD_RW(P4REN, 8, 8)
    END_TYPE()

    // Port B Drive Strength
    BEGIN_TYPE(PBDS_t, uint16_t)
        // Port 3 Drive Strength
        ADD_BITFIELD_RW(P3DS, 0, 8)
        // Port 4 Drive Strength
        ADD_BITFIELD_RW(P4DS, 8, 8)
    END_TYPE()

    // Port B Select 0
    // Reset value: 0x00000000
    BEGIN_TYPE(PBSEL0_t, uint16_t)
        // Port 4 Select 0
        ADD_BITFIELD_RW(P4SEL0, 8, 8)
        // Port 3 Select 0
        ADD_BITFIELD_RW(P3SEL0, 0, 8)
    END_TYPE()

    // Port B Select 1
    // Reset value: 0x00000000
    BEGIN_TYPE(PBSEL1_t, uint16_t)
        // Port 3 Select 1
        ADD_BITFIELD_RW(P3SEL1, 0, 8)
        // Port 4 Select 1
        ADD_BITFIELD_RW(P4SEL1, 8, 8)
    END_TYPE()

    // Port 3 Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(P3IV_t, uint16_t)
        // Port 3 interrupt vector value
        ADD_BITFIELD_RO(P3IV, 0, 5)
    END_TYPE()

    // No interrupt pending
    static const uint32_t P3IV_P3IV__P3IV_0 = 0;
    // Interrupt Source: Port 3.0 interrupt; Interrupt Flag: P3IFG0; Interrupt Priority: Highest
    static const uint32_t P3IV_P3IV__P3IV_2 = 2;
    // Interrupt Source: Port 3.1 interrupt; Interrupt Flag: P3IFG1
    static const uint32_t P3IV_P3IV__P3IV_4 = 4;
    // Interrupt Source: Port 3.2 interrupt; Interrupt Flag: P3IFG2
    static const uint32_t P3IV_P3IV__P3IV_6 = 6;
    // Interrupt Source: Port 3.3 interrupt; Interrupt Flag: P3IFG3
    static const uint32_t P3IV_P3IV__P3IV_8 = 8;
    // Interrupt Source: Port 3.4 interrupt; Interrupt Flag: P3IFG4
    static const uint32_t P3IV_P3IV__P3IV_10 = 10;
    // Interrupt Source: Port 3.5 interrupt; Interrupt Flag: P3IFG5
    static const uint32_t P3IV_P3IV__P3IV_12 = 12;
    // Interrupt Source: Port 3.6 interrupt; Interrupt Flag: P3IFG6
    static const uint32_t P3IV_P3IV__P3IV_14 = 14;
    // Interrupt Source: Port 3.7 interrupt; Interrupt Flag: P3IFG7; Interrupt Priority: Lowest
    static const uint32_t P3IV_P3IV__P3IV_16 = 16;

    // Port B Complement Select
    // Reset value: 0x00000000
    BEGIN_TYPE(PBSELC_t, uint16_t)
        // Port 3 Complement Select
        ADD_BITFIELD_RW(P3SELC, 0, 8)
        // Port 4 Complement Select
        ADD_BITFIELD_RW(P4SELC, 8, 8)
    END_TYPE()

    // Port B Interrupt Edge Select
    // Reset value: 0x00000000
    BEGIN_TYPE(PBIES_t, uint16_t)
        // Port 3 Interrupt Edge Select
        ADD_BITFIELD_RW(P3IES, 0, 8)
        // Port 4 Interrupt Edge Select
        ADD_BITFIELD_RW(P4IES, 8, 8)
    END_TYPE()

    // Port B Interrupt Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(PBIE_t, uint16_t)
        // Port 3 Interrupt Enable
        ADD_BITFIELD_RW(P3IE, 0, 8)
        // Port 4 Interrupt Enable
        ADD_BITFIELD_RW(P4IE, 8, 8)
    END_TYPE()

    // Port B Interrupt Flag
    // Reset value: 0x00000000
    BEGIN_TYPE(PBIFG_t, uint16_t)
        // Port 3 Interrupt Flag
        ADD_BITFIELD_RW(P3IFG, 0, 8)
        // Port 4 Interrupt Flag
        ADD_BITFIELD_RW(P4IFG, 8, 8)
    END_TYPE()

    // Port 4 Interrupt Vector Register
    BEGIN_TYPE(P4IV_t, uint16_t)
        // Port 4 interrupt vector value
        ADD_BITFIELD_RO(P4IV, 0, 5)
    END_TYPE()

    // No interrupt pending
    static const uint32_t P4IV_P4IV__P4IV_0 = 0;
    // Interrupt Source: Port 4.0 interrupt; Interrupt Flag: P4IFG0; Interrupt Priority: Highest
    static const uint32_t P4IV_P4IV__P4IV_2 = 2;
    // Interrupt Source: Port 4.1 interrupt; Interrupt Flag: P4IFG1
    static const uint32_t P4IV_P4IV__P4IV_4 = 4;
    // Interrupt Source: Port 4.2 interrupt; Interrupt Flag: P4IFG2
    static const uint32_t P4IV_P4IV__P4IV_6 = 6;
    // Interrupt Source: Port 4.3 interrupt; Interrupt Flag: P4IFG3
    static const uint32_t P4IV_P4IV__P4IV_8 = 8;
    // Interrupt Source: Port 4.4 interrupt; Interrupt Flag: P4IFG4
    static const uint32_t P4IV_P4IV__P4IV_10 = 10;
    // Interrupt Source: Port 4.5 interrupt; Interrupt Flag: P4IFG5
    static const uint32_t P4IV_P4IV__P4IV_12 = 12;
    // Interrupt Source: Port 4.6 interrupt; Interrupt Flag: P4IFG6
    static const uint32_t P4IV_P4IV__P4IV_14 = 14;
    // Interrupt Source: Port 4.7 interrupt; Interrupt Flag: P4IFG7; Interrupt Priority: Lowest
    static const uint32_t P4IV_P4IV__P4IV_16 = 16;

    // Port C Input
    // Reset value: 0x00000000
    BEGIN_TYPE(PCIN_t, uint16_t)
        // Port 5 Input
        ADD_BITFIELD_RO(P5IN, 0, 8)
        // Port 6 Input
        ADD_BITFIELD_RO(P6IN, 8, 8)
    END_TYPE()

    // Port C Output
    // Reset value: 0x00000000
    BEGIN_TYPE(PCOUT_t, uint16_t)
        // Port 5 Output
        ADD_BITFIELD_RW(P5OUT, 0, 8)
        // Port 6 Output
        ADD_BITFIELD_RW(P6OUT, 8, 8)
    END_TYPE()

    // Port C Direction
    // Reset value: 0x00000000
    BEGIN_TYPE(PCDIR_t, uint16_t)
        // Port 5 Direction
        ADD_BITFIELD_RW(P5DIR, 0, 8)
        // Port 6 Direction
        ADD_BITFIELD_RW(P6DIR, 8, 8)
    END_TYPE()

    // Port C Resistor Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(PCREN_t, uint16_t)
        // Port 5 Resistor Enable
        ADD_BITFIELD_RW(P5REN, 0, 8)
        // Port 6 Resistor Enable
        ADD_BITFIELD_RW(P6REN, 8, 8)
    END_TYPE()

    // Port C Drive Strength
    BEGIN_TYPE(PCDS_t, uint16_t)
        // Port 5 Drive Strength
        ADD_BITFIELD_RW(P5DS, 0, 8)
        // Port 6 Drive Strength
        ADD_BITFIELD_RW(P6DS, 8, 8)
    END_TYPE()

    // Port C Select 0
    // Reset value: 0x00000000
    BEGIN_TYPE(PCSEL0_t, uint16_t)
        // Port 5 Select 0
        ADD_BITFIELD_RW(P5SEL0, 0, 8)
        // Port 6 Select 0
        ADD_BITFIELD_RW(P6SEL0, 8, 8)
    END_TYPE()

    // Port C Select 1
    // Reset value: 0x00000000
    BEGIN_TYPE(PCSEL1_t, uint16_t)
        // Port 5 Select 1
        ADD_BITFIELD_RW(P5SEL1, 0, 8)
        // Port 6 Select 1
        ADD_BITFIELD_RW(P6SEL1, 8, 8)
    END_TYPE()

    // Port 5 Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(P5IV_t, uint16_t)
        // Port 5 interrupt vector value
        ADD_BITFIELD_RO(P5IV, 0, 5)
    END_TYPE()

    // No interrupt pending
    static const uint32_t P5IV_P5IV__P5IV_0 = 0;
    // Interrupt Source: Port 5.0 interrupt; Interrupt Flag: P5IFG0; Interrupt Priority: Highest
    static const uint32_t P5IV_P5IV__P5IV_2 = 2;
    // Interrupt Source: Port 5.1 interrupt; Interrupt Flag: P5IFG1
    static const uint32_t P5IV_P5IV__P5IV_4 = 4;
    // Interrupt Source: Port 5.2 interrupt; Interrupt Flag: P5IFG2
    static const uint32_t P5IV_P5IV__P5IV_6 = 6;
    // Interrupt Source: Port 5.3 interrupt; Interrupt Flag: P5IFG3
    static const uint32_t P5IV_P5IV__P5IV_8 = 8;
    // Interrupt Source: Port 5.4 interrupt; Interrupt Flag: P5IFG4
    static const uint32_t P5IV_P5IV__P5IV_10 = 10;
    // Interrupt Source: Port 5.5 interrupt; Interrupt Flag: P5IFG5
    static const uint32_t P5IV_P5IV__P5IV_12 = 12;
    // Interrupt Source: Port 5.6 interrupt; Interrupt Flag: P5IFG6
    static const uint32_t P5IV_P5IV__P5IV_14 = 14;
    // Interrupt Source: Port 5.7 interrupt; Interrupt Flag: P5IFG7; Interrupt Priority: Lowest
    static const uint32_t P5IV_P5IV__P5IV_16 = 16;

    // Port C Complement Select
    // Reset value: 0x00000000
    BEGIN_TYPE(PCSELC_t, uint16_t)
        // Port 5 Complement Select
        ADD_BITFIELD_RW(P5SELC, 0, 8)
        // Port 6 Complement Select
        ADD_BITFIELD_RW(P6SELC, 8, 8)
    END_TYPE()

    // Port C Interrupt Edge Select
    // Reset value: 0x00000000
    BEGIN_TYPE(PCIES_t, uint16_t)
        // Port 5 Interrupt Edge Select
        ADD_BITFIELD_RW(P5IES, 0, 8)
        // Port 6 Interrupt Edge Select
        ADD_BITFIELD_RW(P6IES, 8, 8)
    END_TYPE()

    // Port C Interrupt Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(PCIE_t, uint16_t)
        // Port 5 Interrupt Enable
        ADD_BITFIELD_RW(P5IE, 0, 8)
        // Port 6 Interrupt Enable
        ADD_BITFIELD_RW(P6IE, 8, 8)
    END_TYPE()

    // Port C Interrupt Flag
    // Reset value: 0x00000000
    BEGIN_TYPE(PCIFG_t, uint16_t)
        // Port 5 Interrupt Flag
        ADD_BITFIELD_RW(P5IFG, 0, 8)
        // Port 6 Interrupt Flag
        ADD_BITFIELD_RW(P6IFG, 8, 8)
    END_TYPE()

    // Port 6 Interrupt Vector Register
    BEGIN_TYPE(P6IV_t, uint16_t)
        // Port 6 interrupt vector value
        ADD_BITFIELD_RO(P6IV, 0, 5)
    END_TYPE()

    // No interrupt pending
    static const uint32_t P6IV_P6IV__P6IV_0 = 0;
    // Interrupt Source: Port 6.0 interrupt; Interrupt Flag: P6IFG0; Interrupt Priority: Highest
    static const uint32_t P6IV_P6IV__P6IV_2 = 2;
    // Interrupt Source: Port 6.1 interrupt; Interrupt Flag: P6IFG1
    static const uint32_t P6IV_P6IV__P6IV_4 = 4;
    // Interrupt Source: Port 6.2 interrupt; Interrupt Flag: P6IFG2
    static const uint32_t P6IV_P6IV__P6IV_6 = 6;
    // Interrupt Source: Port 6.3 interrupt; Interrupt Flag: P6IFG3
    static const uint32_t P6IV_P6IV__P6IV_8 = 8;
    // Interrupt Source: Port 6.4 interrupt; Interrupt Flag: P6IFG4
    static const uint32_t P6IV_P6IV__P6IV_10 = 10;
    // Interrupt Source: Port 6.5 interrupt; Interrupt Flag: P6IFG5
    static const uint32_t P6IV_P6IV__P6IV_12 = 12;
    // Interrupt Source: Port 6.6 interrupt; Interrupt Flag: P6IFG6
    static const uint32_t P6IV_P6IV__P6IV_14 = 14;
    // Interrupt Source: Port 6.7 interrupt; Interrupt Flag: P6IFG7; Interrupt Priority: Lowest
    static const uint32_t P6IV_P6IV__P6IV_16 = 16;

    // Port D Input
    // Reset value: 0x00000000
    BEGIN_TYPE(PDIN_t, uint16_t)
        // Port 7 Input
        ADD_BITFIELD_RO(P7IN, 0, 8)
        // Port 8 Input
        ADD_BITFIELD_RO(P8IN, 8, 8)
    END_TYPE()

    // Port D Output
    // Reset value: 0x00000000
    BEGIN_TYPE(PDOUT_t, uint16_t)
        // Port 7 Output
        ADD_BITFIELD_RW(P7OUT, 0, 8)
        // Port 8 Output
        ADD_BITFIELD_RW(P8OUT, 8, 8)
    END_TYPE()

    // Port D Direction
    // Reset value: 0x00000000
    BEGIN_TYPE(PDDIR_t, uint16_t)
        // Port 7 Direction
        ADD_BITFIELD_RW(P7DIR, 0, 8)
        // Port 8 Direction
        ADD_BITFIELD_RW(P8DIR, 8, 8)
    END_TYPE()

    // Port D Resistor Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(PDREN_t, uint16_t)
        // Port 7 Resistor Enable
        ADD_BITFIELD_RW(P7REN, 0, 8)
        // Port 8 Resistor Enable
        ADD_BITFIELD_RW(P8REN, 8, 8)
    END_TYPE()

    // Port D Drive Strength
    BEGIN_TYPE(PDDS_t, uint16_t)
        // Port 7 Drive Strength
        ADD_BITFIELD_RW(P7DS, 0, 8)
        // Port 8 Drive Strength
        ADD_BITFIELD_RW(P8DS, 8, 8)
    END_TYPE()

    // Port D Select 0
    // Reset value: 0x00000000
    BEGIN_TYPE(PDSEL0_t, uint16_t)
        // Port 7 Select 0
        ADD_BITFIELD_RW(P7SEL0, 0, 8)
        // Port 8 Select 0
        ADD_BITFIELD_RW(P8SEL0, 8, 8)
    END_TYPE()

    // Port D Select 1
    // Reset value: 0x00000000
    BEGIN_TYPE(PDSEL1_t, uint16_t)
        // Port 7 Select 1
        ADD_BITFIELD_RW(P7SEL1, 0, 8)
        // Port 8 Select 1
        ADD_BITFIELD_RW(P8SEL1, 8, 8)
    END_TYPE()

    // Port 7 Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(P7IV_t, uint16_t)
        // Port 7 interrupt vector value
        ADD_BITFIELD_RO(P7IV, 0, 5)
    END_TYPE()

    // No interrupt pending
    static const uint32_t P7IV_P7IV__P7IV_0 = 0;
    // Interrupt Source: Port 7.0 interrupt; Interrupt Flag: P7IFG0; Interrupt Priority: Highest
    static const uint32_t P7IV_P7IV__P7IV_2 = 2;
    // Interrupt Source: Port 7.1 interrupt; Interrupt Flag: P7IFG1
    static const uint32_t P7IV_P7IV__P7IV_4 = 4;
    // Interrupt Source: Port 7.2 interrupt; Interrupt Flag: P7IFG2
    static const uint32_t P7IV_P7IV__P7IV_6 = 6;
    // Interrupt Source: Port 7.3 interrupt; Interrupt Flag: P7IFG3
    static const uint32_t P7IV_P7IV__P7IV_8 = 8;
    // Interrupt Source: Port 7.4 interrupt; Interrupt Flag: P7IFG4
    static const uint32_t P7IV_P7IV__P7IV_10 = 10;
    // Interrupt Source: Port 7.5 interrupt; Interrupt Flag: P7IFG5
    static const uint32_t P7IV_P7IV__P7IV_12 = 12;
    // Interrupt Source: Port 7.6 interrupt; Interrupt Flag: P7IFG6
    static const uint32_t P7IV_P7IV__P7IV_14 = 14;
    // Interrupt Source: Port 7.7 interrupt; Interrupt Flag: P7IFG7; Interrupt Priority: Lowest
    static const uint32_t P7IV_P7IV__P7IV_16 = 16;

    // Port D Complement Select
    // Reset value: 0x00000000
    BEGIN_TYPE(PDSELC_t, uint16_t)
        // Port 7 Complement Select
        ADD_BITFIELD_RW(P7SELC, 0, 8)
        // Port 8 Complement Select
        ADD_BITFIELD_RW(P8SELC, 8, 8)
    END_TYPE()

    // Port D Interrupt Edge Select
    // Reset value: 0x00000000
    BEGIN_TYPE(PDIES_t, uint16_t)
        // Port 7 Interrupt Edge Select
        ADD_BITFIELD_RW(P7IES, 0, 8)
        // Port 8 Interrupt Edge Select
        ADD_BITFIELD_RW(P8IES, 8, 8)
    END_TYPE()

    // Port D Interrupt Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(PDIE_t, uint16_t)
        // Port 7 Interrupt Enable
        ADD_BITFIELD_RW(P7IE, 0, 8)
        // Port 8 Interrupt Enable
        ADD_BITFIELD_RW(P8IE, 8, 8)
    END_TYPE()

    // Port D Interrupt Flag
    // Reset value: 0x00000000
    BEGIN_TYPE(PDIFG_t, uint16_t)
        // Port 7 Interrupt Flag
        ADD_BITFIELD_RW(P7IFG, 0, 8)
        // Port 8 Interrupt Flag
        ADD_BITFIELD_RW(P8IFG, 8, 8)
    END_TYPE()

    // Port 8 Interrupt Vector Register
    BEGIN_TYPE(P8IV_t, uint16_t)
        // Port 8 interrupt vector value
        ADD_BITFIELD_RO(P8IV, 0, 5)
    END_TYPE()

    // No interrupt pending
    static const uint32_t P8IV_P8IV__P8IV_0 = 0;
    // Interrupt Source: Port 8.0 interrupt; Interrupt Flag: P8IFG0; Interrupt Priority: Highest
    static const uint32_t P8IV_P8IV__P8IV_2 = 2;
    // Interrupt Source: Port 8.1 interrupt; Interrupt Flag: P8IFG1
    static const uint32_t P8IV_P8IV__P8IV_4 = 4;
    // Interrupt Source: Port 8.2 interrupt; Interrupt Flag: P8IFG2
    static const uint32_t P8IV_P8IV__P8IV_6 = 6;
    // Interrupt Source: Port 8.3 interrupt; Interrupt Flag: P8IFG3
    static const uint32_t P8IV_P8IV__P8IV_8 = 8;
    // Interrupt Source: Port 8.4 interrupt; Interrupt Flag: P8IFG4
    static const uint32_t P8IV_P8IV__P8IV_10 = 10;
    // Interrupt Source: Port 8.5 interrupt; Interrupt Flag: P8IFG5
    static const uint32_t P8IV_P8IV__P8IV_12 = 12;
    // Interrupt Source: Port 8.6 interrupt; Interrupt Flag: P8IFG6
    static const uint32_t P8IV_P8IV__P8IV_14 = 14;
    // Interrupt Source: Port 8.7 interrupt; Interrupt Flag: P8IFG7; Interrupt Priority: Lowest
    static const uint32_t P8IV_P8IV__P8IV_16 = 16;

    // Port E Input
    // Reset value: 0x00000000
    BEGIN_TYPE(PEIN_t, uint16_t)
        // Port 9 Input
        ADD_BITFIELD_RO(P9IN, 0, 8)
        // Port 10 Input
        ADD_BITFIELD_RO(P10IN, 8, 8)
    END_TYPE()

    // Port E Output
    // Reset value: 0x00000000
    BEGIN_TYPE(PEOUT_t, uint16_t)
        // Port 9 Output
        ADD_BITFIELD_RW(P9OUT, 0, 8)
        // Port 10 Output
        ADD_BITFIELD_RW(P10OUT, 8, 8)
    END_TYPE()

    // Port E Direction
    // Reset value: 0x00000000
    BEGIN_TYPE(PEDIR_t, uint16_t)
        // Port 9 Direction
        ADD_BITFIELD_RW(P9DIR, 0, 8)
        // Port 10 Direction
        ADD_BITFIELD_RW(P10DIR, 8, 8)
    END_TYPE()

    // Port E Resistor Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(PEREN_t, uint16_t)
        // Port 9 Resistor Enable
        ADD_BITFIELD_RW(P9REN, 0, 8)
        // Port 10 Resistor Enable
        ADD_BITFIELD_RW(P10REN, 8, 8)
    END_TYPE()

    // Port E Drive Strength
    BEGIN_TYPE(PEDS_t, uint16_t)
        // Port 9 Drive Strength
        ADD_BITFIELD_RW(P9DS, 0, 8)
        // Port 10 Drive Strength
        ADD_BITFIELD_RW(P10DS, 8, 8)
    END_TYPE()

    // Port E Select 0
    // Reset value: 0x00000000
    BEGIN_TYPE(PESEL0_t, uint16_t)
        // Port 9 Select 0
        ADD_BITFIELD_RW(P9SEL0, 0, 8)
        // Port 10 Select 0
        ADD_BITFIELD_RW(P10SEL0, 8, 8)
    END_TYPE()

    // Port E Select 1
    // Reset value: 0x00000000
    BEGIN_TYPE(PESEL1_t, uint16_t)
        // Port 9 Select 1
        ADD_BITFIELD_RW(P9SEL1, 0, 8)
        // Port 10 Select 1
        ADD_BITFIELD_RW(P10SEL1, 8, 8)
    END_TYPE()

    // Port 9 Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(P9IV_t, uint16_t)
        // Port 9 interrupt vector value
        ADD_BITFIELD_RO(P9IV, 0, 5)
    END_TYPE()

    // No interrupt pending
    static const uint32_t P9IV_P9IV__P9IV_0 = 0;
    // Interrupt Source: Port 9.0 interrupt; Interrupt Flag: P9IFG0; Interrupt Priority: Highest
    static const uint32_t P9IV_P9IV__P9IV_2 = 2;
    // Interrupt Source: Port 9.1 interrupt; Interrupt Flag: P9IFG1
    static const uint32_t P9IV_P9IV__P9IV_4 = 4;
    // Interrupt Source: Port 9.2 interrupt; Interrupt Flag: P9IFG2
    static const uint32_t P9IV_P9IV__P9IV_6 = 6;
    // Interrupt Source: Port 9.3 interrupt; Interrupt Flag: P9IFG3
    static const uint32_t P9IV_P9IV__P9IV_8 = 8;
    // Interrupt Source: Port 9.4 interrupt; Interrupt Flag: P9IFG4
    static const uint32_t P9IV_P9IV__P9IV_10 = 10;
    // Interrupt Source: Port 9.5 interrupt; Interrupt Flag: P9IFG5
    static const uint32_t P9IV_P9IV__P9IV_12 = 12;
    // Interrupt Source: Port 9.6 interrupt; Interrupt Flag: P9IFG6
    static const uint32_t P9IV_P9IV__P9IV_14 = 14;
    // Interrupt Source: Port 9.7 interrupt; Interrupt Flag: P9IFG7; Interrupt Priority: Lowest
    static const uint32_t P9IV_P9IV__P9IV_16 = 16;

    // Port E Complement Select
    // Reset value: 0x00000000
    BEGIN_TYPE(PESELC_t, uint16_t)
        // Port 9 Complement Select
        ADD_BITFIELD_RW(P9SELC, 0, 8)
        // Port 10 Complement Select
        ADD_BITFIELD_RW(P10SELC, 8, 8)
    END_TYPE()

    // Port E Interrupt Edge Select
    // Reset value: 0x00000000
    BEGIN_TYPE(PEIES_t, uint16_t)
        // Port 9 Interrupt Edge Select
        ADD_BITFIELD_RW(P9IES, 0, 8)
        // Port 10 Interrupt Edge Select
        ADD_BITFIELD_RW(P10IES, 8, 8)
    END_TYPE()

    // Port E Interrupt Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(PEIE_t, uint16_t)
        // Port 9 Interrupt Enable
        ADD_BITFIELD_RW(P9IE, 0, 8)
        // Port 10 Interrupt Enable
        ADD_BITFIELD_RW(P10IE, 8, 8)
    END_TYPE()

    // Port E Interrupt Flag
    // Reset value: 0x00000000
    BEGIN_TYPE(PEIFG_t, uint16_t)
        // Port 9 Interrupt Flag
        ADD_BITFIELD_RW(P9IFG, 0, 8)
        // Port 10 Interrupt Flag
        ADD_BITFIELD_RW(P10IFG, 8, 8)
    END_TYPE()

    // Port 10 Interrupt Vector Register
    BEGIN_TYPE(P10IV_t, uint16_t)
        // Port 10 interrupt vector value
        ADD_BITFIELD_RO(P10IV, 0, 5)
    END_TYPE()

    // No interrupt pending
    static const uint32_t P10IV_P10IV__P10IV_0 = 0;
    // Interrupt Source: Port 10.0 interrupt; Interrupt Flag: P10IFG0; Interrupt Priority: Highest
    static const uint32_t P10IV_P10IV__P10IV_2 = 2;
    // Interrupt Source: Port 10.1 interrupt; Interrupt Flag: P10IFG1
    static const uint32_t P10IV_P10IV__P10IV_4 = 4;
    // Interrupt Source: Port 10.2 interrupt; Interrupt Flag: P10IFG2
    static const uint32_t P10IV_P10IV__P10IV_6 = 6;
    // Interrupt Source: Port 10.3 interrupt; Interrupt Flag: P10IFG3
    static const uint32_t P10IV_P10IV__P10IV_8 = 8;
    // Interrupt Source: Port 10.4 interrupt; Interrupt Flag: P10IFG4
    static const uint32_t P10IV_P10IV__P10IV_10 = 10;
    // Interrupt Source: Port 10.5 interrupt; Interrupt Flag: P10IFG5
    static const uint32_t P10IV_P10IV__P10IV_12 = 12;
    // Interrupt Source: Port 10.6 interrupt; Interrupt Flag: P10IFG6
    static const uint32_t P10IV_P10IV__P10IV_14 = 14;
    // Interrupt Source: Port 10.7 interrupt; Interrupt Flag: P10IFG7; Interrupt Priority: Lowest
    static const uint32_t P10IV_P10IV__P10IV_16 = 16;

    // Port J Input
    // Reset value: 0x00000000
    BEGIN_TYPE(PJIN_t, uint16_t)
        // Port J Input
        ADD_BITFIELD_RO(PJIN, 0, 16)
    END_TYPE()

    // Port J Output
    // Reset value: 0x00000000
    BEGIN_TYPE(PJOUT_t, uint16_t)
        // Port J Output
        ADD_BITFIELD_RW(PJOUT, 0, 16)
    END_TYPE()

    // Port J Direction
    // Reset value: 0x00000000
    BEGIN_TYPE(PJDIR_t, uint16_t)
        // Port J Direction
        ADD_BITFIELD_RW(PJDIR, 0, 16)
    END_TYPE()

    // Port J Resistor Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(PJREN_t, uint16_t)
        // Port J Resistor Enable
        ADD_BITFIELD_RW(PJREN, 0, 16)
    END_TYPE()

    // Port J Drive Strength
    BEGIN_TYPE(PJDS_t, uint16_t)
        // Port J Drive Strength
        ADD_BITFIELD_RW(PJDS, 0, 16)
    END_TYPE()

    // Port J Select 0
    // Reset value: 0x00000000
    BEGIN_TYPE(PJSEL0_t, uint16_t)
        // Port J Select 0
        ADD_BITFIELD_RW(PJSEL0, 0, 16)
    END_TYPE()

    // Port J Select 1
    // Reset value: 0x00000000
    BEGIN_TYPE(PJSEL1_t, uint16_t)
        // Port J Select 1
        ADD_BITFIELD_RW(PJSEL1, 0, 16)
    END_TYPE()

    // Port J Complement Select
    // Reset value: 0x00000000
    BEGIN_TYPE(PJSELC_t, uint16_t)
        // Port J Complement Select
        ADD_BITFIELD_RW(PJSELC, 0, 16)
    END_TYPE()

    struct DIO_t {
        PAIN_t                        PAIN;
        PAOUT_t                       PAOUT;
        PADIR_t                       PADIR;
        PAREN_t                       PAREN;
        PADS_t                        PADS;
        PASEL0_t                      PASEL0;
        PASEL1_t                      PASEL1;
        P1IV_t                        P1IV;
        uint16_t                      reserved0[3];
        PASELC_t                      PASELC;
        PAIES_t                       PAIES;
        PAIE_t                        PAIE;
        PAIFG_t                       PAIFG;
        P2IV_t                        P2IV;
        PBIN_t                        PBIN;
        PBOUT_t                       PBOUT;
        PBDIR_t                       PBDIR;
        PBREN_t                       PBREN;
        PBDS_t                        PBDS;
        PBSEL0_t                      PBSEL0;
        PBSEL1_t                      PBSEL1;
        P3IV_t                        P3IV;
        uint16_t                      reserved1[3];
        PBSELC_t                      PBSELC;
        PBIES_t                       PBIES;
        PBIE_t                        PBIE;
        PBIFG_t                       PBIFG;
        P4IV_t                        P4IV;
        PCIN_t                        PCIN;
        PCOUT_t                       PCOUT;
        PCDIR_t                       PCDIR;
        PCREN_t                       PCREN;
        PCDS_t                        PCDS;
        PCSEL0_t                      PCSEL0;
        PCSEL1_t                      PCSEL1;
        P5IV_t                        P5IV;
        uint16_t                      reserved2[3];
        PCSELC_t                      PCSELC;
        PCIES_t                       PCIES;
        PCIE_t                        PCIE;
        PCIFG_t                       PCIFG;
        P6IV_t                        P6IV;
        PDIN_t                        PDIN;
        PDOUT_t                       PDOUT;
        PDDIR_t                       PDDIR;
        PDREN_t                       PDREN;
        PDDS_t                        PDDS;
        PDSEL0_t                      PDSEL0;
        PDSEL1_t                      PDSEL1;
        P7IV_t                        P7IV;
        uint16_t                      reserved3[3];
        PDSELC_t                      PDSELC;
        PDIES_t                       PDIES;
        PDIE_t                        PDIE;
        PDIFG_t                       PDIFG;
        P8IV_t                        P8IV;
        PEIN_t                        PEIN;
        PEOUT_t                       PEOUT;
        PEDIR_t                       PEDIR;
        PEREN_t                       PEREN;
        PEDS_t                        PEDS;
        PESEL0_t                      PESEL0;
        PESEL1_t                      PESEL1;
        P9IV_t                        P9IV;
        uint16_t                      reserved4[3];
        PESELC_t                      PESELC;
        PEIES_t                       PEIES;
        PEIE_t                        PEIE;
        PEIFG_t                       PEIFG;
        P10IV_t                       P10IV;
        uint16_t                      reserved5[64];
        PJIN_t                        PJIN;
        PJOUT_t                       PJOUT;
        PJDIR_t                       PJDIR;
        PJREN_t                       PJREN;
        PJDS_t                        PJDS;
        PJSEL0_t                      PJSEL0;
        PJSEL1_t                      PJSEL1;
        uint16_t                      reserved6[4];
        PJSELC_t                      PJSELC;
    };

    static DIO_t & DIO     = (*(DIO_t *)0x40004c00);

} // _DIO_

// PMAP
namespace _PMAP_  {

    // Port Mapping Key Register
    // Reset value: 0x000096a5
    BEGIN_TYPE(PMAPKEYID_t, uint16_t)
        // Port mapping controller write access key
        ADD_BITFIELD_RW(PMAPKEY, 0, 16)
    END_TYPE()

    // Port Mapping Control Register
    // Reset value: 0x00000001
    BEGIN_TYPE(PMAPCTL_t, uint16_t)
        // Port mapping lock bit
        ADD_BITFIELD_RO(PMAPLOCKED, 0, 1)
        // Port mapping reconfiguration control bit
        ADD_BITFIELD_RW(PMAPRECFG, 1, 1)
    END_TYPE()

    // Access to mapping registers is granted
    static const uint32_t PMAPCTL_PMAPLOCKED__PMAPLOCKED_0 = 0;
    // Access to mapping registers is locked
    static const uint32_t PMAPCTL_PMAPLOCKED__PMAPLOCKED_1 = 1;
    // Configuration allowed only once
    static const uint32_t PMAPCTL_PMAPRECFG__PMAPRECFG_0 = 0;
    // Allow reconfiguration of port mapping
    static const uint32_t PMAPCTL_PMAPRECFG__PMAPRECFG_1 = 1;

    // Port mapping register, P1.0 and P1.1
    BEGIN_TYPE(P1MAP01_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P1.2 and P1.3
    BEGIN_TYPE(P1MAP23_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P1.4 and P1.5
    BEGIN_TYPE(P1MAP45_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P1.6 and P1.7
    BEGIN_TYPE(P1MAP67_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P2.0 and P2.1
    BEGIN_TYPE(P2MAP01_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P2.2 and P2.3
    BEGIN_TYPE(P2MAP23_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P2.4 and P2.5
    BEGIN_TYPE(P2MAP45_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P2.6 and P2.7
    BEGIN_TYPE(P2MAP67_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P3.0 and P3.1
    BEGIN_TYPE(P3MAP01_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P3.2 and P3.3
    BEGIN_TYPE(P3MAP23_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P3.4 and P3.5
    BEGIN_TYPE(P3MAP45_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P3.6 and P3.7
    BEGIN_TYPE(P3MAP67_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P4.0 and P4.1
    BEGIN_TYPE(P4MAP01_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P4.2 and P4.3
    BEGIN_TYPE(P4MAP23_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P4.4 and P4.5
    BEGIN_TYPE(P4MAP45_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P4.6 and P4.7
    BEGIN_TYPE(P4MAP67_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P5.0 and P5.1
    BEGIN_TYPE(P5MAP01_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P5.2 and P5.3
    BEGIN_TYPE(P5MAP23_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P5.4 and P5.5
    BEGIN_TYPE(P5MAP45_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P5.6 and P5.7
    BEGIN_TYPE(P5MAP67_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P6.0 and P6.1
    BEGIN_TYPE(P6MAP01_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P6.2 and P6.3
    BEGIN_TYPE(P6MAP23_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P6.4 and P6.5
    BEGIN_TYPE(P6MAP45_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P6.6 and P6.7
    BEGIN_TYPE(P6MAP67_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P7.0 and P7.1
    BEGIN_TYPE(P7MAP01_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P7.2 and P7.3
    BEGIN_TYPE(P7MAP23_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P7.4 and P7.5
    BEGIN_TYPE(P7MAP45_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    // Port mapping register, P7.6 and P7.7
    BEGIN_TYPE(P7MAP67_t, uint16_t)
        // Selects secondary port function
        ADD_BITFIELD_RW(PMAPx, 0, 16)
    END_TYPE()

    struct PMAP_t {
        PMAPKEYID_t                   PMAPKEYID;
        PMAPCTL_t                     PMAPCTL;
        uint16_t                      reserved0[2];
        P1MAP01_t                     P1MAP01;
        P1MAP23_t                     P1MAP23;
        P1MAP45_t                     P1MAP45;
        P1MAP67_t                     P1MAP67;
        P2MAP01_t                     P2MAP01;
        P2MAP23_t                     P2MAP23;
        P2MAP45_t                     P2MAP45;
        P2MAP67_t                     P2MAP67;
        P3MAP01_t                     P3MAP01;
        P3MAP23_t                     P3MAP23;
        P3MAP45_t                     P3MAP45;
        P3MAP67_t                     P3MAP67;
        P4MAP01_t                     P4MAP01;
        P4MAP23_t                     P4MAP23;
        P4MAP45_t                     P4MAP45;
        P4MAP67_t                     P4MAP67;
        P5MAP01_t                     P5MAP01;
        P5MAP23_t                     P5MAP23;
        P5MAP45_t                     P5MAP45;
        P5MAP67_t                     P5MAP67;
        P6MAP01_t                     P6MAP01;
        P6MAP23_t                     P6MAP23;
        P6MAP45_t                     P6MAP45;
        P6MAP67_t                     P6MAP67;
        P7MAP01_t                     P7MAP01;
        P7MAP23_t                     P7MAP23;
        P7MAP45_t                     P7MAP45;
        P7MAP67_t                     P7MAP67;
    };

    static PMAP_t & PMAP     = (*(PMAP_t *)0x40005000);

} // _PMAP_

// CAPTIO0
namespace _CAPTIO0_  {

    // Capacitive Touch IO x Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(CAPTIOxCTL_t, uint16_t)
        // Capacitive Touch IO pin select
        ADD_BITFIELD_RW(CAPTIOPISELx, 1, 3)
        // Capacitive Touch IO port select
        ADD_BITFIELD_RW(CAPTIOPOSELx, 4, 4)
        // Capacitive Touch IO enable
        ADD_BITFIELD_RW(CAPTIOEN, 8, 1)
        // Capacitive Touch IO state
        ADD_BITFIELD_RO(CAPTIOSTATE, 9, 1)
    END_TYPE()

    // Px.0
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_0 = 0;
    // Px.1
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_1 = 1;
    // Px.2
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_2 = 2;
    // Px.3
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_3 = 3;
    // Px.4
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_4 = 4;
    // Px.5
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_5 = 5;
    // Px.6
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_6 = 6;
    // Px.7
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_7 = 7;
    // Px = PJ
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_0 = 0;
    // Px = P1
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_1 = 1;
    // Px = P2
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_2 = 2;
    // Px = P3
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_3 = 3;
    // Px = P4
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_4 = 4;
    // Px = P5
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_5 = 5;
    // Px = P6
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_6 = 6;
    // Px = P7
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_7 = 7;
    // Px = P8
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_8 = 8;
    // Px = P9
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_9 = 9;
    // Px = P10
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_10 = 10;
    // Px = P11
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_11 = 11;
    // Px = P12
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_12 = 12;
    // Px = P13
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_13 = 13;
    // Px = P14
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_14 = 14;
    // Px = P15
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_15 = 15;
    // All Capacitive Touch IOs are disabled. Signal towards timers is 0.
    static const uint32_t CAPTIOxCTL_CAPTIOEN__CAPTIOEN_0 = 0;
    // Selected Capacitive Touch IO is enabled
    static const uint32_t CAPTIOxCTL_CAPTIOEN__CAPTIOEN_1 = 1;
    // Curent state 0 or Capacitive Touch IO is disabled
    static const uint32_t CAPTIOxCTL_CAPTIOSTATE__CAPTIOSTATE_0 = 0;
    // Current state 1
    static const uint32_t CAPTIOxCTL_CAPTIOSTATE__CAPTIOSTATE_1 = 1;

    struct CAPTIO0_t {
        uint16_t                      reserved0[7];
        CAPTIOxCTL_t                  CAPTIOxCTL;
    };

    static CAPTIO0_t & CAPTIO0     = (*(CAPTIO0_t *)0x40005400);

} // _CAPTIO0_

// CAPTIO1
namespace _CAPTIO1_  {

    // Capacitive Touch IO x Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(CAPTIOxCTL_t, uint16_t)
        // Capacitive Touch IO pin select
        ADD_BITFIELD_RW(CAPTIOPISELx, 1, 3)
        // Capacitive Touch IO port select
        ADD_BITFIELD_RW(CAPTIOPOSELx, 4, 4)
        // Capacitive Touch IO enable
        ADD_BITFIELD_RW(CAPTIOEN, 8, 1)
        // Capacitive Touch IO state
        ADD_BITFIELD_RO(CAPTIOSTATE, 9, 1)
    END_TYPE()

    // Px.0
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_0 = 0;
    // Px.1
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_1 = 1;
    // Px.2
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_2 = 2;
    // Px.3
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_3 = 3;
    // Px.4
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_4 = 4;
    // Px.5
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_5 = 5;
    // Px.6
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_6 = 6;
    // Px.7
    static const uint32_t CAPTIOxCTL_CAPTIOPISELx__CAPTIOPISELx_7 = 7;
    // Px = PJ
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_0 = 0;
    // Px = P1
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_1 = 1;
    // Px = P2
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_2 = 2;
    // Px = P3
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_3 = 3;
    // Px = P4
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_4 = 4;
    // Px = P5
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_5 = 5;
    // Px = P6
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_6 = 6;
    // Px = P7
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_7 = 7;
    // Px = P8
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_8 = 8;
    // Px = P9
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_9 = 9;
    // Px = P10
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_10 = 10;
    // Px = P11
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_11 = 11;
    // Px = P12
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_12 = 12;
    // Px = P13
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_13 = 13;
    // Px = P14
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_14 = 14;
    // Px = P15
    static const uint32_t CAPTIOxCTL_CAPTIOPOSELx__CAPTIOPOSELx_15 = 15;
    // All Capacitive Touch IOs are disabled. Signal towards timers is 0.
    static const uint32_t CAPTIOxCTL_CAPTIOEN__CAPTIOEN_0 = 0;
    // Selected Capacitive Touch IO is enabled
    static const uint32_t CAPTIOxCTL_CAPTIOEN__CAPTIOEN_1 = 1;
    // Curent state 0 or Capacitive Touch IO is disabled
    static const uint32_t CAPTIOxCTL_CAPTIOSTATE__CAPTIOSTATE_0 = 0;
    // Current state 1
    static const uint32_t CAPTIOxCTL_CAPTIOSTATE__CAPTIOSTATE_1 = 1;

    struct CAPTIO1_t {
        uint16_t                      reserved0[7];
        CAPTIOxCTL_t                  CAPTIOxCTL;
    };

    static CAPTIO1_t & CAPTIO1     = (*(CAPTIO1_t *)0x40005800);

} // _CAPTIO1_

// TIMER32
namespace _TIMER32_  {

    // Timer 1 Load Register
    // Reset value: 0x00000000
    BEGIN_TYPE(T32LOAD1_t, uint32_t)
        // The value from which the Timer 1 counter decrements
        ADD_BITFIELD_RW(LOAD, 0, 32)
    END_TYPE()

    // Timer 1 Current Value Register
    // Reset value: 0xffffffff
    BEGIN_TYPE(T32VALUE1_t, uint32_t)
        // Current value
        ADD_BITFIELD_RO(VALUE, 0, 32)
    END_TYPE()

    // Timer 1 Timer Control Register
    // Reset value: 0x00000020
    BEGIN_TYPE(T32CONTROL1_t, uint32_t)
        // Selects one-shot or wrapping counter mode
        ADD_BITFIELD_RW(ONESHOT, 0, 1)
        // Selects 16 or 32 bit counter operation
        ADD_BITFIELD_RW(SIZE, 1, 1)
        // Prescale bits
        ADD_BITFIELD_RW(PRESCALE, 2, 2)
        // Interrupt enable bit
        ADD_BITFIELD_RW(IE, 5, 1)
        // Mode bit
        ADD_BITFIELD_RW(MODE, 6, 1)
        // Enable bit
        ADD_BITFIELD_RW(ENABLE, 7, 1)
    END_TYPE()

    // wrapping mode
    static const uint32_t T32CONTROL1_ONESHOT__ONESHOT_0 = 0;
    // one-shot mode
    static const uint32_t T32CONTROL1_ONESHOT__ONESHOT_1 = 1;
    // 16-bit counter
    static const uint32_t T32CONTROL1_SIZE__SIZE_0 = 0;
    // 32-bit counter
    static const uint32_t T32CONTROL1_SIZE__SIZE_1 = 1;
    // 0 stages of prescale, clock is divided by 1
    static const uint32_t T32CONTROL1_PRESCALE__PRESCALE_0 = 0;
    // 4 stages of prescale, clock is divided by 16
    static const uint32_t T32CONTROL1_PRESCALE__PRESCALE_1 = 1;
    // 8 stages of prescale, clock is divided by 256
    static const uint32_t T32CONTROL1_PRESCALE__PRESCALE_2 = 2;
    // Timer interrupt disabled
    static const uint32_t T32CONTROL1_IE__IE_0 = 0;
    // Timer interrupt enabled
    static const uint32_t T32CONTROL1_IE__IE_1 = 1;
    // Timer is in free-running mode
    static const uint32_t T32CONTROL1_MODE__MODE_0 = 0;
    // Timer is in periodic mode
    static const uint32_t T32CONTROL1_MODE__MODE_1 = 1;
    // Timer disabled
    static const uint32_t T32CONTROL1_ENABLE__ENABLE_0 = 0;
    // Timer enabled
    static const uint32_t T32CONTROL1_ENABLE__ENABLE_1 = 1;

    // Timer 1 Interrupt Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(T32INTCLR1_t, uint32_t)
        // Write clears interrupt output
        ADD_BITFIELD_WO(INTCLR, 0, 32)
    END_TYPE()

    // Timer 1 Raw Interrupt Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(T32RIS1_t, uint32_t)
        // Raw interrupt status
        ADD_BITFIELD_RO(RAW_IFG, 0, 1)
    END_TYPE()

    // Timer 1 Interrupt Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(T32MIS1_t, uint32_t)
        // Enabled interrupt status
        ADD_BITFIELD_RO(IFG, 0, 1)
    END_TYPE()

    // Timer 1 Background Load Register
    // Reset value: 0x00000000
    BEGIN_TYPE(T32BGLOAD1_t, uint32_t)
        // Value from which the counter decrements
        ADD_BITFIELD_RW(BGLOAD, 0, 32)
    END_TYPE()

    // Timer 2 Load Register
    // Reset value: 0x00000000
    BEGIN_TYPE(T32LOAD2_t, uint32_t)
        // The value from which the Timer 2 counter decrements
        ADD_BITFIELD_RW(LOAD, 0, 32)
    END_TYPE()

    // Timer 2 Current Value Register
    // Reset value: 0xffffffff
    BEGIN_TYPE(T32VALUE2_t, uint32_t)
        // Current value of the decrementing counter
        ADD_BITFIELD_RO(VALUE, 0, 32)
    END_TYPE()

    // Timer 2 Timer Control Register
    // Reset value: 0x00000020
    BEGIN_TYPE(T32CONTROL2_t, uint32_t)
        // Selects one-shot or wrapping counter mode
        ADD_BITFIELD_RW(ONESHOT, 0, 1)
        // Selects 16 or 32 bit counter operation
        ADD_BITFIELD_RW(SIZE, 1, 1)
        // Prescale bits
        ADD_BITFIELD_RW(PRESCALE, 2, 2)
        // Interrupt enable bit
        ADD_BITFIELD_RW(IE, 5, 1)
        // Mode bit
        ADD_BITFIELD_RW(MODE, 6, 1)
        // Enable bit
        ADD_BITFIELD_RW(ENABLE, 7, 1)
    END_TYPE()

    // wrapping mode
    static const uint32_t T32CONTROL2_ONESHOT__ONESHOT_0 = 0;
    // one-shot mode
    static const uint32_t T32CONTROL2_ONESHOT__ONESHOT_1 = 1;
    // 16-bit counter
    static const uint32_t T32CONTROL2_SIZE__SIZE_0 = 0;
    // 32-bit counter
    static const uint32_t T32CONTROL2_SIZE__SIZE_1 = 1;
    // 0 stages of prescale, clock is divided by 1
    static const uint32_t T32CONTROL2_PRESCALE__PRESCALE_0 = 0;
    // 4 stages of prescale, clock is divided by 16
    static const uint32_t T32CONTROL2_PRESCALE__PRESCALE_1 = 1;
    // 8 stages of prescale, clock is divided by 256
    static const uint32_t T32CONTROL2_PRESCALE__PRESCALE_2 = 2;
    // Timer interrupt disabled
    static const uint32_t T32CONTROL2_IE__IE_0 = 0;
    // Timer interrupt enabled
    static const uint32_t T32CONTROL2_IE__IE_1 = 1;
    // Timer is in free-running mode
    static const uint32_t T32CONTROL2_MODE__MODE_0 = 0;
    // Timer is in periodic mode
    static const uint32_t T32CONTROL2_MODE__MODE_1 = 1;
    // Timer disabled
    static const uint32_t T32CONTROL2_ENABLE__ENABLE_0 = 0;
    // Timer enabled
    static const uint32_t T32CONTROL2_ENABLE__ENABLE_1 = 1;

    // Timer 2 Interrupt Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(T32INTCLR2_t, uint32_t)
        // Write clears the interrupt output
        ADD_BITFIELD_WO(INTCLR, 0, 32)
    END_TYPE()

    // Timer 2 Raw Interrupt Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(T32RIS2_t, uint32_t)
        // Raw interrupt status
        ADD_BITFIELD_RO(RAW_IFG, 0, 1)
    END_TYPE()

    // Timer 2 Interrupt Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(T32MIS2_t, uint32_t)
        // Enabled interrupt status
        ADD_BITFIELD_RO(IFG, 0, 1)
    END_TYPE()

    // Timer 2 Background Load Register
    // Reset value: 0x00000000
    BEGIN_TYPE(T32BGLOAD2_t, uint32_t)
        // Value from which the counter decrements
        ADD_BITFIELD_RW(BGLOAD, 0, 32)
    END_TYPE()

    struct TIMER32_t {
        T32LOAD1_t                    T32LOAD1;
        T32VALUE1_t                   T32VALUE1;
        T32CONTROL1_t                 T32CONTROL1;
        T32INTCLR1_t                  T32INTCLR1;
        T32RIS1_t                     T32RIS1;
        T32MIS1_t                     T32MIS1;
        T32BGLOAD1_t                  T32BGLOAD1;
        uint32_t                      reserved0;
        T32LOAD2_t                    T32LOAD2;
        T32VALUE2_t                   T32VALUE2;
        T32CONTROL2_t                 T32CONTROL2;
        T32INTCLR2_t                  T32INTCLR2;
        T32RIS2_t                     T32RIS2;
        T32MIS2_t                     T32MIS2;
        T32BGLOAD2_t                  T32BGLOAD2;
    };

    static TIMER32_t & TIMER32     = (*(TIMER32_t *)0x4000c000);

} // _TIMER32_

// DMA
namespace _DMA_  {

    // Device Configuration Status
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_DEVICE_CFG_t, uint32_t)
        // Number of DMA channels available
        ADD_BITFIELD_RO(NUM_DMA_CHANNELS, 0, 8)
        // Number of DMA sources per channel
        ADD_BITFIELD_RO(NUM_SRC_PER_CHANNEL, 8, 8)
    END_TYPE()

    // Software Channel Trigger Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_SW_CHTRIG_t, uint32_t)
        // Write 1, triggers DMA_CHANNEL0
        ADD_BITFIELD_RW(CH0, 0, 1)
        // Write 1, triggers DMA_CHANNEL1
        ADD_BITFIELD_RW(CH1, 1, 1)
        // Write 1, triggers DMA_CHANNEL2
        ADD_BITFIELD_RW(CH2, 2, 1)
        // Write 1, triggers DMA_CHANNEL3
        ADD_BITFIELD_RW(CH3, 3, 1)
        // Write 1, triggers DMA_CHANNEL4
        ADD_BITFIELD_RW(CH4, 4, 1)
        // Write 1, triggers DMA_CHANNEL5
        ADD_BITFIELD_RW(CH5, 5, 1)
        // Write 1, triggers DMA_CHANNEL6
        ADD_BITFIELD_RW(CH6, 6, 1)
        // Write 1, triggers DMA_CHANNEL7
        ADD_BITFIELD_RW(CH7, 7, 1)
        // Write 1, triggers DMA_CHANNEL8
        ADD_BITFIELD_RW(CH8, 8, 1)
        // Write 1, triggers DMA_CHANNEL9
        ADD_BITFIELD_RW(CH9, 9, 1)
        // Write 1, triggers DMA_CHANNEL10
        ADD_BITFIELD_RW(CH10, 10, 1)
        // Write 1, triggers DMA_CHANNEL11
        ADD_BITFIELD_RW(CH11, 11, 1)
        // Write 1, triggers DMA_CHANNEL12
        ADD_BITFIELD_RW(CH12, 12, 1)
        // Write 1, triggers DMA_CHANNEL13
        ADD_BITFIELD_RW(CH13, 13, 1)
        // Write 1, triggers DMA_CHANNEL14
        ADD_BITFIELD_RW(CH14, 14, 1)
        // Write 1, triggers DMA_CHANNEL15
        ADD_BITFIELD_RW(CH15, 15, 1)
        // Write 1, triggers DMA_CHANNEL16
        ADD_BITFIELD_RW(CH16, 16, 1)
        // Write 1, triggers DMA_CHANNEL17
        ADD_BITFIELD_RW(CH17, 17, 1)
        // Write 1, triggers DMA_CHANNEL18
        ADD_BITFIELD_RW(CH18, 18, 1)
        // Write 1, triggers DMA_CHANNEL19
        ADD_BITFIELD_RW(CH19, 19, 1)
        // Write 1, triggers DMA_CHANNEL20
        ADD_BITFIELD_RW(CH20, 20, 1)
        // Write 1, triggers DMA_CHANNEL21
        ADD_BITFIELD_RW(CH21, 21, 1)
        // Write 1, triggers DMA_CHANNEL22
        ADD_BITFIELD_RW(CH22, 22, 1)
        // Write 1, triggers DMA_CHANNEL23
        ADD_BITFIELD_RW(CH23, 23, 1)
        // Write 1, triggers DMA_CHANNEL24
        ADD_BITFIELD_RW(CH24, 24, 1)
        // Write 1, triggers DMA_CHANNEL25
        ADD_BITFIELD_RW(CH25, 25, 1)
        // Write 1, triggers DMA_CHANNEL26
        ADD_BITFIELD_RW(CH26, 26, 1)
        // Write 1, triggers DMA_CHANNEL27
        ADD_BITFIELD_RW(CH27, 27, 1)
        // Write 1, triggers DMA_CHANNEL28
        ADD_BITFIELD_RW(CH28, 28, 1)
        // Write 1, triggers DMA_CHANNEL29
        ADD_BITFIELD_RW(CH29, 29, 1)
        // Write 1, triggers DMA_CHANNEL30
        ADD_BITFIELD_RW(CH30, 30, 1)
        // Write 1, triggers DMA_CHANNEL31
        ADD_BITFIELD_RW(CH31, 31, 1)
    END_TYPE()

    // Channel n Source Configuration Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_CH_SRCCFG_t, uint32_t)
        // Device level DMA source mapping to channel input
        ADD_BITFIELD_RW(DMA_SRC, 0, 8)
    END_TYPE()

    // Interrupt 1 Source Channel Configuration
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_INT1_SRCCFG_t, uint32_t)
        // Controls which channel's completion event is mapped as a source of this Interrupt
        ADD_BITFIELD_RW(INT_SRC, 0, 5)
        // Enables DMA_INT1 mapping
        ADD_BITFIELD_RW(EN, 5, 1)
    END_TYPE()

    // Interrupt 2 Source Channel Configuration Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_INT2_SRCCFG_t, uint32_t)
        // Controls which channel's completion event is mapped as a source of this Interrupt
        ADD_BITFIELD_RW(INT_SRC, 0, 5)
        // Enables DMA_INT2 mapping
        ADD_BITFIELD_RW(EN, 5, 1)
    END_TYPE()

    // Interrupt 3 Source Channel Configuration Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_INT3_SRCCFG_t, uint32_t)
        // Controls which channel's completion event is mapped as a source of this Interrupt
        ADD_BITFIELD_RW(INT_SRC, 0, 5)
        // Enables DMA_INT3 mapping
        ADD_BITFIELD_RW(EN, 5, 1)
    END_TYPE()

    // Interrupt 0 Source Channel Flag Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_INT0_SRCFLG_t, uint32_t)
        // Channel 0 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH0, 0, 1)
        // Channel 1 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH1, 1, 1)
        // Channel 2 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH2, 2, 1)
        // Channel 3 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH3, 3, 1)
        // Channel 4 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH4, 4, 1)
        // Channel 5 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH5, 5, 1)
        // Channel 6 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH6, 6, 1)
        // Channel 7 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH7, 7, 1)
        // Channel 8 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH8, 8, 1)
        // Channel 9 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH9, 9, 1)
        // Channel 10 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH10, 10, 1)
        // Channel 11 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH11, 11, 1)
        // Channel 12 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH12, 12, 1)
        // Channel 13 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH13, 13, 1)
        // Channel 14 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH14, 14, 1)
        // Channel 15 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH15, 15, 1)
        // Channel 16 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH16, 16, 1)
        // Channel 17 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH17, 17, 1)
        // Channel 18 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH18, 18, 1)
        // Channel 19 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH19, 19, 1)
        // Channel 20 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH20, 20, 1)
        // Channel 21 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH21, 21, 1)
        // Channel 22 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH22, 22, 1)
        // Channel 23 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH23, 23, 1)
        // Channel 24 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH24, 24, 1)
        // Channel 25 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH25, 25, 1)
        // Channel 26 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH26, 26, 1)
        // Channel 27 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH27, 27, 1)
        // Channel 28 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH28, 28, 1)
        // Channel 29 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH29, 29, 1)
        // Channel 30 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH30, 30, 1)
        // Channel 31 was the source of DMA_INT0
        ADD_BITFIELD_RO(CH31, 31, 1)
    END_TYPE()

    // Interrupt 0 Source Channel Clear Flag Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_INT0_CLRFLG_t, uint32_t)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH0, 0, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH1, 1, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH2, 2, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH3, 3, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH4, 4, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH5, 5, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH6, 6, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH7, 7, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH8, 8, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH9, 9, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH10, 10, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH11, 11, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH12, 12, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH13, 13, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH14, 14, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH15, 15, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH16, 16, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH17, 17, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH18, 18, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH19, 19, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH20, 20, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH21, 21, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH22, 22, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH23, 23, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH24, 24, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH25, 25, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH26, 26, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH27, 27, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH28, 28, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH29, 29, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH30, 30, 1)
        // Clear corresponding DMA_INT0_SRCFLG_REG
        ADD_BITFIELD_WO(CH31, 31, 1)
    END_TYPE()

    // Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_STAT_t, uint32_t)
        // Enable status of the controller
        ADD_BITFIELD_RO(MASTEN, 0, 1)
        // Current state of the control state machine. State can be one of the following:
        ADD_BITFIELD_RO(STATE, 4, 4)
        // Number of available DMA channels minus one.
        ADD_BITFIELD_RO(DMACHANS, 16, 5)
        // To reduce the gate count the controller can be configured to exclude the integration test logic. The values 2h to Fh are Reserved.
        ADD_BITFIELD_RO(TESTSTAT, 28, 4)
    END_TYPE()

    // Controller disabled
    static const uint32_t DMA_STAT_MASTEN__MASTEN_0 = 0;
    // Controller enabled
    static const uint32_t DMA_STAT_MASTEN__MASTEN_1 = 1;
    // idle
    static const uint32_t DMA_STAT_STATE__STATE_0 = 0;
    // reading channel controller data
    static const uint32_t DMA_STAT_STATE__STATE_1 = 1;
    // reading source data end pointer
    static const uint32_t DMA_STAT_STATE__STATE_2 = 2;
    // reading destination data end pointer
    static const uint32_t DMA_STAT_STATE__STATE_3 = 3;
    // reading source data
    static const uint32_t DMA_STAT_STATE__STATE_4 = 4;
    // writing destination data
    static const uint32_t DMA_STAT_STATE__STATE_5 = 5;
    // waiting for DMA request to clear
    static const uint32_t DMA_STAT_STATE__STATE_6 = 6;
    // writing channel controller data
    static const uint32_t DMA_STAT_STATE__STATE_7 = 7;
    // stalled
    static const uint32_t DMA_STAT_STATE__STATE_8 = 8;
    // done
    static const uint32_t DMA_STAT_STATE__STATE_9 = 9;
    // peripheral scatter-gather transition
    static const uint32_t DMA_STAT_STATE__STATE_10 = 10;
    // Controller configured to use 1 DMA channel
    static const uint32_t DMA_STAT_DMACHANS__DMACHANS_0 = 0;
    // Controller configured to use 2 DMA channels
    static const uint32_t DMA_STAT_DMACHANS__DMACHANS_1 = 1;
    // Controller configured to use 31 DMA channels
    static const uint32_t DMA_STAT_DMACHANS__DMACHANS_30 = 30;
    // Controller configured to use 32 DMA channels
    static const uint32_t DMA_STAT_DMACHANS__DMACHANS_31 = 31;
    // Controller does not include the integration test logic
    static const uint32_t DMA_STAT_TESTSTAT__TESTSTAT_0 = 0;
    // Controller includes the integration test logic
    static const uint32_t DMA_STAT_TESTSTAT__TESTSTAT_1 = 1;

    // Configuration Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_CFG_t, uint32_t)
        // Enable status of the controller
        ADD_BITFIELD_WO(MASTEN, 0, 1)
        // Sets the AHB-Lite protection by controlling the HPROT[3:1] signal levels as follows: Bit [7] Controls HPROT[3] to indicate if a cacheable access is occurring. Bit [6] Controls HPROT[2] to indicate if a bufferable access is occurring. Bit [5] Controls HPROT[1] to indicate if a privileged access is occurring. Note: When bit [n] = 1 then the corresponding HPROT is HIGH. When bit [n] = 0 then the corresponding HPROT is LOW.
        ADD_BITFIELD_WO(CHPROTCTRL, 5, 3)
    END_TYPE()

    // Controller disabled
    static const uint32_t DMA_CFG_MASTEN__MASTEN_0 = 0;
    // Controller enabled
    static const uint32_t DMA_CFG_MASTEN__MASTEN_1 = 1;

    // Channel Control Data Base Pointer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_CTLBASE_t, uint32_t)
        // Pointer to the base address of the primary data structure.
        ADD_BITFIELD_RW(ADDR, 5, 27)
    END_TYPE()

    // Channel Alternate Control Data Base Pointer Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_ALTBASE_t, uint32_t)
        // Base address of the alternate data structure
        ADD_BITFIELD_RO(ADDR, 0, 32)
    END_TYPE()

    // Channel Wait on Request Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_WAITSTAT_t, uint32_t)
        // Channel wait on request status.
        ADD_BITFIELD_RO(WAITREQ, 0, 32)
    END_TYPE()

    // dma_waitonreq[C] is LOW.
    static const uint32_t DMA_WAITSTAT_WAITREQ__WAITREQ_0 = 0;
    // dma_waitonreq[C] is HIGH.
    static const uint32_t DMA_WAITSTAT_WAITREQ__WAITREQ_1 = 1;

    // Channel Software Request Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_SWREQ_t, uint32_t)
        // Set the appropriate bit to generate a software DMA request on the corresponding DMA channel. Writing to a bit where a DMA channel is not implemented does not create a DMA request for that channel.
        ADD_BITFIELD_WO(CHNL_SW_REQ, 0, 32)
    END_TYPE()

    // Does not create a DMA request for the channel
    static const uint32_t DMA_SWREQ_CHNL_SW_REQ__CHNL_SW_REQ_0 = 0;
    // Creates a DMA request for the channel
    static const uint32_t DMA_SWREQ_CHNL_SW_REQ__CHNL_SW_REQ_1 = 1;

    // Channel Useburst Set Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_USEBURSTSET_t, uint32_t)
        // Returns the useburst status, or disables dma_sreq from generating DMA requests.
        ADD_BITFIELD_RW(SET, 0, 32)
    END_TYPE()

    // DMA channel C responds to requests that it receives on dma_req[C] or dma_sreq[C]. The controller performs 2R, or single, bus transfers.
    static const uint32_t DMA_USEBURSTSET_SET__SET_0_READ = 0;
    // DMA channel C does not respond to requests that it receives on dma_sreq[C]. The controller only responds to dma_req[C] requests and performs 2R transfers.
    static const uint32_t DMA_USEBURSTSET_SET__SET_1_READ = 1;

    // Channel Useburst Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_USEBURSTCLR_t, uint32_t)
        // Set the appropriate bit to enable dma_sreq to generate requests.
        ADD_BITFIELD_WO(CLR, 0, 32)
    END_TYPE()

    // No effect. Use the DMA_USEBURST_SET Register to disable dma_sreq from generating requests.
    static const uint32_t DMA_USEBURSTCLR_CLR__CLR_0 = 0;
    // Enables dma_sreq[C] to generate DMA requests. Writing to a bit where a DMA channel is not implemented has no effect.
    static const uint32_t DMA_USEBURSTCLR_CLR__CLR_1 = 1;

    // Channel Request Mask Set Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_REQMASKSET_t, uint32_t)
        // Returns the request mask status of dma_req and dma_sreq, or disables the corresponding channel from generating DMA requests.
        ADD_BITFIELD_RW(SET, 0, 32)
    END_TYPE()

    // External requests are enabled for channel C.
    static const uint32_t DMA_REQMASKSET_SET__SET_0_READ = 0;
    // External requests are disabled for channel C.
    static const uint32_t DMA_REQMASKSET_SET__SET_1_READ = 1;

    // Channel Request Mask Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_REQMASKCLR_t, uint32_t)
        // Set the appropriate bit to enable DMA requests for the channel corresponding to dma_req and dma_sreq.
        ADD_BITFIELD_WO(CLR, 0, 32)
    END_TYPE()

    // No effect. Use the DMA_REQMASKSET Register to disable dma_req and dma_sreq from generating requests.
    static const uint32_t DMA_REQMASKCLR_CLR__CLR_0 = 0;
    // Enables dma_req[C] or dma_sreq[C] to generate DMA requests. Writing to a bit where a DMA channel is not implemented has no effect.
    static const uint32_t DMA_REQMASKCLR_CLR__CLR_1 = 1;

    // Channel Enable Set Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_ENASET_t, uint32_t)
        // Returns the enable status of the channels, or enables the corresponding channels.
        ADD_BITFIELD_RW(SET, 0, 32)
    END_TYPE()

    // Channel C is disabled.
    static const uint32_t DMA_ENASET_SET__SET_0_READ = 0;
    // Channel C is enabled.
    static const uint32_t DMA_ENASET_SET__SET_1_READ = 1;

    // Channel Enable Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_ENACLR_t, uint32_t)
        // Set the appropriate bit to disable the corresponding DMA channel. Note: The controller disables a channel, by setting the appropriate bit, when: a) it completes the DMA cycle b) it reads a channel_cfg memory location which has cycle_ctrl = b000 c) an ERROR occurs on the AHB-Lite bus.
        ADD_BITFIELD_WO(CLR, 0, 32)
    END_TYPE()

    // No effect. Use the DMA_ENASET Register to enable DMA channels.
    static const uint32_t DMA_ENACLR_CLR__CLR_0 = 0;
    // Disables channel C. Writing to a bit where a DMA channel is not implemented has no effect.
    static const uint32_t DMA_ENACLR_CLR__CLR_1 = 1;

    // Channel Primary-Alternate Set Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_ALTSET_t, uint32_t)
        // Channel Primary-Alternate Set Register
        ADD_BITFIELD_RW(SET, 0, 32)
    END_TYPE()

    // DMA channel C is using the primary data structure.
    static const uint32_t DMA_ALTSET_SET__SET_0_READ = 0;
    // DMA channel C is using the alternate data structure.
    static const uint32_t DMA_ALTSET_SET__SET_1_READ = 1;

    // Channel Primary-Alternate Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_ALTCLR_t, uint32_t)
        // Channel Primary-Alternate Clear Register
        ADD_BITFIELD_WO(CLR, 0, 32)
    END_TYPE()

    // No effect. Use the DMA_ALTSET Register to select the alternate data structure.
    static const uint32_t DMA_ALTCLR_CLR__CLR_0 = 0;
    // Selects the primary data structure for channel C. Writing to a bit where a DMA channel is not implemented has no effect.
    static const uint32_t DMA_ALTCLR_CLR__CLR_1 = 1;

    // Channel Priority Set Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_PRIOSET_t, uint32_t)
        // Returns the channel priority mask status, or sets the channel priority to high.
        ADD_BITFIELD_RW(SET, 0, 32)
    END_TYPE()

    // DMA channel C is using the default priority level.
    static const uint32_t DMA_PRIOSET_SET__SET_0_READ = 0;
    // DMA channel C is using a high priority level.
    static const uint32_t DMA_PRIOSET_SET__SET_1_READ = 1;

    // Channel Priority Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_PRIOCLR_t, uint32_t)
        // Set the appropriate bit to select the default priority level for the specified DMA channel.
        ADD_BITFIELD_WO(CLR, 0, 32)
    END_TYPE()

    // No effect. Use the DMA_PRIOSET Register to set channel C to the high priority level.
    static const uint32_t DMA_PRIOCLR_CLR__CLR_0 = 0;
    // Channel C uses the default priority level. Writing to a bit where a DMA channel is not implemented has no effect.
    static const uint32_t DMA_PRIOCLR_CLR__CLR_1 = 1;

    // Bus Error Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DMA_ERRCLR_t, uint32_t)
        // Returns the status of dma_err, or sets the signal LOW. For test purposes, use the ERRSET register to set dma_err HIGH. Note: If you deassert dma_err at the same time as an ERROR occurs on the AHB-Lite bus, then the ERROR condition takes precedence and dma_err remains asserted.
        ADD_BITFIELD_RW(ERRCLR, 0, 1)
    END_TYPE()

    // dma_err is LOW
    static const uint32_t DMA_ERRCLR_ERRCLR__ERRCLR_0_READ = 0;
    // dma_err is HIGH.
    static const uint32_t DMA_ERRCLR_ERRCLR__ERRCLR_1_READ = 1;

    struct DMA_t {
        DMA_DEVICE_CFG_t              DMA_DEVICE_CFG;
        DMA_SW_CHTRIG_t               DMA_SW_CHTRIG;
        uint32_t                      reserved0[2];
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG0;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG1;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG2;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG3;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG4;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG5;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG6;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG7;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG8;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG9;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG10;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG11;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG12;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG13;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG14;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG15;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG16;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG17;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG18;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG19;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG20;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG21;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG22;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG23;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG24;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG25;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG26;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG27;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG28;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG29;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG30;
        DMA_CH_SRCCFG_t               DMA_CH_SRCCFG31;
        uint32_t                      reserved1[28];
        DMA_INT1_SRCCFG_t             DMA_INT1_SRCCFG;
        DMA_INT2_SRCCFG_t             DMA_INT2_SRCCFG;
        DMA_INT3_SRCCFG_t             DMA_INT3_SRCCFG;
        uint32_t                      reserved2;
        DMA_INT0_SRCFLG_t             DMA_INT0_SRCFLG;
        DMA_INT0_CLRFLG_t             DMA_INT0_CLRFLG;
        uint32_t                      reserved3[954];
        DMA_STAT_t                    DMA_STAT;
        DMA_CFG_t                     DMA_CFG;
        DMA_CTLBASE_t                 DMA_CTLBASE;
        DMA_ALTBASE_t                 DMA_ALTBASE;
        DMA_WAITSTAT_t                DMA_WAITSTAT;
        DMA_SWREQ_t                   DMA_SWREQ;
        DMA_USEBURSTSET_t             DMA_USEBURSTSET;
        DMA_USEBURSTCLR_t             DMA_USEBURSTCLR;
        DMA_REQMASKSET_t              DMA_REQMASKSET;
        DMA_REQMASKCLR_t              DMA_REQMASKCLR;
        DMA_ENASET_t                  DMA_ENASET;
        DMA_ENACLR_t                  DMA_ENACLR;
        DMA_ALTSET_t                  DMA_ALTSET;
        DMA_ALTCLR_t                  DMA_ALTCLR;
        DMA_PRIOSET_t                 DMA_PRIOSET;
        DMA_PRIOCLR_t                 DMA_PRIOCLR;
        uint32_t                      reserved4[3];
        DMA_ERRCLR_t                  DMA_ERRCLR;
    };

    static DMA_t & DMA     = (*(DMA_t *)0x4000e000);

} // _DMA_

// PCM
namespace _PCM_  {

    // Control 0 Register
    // Reset value: 0xa5960000
    BEGIN_TYPE(PCMCTL0_t, uint32_t)
        // Active Mode Request
        ADD_BITFIELD_RW(AMR, 0, 4)
        // Low Power Mode Request
        ADD_BITFIELD_RW(LPMR, 4, 4)
        // Current Power Mode
        ADD_BITFIELD_RO(CPM, 8, 6)
        // PCM key
        ADD_BITFIELD_RW(PCMKEY, 16, 16)
    END_TYPE()

    // LDO based Active Mode at Core voltage setting 0.
    static const uint32_t PCMCTL0_AMR__AMR_0 = 0;
    // LDO based Active Mode at Core voltage setting 1.
    static const uint32_t PCMCTL0_AMR__AMR_1 = 1;
    // DC-DC based Active Mode at Core voltage setting 0.
    static const uint32_t PCMCTL0_AMR__AMR_4 = 4;
    // DC-DC based Active Mode at Core voltage setting 1.
    static const uint32_t PCMCTL0_AMR__AMR_5 = 5;
    // Low-Frequency Active Mode at Core voltage setting 0.
    static const uint32_t PCMCTL0_AMR__AMR_8 = 8;
    // Low-Frequency Active Mode at Core voltage setting 1.
    static const uint32_t PCMCTL0_AMR__AMR_9 = 9;
    // LPM3. Core voltage setting is similar to the mode from which LPM3 is entered.
    static const uint32_t PCMCTL0_LPMR__LPMR_0 = 0;
    // LPM3.5. Core voltage setting 0.
    static const uint32_t PCMCTL0_LPMR__LPMR_10 = 10;
    // LPM4.5
    static const uint32_t PCMCTL0_LPMR__LPMR_12 = 12;
    // LDO based Active Mode at Core voltage setting 0.
    static const uint32_t PCMCTL0_CPM__CPM_0 = 0;
    // LDO based Active Mode at Core voltage setting 1.
    static const uint32_t PCMCTL0_CPM__CPM_1 = 1;
    // DC-DC based Active Mode at Core voltage setting 0.
    static const uint32_t PCMCTL0_CPM__CPM_4 = 4;
    // DC-DC based Active Mode at Core voltage setting 1.
    static const uint32_t PCMCTL0_CPM__CPM_5 = 5;
    // Low-Frequency Active Mode at Core voltage setting 0.
    static const uint32_t PCMCTL0_CPM__CPM_8 = 8;
    // Low-Frequency Active Mode at Core voltage setting 1.
    static const uint32_t PCMCTL0_CPM__CPM_9 = 9;
    // LDO based LPM0 at Core voltage setting 0.
    static const uint32_t PCMCTL0_CPM__CPM_16 = 16;
    // LDO based LPM0 at Core voltage setting 1.
    static const uint32_t PCMCTL0_CPM__CPM_17 = 17;
    // DC-DC based LPM0 at Core voltage setting 0.
    static const uint32_t PCMCTL0_CPM__CPM_20 = 20;
    // DC-DC based LPM0 at Core voltage setting 1.
    static const uint32_t PCMCTL0_CPM__CPM_21 = 21;
    // Low-Frequency LPM0 at Core voltage setting 0.
    static const uint32_t PCMCTL0_CPM__CPM_24 = 24;
    // Low-Frequency LPM0 at Core voltage setting 1.
    static const uint32_t PCMCTL0_CPM__CPM_25 = 25;
    // LPM3
    static const uint32_t PCMCTL0_CPM__CPM_32 = 32;

    // Control 1 Register
    // Reset value: 0xa5960000
    BEGIN_TYPE(PCMCTL1_t, uint32_t)
        // Lock LPM5
        ADD_BITFIELD_RW(LOCKLPM5, 0, 1)
        // Lock Backup
        ADD_BITFIELD_RW(LOCKBKUP, 1, 1)
        // Force LPM entry
        ADD_BITFIELD_RW(FORCE_LPM_ENTRY, 2, 1)
        // Power mode request busy flag
        ADD_BITFIELD_RW(PMR_BUSY, 8, 1)
        // PCM key
        ADD_BITFIELD_RW(PCMKEY, 16, 16)
    END_TYPE()

    // LPMx.5 configuration defaults to reset condition
    static const uint32_t PCMCTL1_LOCKLPM5__LOCKLPM5_0 = 0;
    // LPMx.5 configuration remains locked during LPMx.5 entry and exit
    static const uint32_t PCMCTL1_LOCKLPM5__LOCKLPM5_1 = 1;
    // Backup domain configuration defaults to reset condition
    static const uint32_t PCMCTL1_LOCKBKUP__LOCKBKUP_0 = 0;
    // Backup domain configuration remains locked during LPM3.5 entry and exit
    static const uint32_t PCMCTL1_LOCKBKUP__LOCKBKUP_1 = 1;
    // PCM aborts LPM3/LPMx.5 transition if the active clock configuration does not meet the LPM3/LPMx.5 entry criteria. PCM generates the LPM_INVALID_CLK flag on abort to LPM3/LPMx.5 entry.
    static const uint32_t PCMCTL1_FORCE_LPM_ENTRY__FORCE_LPM_ENTRY_0 = 0;
    // PCM enters LPM3/LPMx.5 after shuting off the clocks forcefully. Application needs to ensure RTC and WDT are clocked using BCLK tree to keep these modules alive in LPM3/LPM3.5. In LPM4.5 all clocks are forcefully shutoff and the core voltage is turned off.
    static const uint32_t PCMCTL1_FORCE_LPM_ENTRY__FORCE_LPM_ENTRY_1 = 1;

    // Interrupt Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(PCMIE_t, uint32_t)
        // LPM invalid transition interrupt enable
        ADD_BITFIELD_RW(LPM_INVALID_TR_IE, 0, 1)
        // LPM invalid clock interrupt enable
        ADD_BITFIELD_RW(LPM_INVALID_CLK_IE, 1, 1)
        // Active mode invalid transition interrupt enable
        ADD_BITFIELD_RW(AM_INVALID_TR_IE, 2, 1)
        // DC-DC error interrupt enable
        ADD_BITFIELD_RW(DCDC_ERROR_IE, 6, 1)
    END_TYPE()

    // Disabled
    static const uint32_t PCMIE_LPM_INVALID_TR_IE__LPM_INVALID_TR_IE_0 = 0;
    // Enabled
    static const uint32_t PCMIE_LPM_INVALID_TR_IE__LPM_INVALID_TR_IE_1 = 1;
    // Disabled
    static const uint32_t PCMIE_LPM_INVALID_CLK_IE__LPM_INVALID_CLK_IE_0 = 0;
    // Enabled
    static const uint32_t PCMIE_LPM_INVALID_CLK_IE__LPM_INVALID_CLK_IE_1 = 1;
    // Disabled
    static const uint32_t PCMIE_AM_INVALID_TR_IE__AM_INVALID_TR_IE_0 = 0;
    // Enabled
    static const uint32_t PCMIE_AM_INVALID_TR_IE__AM_INVALID_TR_IE_1 = 1;
    // Disabled
    static const uint32_t PCMIE_DCDC_ERROR_IE__DCDC_ERROR_IE_0 = 0;
    // Enabled
    static const uint32_t PCMIE_DCDC_ERROR_IE__DCDC_ERROR_IE_1 = 1;

    // Interrupt Flag Register
    // Reset value: 0x00000000
    BEGIN_TYPE(PCMIFG_t, uint32_t)
        // LPM invalid transition flag
        ADD_BITFIELD_RO(LPM_INVALID_TR_IFG, 0, 1)
        // LPM invalid clock flag
        ADD_BITFIELD_RO(LPM_INVALID_CLK_IFG, 1, 1)
        // Active mode invalid transition flag
        ADD_BITFIELD_RO(AM_INVALID_TR_IFG, 2, 1)
        // DC-DC error flag
        ADD_BITFIELD_RO(DCDC_ERROR_IFG, 6, 1)
    END_TYPE()

    // Clear Interrupt Flag Register
    // Reset value: 0x00000000
    BEGIN_TYPE(PCMCLRIFG_t, uint32_t)
        // Clear LPM invalid transition flag
        ADD_BITFIELD_WO(CLR_LPM_INVALID_TR_IFG, 0, 1)
        // Clear LPM invalid clock flag
        ADD_BITFIELD_WO(CLR_LPM_INVALID_CLK_IFG, 1, 1)
        // Clear active mode invalid transition flag
        ADD_BITFIELD_WO(CLR_AM_INVALID_TR_IFG, 2, 1)
        // Clear DC-DC error flag
        ADD_BITFIELD_WO(CLR_DCDC_ERROR_IFG, 6, 1)
    END_TYPE()

    struct PCM_t {
        PCMCTL0_t                     PCMCTL0;
        PCMCTL1_t                     PCMCTL1;
        PCMIE_t                       PCMIE;
        PCMIFG_t                      PCMIFG;
        PCMCLRIFG_t                   PCMCLRIFG;
    };

    static PCM_t & PCM     = (*(PCM_t *)0x40010000);

} // _PCM_

// CS
namespace _CS_  {

    // Key Register
    // Reset value: 0x0000a596
    BEGIN_TYPE(CSKEY_t, uint32_t)
        // Write xxxx_695Ah to unlock
        ADD_BITFIELD_RW(CSKEY, 0, 16)
    END_TYPE()

    // Control 0 Register
    // Reset value: 0x00010000
    BEGIN_TYPE(CSCTL0_t, uint32_t)
        // DCO frequency tuning select
        ADD_BITFIELD_RW(DCOTUNE, 0, 10)
        // DCO frequency range select
        ADD_BITFIELD_RW(DCORSEL, 16, 3)
        // Enables the DCO external resistor mode
        ADD_BITFIELD_RW(DCORES, 22, 1)
        // Enables the DCO oscillator
        ADD_BITFIELD_RW(DCOEN, 23, 1)
    END_TYPE()

    // Nominal DCO Frequency Range (MHz): 1 to 2
    static const uint32_t CSCTL0_DCORSEL__DCORSEL_0 = 0;
    // Nominal DCO Frequency Range (MHz): 2 to 4
    static const uint32_t CSCTL0_DCORSEL__DCORSEL_1 = 1;
    // Nominal DCO Frequency Range (MHz): 4 to 8
    static const uint32_t CSCTL0_DCORSEL__DCORSEL_2 = 2;
    // Nominal DCO Frequency Range (MHz): 8 to 16
    static const uint32_t CSCTL0_DCORSEL__DCORSEL_3 = 3;
    // Nominal DCO Frequency Range (MHz): 16 to 32
    static const uint32_t CSCTL0_DCORSEL__DCORSEL_4 = 4;
    // Nominal DCO Frequency Range (MHz): 32 to 64
    static const uint32_t CSCTL0_DCORSEL__DCORSEL_5 = 5;
    // Internal resistor mode
    static const uint32_t CSCTL0_DCORES__DCORES_0 = 0;
    // External resistor mode
    static const uint32_t CSCTL0_DCORES__DCORES_1 = 1;
    // DCO is on if it is used as a source for MCLK, HSMCLK , or SMCLK and clock is requested, otherwise it is disabled.
    static const uint32_t CSCTL0_DCOEN__DCOEN_0 = 0;
    // DCO is on
    static const uint32_t CSCTL0_DCOEN__DCOEN_1 = 1;

    // Control 1 Register
    // Reset value: 0x00000033
    BEGIN_TYPE(CSCTL1_t, uint32_t)
        // Selects the MCLK source
        ADD_BITFIELD_RW(SELM, 0, 3)
        // Selects the SMCLK and HSMCLK source
        ADD_BITFIELD_RW(SELS, 4, 3)
        // Selects the ACLK source
        ADD_BITFIELD_RW(SELA, 8, 3)
        // Selects the BCLK source
        ADD_BITFIELD_RW(SELB, 12, 1)
        // MCLK source divider
        ADD_BITFIELD_RW(DIVM, 16, 3)
        // HSMCLK source divider
        ADD_BITFIELD_RW(DIVHS, 20, 3)
        // ACLK source divider
        ADD_BITFIELD_RW(DIVA, 24, 3)
        // SMCLK source divider
        ADD_BITFIELD_RW(DIVS, 28, 3)
    END_TYPE()

    // when LFXT available, otherwise REFOCLK
    static const uint32_t CSCTL1_SELM__SELM_0 = 0;
    static const uint32_t CSCTL1_SELM__SELM_1 = 1;
    static const uint32_t CSCTL1_SELM__SELM_2 = 2;
    static const uint32_t CSCTL1_SELM__SELM_3 = 3;
    static const uint32_t CSCTL1_SELM__SELM_4 = 4;
    // when HFXT available, otherwise DCOCLK
    static const uint32_t CSCTL1_SELM__SELM_5 = 5;
    // when HFXT2 available, otherwise DCOCLK
    static const uint32_t CSCTL1_SELM__SELM_6 = 6;
    // for future use. Defaults to DCOCLK. Not recommended for use to ensure future compatibilities.
    static const uint32_t CSCTL1_SELM__SELM_7 = 7;
    // when LFXT available, otherwise REFOCLK
    static const uint32_t CSCTL1_SELS__SELS_0 = 0;
    static const uint32_t CSCTL1_SELS__SELS_1 = 1;
    static const uint32_t CSCTL1_SELS__SELS_2 = 2;
    static const uint32_t CSCTL1_SELS__SELS_3 = 3;
    static const uint32_t CSCTL1_SELS__SELS_4 = 4;
    // when HFXT available, otherwise DCOCLK
    static const uint32_t CSCTL1_SELS__SELS_5 = 5;
    // when HFXT2 available, otherwise DCOCLK
    static const uint32_t CSCTL1_SELS__SELS_6 = 6;
    // for furture use. Defaults to DCOCLK. Do not use to ensure future compatibilities.
    static const uint32_t CSCTL1_SELS__SELS_7 = 7;
    // when LFXT available, otherwise REFOCLK
    static const uint32_t CSCTL1_SELA__SELA_0 = 0;
    static const uint32_t CSCTL1_SELA__SELA_1 = 1;
    static const uint32_t CSCTL1_SELA__SELA_2 = 2;
    // for future use. Defaults to REFOCLK. Not recommended for use to ensure future compatibilities.
    static const uint32_t CSCTL1_SELA__SELA_3 = 3;
    // for future use. Defaults to REFOCLK. Not recommended for use to ensure future compatibilities.
    static const uint32_t CSCTL1_SELA__SELA_4 = 4;
    // for future use. Defaults to REFOCLK. Not recommended for use to ensure future compatibilities.
    static const uint32_t CSCTL1_SELA__SELA_5 = 5;
    // for future use. Defaults to REFOCLK. Not recommended for use to ensure future compatibilities.
    static const uint32_t CSCTL1_SELA__SELA_6 = 6;
    // for future use. Defaults to REFOCLK. Not recommended for use to ensure future compatibilities.
    static const uint32_t CSCTL1_SELA__SELA_7 = 7;
    // LFXTCLK
    static const uint32_t CSCTL1_SELB__SELB_0 = 0;
    // REFOCLK
    static const uint32_t CSCTL1_SELB__SELB_1 = 1;
    // f(MCLK)/1
    static const uint32_t CSCTL1_DIVM__DIVM_0 = 0;
    // f(MCLK)/2
    static const uint32_t CSCTL1_DIVM__DIVM_1 = 1;
    // f(MCLK)/4
    static const uint32_t CSCTL1_DIVM__DIVM_2 = 2;
    // f(MCLK)/8
    static const uint32_t CSCTL1_DIVM__DIVM_3 = 3;
    // f(MCLK)/16
    static const uint32_t CSCTL1_DIVM__DIVM_4 = 4;
    // f(MCLK)/32
    static const uint32_t CSCTL1_DIVM__DIVM_5 = 5;
    // f(MCLK)/64
    static const uint32_t CSCTL1_DIVM__DIVM_6 = 6;
    // f(MCLK)/128
    static const uint32_t CSCTL1_DIVM__DIVM_7 = 7;
    // f(HSMCLK)/1
    static const uint32_t CSCTL1_DIVHS__DIVHS_0 = 0;
    // f(HSMCLK)/2
    static const uint32_t CSCTL1_DIVHS__DIVHS_1 = 1;
    // f(HSMCLK)/4
    static const uint32_t CSCTL1_DIVHS__DIVHS_2 = 2;
    // f(HSMCLK)/8
    static const uint32_t CSCTL1_DIVHS__DIVHS_3 = 3;
    // f(HSMCLK)/16
    static const uint32_t CSCTL1_DIVHS__DIVHS_4 = 4;
    // f(HSMCLK)/32
    static const uint32_t CSCTL1_DIVHS__DIVHS_5 = 5;
    // f(HSMCLK)/64
    static const uint32_t CSCTL1_DIVHS__DIVHS_6 = 6;
    // f(HSMCLK)/128
    static const uint32_t CSCTL1_DIVHS__DIVHS_7 = 7;
    // f(ACLK)/1
    static const uint32_t CSCTL1_DIVA__DIVA_0 = 0;
    // f(ACLK)/2
    static const uint32_t CSCTL1_DIVA__DIVA_1 = 1;
    // f(ACLK)/4
    static const uint32_t CSCTL1_DIVA__DIVA_2 = 2;
    // f(ACLK)/8
    static const uint32_t CSCTL1_DIVA__DIVA_3 = 3;
    // f(ACLK)/16
    static const uint32_t CSCTL1_DIVA__DIVA_4 = 4;
    // f(ACLK)/32
    static const uint32_t CSCTL1_DIVA__DIVA_5 = 5;
    // f(ACLK)/64
    static const uint32_t CSCTL1_DIVA__DIVA_6 = 6;
    // f(ACLK)/128
    static const uint32_t CSCTL1_DIVA__DIVA_7 = 7;
    // f(SMCLK)/1
    static const uint32_t CSCTL1_DIVS__DIVS_0 = 0;
    // f(SMCLK)/2
    static const uint32_t CSCTL1_DIVS__DIVS_1 = 1;
    // f(SMCLK)/4
    static const uint32_t CSCTL1_DIVS__DIVS_2 = 2;
    // f(SMCLK)/8
    static const uint32_t CSCTL1_DIVS__DIVS_3 = 3;
    // f(SMCLK)/16
    static const uint32_t CSCTL1_DIVS__DIVS_4 = 4;
    // f(SMCLK)/32
    static const uint32_t CSCTL1_DIVS__DIVS_5 = 5;
    // f(SMCLK)/64
    static const uint32_t CSCTL1_DIVS__DIVS_6 = 6;
    // f(SMCLK)/128
    static const uint32_t CSCTL1_DIVS__DIVS_7 = 7;

    // Control 2 Register
    // Reset value: 0x00010003
    BEGIN_TYPE(CSCTL2_t, uint32_t)
        // LFXT oscillator current can be adjusted to its drive needs
        ADD_BITFIELD_RW(LFXTDRIVE, 0, 2)
        // Disables the automatic gain control of the LFXT crystal
        ADD_BITFIELD_RW(LFXTAGCOFF, 7, 1)
        // Turns on the LFXT oscillator regardless if used as a clock resource
        ADD_BITFIELD_RW(LFXT_EN, 8, 1)
        // LFXT bypass select
        ADD_BITFIELD_RW(LFXTBYPASS, 9, 1)
        // HFXT oscillator drive selection
        ADD_BITFIELD_RW(HFXTDRIVE, 16, 1)
        // HFXT frequency selection
        ADD_BITFIELD_RW(HFXTFREQ, 20, 3)
        // Turns on the HFXT oscillator regardless if used as a clock resource
        ADD_BITFIELD_RW(HFXT_EN, 24, 1)
        // HFXT bypass select
        ADD_BITFIELD_RW(HFXTBYPASS, 25, 1)
    END_TYPE()

    // Lowest drive strength and current consumption LFXT oscillator.
    static const uint32_t CSCTL2_LFXTDRIVE__LFXTDRIVE_0 = 0;
    // Increased drive strength LFXT oscillator.
    static const uint32_t CSCTL2_LFXTDRIVE__LFXTDRIVE_1 = 1;
    // Increased drive strength LFXT oscillator.
    static const uint32_t CSCTL2_LFXTDRIVE__LFXTDRIVE_2 = 2;
    // Maximum drive strength and maximum current consumption LFXT oscillator.
    static const uint32_t CSCTL2_LFXTDRIVE__LFXTDRIVE_3 = 3;
    // AGC enabled.
    static const uint32_t CSCTL2_LFXTAGCOFF__LFXTAGCOFF_0 = 0;
    // AGC disabled.
    static const uint32_t CSCTL2_LFXTAGCOFF__LFXTAGCOFF_1 = 1;
    // LFXT is on if it is used as a source for ACLK, MCLK, HSMCLK , or SMCLK and is selected via the port selection and not in bypass mode of operation.
    static const uint32_t CSCTL2_LFXT_EN__LFXT_EN_0 = 0;
    // LFXT is on if LFXT is selected via the port selection and LFXT is not in bypass mode of operation.
    static const uint32_t CSCTL2_LFXT_EN__LFXT_EN_1 = 1;
    // LFXT sourced by external crystal.
    static const uint32_t CSCTL2_LFXTBYPASS__LFXTBYPASS_0 = 0;
    // LFXT sourced by external square wave.
    static const uint32_t CSCTL2_LFXTBYPASS__LFXTBYPASS_1 = 1;
    // To be used for HFXTFREQ setting 000b
    static const uint32_t CSCTL2_HFXTDRIVE__HFXTDRIVE_0 = 0;
    // To be used for HFXTFREQ settings 001b to 110b
    static const uint32_t CSCTL2_HFXTDRIVE__HFXTDRIVE_1 = 1;
    // 1 MHz to 4 MHz
    static const uint32_t CSCTL2_HFXTFREQ__HFXTFREQ_0 = 0;
    // >4 MHz to 8 MHz
    static const uint32_t CSCTL2_HFXTFREQ__HFXTFREQ_1 = 1;
    // >8 MHz to 16 MHz
    static const uint32_t CSCTL2_HFXTFREQ__HFXTFREQ_2 = 2;
    // >16 MHz to 24 MHz
    static const uint32_t CSCTL2_HFXTFREQ__HFXTFREQ_3 = 3;
    // >24 MHz to 32 MHz
    static const uint32_t CSCTL2_HFXTFREQ__HFXTFREQ_4 = 4;
    // >32 MHz to 40 MHz
    static const uint32_t CSCTL2_HFXTFREQ__HFXTFREQ_5 = 5;
    // >40 MHz to 48 MHz
    static const uint32_t CSCTL2_HFXTFREQ__HFXTFREQ_6 = 6;
    // HFXT is on if it is used as a source for MCLK, HSMCLK , or SMCLK and is selected via the port selection and not in bypass mode of operation.
    static const uint32_t CSCTL2_HFXT_EN__HFXT_EN_0 = 0;
    // HFXT is on if HFXT is selected via the port selection and HFXT is not in bypass mode of operation.
    static const uint32_t CSCTL2_HFXT_EN__HFXT_EN_1 = 1;
    // HFXT sourced by external crystal.
    static const uint32_t CSCTL2_HFXTBYPASS__HFXTBYPASS_0 = 0;
    // HFXT sourced by external square wave.
    static const uint32_t CSCTL2_HFXTBYPASS__HFXTBYPASS_1 = 1;

    // Control 3 Register
    // Reset value: 0x00000bbb
    BEGIN_TYPE(CSCTL3_t, uint32_t)
        // Start flag counter for LFXT
        ADD_BITFIELD_RW(FCNTLF, 0, 2)
        // Reset start fault counter for LFXT
        ADD_BITFIELD_WO(RFCNTLF, 2, 1)
        // Enable start fault counter for LFXT
        ADD_BITFIELD_RW(FCNTLF_EN, 3, 1)
        // Start flag counter for HFXT
        ADD_BITFIELD_RW(FCNTHF, 4, 2)
        // Reset start fault counter for HFXT
        ADD_BITFIELD_WO(RFCNTHF, 6, 1)
        // Enable start fault counter for HFXT
        ADD_BITFIELD_RW(FCNTHF_EN, 7, 1)
        // Start flag counter for HFXT2
        ADD_BITFIELD_RW(FCNTHF2, 8, 2)
        // Reset start fault counter for HFXT2
        ADD_BITFIELD_WO(RFCNTHF2, 10, 1)
        // Enable start fault counter for HFXT2
        ADD_BITFIELD_RW(FCNTHF2_EN, 11, 1)
    END_TYPE()

    // 4096 cycles
    static const uint32_t CSCTL3_FCNTLF__FCNTLF_0 = 0;
    // 8192 cycles
    static const uint32_t CSCTL3_FCNTLF__FCNTLF_1 = 1;
    // 16384 cycles
    static const uint32_t CSCTL3_FCNTLF__FCNTLF_2 = 2;
    // 32768 cycles
    static const uint32_t CSCTL3_FCNTLF__FCNTLF_3 = 3;
    // Not applicable. Always reads as zero due to self clearing.
    static const uint32_t CSCTL3_RFCNTLF__RFCNTLF_0 = 0;
    // Restarts the counter immediately.
    static const uint32_t CSCTL3_RFCNTLF__RFCNTLF_1 = 1;
    // Startup fault counter disabled. Counter is cleared.
    static const uint32_t CSCTL3_FCNTLF_EN__FCNTLF_EN_0 = 0;
    // Startup fault counter enabled.
    static const uint32_t CSCTL3_FCNTLF_EN__FCNTLF_EN_1 = 1;
    // 2048 cycles
    static const uint32_t CSCTL3_FCNTHF__FCNTHF_0 = 0;
    // 4096 cycles
    static const uint32_t CSCTL3_FCNTHF__FCNTHF_1 = 1;
    // 8192 cycles
    static const uint32_t CSCTL3_FCNTHF__FCNTHF_2 = 2;
    // 16384 cycles
    static const uint32_t CSCTL3_FCNTHF__FCNTHF_3 = 3;
    // Not applicable. Always reads as zero due to self clearing.
    static const uint32_t CSCTL3_RFCNTHF__RFCNTHF_0 = 0;
    // Restarts the counter immediately.
    static const uint32_t CSCTL3_RFCNTHF__RFCNTHF_1 = 1;
    // Startup fault counter disabled. Counter is cleared.
    static const uint32_t CSCTL3_FCNTHF_EN__FCNTHF_EN_0 = 0;
    // Startup fault counter enabled.
    static const uint32_t CSCTL3_FCNTHF_EN__FCNTHF_EN_1 = 1;
    // 2048 cycles
    static const uint32_t CSCTL3_FCNTHF2__FCNTHF2_0 = 0;
    // 4096 cycles
    static const uint32_t CSCTL3_FCNTHF2__FCNTHF2_1 = 1;
    // 8192 cycles
    static const uint32_t CSCTL3_FCNTHF2__FCNTHF2_2 = 2;
    // 16384 cycles
    static const uint32_t CSCTL3_FCNTHF2__FCNTHF2_3 = 3;
    // Not applicable. Always reads as zero due to self clearing.
    static const uint32_t CSCTL3_RFCNTHF2__RFCNTHF2_0 = 0;
    // Restarts the counter immediately.
    static const uint32_t CSCTL3_RFCNTHF2__RFCNTHF2_1 = 1;
    // Startup fault counter disabled. Counter is cleared.
    static const uint32_t CSCTL3_FCNTHF2_EN__FCNTHF2_EN_0 = 0;
    // Startup fault counter enabled.
    static const uint32_t CSCTL3_FCNTHF2_EN__FCNTHF2_EN_1 = 1;

    // Clock Enable Register
    // Reset value: 0x0000000f
    BEGIN_TYPE(CSCLKEN_t, uint32_t)
        // ACLK system clock conditional request enable
        ADD_BITFIELD_RW(ACLK_EN, 0, 1)
        // MCLK system clock conditional request enable
        ADD_BITFIELD_RW(MCLK_EN, 1, 1)
        // HSMCLK system clock conditional request enable
        ADD_BITFIELD_RW(HSMCLK_EN, 2, 1)
        // SMCLK system clock conditional request enable
        ADD_BITFIELD_RW(SMCLK_EN, 3, 1)
        // Turns on the VLO oscillator
        ADD_BITFIELD_RW(VLO_EN, 8, 1)
        // Turns on the REFO oscillator
        ADD_BITFIELD_RW(REFO_EN, 9, 1)
        // Turns on the MODOSC oscillator
        ADD_BITFIELD_RW(MODOSC_EN, 10, 1)
        // Selects REFO nominal frequency
        ADD_BITFIELD_RW(REFOFSEL, 15, 1)
    END_TYPE()

    // ACLK disabled regardless of conditional clock requests
    static const uint32_t CSCLKEN_ACLK_EN__ACLK_EN_0 = 0;
    // ACLK enabled based on any conditional clock requests
    static const uint32_t CSCLKEN_ACLK_EN__ACLK_EN_1 = 1;
    // MCLK disabled regardless of conditional clock requests
    static const uint32_t CSCLKEN_MCLK_EN__MCLK_EN_0 = 0;
    // MCLK enabled based on any conditional clock requests
    static const uint32_t CSCLKEN_MCLK_EN__MCLK_EN_1 = 1;
    // HSMCLK disabled regardless of conditional clock requests
    static const uint32_t CSCLKEN_HSMCLK_EN__HSMCLK_EN_0 = 0;
    // HSMCLK enabled based on any conditional clock requests
    static const uint32_t CSCLKEN_HSMCLK_EN__HSMCLK_EN_1 = 1;
    // SMCLK disabled regardless of conditional clock requests.
    static const uint32_t CSCLKEN_SMCLK_EN__SMCLK_EN_0 = 0;
    // SMCLK enabled based on any conditional clock requests
    static const uint32_t CSCLKEN_SMCLK_EN__SMCLK_EN_1 = 1;
    // VLO is on only if it is used as a source for ACLK, MCLK, HSMCLK or SMCLK.
    static const uint32_t CSCLKEN_VLO_EN__VLO_EN_0 = 0;
    // VLO is on
    static const uint32_t CSCLKEN_VLO_EN__VLO_EN_1 = 1;
    // REFO is on only if it is used as a source for ACLK, MCLK, HSMCLK or SMCLK
    static const uint32_t CSCLKEN_REFO_EN__REFO_EN_0 = 0;
    // REFO is on
    static const uint32_t CSCLKEN_REFO_EN__REFO_EN_1 = 1;
    // MODOSC is on only if it is used as a source for ACLK, MCLK, HSMCLK or SMCLK
    static const uint32_t CSCLKEN_MODOSC_EN__MODOSC_EN_0 = 0;
    // MODOSC is on
    static const uint32_t CSCLKEN_MODOSC_EN__MODOSC_EN_1 = 1;
    // 32 kHz
    static const uint32_t CSCLKEN_REFOFSEL__REFOFSEL_0 = 0;
    // 128 kHz
    static const uint32_t CSCLKEN_REFOFSEL__REFOFSEL_1 = 1;

    // Status Register
    // Reset value: 0x00000003
    BEGIN_TYPE(CSSTAT_t, uint32_t)
        // DCO status
        ADD_BITFIELD_RO(DCO_ON, 0, 1)
        // DCO bias status
        ADD_BITFIELD_RO(DCOBIAS_ON, 1, 1)
        // HFXT status
        ADD_BITFIELD_RO(HFXT_ON, 2, 1)
        // HFXT2 status
        ADD_BITFIELD_RO(HFXT2_ON, 3, 1)
        // MODOSC status
        ADD_BITFIELD_RO(MODOSC_ON, 4, 1)
        // VLO status
        ADD_BITFIELD_RO(VLO_ON, 5, 1)
        // LFXT status
        ADD_BITFIELD_RO(LFXT_ON, 6, 1)
        // REFO status
        ADD_BITFIELD_RO(REFO_ON, 7, 1)
        // ACLK system clock status
        ADD_BITFIELD_RO(ACLK_ON, 16, 1)
        // MCLK system clock status
        ADD_BITFIELD_RO(MCLK_ON, 17, 1)
        // HSMCLK system clock status
        ADD_BITFIELD_RO(HSMCLK_ON, 18, 1)
        // SMCLK system clock status
        ADD_BITFIELD_RO(SMCLK_ON, 19, 1)
        // MODCLK system clock status
        ADD_BITFIELD_RO(MODCLK_ON, 20, 1)
        // VLOCLK system clock status
        ADD_BITFIELD_RO(VLOCLK_ON, 21, 1)
        // LFXTCLK system clock status
        ADD_BITFIELD_RO(LFXTCLK_ON, 22, 1)
        // REFOCLK system clock status
        ADD_BITFIELD_RO(REFOCLK_ON, 23, 1)
        // ACLK Ready status
        ADD_BITFIELD_RO(ACLK_READY, 24, 1)
        // MCLK Ready status
        ADD_BITFIELD_RO(MCLK_READY, 25, 1)
        // HSMCLK Ready status
        ADD_BITFIELD_RO(HSMCLK_READY, 26, 1)
        // SMCLK Ready status
        ADD_BITFIELD_RO(SMCLK_READY, 27, 1)
        // BCLK Ready status
        ADD_BITFIELD_RO(BCLK_READY, 28, 1)
    END_TYPE()

    // Inactive
    static const uint32_t CSSTAT_DCO_ON__DCO_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_DCO_ON__DCO_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_DCOBIAS_ON__DCOBIAS_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_DCOBIAS_ON__DCOBIAS_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_HFXT_ON__HFXT_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_HFXT_ON__HFXT_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_HFXT2_ON__HFXT2_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_HFXT2_ON__HFXT2_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_MODOSC_ON__MODOSC_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_MODOSC_ON__MODOSC_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_VLO_ON__VLO_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_VLO_ON__VLO_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_LFXT_ON__LFXT_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_LFXT_ON__LFXT_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_REFO_ON__REFO_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_REFO_ON__REFO_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_ACLK_ON__ACLK_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_ACLK_ON__ACLK_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_MCLK_ON__MCLK_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_MCLK_ON__MCLK_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_HSMCLK_ON__HSMCLK_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_HSMCLK_ON__HSMCLK_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_SMCLK_ON__SMCLK_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_SMCLK_ON__SMCLK_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_MODCLK_ON__MODCLK_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_MODCLK_ON__MODCLK_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_VLOCLK_ON__VLOCLK_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_VLOCLK_ON__VLOCLK_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_LFXTCLK_ON__LFXTCLK_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_LFXTCLK_ON__LFXTCLK_ON_1 = 1;
    // Inactive
    static const uint32_t CSSTAT_REFOCLK_ON__REFOCLK_ON_0 = 0;
    // Active
    static const uint32_t CSSTAT_REFOCLK_ON__REFOCLK_ON_1 = 1;
    // Not ready
    static const uint32_t CSSTAT_ACLK_READY__ACLK_READY_0 = 0;
    // Ready
    static const uint32_t CSSTAT_ACLK_READY__ACLK_READY_1 = 1;
    // Not ready
    static const uint32_t CSSTAT_MCLK_READY__MCLK_READY_0 = 0;
    // Ready
    static const uint32_t CSSTAT_MCLK_READY__MCLK_READY_1 = 1;
    // Not ready
    static const uint32_t CSSTAT_HSMCLK_READY__HSMCLK_READY_0 = 0;
    // Ready
    static const uint32_t CSSTAT_HSMCLK_READY__HSMCLK_READY_1 = 1;
    // Not ready
    static const uint32_t CSSTAT_SMCLK_READY__SMCLK_READY_0 = 0;
    // Ready
    static const uint32_t CSSTAT_SMCLK_READY__SMCLK_READY_1 = 1;
    // Not ready
    static const uint32_t CSSTAT_BCLK_READY__BCLK_READY_0 = 0;
    // Ready
    static const uint32_t CSSTAT_BCLK_READY__BCLK_READY_1 = 1;

    // Interrupt Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(CSIE_t, uint32_t)
        // LFXT oscillator fault flag interrupt enable
        ADD_BITFIELD_RW(LFXTIE, 0, 1)
        // HFXT oscillator fault flag interrupt enable
        ADD_BITFIELD_RW(HFXTIE, 1, 1)
        // HFXT2 oscillator fault flag interrupt enable
        ADD_BITFIELD_RW(HFXT2IE, 2, 1)
        // DCO external resistor open circuit fault flag interrupt enable.
        ADD_BITFIELD_RW(DCOR_OPNIE, 6, 1)
        // Start fault counter interrupt enable LFXT
        ADD_BITFIELD_RW(FCNTLFIE, 8, 1)
        // Start fault counter interrupt enable HFXT
        ADD_BITFIELD_RW(FCNTHFIE, 9, 1)
        // Start fault counter interrupt enable HFXT2
        ADD_BITFIELD_RW(FCNTHF2IE, 10, 1)
        // PLL out-of-lock interrupt enable
        ADD_BITFIELD_RW(PLLOOLIE, 12, 1)
        // PLL loss-of-signal interrupt enable
        ADD_BITFIELD_RW(PLLLOSIE, 13, 1)
        // PLL out-of-range interrupt enable
        ADD_BITFIELD_RW(PLLOORIE, 14, 1)
        // REFCNT period counter interrupt enable
        ADD_BITFIELD_RW(CALIE, 15, 1)
    END_TYPE()

    // Interrupt disabled
    static const uint32_t CSIE_LFXTIE__LFXTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CSIE_LFXTIE__LFXTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t CSIE_HFXTIE__HFXTIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CSIE_HFXTIE__HFXTIE_1 = 1;
    // Interrupt disabled
    static const uint32_t CSIE_HFXT2IE__HFXT2IE_0 = 0;
    // Interrupt enabled
    static const uint32_t CSIE_HFXT2IE__HFXT2IE_1 = 1;
    // Interrupt disabled
    static const uint32_t CSIE_DCOR_OPNIE__DCOR_OPNIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CSIE_DCOR_OPNIE__DCOR_OPNIE_1 = 1;
    // Interrupt disabled
    static const uint32_t CSIE_FCNTLFIE__FCNTLFIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CSIE_FCNTLFIE__FCNTLFIE_1 = 1;
    // Interrupt disabled
    static const uint32_t CSIE_FCNTHFIE__FCNTHFIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CSIE_FCNTHFIE__FCNTHFIE_1 = 1;
    // Interrupt disabled
    static const uint32_t CSIE_FCNTHF2IE__FCNTHF2IE_0 = 0;
    // Interrupt enabled
    static const uint32_t CSIE_FCNTHF2IE__FCNTHF2IE_1 = 1;
    // Interrupt disabled
    static const uint32_t CSIE_PLLOOLIE__PLLOOLIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CSIE_PLLOOLIE__PLLOOLIE_1 = 1;
    // Interrupt disabled
    static const uint32_t CSIE_PLLLOSIE__PLLLOSIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CSIE_PLLLOSIE__PLLLOSIE_1 = 1;
    // Interrupt disabled
    static const uint32_t CSIE_PLLOORIE__PLLOORIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CSIE_PLLOORIE__PLLOORIE_1 = 1;
    // Interrupt disabled
    static const uint32_t CSIE_CALIE__CALIE_0 = 0;
    // Interrupt enabled
    static const uint32_t CSIE_CALIE__CALIE_1 = 1;

    // Interrupt Flag Register
    // Reset value: 0x00000001
    BEGIN_TYPE(CSIFG_t, uint32_t)
        // LFXT oscillator fault flag
        ADD_BITFIELD_RO(LFXTIFG, 0, 1)
        // HFXT oscillator fault flag
        ADD_BITFIELD_RO(HFXTIFG, 1, 1)
        // HFXT2 oscillator fault flag
        ADD_BITFIELD_RO(HFXT2IFG, 2, 1)
        // DCO external resistor short circuit fault flag.
        ADD_BITFIELD_RO(DCOR_SHTIFG, 5, 1)
        // DCO external resistor open circuit fault flag.
        ADD_BITFIELD_RO(DCOR_OPNIFG, 6, 1)
        // Start fault counter interrupt flag LFXT
        ADD_BITFIELD_RO(FCNTLFIFG, 8, 1)
        // Start fault counter interrupt flag HFXT
        ADD_BITFIELD_RO(FCNTHFIFG, 9, 1)
        // Start fault counter interrupt flag HFXT2
        ADD_BITFIELD_RO(FCNTHF2IFG, 11, 1)
        // PLL out-of-lock interrupt flag
        ADD_BITFIELD_RO(PLLOOLIFG, 12, 1)
        // PLL loss-of-signal interrupt flag
        ADD_BITFIELD_RO(PLLLOSIFG, 13, 1)
        // PLL out-of-range interrupt flag
        ADD_BITFIELD_RO(PLLOORIFG, 14, 1)
        // REFCNT period counter expired
        ADD_BITFIELD_RO(CALIFG, 15, 1)
    END_TYPE()

    // No fault condition occurred after the last reset
    static const uint32_t CSIFG_LFXTIFG__LFXTIFG_0 = 0;
    // LFXT fault. A LFXT fault occurred after the last reset
    static const uint32_t CSIFG_LFXTIFG__LFXTIFG_1 = 1;
    // No fault condition occurred after the last reset
    static const uint32_t CSIFG_HFXTIFG__HFXTIFG_0 = 0;
    // HFXT fault. A HFXT fault occurred after the last reset
    static const uint32_t CSIFG_HFXTIFG__HFXTIFG_1 = 1;
    // No fault condition occurred after the last reset
    static const uint32_t CSIFG_HFXT2IFG__HFXT2IFG_0 = 0;
    // HFXT2 fault. A HFXT2 fault occurred after the last reset
    static const uint32_t CSIFG_HFXT2IFG__HFXT2IFG_1 = 1;
    // DCO external resistor present
    static const uint32_t CSIFG_DCOR_SHTIFG__DCOR_SHTIFG_0 = 0;
    // DCO external resistor short circuit fault
    static const uint32_t CSIFG_DCOR_SHTIFG__DCOR_SHTIFG_1 = 1;
    // DCO external resistor present
    static const uint32_t CSIFG_DCOR_OPNIFG__DCOR_OPNIFG_0 = 0;
    // DCO external resistor open circuit fault
    static const uint32_t CSIFG_DCOR_OPNIFG__DCOR_OPNIFG_1 = 1;
    // Start counter not expired
    static const uint32_t CSIFG_FCNTLFIFG__FCNTLFIFG_0 = 0;
    // Start counter expired
    static const uint32_t CSIFG_FCNTLFIFG__FCNTLFIFG_1 = 1;
    // Start counter not expired
    static const uint32_t CSIFG_FCNTHFIFG__FCNTHFIFG_0 = 0;
    // Start counter expired
    static const uint32_t CSIFG_FCNTHFIFG__FCNTHFIFG_1 = 1;
    // Start counter not expired
    static const uint32_t CSIFG_FCNTHF2IFG__FCNTHF2IFG_0 = 0;
    // Start counter expired
    static const uint32_t CSIFG_FCNTHF2IFG__FCNTHF2IFG_1 = 1;
    // No interrupt pending
    static const uint32_t CSIFG_PLLOOLIFG__PLLOOLIFG_0 = 0;
    // Interrupt pending
    static const uint32_t CSIFG_PLLOOLIFG__PLLOOLIFG_1 = 1;
    // No interrupt pending
    static const uint32_t CSIFG_PLLLOSIFG__PLLLOSIFG_0 = 0;
    // Interrupt pending
    static const uint32_t CSIFG_PLLLOSIFG__PLLLOSIFG_1 = 1;
    // No interrupt pending
    static const uint32_t CSIFG_PLLOORIFG__PLLOORIFG_0 = 0;
    // Interrupt pending
    static const uint32_t CSIFG_PLLOORIFG__PLLOORIFG_1 = 1;
    // REFCNT period counter not expired
    static const uint32_t CSIFG_CALIFG__CALIFG_0 = 0;
    // REFCNT period counter expired
    static const uint32_t CSIFG_CALIFG__CALIFG_1 = 1;

    // Clear Interrupt Flag Register
    // Reset value: 0x00000000
    BEGIN_TYPE(CSCLRIFG_t, uint32_t)
        // Clear LFXT oscillator fault interrupt flag
        ADD_BITFIELD_WO(CLR_LFXTIFG, 0, 1)
        // Clear HFXT oscillator fault interrupt flag
        ADD_BITFIELD_WO(CLR_HFXTIFG, 1, 1)
        // Clear HFXT2 oscillator fault interrupt flag
        ADD_BITFIELD_WO(CLR_HFXT2IFG, 2, 1)
        // Clear DCO external resistor open circuit fault interrupt flag.
        ADD_BITFIELD_WO(CLR_DCOR_OPNIFG, 6, 1)
        // REFCNT period counter clear interrupt flag
        ADD_BITFIELD_WO(CLR_CALIFG, 15, 1)
        // Start fault counter clear interrupt flag LFXT
        ADD_BITFIELD_WO(CLR_FCNTLFIFG, 8, 1)
        // Start fault counter clear interrupt flag HFXT
        ADD_BITFIELD_WO(CLR_FCNTHFIFG, 9, 1)
        // Start fault counter clear interrupt flag HFXT2
        ADD_BITFIELD_WO(CLR_FCNTHF2IFG, 10, 1)
        // PLL out-of-lock clear interrupt flag
        ADD_BITFIELD_WO(CLR_PLLOOLIFG, 12, 1)
        // PLL loss-of-signal clear interrupt flag
        ADD_BITFIELD_WO(CLR_PLLLOSIFG, 13, 1)
        // PLL out-of-range clear interrupt flag
        ADD_BITFIELD_WO(CLR_PLLOORIFG, 14, 1)
    END_TYPE()

    // No effect
    static const uint32_t CSCLRIFG_CLR_LFXTIFG__CLR_LFXTIFG_0 = 0;
    // Clear pending interrupt flag
    static const uint32_t CSCLRIFG_CLR_LFXTIFG__CLR_LFXTIFG_1 = 1;
    // No effect
    static const uint32_t CSCLRIFG_CLR_HFXTIFG__CLR_HFXTIFG_0 = 0;
    // Clear pending interrupt flag
    static const uint32_t CSCLRIFG_CLR_HFXTIFG__CLR_HFXTIFG_1 = 1;
    // No effect
    static const uint32_t CSCLRIFG_CLR_HFXT2IFG__CLR_HFXT2IFG_0 = 0;
    // Clear pending interrupt flag
    static const uint32_t CSCLRIFG_CLR_HFXT2IFG__CLR_HFXT2IFG_1 = 1;
    // No effect
    static const uint32_t CSCLRIFG_CLR_DCOR_OPNIFG__CLR_DCOR_OPNIFG_0 = 0;
    // Clear pending interrupt flag
    static const uint32_t CSCLRIFG_CLR_DCOR_OPNIFG__CLR_DCOR_OPNIFG_1 = 1;
    // No effect
    static const uint32_t CSCLRIFG_CLR_CALIFG__CLR_CALIFG_0 = 0;
    // Clear pending interrupt flag
    static const uint32_t CSCLRIFG_CLR_CALIFG__CLR_CALIFG_1 = 1;
    // No effect
    static const uint32_t CSCLRIFG_CLR_FCNTLFIFG__CLR_FCNTLFIFG_0 = 0;
    // Clear pending interrupt flag
    static const uint32_t CSCLRIFG_CLR_FCNTLFIFG__CLR_FCNTLFIFG_1 = 1;
    // No effect
    static const uint32_t CSCLRIFG_CLR_FCNTHFIFG__CLR_FCNTHFIFG_0 = 0;
    // Clear pending interrupt flag
    static const uint32_t CSCLRIFG_CLR_FCNTHFIFG__CLR_FCNTHFIFG_1 = 1;
    // No effect
    static const uint32_t CSCLRIFG_CLR_FCNTHF2IFG__CLR_FCNTHF2IFG_0 = 0;
    // Clear pending interrupt flag
    static const uint32_t CSCLRIFG_CLR_FCNTHF2IFG__CLR_FCNTHF2IFG_1 = 1;
    // No effect
    static const uint32_t CSCLRIFG_CLR_PLLOOLIFG__CLR_PLLOOLIFG_0 = 0;
    // Clear pending interrupt flag
    static const uint32_t CSCLRIFG_CLR_PLLOOLIFG__CLR_PLLOOLIFG_1 = 1;
    // No effect
    static const uint32_t CSCLRIFG_CLR_PLLLOSIFG__CLR_PLLLOSIFG_0 = 0;
    // Clear pending interrupt flag
    static const uint32_t CSCLRIFG_CLR_PLLLOSIFG__CLR_PLLLOSIFG_1 = 1;
    // No effect
    static const uint32_t CSCLRIFG_CLR_PLLOORIFG__CLR_PLLOORIFG_0 = 0;
    // Clear pending interrupt flag
    static const uint32_t CSCLRIFG_CLR_PLLOORIFG__CLR_PLLOORIFG_1 = 1;

    // Set Interrupt Flag Register
    // Reset value: 0x00000000
    BEGIN_TYPE(CSSETIFG_t, uint32_t)
        // Set LFXT oscillator fault interrupt flag
        ADD_BITFIELD_WO(SET_LFXTIFG, 0, 1)
        // Set HFXT oscillator fault interrupt flag
        ADD_BITFIELD_WO(SET_HFXTIFG, 1, 1)
        // Set HFXT2 oscillator fault interrupt flag
        ADD_BITFIELD_WO(SET_HFXT2IFG, 2, 1)
        // Set DCO external resistor open circuit fault interrupt flag.
        ADD_BITFIELD_WO(SET_DCOR_OPNIFG, 6, 1)
        // REFCNT period counter set interrupt flag
        ADD_BITFIELD_WO(SET_CALIFG, 15, 1)
        // Start fault counter set interrupt flag HFXT
        ADD_BITFIELD_WO(SET_FCNTHFIFG, 9, 1)
        // Start fault counter set interrupt flag HFXT2
        ADD_BITFIELD_WO(SET_FCNTHF2IFG, 10, 1)
        // Start fault counter set interrupt flag LFXT
        ADD_BITFIELD_WO(SET_FCNTLFIFG, 8, 1)
        // PLL out-of-lock set interrupt flag
        ADD_BITFIELD_WO(SET_PLLOOLIFG, 12, 1)
        // PLL loss-of-signal set interrupt flag
        ADD_BITFIELD_WO(SET_PLLLOSIFG, 13, 1)
        // PLL out-of-range set interrupt flag
        ADD_BITFIELD_WO(SET_PLLOORIFG, 14, 1)
    END_TYPE()

    // No effect
    static const uint32_t CSSETIFG_SET_LFXTIFG__SET_LFXTIFG_0 = 0;
    // Set pending interrupt flag
    static const uint32_t CSSETIFG_SET_LFXTIFG__SET_LFXTIFG_1 = 1;
    // No effect
    static const uint32_t CSSETIFG_SET_HFXTIFG__SET_HFXTIFG_0 = 0;
    // Set pending interrupt flag
    static const uint32_t CSSETIFG_SET_HFXTIFG__SET_HFXTIFG_1 = 1;
    // No effect
    static const uint32_t CSSETIFG_SET_HFXT2IFG__SET_HFXT2IFG_0 = 0;
    // Set pending interrupt flag
    static const uint32_t CSSETIFG_SET_HFXT2IFG__SET_HFXT2IFG_1 = 1;
    // No effect
    static const uint32_t CSSETIFG_SET_DCOR_OPNIFG__SET_DCOR_OPNIFG_0 = 0;
    // Set pending interrupt flag
    static const uint32_t CSSETIFG_SET_DCOR_OPNIFG__SET_DCOR_OPNIFG_1 = 1;
    // No effect
    static const uint32_t CSSETIFG_SET_CALIFG__SET_CALIFG_0 = 0;
    // Set pending interrupt flag
    static const uint32_t CSSETIFG_SET_CALIFG__SET_CALIFG_1 = 1;
    // No effect
    static const uint32_t CSSETIFG_SET_FCNTHFIFG__SET_FCNTHFIFG_0 = 0;
    // Set pending interrupt flag
    static const uint32_t CSSETIFG_SET_FCNTHFIFG__SET_FCNTHFIFG_1 = 1;
    // No effect
    static const uint32_t CSSETIFG_SET_FCNTHF2IFG__SET_FCNTHF2IFG_0 = 0;
    // Set pending interrupt flag
    static const uint32_t CSSETIFG_SET_FCNTHF2IFG__SET_FCNTHF2IFG_1 = 1;
    // No effect
    static const uint32_t CSSETIFG_SET_FCNTLFIFG__SET_FCNTLFIFG_0 = 0;
    // Set pending interrupt flag
    static const uint32_t CSSETIFG_SET_FCNTLFIFG__SET_FCNTLFIFG_1 = 1;
    // No effect
    static const uint32_t CSSETIFG_SET_PLLOOLIFG__SET_PLLOOLIFG_0 = 0;
    // Set pending interrupt flag
    static const uint32_t CSSETIFG_SET_PLLOOLIFG__SET_PLLOOLIFG_1 = 1;
    // No effect
    static const uint32_t CSSETIFG_SET_PLLLOSIFG__SET_PLLLOSIFG_0 = 0;
    // Set pending interrupt flag
    static const uint32_t CSSETIFG_SET_PLLLOSIFG__SET_PLLLOSIFG_1 = 1;
    // No effect
    static const uint32_t CSSETIFG_SET_PLLOORIFG__SET_PLLOORIFG_0 = 0;
    // Set pending interrupt flag
    static const uint32_t CSSETIFG_SET_PLLOORIFG__SET_PLLOORIFG_1 = 1;

    // DCO External Resistor Cailbration 0 Register
    // Reset value: 0x01000000
    BEGIN_TYPE(CSDCOERCAL0_t, uint32_t)
        // DCO Temperature compensation calibration
        ADD_BITFIELD_RW(DCO_TCCAL, 0, 2)
        // DCO frequency calibration for DCO frequency range (DCORSEL) 0 to 4.
        ADD_BITFIELD_RW(DCO_FCAL_RSEL04, 16, 10)
    END_TYPE()

    // DCO External Resistor Calibration 1 Register
    // Reset value: 0x00000100
    BEGIN_TYPE(CSDCOERCAL1_t, uint32_t)
        // DCO frequency calibration for DCO frequency range (DCORSEL) 5.
        ADD_BITFIELD_RW(DCO_FCAL_RSEL5, 0, 10)
    END_TYPE()

    struct CS_t {
        CSKEY_t                       CSKEY;
        CSCTL0_t                      CSCTL0;
        CSCTL1_t                      CSCTL1;
        CSCTL2_t                      CSCTL2;
        CSCTL3_t                      CSCTL3;
        uint32_t                      reserved0[7];
        CSCLKEN_t                     CSCLKEN;
        CSSTAT_t                      CSSTAT;
        uint32_t                      reserved1[2];
        CSIE_t                        CSIE;
        uint32_t                      reserved2;
        CSIFG_t                       CSIFG;
        uint32_t                      reserved3;
        CSCLRIFG_t                    CSCLRIFG;
        uint32_t                      reserved4;
        CSSETIFG_t                    CSSETIFG;
        uint32_t                      reserved5;
        CSDCOERCAL0_t                 CSDCOERCAL0;
        CSDCOERCAL1_t                 CSDCOERCAL1;
    };

    static CS_t & CS     = (*(CS_t *)0x40010400);

} // _CS_

// PSS
namespace _PSS_  {

    // Key Register
    // Reset value: 0x0000a596
    BEGIN_TYPE(PSSKEY_t, uint32_t)
        // PSS control key
        ADD_BITFIELD_RW(PSSKEY, 0, 16)
    END_TYPE()

    // Control 0 Register
    // Reset value: 0x00002000
    BEGIN_TYPE(PSSCTL0_t, uint32_t)
        // SVSM high-side off
        ADD_BITFIELD_RW(SVSMHOFF, 0, 1)
        // SVSM high-side low power normal performance mode
        ADD_BITFIELD_RW(SVSMHLP, 1, 1)
        // Supply supervisor or monitor selection for the high-side
        ADD_BITFIELD_RW(SVSMHS, 2, 1)
        // SVSM high-side reset voltage level
        ADD_BITFIELD_RW(SVSMHTH, 3, 3)
        // SVSM high-side output enable
        ADD_BITFIELD_RW(SVMHOE, 6, 1)
        // SVMHOUT pin polarity active low
        ADD_BITFIELD_RW(SVMHOUTPOLAL, 7, 1)
        // Force DC-DC regulator operation
        ADD_BITFIELD_RW(DCDC_FORCE, 10, 1)
        // Controls core voltage level transition time
        ADD_BITFIELD_RW(VCORETRAN, 12, 2)
    END_TYPE()

    // The SVSMH is on
    static const uint32_t PSSCTL0_SVSMHOFF__SVSMHOFF_0 = 0;
    // The SVSMH is off
    static const uint32_t PSSCTL0_SVSMHOFF__SVSMHOFF_1 = 1;
    // Full performance mode. See the device-specific data sheet for response times.
    static const uint32_t PSSCTL0_SVSMHLP__SVSMHLP_0 = 0;
    // Low power normal performance mode in LPM3, LPM4, and LPMx.5, full performance in all other modes. See the device-specific data sheet for response times.
    static const uint32_t PSSCTL0_SVSMHLP__SVSMHLP_1 = 1;
    // Configure as SVSH
    static const uint32_t PSSCTL0_SVSMHS__SVSMHS_0 = 0;
    // Configure as SVMH
    static const uint32_t PSSCTL0_SVSMHS__SVSMHS_1 = 1;
    // SVSMHIFG bit is not output
    static const uint32_t PSSCTL0_SVMHOE__SVMHOE_0 = 0;
    // SVSMHIFG bit is output to the device SVMHOUT pin. The device-specific port logic must be configured accordingly
    static const uint32_t PSSCTL0_SVMHOE__SVMHOE_1 = 1;
    // SVMHOUT is active high. An error condition is signaled by a 1 at the SVMHOUT pin
    static const uint32_t PSSCTL0_SVMHOUTPOLAL__SVMHOUTPOLAL_0 = 0;
    // SVMHOUT is active low. An error condition is signaled by a 0 at the SVMHOUT pin
    static const uint32_t PSSCTL0_SVMHOUTPOLAL__SVMHOUTPOLAL_1 = 1;
    // DC-DC regulator operation not forced. Automatic fail-safe mechanism switches the core voltage regulator from DC-DC to LDO when the supply voltage falls below the minimum supply voltage necessary for DC-DC operation.
    static const uint32_t PSSCTL0_DCDC_FORCE__DCDC_FORCE_0 = 0;
    // DC-DC regulator operation forced. Automatic fail-safe mechanism is disabled and device continues to operate out of DC-DC regulator.
    static const uint32_t PSSCTL0_DCDC_FORCE__DCDC_FORCE_1 = 1;
    // 32 s / 100 mV
    static const uint32_t PSSCTL0_VCORETRAN__VCORETRAN_0 = 0;
    // 64 s / 100 mV
    static const uint32_t PSSCTL0_VCORETRAN__VCORETRAN_1 = 1;
    // 128 s / 100 mV (default)
    static const uint32_t PSSCTL0_VCORETRAN__VCORETRAN_2 = 2;
    // 256 s / 100 mV
    static const uint32_t PSSCTL0_VCORETRAN__VCORETRAN_3 = 3;

    // Interrupt Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(PSSIE_t, uint32_t)
        // High-side SVSM interrupt enable
        ADD_BITFIELD_RW(SVSMHIE, 1, 1)
    END_TYPE()

    // Interrupt disabled
    static const uint32_t PSSIE_SVSMHIE__SVSMHIE_0 = 0;
    // Interrupt enabled
    static const uint32_t PSSIE_SVSMHIE__SVSMHIE_1 = 1;

    // Interrupt Flag Register
    // Reset value: 0x00000000
    BEGIN_TYPE(PSSIFG_t, uint32_t)
        // High-side SVSM interrupt flag
        ADD_BITFIELD_RO(SVSMHIFG, 1, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t PSSIFG_SVSMHIFG__SVSMHIFG_0 = 0;
    // Interrupt due to SVSMH
    static const uint32_t PSSIFG_SVSMHIFG__SVSMHIFG_1 = 1;

    // Clear Interrupt Flag Register
    // Reset value: 0x00000000
    BEGIN_TYPE(PSSCLRIFG_t, uint32_t)
        // SVSMH clear interrupt flag
        ADD_BITFIELD_WO(CLRSVSMHIFG, 1, 1)
    END_TYPE()

    // No effect
    static const uint32_t PSSCLRIFG_CLRSVSMHIFG__CLRSVSMHIFG_0 = 0;
    // Clear pending interrupt flag
    static const uint32_t PSSCLRIFG_CLRSVSMHIFG__CLRSVSMHIFG_1 = 1;

    struct PSS_t {
        PSSKEY_t                      PSSKEY;
        PSSCTL0_t                     PSSCTL0;
        uint32_t                      reserved0[11];
        PSSIE_t                       PSSIE;
        PSSIFG_t                      PSSIFG;
        PSSCLRIFG_t                   PSSCLRIFG;
    };

    static PSS_t & PSS     = (*(PSS_t *)0x40010800);

} // _PSS_

// FLCTL
namespace _FLCTL_  {

    // Power Status Register
    // Reset value: 0x00000080
    BEGIN_TYPE(FLCTL_POWER_STAT_t, uint32_t)
        // Flash power status
        ADD_BITFIELD_RO(PSTAT, 0, 3)
        // PSS FLDO GOOD status
        ADD_BITFIELD_RO(LDOSTAT, 3, 1)
        // PSS VREF stable status
        ADD_BITFIELD_RO(VREFSTAT, 4, 1)
        // PSS IREF stable status
        ADD_BITFIELD_RO(IREFSTAT, 5, 1)
        // PSS trim done status
        ADD_BITFIELD_RO(TRIMSTAT, 6, 1)
        // Indicates if Flash is being accessed in 2T mode
        ADD_BITFIELD_RO(RD_2T, 7, 1)
    END_TYPE()

    // Flash IP in power-down mode
    static const uint32_t FLCTL_POWER_STAT_PSTAT__PSTAT_0 = 0;
    // Flash IP Vdd domain power-up in progress
    static const uint32_t FLCTL_POWER_STAT_PSTAT__PSTAT_1 = 1;
    // PSS LDO_GOOD, IREF_OK and VREF_OK check in progress
    static const uint32_t FLCTL_POWER_STAT_PSTAT__PSTAT_2 = 2;
    // Flash IP SAFE_LV check in progress
    static const uint32_t FLCTL_POWER_STAT_PSTAT__PSTAT_3 = 3;
    // Flash IP Active
    static const uint32_t FLCTL_POWER_STAT_PSTAT__PSTAT_4 = 4;
    // Flash IP Active in Low-Frequency Active and Low-Frequency LPM0 modes.
    static const uint32_t FLCTL_POWER_STAT_PSTAT__PSTAT_5 = 5;
    // Flash IP in Standby mode
    static const uint32_t FLCTL_POWER_STAT_PSTAT__PSTAT_6 = 6;
    // Flash IP in Current mirror boost state
    static const uint32_t FLCTL_POWER_STAT_PSTAT__PSTAT_7 = 7;
    // FLDO not GOOD
    static const uint32_t FLCTL_POWER_STAT_LDOSTAT__LDOSTAT_0 = 0;
    // FLDO GOOD
    static const uint32_t FLCTL_POWER_STAT_LDOSTAT__LDOSTAT_1 = 1;
    // Flash LDO not stable
    static const uint32_t FLCTL_POWER_STAT_VREFSTAT__VREFSTAT_0 = 0;
    // Flash LDO stable
    static const uint32_t FLCTL_POWER_STAT_VREFSTAT__VREFSTAT_1 = 1;
    // IREF not stable
    static const uint32_t FLCTL_POWER_STAT_IREFSTAT__IREFSTAT_0 = 0;
    // IREF stable
    static const uint32_t FLCTL_POWER_STAT_IREFSTAT__IREFSTAT_1 = 1;
    // PSS trim not complete
    static const uint32_t FLCTL_POWER_STAT_TRIMSTAT__TRIMSTAT_0 = 0;
    // PSS trim complete
    static const uint32_t FLCTL_POWER_STAT_TRIMSTAT__TRIMSTAT_1 = 1;
    // Flash reads are in 1T mode
    static const uint32_t FLCTL_POWER_STAT_RD_2T__RD_2T_0 = 0;
    // Flash reads are in 2T mode
    static const uint32_t FLCTL_POWER_STAT_RD_2T__RD_2T_1 = 1;

    // Bank0 Read Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_BANK0_RDCTL_t, uint32_t)
        // Flash read mode control setting for Bank 0
        ADD_BITFIELD_RW(RD_MODE, 0, 4)
        // Enables read buffering feature for instruction fetches to this Bank
        ADD_BITFIELD_RW(BUFI, 4, 1)
        // Enables read buffering feature for data reads to this Bank
        ADD_BITFIELD_RW(BUFD, 5, 1)
        // Number of wait states for read
        ADD_BITFIELD_RW(WAIT, 12, 4)
        // Read mode
        ADD_BITFIELD_RO(RD_MODE_STATUS, 16, 4)
    END_TYPE()

    // Normal read mode
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE__RD_MODE_0 = 0;
    // Read Margin 0
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE__RD_MODE_1 = 1;
    // Read Margin 1
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE__RD_MODE_2 = 2;
    // Program Verify
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE__RD_MODE_3 = 3;
    // Erase Verify
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE__RD_MODE_4 = 4;
    // Leakage Verify
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE__RD_MODE_5 = 5;
    // Read Margin 0B
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE__RD_MODE_9 = 9;
    // Read Margin 1B
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE__RD_MODE_10 = 10;
    // 0 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_0 = 0;
    // 1 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_1 = 1;
    // 2 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_2 = 2;
    // 3 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_3 = 3;
    // 4 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_4 = 4;
    // 5 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_5 = 5;
    // 6 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_6 = 6;
    // 7 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_7 = 7;
    // 8 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_8 = 8;
    // 9 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_9 = 9;
    // 10 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_10 = 10;
    // 11 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_11 = 11;
    // 12 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_12 = 12;
    // 13 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_13 = 13;
    // 14 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_14 = 14;
    // 15 wait states
    static const uint32_t FLCTL_BANK0_RDCTL_WAIT__WAIT_15 = 15;
    // Normal read mode
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_0 = 0;
    // Read Margin 0
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_1 = 1;
    // Read Margin 1
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_2 = 2;
    // Program Verify
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_3 = 3;
    // Erase Verify
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_4 = 4;
    // Leakage Verify
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_5 = 5;
    // Read Margin 0B
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_9 = 9;
    // Read Margin 1B
    static const uint32_t FLCTL_BANK0_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_10 = 10;

    // Bank1 Read Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_BANK1_RDCTL_t, uint32_t)
        // Flash read mode control setting for Bank 0
        ADD_BITFIELD_RW(RD_MODE, 0, 4)
        // Enables read buffering feature for instruction fetches to this Bank
        ADD_BITFIELD_RW(BUFI, 4, 1)
        // Enables read buffering feature for data reads to this Bank
        ADD_BITFIELD_RW(BUFD, 5, 1)
        // Read mode
        ADD_BITFIELD_RO(RD_MODE_STATUS, 16, 4)
        // Number of wait states for read
        ADD_BITFIELD_RW(WAIT, 12, 4)
    END_TYPE()

    // Normal read mode
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE__RD_MODE_0 = 0;
    // Read Margin 0
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE__RD_MODE_1 = 1;
    // Read Margin 1
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE__RD_MODE_2 = 2;
    // Program Verify
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE__RD_MODE_3 = 3;
    // Erase Verify
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE__RD_MODE_4 = 4;
    // Leakage Verify
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE__RD_MODE_5 = 5;
    // Read Margin 0B
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE__RD_MODE_9 = 9;
    // Read Margin 1B
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE__RD_MODE_10 = 10;
    // Normal read mode
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_0 = 0;
    // Read Margin 0
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_1 = 1;
    // Read Margin 1
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_2 = 2;
    // Program Verify
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_3 = 3;
    // Erase Verify
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_4 = 4;
    // Leakage Verify
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_5 = 5;
    // Read Margin 0B
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_9 = 9;
    // Read Margin 1B
    static const uint32_t FLCTL_BANK1_RDCTL_RD_MODE_STATUS__RD_MODE_STATUS_10 = 10;
    // 0 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_0 = 0;
    // 1 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_1 = 1;
    // 2 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_2 = 2;
    // 3 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_3 = 3;
    // 4 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_4 = 4;
    // 5 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_5 = 5;
    // 6 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_6 = 6;
    // 7 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_7 = 7;
    // 8 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_8 = 8;
    // 9 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_9 = 9;
    // 10 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_10 = 10;
    // 11 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_11 = 11;
    // 12 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_12 = 12;
    // 13 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_13 = 13;
    // 14 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_14 = 14;
    // 15 wait states
    static const uint32_t FLCTL_BANK1_RDCTL_WAIT__WAIT_15 = 15;

    // Read Burst/Compare Control and Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_RDBRST_CTLSTAT_t, uint32_t)
        // Start of burst/compare operation
        ADD_BITFIELD_WO(START, 0, 1)
        // Type of memory that burst is carried out on
        ADD_BITFIELD_RW(MEM_TYPE, 1, 2)
        // Terminate burst/compare operation
        ADD_BITFIELD_RW(STOP_FAIL, 3, 1)
        // Data pattern used for comparison against memory read data
        ADD_BITFIELD_RW(DATA_CMP, 4, 1)
        // Enable comparison against test data compare registers
        ADD_BITFIELD_RW(TEST_EN, 6, 1)
        // Status of Burst/Compare operation
        ADD_BITFIELD_RO(BRST_STAT, 16, 2)
        // Burst/Compare Operation encountered atleast one data
        ADD_BITFIELD_RO(CMP_ERR, 18, 1)
        // Burst/Compare Operation was terminated due to access to
        ADD_BITFIELD_RO(ADDR_ERR, 19, 1)
        // Clear status bits 19-16 of this register
        ADD_BITFIELD_WO(CLR_STAT, 23, 1)
    END_TYPE()

    // Main Memory
    static const uint32_t FLCTL_RDBRST_CTLSTAT_MEM_TYPE__MEM_TYPE_0 = 0;
    // Information Memory
    static const uint32_t FLCTL_RDBRST_CTLSTAT_MEM_TYPE__MEM_TYPE_1 = 1;
    // Engineering Memory
    static const uint32_t FLCTL_RDBRST_CTLSTAT_MEM_TYPE__MEM_TYPE_3 = 3;
    // 0000_0000_0000_0000_0000_0000_0000_0000
    static const uint32_t FLCTL_RDBRST_CTLSTAT_DATA_CMP__DATA_CMP_0 = 0;
    // FFFF_FFFF_FFFF_FFFF_FFFF_FFFF_FFFF_FFFF
    static const uint32_t FLCTL_RDBRST_CTLSTAT_DATA_CMP__DATA_CMP_1 = 1;
    // Idle
    static const uint32_t FLCTL_RDBRST_CTLSTAT_BRST_STAT__BRST_STAT_0 = 0;
    // Burst/Compare START bit written, but operation pending
    static const uint32_t FLCTL_RDBRST_CTLSTAT_BRST_STAT__BRST_STAT_1 = 1;
    // Burst/Compare in progress
    static const uint32_t FLCTL_RDBRST_CTLSTAT_BRST_STAT__BRST_STAT_2 = 2;
    // Burst complete (status of completed burst remains in this state unless explicitly cleared by SW)
    static const uint32_t FLCTL_RDBRST_CTLSTAT_BRST_STAT__BRST_STAT_3 = 3;

    // Read Burst/Compare Start Address Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_RDBRST_STARTADDR_t, uint32_t)
        // Start Address of Burst Operation
        ADD_BITFIELD_RW(START_ADDRESS, 0, 21)
    END_TYPE()

    // Read Burst/Compare Length Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_RDBRST_LEN_t, uint32_t)
        // Length of Burst Operation
        ADD_BITFIELD_RW(BURST_LENGTH, 0, 21)
    END_TYPE()

    // Read Burst/Compare Fail Address Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_RDBRST_FAILADDR_t, uint32_t)
        // Reflects address of last failed compare
        ADD_BITFIELD_RW(FAIL_ADDRESS, 0, 21)
    END_TYPE()

    // Read Burst/Compare Fail Count Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_RDBRST_FAILCNT_t, uint32_t)
        // Number of failures encountered in burst operation
        ADD_BITFIELD_RW(FAIL_COUNT, 0, 17)
    END_TYPE()

    // Program Control and Status Register
    // Reset value: 0x0000000c
    BEGIN_TYPE(FLCTL_PRG_CTLSTAT_t, uint32_t)
        // Master control for all word program operations
        ADD_BITFIELD_RW(ENABLE, 0, 1)
        // Write mode
        ADD_BITFIELD_RW(MODE, 1, 1)
        // Controls automatic pre program verify operations
        ADD_BITFIELD_RW(VER_PRE, 2, 1)
        // Controls automatic post program verify operations
        ADD_BITFIELD_RW(VER_PST, 3, 1)
        // Status of program operations in the Flash memory
        ADD_BITFIELD_RO(STATUS, 16, 2)
        // Bank active
        ADD_BITFIELD_RO(BNK_ACT, 18, 1)
    END_TYPE()

    // Word program operation disabled
    static const uint32_t FLCTL_PRG_CTLSTAT_ENABLE__ENABLE_0 = 0;
    // Word program operation enabled
    static const uint32_t FLCTL_PRG_CTLSTAT_ENABLE__ENABLE_1 = 1;
    // Write immediate mode. Starts program operation immediately on each write to the Flash
    static const uint32_t FLCTL_PRG_CTLSTAT_MODE__MODE_0 = 0;
    // Full word write mode. Flash controller collates data over multiple writes to compose the full 128bit word before initiating the program operation
    static const uint32_t FLCTL_PRG_CTLSTAT_MODE__MODE_1 = 1;
    // No pre program verification
    static const uint32_t FLCTL_PRG_CTLSTAT_VER_PRE__VER_PRE_0 = 0;
    // Pre verify feature automatically invoked for each write operation (irrespective of the mode)
    static const uint32_t FLCTL_PRG_CTLSTAT_VER_PRE__VER_PRE_1 = 1;
    // No post program verification
    static const uint32_t FLCTL_PRG_CTLSTAT_VER_PST__VER_PST_0 = 0;
    // Post verify feature automatically invoked for each write operation (irrespective of the mode)
    static const uint32_t FLCTL_PRG_CTLSTAT_VER_PST__VER_PST_1 = 1;
    // Idle (no program operation currently active)
    static const uint32_t FLCTL_PRG_CTLSTAT_STATUS__STATUS_0 = 0;
    // Single word program operation triggered, but pending
    static const uint32_t FLCTL_PRG_CTLSTAT_STATUS__STATUS_1 = 1;
    // Single word program in progress
    static const uint32_t FLCTL_PRG_CTLSTAT_STATUS__STATUS_2 = 2;
    // Word in Bank0 being programmed
    static const uint32_t FLCTL_PRG_CTLSTAT_BNK_ACT__BNK_ACT_0 = 0;
    // Word in Bank1 being programmed
    static const uint32_t FLCTL_PRG_CTLSTAT_BNK_ACT__BNK_ACT_1 = 1;

    // Program Burst Control and Status Register
    // Reset value: 0x000000c0
    BEGIN_TYPE(FLCTL_PRGBRST_CTLSTAT_t, uint32_t)
        // Trigger start of burst program operation
        ADD_BITFIELD_WO(START, 0, 1)
        // Type of memory that burst program is carried out on
        ADD_BITFIELD_RW(TYPE, 1, 2)
        // Length of burst
        ADD_BITFIELD_RW(LEN, 3, 3)
        // Auto-Verify operation before the Burst Program
        ADD_BITFIELD_RW(AUTO_PRE, 6, 1)
        // Auto-Verify operation after the Burst Program
        ADD_BITFIELD_RW(AUTO_PST, 7, 1)
        // Status of a Burst Operation
        ADD_BITFIELD_RO(BURST_STATUS, 16, 3)
        // Burst Operation encountered preprogram auto-verify errors
        ADD_BITFIELD_RO(PRE_ERR, 19, 1)
        // Burst Operation encountered postprogram auto-verify errors
        ADD_BITFIELD_RO(PST_ERR, 20, 1)
        // Burst Operation was terminated due to attempted program of reserved memory
        ADD_BITFIELD_RO(ADDR_ERR, 21, 1)
        // Clear status bits 21-16 of this register
        ADD_BITFIELD_WO(CLR_STAT, 23, 1)
    END_TYPE()

    // Main Memory
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_TYPE__TYPE_0 = 0;
    // Information Memory
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_TYPE__TYPE_1 = 1;
    // Engineering Memory
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_TYPE__TYPE_3 = 3;
    // No burst operation
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_LEN__LEN_0 = 0;
    // 1 word burst of 128 bits, starting with address in the FLCTL_PRGBRST_STARTADDR Register
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_LEN__LEN_1 = 1;
    // 2*128 bits burst write, starting with address in the FLCTL_PRGBRST_STARTADDR Register
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_LEN__LEN_2 = 2;
    // 3*128 bits burst write, starting with address in the FLCTL_PRGBRST_STARTADDR Register
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_LEN__LEN_3 = 3;
    // 4*128 bits burst write, starting with address in the FLCTL_PRGBRST_STARTADDR Register
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_LEN__LEN_4 = 4;
    // No program verify operations carried out
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_AUTO_PRE__AUTO_PRE_0 = 0;
    // Causes an automatic Burst Program Verify after the Burst Program Operation
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_AUTO_PRE__AUTO_PRE_1 = 1;
    // No program verify operations carried out
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_AUTO_PST__AUTO_PST_0 = 0;
    // Causes an automatic Burst Program Verify before the Burst Program Operation
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_AUTO_PST__AUTO_PST_1 = 1;
    // Idle (Burst not active)
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_BURST_STATUS__BURST_STATUS_0 = 0;
    // Burst program started but pending
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_BURST_STATUS__BURST_STATUS_1 = 1;
    // Burst active, with 1st 128 bit word being written into Flash
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_BURST_STATUS__BURST_STATUS_2 = 2;
    // Burst active, with 2nd 128 bit word being written into Flash
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_BURST_STATUS__BURST_STATUS_3 = 3;
    // Burst active, with 3rd 128 bit word being written into Flash
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_BURST_STATUS__BURST_STATUS_4 = 4;
    // Burst active, with 4th 128 bit word being written into Flash
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_BURST_STATUS__BURST_STATUS_5 = 5;
    // Burst Complete (status of completed burst remains in this state unless explicitly cleared by SW)
    static const uint32_t FLCTL_PRGBRST_CTLSTAT_BURST_STATUS__BURST_STATUS_7 = 7;

    // Program Burst Start Address Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_PRGBRST_STARTADDR_t, uint32_t)
        // Start Address of Program Burst Operation
        ADD_BITFIELD_RW(START_ADDRESS, 0, 22)
    END_TYPE()

    // Program Burst Data0 Register0
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA0_0_t, uint32_t)
        // Program Burst 128 bit Data Word 0
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data0 Register1
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA0_1_t, uint32_t)
        // Program Burst 128 bit Data Word 0
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data0 Register2
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA0_2_t, uint32_t)
        // Program Burst 128 bit Data Word 0
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data0 Register3
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA0_3_t, uint32_t)
        // Program Burst 128 bit Data Word 0
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data1 Register0
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA1_0_t, uint32_t)
        // Program Burst 128 bit Data Word 1
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data1 Register1
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA1_1_t, uint32_t)
        // Program Burst 128 bit Data Word 1
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data1 Register2
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA1_2_t, uint32_t)
        // Program Burst 128 bit Data Word 1
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data1 Register3
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA1_3_t, uint32_t)
        // Program Burst 128 bit Data Word 1
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data2 Register0
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA2_0_t, uint32_t)
        // Program Burst 128 bit Data Word 2
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data2 Register1
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA2_1_t, uint32_t)
        // Program Burst 128 bit Data Word 2
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data2 Register2
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA2_2_t, uint32_t)
        // Program Burst 128 bit Data Word 2
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data2 Register3
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA2_3_t, uint32_t)
        // Program Burst 128 bit Data Word 2
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data3 Register0
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA3_0_t, uint32_t)
        // Program Burst 128 bit Data Word 3
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data3 Register1
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA3_1_t, uint32_t)
        // Program Burst 128 bit Data Word 3
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data3 Register2
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA3_2_t, uint32_t)
        // Program Burst 128 bit Data Word 3
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Program Burst Data3 Register3
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_PRGBRST_DATA3_3_t, uint32_t)
        // Program Burst 128 bit Data Word 3
        ADD_BITFIELD_RW(DATAIN, 0, 32)
    END_TYPE()

    // Erase Control and Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_ERASE_CTLSTAT_t, uint32_t)
        // Start of Erase operation
        ADD_BITFIELD_WO(START, 0, 1)
        // Erase mode selected by application
        ADD_BITFIELD_RW(MODE, 1, 1)
        // Type of memory that erase operation is carried out on
        ADD_BITFIELD_RW(TYPE, 2, 2)
        // Status of erase operations in the Flash memory
        ADD_BITFIELD_RO(STATUS, 16, 2)
        // Erase Operation was terminated due to attempted erase of reserved memory address
        ADD_BITFIELD_RO(ADDR_ERR, 18, 1)
        // Clear status bits 18-16 of this register
        ADD_BITFIELD_WO(CLR_STAT, 19, 1)
    END_TYPE()

    // Sector Erase (controlled by FLTCTL_ERASE_SECTADDR)
    static const uint32_t FLCTL_ERASE_CTLSTAT_MODE__MODE_0 = 0;
    // Mass Erase (includes all Main and Information memory sectors that don't have corresponding WE bits set)
    static const uint32_t FLCTL_ERASE_CTLSTAT_MODE__MODE_1 = 1;
    // Main Memory
    static const uint32_t FLCTL_ERASE_CTLSTAT_TYPE__TYPE_0 = 0;
    // Information Memory
    static const uint32_t FLCTL_ERASE_CTLSTAT_TYPE__TYPE_1 = 1;
    // Engineering Memory
    static const uint32_t FLCTL_ERASE_CTLSTAT_TYPE__TYPE_3 = 3;
    // Idle (no program operation currently active)
    static const uint32_t FLCTL_ERASE_CTLSTAT_STATUS__STATUS_0 = 0;
    // Erase operation triggered to START but pending
    static const uint32_t FLCTL_ERASE_CTLSTAT_STATUS__STATUS_1 = 1;
    // Erase operation in progress
    static const uint32_t FLCTL_ERASE_CTLSTAT_STATUS__STATUS_2 = 2;
    // Erase operation completed (status of completed erase remains in this state unless explicitly cleared by SW)
    static const uint32_t FLCTL_ERASE_CTLSTAT_STATUS__STATUS_3 = 3;

    // Erase Sector Address Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_ERASE_SECTADDR_t, uint32_t)
        // Address of Sector being Erased
        ADD_BITFIELD_RW(SECT_ADDRESS, 0, 22)
    END_TYPE()

    // Information Memory Bank0 Write/Erase Protection Register
    // Reset value: 0x00000003
    BEGIN_TYPE(FLCTL_BANK0_INFO_WEPROT_t, uint32_t)
        // Protects Sector 0 from program or erase
        ADD_BITFIELD_RW(PROT0, 0, 1)
        // Protects Sector 1 from program or erase
        ADD_BITFIELD_RW(PROT1, 1, 1)
    END_TYPE()

    // Main Memory Bank0 Write/Erase Protection Register
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_BANK0_MAIN_WEPROT_t, uint32_t)
        // Protects Sector 0 from program or erase
        ADD_BITFIELD_RW(PROT0, 0, 1)
        // Protects Sector 1 from program or erase
        ADD_BITFIELD_RW(PROT1, 1, 1)
        // Protects Sector 2 from program or erase
        ADD_BITFIELD_RW(PROT2, 2, 1)
        // Protects Sector 3 from program or erase
        ADD_BITFIELD_RW(PROT3, 3, 1)
        // Protects Sector 4 from program or erase
        ADD_BITFIELD_RW(PROT4, 4, 1)
        // Protects Sector 5 from program or erase
        ADD_BITFIELD_RW(PROT5, 5, 1)
        // Protects Sector 6 from program or erase
        ADD_BITFIELD_RW(PROT6, 6, 1)
        // Protects Sector 7 from program or erase
        ADD_BITFIELD_RW(PROT7, 7, 1)
        // Protects Sector 8 from program or erase
        ADD_BITFIELD_RW(PROT8, 8, 1)
        // Protects Sector 9 from program or erase
        ADD_BITFIELD_RW(PROT9, 9, 1)
        // Protects Sector 10 from program or erase
        ADD_BITFIELD_RW(PROT10, 10, 1)
        // Protects Sector 11 from program or erase
        ADD_BITFIELD_RW(PROT11, 11, 1)
        // Protects Sector 12 from program or erase
        ADD_BITFIELD_RW(PROT12, 12, 1)
        // Protects Sector 13 from program or erase
        ADD_BITFIELD_RW(PROT13, 13, 1)
        // Protects Sector 14 from program or erase
        ADD_BITFIELD_RW(PROT14, 14, 1)
        // Protects Sector 15 from program or erase
        ADD_BITFIELD_RW(PROT15, 15, 1)
        // Protects Sector 16 from program or erase
        ADD_BITFIELD_RW(PROT16, 16, 1)
        // Protects Sector 17 from program or erase
        ADD_BITFIELD_RW(PROT17, 17, 1)
        // Protects Sector 18 from program or erase
        ADD_BITFIELD_RW(PROT18, 18, 1)
        // Protects Sector 19 from program or erase
        ADD_BITFIELD_RW(PROT19, 19, 1)
        // Protects Sector 20 from program or erase
        ADD_BITFIELD_RW(PROT20, 20, 1)
        // Protects Sector 21 from program or erase
        ADD_BITFIELD_RW(PROT21, 21, 1)
        // Protects Sector 22 from program or erase
        ADD_BITFIELD_RW(PROT22, 22, 1)
        // Protects Sector 23 from program or erase
        ADD_BITFIELD_RW(PROT23, 23, 1)
        // Protects Sector 24 from program or erase
        ADD_BITFIELD_RW(PROT24, 24, 1)
        // Protects Sector 25 from program or erase
        ADD_BITFIELD_RW(PROT25, 25, 1)
        // Protects Sector 26 from program or erase
        ADD_BITFIELD_RW(PROT26, 26, 1)
        // Protects Sector 27 from program or erase
        ADD_BITFIELD_RW(PROT27, 27, 1)
        // Protects Sector 28 from program or erase
        ADD_BITFIELD_RW(PROT28, 28, 1)
        // Protects Sector 29 from program or erase
        ADD_BITFIELD_RW(PROT29, 29, 1)
        // Protects Sector 30 from program or erase
        ADD_BITFIELD_RW(PROT30, 30, 1)
        // Protects Sector 31 from program or erase
        ADD_BITFIELD_RW(PROT31, 31, 1)
    END_TYPE()

    // Information Memory Bank1 Write/Erase Protection Register
    // Reset value: 0x00000003
    BEGIN_TYPE(FLCTL_BANK1_INFO_WEPROT_t, uint32_t)
        // Protects Sector 0 from program or erase operations
        ADD_BITFIELD_RW(PROT0, 0, 1)
        // Protects Sector 1 from program or erase operations
        ADD_BITFIELD_RW(PROT1, 1, 1)
    END_TYPE()

    // Main Memory Bank1 Write/Erase Protection Register
    // Reset value: 0xffffffff
    BEGIN_TYPE(FLCTL_BANK1_MAIN_WEPROT_t, uint32_t)
        // Protects Sector 0 from program or erase operations
        ADD_BITFIELD_RW(PROT0, 0, 1)
        // Protects Sector 1 from program or erase operations
        ADD_BITFIELD_RW(PROT1, 1, 1)
        // Protects Sector 2 from program or erase operations
        ADD_BITFIELD_RW(PROT2, 2, 1)
        // Protects Sector 3 from program or erase operations
        ADD_BITFIELD_RW(PROT3, 3, 1)
        // Protects Sector 4 from program or erase operations
        ADD_BITFIELD_RW(PROT4, 4, 1)
        // Protects Sector 5 from program or erase operations
        ADD_BITFIELD_RW(PROT5, 5, 1)
        // Protects Sector 6 from program or erase operations
        ADD_BITFIELD_RW(PROT6, 6, 1)
        // Protects Sector 7 from program or erase operations
        ADD_BITFIELD_RW(PROT7, 7, 1)
        // Protects Sector 8 from program or erase operations
        ADD_BITFIELD_RW(PROT8, 8, 1)
        // Protects Sector 9 from program or erase operations
        ADD_BITFIELD_RW(PROT9, 9, 1)
        // Protects Sector 10 from program or erase operations
        ADD_BITFIELD_RW(PROT10, 10, 1)
        // Protects Sector 11 from program or erase operations
        ADD_BITFIELD_RW(PROT11, 11, 1)
        // Protects Sector 12 from program or erase operations
        ADD_BITFIELD_RW(PROT12, 12, 1)
        // Protects Sector 13 from program or erase operations
        ADD_BITFIELD_RW(PROT13, 13, 1)
        // Protects Sector 14 from program or erase operations
        ADD_BITFIELD_RW(PROT14, 14, 1)
        // Protects Sector 15 from program or erase operations
        ADD_BITFIELD_RW(PROT15, 15, 1)
        // Protects Sector 16 from program or erase operations
        ADD_BITFIELD_RW(PROT16, 16, 1)
        // Protects Sector 17 from program or erase operations
        ADD_BITFIELD_RW(PROT17, 17, 1)
        // Protects Sector 18 from program or erase operations
        ADD_BITFIELD_RW(PROT18, 18, 1)
        // Protects Sector 19 from program or erase operations
        ADD_BITFIELD_RW(PROT19, 19, 1)
        // Protects Sector 20 from program or erase operations
        ADD_BITFIELD_RW(PROT20, 20, 1)
        // Protects Sector 21 from program or erase operations
        ADD_BITFIELD_RW(PROT21, 21, 1)
        // Protects Sector 22 from program or erase operations
        ADD_BITFIELD_RW(PROT22, 22, 1)
        // Protects Sector 23 from program or erase operations
        ADD_BITFIELD_RW(PROT23, 23, 1)
        // Protects Sector 24 from program or erase operations
        ADD_BITFIELD_RW(PROT24, 24, 1)
        // Protects Sector 25 from program or erase operations
        ADD_BITFIELD_RW(PROT25, 25, 1)
        // Protects Sector 26 from program or erase operations
        ADD_BITFIELD_RW(PROT26, 26, 1)
        // Protects Sector 27 from program or erase operations
        ADD_BITFIELD_RW(PROT27, 27, 1)
        // Protects Sector 28 from program or erase operations
        ADD_BITFIELD_RW(PROT28, 28, 1)
        // Protects Sector 29 from program or erase operations
        ADD_BITFIELD_RW(PROT29, 29, 1)
        // Protects Sector 30 from program or erase operations
        ADD_BITFIELD_RW(PROT30, 30, 1)
        // Protects Sector 31 from program or erase operations
        ADD_BITFIELD_RW(PROT31, 31, 1)
    END_TYPE()

    // Benchmark Control and Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_BMRK_CTLSTAT_t, uint32_t)
        // When 1, increments the Instruction Benchmark count register on each instruction fetch to the Flash
        ADD_BITFIELD_RW(I_BMRK, 0, 1)
        // When 1, increments the Data Benchmark count register on each data read access to the Flash
        ADD_BITFIELD_RW(D_BMRK, 1, 1)
        // When 1, enables comparison of the Instruction or Data Benchmark Registers against the threshold value
        ADD_BITFIELD_RW(CMP_EN, 2, 1)
        // Selects which benchmark register should be compared against the threshold
        ADD_BITFIELD_RW(CMP_SEL, 3, 1)
    END_TYPE()

    // Compares the Instruction Benchmark Register against the threshold value
    static const uint32_t FLCTL_BMRK_CTLSTAT_CMP_SEL__en_1_0x0 = 0;
    // Compares the Data Benchmark Register against the threshold value
    static const uint32_t FLCTL_BMRK_CTLSTAT_CMP_SEL__en_2_0x1 = 1;

    // Benchmark Instruction Fetch Count Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_BMRK_IFETCH_t, uint32_t)
        // Reflects the number of Instruction Fetches to the Flash (increments by one on each fetch)
        ADD_BITFIELD_RW(COUNT, 0, 32)
    END_TYPE()

    // Benchmark Data Read Count Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_BMRK_DREAD_t, uint32_t)
        // Reflects the number of Data Read operations to the Flash (increments by one on each read)
        ADD_BITFIELD_RW(COUNT, 0, 32)
    END_TYPE()

    // Benchmark Count Compare Register
    // Reset value: 0x00010000
    BEGIN_TYPE(FLCTL_BMRK_CMP_t, uint32_t)
        // Reflects the threshold value that is compared against either the IFETCH or DREAD Benchmark Counters
        ADD_BITFIELD_RW(COUNT, 0, 32)
    END_TYPE()

    // Interrupt Flag Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_IFG_t, uint32_t)
        // If set to 1, indicates that the Read Burst/Compare operation is complete
        ADD_BITFIELD_RO(RDBRST, 0, 1)
        // If set to 1, indicates that the pre-program verify operation has detected an error
        ADD_BITFIELD_RO(AVPRE, 1, 1)
        // If set to 1, indicates that the post-program verify operation has failed comparison
        ADD_BITFIELD_RO(AVPST, 2, 1)
        // If set to 1, indicates that a word Program operation is complete
        ADD_BITFIELD_RO(PRG, 3, 1)
        // If set to 1, indicates that the configured Burst Program operation is complete
        ADD_BITFIELD_RO(PRGB, 4, 1)
        // If set to 1, indicates that the Erase operation is complete
        ADD_BITFIELD_RO(ERASE, 5, 1)
        // If set to 1, indicates that a Benchmark Compare match occurred
        ADD_BITFIELD_RO(BMRK, 8, 1)
        // If set to 1, indicates a word composition error in full word write mode (possible data loss due to writes crossing over to a new 128bit boundary before full word has been composed)
        ADD_BITFIELD_RO(PRG_ERR, 9, 1)
    END_TYPE()

    // Interrupt Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_IE_t, uint32_t)
        // If set to 1, enables the Controller to generate an interrupt based on the corresponding bit in the FLCTL_IFG
        ADD_BITFIELD_RW(RDBRST, 0, 1)
        // If set to 1, enables the Controller to generate an interrupt based on the corresponding bit in the FLCTL_IFG
        ADD_BITFIELD_RW(AVPRE, 1, 1)
        // If set to 1, enables the Controller to generate an interrupt based on the corresponding bit in the FLCTL_IFG
        ADD_BITFIELD_RW(AVPST, 2, 1)
        // If set to 1, enables the Controller to generate an interrupt based on the corresponding bit in the FLCTL_IFG
        ADD_BITFIELD_RW(PRG, 3, 1)
        // If set to 1, enables the Controller to generate an interrupt based on the corresponding bit in the FLCTL_IFG
        ADD_BITFIELD_RW(PRGB, 4, 1)
        // If set to 1, enables the Controller to generate an interrupt based on the corresponding bit in the FLCTL_IFG
        ADD_BITFIELD_RW(ERASE, 5, 1)
        // If set to 1, enables the Controller to generate an interrupt based on the corresponding bit in the FLCTL_IFG
        ADD_BITFIELD_RW(BMRK, 8, 1)
        // If set to 1, enables the Controller to generate an interrupt based on the corresponding bit in the FLCTL_IFG
        ADD_BITFIELD_RW(PRG_ERR, 9, 1)
    END_TYPE()

    // Clear Interrupt Flag Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_CLRIFG_t, uint32_t)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(RDBRST, 0, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(AVPRE, 1, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(AVPST, 2, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(PRG, 3, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(PRGB, 4, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(ERASE, 5, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(BMRK, 8, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(PRG_ERR, 9, 1)
    END_TYPE()

    // Set Interrupt Flag Register
    // Reset value: 0x00000000
    BEGIN_TYPE(FLCTL_SETIFG_t, uint32_t)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(RDBRST, 0, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(AVPRE, 1, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(AVPST, 2, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(PRG, 3, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(PRGB, 4, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(ERASE, 5, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(BMRK, 8, 1)
        // Write 1 clears the corresponding interrupt flag bit in the FLCTL_IFG
        ADD_BITFIELD_WO(PRG_ERR, 9, 1)
    END_TYPE()

    // Read Timing Control Register
    BEGIN_TYPE(FLCTL_READ_TIMCTL_t, uint32_t)
        // Configures the length of the Setup phase for this operation
        ADD_BITFIELD_RO(SETUP, 0, 8)
        // Length of the IREF_BOOST1 signal of the IP
        ADD_BITFIELD_RO(IREF_BOOST1, 12, 4)
        // Length of the Setup time into read mode when the device is recovering from one of the following conditions: Moving from Power-down or Standby back to Active and device is not trimmed. Moving from standby to active state in low-frequency active mode. Recovering from the LDO Boost operation after a Mass Erase.
        ADD_BITFIELD_RO(SETUP_LONG, 16, 8)
    END_TYPE()

    // Read Margin Timing Control Register
    BEGIN_TYPE(FLCTL_READMARGIN_TIMCTL_t, uint32_t)
        // Length of the Setup phase for this operation
        ADD_BITFIELD_RO(SETUP, 0, 8)
    END_TYPE()

    // Program Verify Timing Control Register
    BEGIN_TYPE(FLCTL_PRGVER_TIMCTL_t, uint32_t)
        // Length of the Setup phase for this operation
        ADD_BITFIELD_RO(SETUP, 0, 8)
        // Length of the Active phase for this operation
        ADD_BITFIELD_RO(ACTIVE, 8, 4)
        // Length of the Hold phase for this operation
        ADD_BITFIELD_RO(HOLD, 12, 4)
    END_TYPE()

    // Erase Verify Timing Control Register
    BEGIN_TYPE(FLCTL_ERSVER_TIMCTL_t, uint32_t)
        // Length of the Setup phase for this operation
        ADD_BITFIELD_RO(SETUP, 0, 8)
    END_TYPE()

    // Leakage Verify Timing Control Register
    BEGIN_TYPE(FLCTL_LKGVER_TIMCTL_t, uint32_t)
        // Length of the Setup phase for this operation
        ADD_BITFIELD_RO(SETUP, 0, 8)
    END_TYPE()

    // Program Timing Control Register
    BEGIN_TYPE(FLCTL_PROGRAM_TIMCTL_t, uint32_t)
        // Length of the Setup phase for this operation
        ADD_BITFIELD_RO(SETUP, 0, 8)
        // Length of the Active phase for this operation
        ADD_BITFIELD_RO(ACTIVE, 8, 20)
        // Length of the Hold phase for this operation
        ADD_BITFIELD_RO(HOLD, 28, 4)
    END_TYPE()

    // Erase Timing Control Register
    BEGIN_TYPE(FLCTL_ERASE_TIMCTL_t, uint32_t)
        // Length of the Setup phase for this operation
        ADD_BITFIELD_RO(SETUP, 0, 8)
        // Length of the Active phase for this operation
        ADD_BITFIELD_RO(ACTIVE, 8, 20)
        // Length of the Hold phase for this operation
        ADD_BITFIELD_RO(HOLD, 28, 4)
    END_TYPE()

    // Mass Erase Timing Control Register
    BEGIN_TYPE(FLCTL_MASSERASE_TIMCTL_t, uint32_t)
        // Length of the time for which LDO Boost Signal is kept active
        ADD_BITFIELD_RO(BOOST_ACTIVE, 0, 8)
        // Length for which Flash deactivates the LDO Boost signal before processing any new commands
        ADD_BITFIELD_RO(BOOST_HOLD, 8, 8)
    END_TYPE()

    // Burst Program Timing Control Register
    BEGIN_TYPE(FLCTL_BURSTPRG_TIMCTL_t, uint32_t)
        // Length of the Active phase for this operation
        ADD_BITFIELD_RO(ACTIVE, 8, 20)
    END_TYPE()

    struct FLCTL_t {
        FLCTL_POWER_STAT_t            FLCTL_POWER_STAT;
        uint32_t                      reserved0[3];
        FLCTL_BANK0_RDCTL_t           FLCTL_BANK0_RDCTL;
        FLCTL_BANK1_RDCTL_t           FLCTL_BANK1_RDCTL;
        uint32_t                      reserved1[2];
        FLCTL_RDBRST_CTLSTAT_t        FLCTL_RDBRST_CTLSTAT;
        FLCTL_RDBRST_STARTADDR_t      FLCTL_RDBRST_STARTADDR;
        FLCTL_RDBRST_LEN_t            FLCTL_RDBRST_LEN;
        uint32_t                      reserved2[4];
        FLCTL_RDBRST_FAILADDR_t       FLCTL_RDBRST_FAILADDR;
        FLCTL_RDBRST_FAILCNT_t        FLCTL_RDBRST_FAILCNT;
        uint32_t                      reserved3[3];
        FLCTL_PRG_CTLSTAT_t           FLCTL_PRG_CTLSTAT;
        FLCTL_PRGBRST_CTLSTAT_t       FLCTL_PRGBRST_CTLSTAT;
        FLCTL_PRGBRST_STARTADDR_t     FLCTL_PRGBRST_STARTADDR;
        uint32_t                      reserved4;
        FLCTL_PRGBRST_DATA0_0_t       FLCTL_PRGBRST_DATA0_0;
        FLCTL_PRGBRST_DATA0_1_t       FLCTL_PRGBRST_DATA0_1;
        FLCTL_PRGBRST_DATA0_2_t       FLCTL_PRGBRST_DATA0_2;
        FLCTL_PRGBRST_DATA0_3_t       FLCTL_PRGBRST_DATA0_3;
        FLCTL_PRGBRST_DATA1_0_t       FLCTL_PRGBRST_DATA1_0;
        FLCTL_PRGBRST_DATA1_1_t       FLCTL_PRGBRST_DATA1_1;
        FLCTL_PRGBRST_DATA1_2_t       FLCTL_PRGBRST_DATA1_2;
        FLCTL_PRGBRST_DATA1_3_t       FLCTL_PRGBRST_DATA1_3;
        FLCTL_PRGBRST_DATA2_0_t       FLCTL_PRGBRST_DATA2_0;
        FLCTL_PRGBRST_DATA2_1_t       FLCTL_PRGBRST_DATA2_1;
        FLCTL_PRGBRST_DATA2_2_t       FLCTL_PRGBRST_DATA2_2;
        FLCTL_PRGBRST_DATA2_3_t       FLCTL_PRGBRST_DATA2_3;
        FLCTL_PRGBRST_DATA3_0_t       FLCTL_PRGBRST_DATA3_0;
        FLCTL_PRGBRST_DATA3_1_t       FLCTL_PRGBRST_DATA3_1;
        FLCTL_PRGBRST_DATA3_2_t       FLCTL_PRGBRST_DATA3_2;
        FLCTL_PRGBRST_DATA3_3_t       FLCTL_PRGBRST_DATA3_3;
        FLCTL_ERASE_CTLSTAT_t         FLCTL_ERASE_CTLSTAT;
        FLCTL_ERASE_SECTADDR_t        FLCTL_ERASE_SECTADDR;
        uint32_t                      reserved5[2];
        FLCTL_BANK0_INFO_WEPROT_t     FLCTL_BANK0_INFO_WEPROT;
        FLCTL_BANK0_MAIN_WEPROT_t     FLCTL_BANK0_MAIN_WEPROT;
        uint32_t                      reserved6[2];
        FLCTL_BANK1_INFO_WEPROT_t     FLCTL_BANK1_INFO_WEPROT;
        FLCTL_BANK1_MAIN_WEPROT_t     FLCTL_BANK1_MAIN_WEPROT;
        uint32_t                      reserved7[2];
        FLCTL_BMRK_CTLSTAT_t          FLCTL_BMRK_CTLSTAT;
        FLCTL_BMRK_IFETCH_t           FLCTL_BMRK_IFETCH;
        FLCTL_BMRK_DREAD_t            FLCTL_BMRK_DREAD;
        FLCTL_BMRK_CMP_t              FLCTL_BMRK_CMP;
        uint32_t                      reserved8[4];
        FLCTL_IFG_t                   FLCTL_IFG;
        FLCTL_IE_t                    FLCTL_IE;
        FLCTL_CLRIFG_t                FLCTL_CLRIFG;
        FLCTL_SETIFG_t                FLCTL_SETIFG;
        FLCTL_READ_TIMCTL_t           FLCTL_READ_TIMCTL;
        FLCTL_READMARGIN_TIMCTL_t     FLCTL_READMARGIN_TIMCTL;
        FLCTL_PRGVER_TIMCTL_t         FLCTL_PRGVER_TIMCTL;
        FLCTL_ERSVER_TIMCTL_t         FLCTL_ERSVER_TIMCTL;
        FLCTL_LKGVER_TIMCTL_t         FLCTL_LKGVER_TIMCTL;
        FLCTL_PROGRAM_TIMCTL_t        FLCTL_PROGRAM_TIMCTL;
        FLCTL_ERASE_TIMCTL_t          FLCTL_ERASE_TIMCTL;
        FLCTL_MASSERASE_TIMCTL_t      FLCTL_MASSERASE_TIMCTL;
        FLCTL_BURSTPRG_TIMCTL_t       FLCTL_BURSTPRG_TIMCTL;
    };

    static FLCTL_t & FLCTL     = (*(FLCTL_t *)0x40011000);

} // _FLCTL_

// ADC14
namespace _ADC14_  {

    // Control 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ADC14CTL0_t, uint32_t)
        // ADC14 start conversion
        ADD_BITFIELD_RW(ADC14SC, 0, 1)
        // ADC14 enable conversion
        ADD_BITFIELD_RW(ADC14ENC, 1, 1)
        // ADC14 on
        ADD_BITFIELD_RW(ADC14ON, 4, 1)
        // ADC14 multiple sample and conversion
        ADD_BITFIELD_RW(ADC14MSC, 7, 1)
        // ADC14 sample-and-hold time
        ADD_BITFIELD_RW(ADC14SHT0, 8, 4)
        // ADC14 sample-and-hold time
        ADD_BITFIELD_RW(ADC14SHT1, 12, 4)
        // ADC14 busy
        ADD_BITFIELD_RO(ADC14BUSY, 16, 1)
        // ADC14 conversion sequence mode select
        ADD_BITFIELD_RW(ADC14CONSEQ, 17, 2)
        // ADC14 clock source select
        ADD_BITFIELD_RW(ADC14SSEL, 19, 3)
        // ADC14 clock divider
        ADD_BITFIELD_RW(ADC14DIV, 22, 3)
        // ADC14 invert signal sample-and-hold
        ADD_BITFIELD_RW(ADC14ISSH, 25, 1)
        // ADC14 sample-and-hold pulse-mode select
        ADD_BITFIELD_RW(ADC14SHP, 26, 1)
        // ADC14 sample-and-hold source select
        ADD_BITFIELD_RW(ADC14SHS, 27, 3)
        // ADC14 predivider
        ADD_BITFIELD_RW(ADC14PDIV, 30, 2)
    END_TYPE()

    // No sample-and-conversion-start
    static const uint32_t ADC14CTL0_ADC14SC__ADC14SC_0 = 0;
    // Start sample-and-conversion
    static const uint32_t ADC14CTL0_ADC14SC__ADC14SC_1 = 1;
    // ADC14 disabled
    static const uint32_t ADC14CTL0_ADC14ENC__ADC14ENC_0 = 0;
    // ADC14 enabled
    static const uint32_t ADC14CTL0_ADC14ENC__ADC14ENC_1 = 1;
    // ADC14 off
    static const uint32_t ADC14CTL0_ADC14ON__ADC14ON_0 = 0;
    // ADC14 on. ADC core is ready to power up when a valid conversion is triggered.
    static const uint32_t ADC14CTL0_ADC14ON__ADC14ON_1 = 1;
    // The sampling timer requires a rising edge of the SHI signal to trigger each sample-and-convert
    static const uint32_t ADC14CTL0_ADC14MSC__ADC14MSC_0 = 0;
    // The first rising edge of the SHI signal triggers the sampling timer, but further sample-and-conversions are performed automatically as soon as the prior conversion is completed
    static const uint32_t ADC14CTL0_ADC14MSC__ADC14MSC_1 = 1;
    // 4
    static const uint32_t ADC14CTL0_ADC14SHT0__ADC14SHT0_0 = 0;
    // 8
    static const uint32_t ADC14CTL0_ADC14SHT0__ADC14SHT0_1 = 1;
    // 16
    static const uint32_t ADC14CTL0_ADC14SHT0__ADC14SHT0_2 = 2;
    // 32
    static const uint32_t ADC14CTL0_ADC14SHT0__ADC14SHT0_3 = 3;
    // 64
    static const uint32_t ADC14CTL0_ADC14SHT0__ADC14SHT0_4 = 4;
    // 96
    static const uint32_t ADC14CTL0_ADC14SHT0__ADC14SHT0_5 = 5;
    // 128
    static const uint32_t ADC14CTL0_ADC14SHT0__ADC14SHT0_6 = 6;
    // 192
    static const uint32_t ADC14CTL0_ADC14SHT0__ADC14SHT0_7 = 7;
    // 4
    static const uint32_t ADC14CTL0_ADC14SHT1__ADC14SHT1_0 = 0;
    // 8
    static const uint32_t ADC14CTL0_ADC14SHT1__ADC14SHT1_1 = 1;
    // 16
    static const uint32_t ADC14CTL0_ADC14SHT1__ADC14SHT1_2 = 2;
    // 32
    static const uint32_t ADC14CTL0_ADC14SHT1__ADC14SHT1_3 = 3;
    // 64
    static const uint32_t ADC14CTL0_ADC14SHT1__ADC14SHT1_4 = 4;
    // 96
    static const uint32_t ADC14CTL0_ADC14SHT1__ADC14SHT1_5 = 5;
    // 128
    static const uint32_t ADC14CTL0_ADC14SHT1__ADC14SHT1_6 = 6;
    // 192
    static const uint32_t ADC14CTL0_ADC14SHT1__ADC14SHT1_7 = 7;
    // No operation is active
    static const uint32_t ADC14CTL0_ADC14BUSY__ADC14BUSY_0 = 0;
    // A sequence, sample, or conversion is active
    static const uint32_t ADC14CTL0_ADC14BUSY__ADC14BUSY_1 = 1;
    // Single-channel, single-conversion
    static const uint32_t ADC14CTL0_ADC14CONSEQ__ADC14CONSEQ_0 = 0;
    // Sequence-of-channels
    static const uint32_t ADC14CTL0_ADC14CONSEQ__ADC14CONSEQ_1 = 1;
    // Repeat-single-channel
    static const uint32_t ADC14CTL0_ADC14CONSEQ__ADC14CONSEQ_2 = 2;
    // Repeat-sequence-of-channels
    static const uint32_t ADC14CTL0_ADC14CONSEQ__ADC14CONSEQ_3 = 3;
    // MODCLK
    static const uint32_t ADC14CTL0_ADC14SSEL__ADC14SSEL_0 = 0;
    // SYSCLK
    static const uint32_t ADC14CTL0_ADC14SSEL__ADC14SSEL_1 = 1;
    // ACLK
    static const uint32_t ADC14CTL0_ADC14SSEL__ADC14SSEL_2 = 2;
    // MCLK
    static const uint32_t ADC14CTL0_ADC14SSEL__ADC14SSEL_3 = 3;
    // SMCLK
    static const uint32_t ADC14CTL0_ADC14SSEL__ADC14SSEL_4 = 4;
    // HSMCLK
    static const uint32_t ADC14CTL0_ADC14SSEL__ADC14SSEL_5 = 5;
    // /1
    static const uint32_t ADC14CTL0_ADC14DIV__ADC14DIV_0 = 0;
    // /2
    static const uint32_t ADC14CTL0_ADC14DIV__ADC14DIV_1 = 1;
    // /3
    static const uint32_t ADC14CTL0_ADC14DIV__ADC14DIV_2 = 2;
    // /4
    static const uint32_t ADC14CTL0_ADC14DIV__ADC14DIV_3 = 3;
    // /5
    static const uint32_t ADC14CTL0_ADC14DIV__ADC14DIV_4 = 4;
    // /6
    static const uint32_t ADC14CTL0_ADC14DIV__ADC14DIV_5 = 5;
    // /7
    static const uint32_t ADC14CTL0_ADC14DIV__ADC14DIV_6 = 6;
    // /8
    static const uint32_t ADC14CTL0_ADC14DIV__ADC14DIV_7 = 7;
    // The sample-input signal is not inverted
    static const uint32_t ADC14CTL0_ADC14ISSH__ADC14ISSH_0 = 0;
    // The sample-input signal is inverted
    static const uint32_t ADC14CTL0_ADC14ISSH__ADC14ISSH_1 = 1;
    // SAMPCON signal is sourced from the sample-input signal
    static const uint32_t ADC14CTL0_ADC14SHP__ADC14SHP_0 = 0;
    // SAMPCON signal is sourced from the sampling timer
    static const uint32_t ADC14CTL0_ADC14SHP__ADC14SHP_1 = 1;
    // ADC14SC bit
    static const uint32_t ADC14CTL0_ADC14SHS__ADC14SHS_0 = 0;
    // See device-specific data sheet for source
    static const uint32_t ADC14CTL0_ADC14SHS__ADC14SHS_1 = 1;
    // See device-specific data sheet for source
    static const uint32_t ADC14CTL0_ADC14SHS__ADC14SHS_2 = 2;
    // See device-specific data sheet for source
    static const uint32_t ADC14CTL0_ADC14SHS__ADC14SHS_3 = 3;
    // See device-specific data sheet for source
    static const uint32_t ADC14CTL0_ADC14SHS__ADC14SHS_4 = 4;
    // See device-specific data sheet for source
    static const uint32_t ADC14CTL0_ADC14SHS__ADC14SHS_5 = 5;
    // See device-specific data sheet for source
    static const uint32_t ADC14CTL0_ADC14SHS__ADC14SHS_6 = 6;
    // See device-specific data sheet for source
    static const uint32_t ADC14CTL0_ADC14SHS__ADC14SHS_7 = 7;
    // Predivide by 1
    static const uint32_t ADC14CTL0_ADC14PDIV__ADC14PDIV_0 = 0;
    // Predivide by 4
    static const uint32_t ADC14CTL0_ADC14PDIV__ADC14PDIV_1 = 1;
    // Predivide by 32
    static const uint32_t ADC14CTL0_ADC14PDIV__ADC14PDIV_2 = 2;
    // Predivide by 64
    static const uint32_t ADC14CTL0_ADC14PDIV__ADC14PDIV_3 = 3;

    // Control 1 Register
    // Reset value: 0x00000030
    BEGIN_TYPE(ADC14CTL1_t, uint32_t)
        // ADC14 power modes
        ADD_BITFIELD_RW(ADC14PWRMD, 0, 2)
        // ADC14 reference buffer burst
        ADD_BITFIELD_RW(ADC14REFBURST, 2, 1)
        // ADC14 data read-back format
        ADD_BITFIELD_RW(ADC14DF, 3, 1)
        // ADC14 resolution
        ADD_BITFIELD_RW(ADC14RES, 4, 2)
        // ADC14 conversion start address
        ADD_BITFIELD_RW(ADC14CSTARTADD, 16, 5)
        // Controls 1/2 AVCC ADC input channel selection
        ADD_BITFIELD_RW(ADC14BATMAP, 22, 1)
        // Controls temperature sensor ADC input channel selection
        ADD_BITFIELD_RW(ADC14TCMAP, 23, 1)
        // Controls internal channel 0 selection to ADC input channel MAX-2
        ADD_BITFIELD_RW(ADC14CH0MAP, 24, 1)
        // Controls internal channel 1 selection to ADC input channel MAX-3
        ADD_BITFIELD_RW(ADC14CH1MAP, 25, 1)
        // Controls internal channel 2 selection to ADC input channel MAX-4
        ADD_BITFIELD_RW(ADC14CH2MAP, 26, 1)
        // Controls internal channel 3 selection to ADC input channel MAX-5
        ADD_BITFIELD_RW(ADC14CH3MAP, 27, 1)
    END_TYPE()

    // Regular power mode for use with any resolution setting. Sample rate can be up to 1 Msps.
    static const uint32_t ADC14CTL1_ADC14PWRMD__ADC14PWRMD_0 = 0;
    // Low-power mode for 12-bit, 10-bit, and 8-bit resolution settings. Sample rate must not exceed 200 ksps.
    static const uint32_t ADC14CTL1_ADC14PWRMD__ADC14PWRMD_2 = 2;
    // ADC reference buffer on continuously
    static const uint32_t ADC14CTL1_ADC14REFBURST__ADC14REFBURST_0 = 0;
    // ADC reference buffer on only during sample-and-conversion
    static const uint32_t ADC14CTL1_ADC14REFBURST__ADC14REFBURST_1 = 1;
    // Binary unsigned. Theoretically, for ADC14DIF = 0 and 14-bit mode, the analog input voltage - V(REF) results in 0000h, and the analog input voltage + V(REF) results in 3FFFh
    static const uint32_t ADC14CTL1_ADC14DF__ADC14DF_0 = 0;
    // Signed binary (2s complement), left aligned. Theoretically, for ADC14DIF = 0 and 14-bit mode, the analog input voltage - V(REF) results in 8000h, and the analog input voltage + V(REF) results in 7FFCh
    static const uint32_t ADC14CTL1_ADC14DF__ADC14DF_1 = 1;
    // 8 bit (9 clock cycle conversion time)
    static const uint32_t ADC14CTL1_ADC14RES__ADC14RES_0 = 0;
    // 10 bit (11 clock cycle conversion time)
    static const uint32_t ADC14CTL1_ADC14RES__ADC14RES_1 = 1;
    // 12 bit (14 clock cycle conversion time)
    static const uint32_t ADC14CTL1_ADC14RES__ADC14RES_2 = 2;
    // 14 bit (16 clock cycle conversion time)
    static const uint32_t ADC14CTL1_ADC14RES__ADC14RES_3 = 3;
    // ADC internal 1/2 x AVCC channel is not selected for ADC
    static const uint32_t ADC14CTL1_ADC14BATMAP__ADC14BATMAP_0 = 0;
    // ADC internal 1/2 x AVCC channel is selected for ADC input channel MAX
    static const uint32_t ADC14CTL1_ADC14BATMAP__ADC14BATMAP_1 = 1;
    // ADC internal temperature sensor channel is not selected for ADC
    static const uint32_t ADC14CTL1_ADC14TCMAP__ADC14TCMAP_0 = 0;
    // ADC internal temperature sensor channel is selected for ADC input channel MAX-1
    static const uint32_t ADC14CTL1_ADC14TCMAP__ADC14TCMAP_1 = 1;
    // ADC input channel internal 0 is not selected
    static const uint32_t ADC14CTL1_ADC14CH0MAP__ADC14CH0MAP_0 = 0;
    // ADC input channel internal 0 is selected for ADC input channel MAX-2
    static const uint32_t ADC14CTL1_ADC14CH0MAP__ADC14CH0MAP_1 = 1;
    // ADC input channel internal 1 is not selected
    static const uint32_t ADC14CTL1_ADC14CH1MAP__ADC14CH1MAP_0 = 0;
    // ADC input channel internal 1 is selected for ADC input channel MAX-3
    static const uint32_t ADC14CTL1_ADC14CH1MAP__ADC14CH1MAP_1 = 1;
    // ADC input channel internal 2 is not selected
    static const uint32_t ADC14CTL1_ADC14CH2MAP__ADC14CH2MAP_0 = 0;
    // ADC input channel internal 2 is selected for ADC input channel MAX-4
    static const uint32_t ADC14CTL1_ADC14CH2MAP__ADC14CH2MAP_1 = 1;
    // ADC input channel internal 3 is not selected
    static const uint32_t ADC14CTL1_ADC14CH3MAP__ADC14CH3MAP_0 = 0;
    // ADC input channel internal 3 is selected for ADC input channel MAX-5
    static const uint32_t ADC14CTL1_ADC14CH3MAP__ADC14CH3MAP_1 = 1;

    // Window Comparator Low Threshold 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ADC14LO0_t, uint32_t)
        // Low threshold 0
        ADD_BITFIELD_RW(ADC14LO0, 0, 16)
    END_TYPE()

    // Window Comparator High Threshold 0 Register
    // Reset value: 0x00003fff
    BEGIN_TYPE(ADC14HI0_t, uint32_t)
        // High threshold 0
        ADD_BITFIELD_RW(ADC14HI0, 0, 16)
    END_TYPE()

    // Window Comparator Low Threshold 1 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ADC14LO1_t, uint32_t)
        // Low threshold 1
        ADD_BITFIELD_RW(ADC14LO1, 0, 16)
    END_TYPE()

    // Window Comparator High Threshold 1 Register
    // Reset value: 0x00003fff
    BEGIN_TYPE(ADC14HI1_t, uint32_t)
        // High threshold 1
        ADD_BITFIELD_RW(ADC14HI1, 0, 16)
    END_TYPE()

    // Conversion Memory Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ADC14MCTL_t, uint32_t)
        // Input channel select
        ADD_BITFIELD_RW(ADC14INCH, 0, 5)
        // End of sequence
        ADD_BITFIELD_RW(ADC14EOS, 7, 1)
        // Selects combinations of V(R+) and V(R-) sources
        ADD_BITFIELD_RW(ADC14VRSEL, 8, 4)
        // Differential mode
        ADD_BITFIELD_RW(ADC14DIF, 13, 1)
        // Comparator window enable
        ADD_BITFIELD_RW(ADC14WINC, 14, 1)
        // Window comparator threshold register selection
        ADD_BITFIELD_RW(ADC14WINCTH, 15, 1)
    END_TYPE()

    // If ADC14DIF = 0: A0; If ADC14DIF = 1: Ain+ = A0, Ain- = A1
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_0 = 0;
    // If ADC14DIF = 0: A1; If ADC14DIF = 1: Ain+ = A0, Ain- = A1
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_1 = 1;
    // If ADC14DIF = 0: A2; If ADC14DIF = 1: Ain+ = A2, Ain- = A3
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_2 = 2;
    // If ADC14DIF = 0: A3; If ADC14DIF = 1: Ain+ = A2, Ain- = A3
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_3 = 3;
    // If ADC14DIF = 0: A4; If ADC14DIF = 1: Ain+ = A4, Ain- = A5
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_4 = 4;
    // If ADC14DIF = 0: A5; If ADC14DIF = 1: Ain+ = A4, Ain- = A5
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_5 = 5;
    // If ADC14DIF = 0: A6; If ADC14DIF = 1: Ain+ = A6, Ain- = A7
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_6 = 6;
    // If ADC14DIF = 0: A7; If ADC14DIF = 1: Ain+ = A6, Ain- = A7
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_7 = 7;
    // If ADC14DIF = 0: A8; If ADC14DIF = 1: Ain+ = A8, Ain- = A9
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_8 = 8;
    // If ADC14DIF = 0: A9; If ADC14DIF = 1: Ain+ = A8, Ain- = A9
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_9 = 9;
    // If ADC14DIF = 0: A10; If ADC14DIF = 1: Ain+ = A10, Ain- = A11
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_10 = 10;
    // If ADC14DIF = 0: A11; If ADC14DIF = 1: Ain+ = A10, Ain- = A11
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_11 = 11;
    // If ADC14DIF = 0: A12; If ADC14DIF = 1: Ain+ = A12, Ain- = A13
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_12 = 12;
    // If ADC14DIF = 0: A13; If ADC14DIF = 1: Ain+ = A12, Ain- = A13
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_13 = 13;
    // If ADC14DIF = 0: A14; If ADC14DIF = 1: Ain+ = A14, Ain- = A15
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_14 = 14;
    // If ADC14DIF = 0: A15; If ADC14DIF = 1: Ain+ = A14, Ain- = A15
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_15 = 15;
    // If ADC14DIF = 0: A16; If ADC14DIF = 1: Ain+ = A16, Ain- = A17
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_16 = 16;
    // If ADC14DIF = 0: A17; If ADC14DIF = 1: Ain+ = A16, Ain- = A17
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_17 = 17;
    // If ADC14DIF = 0: A18; If ADC14DIF = 1: Ain+ = A18, Ain- = A19
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_18 = 18;
    // If ADC14DIF = 0: A19; If ADC14DIF = 1: Ain+ = A18, Ain- = A19
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_19 = 19;
    // If ADC14DIF = 0: A20; If ADC14DIF = 1: Ain+ = A20, Ain- = A21
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_20 = 20;
    // If ADC14DIF = 0: A21; If ADC14DIF = 1: Ain+ = A20, Ain- = A21
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_21 = 21;
    // If ADC14DIF = 0: A22; If ADC14DIF = 1: Ain+ = A22, Ain- = A23
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_22 = 22;
    // If ADC14DIF = 0: A23; If ADC14DIF = 1: Ain+ = A22, Ain- = A23
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_23 = 23;
    // If ADC14DIF = 0: A24; If ADC14DIF = 1: Ain+ = A24, Ain- = A25
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_24 = 24;
    // If ADC14DIF = 0: A25; If ADC14DIF = 1: Ain+ = A24, Ain- = A25
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_25 = 25;
    // If ADC14DIF = 0: A26; If ADC14DIF = 1: Ain+ = A26, Ain- = A27
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_26 = 26;
    // If ADC14DIF = 0: A27; If ADC14DIF = 1: Ain+ = A26, Ain- = A27
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_27 = 27;
    // If ADC14DIF = 0: A28; If ADC14DIF = 1: Ain+ = A28, Ain- = A29
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_28 = 28;
    // If ADC14DIF = 0: A29; If ADC14DIF = 1: Ain+ = A28, Ain- = A29
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_29 = 29;
    // If ADC14DIF = 0: A30; If ADC14DIF = 1: Ain+ = A30, Ain- = A31
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_30 = 30;
    // If ADC14DIF = 0: A31; If ADC14DIF = 1: Ain+ = A30, Ain- = A31
    static const uint32_t ADC14MCTL_ADC14INCH__ADC14INCH_31 = 31;
    // Not end of sequence
    static const uint32_t ADC14MCTL_ADC14EOS__ADC14EOS_0 = 0;
    // End of sequence
    static const uint32_t ADC14MCTL_ADC14EOS__ADC14EOS_1 = 1;
    // V(R+) = AVCC, V(R-) = AVSS
    static const uint32_t ADC14MCTL_ADC14VRSEL__ADC14VRSEL_0 = 0;
    // V(R+) = VREF buffered, V(R-) = AVSS
    static const uint32_t ADC14MCTL_ADC14VRSEL__ADC14VRSEL_1 = 1;
    // V(R+) = VeREF+, V(R-) = VeREF-
    static const uint32_t ADC14MCTL_ADC14VRSEL__ADC14VRSEL_14 = 14;
    // V(R+) = VeREF+ buffered, V(R-) = VeREF
    static const uint32_t ADC14MCTL_ADC14VRSEL__ADC14VRSEL_15 = 15;
    // Single-ended mode enabled
    static const uint32_t ADC14MCTL_ADC14DIF__ADC14DIF_0 = 0;
    // Differential mode enabled
    static const uint32_t ADC14MCTL_ADC14DIF__ADC14DIF_1 = 1;
    // Comparator window disabled
    static const uint32_t ADC14MCTL_ADC14WINC__ADC14WINC_0 = 0;
    // Comparator window enabled
    static const uint32_t ADC14MCTL_ADC14WINC__ADC14WINC_1 = 1;
    // Use window comparator thresholds 0, ADC14LO0 and ADC14HI0
    static const uint32_t ADC14MCTL_ADC14WINCTH__ADC14WINCTH_0 = 0;
    // Use window comparator thresholds 1, ADC14LO1 and ADC14HI1
    static const uint32_t ADC14MCTL_ADC14WINCTH__ADC14WINCTH_1 = 1;

    // Conversion Memory Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ADC14MEM_t, uint32_t)
        // Conversion Result
        ADD_BITFIELD_RW(Conversion_Results, 0, 16)
    END_TYPE()

    // Interrupt Enable 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ADC14IER0_t, uint32_t)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE0, 0, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE1, 1, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE2, 2, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE3, 3, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE4, 4, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE5, 5, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE6, 6, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE7, 7, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE8, 8, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE9, 9, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE10, 10, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE11, 11, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE12, 12, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE13, 13, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE14, 14, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE15, 15, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE16, 16, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE17, 17, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE19, 19, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE18, 18, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE20, 20, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE21, 21, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE22, 22, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE23, 23, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE24, 24, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE25, 25, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE26, 26, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE27, 27, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE28, 28, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE29, 29, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE30, 30, 1)
        // Interrupt enable
        ADD_BITFIELD_RW(ADC14IE31, 31, 1)
    END_TYPE()

    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE0__ADC14IE0_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE0__ADC14IE0_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE1__ADC14IE1_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE1__ADC14IE1_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE2__ADC14IE2_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE2__ADC14IE2_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE3__ADC14IE3_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE3__ADC14IE3_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE4__ADC14IE4_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE4__ADC14IE4_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE5__ADC14IE5_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE5__ADC14IE5_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE6__ADC14IE6_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE6__ADC14IE6_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE7__ADC14IE7_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE7__ADC14IE7_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE8__ADC14IE8_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE8__ADC14IE8_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE9__ADC14IE9_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE9__ADC14IE9_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE10__ADC14IE10_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE10__ADC14IE10_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE11__ADC14IE11_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE11__ADC14IE11_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE12__ADC14IE12_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE12__ADC14IE12_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE13__ADC14IE13_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE13__ADC14IE13_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE14__ADC14IE14_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE14__ADC14IE14_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE15__ADC14IE15_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE15__ADC14IE15_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE16__ADC14IE16_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE16__ADC14IE16_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE17__ADC14IE17_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE17__ADC14IE17_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE19__ADC14IE19_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE19__ADC14IE19_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE18__ADC14IE18_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE18__ADC14IE18_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE20__ADC14IE20_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE20__ADC14IE20_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE21__ADC14IE21_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE21__ADC14IE21_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE22__ADC14IE22_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE22__ADC14IE22_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE23__ADC14IE23_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE23__ADC14IE23_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE24__ADC14IE24_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE24__ADC14IE24_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE25__ADC14IE25_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE25__ADC14IE25_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE26__ADC14IE26_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE26__ADC14IE26_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE27__ADC14IE27_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE27__ADC14IE27_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE28__ADC14IE28_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE28__ADC14IE28_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE29__ADC14IE29_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE29__ADC14IE29_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE30__ADC14IE30_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE30__ADC14IE30_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER0_ADC14IE31__ADC14IE31_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER0_ADC14IE31__ADC14IE31_1 = 1;

    // Interrupt Enable 1 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ADC14IER1_t, uint32_t)
        // Interrupt enable for ADC14MEMx within comparator window
        ADD_BITFIELD_RW(ADC14INIE, 1, 1)
        // Interrupt enable for ADC14MEMx below comparator window
        ADD_BITFIELD_RW(ADC14LOIE, 2, 1)
        // Interrupt enable for ADC14MEMx above comparator window
        ADD_BITFIELD_RW(ADC14HIIE, 3, 1)
        // ADC14MEMx overflow-interrupt enable
        ADD_BITFIELD_RW(ADC14OVIE, 4, 1)
        // ADC14 conversion-time-overflow interrupt enable
        ADD_BITFIELD_RW(ADC14TOVIE, 5, 1)
        // ADC14 local buffered reference ready interrupt enable
        ADD_BITFIELD_RW(ADC14RDYIE, 6, 1)
    END_TYPE()

    // Interrupt disabled
    static const uint32_t ADC14IER1_ADC14INIE__ADC14INIE_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER1_ADC14INIE__ADC14INIE_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER1_ADC14LOIE__ADC14LOIE_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER1_ADC14LOIE__ADC14LOIE_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER1_ADC14HIIE__ADC14HIIE_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER1_ADC14HIIE__ADC14HIIE_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER1_ADC14OVIE__ADC14OVIE_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER1_ADC14OVIE__ADC14OVIE_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER1_ADC14TOVIE__ADC14TOVIE_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER1_ADC14TOVIE__ADC14TOVIE_1 = 1;
    // Interrupt disabled
    static const uint32_t ADC14IER1_ADC14RDYIE__ADC14RDYIE_0 = 0;
    // Interrupt enabled
    static const uint32_t ADC14IER1_ADC14RDYIE__ADC14RDYIE_1 = 1;

    // Interrupt Flag 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ADC14IFGR0_t, uint32_t)
        // ADC14MEM0 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG0, 0, 1)
        // ADC14MEM1 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG1, 1, 1)
        // ADC14MEM2 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG2, 2, 1)
        // ADC14MEM3 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG3, 3, 1)
        // ADC14MEM4 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG4, 4, 1)
        // ADC14MEM5 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG5, 5, 1)
        // ADC14MEM6 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG6, 6, 1)
        // ADC14MEM7 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG7, 7, 1)
        // ADC14MEM8 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG8, 8, 1)
        // ADC14MEM9 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG9, 9, 1)
        // ADC14MEM10 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG10, 10, 1)
        // ADC14MEM11 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG11, 11, 1)
        // ADC14MEM12 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG12, 12, 1)
        // ADC14MEM13 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG13, 13, 1)
        // ADC14MEM14 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG14, 14, 1)
        // ADC14MEM15 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG15, 15, 1)
        // ADC14MEM16 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG16, 16, 1)
        // ADC14MEM17 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG17, 17, 1)
        // ADC14MEM18 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG18, 18, 1)
        // ADC14MEM19 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG19, 19, 1)
        // ADC14MEM20 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG20, 20, 1)
        // ADC14MEM21 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG21, 21, 1)
        // ADC14MEM22 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG22, 22, 1)
        // ADC14MEM23 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG23, 23, 1)
        // ADC14MEM24 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG24, 24, 1)
        // ADC14MEM25 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG25, 25, 1)
        // ADC14MEM26 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG26, 26, 1)
        // ADC14MEM27 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG27, 27, 1)
        // ADC14MEM28 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG28, 28, 1)
        // ADC14MEM29 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG29, 29, 1)
        // ADC14MEM30 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG30, 30, 1)
        // ADC14MEM31 interrupt flag
        ADD_BITFIELD_RO(ADC14IFG31, 31, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG0__ADC14IFG0_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG0__ADC14IFG0_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG1__ADC14IFG1_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG1__ADC14IFG1_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG2__ADC14IFG2_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG2__ADC14IFG2_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG3__ADC14IFG3_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG3__ADC14IFG3_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG4__ADC14IFG4_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG4__ADC14IFG4_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG5__ADC14IFG5_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG5__ADC14IFG5_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG6__ADC14IFG6_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG6__ADC14IFG6_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG7__ADC14IFG7_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG7__ADC14IFG7_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG8__ADC14IFG8_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG8__ADC14IFG8_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG9__ADC14IFG9_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG9__ADC14IFG9_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG10__ADC14IFG10_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG10__ADC14IFG10_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG11__ADC14IFG11_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG11__ADC14IFG11_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG12__ADC14IFG12_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG12__ADC14IFG12_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG13__ADC14IFG13_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG13__ADC14IFG13_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG14__ADC14IFG14_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG14__ADC14IFG14_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG15__ADC14IFG15_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG15__ADC14IFG15_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG16__ADC14IFG16_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG16__ADC14IFG16_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG17__ADC14IFG17_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG17__ADC14IFG17_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG18__ADC14IFG18_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG18__ADC14IFG18_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG19__ADC14IFG19_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG19__ADC14IFG19_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG20__ADC14IFG20_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG20__ADC14IFG20_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG21__ADC14IFG21_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG21__ADC14IFG21_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG22__ADC14IFG22_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG22__ADC14IFG22_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG23__ADC14IFG23_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG23__ADC14IFG23_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG24__ADC14IFG24_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG24__ADC14IFG24_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG25__ADC14IFG25_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG25__ADC14IFG25_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG26__ADC14IFG26_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG26__ADC14IFG26_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG27__ADC14IFG27_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG27__ADC14IFG27_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG28__ADC14IFG28_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG28__ADC14IFG28_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG29__ADC14IFG29_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG29__ADC14IFG29_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG30__ADC14IFG30_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG30__ADC14IFG30_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG31__ADC14IFG31_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR0_ADC14IFG31__ADC14IFG31_1 = 1;

    // Interrupt Flag 1 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ADC14IFGR1_t, uint32_t)
        // Interrupt flag for ADC14MEMx within comparator window
        ADD_BITFIELD_RO(ADC14INIFG, 1, 1)
        // Interrupt flag for ADC14MEMx below comparator window
        ADD_BITFIELD_RO(ADC14LOIFG, 2, 1)
        // Interrupt flag for ADC14MEMx above comparator window
        ADD_BITFIELD_RO(ADC14HIIFG, 3, 1)
        // ADC14MEMx overflow interrupt flag
        ADD_BITFIELD_RO(ADC14OVIFG, 4, 1)
        // ADC14 conversion time overflow interrupt flag
        ADD_BITFIELD_RO(ADC14TOVIFG, 5, 1)
        // ADC14 local buffered reference ready interrupt flag
        ADD_BITFIELD_RO(ADC14RDYIFG, 6, 1)
    END_TYPE()

    // No interrupt pending
    static const uint32_t ADC14IFGR1_ADC14INIFG__ADC14INIFG_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR1_ADC14INIFG__ADC14INIFG_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR1_ADC14LOIFG__ADC14LOIFG_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR1_ADC14LOIFG__ADC14LOIFG_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR1_ADC14HIIFG__ADC14HIIFG_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR1_ADC14HIIFG__ADC14HIIFG_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR1_ADC14OVIFG__ADC14OVIFG_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR1_ADC14OVIFG__ADC14OVIFG_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR1_ADC14TOVIFG__ADC14TOVIFG_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR1_ADC14TOVIFG__ADC14TOVIFG_1 = 1;
    // No interrupt pending
    static const uint32_t ADC14IFGR1_ADC14RDYIFG__ADC14RDYIFG_0 = 0;
    // Interrupt pending
    static const uint32_t ADC14IFGR1_ADC14RDYIFG__ADC14RDYIFG_1 = 1;

    // Clear Interrupt Flag 0 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ADC14CLRIFGR0_t, uint32_t)
        // clear ADC14IFG0
        ADD_BITFIELD_WO(CLRADC14IFG0, 0, 1)
        // clear ADC14IFG1
        ADD_BITFIELD_WO(CLRADC14IFG1, 1, 1)
        // clear ADC14IFG2
        ADD_BITFIELD_WO(CLRADC14IFG2, 2, 1)
        // clear ADC14IFG3
        ADD_BITFIELD_WO(CLRADC14IFG3, 3, 1)
        // clear ADC14IFG4
        ADD_BITFIELD_WO(CLRADC14IFG4, 4, 1)
        // clear ADC14IFG5
        ADD_BITFIELD_WO(CLRADC14IFG5, 5, 1)
        // clear ADC14IFG6
        ADD_BITFIELD_WO(CLRADC14IFG6, 6, 1)
        // clear ADC14IFG7
        ADD_BITFIELD_WO(CLRADC14IFG7, 7, 1)
        // clear ADC14IFG8
        ADD_BITFIELD_WO(CLRADC14IFG8, 8, 1)
        // clear ADC14IFG9
        ADD_BITFIELD_WO(CLRADC14IFG9, 9, 1)
        // clear ADC14IFG10
        ADD_BITFIELD_WO(CLRADC14IFG10, 10, 1)
        // clear ADC14IFG11
        ADD_BITFIELD_WO(CLRADC14IFG11, 11, 1)
        // clear ADC14IFG12
        ADD_BITFIELD_WO(CLRADC14IFG12, 12, 1)
        // clear ADC14IFG13
        ADD_BITFIELD_WO(CLRADC14IFG13, 13, 1)
        // clear ADC14IFG14
        ADD_BITFIELD_WO(CLRADC14IFG14, 14, 1)
        // clear ADC14IFG15
        ADD_BITFIELD_WO(CLRADC14IFG15, 15, 1)
        // clear ADC14IFG16
        ADD_BITFIELD_WO(CLRADC14IFG16, 16, 1)
        // clear ADC14IFG17
        ADD_BITFIELD_WO(CLRADC14IFG17, 17, 1)
        // clear ADC14IFG18
        ADD_BITFIELD_WO(CLRADC14IFG18, 18, 1)
        // clear ADC14IFG19
        ADD_BITFIELD_WO(CLRADC14IFG19, 19, 1)
        // clear ADC14IFG20
        ADD_BITFIELD_WO(CLRADC14IFG20, 20, 1)
        // clear ADC14IFG21
        ADD_BITFIELD_WO(CLRADC14IFG21, 21, 1)
        // clear ADC14IFG22
        ADD_BITFIELD_WO(CLRADC14IFG22, 22, 1)
        // clear ADC14IFG23
        ADD_BITFIELD_WO(CLRADC14IFG23, 23, 1)
        // clear ADC14IFG24
        ADD_BITFIELD_WO(CLRADC14IFG24, 24, 1)
        // clear ADC14IFG25
        ADD_BITFIELD_WO(CLRADC14IFG25, 25, 1)
        // clear ADC14IFG26
        ADD_BITFIELD_WO(CLRADC14IFG26, 26, 1)
        // clear ADC14IFG27
        ADD_BITFIELD_WO(CLRADC14IFG27, 27, 1)
        // clear ADC14IFG28
        ADD_BITFIELD_WO(CLRADC14IFG28, 28, 1)
        // clear ADC14IFG29
        ADD_BITFIELD_WO(CLRADC14IFG29, 29, 1)
        // clear ADC14IFG30
        ADD_BITFIELD_WO(CLRADC14IFG30, 30, 1)
        // clear ADC14IFG31
        ADD_BITFIELD_WO(CLRADC14IFG31, 31, 1)
    END_TYPE()

    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG0__CLRADC14IFG0_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG0__CLRADC14IFG0_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG1__CLRADC14IFG1_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG1__CLRADC14IFG1_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG2__CLRADC14IFG2_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG2__CLRADC14IFG2_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG3__CLRADC14IFG3_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG3__CLRADC14IFG3_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG4__CLRADC14IFG4_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG4__CLRADC14IFG4_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG5__CLRADC14IFG5_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG5__CLRADC14IFG5_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG6__CLRADC14IFG6_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG6__CLRADC14IFG6_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG7__CLRADC14IFG7_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG7__CLRADC14IFG7_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG8__CLRADC14IFG8_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG8__CLRADC14IFG8_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG9__CLRADC14IFG9_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG9__CLRADC14IFG9_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG10__CLRADC14IFG10_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG10__CLRADC14IFG10_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG11__CLRADC14IFG11_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG11__CLRADC14IFG11_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG12__CLRADC14IFG12_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG12__CLRADC14IFG12_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG13__CLRADC14IFG13_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG13__CLRADC14IFG13_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG14__CLRADC14IFG14_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG14__CLRADC14IFG14_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG15__CLRADC14IFG15_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG15__CLRADC14IFG15_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG16__CLRADC14IFG16_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG16__CLRADC14IFG16_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG17__CLRADC14IFG17_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG17__CLRADC14IFG17_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG18__CLRADC14IFG18_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG18__CLRADC14IFG18_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG19__CLRADC14IFG19_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG19__CLRADC14IFG19_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG20__CLRADC14IFG20_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG20__CLRADC14IFG20_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG21__CLRADC14IFG21_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG21__CLRADC14IFG21_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG22__CLRADC14IFG22_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG22__CLRADC14IFG22_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG23__CLRADC14IFG23_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG23__CLRADC14IFG23_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG24__CLRADC14IFG24_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG24__CLRADC14IFG24_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG25__CLRADC14IFG25_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG25__CLRADC14IFG25_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG26__CLRADC14IFG26_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG26__CLRADC14IFG26_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG27__CLRADC14IFG27_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG27__CLRADC14IFG27_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG28__CLRADC14IFG28_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG28__CLRADC14IFG28_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG29__CLRADC14IFG29_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG29__CLRADC14IFG29_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG30__CLRADC14IFG30_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG30__CLRADC14IFG30_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG31__CLRADC14IFG31_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR0_CLRADC14IFG31__CLRADC14IFG31_1 = 1;

    // Clear Interrupt Flag 1 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ADC14CLRIFGR1_t, uint32_t)
        // clear ADC14INIFG
        ADD_BITFIELD_WO(CLRADC14INIFG, 1, 1)
        // clear ADC14LOIFG
        ADD_BITFIELD_WO(CLRADC14LOIFG, 2, 1)
        // clear ADC14HIIFG
        ADD_BITFIELD_WO(CLRADC14HIIFG, 3, 1)
        // clear ADC14OVIFG
        ADD_BITFIELD_WO(CLRADC14OVIFG, 4, 1)
        // clear ADC14TOVIFG
        ADD_BITFIELD_WO(CLRADC14TOVIFG, 5, 1)
        // clear ADC14RDYIFG
        ADD_BITFIELD_WO(CLRADC14RDYIFG, 6, 1)
    END_TYPE()

    // no effect
    static const uint32_t ADC14CLRIFGR1_CLRADC14INIFG__CLRADC14INIFG_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR1_CLRADC14INIFG__CLRADC14INIFG_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR1_CLRADC14LOIFG__CLRADC14LOIFG_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR1_CLRADC14LOIFG__CLRADC14LOIFG_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR1_CLRADC14HIIFG__CLRADC14HIIFG_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR1_CLRADC14HIIFG__CLRADC14HIIFG_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR1_CLRADC14OVIFG__CLRADC14OVIFG_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR1_CLRADC14OVIFG__CLRADC14OVIFG_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR1_CLRADC14TOVIFG__CLRADC14TOVIFG_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR1_CLRADC14TOVIFG__CLRADC14TOVIFG_1 = 1;
    // no effect
    static const uint32_t ADC14CLRIFGR1_CLRADC14RDYIFG__CLRADC14RDYIFG_0 = 0;
    // clear pending interrupt flag
    static const uint32_t ADC14CLRIFGR1_CLRADC14RDYIFG__CLRADC14RDYIFG_1 = 1;

    // Interrupt Vector Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ADC14IV_t, uint32_t)
        // ADC14 interrupt vector value
        ADD_BITFIELD_RW(ADC14IV, 0, 32)
    END_TYPE()

    // No interrupt pending
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_0 = 0;
    // Interrupt Source: ADC14MEMx overflow; Interrupt Flag: ADC14OVIFG; Interrupt Priority: Highest
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_2 = 2;
    // Interrupt Source: Conversion time overflow; Interrupt Flag: ADC14TOVIFG
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_4 = 4;
    // Interrupt Source: ADC14 window high interrupt flag; Interrupt Flag: ADC14HIIFG
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_6 = 6;
    // Interrupt Source: ADC14 window low interrupt flag; Interrupt Flag: ADC14LOIFG
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_8 = 8;
    // Interrupt Source: ADC14 in-window interrupt flag; Interrupt Flag: ADC14INIFG
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_10 = 10;
    // Interrupt Source: ADC14MEM0 interrupt flag; Interrupt Flag: ADC14IFG0
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_12 = 12;
    // Interrupt Source: ADC14MEM1 interrupt flag; Interrupt Flag: ADC14IFG1
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_14 = 14;
    // Interrupt Source: ADC14MEM2 interrupt flag; Interrupt Flag: ADC14IFG2
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_16 = 16;
    // Interrupt Source: ADC14MEM3 interrupt flag; Interrupt Flag: ADC14IFG3
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_18 = 18;
    // Interrupt Source: ADC14MEM4 interrupt flag; Interrupt Flag: ADC14IFG4
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_20 = 20;
    // Interrupt Source: ADC14MEM5 interrupt flag; Interrupt Flag: ADC14IFG5
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_22 = 22;
    // Interrupt Source: ADC14MEM6 interrupt flag; Interrupt Flag: ADC14IFG6
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_24 = 24;
    // Interrupt Source: ADC14MEM7 interrupt flag; Interrupt Flag: ADC14IFG7
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_26 = 26;
    // Interrupt Source: ADC14MEM8 interrupt flag; Interrupt Flag: ADC14IFG8
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_28 = 28;
    // Interrupt Source: ADC14MEM9 interrupt flag; Interrupt Flag: ADC14IFG9
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_30 = 30;
    // Interrupt Source: ADC14MEM10 interrupt flag; Interrupt Flag: ADC14IFG10
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_32 = 32;
    // Interrupt Source: ADC14MEM11 interrupt flag; Interrupt Flag: ADC14IFG11
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_34 = 34;
    // Interrupt Source: ADC14MEM12 interrupt flag; Interrupt Flag: ADC14IFG12
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_36 = 36;
    // Interrupt Source: ADC14MEM13 interrupt flag; Interrupt Flag: ADC14IFG13
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_38 = 38;
    // Interrupt Source: ADC14MEM14 interrupt flag; Interrupt Flag: ADC14IFG14
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_40 = 40;
    // Interrupt Source: ADC14MEM15 interrupt flag; Interrupt Flag: ADC14IFG15
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_42 = 42;
    // Interrupt Source: ADC14MEM16 interrupt flag; Interrupt Flag: ADC14IFG16
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_44 = 44;
    // Interrupt Source: ADC14MEM17 interrupt flag; Interrupt Flag: ADC14IFG17
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_46 = 46;
    // Interrupt Source: ADC14MEM18 interrupt flag; Interrupt Flag: ADC14IFG18
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_48 = 48;
    // Interrupt Source: ADC14MEM19 interrupt flag; Interrupt Flag: ADC14IFG19
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_50 = 50;
    // Interrupt Source: ADC14MEM20 interrupt flag; Interrupt Flag: ADC14IFG20
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_52 = 52;
    // Interrupt Source: ADC14MEM22 interrupt flag; Interrupt Flag: ADC14IFG22
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_54 = 54;
    // Interrupt Source: ADC14MEM22 interrupt flag; Interrupt Flag: ADC14IFG22
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_56 = 56;
    // Interrupt Source: ADC14MEM23 interrupt flag; Interrupt Flag: ADC14IFG23
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_58 = 58;
    // Interrupt Source: ADC14MEM24 interrupt flag; Interrupt Flag: ADC14IFG24
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_60 = 60;
    // Interrupt Source: ADC14MEM25 interrupt flag; Interrupt Flag: ADC14IFG25
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_62 = 62;
    // Interrupt Source: ADC14MEM26 interrupt flag; Interrupt Flag: ADC14IFG26
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_64 = 64;
    // Interrupt Source: ADC14MEM27 interrupt flag; Interrupt Flag: ADC14IFG27
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_66 = 66;
    // Interrupt Source: ADC14MEM28 interrupt flag; Interrupt Flag: ADC14IFG28
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_68 = 68;
    // Interrupt Source: ADC14MEM29 interrupt flag; Interrupt Flag: ADC14IFG29
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_70 = 70;
    // Interrupt Source: ADC14MEM30 interrupt flag; Interrupt Flag: ADC14IFG30
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_72 = 72;
    // Interrupt Source: ADC14MEM31 interrupt flag; Interrupt Flag: ADC14IFG31
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_74 = 74;
    // Interrupt Source: ADC14RDYIFG interrupt flag; Interrupt Flag: ADC14RDYIFG; Interrupt Priority: Lowest
    static const uint32_t ADC14IV_ADC14IV__ADC14IV_76 = 76;

    struct ADC14_t {
        ADC14CTL0_t                   ADC14CTL0;
        ADC14CTL1_t                   ADC14CTL1;
        ADC14LO0_t                    ADC14LO0;
        ADC14HI0_t                    ADC14HI0;
        ADC14LO1_t                    ADC14LO1;
        ADC14HI1_t                    ADC14HI1;
        ADC14MCTL_t                   ADC14MCTL0;
        ADC14MCTL_t                   ADC14MCTL1;
        ADC14MCTL_t                   ADC14MCTL2;
        ADC14MCTL_t                   ADC14MCTL3;
        ADC14MCTL_t                   ADC14MCTL4;
        ADC14MCTL_t                   ADC14MCTL5;
        ADC14MCTL_t                   ADC14MCTL6;
        ADC14MCTL_t                   ADC14MCTL7;
        ADC14MCTL_t                   ADC14MCTL8;
        ADC14MCTL_t                   ADC14MCTL9;
        ADC14MCTL_t                   ADC14MCTL10;
        ADC14MCTL_t                   ADC14MCTL11;
        ADC14MCTL_t                   ADC14MCTL12;
        ADC14MCTL_t                   ADC14MCTL13;
        ADC14MCTL_t                   ADC14MCTL14;
        ADC14MCTL_t                   ADC14MCTL15;
        ADC14MCTL_t                   ADC14MCTL16;
        ADC14MCTL_t                   ADC14MCTL17;
        ADC14MCTL_t                   ADC14MCTL18;
        ADC14MCTL_t                   ADC14MCTL19;
        ADC14MCTL_t                   ADC14MCTL20;
        ADC14MCTL_t                   ADC14MCTL21;
        ADC14MCTL_t                   ADC14MCTL22;
        ADC14MCTL_t                   ADC14MCTL23;
        ADC14MCTL_t                   ADC14MCTL24;
        ADC14MCTL_t                   ADC14MCTL25;
        ADC14MCTL_t                   ADC14MCTL26;
        ADC14MCTL_t                   ADC14MCTL27;
        ADC14MCTL_t                   ADC14MCTL28;
        ADC14MCTL_t                   ADC14MCTL29;
        ADC14MCTL_t                   ADC14MCTL30;
        ADC14MCTL_t                   ADC14MCTL31;
        ADC14MEM_t                    ADC14MEM0;
        ADC14MEM_t                    ADC14MEM1;
        ADC14MEM_t                    ADC14MEM2;
        ADC14MEM_t                    ADC14MEM3;
        ADC14MEM_t                    ADC14MEM4;
        ADC14MEM_t                    ADC14MEM5;
        ADC14MEM_t                    ADC14MEM6;
        ADC14MEM_t                    ADC14MEM7;
        ADC14MEM_t                    ADC14MEM8;
        ADC14MEM_t                    ADC14MEM9;
        ADC14MEM_t                    ADC14MEM10;
        ADC14MEM_t                    ADC14MEM11;
        ADC14MEM_t                    ADC14MEM12;
        ADC14MEM_t                    ADC14MEM13;
        ADC14MEM_t                    ADC14MEM14;
        ADC14MEM_t                    ADC14MEM15;
        ADC14MEM_t                    ADC14MEM16;
        ADC14MEM_t                    ADC14MEM17;
        ADC14MEM_t                    ADC14MEM18;
        ADC14MEM_t                    ADC14MEM19;
        ADC14MEM_t                    ADC14MEM20;
        ADC14MEM_t                    ADC14MEM21;
        ADC14MEM_t                    ADC14MEM22;
        ADC14MEM_t                    ADC14MEM23;
        ADC14MEM_t                    ADC14MEM24;
        ADC14MEM_t                    ADC14MEM25;
        ADC14MEM_t                    ADC14MEM26;
        ADC14MEM_t                    ADC14MEM27;
        ADC14MEM_t                    ADC14MEM28;
        ADC14MEM_t                    ADC14MEM29;
        ADC14MEM_t                    ADC14MEM30;
        ADC14MEM_t                    ADC14MEM31;
        uint32_t                      reserved0[9];
        ADC14IER0_t                   ADC14IER0;
        ADC14IER1_t                   ADC14IER1;
        ADC14IFGR0_t                  ADC14IFGR0;
        ADC14IFGR1_t                  ADC14IFGR1;
        ADC14CLRIFGR0_t               ADC14CLRIFGR0;
        ADC14CLRIFGR1_t               ADC14CLRIFGR1;
        ADC14IV_t                     ADC14IV;
    };

    static ADC14_t & ADC14     = (*(ADC14_t *)0x40012000);

} // _ADC14_

// ITM
namespace _ITM_  {

    // ITM Stimulus Port 0
    typedef uint32_t ITM_STIM0_t;

    // ITM Stimulus Port 1
    typedef uint32_t ITM_STIM1_t;

    // ITM Stimulus Port 2
    typedef uint32_t ITM_STIM2_t;

    // ITM Stimulus Port 3
    typedef uint32_t ITM_STIM3_t;

    // ITM Stimulus Port 4
    typedef uint32_t ITM_STIM4_t;

    // ITM Stimulus Port 5
    typedef uint32_t ITM_STIM5_t;

    // ITM Stimulus Port 6
    typedef uint32_t ITM_STIM6_t;

    // ITM Stimulus Port 7
    typedef uint32_t ITM_STIM7_t;

    // ITM Stimulus Port 8
    typedef uint32_t ITM_STIM8_t;

    // ITM Stimulus Port 9
    typedef uint32_t ITM_STIM9_t;

    // ITM Stimulus Port 10
    typedef uint32_t ITM_STIM10_t;

    // ITM Stimulus Port 11
    typedef uint32_t ITM_STIM11_t;

    // ITM Stimulus Port 12
    typedef uint32_t ITM_STIM12_t;

    // ITM Stimulus Port 13
    typedef uint32_t ITM_STIM13_t;

    // ITM Stimulus Port 14
    typedef uint32_t ITM_STIM14_t;

    // ITM Stimulus Port 15
    typedef uint32_t ITM_STIM15_t;

    // ITM Stimulus Port 16
    typedef uint32_t ITM_STIM16_t;

    // ITM Stimulus Port 17
    typedef uint32_t ITM_STIM17_t;

    // ITM Stimulus Port 18
    typedef uint32_t ITM_STIM18_t;

    // ITM Stimulus Port 19
    typedef uint32_t ITM_STIM19_t;

    // ITM Stimulus Port 20
    typedef uint32_t ITM_STIM20_t;

    // ITM Stimulus Port 21
    typedef uint32_t ITM_STIM21_t;

    // ITM Stimulus Port 22
    typedef uint32_t ITM_STIM22_t;

    // ITM Stimulus Port 23
    typedef uint32_t ITM_STIM23_t;

    // ITM Stimulus Port 24
    typedef uint32_t ITM_STIM24_t;

    // ITM Stimulus Port 25
    typedef uint32_t ITM_STIM25_t;

    // ITM Stimulus Port 26
    typedef uint32_t ITM_STIM26_t;

    // ITM Stimulus Port 27
    typedef uint32_t ITM_STIM27_t;

    // ITM Stimulus Port 28
    typedef uint32_t ITM_STIM28_t;

    // ITM Stimulus Port 29
    typedef uint32_t ITM_STIM29_t;

    // ITM Stimulus Port 30
    typedef uint32_t ITM_STIM30_t;

    // ITM Stimulus Port 31
    typedef uint32_t ITM_STIM31_t;

    // ITM Trace Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ITM_TER_t, uint32_t)
        // Bit mask to enable tracing on ITM stimulus ports. One bit per stimulus port.
        ADD_BITFIELD_RW(STIMENA, 0, 32)
    END_TYPE()

    // ITM Trace Privilege Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ITM_TPR_t, uint32_t)
        // Bit mask to enable tracing on ITM stimulus ports: bit [0] = stimulus ports [7:0], bit [1] = stimulus ports [15:8], bit [2] = stimulus ports [23:16], bit [3] = stimulus ports [31:24].
        ADD_BITFIELD_RW(PRIVMASK, 0, 4)
    END_TYPE()

    // ITM Trace Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ITM_TCR_t, uint32_t)
        // Enable ITM. This is the master enable, and must be set before ITM Stimulus and Trace Enable registers can be written.
        ADD_BITFIELD_RW(ITMENA, 0, 1)
        // Enables differential timestamps. Differential timestamps are emitted when a packet is written to the FIFO with a non-zero timestamp counter, and when the timestamp counter overflows. Timestamps are emitted during idle times after a fixed number of two million cycles. This provides a time reference for packets and inter-packet gaps. If SWOENA (bit [4]) is set, timestamps are triggered by activity on the internal trace bus only. In this case there is no regular timestamp output when the ITM is idle.
        ADD_BITFIELD_RW(TSENA, 1, 1)
        // Enables sync packets for TPIU.
        ADD_BITFIELD_RW(SYNCENA, 2, 1)
        // Enables the DWT stimulus.
        ADD_BITFIELD_RW(DWTENA, 3, 1)
        // Enables asynchronous clocking of the timestamp counter.
        ADD_BITFIELD_RW(SWOENA, 4, 1)
        // TSPrescale Timestamp prescaler.
        ADD_BITFIELD_RW(TSPRESCALE, 8, 2)
        // ATB ID for CoreSight system.
        ADD_BITFIELD_RW(ATBID, 16, 7)
        // Set when ITM events present and being drained.
        ADD_BITFIELD_RW(BUSY, 23, 1)
    END_TYPE()

    // no prescaling
    static const uint32_t ITM_TCR_TSPRESCALE__en_0b00 = 0;
    // divide by 4
    static const uint32_t ITM_TCR_TSPRESCALE__en_0b01 = 1;
    // divide by 16
    static const uint32_t ITM_TCR_TSPRESCALE__en_0b10 = 2;
    // divide by 64
    static const uint32_t ITM_TCR_TSPRESCALE__en_0b11 = 3;

    // ITM Integration Write Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ITM_IWR_t, uint32_t)
        // When the integration mode is set: 0 = ATVALIDM clear. 1 = ATVALIDM set.
        ADD_BITFIELD_WO(ATVALIDM, 0, 1)
    END_TYPE()

    // ATVALIDM clear
    static const uint32_t ITM_IWR_ATVALIDM__en_0b0 = 0;
    // ATVALIDM set
    static const uint32_t ITM_IWR_ATVALIDM__en_0b1 = 1;

    // ITM Integration Mode Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ITM_IMCR_t, uint32_t)
        ADD_BITFIELD_RW(INTEGRATION, 0, 1)
    END_TYPE()

    // ATVALIDM normal
    static const uint32_t ITM_IMCR_INTEGRATION__en_0b0 = 0;
    // ATVALIDM driven from Integration Write Register
    static const uint32_t ITM_IMCR_INTEGRATION__en_0b1 = 1;

    // ITM Lock Access Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ITM_LAR_t, uint32_t)
        // A privileged write of 0xC5ACCE55 enables more write access to Control Register 0xE00::0xFFC. An invalid write removes write access.
        ADD_BITFIELD_WO(LOCK_ACCESS, 0, 32)
    END_TYPE()

    // ITM Lock Status Register
    // Reset value: 0x00000003
    BEGIN_TYPE(ITM_LSR_t, uint32_t)
        // Indicates that a lock mechanism exists for this component.
        ADD_BITFIELD_RO(PRESENT, 0, 1)
        // Write access to component is blocked. All writes are ignored, reads are permitted.
        ADD_BITFIELD_RO(ACCESS, 1, 1)
        // You cannot implement 8-bit lock accesses.
        ADD_BITFIELD_RO(BYTEACC, 2, 1)
    END_TYPE()

    struct ITM_t {
        ITM_STIM0_t                   ITM_STIM0;
        ITM_STIM1_t                   ITM_STIM1;
        ITM_STIM2_t                   ITM_STIM2;
        ITM_STIM3_t                   ITM_STIM3;
        ITM_STIM4_t                   ITM_STIM4;
        ITM_STIM5_t                   ITM_STIM5;
        ITM_STIM6_t                   ITM_STIM6;
        ITM_STIM7_t                   ITM_STIM7;
        ITM_STIM8_t                   ITM_STIM8;
        ITM_STIM9_t                   ITM_STIM9;
        ITM_STIM10_t                  ITM_STIM10;
        ITM_STIM11_t                  ITM_STIM11;
        ITM_STIM12_t                  ITM_STIM12;
        ITM_STIM13_t                  ITM_STIM13;
        ITM_STIM14_t                  ITM_STIM14;
        ITM_STIM15_t                  ITM_STIM15;
        ITM_STIM16_t                  ITM_STIM16;
        ITM_STIM17_t                  ITM_STIM17;
        ITM_STIM18_t                  ITM_STIM18;
        ITM_STIM19_t                  ITM_STIM19;
        ITM_STIM20_t                  ITM_STIM20;
        ITM_STIM21_t                  ITM_STIM21;
        ITM_STIM22_t                  ITM_STIM22;
        ITM_STIM23_t                  ITM_STIM23;
        ITM_STIM24_t                  ITM_STIM24;
        ITM_STIM25_t                  ITM_STIM25;
        ITM_STIM26_t                  ITM_STIM26;
        ITM_STIM27_t                  ITM_STIM27;
        ITM_STIM28_t                  ITM_STIM28;
        ITM_STIM29_t                  ITM_STIM29;
        ITM_STIM30_t                  ITM_STIM30;
        ITM_STIM31_t                  ITM_STIM31;
        uint32_t                      reserved0[864];
        ITM_TER_t                     ITM_TER;
        uint32_t                      reserved1[15];
        ITM_TPR_t                     ITM_TPR;
        uint32_t                      reserved2[15];
        ITM_TCR_t                     ITM_TCR;
        uint32_t                      reserved3[29];
        ITM_IWR_t                     ITM_IWR;
        uint32_t                      reserved4;
        ITM_IMCR_t                    ITM_IMCR;
        uint32_t                      reserved5[43];
        ITM_LAR_t                     ITM_LAR;
        ITM_LSR_t                     ITM_LSR;
    };

    static ITM_t & ITM     = (*(ITM_t *)0xe0000000);

} // _ITM_

// DWT
namespace _DWT_  {

    // DWT Control Register
    // Reset value: 0x40000000
    BEGIN_TYPE(DWT_CTRL_t, uint32_t)
        // Enable the CYCCNT counter. If not enabled, the counter does not count and no event is generated for PS sampling or CYCCNTENA. In normal use, the debugger must initialize the CYCCNT counter to 0.
        ADD_BITFIELD_RW(CYCCNTENA, 0, 1)
        // Reload value for POSTCNT, bits [8:5], post-scalar counter. If this value is 0, events are triggered on each tap change (a power of 2). If this field has a non-0 value, this forms a count-down value, to be reloaded into POSTCNT each time it reaches 0. For example, a value 1 in this register means an event is formed every other tap change.
        ADD_BITFIELD_RW(POSTPRESET, 1, 4)
        // Post-scalar counter for CYCTAP. When the selected tapped bit changes from 0 to 1 or 1 to 0, the post scalar counter is down-counted when not 0. If 0, it triggers an event for PCSAMPLENA or CYCEVTENA use. It also reloads with the value from POSTPRESET (bits [4:1]).
        ADD_BITFIELD_RW(POSTCNT, 5, 4)
        // Selects a tap on the DWT_CYCCNT register. These are spaced at bits [6] and [10]. When the selected bit in the CYCCNT register changes from 0 to 1 or 1 to 0, it emits into the POSTCNT, bits [8:5], post-scalar counter. That counter then counts down. On a bit change when post-scalar is 0, it triggers an event for PC sampling or CYCEVTCNT.
        ADD_BITFIELD_RW(CYCTAP, 9, 1)
        // Feeds a synchronization pulse to the ITM SYNCENA control. The value selected here picks the rate (approximately 1/second or less) by selecting a tap on the DWT_CYCCNT register. To use synchronization (heartbeat and hot-connect synchronization), CYCCNTENA must be set to 1, SYNCTAP must be set to one of its values, and SYNCENA must be set to 1.
        ADD_BITFIELD_RW(SYNCTAP, 10, 2)
        // Enables PC Sampling event. A PC sample event is emitted when the POSTCNT counter triggers it. See CYCTAP, bit [9], and POSTPRESET, bits [4:1], for details. Enabling this bit overrides CYCEVTENA (bit [20]). Reset clears the PCSAMPLENA bit.
        ADD_BITFIELD_RW(PCSAMPLEENA, 12, 1)
        // Enables Interrupt event tracing. Reset clears the EXCEVTENA bit.
        ADD_BITFIELD_RW(EXCTRCENA, 16, 1)
        // Enables CPI count event. Emits an event when DWT_CPICNT overflows (every 256 cycles of multi-cycle instructions). Reset clears the CPIEVTENA bit.
        ADD_BITFIELD_RW(CPIEVTENA, 17, 1)
        // Enables Interrupt overhead event. Emits an event when DWT_EXCCNT overflows (every 256 cycles of interrupt overhead). Reset clears the EXCEVTENA bit.
        ADD_BITFIELD_RW(EXCEVTENA, 18, 1)
        // Enables Sleep count event. Emits an event when DWT_SLEEPCNT overflows (every 256 cycles that the processor is sleeping). Reset clears the SLEEPEVTENA bit.
        ADD_BITFIELD_RW(SLEEPEVTENA, 19, 1)
        // Enables LSU count event. Emits an event when DWT_LSUCNT overflows (every 256 cycles of LSU operation). LSU counts include all LSU costs after the initial cycle for the instruction. Reset clears the LSUEVTENA bit.
        ADD_BITFIELD_RW(LSUEVTENA, 20, 1)
        // Enables Folded instruction count event. Emits an event when DWT_FOLDCNT overflows (every 256 cycles of folded instructions). A folded instruction is one that does not incur even one cycle to execute. For example, an IT instruction is folded away and so does not use up one cycle. Reset clears the FOLDEVTENA bit.
        ADD_BITFIELD_RW(FOLDEVTENA, 21, 1)
        // Enables Cycle count event. Emits an event when the POSTCNT counter triggers it. See CYCTAP (bit [9]) and POSTPRESET, bits [4:1], for details. This event is only emitted if PCSAMPLENA, bit [12], is disabled. PCSAMPLENA overrides the setting of this bit. Reset clears the CYCEVTENA bit.
        ADD_BITFIELD_RW(CYCEVTENA, 22, 1)
        // When set, DWT_FOLDCNT, DWT_LSUCNT, DWT_SLEEPCNT, DWT_EXCCNT, and DWT_CPICNT are not supported.
        ADD_BITFIELD_RW(NOPRFCNT, 24, 1)
        // When set, DWT_CYCCNT is not supported.
        ADD_BITFIELD_RW(NOCYCCNT, 25, 1)
    END_TYPE()

    // selects bit [6] to tap
    static const uint32_t DWT_CTRL_CYCTAP__en_0b0 = 0;
    // selects bit [10] to tap.
    static const uint32_t DWT_CTRL_CYCTAP__en_0b1 = 1;
    // Disabled. No synch counting.
    static const uint32_t DWT_CTRL_SYNCTAP__en_0b00 = 0;
    // Tap at CYCCNT bit 24.
    static const uint32_t DWT_CTRL_SYNCTAP__en_0b01 = 1;
    // Tap at CYCCNT bit 26.
    static const uint32_t DWT_CTRL_SYNCTAP__en_0b10 = 2;
    // Tap at CYCCNT bit 28.
    static const uint32_t DWT_CTRL_SYNCTAP__en_0b11 = 3;
    // PC Sampling event disabled.
    static const uint32_t DWT_CTRL_PCSAMPLEENA__en_0b0 = 0;
    // Sampling event enabled.
    static const uint32_t DWT_CTRL_PCSAMPLEENA__en_0b1 = 1;
    // interrupt event trace disabled.
    static const uint32_t DWT_CTRL_EXCTRCENA__en_0b0 = 0;
    // interrupt event trace enabled.
    static const uint32_t DWT_CTRL_EXCTRCENA__en_0b1 = 1;
    // CPI counter events disabled.
    static const uint32_t DWT_CTRL_CPIEVTENA__en_0b0 = 0;
    // CPI counter events enabled.
    static const uint32_t DWT_CTRL_CPIEVTENA__en_0b1 = 1;
    // Interrupt overhead event disabled.
    static const uint32_t DWT_CTRL_EXCEVTENA__en_0b0 = 0;
    // Interrupt overhead event enabled.
    static const uint32_t DWT_CTRL_EXCEVTENA__en_0b1 = 1;
    // Sleep count events disabled.
    static const uint32_t DWT_CTRL_SLEEPEVTENA__en_0b0 = 0;
    // Sleep count events enabled.
    static const uint32_t DWT_CTRL_SLEEPEVTENA__en_0b1 = 1;
    // LSU count events disabled.
    static const uint32_t DWT_CTRL_LSUEVTENA__en_0b0 = 0;
    // LSU count events enabled.
    static const uint32_t DWT_CTRL_LSUEVTENA__en_0b1 = 1;
    // Folded instruction count events disabled.
    static const uint32_t DWT_CTRL_FOLDEVTENA__en_0b0 = 0;
    // Folded instruction count events enabled.
    static const uint32_t DWT_CTRL_FOLDEVTENA__en_0b1 = 1;
    // Cycle count events disabled.
    static const uint32_t DWT_CTRL_CYCEVTENA__en_0b0 = 0;
    // Cycle count events enabled.
    static const uint32_t DWT_CTRL_CYCEVTENA__en_0b1 = 1;

    // DWT Current PC Sampler Cycle Count Register
    // Reset value: 0x00000000
    BEGIN_TYPE(DWT_CYCCNT_t, uint32_t)
        // Current PC Sampler Cycle Counter count value. When enabled, this counter counts the number of core cycles, except when the core is halted. CYCCNT is a free running counter, counting upwards. It wraps around to 0 on overflow. The debugger must initialize this to 0 when first enabling.
        ADD_BITFIELD_RW(CYCCNT, 0, 32)
    END_TYPE()

    // DWT CPI Count Register
    BEGIN_TYPE(DWT_CPICNT_t, uint32_t)
        // Current CPI counter value. Increments on the additional cycles (the first cycle is not counted) required to execute all instructions except those recorded by DWT_LSUCNT. This counter also increments on all instruction fetch stalls. If CPIEVTENA is set, an event is emitted when the counter overflows. Clears to 0 on enabling.
        ADD_BITFIELD_RW(CPICNT, 0, 8)
    END_TYPE()

    // DWT Exception Overhead Count Register
    BEGIN_TYPE(DWT_EXCCNT_t, uint32_t)
        // Current interrupt overhead counter value. Counts the total cycles spent in interrupt processing (for example entry stacking, return unstacking, pre-emption). An event is emitted on counter overflow (every 256 cycles). This counter initializes to 0 when enabled. Clears to 0 on enabling.
        ADD_BITFIELD_RW(EXCCNT, 0, 8)
    END_TYPE()

    // DWT Sleep Count Register
    BEGIN_TYPE(DWT_SLEEPCNT_t, uint32_t)
        // Sleep counter. Counts the number of cycles during which the processor is sleeping. An event is emitted on counter overflow (every 256 cycles). This counter initializes to 0 when enabled. Note that SLEEPCNT is clocked using FCLK. It is possible that the frequency of FCLK might be reduced while the processor is sleeping to minimize power consumption. This means that sleep duration must be calculated with the frequency of FCLK during sleep.
        ADD_BITFIELD_RW(SLEEPCNT, 0, 8)
    END_TYPE()

    // DWT LSU Count Register
    BEGIN_TYPE(DWT_LSUCNT_t, uint32_t)
        // LSU counter. This counts the total number of cycles that the processor is processing an LSU operation. The initial execution cost of the instruction is not counted. For example, an LDR that takes two cycles to complete increments this counter one cycle. Equivalently, an LDR that stalls for two cycles (and so takes four cycles), increments this counter three times. An event is emitted on counter overflow (every 256 cycles). Clears to 0 on enabling.
        ADD_BITFIELD_RW(LSUCNT, 0, 8)
    END_TYPE()

    // DWT Fold Count Register
    BEGIN_TYPE(DWT_FOLDCNT_t, uint32_t)
        // This counts the total number folded instructions. This counter initializes to 0 when enabled.
        ADD_BITFIELD_RW(FOLDCNT, 0, 8)
    END_TYPE()

    // DWT Program Counter Sample Register
    BEGIN_TYPE(DWT_PCSR_t, uint32_t)
        // Execution instruction address sample, or 0xFFFFFFFF if the core is halted.
        ADD_BITFIELD_RO(EIASAMPLE, 0, 32)
    END_TYPE()

    // DWT Comparator Register 0
    BEGIN_TYPE(DWT_COMP0_t, uint32_t)
        // Data value to compare against PC and the data address as given by DWT_FUNCTION0. DWT_COMP0 can also compare against the value of the PC Sampler Counter (DWT_CYCCNT).
        ADD_BITFIELD_RW(COMP, 0, 32)
    END_TYPE()

    // DWT Mask Register 0
    BEGIN_TYPE(DWT_MASK0_t, uint32_t)
        // Mask on data address when matching against COMP. This is the size of the ignore mask. hat is, DWT matching is performed as:(ADDR ANDed with (~0 left bit-shifted by MASK)) == COMP. However, the actual comparison is slightly more complex to enable matching an address wherever it appears on a bus. So, if COMP is 3, this matches a word access of 0, because 3 would be within the word.
        ADD_BITFIELD_RW(MASK, 0, 4)
    END_TYPE()

    // DWT Function Register 0
    // Reset value: 0x00000000
    BEGIN_TYPE(DWT_FUNCTION0_t, uint32_t)
        // Function settings. Note 1: If the ETM is not fitted, then ETM trigger is not possible. Note 2: Data value is only sampled for accesses that do not fault (MPU or bus fault). The PC is sampled irrespective of any faults. The PC is only sampled for the first address of a burst. Note 3: PC match is not recommended for watchpoints because it stops after the instruction. It mainly guards and triggers the ETM.
        ADD_BITFIELD_RW(FUNCTION, 0, 4)
        // Emit range field. Reserved to permit emitting offset when range match occurs. Reset clears the EMITRANGE bit. PC sampling is not supported when EMITRANGE is enabled. EMITRANGE only applies for: FUNCTION = b0001, b0010, b0011, b1100, b1101, b1110, and b1111.
        ADD_BITFIELD_RW(EMITRANGE, 5, 1)
        // This bit is only available in comparator 1. When DATAVMATCH is set, this comparator performs data value compares. The comparators given by DATAVADDR0 and DATAVADDR1provide the address for the data comparison. If DATAVMATCH is set in DWT_FUNCTION1, the FUNCTION setting for the comparators given by DATAVADDR0 and DATAVADDR1 are overridden and those comparators only provide the address match for the data comparison.
        ADD_BITFIELD_RW(DATAVMATCH, 8, 1)
        ADD_BITFIELD_RO(LNK1ENA, 9, 1)
        // Defines the size of the data in the COMP register that is to be matched:
        ADD_BITFIELD_RW(DATAVSIZE, 10, 2)
        // Identity of a linked address comparator for data value matching when DATAVMATCH == 1.
        ADD_BITFIELD_RW(DATAVADDR0, 12, 4)
        // Identity of a second linked address comparator for data value matching when DATAVMATCH == 1 and LNK1ENA == 1.
        ADD_BITFIELD_RW(DATAVADDR1, 16, 4)
        // This bit is set when the comparator matches, and indicates that the operation defined by FUNCTION has occurred since this bit was last read. This bit is cleared on read.
        ADD_BITFIELD_RW(MATCHED, 24, 1)
    END_TYPE()

    // Disabled
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b0000 = 0;
    // EMITRANGE = 0, sample and emit PC through ITM. EMITRANGE = 1, emit address offset through ITM
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b0001 = 1;
    // EMITRANGE = 0, emit data through ITM on read and write. EMITRANGE = 1, emit data and address offset through ITM on read or write.
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b0010 = 2;
    // EMITRANGE = 0, sample PC and data value through ITM on read or write. EMITRANGE = 1, emit address offset and data value through ITM on read or write.
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b0011 = 3;
    // Watchpoint on PC match.
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b0100 = 4;
    // Watchpoint on read.
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b0101 = 5;
    // Watchpoint on write.
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b0110 = 6;
    // Watchpoint on read or write.
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b0111 = 7;
    // ETM trigger on PC match
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b1000 = 8;
    // ETM trigger on read
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b1001 = 9;
    // ETM trigger on write
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b1010 = 10;
    // ETM trigger on read or write
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b1011 = 11;
    // EMITRANGE = 0, sample data for read transfers. EMITRANGE = 1, sample Daddr [15:0] for read transfers
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b1100 = 12;
    // EMITRANGE = 0, sample data for write transfers. EMITRANGE = 1, sample Daddr [15:0] for write transfers
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b1101 = 13;
    // EMITRANGE = 0, sample PC + data for read transfers. EMITRANGE = 1, sample Daddr [15:0] + data for read transfers
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b1110 = 14;
    // EMITRANGE = 0, sample PC + data for write transfers. EMITRANGE = 1, sample Daddr [15:0] + data for write transfers
    static const uint32_t DWT_FUNCTION0_FUNCTION__en_0b1111 = 15;
    // DATAVADDR1 not supported
    static const uint32_t DWT_FUNCTION0_LNK1ENA__en_0b0 = 0;
    // DATAVADDR1 supported (enabled).
    static const uint32_t DWT_FUNCTION0_LNK1ENA__en_0b1 = 1;
    // byte
    static const uint32_t DWT_FUNCTION0_DATAVSIZE__en_0b00 = 0;
    // halfword
    static const uint32_t DWT_FUNCTION0_DATAVSIZE__en_0b01 = 1;
    // word
    static const uint32_t DWT_FUNCTION0_DATAVSIZE__en_0b10 = 2;
    // Unpredictable.
    static const uint32_t DWT_FUNCTION0_DATAVSIZE__en_0b11 = 3;

    // DWT Comparator Register 1
    BEGIN_TYPE(DWT_COMP1_t, uint32_t)
        // Data value to compare against PC and the data address as given by DWT_FUNCTION1.
        ADD_BITFIELD_RW(COMP, 0, 32)
    END_TYPE()

    // DWT Mask Register 1
    BEGIN_TYPE(DWT_MASK1_t, uint32_t)
        // Mask on data address when matching against COMP. This is the size of the ignore mask. hat is, DWT matching is performed as:(ADDR ANDed with (~0 left bit-shifted by MASK)) == COMP. However, the actual comparison is slightly more complex to enable matching an address wherever it appears on a bus. So, if COMP is 3, this matches a word access of 0, because 3 would be within the word.
        ADD_BITFIELD_RW(MASK, 0, 4)
    END_TYPE()

    // DWT Function Register 1
    // Reset value: 0x00000000
    BEGIN_TYPE(DWT_FUNCTION1_t, uint32_t)
        // Function settings. Note 1: If the ETM is not fitted, then ETM trigger is not possible. Note 2: Data value is only sampled for accesses that do not fault (MPU or bus fault). The PC is sampled irrespective of any faults. The PC is only sampled for the first address of a burst. Note 3: FUNCTION is overridden for comparators given by DATAVADDR0 and DATAVADDR1 in DWT_FUNCTION1if DATAVMATCH is also set in DWT_FUNCTION1. The comparators given by DATAVADDR0 and DATAVADDR1 can then only perform address comparator matches for comparator 1 data matches. Note 4: If the data matching functionality is not included during implementation it is not possible to set DATAVADDR0, DATAVADDR1, or DATAVMATCH in DWT_FUNCTION1. This means that the data matching functionality is not available in the implementation. Test the availability of data matching by writing and reading the DATAVMATCH bit in DWT_FUNCTION1. If it is not settable then data matching is unavailable. Note 5: PC match is not recommended for watchpoints because it stops after the instruction. It mainly guards and triggers the ETM.
        ADD_BITFIELD_RW(FUNCTION, 0, 4)
        // Emit range field. Reserved to permit emitting offset when range match occurs. Reset clears the EMITRANGE bit. PC sampling is not supported when EMITRANGE is enabled. EMITRANGE only applies for: FUNCTION = b0001, b0010, b0011, b1100, b1101, b1110, and b1111.
        ADD_BITFIELD_RW(EMITRANGE, 5, 1)
        // Only available in comparator 0. When set, this comparator compares against the clock cycle counter.
        ADD_BITFIELD_RW(CYCMATCH, 7, 1)
        // This bit is only available in comparator 1. When DATAVMATCH is set, this comparator performs data value compares. The comparators given by DATAVADDR0 and DATAVADDR1provide the address for the data comparison. If DATAVMATCH is set in DWT_FUNCTION1, the FUNCTION setting for the comparators given by DATAVADDR0 and DATAVADDR1 are overridden and those comparators only provide the address match for the data comparison.
        ADD_BITFIELD_RW(DATAVMATCH, 8, 1)
        ADD_BITFIELD_RO(LNK1ENA, 9, 1)
        // Defines the size of the data in the COMP register that is to be matched:
        ADD_BITFIELD_RW(DATAVSIZE, 10, 2)
        // Identity of a linked address comparator for data value matching when DATAVMATCH == 1.
        ADD_BITFIELD_RW(DATAVADDR0, 12, 4)
        // Identity of a second linked address comparator for data value matching when DATAVMATCH == 1 and LNK1ENA == 1.
        ADD_BITFIELD_RW(DATAVADDR1, 16, 4)
        // This bit is set when the comparator matches, and indicates that the operation defined by FUNCTION has occurred since this bit was last read. This bit is cleared on read.
        ADD_BITFIELD_RW(MATCHED, 24, 1)
    END_TYPE()

    // Disabled
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b0000 = 0;
    // EMITRANGE = 0, sample and emit PC through ITM. EMITRANGE = 1, emit address offset through ITM
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b0001 = 1;
    // EMITRANGE = 0, emit data through ITM on read and write. EMITRANGE = 1, emit data and address offset through ITM on read or write.
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b0010 = 2;
    // EMITRANGE = 0, sample PC and data value through ITM on read or write. EMITRANGE = 1, emit address offset and data value through ITM on read or write.
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b0011 = 3;
    // Watchpoint on PC match.
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b0100 = 4;
    // Watchpoint on read.
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b0101 = 5;
    // Watchpoint on write.
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b0110 = 6;
    // Watchpoint on read or write.
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b0111 = 7;
    // ETM trigger on PC match
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b1000 = 8;
    // ETM trigger on read
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b1001 = 9;
    // ETM trigger on write
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b1010 = 10;
    // ETM trigger on read or write
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b1011 = 11;
    // EMITRANGE = 0, sample data for read transfers. EMITRANGE = 1, sample Daddr [15:0] for read transfers
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b1100 = 12;
    // EMITRANGE = 0, sample data for write transfers. EMITRANGE = 1, sample Daddr [15:0] for write transfers
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b1101 = 13;
    // EMITRANGE = 0, sample PC + data for read transfers. EMITRANGE = 1, sample Daddr [15:0] + data for read transfers
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b1110 = 14;
    // EMITRANGE = 0, sample PC + data for write transfers. EMITRANGE = 1, sample Daddr [15:0] + data for write transfers
    static const uint32_t DWT_FUNCTION1_FUNCTION__en_0b1111 = 15;
    // DATAVADDR1 not supported
    static const uint32_t DWT_FUNCTION1_LNK1ENA__en_0b0 = 0;
    // DATAVADDR1 supported (enabled).
    static const uint32_t DWT_FUNCTION1_LNK1ENA__en_0b1 = 1;
    // byte
    static const uint32_t DWT_FUNCTION1_DATAVSIZE__en_0b00 = 0;
    // halfword
    static const uint32_t DWT_FUNCTION1_DATAVSIZE__en_0b01 = 1;
    // word
    static const uint32_t DWT_FUNCTION1_DATAVSIZE__en_0b10 = 2;
    // Unpredictable.
    static const uint32_t DWT_FUNCTION1_DATAVSIZE__en_0b11 = 3;

    // DWT Comparator Register 2
    BEGIN_TYPE(DWT_COMP2_t, uint32_t)
        // Data value to compare against PC and the data address as given by DWT_FUNCTION2.
        ADD_BITFIELD_RW(COMP, 0, 32)
    END_TYPE()

    // DWT Mask Register 2
    BEGIN_TYPE(DWT_MASK2_t, uint32_t)
        // Mask on data address when matching against COMP. This is the size of the ignore mask. hat is, DWT matching is performed as:(ADDR ANDed with (~0 left bit-shifted by MASK)) == COMP. However, the actual comparison is slightly more complex to enable matching an address wherever it appears on a bus. So, if COMP is 3, this matches a word access of 0, because 3 would be within the word.
        ADD_BITFIELD_RW(MASK, 0, 4)
    END_TYPE()

    // DWT Function Register 2
    // Reset value: 0x00000000
    BEGIN_TYPE(DWT_FUNCTION2_t, uint32_t)
        // Function settings. Note 1: If the ETM is not fitted, then ETM trigger is not possible. Note 2: Data value is only sampled for accesses that do not fault (MPU or bus fault). The PC is sampled irrespective of any faults. The PC is only sampled for the first address of a burst. Note 3: PC match is not recommended for watchpoints because it stops after the instruction. It mainly guards and triggers the ETM.
        ADD_BITFIELD_RW(FUNCTION, 0, 4)
        // Emit range field. Reserved to permit emitting offset when range match occurs. Reset clears the EMITRANGE bit. PC sampling is not supported when EMITRANGE is enabled. EMITRANGE only applies for: FUNCTION = b0001, b0010, b0011, b1100, b1101, b1110, and b1111.
        ADD_BITFIELD_RW(EMITRANGE, 5, 1)
        // This bit is only available in comparator 1. When DATAVMATCH is set, this comparator performs data value compares. The comparators given by DATAVADDR0 and DATAVADDR1provide the address for the data comparison. If DATAVMATCH is set in DWT_FUNCTION1, the FUNCTION setting for the comparators given by DATAVADDR0 and DATAVADDR1 are overridden and those comparators only provide the address match for the data comparison.
        ADD_BITFIELD_RW(DATAVMATCH, 8, 1)
        ADD_BITFIELD_RO(LNK1ENA, 9, 1)
        // Defines the size of the data in the COMP register that is to be matched:
        ADD_BITFIELD_RW(DATAVSIZE, 10, 2)
        // Identity of a linked address comparator for data value matching when DATAVMATCH == 1.
        ADD_BITFIELD_RW(DATAVADDR0, 12, 4)
        // Identity of a second linked address comparator for data value matching when DATAVMATCH == 1 and LNK1ENA == 1.
        ADD_BITFIELD_RW(DATAVADDR1, 16, 4)
        // This bit is set when the comparator matches, and indicates that the operation defined by FUNCTION has occurred since this bit was last read. This bit is cleared on read.
        ADD_BITFIELD_RW(MATCHED, 24, 1)
    END_TYPE()

    // Disabled
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b0000 = 0;
    // EMITRANGE = 0, sample and emit PC through ITM. EMITRANGE = 1, emit address offset through ITM
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b0001 = 1;
    // EMITRANGE = 0, emit data through ITM on read and write. EMITRANGE = 1, emit data and address offset through ITM on read or write.
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b0010 = 2;
    // EMITRANGE = 0, sample PC and data value through ITM on read or write. EMITRANGE = 1, emit address offset and data value through ITM on read or write.
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b0011 = 3;
    // Watchpoint on PC match.
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b0100 = 4;
    // Watchpoint on read.
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b0101 = 5;
    // Watchpoint on write.
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b0110 = 6;
    // Watchpoint on read or write.
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b0111 = 7;
    // ETM trigger on PC match
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b1000 = 8;
    // ETM trigger on read
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b1001 = 9;
    // ETM trigger on write
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b1010 = 10;
    // ETM trigger on read or write
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b1011 = 11;
    // EMITRANGE = 0, sample data for read transfers. EMITRANGE = 1, sample Daddr [15:0] for read transfers
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b1100 = 12;
    // EMITRANGE = 0, sample data for write transfers. EMITRANGE = 1, sample Daddr [15:0] for write transfers
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b1101 = 13;
    // EMITRANGE = 0, sample PC + data for read transfers. EMITRANGE = 1, sample Daddr [15:0] + data for read transfers
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b1110 = 14;
    // EMITRANGE = 0, sample PC + data for write transfers. EMITRANGE = 1, sample Daddr [15:0] + data for write transfers
    static const uint32_t DWT_FUNCTION2_FUNCTION__en_0b1111 = 15;
    // DATAVADDR1 not supported
    static const uint32_t DWT_FUNCTION2_LNK1ENA__en_0b0 = 0;
    // DATAVADDR1 supported (enabled).
    static const uint32_t DWT_FUNCTION2_LNK1ENA__en_0b1 = 1;
    // byte
    static const uint32_t DWT_FUNCTION2_DATAVSIZE__en_0b00 = 0;
    // halfword
    static const uint32_t DWT_FUNCTION2_DATAVSIZE__en_0b01 = 1;
    // word
    static const uint32_t DWT_FUNCTION2_DATAVSIZE__en_0b10 = 2;
    // Unpredictable.
    static const uint32_t DWT_FUNCTION2_DATAVSIZE__en_0b11 = 3;

    // DWT Comparator Register 3
    BEGIN_TYPE(DWT_COMP3_t, uint32_t)
        // Data value to compare against PC and the data address as given by DWT_FUNCTION3.
        ADD_BITFIELD_RW(COMP, 0, 32)
    END_TYPE()

    // DWT Mask Register 3
    BEGIN_TYPE(DWT_MASK3_t, uint32_t)
        // Mask on data address when matching against COMP. This is the size of the ignore mask. hat is, DWT matching is performed as:(ADDR ANDed with (~0 left bit-shifted by MASK)) == COMP. However, the actual comparison is slightly more complex to enable matching an address wherever it appears on a bus. So, if COMP is 3, this matches a word access of 0, because 3 would be within the word.
        ADD_BITFIELD_RW(MASK, 0, 4)
    END_TYPE()

    // DWT Function Register 3
    // Reset value: 0x00000000
    BEGIN_TYPE(DWT_FUNCTION3_t, uint32_t)
        // Function settings. Note 1: If the ETM is not fitted, then ETM trigger is not possible. Note 2: Data value is only sampled for accesses that do not fault (MPU or bus fault). The PC is sampled irrespective of any faults. The PC is only sampled for the first address of a burst. Note 3: PC match is not recommended for watchpoints because it stops after the instruction. It mainly guards and triggers the ETM.
        ADD_BITFIELD_RW(FUNCTION, 0, 4)
        // Emit range field. Reserved to permit emitting offset when range match occurs. Reset clears the EMITRANGE bit. PC sampling is not supported when EMITRANGE is enabled. EMITRANGE only applies for: FUNCTION = b0001, b0010, b0011, b1100, b1101, b1110, and b1111.
        ADD_BITFIELD_RW(EMITRANGE, 5, 1)
        // This bit is only available in comparator 1. When DATAVMATCH is set, this comparator performs data value compares. The comparators given by DATAVADDR0 and DATAVADDR1provide the address for the data comparison. If DATAVMATCH is set in DWT_FUNCTION1, the FUNCTION setting for the comparators given by DATAVADDR0 and DATAVADDR1 are overridden and those comparators only provide the address match for the data comparison.
        ADD_BITFIELD_RW(DATAVMATCH, 8, 1)
        ADD_BITFIELD_RO(LNK1ENA, 9, 1)
        // Defines the size of the data in the COMP register that is to be matched:
        ADD_BITFIELD_RW(DATAVSIZE, 10, 2)
        // Identity of a linked address comparator for data value matching when DATAVMATCH == 1.
        ADD_BITFIELD_RW(DATAVADDR0, 12, 4)
        // Identity of a second linked address comparator for data value matching when DATAVMATCH == 1 and LNK1ENA == 1.
        ADD_BITFIELD_RW(DATAVADDR1, 16, 4)
        // This bit is set when the comparator matches, and indicates that the operation defined by FUNCTION has occurred since this bit was last read. This bit is cleared on read.
        ADD_BITFIELD_RW(MATCHED, 24, 1)
    END_TYPE()

    // Disabled
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b0000 = 0;
    // EMITRANGE = 0, sample and emit PC through ITM. EMITRANGE = 1, emit address offset through ITM
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b0001 = 1;
    // EMITRANGE = 0, emit data through ITM on read and write. EMITRANGE = 1, emit data and address offset through ITM on read or write.
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b0010 = 2;
    // EMITRANGE = 0, sample PC and data value through ITM on read or write. EMITRANGE = 1, emit address offset and data value through ITM on read or write.
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b0011 = 3;
    // Watchpoint on PC match.
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b0100 = 4;
    // Watchpoint on read.
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b0101 = 5;
    // Watchpoint on write.
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b0110 = 6;
    // Watchpoint on read or write.
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b0111 = 7;
    // ETM trigger on PC match
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b1000 = 8;
    // ETM trigger on read
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b1001 = 9;
    // ETM trigger on write
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b1010 = 10;
    // ETM trigger on read or write
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b1011 = 11;
    // EMITRANGE = 0, sample data for read transfers. EMITRANGE = 1, sample Daddr [15:0] for read transfers
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b1100 = 12;
    // EMITRANGE = 0, sample data for write transfers. EMITRANGE = 1, sample Daddr [15:0] for write transfers
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b1101 = 13;
    // EMITRANGE = 0, sample PC + data for read transfers. EMITRANGE = 1, sample Daddr [15:0] + data for read transfers
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b1110 = 14;
    // EMITRANGE = 0, sample PC + data for write transfers. EMITRANGE = 1, sample Daddr [15:0] + data for write transfers
    static const uint32_t DWT_FUNCTION3_FUNCTION__en_0b1111 = 15;
    // DATAVADDR1 not supported
    static const uint32_t DWT_FUNCTION3_LNK1ENA__en_0b0 = 0;
    // DATAVADDR1 supported (enabled).
    static const uint32_t DWT_FUNCTION3_LNK1ENA__en_0b1 = 1;
    // byte
    static const uint32_t DWT_FUNCTION3_DATAVSIZE__en_0b00 = 0;
    // halfword
    static const uint32_t DWT_FUNCTION3_DATAVSIZE__en_0b01 = 1;
    // word
    static const uint32_t DWT_FUNCTION3_DATAVSIZE__en_0b10 = 2;
    // Unpredictable.
    static const uint32_t DWT_FUNCTION3_DATAVSIZE__en_0b11 = 3;

    struct DWT_t {
        DWT_CTRL_t                    DWT_CTRL;
        DWT_CYCCNT_t                  DWT_CYCCNT;
        DWT_CPICNT_t                  DWT_CPICNT;
        DWT_EXCCNT_t                  DWT_EXCCNT;
        DWT_SLEEPCNT_t                DWT_SLEEPCNT;
        DWT_LSUCNT_t                  DWT_LSUCNT;
        DWT_FOLDCNT_t                 DWT_FOLDCNT;
        DWT_PCSR_t                    DWT_PCSR;
        DWT_COMP0_t                   DWT_COMP0;
        DWT_MASK0_t                   DWT_MASK0;
        DWT_FUNCTION0_t               DWT_FUNCTION0;
        uint32_t                      reserved0;
        DWT_COMP1_t                   DWT_COMP1;
        DWT_MASK1_t                   DWT_MASK1;
        DWT_FUNCTION1_t               DWT_FUNCTION1;
        uint32_t                      reserved1;
        DWT_COMP2_t                   DWT_COMP2;
        DWT_MASK2_t                   DWT_MASK2;
        DWT_FUNCTION2_t               DWT_FUNCTION2;
        uint32_t                      reserved2;
        DWT_COMP3_t                   DWT_COMP3;
        DWT_MASK3_t                   DWT_MASK3;
        DWT_FUNCTION3_t               DWT_FUNCTION3;
    };

    static DWT_t & DWT     = (*(DWT_t *)0xe0001000);

} // _DWT_

// FPB
namespace _FPB_  {

    // Flash Patch Control Register
    // Reset value: 0x00000130
    BEGIN_TYPE(FP_CTRL_t, uint32_t)
        // Flash patch unit enable bit
        ADD_BITFIELD_RW(ENABLE, 0, 1)
        // Key field. To write to the Flash Patch Control Register, you must write a 1 to this write-only bit.
        ADD_BITFIELD_WO(KEY, 1, 1)
        // Number of code slots field.
        ADD_BITFIELD_RO(NUM_CODE1, 4, 4)
        // Number of literal slots field.
        ADD_BITFIELD_RO(NUM_LIT, 8, 4)
        // Number of full banks of code comparators, sixteen comparators per bank. Where less than sixteen code comparators are provided, the bank count is zero, and the number present indicated by NUM_CODE. This read only field contains 3'b000 to indicate 0 banks for Cortex-M4 processor.
        ADD_BITFIELD_RO(NUM_CODE2, 12, 2)
    END_TYPE()

    // flash patch unit disabled
    static const uint32_t FP_CTRL_ENABLE__en_0b0 = 0;
    // flash patch unit enabled
    static const uint32_t FP_CTRL_ENABLE__en_0b1 = 1;
    // no code slots
    static const uint32_t FP_CTRL_NUM_CODE1__en_0b0000 = 0;
    // two code slots
    static const uint32_t FP_CTRL_NUM_CODE1__en_0b0010 = 2;
    // six code slots
    static const uint32_t FP_CTRL_NUM_CODE1__en_0b0110 = 6;
    // no literal slots
    static const uint32_t FP_CTRL_NUM_LIT__en_0b0000 = 0;
    // two literal slots
    static const uint32_t FP_CTRL_NUM_LIT__en_0b0010 = 2;

    // Flash Patch Remap Register
    BEGIN_TYPE(FP_REMAP_t, uint32_t)
        // Remap base address field.
        ADD_BITFIELD_RW(REMAP, 5, 24)
    END_TYPE()

    // Flash Patch Comparator Registers
    // Reset value: 0x00000000
    BEGIN_TYPE(FP_COMP0_t, uint32_t)
        // Compare and remap enable for Flash Patch Comparator Register 0. The ENABLE bit of FP_CTRL must also be set to enable comparisons. Reset clears the ENABLE bit.
        ADD_BITFIELD_RW(ENABLE, 0, 1)
        // Comparison address.
        ADD_BITFIELD_RW(COMP, 2, 27)
        // This selects what happens when the COMP address is matched. Settings other than b00 are only valid for instruction comparators. Literal comparators ignore non-b00 settings. Address remapping only takes place for the b00 setting.
        ADD_BITFIELD_RW(REPLACE, 30, 2)
    END_TYPE()

    // Flash Patch Comparator Register 0 compare and remap disabled
    static const uint32_t FP_COMP0_ENABLE__en_0b0 = 0;
    // Flash Patch Comparator Register 0 compare and remap enabled
    static const uint32_t FP_COMP0_ENABLE__en_0b1 = 1;
    // remap to remap address. See FP_REMAP
    static const uint32_t FP_COMP0_REPLACE__en_0b00 = 0;
    // set BKPT on lower halfword, upper is unaffected
    static const uint32_t FP_COMP0_REPLACE__en_0b01 = 1;
    // set BKPT on upper halfword, lower is unaffected
    static const uint32_t FP_COMP0_REPLACE__en_0b10 = 2;
    // set BKPT on both lower and upper halfwords.
    static const uint32_t FP_COMP0_REPLACE__en_0b11 = 3;

    // Flash Patch Comparator Registers
    // Reset value: 0x00000000
    BEGIN_TYPE(FP_COMP1_t, uint32_t)
        // Compare and remap enable for Flash Patch Comparator Register 1. The ENABLE bit of FP_CTRL must also be set to enable comparisons. Reset clears the ENABLE bit.
        ADD_BITFIELD_RW(ENABLE, 0, 1)
        // Comparison address.
        ADD_BITFIELD_RW(COMP, 2, 27)
        // This selects what happens when the COMP address is matched. Settings other than b00 are only valid for instruction comparators. Literal comparators ignore non-b00 settings. Address remapping only takes place for the b00 setting.
        ADD_BITFIELD_RW(REPLACE, 30, 2)
    END_TYPE()

    // Flash Patch Comparator Register 1 compare and remap disabled
    static const uint32_t FP_COMP1_ENABLE__en_0b0 = 0;
    // Flash Patch Comparator Register 1 compare and remap enabled
    static const uint32_t FP_COMP1_ENABLE__en_0b1 = 1;
    // remap to remap address. See FP_REMAP
    static const uint32_t FP_COMP1_REPLACE__en_0b00 = 0;
    // set BKPT on lower halfword, upper is unaffected
    static const uint32_t FP_COMP1_REPLACE__en_0b01 = 1;
    // set BKPT on upper halfword, lower is unaffected
    static const uint32_t FP_COMP1_REPLACE__en_0b10 = 2;
    // set BKPT on both lower and upper halfwords.
    static const uint32_t FP_COMP1_REPLACE__en_0b11 = 3;

    // Flash Patch Comparator Registers
    // Reset value: 0x00000000
    BEGIN_TYPE(FP_COMP2_t, uint32_t)
        // Compare and remap enable for Flash Patch Comparator Register 2. The ENABLE bit of FP_CTRL must also be set to enable comparisons. Reset clears the ENABLE bit.
        ADD_BITFIELD_RW(ENABLE, 0, 1)
        // Comparison address.
        ADD_BITFIELD_RW(COMP, 2, 27)
        // This selects what happens when the COMP address is matched. Settings other than b00 are only valid for instruction comparators. Literal comparators ignore non-b00 settings. Address remapping only takes place for the b00 setting.
        ADD_BITFIELD_RW(REPLACE, 30, 2)
    END_TYPE()

    // Flash Patch Comparator Register 2 compare and remap disabled
    static const uint32_t FP_COMP2_ENABLE__en_0b0 = 0;
    // Flash Patch Comparator Register 2 compare and remap enabled
    static const uint32_t FP_COMP2_ENABLE__en_0b1 = 1;
    // remap to remap address. See FP_REMAP
    static const uint32_t FP_COMP2_REPLACE__en_0b00 = 0;
    // set BKPT on lower halfword, upper is unaffected
    static const uint32_t FP_COMP2_REPLACE__en_0b01 = 1;
    // set BKPT on upper halfword, lower is unaffected
    static const uint32_t FP_COMP2_REPLACE__en_0b10 = 2;
    // set BKPT on both lower and upper halfwords.
    static const uint32_t FP_COMP2_REPLACE__en_0b11 = 3;

    // Flash Patch Comparator Registers
    // Reset value: 0x00000000
    BEGIN_TYPE(FP_COMP3_t, uint32_t)
        // Compare and remap enable for Flash Patch Comparator Register 3. The ENABLE bit of FP_CTRL must also be set to enable comparisons. Reset clears the ENABLE bit.
        ADD_BITFIELD_RW(ENABLE, 0, 1)
        // Comparison address.
        ADD_BITFIELD_RW(COMP, 2, 27)
        // This selects what happens when the COMP address is matched. Settings other than b00 are only valid for instruction comparators. Literal comparators ignore non-b00 settings. Address remapping only takes place for the b00 setting.
        ADD_BITFIELD_RW(REPLACE, 30, 2)
    END_TYPE()

    // Flash Patch Comparator Register 3 compare and remap disabled
    static const uint32_t FP_COMP3_ENABLE__en_0b0 = 0;
    // Flash Patch Comparator Register 3 compare and remap enabled
    static const uint32_t FP_COMP3_ENABLE__en_0b1 = 1;
    // remap to remap address. See FP_REMAP
    static const uint32_t FP_COMP3_REPLACE__en_0b00 = 0;
    // set BKPT on lower halfword, upper is unaffected
    static const uint32_t FP_COMP3_REPLACE__en_0b01 = 1;
    // set BKPT on upper halfword, lower is unaffected
    static const uint32_t FP_COMP3_REPLACE__en_0b10 = 2;
    // set BKPT on both lower and upper halfwords.
    static const uint32_t FP_COMP3_REPLACE__en_0b11 = 3;

    // Flash Patch Comparator Registers
    // Reset value: 0x00000000
    BEGIN_TYPE(FP_COMP4_t, uint32_t)
        // Compare and remap enable for Flash Patch Comparator Register 4. The ENABLE bit of FP_CTRL must also be set to enable comparisons. Reset clears the ENABLE bit.
        ADD_BITFIELD_RW(ENABLE, 0, 1)
        // Comparison address.
        ADD_BITFIELD_RW(COMP, 2, 27)
        // This selects what happens when the COMP address is matched. Settings other than b00 are only valid for instruction comparators. Literal comparators ignore non-b00 settings. Address remapping only takes place for the b00 setting.
        ADD_BITFIELD_RW(REPLACE, 30, 2)
    END_TYPE()

    // Flash Patch Comparator Register 4 compare and remap disabled
    static const uint32_t FP_COMP4_ENABLE__en_0b0 = 0;
    // Flash Patch Comparator Register 4 compare and remap enabled
    static const uint32_t FP_COMP4_ENABLE__en_0b1 = 1;
    // remap to remap address. See FP_REMAP
    static const uint32_t FP_COMP4_REPLACE__en_0b00 = 0;
    // set BKPT on lower halfword, upper is unaffected
    static const uint32_t FP_COMP4_REPLACE__en_0b01 = 1;
    // set BKPT on upper halfword, lower is unaffected
    static const uint32_t FP_COMP4_REPLACE__en_0b10 = 2;
    // set BKPT on both lower and upper halfwords.
    static const uint32_t FP_COMP4_REPLACE__en_0b11 = 3;

    // Flash Patch Comparator Registers
    // Reset value: 0x00000000
    BEGIN_TYPE(FP_COMP5_t, uint32_t)
        // Compare and remap enable for Flash Patch Comparator Register 5. The ENABLE bit of FP_CTRL must also be set to enable comparisons. Reset clears the ENABLE bit.
        ADD_BITFIELD_RW(ENABLE, 0, 1)
        // Comparison address.
        ADD_BITFIELD_RW(COMP, 2, 27)
        // This selects what happens when the COMP address is matched. Settings other than b00 are only valid for instruction comparators. Literal comparators ignore non-b00 settings. Address remapping only takes place for the b00 setting.
        ADD_BITFIELD_RW(REPLACE, 30, 2)
    END_TYPE()

    // Flash Patch Comparator Register 5 compare and remap disabled
    static const uint32_t FP_COMP5_ENABLE__en_0b0 = 0;
    // Flash Patch Comparator Register 5 compare and remap enabled
    static const uint32_t FP_COMP5_ENABLE__en_0b1 = 1;
    // remap to remap address. See FP_REMAP
    static const uint32_t FP_COMP5_REPLACE__en_0b00 = 0;
    // set BKPT on lower halfword, upper is unaffected
    static const uint32_t FP_COMP5_REPLACE__en_0b01 = 1;
    // set BKPT on upper halfword, lower is unaffected
    static const uint32_t FP_COMP5_REPLACE__en_0b10 = 2;
    // set BKPT on both lower and upper halfwords.
    static const uint32_t FP_COMP5_REPLACE__en_0b11 = 3;

    // Flash Patch Comparator Registers
    // Reset value: 0x00000000
    BEGIN_TYPE(FP_COMP6_t, uint32_t)
        // Compare and remap enable for Flash Patch Comparator Register 6. The ENABLE bit of FP_CTRL must also be set to enable comparisons. Reset clears the ENABLE bit.
        ADD_BITFIELD_RW(ENABLE, 0, 1)
        // Comparison address.
        ADD_BITFIELD_RW(COMP, 2, 27)
        // This selects what happens when the COMP address is matched. Settings other than b00 are only valid for instruction comparators. Literal comparators ignore non-b00 settings. Address remapping only takes place for the b00 setting.
        ADD_BITFIELD_RW(REPLACE, 30, 2)
    END_TYPE()

    // Flash Patch Comparator Register 6 compare and remap disabled
    static const uint32_t FP_COMP6_ENABLE__en_0b0 = 0;
    // Flash Patch Comparator Register 6 compare and remap enabled
    static const uint32_t FP_COMP6_ENABLE__en_0b1 = 1;
    // remap to remap address. See FP_REMAP
    static const uint32_t FP_COMP6_REPLACE__en_0b00 = 0;
    // set BKPT on lower halfword, upper is unaffected
    static const uint32_t FP_COMP6_REPLACE__en_0b01 = 1;
    // set BKPT on upper halfword, lower is unaffected
    static const uint32_t FP_COMP6_REPLACE__en_0b10 = 2;
    // set BKPT on both lower and upper halfwords.
    static const uint32_t FP_COMP6_REPLACE__en_0b11 = 3;

    // Flash Patch Comparator Registers
    // Reset value: 0x00000000
    BEGIN_TYPE(FP_COMP7_t, uint32_t)
        // Compare and remap enable for Flash Patch Comparator Register 7. The ENABLE bit of FP_CTRL must also be set to enable comparisons. Reset clears the ENABLE bit.
        ADD_BITFIELD_RW(ENABLE, 0, 1)
        // Comparison address.
        ADD_BITFIELD_RW(COMP, 2, 27)
        // This selects what happens when the COMP address is matched. Settings other than b00 are only valid for instruction comparators. Literal comparators ignore non-b00 settings. Address remapping only takes place for the b00 setting.
        ADD_BITFIELD_RW(REPLACE, 30, 2)
    END_TYPE()

    // Flash Patch Comparator Register 7 compare and remap disabled
    static const uint32_t FP_COMP7_ENABLE__en_0b0 = 0;
    // Flash Patch Comparator Register 7 compare and remap enabled
    static const uint32_t FP_COMP7_ENABLE__en_0b1 = 1;
    // remap to remap address. See FP_REMAP
    static const uint32_t FP_COMP7_REPLACE__en_0b00 = 0;
    // set BKPT on lower halfword, upper is unaffected
    static const uint32_t FP_COMP7_REPLACE__en_0b01 = 1;
    // set BKPT on upper halfword, lower is unaffected
    static const uint32_t FP_COMP7_REPLACE__en_0b10 = 2;
    // set BKPT on both lower and upper halfwords.
    static const uint32_t FP_COMP7_REPLACE__en_0b11 = 3;

    struct FPB_t {
        FP_CTRL_t                     FP_CTRL;
        FP_REMAP_t                    FP_REMAP;
        FP_COMP0_t                    FP_COMP0;
        FP_COMP1_t                    FP_COMP1;
        FP_COMP2_t                    FP_COMP2;
        FP_COMP3_t                    FP_COMP3;
        FP_COMP4_t                    FP_COMP4;
        FP_COMP5_t                    FP_COMP5;
        FP_COMP6_t                    FP_COMP6;
        FP_COMP7_t                    FP_COMP7;
    };

    static FPB_t & FPB     = (*(FPB_t *)0xe0002000);

} // _FPB_

// System Control Space for ARM core: SCnSCB, SCB, SysTick, NVIC, CoreDebug, MPU, FPU
namespace _SystemControlSpace_  {

    // Interrupt Control Type Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ICTR_t, uint32_t)
        // Total number of interrupt lines in groups of 32.
        ADD_BITFIELD_RO(INTLINESNUM, 0, 5)
    END_TYPE()

    // Auxiliary Control Register
    // Reset value: 0x00000000
    BEGIN_TYPE(ACTLR_t, uint32_t)
        // Disables interruption of multi-cycle instructions. This increases the interrupt latency of the processor becuase LDM/STM completes before interrupt stacking occurs.
        ADD_BITFIELD_RW(DISMCYCINT, 0, 1)
        // Disables write buffer us during default memorty map accesses. This causes all bus faults to be precise bus faults but decreases the performance of the processor because the stores to memory have to complete before the next instruction can be executed.
        ADD_BITFIELD_RW(DISDEFWBUF, 1, 1)
        // Disables IT folding.
        ADD_BITFIELD_RW(DISFOLD, 2, 1)
        // Disable automatic update of CONTROL.FPCA
        ADD_BITFIELD_RW(DISFPCA, 8, 1)
        // Disables floating point instructions completing out of order with respect to integer instructions.
        ADD_BITFIELD_RW(DISOOFP, 9, 1)
    END_TYPE()

    struct SystemControlSpace_t {
        uint32_t                      reserved0;
        ICTR_t                        ICTR;
        ACTLR_t                       ACTLR;
    };

    static SystemControlSpace_t & SystemControlSpace     = (*(SystemControlSpace_t *)0xe000e000);

} // _SystemControlSpace_

// RSTCTL
namespace _RSTCTL_  {

    // Reset Request Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_RESET_REQ_t, uint32_t)
        // Soft Reset request
        ADD_BITFIELD_WO(SOFT_REQ, 0, 1)
        // Hard Reset request
        ADD_BITFIELD_WO(HARD_REQ, 1, 1)
        // Write key to unlock reset request bits
        ADD_BITFIELD_WO(RSTKEY, 8, 8)
    END_TYPE()

    // Hard Reset Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_HARDRESET_STAT_t, uint32_t)
        // Indicates that SRC0 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC0, 0, 1)
        // Indicates that SRC1 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC1, 1, 1)
        // Indicates that SRC2 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC2, 2, 1)
        // Indicates that SRC3 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC3, 3, 1)
        // Indicates that SRC4 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC4, 4, 1)
        // Indicates that SRC5 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC5, 5, 1)
        // Indicates that SRC6 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC6, 6, 1)
        // Indicates that SRC7 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC7, 7, 1)
        // Indicates that SRC8 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC8, 8, 1)
        // Indicates that SRC9 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC9, 9, 1)
        // Indicates that SRC10 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC10, 10, 1)
        // Indicates that SRC11 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC11, 11, 1)
        // Indicates that SRC12 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC12, 12, 1)
        // Indicates that SRC13 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC13, 13, 1)
        // Indicates that SRC14 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC14, 14, 1)
        // Indicates that SRC15 was the source of the Hard Reset
        ADD_BITFIELD_RO(SRC15, 15, 1)
    END_TYPE()

    // Hard Reset Status Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_HARDRESET_CLR_t, uint32_t)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC0, 0, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC1, 1, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC2, 2, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC3, 3, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC4, 4, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC5, 5, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC6, 6, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC7, 7, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC8, 8, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC9, 9, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC10, 10, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC11, 11, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC12, 12, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC13, 13, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HARDRESET_STAT
        ADD_BITFIELD_WO(SRC14, 14, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_HRDRESETSTAT_REG
        ADD_BITFIELD_WO(SRC15, 15, 1)
    END_TYPE()

    // Hard Reset Status Set Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_HARDRESET_SET_t, uint32_t)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC0, 0, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC1, 1, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC2, 2, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC3, 3, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC4, 4, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC5, 5, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC6, 6, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC7, 7, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC8, 8, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC9, 9, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC10, 10, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC11, 11, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC12, 12, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC13, 13, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC14, 14, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_HARDRESET_STAT (and initiates a Hard Reset)
        ADD_BITFIELD_WO(SRC15, 15, 1)
    END_TYPE()

    // Soft Reset Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_SOFTRESET_STAT_t, uint32_t)
        // If 1, indicates that SRC0 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC0, 0, 1)
        // If 1, indicates that SRC1 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC1, 1, 1)
        // If 1, indicates that SRC2 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC2, 2, 1)
        // If 1, indicates that SRC3 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC3, 3, 1)
        // If 1, indicates that SRC4 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC4, 4, 1)
        // If 1, indicates that SRC5 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC5, 5, 1)
        // If 1, indicates that SRC6 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC6, 6, 1)
        // If 1, indicates that SRC7 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC7, 7, 1)
        // If 1, indicates that SRC8 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC8, 8, 1)
        // If 1, indicates that SRC9 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC9, 9, 1)
        // If 1, indicates that SRC10 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC10, 10, 1)
        // If 1, indicates that SRC11 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC11, 11, 1)
        // If 1, indicates that SRC12 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC12, 12, 1)
        // If 1, indicates that SRC13 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC13, 13, 1)
        // If 1, indicates that SRC14 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC14, 14, 1)
        // If 1, indicates that SRC15 was the source of the Soft Reset
        ADD_BITFIELD_RO(SRC15, 15, 1)
    END_TYPE()

    // Soft Reset Status Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_SOFTRESET_CLR_t, uint32_t)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC0, 0, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC1, 1, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC2, 2, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC3, 3, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC4, 4, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC5, 5, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC6, 6, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC7, 7, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC8, 8, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC9, 9, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC10, 10, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC11, 11, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC12, 12, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC13, 13, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC14, 14, 1)
        // Write 1 clears the corresponding bit in the RSTCTL_SOFTRESET_STAT
        ADD_BITFIELD_WO(SRC15, 15, 1)
    END_TYPE()

    // Soft Reset Status Set Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_SOFTRESET_SET_t, uint32_t)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC0, 0, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC1, 1, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC2, 2, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC3, 3, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC4, 4, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC5, 5, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC6, 6, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC7, 7, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC8, 8, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC9, 9, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC10, 10, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC11, 11, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC12, 12, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC13, 13, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC14, 14, 1)
        // Write 1 sets the corresponding bit in the RSTCTL_SOFTRESET_STAT (and initiates a Soft Reset)
        ADD_BITFIELD_WO(SRC15, 15, 1)
    END_TYPE()

    // PSS Reset Status Register
    // Reset value: 0x0000000f
    BEGIN_TYPE(RSTCTL_PSSRESET_STAT_t, uint32_t)
        // Indicates if POR was caused by an SVSMH trip condition int the PSS
        ADD_BITFIELD_RO(SVSMH, 1, 1)
        // Indicates if POR was caused by a BGREF not okay condition in the PSS
        ADD_BITFIELD_RO(BGREF, 2, 1)
        // Indicates if POR was caused by a VCCDET trip condition in the PSS
        ADD_BITFIELD_RO(VCCDET, 3, 1)
        // Indicates if POR was caused by an SVSL trip condition in the PSS
        ADD_BITFIELD_RO(SVSL, 0, 1)
    END_TYPE()

    // PSS Reset Status Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_PSSRESET_CLR_t, uint32_t)
        // Write 1 clears all PSS Reset Flags in the RSTCTL_PSSRESET_STAT
        ADD_BITFIELD_WO(CLR, 0, 1)
    END_TYPE()

    // PCM Reset Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_PCMRESET_STAT_t, uint32_t)
        // Indicates if POR was caused by PCM due to an exit from LPM3.5
        ADD_BITFIELD_RO(LPM35, 0, 1)
        // Indicates if POR was caused by PCM due to an exit from LPM4.5
        ADD_BITFIELD_RO(LPM45, 1, 1)
    END_TYPE()

    // PCM Reset Status Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_PCMRESET_CLR_t, uint32_t)
        // Write 1 clears all PCM Reset Flags in the RSTCTL_PCMRESET_STAT
        ADD_BITFIELD_WO(CLR, 0, 1)
    END_TYPE()

    // Pin Reset Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_PINRESET_STAT_t, uint32_t)
        // POR was caused by RSTn/NMI pin based reset event
        ADD_BITFIELD_RO(RSTNMI, 0, 1)
    END_TYPE()

    // Pin Reset Status Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_PINRESET_CLR_t, uint32_t)
        // Write 1 clears the RSTn/NMI Pin Reset Flag in RSTCTL_PINRESET_STAT
        ADD_BITFIELD_WO(CLR, 0, 1)
    END_TYPE()

    // Reboot Reset Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_REBOOTRESET_STAT_t, uint32_t)
        // Indicates if Reboot reset was caused by the SYSCTL module.
        ADD_BITFIELD_RO(REBOOT, 0, 1)
    END_TYPE()

    // Reboot Reset Status Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_REBOOTRESET_CLR_t, uint32_t)
        // Write 1 clears the Reboot Reset Flag in RSTCTL_REBOOTRESET_STAT
        ADD_BITFIELD_WO(CLR, 0, 1)
    END_TYPE()

    // CS Reset Status Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_CSRESET_STAT_t, uint32_t)
        // Indicates if POR was caused by DCO short circuit fault in the external resistor mode
        ADD_BITFIELD_RO(DCOR_SHT, 0, 1)
    END_TYPE()

    // CS Reset Status Clear Register
    // Reset value: 0x00000000
    BEGIN_TYPE(RSTCTL_CSRESET_CLR_t, uint32_t)
        // Write 1 clears the DCOR_SHT Flag in RSTCTL_CSRESET_STAT as well as DCOR_SHTIFG flag in CSIFG register of clock system
        ADD_BITFIELD_WO(CLR, 0, 1)
    END_TYPE()

    struct RSTCTL_t {
        RSTCTL_RESET_REQ_t            RSTCTL_RESET_REQ;
        RSTCTL_HARDRESET_STAT_t       RSTCTL_HARDRESET_STAT;
        RSTCTL_HARDRESET_CLR_t        RSTCTL_HARDRESET_CLR;
        RSTCTL_HARDRESET_SET_t        RSTCTL_HARDRESET_SET;
        RSTCTL_SOFTRESET_STAT_t       RSTCTL_SOFTRESET_STAT;
        RSTCTL_SOFTRESET_CLR_t        RSTCTL_SOFTRESET_CLR;
        RSTCTL_SOFTRESET_SET_t        RSTCTL_SOFTRESET_SET;
        uint32_t                      reserved0[57];
        RSTCTL_PSSRESET_STAT_t        RSTCTL_PSSRESET_STAT;
        RSTCTL_PSSRESET_CLR_t         RSTCTL_PSSRESET_CLR;
        RSTCTL_PCMRESET_STAT_t        RSTCTL_PCMRESET_STAT;
        RSTCTL_PCMRESET_CLR_t         RSTCTL_PCMRESET_CLR;
        RSTCTL_PINRESET_STAT_t        RSTCTL_PINRESET_STAT;
        RSTCTL_PINRESET_CLR_t         RSTCTL_PINRESET_CLR;
        RSTCTL_REBOOTRESET_STAT_t     RSTCTL_REBOOTRESET_STAT;
        RSTCTL_REBOOTRESET_CLR_t      RSTCTL_REBOOTRESET_CLR;
        RSTCTL_CSRESET_STAT_t         RSTCTL_CSRESET_STAT;
        RSTCTL_CSRESET_CLR_t          RSTCTL_CSRESET_CLR;
    };

    static RSTCTL_t & RSTCTL     = (*(RSTCTL_t *)0xe0042000);

} // _RSTCTL_

// SYSCTL
namespace _SYSCTL_  {

    // Reboot Control Register
    // Reset value: 0x000000fe
    BEGIN_TYPE(SYS_REBOOT_CTL_t, uint32_t)
        // Write 1 initiates a Reboot of the device
        ADD_BITFIELD_RW(REBOOT, 0, 1)
        // Key to enable writes to bit 0
        ADD_BITFIELD_WO(WKEY, 8, 8)
    END_TYPE()

    // NMI Control and Status Register
    // Reset value: 0x00000007
    BEGIN_TYPE(SYS_NMI_CTLSTAT_t, uint32_t)
        // CS interrupt as a source of NMI
        ADD_BITFIELD_RW(CS_SRC, 0, 1)
        // PSS interrupt as a source of NMI
        ADD_BITFIELD_RW(PSS_SRC, 1, 1)
        // PCM interrupt as a source of NMI
        ADD_BITFIELD_RW(PCM_SRC, 2, 1)
        // RSTn/NMI pin configuration Note: When the device enters LPM3/LPM4 modes of operation, the functionality selected by this bit is retained. If selected as an NMI, activity on this pin in  LPM3/LPM4 wakes the device and processes the interrupt, without causing a POR. If selected as a Reset, activity on this pin in LPM3/LPM4 causes a device-level POR When the device enters LPM3.5/LPM4.5 modes of operation, this bit is always cleared to 0. In other words, the RSTn/NMI pin always assumes a reset functionality in LPM3.5/LPM4.5 modes.
        ADD_BITFIELD_RW(PIN_SRC, 3, 1)
        // CS interrupt was the source of NMI
        ADD_BITFIELD_RO(CS_FLG, 16, 1)
        // PSS interrupt was the source of NMI
        ADD_BITFIELD_RO(PSS_FLG, 17, 1)
        // PCM interrupt was the source of NMI
        ADD_BITFIELD_RO(PCM_FLG, 18, 1)
        // RSTn/NMI pin was the source of NMI
        ADD_BITFIELD_RW(PIN_FLG, 19, 1)
    END_TYPE()

    // Disables CS interrupt as a source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_CS_SRC__CS_SRC_0 = 0;
    // Enables CS interrupt as a source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_CS_SRC__CS_SRC_1 = 1;
    // Disables the PSS interrupt as a source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_PSS_SRC__PSS_SRC_0 = 0;
    // Enables the PSS interrupt as a source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_PSS_SRC__PSS_SRC_1 = 1;
    // Disbles the PCM interrupt as a source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_PCM_SRC__PCM_SRC_0 = 0;
    // Enables the PCM interrupt as a source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_PCM_SRC__PCM_SRC_1 = 1;
    // Configures the RSTn_NMI pin as a source of POR Class Reset
    static const uint32_t SYS_NMI_CTLSTAT_PIN_SRC__PIN_SRC_0 = 0;
    // Configures the RSTn_NMI pin as a source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_PIN_SRC__PIN_SRC_1 = 1;
    // indicates CS interrupt was not the source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_CS_FLG__CS_FLG_0 = 0;
    // indicates CS interrupt was the source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_CS_FLG__CS_FLG_1 = 1;
    // indicates the PSS interrupt was not the source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_PSS_FLG__PSS_FLG_0 = 0;
    // indicates the PSS interrupt was the source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_PSS_FLG__PSS_FLG_1 = 1;
    // indicates the PCM interrupt was not the source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_PCM_FLG__PCM_FLG_0 = 0;
    // indicates the PCM interrupt was the source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_PCM_FLG__PCM_FLG_1 = 1;
    // Indicates the RSTn_NMI pin was not the source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_PIN_FLG__PIN_FLG_0 = 0;
    // Indicates the RSTn_NMI pin was the source of NMI
    static const uint32_t SYS_NMI_CTLSTAT_PIN_FLG__PIN_FLG_1 = 1;

    // Watchdog Reset Control Register
    // Reset value: 0x00000003
    BEGIN_TYPE(SYS_WDTRESET_CTL_t, uint32_t)
        // WDT timeout reset type
        ADD_BITFIELD_RW(TIMEOUT, 0, 1)
        // WDT password violation reset type
        ADD_BITFIELD_RW(VIOLATION, 1, 1)
    END_TYPE()

    // WDT timeout event generates Soft reset
    static const uint32_t SYS_WDTRESET_CTL_TIMEOUT__TIMEOUT_0 = 0;
    // WDT timeout event generates Hard reset
    static const uint32_t SYS_WDTRESET_CTL_TIMEOUT__TIMEOUT_1 = 1;
    // WDT password violation event generates Soft reset
    static const uint32_t SYS_WDTRESET_CTL_VIOLATION__VIOLATION_0 = 0;
    // WDT password violation event generates Hard reset
    static const uint32_t SYS_WDTRESET_CTL_VIOLATION__VIOLATION_1 = 1;

    // Peripheral Halt Control Register
    // Reset value: 0x00004000
    BEGIN_TYPE(SYS_PERIHALT_CTL_t, uint32_t)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_T16_0, 0, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_T16_1, 1, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_T16_2, 2, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_T16_3, 3, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_T32_0, 4, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_eUA0, 5, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_eUA1, 6, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_eUA2, 7, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_eUA3, 8, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_eUB0, 9, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_eUB1, 10, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_eUB2, 11, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_eUB3, 12, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_ADC, 13, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_WDT, 14, 1)
        // Freezes IP operation when CPU is halted
        ADD_BITFIELD_RW(HALT_DMA, 15, 1)
    END_TYPE()

    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_T16_0__HALT_T16_0_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_T16_0__HALT_T16_0_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_T16_1__HALT_T16_1_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_T16_1__HALT_T16_1_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_T16_2__HALT_T16_2_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_T16_2__HALT_T16_2_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_T16_3__HALT_T16_3_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_T16_3__HALT_T16_3_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_T32_0__HALT_T32_0_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_T32_0__HALT_T32_0_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUA0__HALT_eUA0_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUA0__HALT_eUA0_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUA1__HALT_eUA1_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUA1__HALT_eUA1_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUA2__HALT_eUA2_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUA2__HALT_eUA2_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUA3__HALT_eUA3_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUA3__HALT_eUA3_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUB0__HALT_eUB0_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUB0__HALT_eUB0_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUB1__HALT_eUB1_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUB1__HALT_eUB1_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUB2__HALT_eUB2_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUB2__HALT_eUB2_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUB3__HALT_eUB3_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_eUB3__HALT_eUB3_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_ADC__HALT_ADC_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_ADC__HALT_ADC_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_WDT__HALT_WDT_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_WDT__HALT_WDT_1 = 1;
    // IP operation unaffected when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_DMA__HALT_DMA_0 = 0;
    // freezes IP operation when CPU is halted
    static const uint32_t SYS_PERIHALT_CTL_HALT_DMA__HALT_DMA_1 = 1;

    // SRAM Size Register
    BEGIN_TYPE(SYS_SRAM_SIZE_t, uint32_t)
        // Indicates the size of SRAM on the device
        ADD_BITFIELD_RO(SIZE, 0, 32)
    END_TYPE()

    // SRAM Bank Enable Register
    // Reset value: 0x000000ff
    BEGIN_TYPE(SYS_SRAM_BANKEN_t, uint32_t)
        // SRAM Bank0 enable
        ADD_BITFIELD_RO(BNK0_EN, 0, 1)
        // SRAM Bank1 enable
        ADD_BITFIELD_RW(BNK1_EN, 1, 1)
        // SRAM Bank1 enable
        ADD_BITFIELD_RW(BNK2_EN, 2, 1)
        // SRAM Bank1 enable
        ADD_BITFIELD_RW(BNK3_EN, 3, 1)
        // SRAM Bank1 enable
        ADD_BITFIELD_RW(BNK4_EN, 4, 1)
        // SRAM Bank1 enable
        ADD_BITFIELD_RW(BNK5_EN, 5, 1)
        // SRAM Bank1 enable
        ADD_BITFIELD_RW(BNK6_EN, 6, 1)
        // SRAM Bank1 enable
        ADD_BITFIELD_RW(BNK7_EN, 7, 1)
        // SRAM ready
        ADD_BITFIELD_RO(SRAM_RDY, 16, 1)
    END_TYPE()

    // Disables Bank1 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK1_EN__BNK1_EN_0 = 0;
    // Enables Bank1 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK1_EN__BNK1_EN_1 = 1;
    // Disables Bank2 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK2_EN__BNK2_EN_0 = 0;
    // Enables Bank2 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK2_EN__BNK2_EN_1 = 1;
    // Disables Bank3 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK3_EN__BNK3_EN_0 = 0;
    // Enables Bank3 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK3_EN__BNK3_EN_1 = 1;
    // Disables Bank4 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK4_EN__BNK4_EN_0 = 0;
    // Enables Bank4 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK4_EN__BNK4_EN_1 = 1;
    // Disables Bank5 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK5_EN__BNK5_EN_0 = 0;
    // Enables Bank5 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK5_EN__BNK5_EN_1 = 1;
    // Disables Bank6 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK6_EN__BNK6_EN_0 = 0;
    // Enables Bank6 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK6_EN__BNK6_EN_1 = 1;
    // Disables Bank7 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK7_EN__BNK7_EN_0 = 0;
    // Enables Bank7 of the SRAM
    static const uint32_t SYS_SRAM_BANKEN_BNK7_EN__BNK7_EN_1 = 1;
    // SRAM is not ready for accesses. Banks are undergoing an enable or disable sequence, and reads or writes to SRAM are stalled until the banks are ready
    static const uint32_t SYS_SRAM_BANKEN_SRAM_RDY__SRAM_RDY_0 = 0;
    // SRAM is ready for accesses. All SRAM banks are enabled/disabled according to values of bits 7:0 of this register
    static const uint32_t SYS_SRAM_BANKEN_SRAM_RDY__SRAM_RDY_1 = 1;

    // SRAM Bank Retention Control Register
    // Reset value: 0x000000ff
    BEGIN_TYPE(SYS_SRAM_BANKRET_t, uint32_t)
        // Bank0 retention
        ADD_BITFIELD_RO(BNK0_RET, 0, 1)
        // Bank1 retention
        ADD_BITFIELD_RW(BNK1_RET, 1, 1)
        // Bank2 retention
        ADD_BITFIELD_RW(BNK2_RET, 2, 1)
        // Bank3 retention
        ADD_BITFIELD_RW(BNK3_RET, 3, 1)
        // Bank4 retention
        ADD_BITFIELD_RW(BNK4_RET, 4, 1)
        // Bank5 retention
        ADD_BITFIELD_RW(BNK5_RET, 5, 1)
        // Bank6 retention
        ADD_BITFIELD_RW(BNK6_RET, 6, 1)
        // Bank7 retention
        ADD_BITFIELD_RW(BNK7_RET, 7, 1)
        // SRAM ready
        ADD_BITFIELD_RO(SRAM_RDY, 16, 1)
    END_TYPE()

    // Bank1 of the SRAM is not retained in LPM3 or LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK1_RET__BNK1_RET_0 = 0;
    // Bank1 of the SRAM is retained in LPM3 and LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK1_RET__BNK1_RET_1 = 1;
    // Bank2 of the SRAM is not retained in LPM3 or LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK2_RET__BNK2_RET_0 = 0;
    // Bank2 of the SRAM is retained in LPM3 and LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK2_RET__BNK2_RET_1 = 1;
    // Bank3 of the SRAM is not retained in LPM3 or LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK3_RET__BNK3_RET_0 = 0;
    // Bank3 of the SRAM is retained in LPM3 and LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK3_RET__BNK3_RET_1 = 1;
    // Bank4 of the SRAM is not retained in LPM3 or LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK4_RET__BNK4_RET_0 = 0;
    // Bank4 of the SRAM is retained in LPM3 and LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK4_RET__BNK4_RET_1 = 1;
    // Bank5 of the SRAM is not retained in LPM3 or LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK5_RET__BNK5_RET_0 = 0;
    // Bank5 of the SRAM is retained in LPM3 and LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK5_RET__BNK5_RET_1 = 1;
    // Bank6 of the SRAM is not retained in LPM3 or LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK6_RET__BNK6_RET_0 = 0;
    // Bank6 of the SRAM is retained in LPM3 and LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK6_RET__BNK6_RET_1 = 1;
    // Bank7 of the SRAM is not retained in LPM3 or LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK7_RET__BNK7_RET_0 = 0;
    // Bank7 of the SRAM is retained in LPM3 and LPM4
    static const uint32_t SYS_SRAM_BANKRET_BNK7_RET__BNK7_RET_1 = 1;
    // SRAM banks are being set up for retention. Entry into LPM3, LPM4 should not be attempted until this bit is set to 1
    static const uint32_t SYS_SRAM_BANKRET_SRAM_RDY__SRAM_RDY_0 = 0;
    // SRAM is ready for accesses. All SRAM banks are enabled/disabled for retention according to values of bits 7:0 of this register
    static const uint32_t SYS_SRAM_BANKRET_SRAM_RDY__SRAM_RDY_1 = 1;

    // Flash Size Register
    BEGIN_TYPE(SYS_FLASH_SIZE_t, uint32_t)
        // Flash User Region size
        ADD_BITFIELD_RO(SIZE, 0, 32)
    END_TYPE()

    // Digital I/O Glitch Filter Control Register
    // Reset value: 0x00000001
    BEGIN_TYPE(SYS_DIO_GLTFLT_CTL_t, uint32_t)
        // Glitch filter enable
        ADD_BITFIELD_RW(GLTCH_EN, 0, 1)
    END_TYPE()

    // Disables glitch filter on the digital I/Os
    static const uint32_t SYS_DIO_GLTFLT_CTL_GLTCH_EN__GLTCH_EN_0 = 0;
    // Enables glitch filter on the digital I/Os
    static const uint32_t SYS_DIO_GLTFLT_CTL_GLTCH_EN__GLTCH_EN_1 = 1;

    // IP Protected Secure Zone Data Access Unlock Register
    // Reset value: 0x00000000
    BEGIN_TYPE(SYS_SECDATA_UNLOCK_t, uint32_t)
        // Unlock key
        ADD_BITFIELD_RW(UNLKEY, 0, 16)
    END_TYPE()

    // Master Unlock Register
    // Reset value: 0x00000000
    BEGIN_TYPE(SYS_MASTER_UNLOCK_t, uint32_t)
        // Unlock Key
        ADD_BITFIELD_RW(UNLKEY, 0, 16)
    END_TYPE()

    // Boot Override Request Register
    // Reset value: 0x00000000
    BEGIN_TYPE(SYS_BOOTOVER_REQ_t, uint32_t)
        // Value set by debugger, read and clear by the CPU
        ADD_BITFIELD_RW(REGVAL, 0, 32)
    END_TYPE()

    // Boot Override Acknowledge Register
    // Reset value: 0x00000000
    BEGIN_TYPE(SYS_BOOTOVER_ACK_t, uint32_t)
        // Value set by CPU, read/clear by the debugger
        ADD_BITFIELD_RW(REGVAL, 0, 32)
    END_TYPE()

    // Reset Request Register
    BEGIN_TYPE(SYS_RESET_REQ_t, uint32_t)
        // Generate POR
        ADD_BITFIELD_WO(POR, 0, 1)
        // Generate Reboot_Reset
        ADD_BITFIELD_WO(REBOOT, 1, 1)
        // Write key
        ADD_BITFIELD_WO(WKEY, 8, 8)
    END_TYPE()

    // Reset Status and Override Register
    // Reset value: 0x00000000
    BEGIN_TYPE(SYS_RESET_STATOVER_t, uint32_t)
        // Indicates if SOFT Reset is active
        ADD_BITFIELD_RO(SOFT, 0, 1)
        // Indicates if HARD Reset is active
        ADD_BITFIELD_RO(HARD, 1, 1)
        // Indicates if Reboot Reset is active
        ADD_BITFIELD_RO(REBOOT, 2, 1)
        // SOFT_Reset overwrite request
        ADD_BITFIELD_RW(SOFT_OVER, 8, 1)
        // HARD_Reset overwrite request
        ADD_BITFIELD_RW(HARD_OVER, 9, 1)
        // Reboot Reset overwrite request
        ADD_BITFIELD_RW(RBT_OVER, 10, 1)
    END_TYPE()

    // System Status Register
    BEGIN_TYPE(SYS_SYSTEM_STAT_t, uint32_t)
        // Debug Security active
        ADD_BITFIELD_RO(DBG_SEC_ACT, 3, 1)
        // Indicates if JTAG and SWD Lock is active
        ADD_BITFIELD_RO(JTAG_SWD_LOCK_ACT, 4, 1)
        // Indicates if IP protection is active
        ADD_BITFIELD_RO(IP_PROT_ACT, 5, 1)
    END_TYPE()

    struct SYSCTL_t {
        SYS_REBOOT_CTL_t              SYS_REBOOT_CTL;
        SYS_NMI_CTLSTAT_t             SYS_NMI_CTLSTAT;
        SYS_WDTRESET_CTL_t            SYS_WDTRESET_CTL;
        SYS_PERIHALT_CTL_t            SYS_PERIHALT_CTL;
        SYS_SRAM_SIZE_t               SYS_SRAM_SIZE;
        SYS_SRAM_BANKEN_t             SYS_SRAM_BANKEN;
        SYS_SRAM_BANKRET_t            SYS_SRAM_BANKRET;
        uint32_t                      reserved0;
        SYS_FLASH_SIZE_t              SYS_FLASH_SIZE;
        uint32_t                      reserved1[3];
        SYS_DIO_GLTFLT_CTL_t          SYS_DIO_GLTFLT_CTL;
        uint32_t                      reserved2[3];
        SYS_SECDATA_UNLOCK_t          SYS_SECDATA_UNLOCK;
        uint32_t                      reserved3[1007];
        SYS_MASTER_UNLOCK_t           SYS_MASTER_UNLOCK;
        SYS_BOOTOVER_REQ_t            SYS_BOOTOVER_REQ0;
        SYS_BOOTOVER_REQ_t            SYS_BOOTOVER_REQ1;
        SYS_BOOTOVER_ACK_t            SYS_BOOTOVER_ACK;
        SYS_RESET_REQ_t               SYS_RESET_REQ;
        SYS_RESET_STATOVER_t          SYS_RESET_STATOVER;
        uint32_t                      reserved4[2];
        SYS_SYSTEM_STAT_t             SYS_SYSTEM_STAT;
    };

    static SYSCTL_t & SYSCTL     = (*(SYSCTL_t *)0xe0043000);

} // _SYSCTL_

// Interrupt numbers
#define PSS_IRQ               0
#define CS_IRQ                1
#define PCM_IRQ               2
#define WDT_A_IRQ             3
#define FPU_IRQ               4
#define FLCTL_IRQ             5
#define COMP_E0_IRQ           6
#define COMP_E1_IRQ           7
#define TA0_0_IRQ             8
#define TA0_N_IRQ             9
#define TA1_0_IRQ             10
#define TA1_N_IRQ             11
#define TA2_0_IRQ             12
#define TA2_N_IRQ             13
#define TA3_0_IRQ             14
#define TA3_N_IRQ             15
#define EUSCIA0_IRQ           16
#define EUSCIA1_IRQ           17
#define EUSCIA2_IRQ           18
#define EUSCIA3_IRQ           19
#define EUSCIB0_IRQ           20
#define EUSCIB1_IRQ           21
#define EUSCIB2_IRQ           22
#define EUSCIB3_IRQ           23
#define ADC14_IRQ             24
#define T32_INT1_IRQ          25
#define T32_INT2_IRQ          26
#define T32_INTC_IRQ          27
#define AES256_IRQ            28
#define RTC_C_IRQ             29
#define DMA_ERR_IRQ           30
#define DMA_INT3_IRQ          31
#define DMA_INT2_IRQ          32
#define DMA_INT1_IRQ          33
#define DMA_INT0_IRQ          34
#define PORT1_IRQ             35
#define PORT2_IRQ             36
#define PORT3_IRQ             37
#define PORT4_IRQ             38
#define PORT5_IRQ             39
#define PORT6_IRQ             40

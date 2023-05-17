///////////////////////////////////////////////////////////////////////////
// This file was generated with svd2cpp, source file was ESP8266.svd
// DO NOT EDIT - CHANGES MIGHT BE OVERWRITTEN !!
///////////////////////////////////////////////////////////////////////////
//
#include "bitfield_defs.h"

// name: esp8266
// version: 1.0
// addressUnitBits: 8
// width: 32
// cpu
//   name: Xtensa LX106
//   revision: 1
//   endian: little
//   mpuPresent: false
//   fpuPresent: true
//   nvicPrioBits: 3
//   vendorSystickConfig: false

namespace _DPORT_  {

    // EDGE_INT_ENABLE
    // Reset value: 0x00000000
    BEGIN_TYPE(EDGE_INT_ENABLE_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // DPORT_CTL
    // Reset value: 0x00000000
    BEGIN_TYPE(DPORT_CTL_t, uint32_t)
        ADD_BITFIELD_RW(DPORT_CTL_DOUBLE_CLK, 0, 1)
    END_TYPE()

    struct DPORT_t {
        uint32_t                      reserved0;
        EDGE_INT_ENABLE_t             EDGE_INT_ENABLE;
        uint32_t                      reserved1[3];
        DPORT_CTL_t                   DPORT_CTL;
    };

    static DPORT_t & DPORT     = (*(DPORT_t *)0x3ff00000);

} // _DPORT_

namespace _EFUSE_  {

    // EFUSE_DATA0
    // Reset value: 0x00000000
    BEGIN_TYPE(EFUSE_DATA0_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // EFUSE_DATA1
    // Reset value: 0x00000000
    BEGIN_TYPE(EFUSE_DATA1_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // EFUSE_DATA2
    // Reset value: 0x00000000
    BEGIN_TYPE(EFUSE_DATA2_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // EFUSE_DATA3
    // Reset value: 0x00000000
    BEGIN_TYPE(EFUSE_DATA3_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    struct EFUSE_t {
        EFUSE_DATA0_t                 EFUSE_DATA0;
        EFUSE_DATA1_t                 EFUSE_DATA1;
        EFUSE_DATA2_t                 EFUSE_DATA2;
        EFUSE_DATA3_t                 EFUSE_DATA3;
    };

    static EFUSE_t & EFUSE     = (*(EFUSE_t *)0x3ff00050);

} // _EFUSE_

namespace _GPIO_  {

    // BT-Coexist Selection register
    // Reset value: 0x00000000
    BEGIN_TYPE(OUT_t, uint32_t)
        // BT-Coexist Selection register
        ADD_BITFIELD_RW(BT_SEL, 16, 16)
        // The output value when the GPIO pin is set as output.
        ADD_BITFIELD_RW(DATA, 0, 16)
    END_TYPE()

    // GPIO_OUT_W1TS
    // Reset value: 0x00000000
    BEGIN_TYPE(OUT_W1TS_t, uint32_t)
        // Writing 1 into a bit in this register
        // will set the related bit in GPIO_OUT_DATA
        ADD_BITFIELD_WO(GPIO_OUT_DATA_W1TS, 0, 16)
    END_TYPE()

    // GPIO_OUT_W1TC
    // Reset value: 0x00000000
    BEGIN_TYPE(OUT_W1TC_t, uint32_t)
        // Writing 1 into a bit in this register
        // will clear the related bit in GPIO_OUT_DATA
        ADD_BITFIELD_WO(GPIO_OUT_DATA_W1TC, 0, 16)
    END_TYPE()

    // GPIO_ENABLE
    // Reset value: 0x00000000
    BEGIN_TYPE(ENABLE_t, uint32_t)
        // SDIO-dis selection register
        ADD_BITFIELD_RW(SDIO_SEL, 16, 6)
        // The output enable register.
        ADD_BITFIELD_RW(DATA, 0, 16)
    END_TYPE()

    // GPIO_ENABLE_W1TS
    // Reset value: 0x00000000
    BEGIN_TYPE(ENABLE_W1TS_t, uint32_t)
        // Writing 1 into a bit in this register
        // will set the related bit in GPIO_ENABLE_DATA
        ADD_BITFIELD_WO(GPIO_ENABLE_DATA_W1TS, 0, 16)
    END_TYPE()

    // GPIO_ENABLE_W1TC
    // Reset value: 0x00000000
    BEGIN_TYPE(ENABLE_W1TC_t, uint32_t)
        // Writing 1 into a bit in this register
        // will clear the related bit in GPIO_ENABLE_DATA
        ADD_BITFIELD_WO(GPIO_ENABLE_DATA_W1TC, 0, 16)
    END_TYPE()

    // The values of the strapping pins.
    // Reset value: 0x00000000
    BEGIN_TYPE(IN_t, uint32_t)
        // The values of the strapping pins.
        ADD_BITFIELD_RW(STRAPPING, 16, 16)
        // The values of the GPIO pins when the GPIO pin is set as input.
        ADD_BITFIELD_RW(DATA, 0, 16)
    END_TYPE()

    // GPIO_STATUS
    // Reset value: 0x00000000
    BEGIN_TYPE(STATUS_t, uint32_t)
        // Interrupt enable register.
        ADD_BITFIELD_RW(GPIO_STATUS_INTERRUPT, 0, 16)
    END_TYPE()

    // GPIO_STATUS_W1TS
    // Reset value: 0x00000000
    BEGIN_TYPE(STATUS_W1TS_t, uint32_t)
        // Writing 1 into a bit in this register will
        // set the related bit in GPIO_STATUS_INTERRUPT
        ADD_BITFIELD_WO(GPIO_STATUS_INTERRUPT_W1TS, 0, 16)
    END_TYPE()

    // GPIO_STATUS_W1TC
    // Reset value: 0x00000000
    BEGIN_TYPE(STATUS_W1TC_t, uint32_t)
        // Writing 1 into a bit in this register will
        // clear the related bit in GPIO_STATUS_INTERRUPT
        ADD_BITFIELD_WO(GPIO_STATUS_INTERRUPT_W1TC, 0, 16)
    END_TYPE()

    // GPIO_PIN register
    // Reset value: 0x00000000
    BEGIN_TYPE(PIN_t, uint32_t)
        // 1: sigma-delta; 0: GPIO_DATA
        ADD_BITFIELD_RW(SOURCE, 0, 1)
        // 1: open drain; 0: normal
        ADD_BITFIELD_RW(DRIVER, 2, 1)
        // Interrupt type
        ADD_BITFIELD_RW(INT_TYPE, 7, 3)
        // 0: disable; 1: enable GPIO wakeup CPU,
        // only when GPIO INT_TYPE is 0x4 or 0x5
        ADD_BITFIELD_RW(WAKEUP_ENABLE, 10, 1)
    END_TYPE()

    static const uint32_t PIN_SOURCE__GPIO = 0;
    static const uint32_t PIN_SOURCE__SIGMA_DELTA = 1;
    static const uint32_t PIN_DRIVER__PUSH_PULL = 0;
    static const uint32_t PIN_DRIVER__OPEN_DRAIN = 1;
    static const uint32_t PIN_INT_TYPE__DISABLE = 0;
    static const uint32_t PIN_INT_TYPE__RAISING_EDGE = 1;
    static const uint32_t PIN_INT_TYPE__FALLING_EDGE = 2;
    static const uint32_t PIN_INT_TYPE__BOTH_EDGES = 3;
    static const uint32_t PIN_INT_TYPE__LEVEL_LOW = 4;
    static const uint32_t PIN_INT_TYPE__LEVEL_HIGH = 5;

    // GPIO_SIGMA_DELTA
    // Reset value: 0x00000000
    BEGIN_TYPE(SIGMA_DELTA_t, uint32_t)
        // 1: enable sigma-delta; 0: disable
        ADD_BITFIELD_RW(ENABLE, 16, 1)
        // Clock pre-divider for sigma-delta.
        ADD_BITFIELD_RW(PRESCALE, 8, 8)
        // target level of the sigma-delta. It is a signed byte.
        ADD_BITFIELD_RW(TARGET, 0, 8)
    END_TYPE()

    // Positvie edge of this bit will trigger the RTC-clock-calibration process.
    // Reset value: 0x00000000
    BEGIN_TYPE(RTC_CALIB_SYNC_t, uint32_t)
        // Positvie edge of this bit will trigger the RTC-clock-calibration process.
        ADD_BITFIELD_RW(RTC_CALIB_START, 31, 1)
        // The cycle number of RTC-clock during RTC-clock-calibration
        ADD_BITFIELD_RW(RTC_PERIOD_NUM, 0, 10)
    END_TYPE()

    // 0: during RTC-clock-calibration; 1: RTC-clock-calibration is done
    // Reset value: 0x00000000
    BEGIN_TYPE(RTC_CALIB_VALUE_t, uint32_t)
        // 0: during RTC-clock-calibration; 1: RTC-clock-calibration is done
        ADD_BITFIELD_RW(RTC_CALIB_RDY, 31, 1)
        // 0: during RTC-clock-calibration; 1: RTC-clock-calibration is done
        ADD_BITFIELD_RW(RTC_CALIB_RDY_REAL, 30, 1)
        // The cycle number of clk_xtal (crystal clock)
        // for the RTC_PERIOD_NUM cycles of RTC-clock
        ADD_BITFIELD_RW(RTC_CALIB_VALUE, 0, 20)
    END_TYPE()

    struct GPIO_t {
        OUT_t                         OUT;
        OUT_W1TS_t                    OUT_W1TS;
        OUT_W1TC_t                    OUT_W1TC;
        ENABLE_t                      ENABLE;
        ENABLE_W1TS_t                 ENABLE_W1TS;
        ENABLE_W1TC_t                 ENABLE_W1TC;
        IN_t                          IN;
        STATUS_t                      STATUS;
        STATUS_W1TS_t                 STATUS_W1TS;
        STATUS_W1TC_t                 STATUS_W1TC;
        PIN_t                         PIN[16];
        SIGMA_DELTA_t                 SIGMA_DELTA;
        RTC_CALIB_SYNC_t              RTC_CALIB_SYNC;
        RTC_CALIB_VALUE_t             RTC_CALIB_VALUE;
    };

    static GPIO_t & GPIO     = (*(GPIO_t *)0x60000300);

} // _GPIO_

namespace _I2S_  {

    // I2STXFIFO
    // Reset value: 0x00000000
    BEGIN_TYPE(I2STXFIFO_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // I2SRXFIFO
    // Reset value: 0x00000000
    BEGIN_TYPE(I2SRXFIFO_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // I2SCONF
    // Reset value: 0x00000000
    BEGIN_TYPE(I2SCONF_t, uint32_t)
        ADD_BITFIELD_RW(I2S_BCK_DIV_NUM, 22, 6)
        ADD_BITFIELD_RW(I2S_CLKM_DIV_NUM, 16, 6)
        ADD_BITFIELD_RW(I2S_BITS_MOD, 12, 4)
        ADD_BITFIELD_RW(I2S_RECE_MSB_SHIFT, 11, 1)
        ADD_BITFIELD_RW(I2S_TRANS_MSB_SHIFT, 10, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_START, 9, 1)
        ADD_BITFIELD_RW(I2S_I2S_TX_START, 8, 1)
        ADD_BITFIELD_RW(I2S_MSB_RIGHT, 7, 1)
        ADD_BITFIELD_RW(I2S_RIGHT_FIRST, 6, 1)
        ADD_BITFIELD_RW(I2S_RECE_SLAVE_MOD, 5, 1)
        ADD_BITFIELD_RW(I2S_TRANS_SLAVE_MOD, 4, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_FIFO_RESET, 3, 1)
        ADD_BITFIELD_RW(I2S_I2S_TX_FIFO_RESET, 2, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_RESET, 1, 1)
        ADD_BITFIELD_RW(I2S_I2S_TX_RESET, 0, 1)
    END_TYPE()

    // I2SINT_RAW
    // Reset value: 0x00000000
    BEGIN_TYPE(I2SINT_RAW_t, uint32_t)
        ADD_BITFIELD_RW(I2S_I2S_TX_REMPTY_INT_RAW, 5, 1)
        ADD_BITFIELD_RW(I2S_I2S_TX_WFULL_INT_RAW, 4, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_REMPTY_INT_RAW, 3, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_WFULL_INT_RAW, 2, 1)
        ADD_BITFIELD_RW(I2S_I2S_TX_PUT_DATA_INT_RAW, 1, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_TAKE_DATA_INT_RAW, 0, 1)
    END_TYPE()

    // I2SINT_ST
    // Reset value: 0x00000000
    BEGIN_TYPE(I2SINT_ST_t, uint32_t)
        ADD_BITFIELD_RW(I2S_I2S_TX_REMPTY_INT_ST, 5, 1)
        ADD_BITFIELD_RW(I2S_I2S_TX_WFULL_INT_ST, 4, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_REMPTY_INT_ST, 3, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_WFULL_INT_ST, 2, 1)
        ADD_BITFIELD_RW(I2S_I2S_TX_PUT_DATA_INT_ST, 1, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_TAKE_DATA_INT_ST, 0, 1)
    END_TYPE()

    // I2SINT_ENA
    // Reset value: 0x00000000
    BEGIN_TYPE(I2SINT_ENA_t, uint32_t)
        ADD_BITFIELD_RW(I2S_I2S_TX_REMPTY_INT_ENA, 5, 1)
        ADD_BITFIELD_RW(I2S_I2S_TX_WFULL_INT_ENA, 4, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_REMPTY_INT_ENA, 3, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_WFULL_INT_ENA, 2, 1)
        ADD_BITFIELD_RW(I2S_I2S_TX_PUT_DATA_INT_ENA, 1, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_TAKE_DATA_INT_ENA, 0, 1)
    END_TYPE()

    // I2SINT_CLR
    // Reset value: 0x00000000
    BEGIN_TYPE(I2SINT_CLR_t, uint32_t)
        ADD_BITFIELD_RW(I2S_I2S_TX_REMPTY_INT_CLR, 5, 1)
        ADD_BITFIELD_RW(I2S_I2S_TX_WFULL_INT_CLR, 4, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_REMPTY_INT_CLR, 3, 1)
        ADD_BITFIELD_RW(I2S_I2S_RX_WFULL_INT_CLR, 2, 1)
        ADD_BITFIELD_RW(I2S_I2S_PUT_DATA_INT_CLR, 1, 1)
        ADD_BITFIELD_RW(I2S_I2S_TAKE_DATA_INT_CLR, 0, 1)
    END_TYPE()

    // I2STIMING
    // Reset value: 0x00000000
    BEGIN_TYPE(I2STIMING_t, uint32_t)
        ADD_BITFIELD_RW(I2S_TRANS_BCK_IN_INV, 22, 1)
        ADD_BITFIELD_RW(I2S_RECE_DSYNC_SW, 21, 1)
        ADD_BITFIELD_RW(I2S_TRANS_DSYNC_SW, 20, 1)
        ADD_BITFIELD_RW(I2S_RECE_BCK_OUT_DELAY, 18, 2)
        ADD_BITFIELD_RW(I2S_RECE_WS_OUT_DELAY, 16, 2)
        ADD_BITFIELD_RW(I2S_TRANS_SD_OUT_DELAY, 14, 2)
        ADD_BITFIELD_RW(I2S_TRANS_WS_OUT_DELAY, 12, 2)
        ADD_BITFIELD_RW(I2S_TRANS_BCK_OUT_DELAY, 10, 2)
        ADD_BITFIELD_RW(I2S_RECE_SD_IN_DELAY, 8, 2)
        ADD_BITFIELD_RW(I2S_RECE_WS_IN_DELAY, 6, 2)
        ADD_BITFIELD_RW(I2S_RECE_BCK_IN_DELAY, 4, 2)
        ADD_BITFIELD_RW(I2S_TRANS_WS_IN_DELAY, 2, 2)
        ADD_BITFIELD_RW(I2S_TRANS_BCK_IN_DELAY, 0, 2)
    END_TYPE()

    // I2S_FIFO_CONF
    // Reset value: 0x00000000
    BEGIN_TYPE(I2S_FIFO_CONF_t, uint32_t)
        ADD_BITFIELD_RW(I2S_I2S_RX_FIFO_MOD, 16, 3)
        ADD_BITFIELD_RW(I2S_I2S_TX_FIFO_MOD, 13, 3)
        ADD_BITFIELD_RW(I2S_I2S_DSCR_EN, 12, 1)
        ADD_BITFIELD_RW(I2S_I2S_TX_DATA_NUM, 6, 6)
        ADD_BITFIELD_RW(I2S_I2S_RX_DATA_NUM, 0, 6)
    END_TYPE()

    // I2SRXEOF_NUM
    // Reset value: 0x00000000
    BEGIN_TYPE(I2SRXEOF_NUM_t, uint32_t)
        ADD_BITFIELD_RW(I2S_I2S_RX_EOF_NUM, 0, 32)
    END_TYPE()

    // I2SCONF_SIGLE_DATA
    // Reset value: 0x00000000
    BEGIN_TYPE(I2SCONF_SIGLE_DATA_t, uint32_t)
        ADD_BITFIELD_RW(I2S_I2S_SIGLE_DATA, 0, 32)
    END_TYPE()

    struct I2S_t {
        I2STXFIFO_t                   I2STXFIFO;
        I2SRXFIFO_t                   I2SRXFIFO;
        I2SCONF_t                     I2SCONF;
        I2SINT_RAW_t                  I2SINT_RAW;
        I2SINT_ST_t                   I2SINT_ST;
        I2SINT_ENA_t                  I2SINT_ENA;
        I2SINT_CLR_t                  I2SINT_CLR;
        I2STIMING_t                   I2STIMING;
        I2S_FIFO_CONF_t               I2S_FIFO_CONF;
        I2SRXEOF_NUM_t                I2SRXEOF_NUM;
        I2SCONF_SIGLE_DATA_t          I2SCONF_SIGLE_DATA;
    };

    static I2S_t & I2S     = (*(I2S_t *)0x60000e00);

} // _I2S_

namespace _IO_MUX_  {

    // IO_MUX_CONF
    // Reset value: 0x00000000
    BEGIN_TYPE(CONF_t, uint32_t)
        ADD_BITFIELD_RW(SPI0_CLK_EQU_SYS_CLK, 8, 1)
        ADD_BITFIELD_RW(SPI1_CLK_EQU_SYS_CLK, 9, 1)
    END_TYPE()

    // IO_MUX Entry
    // Reset value: 0x00000000
    BEGIN_TYPE(ENTRY_t, uint32_t)
        ADD_BITFIELD_RW(OE, 0, 1)
        ADD_BITFIELD_RW(OE_SLEEP, 1, 1)
        ADD_BITFIELD_RW(PULLDOWN_SLEEP, 2, 1)
        ADD_BITFIELD_RW(PULLUP_SLEEP, 3, 1)
        ADD_BITFIELD_RW(PULLDOWN, 6, 1)
        ADD_BITFIELD_RW(PULLUP, 7, 1)
        ADD_BITFIELD_RW(FUNC, 19, 4)
    END_TYPE()

    struct IO_MUX_t {
        CONF_t                        CONF;
        ENTRY_t                       ENTRY[16];
    };

    static IO_MUX_t & IO_MUX     = (*(IO_MUX_t *)0x60000800);

} // _IO_MUX_

namespace _RTC_  {

    // RTC_STORE0
    // Reset value: 0x00000000
    BEGIN_TYPE(RTC_STORE0_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // RTC_STATE1
    // Reset value: 0x00000000
    BEGIN_TYPE(RTC_STATE1_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    struct RTC_t {
        uint32_t                      reserved0[5];
        RTC_STATE1_t                  RTC_STATE1;
        uint32_t                      reserved1[6];
        RTC_STORE0_t                  RTC_STORE0;
    };

    static RTC_t & RTC     = (*(RTC_t *)0x60000700);

} // _RTC_

namespace _SLC_  {

    // SLC_CONF0
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_CONF0_t, uint32_t)
        ADD_BITFIELD_RW(SLC_MODE, 12, 2)
        ADD_BITFIELD_RW(SLC_DATA_BURST_EN, 9, 1)
        ADD_BITFIELD_RW(SLC_DSCR_BURST_EN, 8, 1)
        ADD_BITFIELD_RW(SLC_RX_NO_RESTART_CLR, 7, 1)
        ADD_BITFIELD_RW(SLC_RX_AUTO_WRBACK, 6, 1)
        ADD_BITFIELD_RW(SLC_RX_LOOP_TEST, 5, 1)
        ADD_BITFIELD_RW(SLC_TX_LOOP_TEST, 4, 1)
        ADD_BITFIELD_RW(SLC_AHBM_RST, 3, 1)
        ADD_BITFIELD_RW(SLC_AHBM_FIFO_RST, 2, 1)
        ADD_BITFIELD_RW(SLC_RXLINK_RST, 1, 1)
        ADD_BITFIELD_RW(SLC_TXLINK_RST, 0, 1)
    END_TYPE()

    // SLC_INT_RAW
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_INT_RAW_t, uint32_t)
        ADD_BITFIELD_RW(SLC_TX_DSCR_EMPTY_INT_RAW, 21, 1)
        ADD_BITFIELD_RW(SLC_RX_DSCR_ERR_INT_RAW, 20, 1)
        ADD_BITFIELD_RW(SLC_TX_DSCR_ERR_INT_RAW, 19, 1)
        ADD_BITFIELD_RW(SLC_TOHOST_INT_RAW, 18, 1)
        ADD_BITFIELD_RW(SLC_RX_EOF_INT_RAW, 17, 1)
        ADD_BITFIELD_RW(SLC_RX_DONE_INT_RAW, 16, 1)
        ADD_BITFIELD_RW(SLC_TX_EOF_INT_RAW, 15, 1)
        ADD_BITFIELD_RW(SLC_TX_DONE_INT_RAW, 14, 1)
        ADD_BITFIELD_RW(SLC_TOKEN1_1TO0_INT_RAW, 13, 1)
        ADD_BITFIELD_RW(SLC_TOKEN0_1TO0_INT_RAW, 12, 1)
        ADD_BITFIELD_RW(SLC_TX_OVF_INT_RAW, 11, 1)
        ADD_BITFIELD_RW(SLC_RX_UDF_INT_RAW, 10, 1)
        ADD_BITFIELD_RW(SLC_TX_START_INT_RAW, 9, 1)
        ADD_BITFIELD_RW(SLC_RX_START_INT_RAW, 8, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT7_INT_RAW, 7, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT6_INT_RAW, 6, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT5_INT_RAW, 5, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT4_INT_RAW, 4, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT3_INT_RAW, 3, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT2_INT_RAW, 2, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT1_INT_RAW, 1, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT0_INT_RAW, 0, 1)
    END_TYPE()

    // SLC_INT_STATUS
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_INT_STATUS_t, uint32_t)
        ADD_BITFIELD_RW(SLC_TX_DSCR_EMPTY_INT_ST, 21, 1)
        ADD_BITFIELD_RW(SLC_RX_DSCR_ERR_INT_ST, 20, 1)
        ADD_BITFIELD_RW(SLC_TX_DSCR_ERR_INT_ST, 19, 1)
        ADD_BITFIELD_RW(SLC_TOHOST_INT_ST, 18, 1)
        ADD_BITFIELD_RW(SLC_RX_EOF_INT_ST, 17, 1)
        ADD_BITFIELD_RW(SLC_RX_DONE_INT_ST, 16, 1)
        ADD_BITFIELD_RW(SLC_TX_EOF_INT_ST, 15, 1)
        ADD_BITFIELD_RW(SLC_TX_DONE_INT_ST, 14, 1)
        ADD_BITFIELD_RW(SLC_TOKEN1_1TO0_INT_ST, 13, 1)
        ADD_BITFIELD_RW(SLC_TOKEN0_1TO0_INT_ST, 12, 1)
        ADD_BITFIELD_RW(SLC_TX_OVF_INT_ST, 11, 1)
        ADD_BITFIELD_RW(SLC_RX_UDF_INT_ST, 10, 1)
        ADD_BITFIELD_RW(SLC_TX_START_INT_ST, 9, 1)
        ADD_BITFIELD_RW(SLC_RX_START_INT_ST, 8, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT7_INT_ST, 7, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT6_INT_ST, 6, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT5_INT_ST, 5, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT4_INT_ST, 4, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT3_INT_ST, 3, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT2_INT_ST, 2, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT1_INT_ST, 1, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT0_INT_ST, 0, 1)
    END_TYPE()

    // SLC_INT_ENA
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_INT_ENA_t, uint32_t)
        ADD_BITFIELD_RW(SLC_TX_DSCR_EMPTY_INT_ENA, 21, 1)
        ADD_BITFIELD_RW(SLC_RX_DSCR_ERR_INT_ENA, 20, 1)
        ADD_BITFIELD_RW(SLC_TX_DSCR_ERR_INT_ENA, 19, 1)
        ADD_BITFIELD_RW(SLC_TOHOST_INT_ENA, 18, 1)
        ADD_BITFIELD_RW(SLC_RX_EOF_INT_ENA, 17, 1)
        ADD_BITFIELD_RW(SLC_RX_DONE_INT_ENA, 16, 1)
        ADD_BITFIELD_RW(SLC_TX_EOF_INT_ENA, 15, 1)
        ADD_BITFIELD_RW(SLC_TX_DONE_INT_ENA, 14, 1)
        ADD_BITFIELD_RW(SLC_TOKEN1_1TO0_INT_ENA, 13, 1)
        ADD_BITFIELD_RW(SLC_TOKEN0_1TO0_INT_ENA, 12, 1)
        ADD_BITFIELD_RW(SLC_TX_OVF_INT_ENA, 11, 1)
        ADD_BITFIELD_RW(SLC_RX_UDF_INT_ENA, 10, 1)
        ADD_BITFIELD_RW(SLC_TX_START_INT_ENA, 9, 1)
        ADD_BITFIELD_RW(SLC_RX_START_INT_ENA, 8, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT7_INT_ENA, 7, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT6_INT_ENA, 6, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT5_INT_ENA, 5, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT4_INT_ENA, 4, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT3_INT_ENA, 3, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT2_INT_ENA, 2, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT1_INT_ENA, 1, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT0_INT_ENA, 0, 1)
    END_TYPE()

    // SLC_INT_CLR
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_INT_CLR_t, uint32_t)
        ADD_BITFIELD_RW(SLC_TX_DSCR_EMPTY_INT_CLR, 21, 1)
        ADD_BITFIELD_RW(SLC_RX_DSCR_ERR_INT_CLR, 20, 1)
        ADD_BITFIELD_RW(SLC_TX_DSCR_ERR_INT_CLR, 19, 1)
        ADD_BITFIELD_RW(SLC_TOHOST_INT_CLR, 18, 1)
        ADD_BITFIELD_RW(SLC_RX_EOF_INT_CLR, 17, 1)
        ADD_BITFIELD_RW(SLC_RX_DONE_INT_CLR, 16, 1)
        ADD_BITFIELD_RW(SLC_TX_EOF_INT_CLR, 15, 1)
        ADD_BITFIELD_RW(SLC_TX_DONE_INT_CLR, 14, 1)
        ADD_BITFIELD_RW(SLC_TOKEN1_1TO0_INT_CLR, 13, 1)
        ADD_BITFIELD_RW(SLC_TOKEN0_1TO0_INT_CLR, 12, 1)
        ADD_BITFIELD_RW(SLC_TX_OVF_INT_CLR, 11, 1)
        ADD_BITFIELD_RW(SLC_RX_UDF_INT_CLR, 10, 1)
        ADD_BITFIELD_RW(SLC_TX_START_INT_CLR, 9, 1)
        ADD_BITFIELD_RW(SLC_RX_START_INT_CLR, 8, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT7_INT_CLR, 7, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT6_INT_CLR, 6, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT5_INT_CLR, 5, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT4_INT_CLR, 4, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT3_INT_CLR, 3, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT2_INT_CLR, 2, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT1_INT_CLR, 1, 1)
        ADD_BITFIELD_RW(SLC_FRHOST_BIT0_INT_CLR, 0, 1)
    END_TYPE()

    // SLC_RX_STATUS
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_RX_STATUS_t, uint32_t)
        ADD_BITFIELD_RW(SLC_RX_EMPTY, 1, 1)
        ADD_BITFIELD_RW(SLC_RX_FULL, 0, 1)
    END_TYPE()

    // SLC_RX_FIFO_PUSH
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_RX_FIFO_PUSH_t, uint32_t)
        ADD_BITFIELD_RW(SLC_RXFIFO_PUSH, 16, 1)
        ADD_BITFIELD_RW(SLC_RXFIFO_WDATA, 0, 9)
    END_TYPE()

    // SLC_TX_STATUS
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_TX_STATUS_t, uint32_t)
        ADD_BITFIELD_RW(SLC_TX_EMPTY, 1, 1)
        ADD_BITFIELD_RW(SLC_TX_FULL, 0, 1)
    END_TYPE()

    // SLC_TX_FIFO_POP
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_TX_FIFO_POP_t, uint32_t)
        ADD_BITFIELD_RW(SLC_TXFIFO_POP, 16, 1)
        ADD_BITFIELD_RW(SLC_TXFIFO_RDATA, 0, 11)
    END_TYPE()

    // SLC_RX_LINK
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_RX_LINK_t, uint32_t)
        ADD_BITFIELD_RW(SLC_RXLINK_PARK, 31, 1)
        ADD_BITFIELD_RW(SLC_RXLINK_RESTART, 30, 1)
        ADD_BITFIELD_RW(SLC_RXLINK_START, 29, 1)
        ADD_BITFIELD_RW(SLC_RXLINK_STOP, 28, 1)
        ADD_BITFIELD_RW(SLC_RXLINK_ADDR, 0, 20)
    END_TYPE()

    // SLC_TX_LINK
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_TX_LINK_t, uint32_t)
        ADD_BITFIELD_RW(SLC_TXLINK_PARK, 31, 1)
        ADD_BITFIELD_RW(SLC_TXLINK_RESTART, 30, 1)
        ADD_BITFIELD_RW(SLC_TXLINK_START, 29, 1)
        ADD_BITFIELD_RW(SLC_TXLINK_STOP, 28, 1)
        ADD_BITFIELD_RW(SLC_TXLINK_ADDR, 0, 20)
    END_TYPE()

    // SLC_INTVEC_TOHOST
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_INTVEC_TOHOST_t, uint32_t)
        ADD_BITFIELD_RW(SLC_TOHOST_INTVEC, 0, 8)
    END_TYPE()

    // SLC_TOKEN0
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_TOKEN0_t, uint32_t)
        ADD_BITFIELD_RW(SLC_TOKEN0, 16, 12)
        ADD_BITFIELD_RW(SLC_TOKEN0_LOCAL_INC_MORE, 14, 1)
        ADD_BITFIELD_RW(SLC_TOKEN0_LOCAL_INC, 13, 1)
        ADD_BITFIELD_RW(SLC_TOKEN0_LOCAL_WR, 12, 1)
        ADD_BITFIELD_RW(SLC_TOKEN0_LOCAL_WDATA, 0, 12)
    END_TYPE()

    // SLC_TOKEN1
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_TOKEN1_t, uint32_t)
        ADD_BITFIELD_RW(SLC_TOKEN1, 16, 12)
        ADD_BITFIELD_RW(SLC_TOKEN1_LOCAL_INC_MORE, 14, 1)
        ADD_BITFIELD_RW(SLC_TOKEN1_LOCAL_INC, 13, 1)
        ADD_BITFIELD_RW(SLC_TOKEN1_LOCAL_WR, 12, 1)
        ADD_BITFIELD_RW(SLC_TOKEN1_LOCAL_WDATA, 0, 12)
    END_TYPE()

    // SLC_CONF1
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_CONF1_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_STATE0
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_STATE0_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_STATE1
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_STATE1_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_BRIDGE_CONF
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_BRIDGE_CONF_t, uint32_t)
        ADD_BITFIELD_RW(SLC_TX_PUSH_IDLE_NUM, 16, 16)
        ADD_BITFIELD_RW(SLC_TX_DUMMY_MODE, 12, 1)
        ADD_BITFIELD_RW(SLC_FIFO_MAP_ENA, 8, 4)
        ADD_BITFIELD_RW(SLC_TXEOF_ENA, 0, 6)
    END_TYPE()

    // SLC_RX_EOF_DES_ADDR
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_RX_EOF_DES_ADDR_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_TX_EOF_DES_ADDR
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_TX_EOF_DES_ADDR_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_RX_EOF_BFR_DES_ADDR
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_RX_EOF_BFR_DES_ADDR_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_AHB_TEST
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_AHB_TEST_t, uint32_t)
        ADD_BITFIELD_RW(SLC_AHB_TESTADDR, 4, 2)
        ADD_BITFIELD_RW(SLC_AHB_TESTMODE, 0, 3)
    END_TYPE()

    // SLC_SDIO_ST
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_SDIO_ST_t, uint32_t)
        ADD_BITFIELD_RW(SLC_BUS_ST, 12, 3)
        ADD_BITFIELD_RW(SLC_SDIO_WAKEUP, 8, 1)
        ADD_BITFIELD_RW(SLC_FUNC_ST, 4, 4)
        ADD_BITFIELD_RW(SLC_CMD_ST, 0, 3)
    END_TYPE()

    // SLC_RX_DSCR_CONF
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_RX_DSCR_CONF_t, uint32_t)
        ADD_BITFIELD_RW(SLC_INFOR_NO_REPLACE, 9, 1)
        ADD_BITFIELD_RW(SLC_TOKEN_NO_REPLACE, 8, 1)
    END_TYPE()

    // SLC_TXLINK_DSCR
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_TXLINK_DSCR_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_TXLINK_DSCR_BF0
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_TXLINK_DSCR_BF0_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_TXLINK_DSCR_BF1
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_TXLINK_DSCR_BF1_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_RXLINK_DSCR
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_RXLINK_DSCR_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_RXLINK_DSCR_BF0
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_RXLINK_DSCR_BF0_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_RXLINK_DSCR_BF1
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_RXLINK_DSCR_BF1_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_DATE
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_DATE_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // SLC_ID
    // Reset value: 0x00000000
    BEGIN_TYPE(SLC_ID_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    struct SLC_t {
        SLC_CONF0_t                   SLC_CONF0;
        SLC_INT_RAW_t                 SLC_INT_RAW;
        SLC_INT_STATUS_t              SLC_INT_STATUS;
        SLC_INT_ENA_t                 SLC_INT_ENA;
        SLC_INT_CLR_t                 SLC_INT_CLR;
        SLC_RX_STATUS_t               SLC_RX_STATUS;
        SLC_RX_FIFO_PUSH_t            SLC_RX_FIFO_PUSH;
        SLC_TX_STATUS_t               SLC_TX_STATUS;
        SLC_TX_FIFO_POP_t             SLC_TX_FIFO_POP;
        SLC_RX_LINK_t                 SLC_RX_LINK;
        SLC_TX_LINK_t                 SLC_TX_LINK;
        SLC_INTVEC_TOHOST_t           SLC_INTVEC_TOHOST;
        SLC_TOKEN0_t                  SLC_TOKEN0;
        SLC_TOKEN1_t                  SLC_TOKEN1;
        SLC_CONF1_t                   SLC_CONF1;
        SLC_STATE0_t                  SLC_STATE0;
        SLC_STATE1_t                  SLC_STATE1;
        SLC_BRIDGE_CONF_t             SLC_BRIDGE_CONF;
        SLC_RX_EOF_DES_ADDR_t         SLC_RX_EOF_DES_ADDR;
        SLC_TX_EOF_DES_ADDR_t         SLC_TX_EOF_DES_ADDR;
        SLC_RX_EOF_BFR_DES_ADDR_t     SLC_RX_EOF_BFR_DES_ADDR;
        SLC_AHB_TEST_t                SLC_AHB_TEST;
        SLC_SDIO_ST_t                 SLC_SDIO_ST;
        SLC_RX_DSCR_CONF_t            SLC_RX_DSCR_CONF;
        SLC_TXLINK_DSCR_t             SLC_TXLINK_DSCR;
        SLC_TXLINK_DSCR_BF0_t         SLC_TXLINK_DSCR_BF0;
        SLC_TXLINK_DSCR_BF1_t         SLC_TXLINK_DSCR_BF1;
        SLC_RXLINK_DSCR_t             SLC_RXLINK_DSCR;
        SLC_RXLINK_DSCR_BF0_t         SLC_RXLINK_DSCR_BF0;
        SLC_RXLINK_DSCR_BF1_t         SLC_RXLINK_DSCR_BF1;
        SLC_DATE_t                    SLC_DATE;
        SLC_ID_t                      SLC_ID;
    };

    static SLC_t & SLC     = (*(SLC_t *)0x60000b00);

} // _SLC_

namespace _SPI0_  {

    // In the master mode, it is the start bit of a single operation.
    // Self-clear by hardware
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_CMD_t, uint32_t)
        // In the master mode, it is the start bit of a single operation.
        // Self-clear by hardware
        ADD_BITFIELD_RW(spi_usr, 18, 1)
    END_TYPE()

    // In the master mode, it is the value of address in "address" phase.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_ADDR_t, uint32_t)
        // In the master mode, it is the value of address in "address" phase.
        ADD_BITFIELD_RW(iodata_start_addr, 0, 32)
    END_TYPE()

    // SPI_CTRL
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_CTRL_t, uint32_t)
        // In "command", "address", "write-data" (MOSI) phases,
        // 1: LSB first; 0: MSB first
        ADD_BITFIELD_RW(spi_wr_bit_order, 26, 1)
        // In "read-data" (MISO) phase,
        // 1: LSB first; 0: MSB first
        ADD_BITFIELD_RW(spi_rd_bit_order, 25, 1)
        // In the read operations, "address" phase and "read-data" phase apply 4 signals
        ADD_BITFIELD_RW(spi_qio_mode, 24, 1)
        // In the read operations, "address" phase and "read-data" phase apply 2 signals
        ADD_BITFIELD_RW(spi_dio_mode, 23, 1)
        // In the read operations, "read-data" phase apply 4 signals
        ADD_BITFIELD_RW(spi_qout_mode, 20, 1)
        // In the read operations, "read-data" phase apply 2 signals
        ADD_BITFIELD_RW(spi_dout_mode, 14, 1)
        // this bit enable the bits: spi_qio_mode,
        // spi_dio_mode, spi_qout_mode and spi_dout_mode
        ADD_BITFIELD_RW(spi_fastrd_mode, 13, 1)
    END_TYPE()

    // In the slave mode, this register are the
    // status register for the master to read out.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_RD_STATUS_t, uint32_t)
        // In the slave mode, this register are the
        // status register for the master to read out.
        ADD_BITFIELD_RW(slv_rd_status, 0, 32)
    END_TYPE()

    // spi_cs signal is delayed by 80MHz clock cycles
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_CTRL2_t, uint32_t)
        // spi_cs signal is delayed by 80MHz clock cycles
        ADD_BITFIELD_RW(spi_cs_delay_num, 28, 4)
        // spi_cs signal is delayed by spi_clk.
        // 0: zero; 1: half cycle; 2: one cycle
        ADD_BITFIELD_RW(spi_cs_delay_mode, 26, 2)
        // MOSI signals are delayed by 80MHz clock cycles
        ADD_BITFIELD_RW(spi_mosi_delay_num, 23, 3)
        // MOSI signals are delayed by spi_clk.
        // 0: zero; 1: half cycle; 2: one cycle
        ADD_BITFIELD_RW(spi_mosi_delay_mode, 21, 2)
        // MISO signals are delayed by 80MHz clock cycles
        ADD_BITFIELD_RW(spi_miso_delay_num, 18, 3)
        // MISO signals are delayed by spi_clk.
        // 0: zero; 1: half cycle; 2: one cycle
        ADD_BITFIELD_RW(spi_miso_delay_mode, 16, 2)
    END_TYPE()

    // In the master mode,
    // 1: spi_clk is eqaul to 80MHz, 0: spi_clk is divided from 80 MHz clock.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_CLOCK_t, uint32_t)
        // In the master mode,
        // 1: spi_clk is eqaul to 80MHz, 0: spi_clk is divided from 80 MHz clock.
        ADD_BITFIELD_RW(spi_clk_equ_sysclk, 31, 1)
        // In the master mode, it is pre-divider of spi_clk.
        ADD_BITFIELD_RW(spi_clkdiv_pre, 18, 13)
        // In the master mode, it is the divider of spi_clk.
        // So spi_clk frequency is 80MHz/(spi_clkdiv_pre+1)/(spi_clkcnt_N+1)
        ADD_BITFIELD_RW(spi_clkcnt_N, 12, 6)
        // In the master mode, it must be floor((spi_clkcnt_N+1)/2-1).
        // In the slave mode, it must be 0.
        ADD_BITFIELD_RW(spi_clkcnt_H, 6, 6)
        // In the master mode, it must be eqaul to spi_clkcnt_N.
        // In the slave mode, it must be 0.
        ADD_BITFIELD_RW(spi_clkcnt_L, 0, 6)
    END_TYPE()

    // This bit enable the "command" phase of an operation.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_USER_t, uint32_t)
        // This bit enable the "command" phase of an operation.
        ADD_BITFIELD_RW(spi_usr_command, 31, 1)
        // This bit enable the "address" phase of an operation.
        ADD_BITFIELD_RW(spi_usr_addr, 30, 1)
        // This bit enable the "dummy" phase of an operation.
        ADD_BITFIELD_RW(spi_usr_dummy, 29, 1)
        // This bit enable the "read-data" phase of an operation.
        ADD_BITFIELD_RW(spi_usr_miso, 28, 1)
        // This bit enable the "write-data" phase of an operation.
        ADD_BITFIELD_RW(spi_usr_mosi, 27, 1)
        // 1: "write-data" phase only access to high-part of the buffer spi_w8~spi_w15
        ADD_BITFIELD_RW(reg_usr_mosi_highpart, 25, 1)
        // 1: "read-data" phase only access to high-part of the buffer spi_w8~spi_w15
        ADD_BITFIELD_RW(reg_usr_miso_highpart, 24, 1)
        // 1: mosi and miso signals share the same pin
        ADD_BITFIELD_RW(spi_sio, 16, 1)
        // In the write operations, "address" phase and
        // "read-data" phase apply 4 signals
        ADD_BITFIELD_RW(spi_fwrite_qio, 15, 1)
        // In the write operations, "address" phase and
        // "read-data" phase apply 2 signals
        ADD_BITFIELD_RW(spi_fwrite_dio, 14, 1)
        // In the write operations, "read-data" phase apply 4 signals
        ADD_BITFIELD_RW(spi_fwrite_quad, 13, 1)
        // In the write operations, "read-data" phase apply 2 signals
        ADD_BITFIELD_RW(spi_fwrite_dual, 12, 1)
        // In "command", "address", "write-data" (MOSI) phases,
        // 1: little-endian; 0: big_endian
        ADD_BITFIELD_RW(spi_wr_byte_order, 11, 1)
        // In "read-data" (MISO) phase, 1: little-endian; 0: big_endian
        ADD_BITFIELD_RW(spi_rd_byte_order, 10, 1)
        // In the slave mode, 1: rising-edge; 0: falling-edge
        ADD_BITFIELD_RW(spi_ck_i_edge, 6, 1)
    END_TYPE()

    // The length in bits of "address" phase.
    // The register value shall be (bit_num-1)
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_USER1_t, uint32_t)
        // The length in bits of "address" phase.
        // The register value shall be (bit_num-1)
        ADD_BITFIELD_RW(reg_usr_addr_bitlen, 26, 6)
        // The length in bits of "write-data" phase.
        // The register value shall be (bit_num-1)
        ADD_BITFIELD_RW(reg_usr_mosi_bitlen, 17, 9)
        // The length in bits of "read-data" phase.
        // The register value shall be (bit_num-1)
        ADD_BITFIELD_RW(reg_usr_miso_bitlen, 8, 9)
        // The length in spi_clk cycles of "dummy" phase.
        // The register value shall be (cycle_num-1)
        ADD_BITFIELD_RW(reg_usr_dummy_cyclelen, 0, 8)
    END_TYPE()

    // The length in bits of "command" phase.
    // The register value shall be (bit_num-1)
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_USER2_t, uint32_t)
        // The length in bits of "command" phase.
        // The register value shall be (bit_num-1)
        ADD_BITFIELD_RW(reg_usr_command_bitlen, 28, 4)
        // The value of "command" phase
        ADD_BITFIELD_RW(reg_usr_command_value, 0, 16)
    END_TYPE()

    // In the slave mode, this register are the
    // status register for the master to write into.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_WR_STATUS_t, uint32_t)
        // In the slave mode, this register are the
        // status register for the master to write into.
        ADD_BITFIELD_RW(slv_wr_status, 0, 32)
    END_TYPE()

    // 1: disable CS2; 0: spi_cs signal is from/to CS2 pin
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_PIN_t, uint32_t)
        // 1: disable CS2; 0: spi_cs signal is from/to CS2 pin
        ADD_BITFIELD_RW(spi_cs2_dis, 2, 1)
        // 1: disable CS1; 0: spi_cs signal is from/to CS1 pin
        ADD_BITFIELD_RW(spi_cs1_dis, 1, 1)
        // 1: disable CS0; 0: spi_cs signal is from/to CS0 pin
        ADD_BITFIELD_RW(spi_cs0_dis, 0, 1)
    END_TYPE()

    // It is the synchronous reset signal of the module.
    // This bit is self-cleared by hardware.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_SLAVE_t, uint32_t)
        // It is the synchronous reset signal of the module.
        // This bit is self-cleared by hardware.
        ADD_BITFIELD_RW(spi_sync_reset, 31, 1)
        // 1: slave mode, 0: master mode.
        ADD_BITFIELD_RW(spi_slave_mode, 30, 1)
        // 1: slave mode commands are defined in SPI_SLAVE3.
        // 0: slave mode commands are fixed as
        // 1: "write-status"; 4: "read-status"; 2: "write-buffer" and 3: "read-buffer".
        ADD_BITFIELD_RW(slv_cmd_define, 27, 1)
        // The operations counter in both the master mode and the slave mode.
        ADD_BITFIELD_RO(spi_trans_cnt, 23, 4)
        // Interrupt enable bits for the below 5 sources
        ADD_BITFIELD_RW(spi_int_en, 5, 5)
        // The interrupt raw bit for the completement of any
        // operation in both the master mode and the slave mode.
        ADD_BITFIELD_RW(spi_trans_done, 4, 1)
        // The interrupt raw bit for the completement of
        // "write-status" operation in the slave mode.
        ADD_BITFIELD_RW(slv_wr_sta_done, 3, 1)
        // The interrupt raw bit for the completement of
        // "read-status" operation in the slave mode.
        ADD_BITFIELD_RW(slv_rd_sta_done, 2, 1)
        // The interrupt raw bit for the completement of
        // "write-buffer" operation in the slave mode.
        ADD_BITFIELD_RW(slv_wr_buf_done, 1, 1)
        // The interrupt raw bit for the completement of
        // "read-buffer" operation in the slave mode.
        ADD_BITFIELD_RW(slv_rd_buf_done, 0, 1)
    END_TYPE()

    // In the slave mode, it is the length in bits for "write-status"
    // and "read-status" operations. The register valueshall be (bit_num-1)
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_SLAVE1_t, uint32_t)
        // In the slave mode, it is the length in bits for "write-status"
        // and "read-status" operations. The register valueshall be (bit_num-1)
        ADD_BITFIELD_RW(slv_status_bitlen, 27, 5)
        // In the slave mode, it is the length in bits for "write-buffer"
        // and "read-buffer" operations. The register value shallbe (bit_num-1)
        ADD_BITFIELD_RW(slv_buf_bitlen, 16, 9)
        // In the slave mode, it is the address length in bits for "read-buffer"
        // operation. The register value shall be(bit_num-1)
        ADD_BITFIELD_RW(slv_rd_addr_bitlen, 10, 6)
        // In the slave mode, it is the address length in bits for "write-buffer"
        // operation. The register value shall be(bit_num-1)
        ADD_BITFIELD_RW(slv_wr_addr_bitlen, 4, 6)
        // In the slave mode, it is the enable bit of
        // "dummy" phase for "write-status" operations.
        ADD_BITFIELD_RW(slv_wrsta_dummy_en, 3, 1)
        // In the slave mode, it is the enable bit of
        // "dummy" phase for "read-status" operations.
        ADD_BITFIELD_RW(slv_rdsta_dummy_en, 2, 1)
        // In the slave mode, it is the enable bit of
        // "dummy" phase for "write-buffer" operations.
        ADD_BITFIELD_RW(slv_wrbuf_dummy_en, 1, 1)
        // In the slave mode, it is the enable bit of
        // "dummy" phase for "read-buffer" operations.
        ADD_BITFIELD_RW(slv_rdbuf_dummy_en, 0, 1)
    END_TYPE()

    // In the slave mode, it is the length in spi_clk cycles "dummy" phase
    // for "write-buffer" operations. The registervalue shall be (cycle_num-1)
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_SLAVE2_t, uint32_t)
        // In the slave mode, it is the length in spi_clk cycles "dummy" phase
        // for "write-buffer" operations. The registervalue shall be (cycle_num-1)
        ADD_BITFIELD_RW(slv_wrbuf_dummy_cyclelen, 24, 8)
        // In the slave mode, it is the length in spi_clk cycles of "dummy" phase
        // for "read-buffer" operations. The registervalue shall be (cycle_num-1)
        ADD_BITFIELD_RW(slv_rdbuf_dummy_cyclelen, 16, 8)
        // In the slave mode, it is the length in spi_clk cycles of "dummy" phase
        // for "write-status" operations. Theregister value shall be (cycle_num-1)
        ADD_BITFIELD_RW(slv_wrsta_dummy_cyclelen, 8, 8)
        // In the slave mode, it is the length in spi_clk cycles of "dummy" phase
        // for "read-status" operations. Theregister value shall be (cycle_num-1)
        ADD_BITFIELD_RW(slv_rdsta_dummy_cyclelen, 0, 8)
    END_TYPE()

    // In slave mode, it is the value of "write-status" command
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_SLAVE3_t, uint32_t)
        // In slave mode, it is the value of "write-status" command
        ADD_BITFIELD_RW(slv_wrsta_cmd_value, 24, 8)
        // In slave mode, it is the value of "read-status" command
        ADD_BITFIELD_RW(slv_rdsta_cmd_value, 16, 8)
        // In slave mode, it is the value of "write-buffer" command
        ADD_BITFIELD_RW(slv_wrbuf_cmd_value, 8, 8)
        // In slave mode, it is the value of "read-buffer" command
        ADD_BITFIELD_RW(slv_rdbuf_cmd_value, 0, 8)
    END_TYPE()

    // This register is for two SPI masters to share the same cs,
    // clock and data signals.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_EXT3_t, uint32_t)
        // This register is for two SPI masters to share the same cs,
        // clock and data signals.
        ADD_BITFIELD_RW(reg_int_hold_ena, 0, 2)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 0
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W0_t, uint32_t)
        // The data inside the buffer of the SPI module, word 0
        ADD_BITFIELD_RW(spi_w0, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 1
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W1_t, uint32_t)
        // The data inside the buffer of the SPI module, word 1
        ADD_BITFIELD_RW(spi_w1, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 2
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W2_t, uint32_t)
        // The data inside the buffer of the SPI module, word 2
        ADD_BITFIELD_RW(spi_w2, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 3
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W3_t, uint32_t)
        // The data inside the buffer of the SPI module, word 3
        ADD_BITFIELD_RW(spi_w3, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 4
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W4_t, uint32_t)
        // The data inside the buffer of the SPI module, word 4
        ADD_BITFIELD_RW(spi_w4, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 5
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W5_t, uint32_t)
        // The data inside the buffer of the SPI module, word 5
        ADD_BITFIELD_RW(spi_w5, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 6
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W6_t, uint32_t)
        // The data inside the buffer of the SPI module, word 6
        ADD_BITFIELD_RW(spi_w6, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 7
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W7_t, uint32_t)
        // The data inside the buffer of the SPI module, word 7
        ADD_BITFIELD_RW(spi_w7, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 8
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W8_t, uint32_t)
        // The data inside the buffer of the SPI module, word 8
        ADD_BITFIELD_RW(spi_w8, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 9
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W9_t, uint32_t)
        // The data inside the buffer of the SPI module, word 9
        ADD_BITFIELD_RW(spi_w9, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 10
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W10_t, uint32_t)
        // The data inside the buffer of the SPI module, word 10
        ADD_BITFIELD_RW(spi_w10, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 11
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W11_t, uint32_t)
        // The data inside the buffer of the SPI module, word 11
        ADD_BITFIELD_RW(spi_w11, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 12
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W12_t, uint32_t)
        // The data inside the buffer of the SPI module, word 12
        ADD_BITFIELD_RW(spi_w12, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 13
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W13_t, uint32_t)
        // The data inside the buffer of the SPI module, word 13
        ADD_BITFIELD_RW(spi_w13, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 14
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W14_t, uint32_t)
        // The data inside the buffer of the SPI module, word 14
        ADD_BITFIELD_RW(spi_w14, 0, 32)
    END_TYPE()

    // The data inside the buffer of the SPI module, word 15
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W15_t, uint32_t)
        // The data inside the buffer of the SPI module, word 15
        ADD_BITFIELD_RW(spi_w15, 0, 32)
    END_TYPE()

    struct SPI0_t {
        SPI_CMD_t                     SPI_CMD;
        SPI_ADDR_t                    SPI_ADDR;
        SPI_CTRL_t                    SPI_CTRL;
        uint32_t                      reserved0;
        SPI_RD_STATUS_t               SPI_RD_STATUS;
        SPI_CTRL2_t                   SPI_CTRL2;
        SPI_CLOCK_t                   SPI_CLOCK;
        SPI_USER_t                    SPI_USER;
        SPI_USER1_t                   SPI_USER1;
        SPI_USER2_t                   SPI_USER2;
        SPI_WR_STATUS_t               SPI_WR_STATUS;
        SPI_PIN_t                     SPI_PIN;
        SPI_SLAVE_t                   SPI_SLAVE;
        SPI_SLAVE1_t                  SPI_SLAVE1;
        SPI_SLAVE2_t                  SPI_SLAVE2;
        SPI_SLAVE3_t                  SPI_SLAVE3;
        SPI_W0_t                      SPI_W0;
        SPI_W1_t                      SPI_W1;
        SPI_W2_t                      SPI_W2;
        SPI_W3_t                      SPI_W3;
        SPI_W4_t                      SPI_W4;
        SPI_W5_t                      SPI_W5;
        SPI_W6_t                      SPI_W6;
        SPI_W7_t                      SPI_W7;
        SPI_W8_t                      SPI_W8;
        SPI_W9_t                      SPI_W9;
        SPI_W10_t                     SPI_W10;
        SPI_W11_t                     SPI_W11;
        SPI_W12_t                     SPI_W12;
        SPI_W13_t                     SPI_W13;
        SPI_W14_t                     SPI_W14;
        SPI_W15_t                     SPI_W15;
        uint32_t                      reserved1[31];
        SPI_EXT3_t                    SPI_EXT3;
    };

    static SPI0_t & SPI0     = (*(SPI0_t *)0x60000200);

} // _SPI0_

namespace _SPI1_  {

    // In the master mode, it is the start bit of a single operation.
    // Self-clear by hardware
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_CMD_t, uint32_t)
        // In the master mode, it is the start bit of a single operation.
        // Self-clear by hardware
        ADD_BITFIELD_RW(spi_usr, 18, 1)
    END_TYPE()

    // In the master mode, it is the value of address in "address" phase.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_ADDR_t, uint32_t)
        // In the master mode, it is the value of address in "address" phase.
        ADD_BITFIELD_RW(iodata_start_addr, 0, 32)
    END_TYPE()

    // SPI_CTRL
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_CTRL_t, uint32_t)
        // In "command", "address", "write-data" (MOSI) phases,
        // 1: LSB first; 0: MSB first
        ADD_BITFIELD_RW(spi_wr_bit_order, 26, 1)
        // In "read-data" (MISO) phase,
        // 1: LSB first; 0: MSB first
        ADD_BITFIELD_RW(spi_rd_bit_order, 25, 1)
        // In the read operations, "address" phase and "read-data" phase apply 4 signals
        ADD_BITFIELD_RW(spi_qio_mode, 24, 1)
        // In the read operations, "address" phase and "read-data" phase apply 2 signals
        ADD_BITFIELD_RW(spi_dio_mode, 23, 1)
        // In the read operations, "read-data" phase apply 4 signals
        ADD_BITFIELD_RW(spi_qout_mode, 20, 1)
        // In the read operations, "read-data" phase apply 2 signals
        ADD_BITFIELD_RW(spi_dout_mode, 14, 1)
        // this bit enable the bits: spi_qio_mode,
        // spi_dio_mode, spi_qout_mode and spi_dout_mode
        ADD_BITFIELD_RW(spi_fastrd_mode, 13, 1)
    END_TYPE()

    // In the slave mode, this register are the status register for the master to read out.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_RD_STATUS_t, uint32_t)
        // In the slave mode, this register are the
        // status register for the master to read  out.
        ADD_BITFIELD_RW(slv_rd_status, 0, 32)
    END_TYPE()

    // spi_cs signal is delayed by 80MHz clock cycles
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_CTRL2_t, uint32_t)
        // spi_cs signal is delayed by 80MHz clock cycles
        ADD_BITFIELD_RW(spi_cs_delay_num, 28, 4)
        // spi_cs signal is delayed by spi_clk.
        // 0: zero; 1: half cycle; 2: one cycle
        ADD_BITFIELD_RW(spi_cs_delay_mode, 26, 2)
        // MOSI signals are delayed by 80MHz clock cycles
        ADD_BITFIELD_RW(spi_mosi_delay_num, 23, 3)
        // MOSI signals are delayed by spi_clk.
        // 0: zero; 1: half cycle; 2: one cycle
        ADD_BITFIELD_RW(spi_mosi_delay_mode, 21, 2)
        // MISO signals are delayed by 80MHz clock cycles
        ADD_BITFIELD_RW(spi_miso_delay_num, 18, 3)
        // MISO signals are delayed by spi_clk.
        // 0: zero; 1: half cycle; 2: one cycle
        ADD_BITFIELD_RW(spi_miso_delay_mode, 16, 2)
    END_TYPE()

    // In the master mode,
    // 1: spi_clk is eqaul to 80MHz, 0: spi_clk is divided from 80 MHz clock.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_CLOCK_t, uint32_t)
        // In the master mode,
        // 1: spi_clk is eqaul to 80MHz, 0: spi_clk is divided from 80 MHz clock.
        ADD_BITFIELD_RW(spi_clk_equ_sysclk, 31, 1)
        // In the master mode, it is pre-divider of spi_clk.
        ADD_BITFIELD_RW(spi_clkdiv_pre, 18, 13)
        // In the master mode, it is the divider of spi_clk.
        // So spi_clk frequency is 80MHz/(spi_clkdiv_pre+1)/(spi_clkcnt_N+1)
        ADD_BITFIELD_RW(spi_clkcnt_N, 12, 6)
        // In the master mode, it must be floor((spi_clkcnt_N+1)/2-1).
        // In the slave mode, it must be 0.
        ADD_BITFIELD_RW(spi_clkcnt_H, 6, 6)
        // In the master mode, it must be eqaul to spi_clkcnt_N.
        // In the slave mode, it must be 0.
        ADD_BITFIELD_RW(spi_clkcnt_L, 0, 6)
    END_TYPE()

    // This bit enable the "command" phase of an operation.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_USER_t, uint32_t)
        // This bit enable the "command" phase of an operation.
        ADD_BITFIELD_RW(spi_usr_command, 31, 1)
        // This bit enable the "address" phase of an operation.
        ADD_BITFIELD_RW(spi_usr_addr, 30, 1)
        // This bit enable the "dummy" phase of an operation.
        ADD_BITFIELD_RW(spi_usr_dummy, 29, 1)
        // This bit enable the "read-data" phase of an operation.
        ADD_BITFIELD_RW(spi_usr_miso, 28, 1)
        // This bit enable the "write-data" phase of an operation.
        ADD_BITFIELD_RW(spi_usr_mosi, 27, 1)
        // 1: "write-data" phase only access to high-part of the buffer spi_w8~spi_w15
        ADD_BITFIELD_RW(reg_usr_mosi_highpart, 25, 1)
        // 1: "read-data" phase only access to high-part of the buffer spi_w8~spi_w15
        ADD_BITFIELD_RW(reg_usr_miso_highpart, 24, 1)
        // 1: mosi and miso signals share the same pin
        ADD_BITFIELD_RW(spi_sio, 16, 1)
        // In the write operations, "address" phase and
        // "read-data" phase apply 4 signals
        ADD_BITFIELD_RW(spi_fwrite_qio, 15, 1)
        // In the write operations, "address" phase
        // and "read-data" phase apply 2 signals
        ADD_BITFIELD_RW(spi_fwrite_dio, 14, 1)
        // In the write operations, "read-data" phase apply 4 signals
        ADD_BITFIELD_RW(spi_fwrite_quad, 13, 1)
        // In the write operations, "read-data" phase apply 2 signals
        ADD_BITFIELD_RW(spi_fwrite_dual, 12, 1)
        // In "command", "address", "write-data" (MOSI) phases,
        // 1: little-endian; 0: big_endian
        ADD_BITFIELD_RW(spi_wr_byte_order, 11, 1)
        // In "read-data" (MISO) phase,
        // 1: little-endian; 0: big_endian
        ADD_BITFIELD_RW(spi_rd_byte_order, 10, 1)
        // In the slave mode,
        // 1: rising-edge; 0: falling-edge
        ADD_BITFIELD_RW(spi_ck_i_edge, 6, 1)
    END_TYPE()

    // The length in bits of "address" phase.
    // The register value shall be (bit_num-1)
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_USER1_t, uint32_t)
        // The length in bits of "address" phase.
        // The register value shall be (bit_num-1)
        ADD_BITFIELD_RW(reg_usr_addr_bitlen, 26, 6)
        // The length in bits of "write-data" phase.
        // The register value shall be (bit_num-1)
        ADD_BITFIELD_RW(reg_usr_mosi_bitlen, 17, 9)
        // The length in bits of "read-data" phase.
        // The register value shall be (bit_num-1)
        ADD_BITFIELD_RW(reg_usr_miso_bitlen, 8, 9)
        // The length in spi_clk cycles of "dummy" phase.
        // The register value shall be (cycle_num-1)
        ADD_BITFIELD_RW(reg_usr_dummy_cyclelen, 0, 8)
    END_TYPE()

    // The length in bits of "command" phase.
    // The register value shall be (bit_num-1)
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_USER2_t, uint32_t)
        // The length in bits of "command" phase.
        // The register value shall be (bit_num-1)
        ADD_BITFIELD_RW(reg_usr_command_bitlen, 28, 4)
        // The value of "command" phase
        ADD_BITFIELD_RW(reg_usr_command_value, 0, 16)
    END_TYPE()

    // In the slave mode, this register are the
    // status register for the master to write into.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_WR_STATUS_t, uint32_t)
        // In the slave mode, this register are the
        // status register for the master to write into.
        ADD_BITFIELD_RW(slv_wr_status, 0, 32)
    END_TYPE()

    // 1: disable CS2; 0: spi_cs signal is from/to CS2 pin
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_PIN_t, uint32_t)
        // 1: disable CS2; 0: spi_cs signal is from/to CS2 pin
        ADD_BITFIELD_RW(spi_cs2_dis, 2, 1)
        // 1: disable CS1; 0: spi_cs signal is from/to CS1 pin
        ADD_BITFIELD_RW(spi_cs1_dis, 1, 1)
        // 1: disable CS0; 0: spi_cs signal is from/to CS0 pin
        ADD_BITFIELD_RW(spi_cs0_dis, 0, 1)
    END_TYPE()

    // It is the synchronous reset signal of the module.
    // This bit is self-cleared by hardware.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_SLAVE_t, uint32_t)
        // It is the synchronous reset signal of the module.
        // This bit is self-cleared by hardware.
        ADD_BITFIELD_RW(spi_sync_reset, 31, 1)
        // 1: slave mode, 0: master mode.
        ADD_BITFIELD_RW(spi_slave_mode, 30, 1)
        // 1: slave mode commands are defined in SPI_SLAVE3.
        // 0: slave mode commands are fixed as 1: "write-status";
        // 4: "read-status"; 2: "write-buffer" and 3: "read-buffer".
        ADD_BITFIELD_RW(slv_cmd_define, 27, 1)
        // The operations counter in both the master mode and the slave mode.
        ADD_BITFIELD_RO(spi_trans_cnt, 23, 4)
        // Interrupt enable bits for the below 5 sources
        ADD_BITFIELD_RW(spi_int_en, 5, 5)
        // The interrupt raw bit for the completement of any
        // operation in both the master mode and the slave mode.
        ADD_BITFIELD_RW(spi_trans_done, 4, 1)
        // The interrupt raw bit for the completement
        // of "write-status" operation in the slave mode.
        ADD_BITFIELD_RW(slv_wr_sta_done, 3, 1)
        // The interrupt raw bit for the completement
        // of "read-status" operation in the slave mode.
        ADD_BITFIELD_RW(slv_rd_sta_done, 2, 1)
        // The interrupt raw bit for the completement
        // of "write-buffer" operation in the slave mode.
        ADD_BITFIELD_RW(slv_wr_buf_done, 1, 1)
        // The interrupt raw bit for the completement
        // of "read-buffer" operation in the slave mode.
        ADD_BITFIELD_RW(slv_rd_buf_done, 0, 1)
    END_TYPE()

    // In the slave mode, it is the length in bits for "write-status"
    // and "read-status" operations. The register valueshall be (bit_num-1)
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_SLAVE1_t, uint32_t)
        // In the slave mode, it is the length in bits for "write-status"
        // and "read-status" operations. The register valueshall be (bit_num-1)
        ADD_BITFIELD_RW(slv_status_bitlen, 27, 5)
        // In the slave mode, it is the length in bits for "write-buffer"
        // and "read-buffer" operations. The register value shallbe (bit_num-1)
        ADD_BITFIELD_RW(slv_buf_bitlen, 16, 9)
        // In the slave mode, it is the address length in bits for "read-buffer"
        // operation. The register value shall be(bit_num-1)
        ADD_BITFIELD_RW(slv_rd_addr_bitlen, 10, 6)
        // In the slave mode, it is the address length in bits for "write-buffer"
        // operation. The register value shall be(bit_num-1)
        ADD_BITFIELD_RW(slv_wr_addr_bitlen, 4, 6)
        // In the slave mode, it is the enable bit
        // of "dummy" phase for "write-status" operations.
        ADD_BITFIELD_RW(slv_wrsta_dummy_en, 3, 1)
        // In the slave mode, it is the enable bit of "dummy" phase
        // for "read-status" operations.
        ADD_BITFIELD_RW(slv_rdsta_dummy_en, 2, 1)
        // In the slave mode, it is the enable bit of "dummy" phase
        // for "write-buffer" operations.
        ADD_BITFIELD_RW(slv_wrbuf_dummy_en, 1, 1)
        // In the slave mode, it is the enable bit of "dummy" phase
        // for "read-buffer" operations.
        ADD_BITFIELD_RW(slv_rdbuf_dummy_en, 0, 1)
    END_TYPE()

    // In the slave mode, it is the length in spi_clk cycles "dummy" phase
    // for "write-buffer" operations. The registervalue shall be (cycle_num-1)
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_SLAVE2_t, uint32_t)
        // In the slave mode, it is the length in spi_clk cycles "dummy" phase
        // for "write-buffer" operations. The registervalue shall be (cycle_num-1)
        ADD_BITFIELD_RW(slv_wrbuf_dummy_cyclelen, 24, 8)
        // In the slave mode, it is the length in spi_clk cycles of "dummy" phase
        // for "read-buffer" operations. The registervalue shall be (cycle_num-1)
        ADD_BITFIELD_RW(slv_rdbuf_dummy_cyclelen, 16, 8)
        // In the slave mode, it is the length in spi_clk cycles of "dummy" phase
        // for "write-status" operations. Theregister value shall be (cycle_num-1)
        ADD_BITFIELD_RW(slv_wrsta_dummy_cyclelen, 8, 8)
        // In the slave mode, it is the length in spi_clk cycles of "dummy" phase
        // for "read-status" operations. Theregister value shall be (cycle_num-1)
        ADD_BITFIELD_RW(slv_rdsta_dummy_cyclelen, 0, 8)
    END_TYPE()

    // In slave mode, it is the value of "write-status" command
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_SLAVE3_t, uint32_t)
        // In slave mode, it is the value of "write-status" command
        ADD_BITFIELD_RW(slv_wrsta_cmd_value, 24, 8)
        // In slave mode, it is the value of "read-status" command
        ADD_BITFIELD_RW(slv_rdsta_cmd_value, 16, 8)
        // In slave mode, it is the value of "write-buffer" command
        ADD_BITFIELD_RW(slv_wrbuf_cmd_value, 8, 8)
        // In slave mode, it is the value of "read-buffer" command
        ADD_BITFIELD_RW(slv_rdbuf_cmd_value, 0, 8)
    END_TYPE()

    // This register is for two SPI masters to share the same cs,
    // clock and data signals.
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_EXT3_t, uint32_t)
        // This register is for two SPI masters to share the same cs,
        // clock and data signals.
        ADD_BITFIELD_RW(reg_int_hold_ena, 0, 2)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 0
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W0_t, uint32_t)
        // the data inside the buffer of the SPI module, word 0
        ADD_BITFIELD_RW(spi_w0, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 1
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W1_t, uint32_t)
        // the data inside the buffer of the SPI module, word 1
        ADD_BITFIELD_RW(spi_w1, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 2
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W2_t, uint32_t)
        // the data inside the buffer of the SPI module, word 2
        ADD_BITFIELD_RW(spi_w2, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 3
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W3_t, uint32_t)
        // the data inside the buffer of the SPI module, word 3
        ADD_BITFIELD_RW(spi_w3, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 4
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W4_t, uint32_t)
        // the data inside the buffer of the SPI module, word 4
        ADD_BITFIELD_RW(spi_w4, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 5
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W5_t, uint32_t)
        // the data inside the buffer of the SPI module, word 5
        ADD_BITFIELD_RW(spi_w5, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 6
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W6_t, uint32_t)
        // the data inside the buffer of the SPI module, word 6
        ADD_BITFIELD_RW(spi_w6, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 7
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W7_t, uint32_t)
        // the data inside the buffer of the SPI module, word 7
        ADD_BITFIELD_RW(spi_w7, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 8
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W8_t, uint32_t)
        // the data inside the buffer of the SPI module, word 8
        ADD_BITFIELD_RW(spi_w8, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 9
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W9_t, uint32_t)
        // the data inside the buffer of the SPI module, word 9
        ADD_BITFIELD_RW(spi_w9, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 10
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W10_t, uint32_t)
        // the data inside the buffer of the SPI module, word 10
        ADD_BITFIELD_RW(spi_w10, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 11
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W11_t, uint32_t)
        // the data inside the buffer of the SPI module, word 11
        ADD_BITFIELD_RW(spi_w11, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 12
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W12_t, uint32_t)
        // the data inside the buffer of the SPI module, word 12
        ADD_BITFIELD_RW(spi_w12, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 13
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W13_t, uint32_t)
        // the data inside the buffer of the SPI module, word 13
        ADD_BITFIELD_RW(spi_w13, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 14
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W14_t, uint32_t)
        // the data inside the buffer of the SPI module, word 14
        ADD_BITFIELD_RW(spi_w14, 0, 32)
    END_TYPE()

    // the data inside the buffer of the SPI module, word 15
    // Reset value: 0x00000000
    BEGIN_TYPE(SPI_W15_t, uint32_t)
        // the data inside the buffer of the SPI module, word 15
        ADD_BITFIELD_RW(spi_w15, 0, 32)
    END_TYPE()

    struct SPI1_t {
        SPI_CMD_t                     SPI_CMD;
        SPI_ADDR_t                    SPI_ADDR;
        SPI_CTRL_t                    SPI_CTRL;
        uint32_t                      reserved0;
        SPI_RD_STATUS_t               SPI_RD_STATUS;
        SPI_CTRL2_t                   SPI_CTRL2;
        SPI_CLOCK_t                   SPI_CLOCK;
        SPI_USER_t                    SPI_USER;
        SPI_USER1_t                   SPI_USER1;
        SPI_USER2_t                   SPI_USER2;
        SPI_WR_STATUS_t               SPI_WR_STATUS;
        SPI_PIN_t                     SPI_PIN;
        SPI_SLAVE_t                   SPI_SLAVE;
        SPI_SLAVE1_t                  SPI_SLAVE1;
        SPI_SLAVE2_t                  SPI_SLAVE2;
        SPI_SLAVE3_t                  SPI_SLAVE3;
        SPI_W0_t                      SPI_W0;
        SPI_W1_t                      SPI_W1;
        SPI_W2_t                      SPI_W2;
        SPI_W3_t                      SPI_W3;
        SPI_W4_t                      SPI_W4;
        SPI_W5_t                      SPI_W5;
        SPI_W6_t                      SPI_W6;
        SPI_W7_t                      SPI_W7;
        SPI_W8_t                      SPI_W8;
        SPI_W9_t                      SPI_W9;
        SPI_W10_t                     SPI_W10;
        SPI_W11_t                     SPI_W11;
        SPI_W12_t                     SPI_W12;
        SPI_W13_t                     SPI_W13;
        SPI_W14_t                     SPI_W14;
        SPI_W15_t                     SPI_W15;
        uint32_t                      reserved1[31];
        SPI_EXT3_t                    SPI_EXT3;
    };

    static SPI1_t & SPI1     = (*(SPI1_t *)0x60000100);

} // _SPI1_

namespace _TIMER_  {

    // the load value into the counter
    // Reset value: 0x00000000
    BEGIN_TYPE(FRC1_LOAD_t, uint32_t)
        // the load value into the counter
        ADD_BITFIELD_RW(LOAD, 0, 23)
    END_TYPE()

    // the current value of the counter. It is a decreasingcounter.
    // Reset value: 0x00000000
    BEGIN_TYPE(FRC1_COUNT_t, uint32_t)
        // The current value of the counter. It is a decreasingcounter.
        ADD_BITFIELD_RO(COUNT, 0, 23)
    END_TYPE()

    // FRC1_CTRL
    // Reset value: 0x00000000
    BEGIN_TYPE(FRC1_CTRL_t, uint32_t)
        // Interrupt type, 0:edge, 1:level
        ADD_BITFIELD_RW(INT_TYPE, 0, 1)
        // Timer prescaler divider
        ADD_BITFIELD_RW(DIVIDER, 2, 2)
        // Automatically reload, when the counter is equal to zero
        ADD_BITFIELD_RW(RELOAD, 6, 1)
        // Timer enable
        ADD_BITFIELD_RW(ENABLE, 7, 1)
        // The status of the interrupt, when the count is deceased to zero
        ADD_BITFIELD_RO(INT_STATUS, 8, 1)
    END_TYPE()

    static const uint32_t FRC1_CTRL_INT_TYPE__EDGE = 0;
    static const uint32_t FRC1_CTRL_INT_TYPE__LEVEL = 1;
    static const uint32_t FRC1_CTRL_DIVIDER__1 = 0;
    static const uint32_t FRC1_CTRL_DIVIDER__16 = 1;
    static const uint32_t FRC1_CTRL_DIVIDER__256 = 2;

    // FRC1_INT
    // Reset value: 0x00000000
    BEGIN_TYPE(FRC1_INT_t, uint32_t)
        // write to clear the status of the interrupt, if theinterrupt type is "level"
        ADD_BITFIELD_RW(mask, 0, 1)
    END_TYPE()

    // the load value into the counter
    // Reset value: 0x00000000
    BEGIN_TYPE(FRC2_LOAD_t, uint32_t)
        // the load value into the counter
        ADD_BITFIELD_RW(LOAD, 0, 32)
    END_TYPE()

    // the current value of the counter. It is a increasingcounter.
    // Reset value: 0x00000000
    BEGIN_TYPE(FRC2_COUNT_t, uint32_t)
        // The current value of the counter. It is a increasingcounter.
        ADD_BITFIELD_RO(COUNT, 0, 32)
    END_TYPE()

    // FRC2_CTRL
    // Reset value: 0x00000000
    BEGIN_TYPE(FRC2_CTRL_t, uint32_t)
        // Interrupt type, 0:edge, 1:level
        ADD_BITFIELD_RW(INT_TYPE, 0, 1)
        // Timer prescaler divider
        ADD_BITFIELD_RW(DIVIDER, 2, 2)
        // Automatically reload, when the counter is equal to zero
        ADD_BITFIELD_RW(RELOAD, 6, 1)
        // Timer enable
        ADD_BITFIELD_RW(ENABLE, 7, 1)
        // The status of the interrupt, when the count is deceased to zero
        ADD_BITFIELD_RO(INT_STATUS, 8, 1)
    END_TYPE()

    static const uint32_t FRC2_CTRL_INT_TYPE__EDGE = 0;
    static const uint32_t FRC2_CTRL_INT_TYPE__LEVEL = 1;
    static const uint32_t FRC2_CTRL_DIVIDER__1 = 0;
    static const uint32_t FRC2_CTRL_DIVIDER__16 = 1;
    static const uint32_t FRC2_CTRL_DIVIDER__256 = 2;

    // FRC2_INT
    // Reset value: 0x00000000
    BEGIN_TYPE(FRC2_INT_t, uint32_t)
        // write to clear the status of the interrupt, if theinterrupt type is "level"
        ADD_BITFIELD_RW(mask, 0, 1)
    END_TYPE()

    // the alarm value for the counter
    // Reset value: 0x00000000
    BEGIN_TYPE(FRC2_ALARM_t, uint32_t)
        // the alarm value for the counter
        ADD_BITFIELD_RW(frc2_alarm, 0, 32)
    END_TYPE()

    struct TIMER_t {
        FRC1_LOAD_t                   FRC1_LOAD;
        FRC1_COUNT_t                  FRC1_COUNT;
        FRC1_CTRL_t                   FRC1_CTRL;
        FRC1_INT_t                    FRC1_INT;
        uint32_t                      reserved0[4];
        FRC2_LOAD_t                   FRC2_LOAD;
        FRC2_COUNT_t                  FRC2_COUNT;
        FRC2_CTRL_t                   FRC2_CTRL;
        FRC2_INT_t                    FRC2_INT;
        FRC2_ALARM_t                  FRC2_ALARM;
    };

    static TIMER_t & TIMER     = (*(TIMER_t *)0x60000600);

} // _TIMER_

namespace _UART0_  {

    // UART FIFO,length 128
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_FIFO_t, uint32_t)
        // R/W share the same address
        ADD_BITFIELD_RO(rxfifo_rd_byte, 0, 8)
    END_TYPE()

    // UART INTERRUPT RAW STATE
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_INT_RAW_t, uint32_t)
        // The interrupt raw bit for Rx time-out interrupt
        // (depends on the UART_RX_TOUT_THRHD)
        ADD_BITFIELD_RO(rxfifo_tout_int_raw, 8, 1)
        // The interrupt raw bit for Rx byte start error
        ADD_BITFIELD_RO(brk_det_int_raw, 7, 1)
        // The interrupt raw bit for CTS changing level
        ADD_BITFIELD_RO(cts_chg_int_raw, 6, 1)
        // The interrupt raw bit for DSR changing level
        ADD_BITFIELD_RO(dsr_chg_int_raw, 5, 1)
        // The interrupt raw bit for rx fifo overflow
        ADD_BITFIELD_RO(rxfifo_ovf_int_raw, 4, 1)
        // The interrupt raw bit for other rx error
        ADD_BITFIELD_RO(frm_err_int_raw, 3, 1)
        // The interrupt raw bit for parity check error
        ADD_BITFIELD_RO(parity_err_int_raw, 2, 1)
        // The interrupt raw bit for tx fifo empty interrupt
        // (depends on UART_TXFIFO_EMPTY_THRHD bits)
        ADD_BITFIELD_RO(txfifo_empty_int_raw, 1, 1)
        // The interrupt raw bit for rx fifo full interrupt
        // (depends on UART_RXFIFO_FULL_THRHD bits)
        ADD_BITFIELD_RO(rxfifo_full_int_raw, 0, 1)
    END_TYPE()

    // UART INTERRUPT STATEREGISTER UART_INT_RAW and UART_INT_ENA
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_INT_ST_t, uint32_t)
        // The interrupt state bit for Rx time-out event
        ADD_BITFIELD_RO(rxfifo_tout_int_st, 8, 1)
        // The interrupt state bit for rx byte start error
        ADD_BITFIELD_RO(brk_det_int_st, 7, 1)
        // The interrupt state bit for CTS changing level
        ADD_BITFIELD_RO(cts_chg_int_st, 6, 1)
        // The interrupt state bit for DSR changing level
        ADD_BITFIELD_RO(dsr_chg_int_st, 5, 1)
        // The interrupt state bit for RX fifo overflow
        ADD_BITFIELD_RO(rxfifo_ovf_int_st, 4, 1)
        // The interrupt state for other rx error
        ADD_BITFIELD_RO(frm_err_int_st, 3, 1)
        // The interrupt state bit for rx parity error
        ADD_BITFIELD_RO(parity_err_int_st, 2, 1)
        // The interrupt state bit for TX fifo empty
        ADD_BITFIELD_RO(txfifo_empty_int_st, 1, 1)
        // The interrupt state bit for RX fifo full event
        ADD_BITFIELD_RO(rxfifo_full_int_st, 0, 1)
    END_TYPE()

    // UART INTERRUPT ENABLE REGISTER
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_INT_ENA_t, uint32_t)
        // The interrupt enable bit for rx time-out interrupt
        ADD_BITFIELD_RW(rxfifo_tout_int_ena, 8, 1)
        // The interrupt enable bit for rx byte start error
        ADD_BITFIELD_RW(brk_det_int_ena, 7, 1)
        // The interrupt enable bit for CTS changing level
        ADD_BITFIELD_RW(cts_chg_int_ena, 6, 1)
        // The interrupt enable bit for DSR changing level
        ADD_BITFIELD_RW(dsr_chg_int_ena, 5, 1)
        // The interrupt enable bit for rx fifo overflow
        ADD_BITFIELD_RW(rxfifo_ovf_int_ena, 4, 1)
        // The interrupt enable bit for other rx error
        ADD_BITFIELD_RW(frm_err_int_ena, 3, 1)
        // The interrupt enable bit for parity error
        ADD_BITFIELD_RW(parity_err_int_ena, 2, 1)
        // The interrupt enable bit for tx fifo empty event
        ADD_BITFIELD_RW(txfifo_empty_int_ena, 1, 1)
        // The interrupt enable bit for rx fifo full event
        ADD_BITFIELD_RW(rxfifo_full_int_ena, 0, 1)
    END_TYPE()

    // UART INTERRUPT CLEAR REGISTER
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_INT_CLR_t, uint32_t)
        // Set this bit to clear the rx time-out interrupt
        ADD_BITFIELD_WO(rxfifo_tout_int_clr, 8, 1)
        // Set this bit to clear the rx byte start interrupt
        ADD_BITFIELD_WO(brk_det_int_clr, 7, 1)
        // Set this bit to clear the CTS changing interrupt
        ADD_BITFIELD_WO(cts_chg_int_clr, 6, 1)
        // Set this bit to clear the DSR changing interrupt
        ADD_BITFIELD_WO(dsr_chg_int_clr, 5, 1)
        // Set this bit to clear the rx fifo over-flow interrupt
        ADD_BITFIELD_WO(rxfifo_ovf_int_clr, 4, 1)
        // Set this bit to clear other rx error interrupt
        ADD_BITFIELD_WO(frm_err_int_clr, 3, 1)
        // Set this bit to clear the parity error interrupt
        ADD_BITFIELD_WO(parity_err_int_clr, 2, 1)
        // Set this bit to clear the tx fifo empty interrupt
        ADD_BITFIELD_WO(txfifo_empty_int_clr, 1, 1)
        // Set this bit to clear the rx fifo full interrupt
        ADD_BITFIELD_WO(rxfifo_full_int_clr, 0, 1)
    END_TYPE()

    // UART CLK DIV REGISTER
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_CLKDIV_t, uint32_t)
        // BAUDRATE = UART_CLK_FREQ / UART_CLKDIV
        ADD_BITFIELD_RW(uart_clkdiv, 0, 20)
    END_TYPE()

    // UART BAUDRATE DETECT REGISTER
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_AUTOBAUD_t, uint32_t)
        ADD_BITFIELD_RW(glitch_filt, 8, 8)
        // Set this bit to enable baudrate detect
        ADD_BITFIELD_RW(autobaud_en, 0, 1)
    END_TYPE()

    // UART STATUS REGISTER
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_STATUS_t, uint32_t)
        // The level of the uart txd pin
        ADD_BITFIELD_RO(txd, 31, 1)
        // The level of uart rts pin
        ADD_BITFIELD_RO(rtsn, 30, 1)
        // The level of uart dtr pin
        ADD_BITFIELD_RO(dtrn, 29, 1)
        // Number of data in UART TX fifo
        ADD_BITFIELD_RO(txfifo_cnt, 16, 8)
        // The level of uart rxd pin
        ADD_BITFIELD_RO(rxd, 15, 1)
        // The level of uart cts pin
        ADD_BITFIELD_RO(ctsn, 14, 1)
        // The level of uart dsr pin
        ADD_BITFIELD_RO(dsrn, 13, 1)
        // Number of data in uart rx fifo
        ADD_BITFIELD_RO(rxfifo_cnt, 0, 8)
    END_TYPE()

    // UART CONFIG0(UART0 and UART1)
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_CONF0_t, uint32_t)
        // Set this bit to inverse uart dtr level
        ADD_BITFIELD_RW(uart_dtr_inv, 24, 1)
        // Set this bit to inverse uart rts level
        ADD_BITFIELD_RW(uart_rts_inv, 23, 1)
        // Set this bit to inverse uart txd level
        ADD_BITFIELD_RW(uart_txd_inv, 22, 1)
        // Set this bit to inverse uart dsr level
        ADD_BITFIELD_RW(uart_dsr_inv, 21, 1)
        // Set this bit to inverse uart cts level
        ADD_BITFIELD_RW(uart_cts_inv, 20, 1)
        // Set this bit to inverse uart rxd level
        ADD_BITFIELD_RW(uart_rxd_inv, 19, 1)
        // Set this bit to reset uart tx fifo
        ADD_BITFIELD_RW(txfifo_rst, 18, 1)
        // Set this bit to reset uart rx fifo
        ADD_BITFIELD_RW(rxfifo_rst, 17, 1)
        // Set this bit to enable uart tx hardware flow control
        ADD_BITFIELD_RW(tx_flow_en, 15, 1)
        // Set this bit to enable uart loopback test mode
        ADD_BITFIELD_RW(uart_loopback, 14, 1)
        // RESERVED, DO NOT CHANGE THIS BIT
        ADD_BITFIELD_RW(txd_brk, 8, 1)
        // sw dtr
        ADD_BITFIELD_RW(sw_dtr, 7, 1)
        // sw rts
        ADD_BITFIELD_RW(sw_rts, 6, 1)
        // Set stop bit: 1:1bit 2:1.5bits 3:2bits
        ADD_BITFIELD_RW(stop_bit_num, 4, 2)
        // Set bit num: 0:5bits 1:6bits 2:7bits 3:8bits
        ADD_BITFIELD_RW(bit_num, 2, 2)
        // Set this bit to enable uart parity check
        ADD_BITFIELD_RW(parity_en, 1, 1)
        // Set parity check: 0:even 1:odd, UART CONFIG1
        ADD_BITFIELD_RW(parity, 0, 1)
    END_TYPE()

    // Set this bit to enable rx time-out function
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_CONF1_t, uint32_t)
        // Set this bit to enable rx time-out function
        ADD_BITFIELD_RW(rx_tout_en, 31, 1)
        // Config bits for rx time-out threshold,uint: byte,0-127
        ADD_BITFIELD_RW(rx_tout_thrhd, 24, 7)
        // Set this bit to enable rx hardware flow control
        ADD_BITFIELD_RW(rx_flow_en, 23, 1)
        // The config bits for rx flow control threshold,0-127
        ADD_BITFIELD_RW(rx_flow_thrhd, 16, 7)
        // The config bits for tx fifo empty threshold,0-127
        ADD_BITFIELD_RW(txfifo_empty_thrhd, 8, 7)
        // The config bits for rx fifo full threshold,0-127
        ADD_BITFIELD_RW(rxfifo_full_thrhd, 0, 7)
    END_TYPE()

    // UART_LOWPULSE
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_LOWPULSE_t, uint32_t)
        // used in baudrate detect
        ADD_BITFIELD_RO(lowpulse_min_cnt, 0, 20)
    END_TYPE()

    // UART_HIGHPULSE
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_HIGHPULSE_t, uint32_t)
        // used in baudrate detect
        ADD_BITFIELD_RO(highpulse_min_cnt, 0, 20)
    END_TYPE()

    // UART_RXD_CNT
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_RXD_CNT_t, uint32_t)
        // used in baudrate detect
        ADD_BITFIELD_RO(rxd_edge_cnt, 0, 10)
    END_TYPE()

    // UART HW INFO
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_DATE_t, uint32_t)
        // UART HW INFO
        ADD_BITFIELD_RW(uart_date, 0, 32)
    END_TYPE()

    // UART_ID
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_ID_t, uint32_t)
        ADD_BITFIELD_RW(uart_id, 0, 32)
    END_TYPE()

    struct UART0_t {
        UART_FIFO_t                   UART_FIFO;
        UART_INT_RAW_t                UART_INT_RAW;
        UART_INT_ST_t                 UART_INT_ST;
        UART_INT_ENA_t                UART_INT_ENA;
        UART_INT_CLR_t                UART_INT_CLR;
        UART_CLKDIV_t                 UART_CLKDIV;
        UART_AUTOBAUD_t               UART_AUTOBAUD;
        UART_STATUS_t                 UART_STATUS;
        UART_CONF0_t                  UART_CONF0;
        UART_CONF1_t                  UART_CONF1;
        UART_LOWPULSE_t               UART_LOWPULSE;
        UART_HIGHPULSE_t              UART_HIGHPULSE;
        UART_RXD_CNT_t                UART_RXD_CNT;
        uint32_t                      reserved0[17];
        UART_DATE_t                   UART_DATE;
        UART_ID_t                     UART_ID;
    };

    static UART0_t & UART0     = (*(UART0_t *)0x60000000);

} // _UART0_

namespace _UART1_  {

    // UART FIFO,length 128
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_FIFO_t, uint32_t)
        // R/W share the same address
        ADD_BITFIELD_RO(rxfifo_rd_byte, 0, 8)
    END_TYPE()

    // UART INTERRUPT RAW STATE
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_INT_RAW_t, uint32_t)
        // The interrupt raw bit for Rx time-out interrupt
        // (depends on the UART_RX_TOUT_THRHD)
        ADD_BITFIELD_RO(rxfifo_tout_int_raw, 8, 1)
        // The interrupt raw bit for Rx byte start error
        ADD_BITFIELD_RO(brk_det_int_raw, 7, 1)
        // The interrupt raw bit for CTS changing level
        ADD_BITFIELD_RO(cts_chg_int_raw, 6, 1)
        // The interrupt raw bit for DSR changing level
        ADD_BITFIELD_RO(dsr_chg_int_raw, 5, 1)
        // The interrupt raw bit for rx fifo overflow
        ADD_BITFIELD_RO(rxfifo_ovf_int_raw, 4, 1)
        // The interrupt raw bit for other rx error
        ADD_BITFIELD_RO(frm_err_int_raw, 3, 1)
        // The interrupt raw bit for parity check error
        ADD_BITFIELD_RO(parity_err_int_raw, 2, 1)
        // The interrupt raw bit for tx fifo empty interrupt(depands onUART_TXFIFO_EMPTY_THRHD bits)
        ADD_BITFIELD_RO(txfifo_empty_int_raw, 1, 1)
        // The interrupt raw bit for rx fifo full interrupt
        // (depends on UART_RXFIFO_FULL_THRHD bits)
        ADD_BITFIELD_RO(rxfifo_full_int_raw, 0, 1)
    END_TYPE()

    // UART INTERRUPT STATEREGISTERUART_INT_RAW and UART_INT_ENA
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_INT_ST_t, uint32_t)
        // The interrupt state bit for Rx time-out event
        ADD_BITFIELD_RO(rxfifo_tout_int_st, 8, 1)
        // The interrupt state bit for rx byte start error
        ADD_BITFIELD_RO(brk_det_int_st, 7, 1)
        // The interrupt state bit for CTS changing level
        ADD_BITFIELD_RO(cts_chg_int_st, 6, 1)
        // The interrupt state bit for DSR changing level
        ADD_BITFIELD_RO(dsr_chg_int_st, 5, 1)
        // The interrupt state bit for RX fifo overflow
        ADD_BITFIELD_RO(rxfifo_ovf_int_st, 4, 1)
        // The interrupt state for other rx error
        ADD_BITFIELD_RO(frm_err_int_st, 3, 1)
        // The interrupt state bit for rx parity error
        ADD_BITFIELD_RO(parity_err_int_st, 2, 1)
        // The interrupt state bit for TX fifo empty
        ADD_BITFIELD_RO(txfifo_empty_int_st, 1, 1)
        // The interrupt state bit for RX fifo full event
        ADD_BITFIELD_RO(rxfifo_full_int_st, 0, 1)
    END_TYPE()

    // UART INTERRUPT ENABLE REGISTER
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_INT_ENA_t, uint32_t)
        // The interrupt enable bit for rx time-out interrupt
        ADD_BITFIELD_RW(rxfifo_tout_int_ena, 8, 1)
        // The interrupt enable bit for rx byte start error
        ADD_BITFIELD_RW(brk_det_int_ena, 7, 1)
        // The interrupt enable bit for CTS changing level
        ADD_BITFIELD_RW(cts_chg_int_ena, 6, 1)
        // The interrupt enable bit for DSR changing level
        ADD_BITFIELD_RW(dsr_chg_int_ena, 5, 1)
        // The interrupt enable bit for rx fifo overflow
        ADD_BITFIELD_RW(rxfifo_ovf_int_ena, 4, 1)
        // The interrupt enable bit for other rx error
        ADD_BITFIELD_RW(frm_err_int_ena, 3, 1)
        // The interrupt enable bit for parity error
        ADD_BITFIELD_RW(parity_err_int_ena, 2, 1)
        // The interrupt enable bit for tx fifo empty event
        ADD_BITFIELD_RW(txfifo_empty_int_ena, 1, 1)
        // The interrupt enable bit for rx fifo full event
        ADD_BITFIELD_RW(rxfifo_full_int_ena, 0, 1)
    END_TYPE()

    // UART INTERRUPT CLEAR REGISTER
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_INT_CLR_t, uint32_t)
        // Set this bit to clear the rx time-out interrupt
        ADD_BITFIELD_WO(rxfifo_tout_int_clr, 8, 1)
        // Set this bit to clear the rx byte start interrupt
        ADD_BITFIELD_WO(brk_det_int_clr, 7, 1)
        // Set this bit to clear the CTS changing interrupt
        ADD_BITFIELD_WO(cts_chg_int_clr, 6, 1)
        // Set this bit to clear the DSR changing interrupt
        ADD_BITFIELD_WO(dsr_chg_int_clr, 5, 1)
        // Set this bit to clear the rx fifo over-flow interrupt
        ADD_BITFIELD_WO(rxfifo_ovf_int_clr, 4, 1)
        // Set this bit to clear other rx error interrupt
        ADD_BITFIELD_WO(frm_err_int_clr, 3, 1)
        // Set this bit to clear the parity error interrupt
        ADD_BITFIELD_WO(parity_err_int_clr, 2, 1)
        // Set this bit to clear the tx fifo empty interrupt
        ADD_BITFIELD_WO(txfifo_empty_int_clr, 1, 1)
        // Set this bit to clear the rx fifo full interrupt
        ADD_BITFIELD_WO(rxfifo_full_int_clr, 0, 1)
    END_TYPE()

    // UART CLK DIV REGISTER
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_CLKDIV_t, uint32_t)
        // BAUDRATE = UART_CLK_FREQ / UART_CLKDIV
        ADD_BITFIELD_RW(uart_clkdiv, 0, 20)
    END_TYPE()

    // UART BAUDRATE DETECT REGISTER
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_AUTOBAUD_t, uint32_t)
        ADD_BITFIELD_RW(glitch_filt, 8, 8)
        // Set this bit to enable baudrate detect
        ADD_BITFIELD_RW(autobaud_en, 0, 1)
    END_TYPE()

    // UART STATUS REGISTER
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_STATUS_t, uint32_t)
        // The level of the uart txd pin
        ADD_BITFIELD_RO(txd, 31, 1)
        // The level of uart rts pin
        ADD_BITFIELD_RO(rtsn, 30, 1)
        // The level of uart dtr pin
        ADD_BITFIELD_RO(dtrn, 29, 1)
        // Number of data in UART TX fifo
        ADD_BITFIELD_RO(txfifo_cnt, 16, 8)
        // The level of uart rxd pin
        ADD_BITFIELD_RO(rxd, 15, 1)
        // The level of uart cts pin
        ADD_BITFIELD_RO(ctsn, 14, 1)
        // The level of uart dsr pin
        ADD_BITFIELD_RO(dsrn, 13, 1)
        // Number of data in uart rx fifo
        ADD_BITFIELD_RO(rxfifo_cnt, 0, 8)
    END_TYPE()

    // UART CONFIG0(UART0 and UART1)
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_CONF0_t, uint32_t)
        // Set this bit to inverse uart dtr level
        ADD_BITFIELD_RW(uart_dtr_inv, 24, 1)
        // Set this bit to inverse uart rts level
        ADD_BITFIELD_RW(uart_rts_inv, 23, 1)
        // Set this bit to inverse uart txd level
        ADD_BITFIELD_RW(uart_txd_inv, 22, 1)
        // Set this bit to inverse uart dsr level
        ADD_BITFIELD_RW(uart_dsr_inv, 21, 1)
        // Set this bit to inverse uart cts level
        ADD_BITFIELD_RW(uart_cts_inv, 20, 1)
        // Set this bit to inverse uart rxd level
        ADD_BITFIELD_RW(uart_rxd_inv, 19, 1)
        // Set this bit to reset uart tx fifo
        ADD_BITFIELD_RW(txfifo_rst, 18, 1)
        // Set this bit to reset uart rx fifo
        ADD_BITFIELD_RW(rxfifo_rst, 17, 1)
        // Set this bit to enable uart tx hardware flow control
        ADD_BITFIELD_RW(tx_flow_en, 15, 1)
        // Set this bit to enable uart loopback test mode
        ADD_BITFIELD_RW(uart_loopback, 14, 1)
        // RESERVED, DO NOT CHANGE THIS BIT
        ADD_BITFIELD_RW(txd_brk, 8, 1)
        // sw dtr
        ADD_BITFIELD_RW(sw_dtr, 7, 1)
        // sw rts
        ADD_BITFIELD_RW(sw_rts, 6, 1)
        // Set stop bit: 1:1bit 2:1.5bits 3:2bits
        ADD_BITFIELD_RW(stop_bit_num, 4, 2)
        // Set bit num: 0:5bits 1:6bits 2:7bits 3:8bits
        ADD_BITFIELD_RW(bit_num, 2, 2)
        // Set this bit to enable uart parity check
        ADD_BITFIELD_RW(parity_en, 1, 1)
        // Set parity check: 0:even 1:odd, UART CONFIG1
        ADD_BITFIELD_RW(parity, 0, 1)
    END_TYPE()

    // Set this bit to enable rx time-out function
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_CONF1_t, uint32_t)
        // Set this bit to enable rx time-out function
        ADD_BITFIELD_RW(rx_tout_en, 31, 1)
        // Config bits for rx time-out threshold,uint: byte,0-127
        ADD_BITFIELD_RW(rx_tout_thrhd, 24, 7)
        // Set this bit to enable rx hardware flow control
        ADD_BITFIELD_RW(rx_flow_en, 23, 1)
        // The config bits for rx flow control threshold,0-127
        ADD_BITFIELD_RW(rx_flow_thrhd, 16, 7)
        // The config bits for tx fifo empty threshold,0-127
        ADD_BITFIELD_RW(txfifo_empty_thrhd, 8, 7)
        // The config bits for rx fifo full threshold,0-127
        ADD_BITFIELD_RW(rxfifo_full_thrhd, 0, 7)
    END_TYPE()

    // UART_LOWPULSE
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_LOWPULSE_t, uint32_t)
        // used in baudrate detect
        ADD_BITFIELD_RO(lowpulse_min_cnt, 0, 20)
    END_TYPE()

    // UART_HIGHPULSE
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_HIGHPULSE_t, uint32_t)
        // used in baudrate detect
        ADD_BITFIELD_RO(highpulse_min_cnt, 0, 20)
    END_TYPE()

    // UART_RXD_CNT
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_RXD_CNT_t, uint32_t)
        // used in baudrate detect
        ADD_BITFIELD_RO(rxd_edge_cnt, 0, 10)
    END_TYPE()

    // UART HW INFO
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_DATE_t, uint32_t)
        // UART HW INFO
        ADD_BITFIELD_RW(uart_date, 0, 32)
    END_TYPE()

    // UART_ID
    // Reset value: 0x00000000
    BEGIN_TYPE(UART_ID_t, uint32_t)
        ADD_BITFIELD_RW(uart_id, 0, 32)
    END_TYPE()

    struct UART1_t {
        UART_FIFO_t                   UART_FIFO;
        UART_INT_RAW_t                UART_INT_RAW;
        UART_INT_ST_t                 UART_INT_ST;
        UART_INT_ENA_t                UART_INT_ENA;
        UART_INT_CLR_t                UART_INT_CLR;
        UART_CLKDIV_t                 UART_CLKDIV;
        UART_AUTOBAUD_t               UART_AUTOBAUD;
        UART_STATUS_t                 UART_STATUS;
        UART_CONF0_t                  UART_CONF0;
        UART_CONF1_t                  UART_CONF1;
        UART_LOWPULSE_t               UART_LOWPULSE;
        UART_HIGHPULSE_t              UART_HIGHPULSE;
        UART_RXD_CNT_t                UART_RXD_CNT;
        uint32_t                      reserved0[17];
        UART_DATE_t                   UART_DATE;
        UART_ID_t                     UART_ID;
    };

    static UART1_t & UART1     = (*(UART1_t *)0x60000f00);

} // _UART1_

namespace _WDT_  {

    // WDT_CTL
    // Reset value: 0x00000000
    BEGIN_TYPE(WDT_CTL_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // WDT_OP
    // Reset value: 0x00000000
    BEGIN_TYPE(WDT_OP_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // WDT_OP_ND
    // Reset value: 0x00000000
    BEGIN_TYPE(WDT_OP_ND_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    // WDT_RST
    // Reset value: 0x00000000
    BEGIN_TYPE(WDT_RST_t, uint32_t)
        ADD_BITFIELD_RW(Register, 0, 32)
    END_TYPE()

    struct WDT_t {
        WDT_CTL_t                     WDT_CTL;
        WDT_OP_t                      WDT_OP;
        WDT_OP_ND_t                   WDT_OP_ND;
        uint32_t                      reserved0[2];
        WDT_RST_t                     WDT_RST;
    };

    static WDT_t & WDT     = (*(WDT_t *)0x60000900);

} // _WDT_

// Interrupt numbers

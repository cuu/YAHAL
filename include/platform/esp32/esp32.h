/*
 * esp32.h
 *
 *  Created on: 21.04.2018
 *      Author: aterstegge
 */

#ifndef ESP32_H_
#define ESP32_H_

#include <stdint.h>

#define __RO	const volatile
#define __WO	volatile
#define __RW	volatile

////////////////
// Memory layout
////////////////
#define PERI_BASE	((uint32_t)0x3ff00000)	// Base of all memory mapped peripherals

#define DPORT_BASE	    (PERI_BASE + 0x00000000)	// Base address of DPort Registers
#define AES_ACCEL_BASE	(PERI_BASE + 0x00001000)	// Base address of AES Accelerator
#define RSA_ACCEL_BASE	(PERI_BASE + 0x00002000)	// Base address of RSA Accelerator
#define SHA_ACCEL_BASE	(PERI_BASE + 0x00003000)	// Base address of SHA Accelerator
#define SEC_BOOT_BASE	(PERI_BASE + 0x00004000)	// Base address of Secure Boot
#define CACHE_MMU_BASE	(PERI_BASE + 0x00010000)	// Base address of Cache MMU Table
#define PID_CTRL_BASE	(PERI_BASE + 0x0001f000)	// Base address of PID Controller
#define UART0_BASE	    (PERI_BASE + 0x00040000)	// Base address of UART0
#define SPI1_BASE	    (PERI_BASE + 0x00042000)	// Base address of SPI1
#define SPI0_BASE	    (PERI_BASE + 0x00043000)	// Base address of SPI0
#define GPIO_BASE	    (PERI_BASE + 0x00044000)	// Base address of GPIO
#define RTC_BASE	    (PERI_BASE + 0x00048000)	// Base address of RTC
#define IO_MUX_BASE	    (PERI_BASE + 0x00049000)	// Base address of IO MUX
#define SDIO_SLV1_BASE	(PERI_BASE + 0x0004b000)	// Base address of SDIO Slave 1
#define UDMA1_BASE	    (PERI_BASE + 0x0004c000)	// Base address of UDMA1
#define I2S0_BASE	    (PERI_BASE + 0x0004f000)	// Base address of I2S0
#define UART1_BASE	    (PERI_BASE + 0x00050000)	// Base address of UART1
#define I2C0_BASE	    (PERI_BASE + 0x00053000)	// Base address of I2C0
#define UDMA0_BASE	    (PERI_BASE + 0x00054000)	// Base address of UDMA0
#define SDIO_SLV2_BASE	(PERI_BASE + 0x00055000)	// Base address of SDIO Slave 2
#define RMT_BASE	    (PERI_BASE + 0x00056000)	// Base address of RMT
#define PCNT_BASE	    (PERI_BASE + 0x00057000)	// Base address of PCNT
#define SDIO_SLV3_BASE	(PERI_BASE + 0x00058000)	// Base address of SDIO Slave 3
#define LED_PWM_BASE	(PERI_BASE + 0x00059000)	// Base address of LED PWM
#define EFUSE_BASE	    (PERI_BASE + 0x0005a000)	// Base address of Efuse Controller
#define FLASH_ENC_BASE	(PERI_BASE + 0x0005b000)	// Base address of Flash Encryption
#define PWM0_BASE	    (PERI_BASE + 0x0005e000)	// Base address of PWM0
#define TIMG0_BASE	    (PERI_BASE + 0x0005f000)	// Base address of TIMG0
#define TIMG1_BASE	    (PERI_BASE + 0x00060000)	// Base address of TIMG1
#define SPI2_BASE	    (PERI_BASE + 0x00064000)	// Base address of SPI2
#define SPI3_BASE	    (PERI_BASE + 0x00065000)	// Base address of SPI3
#define SYSCON_BASE	    (PERI_BASE + 0x00066000)	// Base address of SYSCON
#define I2C1_BASE	    (PERI_BASE + 0x00067000)	// Base address of I2C1
#define SDMMC_BASE	    (PERI_BASE + 0x00068000)	// Base address of SDMMC
#define EMAC_BASE	    (PERI_BASE + 0x00069000)	// Base address of EMAC
#define PWM1_BASE	    (PERI_BASE + 0x0006c000)	// Base address of PWM1
#define I2S1_BASE	    (PERI_BASE + 0x0006d000)	// Base address of I2S1
#define UART2_BASE	    (PERI_BASE + 0x0006e000)	// Base address of UART2
#define PWM2_BASE	    (PERI_BASE + 0x0006f000)	// Base address of PWM2
#define PWM3_BASE	    (PERI_BASE + 0x00070000)	// Base address of PWM3
#define RNG_BASE	    (PERI_BASE + 0x00075000)	// Base address of RNG


//////////////////////////////
// Helper templates and macros
//////////////////////////////
template <typename T, int Offset, int Bits>
struct BitFieldMember_RO
{
  private:
    T value;  // This is the value which is 'mirrored' by the union
    static const T max  = (T(1) << Bits) - T(1);

  public:
    inline operator T() const {
        return (value >> Offset) & max;
    }
};

template <typename T, int Offset, int Bits>
struct BitFieldMember_WO
{
  private:
    T value;  // This is the value which is 'mirrored' by the union
    static const T max  = (T(1) << Bits) - T(1);
    static const T mask = max << Offset;

  public:
    inline BitFieldMember_WO & operator=(T v) {
        value = (value & ~mask) | ((v & max) << Offset);
        return *this;
    }
};

template <typename T, int Offset, int Bits>
struct BitFieldMember_RW
{
  private:
    T value;  // This is the value which is 'mirrored' by the union
    static const T max  = (T(1) << Bits) - T(1);
    static const T mask = max << Offset;

  public:
    inline operator T() const {
        return (value >> Offset) & max;
    }
    inline BitFieldMember_RW & operator=(T v) {
        value = (value & ~mask) | ((v & max) << Offset);
        return *this;
    }
};

#define BEGIN_BITFIELD_TYPE(typeName, T) \
    union typeName \
    { \
        T value; \
        typeName& operator=(T v) {  value = v; return *this; } \
        operator T&()      { return value; } \
        operator T() const { return value; } \
        typedef  T StorageType;

#define ADD_BITFIELD_MEMBER_RO(memberName, offset, bits) \
        BitFieldMember_RO<StorageType, offset, bits> memberName;

#define ADD_BITFIELD_MEMBER_WO(memberName, offset, bits) \
        BitFieldMember_WO<StorageType, offset, bits> memberName;

#define ADD_BITFIELD_MEMBER_RW(memberName, offset, bits) \
        BitFieldMember_RW<StorageType, offset, bits> memberName;

#define END_BITFIELD_TYPE() \
    };

//////////////////////////////////
// SPI (SPI0, SPI1) definitions //
//////////////////////////////////

namespace _SPI_ {

	BEGIN_BITFIELD_TYPE(cmd_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(USR,			18, 1)
		ADD_BITFIELD_MEMBER_RW(HPM,			19, 1)
		ADD_BITFIELD_MEMBER_RW(RES,			20, 1)
		ADD_BITFIELD_MEMBER_RW(DP,			21, 1)
		ADD_BITFIELD_MEMBER_RW(CE,			22, 1)
		ADD_BITFIELD_MEMBER_RW(BE,			23, 1)
		ADD_BITFIELD_MEMBER_RW(SE,			24, 1)
		ADD_BITFIELD_MEMBER_RW(PP,			25, 1)
		ADD_BITFIELD_MEMBER_RW(WRSR,		26, 1)
		ADD_BITFIELD_MEMBER_RW(RDSR,		27, 1)
		ADD_BITFIELD_MEMBER_RW(RDID,		28, 1)
		ADD_BITFIELD_MEMBER_RW(WRDI,		29, 1)
		ADD_BITFIELD_MEMBER_RW(WREN,		30, 1)
		ADD_BITFIELD_MEMBER_RW(READ,		31, 1)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(ctrl_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(FASTRD,		13, 1)
		ADD_BITFIELD_MEMBER_RW(DOUT,		14, 1)
		ADD_BITFIELD_MEMBER_RW(RESANDRES,	15, 1)
		ADD_BITFIELD_MEMBER_RW(SSTAAI,		16, 1)
		ADD_BITFIELD_MEMBER_RW(AHB,			17, 1)
		ADD_BITFIELD_MEMBER_RW(HOLD,		18, 1)
		ADD_BITFIELD_MEMBER_RW(SHARE,		19, 1)
		ADD_BITFIELD_MEMBER_RW(QOUT,		20, 1)
		ADD_BITFIELD_MEMBER_RW(WPR,			21, 1)
		ADD_BITFIELD_MEMBER_RW(TWOBSE,		22, 1)
		ADD_BITFIELD_MEMBER_RW(DIO,			23, 1)
		ADD_BITFIELD_MEMBER_RW(QIO,			24, 1)
		ADD_BITFIELD_MEMBER_RW(RD_BO,		25, 1)
		ADD_BITFIELD_MEMBER_RW(WR_BO,		26, 1)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(ctrl1_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(BTL,			 0,16)
		ADD_BITFIELD_MEMBER_RW(TRES,		16,12)
		ADD_BITFIELD_MEMBER_RW(TCSH,		28, 4)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(status_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(BUSY,		 0, 1)
		ADD_BITFIELD_MEMBER_RW(WRE,			 1, 1)
		ADD_BITFIELD_MEMBER_RW(BP0,			 2, 1)
		ADD_BITFIELD_MEMBER_RW(BP1,			 3, 1)
		ADD_BITFIELD_MEMBER_RW(BP2,			 4, 1)
		ADD_BITFIELD_MEMBER_RW(TBP,			 5, 1)
		ADD_BITFIELD_MEMBER_RW(SP,			 7, 1)
		ADD_BITFIELD_MEMBER_RW(WB,			16, 8)
		ADD_BITFIELD_MEMBER_RW(EXT,			24, 8)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(ctrl2_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(ST,			 0, 4)
		ADD_BITFIELD_MEMBER_RW(HT,			 4, 4)
		ADD_BITFIELD_MEMBER_RW(CKOLM,		 8, 4)
		ADD_BITFIELD_MEMBER_RW(CKOHM,		12, 4)
		ADD_BITFIELD_MEMBER_RW(MISODM,		16, 2)
		ADD_BITFIELD_MEMBER_RW(MISODN,		18, 3)
		ADD_BITFIELD_MEMBER_RW(MOSIDM,		21, 2)
		ADD_BITFIELD_MEMBER_RW(MOSIDN,		23, 3)
		ADD_BITFIELD_MEMBER_RW(CSDM,		26, 2)
		ADD_BITFIELD_MEMBER_RW(CSDN,		28, 4)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(clock_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(CNT_L,		 0, 6)
		ADD_BITFIELD_MEMBER_RW(CNT_H,		 6, 6)
		ADD_BITFIELD_MEMBER_RW(CNT_N,		12, 6)
		ADD_BITFIELD_MEMBER_RW(DIVPRE,		18,13)
		ADD_BITFIELD_MEMBER_RW(EQU_SYSCLK,	31, 1)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(user_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(DUPLEX,		 0, 1)
		ADD_BITFIELD_MEMBER_RW(AHBUCMD4B,	 1, 1)
		ADD_BITFIELD_MEMBER_RW(AHBUCMD,		 3, 1)
		ADD_BITFIELD_MEMBER_RW(CSHOLD,		 4, 1)
		ADD_BITFIELD_MEMBER_RW(CSSETUP,		 5, 1)
		ADD_BITFIELD_MEMBER_RW(SSE,			 6, 1)
		ADD_BITFIELD_MEMBER_RW(SME,			 7, 1)
		ADD_BITFIELD_MEMBER_RW(AHBEM,		 8, 2)
		ADD_BITFIELD_MEMBER_RW(RDBYO,		10, 1)
		ADD_BITFIELD_MEMBER_RW(WRBYO,		11, 1)
		ADD_BITFIELD_MEMBER_RW(FWDUAL,		12, 1)
		ADD_BITFIELD_MEMBER_RW(FWQUAD,		13, 1)
		ADD_BITFIELD_MEMBER_RW(FWDIO,		14, 1)
		ADD_BITFIELD_MEMBER_RW(FWQIO,		15, 1)
		ADD_BITFIELD_MEMBER_RW(SIO,			16, 1)
		ADD_BITFIELD_MEMBER_RW(HOLDPOL,		17, 1)
		ADD_BITFIELD_MEMBER_RW(MOSIHOLD,	18, 1)
		ADD_BITFIELD_MEMBER_RW(MISOHOLD,	19, 1)
		ADD_BITFIELD_MEMBER_RW(DUMMYHOLD,	20, 1)
		ADD_BITFIELD_MEMBER_RW(ADDRHOLD,	21, 1)
		ADD_BITFIELD_MEMBER_RW(CMDHOLD,		22, 1)
		ADD_BITFIELD_MEMBER_RW(PREPHOLD,	23, 1)
		ADD_BITFIELD_MEMBER_RW(MISOH,		24, 1)
		ADD_BITFIELD_MEMBER_RW(MOSIH,		25, 1)
		ADD_BITFIELD_MEMBER_RW(DUMMYIDLE,	26, 1)
		ADD_BITFIELD_MEMBER_RW(MOSI,		27, 1)
		ADD_BITFIELD_MEMBER_RW(MISO,		28, 1)
		ADD_BITFIELD_MEMBER_RW(DUMMY,		29, 1)
		ADD_BITFIELD_MEMBER_RW(ADDR,		30, 1)
		ADD_BITFIELD_MEMBER_RW(COMMAND,		31, 1)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(user1_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(DUMMY_CYC,	 0, 8)
		ADD_BITFIELD_MEMBER_RW(MISO_LEN,	 8, 9)
		ADD_BITFIELD_MEMBER_RW(MOSI_LEN,	17, 9)
		ADD_BITFIELD_MEMBER_RW(ADDR_LEN,	26, 6)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(user2_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(CMD_VAL,	 	 0,16)
		ADD_BITFIELD_MEMBER_RW(CMD_LEN,		28, 4)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(pin_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(CS0_DIS,		 0, 1)
		ADD_BITFIELD_MEMBER_RW(CS1_DIS,		 1, 1)
		ADD_BITFIELD_MEMBER_RW(CS2_DIS,		 2, 1)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(slave_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(RD_BUF_DONE,	 0, 1)
		ADD_BITFIELD_MEMBER_RW(WR_BUF_DONE,	 1, 1)
		ADD_BITFIELD_MEMBER_RW(RD_STA_DONE,	 2, 1)
		ADD_BITFIELD_MEMBER_RW(WR_STA_DONE,	 3, 1)
		ADD_BITFIELD_MEMBER_RW(TRANS_DONE,	 4, 1)
		ADD_BITFIELD_MEMBER_RW(RD_BUF_IE,	 5, 1)
		ADD_BITFIELD_MEMBER_RW(WR_BUF_IE,	 6, 1)
		ADD_BITFIELD_MEMBER_RW(RD_STA_IE,	 7, 1)
		ADD_BITFIELD_MEMBER_RW(WR_STA_IE,	 8, 1)
		ADD_BITFIELD_MEMBER_RW(TRANS_IE,	 9, 1)
		ADD_BITFIELD_MEMBER_RW(CS_IM,		10, 2)
		ADD_BITFIELD_MEMBER_RW(SLV_LST_CMD,	17, 3)
		ADD_BITFIELD_MEMBER_RW(SLV_LST_ST,	20, 3)
		ADD_BITFIELD_MEMBER_RO(TRANS_CNT,	23, 4)
		ADD_BITFIELD_MEMBER_RW(CMD_DEFINE,	27, 1)
		ADD_BITFIELD_MEMBER_RW(WRRD_STA_EN,	28, 1)
		ADD_BITFIELD_MEMBER_RW(WRRD_BUF_EN,	29, 1)
		ADD_BITFIELD_MEMBER_RW(SLV_MODE,	30, 1)
		ADD_BITFIELD_MEMBER_RW(SYNC_RESET,	31, 1)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(slave1_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(RDB_DUM_EN,	 0, 1)
		ADD_BITFIELD_MEMBER_RW(WRB_DUM_EN,	 1, 1)
		ADD_BITFIELD_MEMBER_RW(RDS_DUM_EN,	 2, 1)
		ADD_BITFIELD_MEMBER_RW(WRS_DUM_EN,	 3, 1)
		ADD_BITFIELD_MEMBER_RW(WR_ADR_LEN,	 4, 6)
		ADD_BITFIELD_MEMBER_RW(RD_ADR_LEN,	10, 6)
		ADD_BITFIELD_MEMBER_RW(BUF_LEN,		16, 9)
		ADD_BITFIELD_MEMBER_RW(SLV_STAT_RD,	25, 9)
		ADD_BITFIELD_MEMBER_RW(SLV_STAT_FST,26, 9)
		ADD_BITFIELD_MEMBER_RW(STATUS_LEN,	27, 5)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(slave2_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(RDSTA_D_LEN,	 0, 8)
		ADD_BITFIELD_MEMBER_RW(WRSTA_D_LEN,	 8, 8)
		ADD_BITFIELD_MEMBER_RW(RDBUF_D_LEN,	18, 8)
		ADD_BITFIELD_MEMBER_RW(WRBUF_D_LEN,	24, 8)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(slave3_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(RDBUF_C_VAL,	 0, 8)
		ADD_BITFIELD_MEMBER_RW(WRBUF_C_VAL,	 8, 8)
		ADD_BITFIELD_MEMBER_RW(RDSTA_C_VAL,	18, 8)
		ADD_BITFIELD_MEMBER_RW(WRSTA_C_VAL,	24, 8)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(ext0_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(T_PP_TIME,	 0,12)
		ADD_BITFIELD_MEMBER_RW(T_PP_SHIFT,	16, 4)
		ADD_BITFIELD_MEMBER_RW(T_PP_ENA,	31, 1)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(ext1_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(T_ERA_TIME,	 0,12)
		ADD_BITFIELD_MEMBER_RW(T_ERA_SHIFT,	16, 4)
		ADD_BITFIELD_MEMBER_RW(T_ERA_ENA,	31, 1)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(ext2_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(SPI_ST,		 0, 3)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(ext3_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(INT_HOLD_ENA, 0, 2)
	END_BITFIELD_TYPE()

	struct Type {
				cmd_t		CMD;
		__RW	uint32_t	ADDR;
				ctrl_t		CTRL;
				ctrl1_t		CTRL1;
				status_t	RD_STATUS;
				ctrl2_t		CTRL2;
				clock_t		CLOCK;
				user_t		USER;
				user1_t		USER1;
				user2_t		USER2;
		__RW	uint32_t	WR_STATUS;
				pin_t		PIN;
				slave_t		SLAVE;
				slave1_t	SLAVE1;
				slave2_t	SLAVE2;
				slave3_t	SLAVE3;
		__RW	uint32_t	W[16];
		__RO	uint32_t	dummy[28];
				ext0_t		E0;
				ext1_t		E1;
				ext2_t		E2;
				ext3_t		E3;
	};
}

//_SPI_::Type & ESP_SPI0 = (*(_SPI_::Type *) SPI0_BASE);
//_SPI_::Type & ESP_SPI1 = (*(_SPI_::Type *) SPI1_BASE);

#define SPI0 (*(ESP_SPI::Type *) SPI0_BASE)
#define SPI1 (*(ESP_SPI::Type *) SPI1_BASE)

//////////////////////
// GPIO definitions //
//////////////////////

namespace _GPIO_ {

	BEGIN_BITFIELD_TYPE(out_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(DATA,	 0, 16)
		ADD_BITFIELD_MEMBER_RW(BT_SEL,	16, 16)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(enable_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(DATA,	 0, 16)
		ADD_BITFIELD_MEMBER_RW(SDIO_SEL,16,  6)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(in_t, uint32_t)
		ADD_BITFIELD_MEMBER_RO(DATA,	  	 0, 16)
		ADD_BITFIELD_MEMBER_RO(STRAPPING,	16, 16)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(pin_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(SOURCE,         0, 1)
		ADD_BITFIELD_MEMBER_RW(DRIVER,         2, 1)
		ADD_BITFIELD_MEMBER_RW(INT_TYPE,       7, 3)
		ADD_BITFIELD_MEMBER_RW(WAKEUP_ENABLE, 10, 1)
	END_BITFIELD_TYPE()

	// values for SOURCE
	const uint32_t SOURCE_GPIO        = 0;
	const uint32_t SOURCE_SIGMA_DELTA = 1;
	// values for DRIVER
	const uint32_t DRIVER_PUSH_PULL   = 0;
	const uint32_t DRIVER_OPEN_DRAIN  = 1;
	// values for INT_TYPE
	const uint32_t INT_DISABLE        = 0;
	const uint32_t INT_RAISING_EDGE   = 1;
	const uint32_t INT_FALLING_EDGE   = 2;
	const uint32_t INT_BOTH_EDGES     = 3;
	const uint32_t INT_LEVEL_LOW      = 4;
	const uint32_t INT_LEVEL_HIGH     = 5;

	BEGIN_BITFIELD_TYPE(sigmadelta_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(TARGET,		 0, 8)
		ADD_BITFIELD_MEMBER_RW(PRESCALE,	 8, 8)
		ADD_BITFIELD_MEMBER_RW(ENABLE,		16, 1)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(rtc_sync_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(PERIOD_NUM,	 0, 10)
		ADD_BITFIELD_MEMBER_RW(CALIB_START,	 31, 1)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(rtc_value_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(CALIB_VALUE,		 0, 20)
		ADD_BITFIELD_MEMBER_RW(CALIB_RDY_REAL,	30,  1)
		ADD_BITFIELD_MEMBER_RW(CALIB_RDY,		31,  1)
	END_BITFIELD_TYPE()

	struct Type {
				out_t			OUT;
		__WO	uint32_t		OUT_DATA_W1TS;
		__WO	uint32_t		OUT_DATA_W1TC;
				enable_t		ENABLE;
		__WO	uint32_t		ENABLE_W1TS;
		__WO	uint32_t		ENABLE_W1TC;
				in_t			IN;
		__RW	uint32_t		STATUS;
		__WO	uint32_t		STATUS_W1TS;
		__WO	uint32_t		STATUS_W1TC;
				pin_t			PIN[16];
				sigmadelta_t	SIGMA_DELTA;
				rtc_sync_t		RTC_CALIB_SYNC;
				rtc_value_t		RTC_CALIB_VALUE;
	};
}

//_GPIO_::Type & ESP_GPIO = (*(_GPIO_::Type *) GPIO_BASE);
#define ESP_GPIO (*(_GPIO_::Type *) GPIO_BASE)


////////////////////////////////////
// Timer (FRC1, FRC2) definitions //
////////////////////////////////////

namespace _FRC_ {

	BEGIN_BITFIELD_TYPE(frctrl_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(INT_TYPE,	0, 1)
		ADD_BITFIELD_MEMBER_RW(DIVIDER,		2, 2)
		ADD_BITFIELD_MEMBER_RW(RELOAD,		6, 1)
		ADD_BITFIELD_MEMBER_RW(ENABLE,		7, 1)
		ADD_BITFIELD_MEMBER_RO(INT_STATUS,	8, 1)
	END_BITFIELD_TYPE()

	// values for CTRL.INT_TYPE bitfield
	const uint32_t INT_TYPE_EDGE  = 0;
	const uint32_t INT_TYPE_LEVEL = 1;
	// values for CTRL.DIVIDER bitfield
	const uint32_t DIVIDER_1      = 0;
	const uint32_t DIVIDER_16     = 1;
	const uint32_t DIVIDER_256    = 2;
	// values for INT register
	const uint32_t INT_CLR        = 0;

	struct Type1 {
		__RW	uint32_t	LOAD;	// 23 bit value !
		__RO	uint32_t	COUNT;	// 23 bit value, default 0x7fffff
				frctrl_t	CTRL;
		__RW	uint32_t	INT;	// only 1 bit
	}; // __attribute__((packed));

	struct Type2 : public Type1 {
		__RW	uint32_t	ALARM;
	}; // __attribute__((packed));
}

//_FRC_::Type1 & ESP_FRC1 = (*(_FRC_::Type1 *) (FRC_BASE + 0x0000));
//_FRC_::Type2 & ESP_FRC2 = (*(_FRC_::Type2 *) (FRC_BASE + 0x0020));

#define ESP_FRC1 (*(_FRC_::Type1 *) (FRC_BASE + 0x0000))
#define ESP_FRC2 (*(_FRC_::Type2 *) (FRC_BASE + 0x0020))

namespace _IOMUX_ {

	BEGIN_BITFIELD_TYPE(conf_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(SPI0CLK_EQU_SYSCLK,	8, 1)
		ADD_BITFIELD_MEMBER_RW(SPI1CLK_EQU_SYSCLK,	9, 1)
	END_BITFIELD_TYPE()

	BEGIN_BITFIELD_TYPE(mux_t, uint32_t)
		ADD_BITFIELD_MEMBER_RW(OE,				0, 1)
		ADD_BITFIELD_MEMBER_RW(SLEEP_OE,		1, 1)
		ADD_BITFIELD_MEMBER_RW(SLEEP_PULLDOWN,	2, 1)
		ADD_BITFIELD_MEMBER_RW(SLEEP_PULLUP,	3, 1)
		ADD_BITFIELD_MEMBER_RW(PULLDOWN,		6, 1)
		ADD_BITFIELD_MEMBER_RW(PULLUP,			7, 1)
		ADD_BITFIELD_MEMBER_RW(FUNC,		   19, 4)
	END_BITFIELD_TYPE()

	const static uint32_t GPIO_TO_IOMUX[] = { 12,5,13,4,14,15,6,7,8,9,10,11,0,1,2,3 };

	struct Type {
				conf_t			CONF;
				mux_t			ENTRY[16];

		mux_t & operator() (int gpio) {
			return ENTRY[ GPIO_TO_IOMUX[gpio] ];
		}
	};
}

//_IOMUX_::Type & ESP_IOMUX = (*(_IOMUX_::Type *) IOMUX_BASE);

#define ESP_IOMUX (*(_IOMUX_::Type *) IOMUX_BASE)

#endif /* ESP8266EX_H_ */

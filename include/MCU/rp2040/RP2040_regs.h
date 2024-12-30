///////////////////////////////////////////////////////////////////////////
// This file was generated with svd2cpp, source file was RP2040_regs.svd
// DO NOT EDIT - CHANGES MIGHT BE OVERWRITTEN !!
///////////////////////////////////////////////////////////////////////////
//
#include "bitfield_defs.h"

// vendor: Raspberry Pi
// name: RP2040
// version: 0.1
// description: 
// Dual-core Arm Cortex-M0+ processor, flexible clock running up to 133 MHz
// 264KB on-chip SRAM
// 2 x UART, 2 x SPI controllers, 2 x I2C controllers, 16 x PWM channels
// 1 x USB 1.1 controller and PHY, with host and device support
// 8 x Programmable I/O (PIO) state machines for custom peripheral support
// Supported input power 1.8-5.5V DC
// Operating temperature -20C to +85C
// Drag-and-drop programming using mass storage over USB
// Low-power sleep and dormant modes
// Accurate on-chip clock
// Temperature sensor
// Accelerated integer and floating-point libraries on-chip
// licenseText: 
// Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
// 
// SPDX-License-Identifier: BSD-3-Clause
// cpu
//     name: CM0PLUS
//     revision: r0p1
//     endian: little
//     mpuPresent: true
//     fpuPresent: false
//     vtorPresent: 1
//     nvicPrioBits: 2
//     vendorSystickConfig: false
//     deviceNumInterrupts: 26
// addressUnitBits: 8
// width: 32

// QSPI flash execute-in-place block
namespace _XIP_CTRL_  {

    // Cache control
    // Reset value: 0x00000003
    BEGIN_TYPE(CTRL_t, uint32_t)
        // When 1, the cache memories are powered down. They retain state,
        // but can not be accessed. This reduces static power dissipation.
        // Writing 1 to this bit forces CTRL_EN to 0, i.e. the cache cannot
        // be enabled when powered down.
        // Cache-as-SRAM accesses will produce a bus error response when
        // the cache is powered down.
        ADD_BITFIELD_RW(POWER_DOWN, 3, 1)
        // When 1, writes to any alias other than 0x0 (caching, allocating)
        // will produce a bus fault. When 0, these writes are silently ignored.
        // In either case, writes to the 0x0 alias will deallocate on tag match,
        // as usual.
        ADD_BITFIELD_RW(ERR_BADWRITE, 1, 1)
        // When 1, enable the cache. When the cache is disabled, all XIP accesses
        // will go straight to the flash, without querying the cache. When enabled,
        // cacheable XIP accesses will query the cache, and the flash will
        // not be accessed if the tag matches and the valid bit is set.
        // 
        // If the cache is enabled, cache-as-SRAM accesses have no effect on the
        // cache data RAM, and will produce a bus error response.
        ADD_BITFIELD_RW(EN, 0, 1)
    END_TYPE()

    // Cache Flush control
    // Reset value: 0x00000000
    BEGIN_TYPE(FLUSH_t, uint32_t)
        // Write 1 to flush the cache. This clears the tag memory, but
        // the data memory retains its contents. (This means cache-as-SRAM
        // contents is not affected by flush or reset.)
        // Reading will hold the bus (stall the processor) until the flush
        // completes. Alternatively STAT can be polled until completion.
        ADD_BITFIELD_RW(FLUSH, 0, 1)
    END_TYPE()

    // Cache Status
    // Reset value: 0x00000002
    BEGIN_TYPE(STAT_t, uint32_t)
        // When 1, indicates the XIP streaming FIFO is completely full.
        // The streaming FIFO is 2 entries deep, so the full and empty
        // flag allow its level to be ascertained.
        ADD_BITFIELD_RO(FIFO_FULL, 2, 1)
        // When 1, indicates the XIP streaming FIFO is completely empty.
        ADD_BITFIELD_RO(FIFO_EMPTY, 1, 1)
        // Reads as 0 while a cache flush is in progress, and 1 otherwise.
        // The cache is flushed whenever the XIP block is reset, and also
        // when requested via the FLUSH register.
        ADD_BITFIELD_RO(FLUSH_READY, 0, 1)
    END_TYPE()

    // Cache Hit counter
    // A 32 bit saturating counter that increments upon each cache hit,
    // i.e. when an XIP access is serviced directly from cached data.
    // Write any value to clear.
    // Reset value: 0x00000000
    typedef uint32_t CTR_HIT_t;

    // Cache Access counter
    // A 32 bit saturating counter that increments upon each XIP access,
    // whether the cache is hit or not. This includes noncacheable accesses.
    // Write any value to clear.
    // Reset value: 0x00000000
    typedef uint32_t CTR_ACC_t;

    // FIFO stream address
    // Reset value: 0x00000000
    BEGIN_TYPE(STREAM_ADDR_t, uint32_t)
        // The address of the next word to be streamed from flash to the streaming FIFO.
        // Increments automatically after each flash access.
        // Write the initial access address here before starting a streaming read.
        ADD_BITFIELD_RW(STREAM_ADDR, 2, 30)
    END_TYPE()

    // FIFO stream control
    // Reset value: 0x00000000
    BEGIN_TYPE(STREAM_CTR_t, uint32_t)
        // Write a nonzero value to start a streaming read. This will then
        // progress in the background, using flash idle cycles to transfer
        // a linear data block from flash to the streaming FIFO.
        // Decrements automatically (1 at a time) as the stream
        // progresses, and halts on reaching 0.
        // Write 0 to halt an in-progress stream, and discard any in-flight
        // read, so that a new stream can immediately be started (after
        // draining the FIFO and reinitialising STREAM_ADDR)
        ADD_BITFIELD_RW(STREAM_CTR, 0, 22)
    END_TYPE()

    // FIFO stream data
    // Streamed data is buffered here, for retrieval by the system DMA.
    // This FIFO can also be accessed via the XIP_AUX slave, to avoid exposing
    // the DMA to bus stalls caused by other XIP traffic.
    // Reset value: 0x00000000
    typedef uint32_t STREAM_FIFO_t;

    struct XIP_CTRL_t {
        CTRL_t                        CTRL;
        FLUSH_t                       FLUSH;
        STAT_t                        STAT;
        CTR_HIT_t                     CTR_HIT;
        CTR_ACC_t                     CTR_ACC;
        STREAM_ADDR_t                 STREAM_ADDR;
        STREAM_CTR_t                  STREAM_CTR;
        STREAM_FIFO_t                 STREAM_FIFO;
    };

    static XIP_CTRL_t & XIP_CTRL = (*(XIP_CTRL_t *)0x14000000);
    static XIP_CTRL_t & XIP_CTRL_XOR = (*(XIP_CTRL_t *)0x14001000);
    static XIP_CTRL_t & XIP_CTRL_SET = (*(XIP_CTRL_t *)0x14002000);
    static XIP_CTRL_t & XIP_CTRL_CLR = (*(XIP_CTRL_t *)0x14003000);

} // _XIP_CTRL_

// DW_apb_ssi has the following features:
// * APB interface - Allows for easy integration into a DesignWare Synthesizable Components for AMBA 2 implementation.
// * APB3 and APB4 protocol support.
// * Scalable APB data bus width - Supports APB data bus widths of 8, 16, and 32 bits.
// * Serial-master or serial-slave operation - Enables serial communication with serial-master or serial-slave peripheral devices.
// * Programmable Dual/Quad/Octal SPI support in Master Mode.
// * Dual Data Rate (DDR) and Read Data Strobe (RDS) Support - Enables the DW_apb_ssi master to perform operations with the device in DDR and RDS modes when working in Dual/Quad/Octal mode of operation.
// * Data Mask Support - Enables the DW_apb_ssi to selectively update the bytes in the device. This feature is applicable only in enhanced SPI modes.
// * eXecute-In-Place (XIP) support - Enables the DW_apb_ssi master to behave as a memory mapped I/O and fetches the data from the device based on the APB read request. This feature is applicable only in enhanced SPI modes.
// * DMA Controller Interface - Enables the DW_apb_ssi to interface to a DMA controller over the bus using a handshaking interface for transfer requests.
// * Independent masking of interrupts - Master collision, transmit FIFO overflow, transmit FIFO empty, receive FIFO full, receive FIFO underflow, and receive FIFO overflow interrupts can all be masked independently.
// * Multi-master contention detection - Informs the processor of multiple serial-master accesses on the serial bus.
// * Bypass of meta-stability flip-flops for synchronous clocks - When the APB clock (pclk) and the DW_apb_ssi serial clock (ssi_clk) are synchronous, meta-stable flip-flops are not used when transferring control signals across these clock domains.
// * Programmable delay on the sample time of the received serial data bit (rxd); enables programmable control of routing delays resulting in higher serial data-bit rates.
// * Programmable features:
// - Serial interface operation - Choice of Motorola SPI, Texas Instruments Synchronous Serial Protocol or National Semiconductor Microwire.
// - Clock bit-rate - Dynamic control of the serial bit rate of the data transfer; used in only serial-master mode of operation.
// - Data Item size (4 to 32 bits) - Item size of each data transfer under the control of the programmer.
// * Configured features:
// - FIFO depth - 16 words deep. The FIFO width is fixed at 32 bits.
// - 1 slave select output.
// - Hardware slave-select - Dedicated hardware slave-select line.
// - Combined interrupt line - one combined interrupt line from the DW_apb_ssi to the interrupt controller.
// - Interrupt polarity - active high interrupt lines.
// - Serial clock polarity - low serial-clock polarity directly after reset.
// - Serial clock phase - capture on first edge of serial-clock directly after reset.
namespace _XIP_SSI_  {

    // Control register 0
    // Reset value: 0x00000000
    BEGIN_TYPE(CTRLR0_t, uint32_t)
        // Slave select toggle enable
        ADD_BITFIELD_RW(SSTE, 24, 1)
        // SPI frame format
        ADD_BITFIELD_RW(SPI_FRF, 21, 2)
        // Data frame size in 32b transfer mode
        // Value of n -> n+1 clocks per frame.
        ADD_BITFIELD_RW(DFS_32, 16, 5)
        // Control frame size
        // Value of n -> n+1 clocks per frame.
        ADD_BITFIELD_RW(CFS, 12, 4)
        // Shift register loop (test mode)
        ADD_BITFIELD_RW(SRL, 11, 1)
        // Slave output enable
        ADD_BITFIELD_RW(SLV_OE, 10, 1)
        // Transfer mode
        ADD_BITFIELD_RW(TMOD, 8, 2)
        // Serial clock polarity
        ADD_BITFIELD_RW(SCPOL, 7, 1)
        // Serial clock phase
        ADD_BITFIELD_RW(SCPH, 6, 1)
        // Frame format
        ADD_BITFIELD_RW(FRF, 4, 2)
        // Data frame size
        ADD_BITFIELD_RW(DFS, 0, 4)
    END_TYPE()

    // Standard 1-bit SPI frame format; 1 bit per SCK, full-duplex
    static const uint32_t CTRLR0_SPI_FRF__STD = 0;
    // Dual-SPI frame format; two bits per SCK, half-duplex
    static const uint32_t CTRLR0_SPI_FRF__DUAL = 1;
    // Quad-SPI frame format; four bits per SCK, half-duplex
    static const uint32_t CTRLR0_SPI_FRF__QUAD = 2;
    // Both transmit and receive
    static const uint32_t CTRLR0_TMOD__TX_AND_RX = 0;
    // Transmit only (not for FRF == 0, standard SPI mode)
    static const uint32_t CTRLR0_TMOD__TX_ONLY = 1;
    // Receive only (not for FRF == 0, standard SPI mode)
    static const uint32_t CTRLR0_TMOD__RX_ONLY = 2;
    // EEPROM read mode (TX then RX; RX starts after control data TX'd)
    static const uint32_t CTRLR0_TMOD__EEPROM_READ = 3;

    // Master Control register 1
    // Reset value: 0x00000000
    BEGIN_TYPE(CTRLR1_t, uint32_t)
        // Number of data frames
        ADD_BITFIELD_RW(NDF, 0, 16)
    END_TYPE()

    // SSI Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(SSIENR_t, uint32_t)
        // SSI enable
        ADD_BITFIELD_RW(SSI_EN, 0, 1)
    END_TYPE()

    // Microwire Control
    // Reset value: 0x00000000
    BEGIN_TYPE(MWCR_t, uint32_t)
        // Microwire handshaking
        ADD_BITFIELD_RW(MHS, 2, 1)
        // Microwire control
        ADD_BITFIELD_RW(MDD, 1, 1)
        // Microwire transfer mode
        ADD_BITFIELD_RW(MWMOD, 0, 1)
    END_TYPE()

    // Slave enable
    // Reset value: 0x00000000
    BEGIN_TYPE(SER_t, uint32_t)
        // For each bit:
        // 0 -> slave not selected
        // 1 -> slave selected
        ADD_BITFIELD_RW(SER, 0, 1)
    END_TYPE()

    // Baud rate
    // Reset value: 0x00000000
    BEGIN_TYPE(BAUDR_t, uint32_t)
        // SSI clock divider
        ADD_BITFIELD_RW(SCKDV, 0, 16)
    END_TYPE()

    // TX FIFO threshold level
    // Reset value: 0x00000000
    BEGIN_TYPE(TXFTLR_t, uint32_t)
        // Transmit FIFO threshold
        ADD_BITFIELD_RW(TFT, 0, 8)
    END_TYPE()

    // RX FIFO threshold level
    // Reset value: 0x00000000
    BEGIN_TYPE(RXFTLR_t, uint32_t)
        // Receive FIFO threshold
        ADD_BITFIELD_RW(RFT, 0, 8)
    END_TYPE()

    // TX FIFO level
    // Reset value: 0x00000000
    BEGIN_TYPE(TXFLR_t, uint32_t)
        // Transmit FIFO level
        ADD_BITFIELD_RO(TFTFL, 0, 8)
    END_TYPE()

    // RX FIFO level
    // Reset value: 0x00000000
    BEGIN_TYPE(RXFLR_t, uint32_t)
        // Receive FIFO level
        ADD_BITFIELD_RO(RXTFL, 0, 8)
    END_TYPE()

    // Status register
    // Reset value: 0x00000000
    BEGIN_TYPE(SR_t, uint32_t)
        // Data collision error
        ADD_BITFIELD_RO(DCOL, 6, 1)
        // Transmission error
        ADD_BITFIELD_RO(TXE, 5, 1)
        // Receive FIFO full
        ADD_BITFIELD_RO(RFF, 4, 1)
        // Receive FIFO not empty
        ADD_BITFIELD_RO(RFNE, 3, 1)
        // Transmit FIFO empty
        ADD_BITFIELD_RO(TFE, 2, 1)
        // Transmit FIFO not full
        ADD_BITFIELD_RO(TFNF, 1, 1)
        // SSI busy flag
        ADD_BITFIELD_RO(BUSY, 0, 1)
    END_TYPE()

    // Interrupt mask
    // Reset value: 0x00000000
    BEGIN_TYPE(IMR_t, uint32_t)
        // Multi-master contention interrupt mask
        ADD_BITFIELD_RW(MSTIM, 5, 1)
        // Receive FIFO full interrupt mask
        ADD_BITFIELD_RW(RXFIM, 4, 1)
        // Receive FIFO overflow interrupt mask
        ADD_BITFIELD_RW(RXOIM, 3, 1)
        // Receive FIFO underflow interrupt mask
        ADD_BITFIELD_RW(RXUIM, 2, 1)
        // Transmit FIFO overflow interrupt mask
        ADD_BITFIELD_RW(TXOIM, 1, 1)
        // Transmit FIFO empty interrupt mask
        ADD_BITFIELD_RW(TXEIM, 0, 1)
    END_TYPE()

    // Interrupt status
    // Reset value: 0x00000000
    BEGIN_TYPE(ISR_t, uint32_t)
        // Multi-master contention interrupt status
        ADD_BITFIELD_RO(MSTIS, 5, 1)
        // Receive FIFO full interrupt status
        ADD_BITFIELD_RO(RXFIS, 4, 1)
        // Receive FIFO overflow interrupt status
        ADD_BITFIELD_RO(RXOIS, 3, 1)
        // Receive FIFO underflow interrupt status
        ADD_BITFIELD_RO(RXUIS, 2, 1)
        // Transmit FIFO overflow interrupt status
        ADD_BITFIELD_RO(TXOIS, 1, 1)
        // Transmit FIFO empty interrupt status
        ADD_BITFIELD_RO(TXEIS, 0, 1)
    END_TYPE()

    // Raw interrupt status
    // Reset value: 0x00000000
    BEGIN_TYPE(RISR_t, uint32_t)
        // Multi-master contention raw interrupt status
        ADD_BITFIELD_RO(MSTIR, 5, 1)
        // Receive FIFO full raw interrupt status
        ADD_BITFIELD_RO(RXFIR, 4, 1)
        // Receive FIFO overflow raw interrupt status
        ADD_BITFIELD_RO(RXOIR, 3, 1)
        // Receive FIFO underflow raw interrupt status
        ADD_BITFIELD_RO(RXUIR, 2, 1)
        // Transmit FIFO overflow raw interrupt status
        ADD_BITFIELD_RO(TXOIR, 1, 1)
        // Transmit FIFO empty raw interrupt status
        ADD_BITFIELD_RO(TXEIR, 0, 1)
    END_TYPE()

    // TX FIFO overflow interrupt clear
    // Reset value: 0x00000000
    BEGIN_TYPE(TXOICR_t, uint32_t)
        // Clear-on-read transmit FIFO overflow interrupt
        ADD_BITFIELD_RO(TXOICR, 0, 1)
    END_TYPE()

    // RX FIFO overflow interrupt clear
    // Reset value: 0x00000000
    BEGIN_TYPE(RXOICR_t, uint32_t)
        // Clear-on-read receive FIFO overflow interrupt
        ADD_BITFIELD_RO(RXOICR, 0, 1)
    END_TYPE()

    // RX FIFO underflow interrupt clear
    // Reset value: 0x00000000
    BEGIN_TYPE(RXUICR_t, uint32_t)
        // Clear-on-read receive FIFO underflow interrupt
        ADD_BITFIELD_RO(RXUICR, 0, 1)
    END_TYPE()

    // Multi-master interrupt clear
    // Reset value: 0x00000000
    BEGIN_TYPE(MSTICR_t, uint32_t)
        // Clear-on-read multi-master contention interrupt
        ADD_BITFIELD_RO(MSTICR, 0, 1)
    END_TYPE()

    // Interrupt clear
    // Reset value: 0x00000000
    BEGIN_TYPE(ICR_t, uint32_t)
        // Clear-on-read all active interrupts
        ADD_BITFIELD_RO(ICR, 0, 1)
    END_TYPE()

    // DMA control
    // Reset value: 0x00000000
    BEGIN_TYPE(DMACR_t, uint32_t)
        // Transmit DMA enable
        ADD_BITFIELD_RW(TDMAE, 1, 1)
        // Receive DMA enable
        ADD_BITFIELD_RW(RDMAE, 0, 1)
    END_TYPE()

    // DMA TX data level
    // Reset value: 0x00000000
    BEGIN_TYPE(DMATDLR_t, uint32_t)
        // Transmit data watermark level
        ADD_BITFIELD_RW(DMATDL, 0, 8)
    END_TYPE()

    // DMA RX data level
    // Reset value: 0x00000000
    BEGIN_TYPE(DMARDLR_t, uint32_t)
        // Receive data watermark level (DMARDLR+1)
        ADD_BITFIELD_RW(DMARDL, 0, 8)
    END_TYPE()

    // Identification register
    // Reset value: 0x51535049
    BEGIN_TYPE(IDR_t, uint32_t)
        // Peripheral dentification code
        ADD_BITFIELD_RO(IDCODE, 0, 32)
    END_TYPE()

    // Version ID
    // Reset value: 0x3430312a
    BEGIN_TYPE(SSI_VERSION_ID_t, uint32_t)
        // SNPS component version (format X.YY)
        ADD_BITFIELD_RO(SSI_COMP_VERSION, 0, 32)
    END_TYPE()

    // Data Register 0 (of 36)
    // Reset value: 0x00000000
    BEGIN_TYPE(DR0_t, uint32_t)
        // First data register of 36
        ADD_BITFIELD_RW(DR, 0, 32)
    END_TYPE()

    // RX sample delay
    // Reset value: 0x00000000
    BEGIN_TYPE(RX_SAMPLE_DLY_t, uint32_t)
        // RXD sample delay (in SCLK cycles)
        ADD_BITFIELD_RW(RSD, 0, 8)
    END_TYPE()

    // SPI control
    // Reset value: 0x03000000
    BEGIN_TYPE(SPI_CTRLR0_t, uint32_t)
        // SPI Command to send in XIP mode (INST_L = 8-bit) or to append to Address (INST_L = 0-bit)
        ADD_BITFIELD_RW(XIP_CMD, 24, 8)
        // Read data strobe enable
        ADD_BITFIELD_RW(SPI_RXDS_EN, 18, 1)
        // Instruction DDR transfer enable
        ADD_BITFIELD_RW(INST_DDR_EN, 17, 1)
        // SPI DDR transfer enable
        ADD_BITFIELD_RW(SPI_DDR_EN, 16, 1)
        // Wait cycles between control frame transmit and data reception (in SCLK cycles)
        ADD_BITFIELD_RW(WAIT_CYCLES, 11, 5)
        // Instruction length (0/4/8/16b)
        ADD_BITFIELD_RW(INST_L, 8, 2)
        // Address length (0b-60b in 4b increments)
        ADD_BITFIELD_RW(ADDR_L, 2, 4)
        // Address and instruction transfer format
        ADD_BITFIELD_RW(TRANS_TYPE, 0, 2)
    END_TYPE()

    // No instruction
    static const uint32_t SPI_CTRLR0_INST_L__NONE = 0;
    // 4-bit instruction
    static const uint32_t SPI_CTRLR0_INST_L__4B = 1;
    // 8-bit instruction
    static const uint32_t SPI_CTRLR0_INST_L__8B = 2;
    // 16-bit instruction
    static const uint32_t SPI_CTRLR0_INST_L__16B = 3;
    // Command and address both in standard SPI frame format
    static const uint32_t SPI_CTRLR0_TRANS_TYPE__1C1A = 0;
    // Command in standard SPI format, address in format specified by FRF
    static const uint32_t SPI_CTRLR0_TRANS_TYPE__1C2A = 1;
    // Command and address both in format specified by FRF (e.g. Dual-SPI)
    static const uint32_t SPI_CTRLR0_TRANS_TYPE__2C2A = 2;

    // TX drive edge
    // Reset value: 0x00000000
    BEGIN_TYPE(TXD_DRIVE_EDGE_t, uint32_t)
        // TXD drive edge
        ADD_BITFIELD_RW(TDE, 0, 8)
    END_TYPE()

    struct XIP_SSI_t {
        CTRLR0_t                      CTRLR0;
        CTRLR1_t                      CTRLR1;
        SSIENR_t                      SSIENR;
        MWCR_t                        MWCR;
        SER_t                         SER;
        BAUDR_t                       BAUDR;
        TXFTLR_t                      TXFTLR;
        RXFTLR_t                      RXFTLR;
        TXFLR_t                       TXFLR;
        RXFLR_t                       RXFLR;
        SR_t                          SR;
        IMR_t                         IMR;
        ISR_t                         ISR;
        RISR_t                        RISR;
        TXOICR_t                      TXOICR;
        RXOICR_t                      RXOICR;
        RXUICR_t                      RXUICR;
        MSTICR_t                      MSTICR;
        ICR_t                         ICR;
        DMACR_t                       DMACR;
        DMATDLR_t                     DMATDLR;
        DMARDLR_t                     DMARDLR;
        IDR_t                         IDR;
        SSI_VERSION_ID_t              SSI_VERSION_ID;
        DR0_t                         DR0;
        uint32_t                      reserved0[35];
        RX_SAMPLE_DLY_t               RX_SAMPLE_DLY;
        SPI_CTRLR0_t                  SPI_CTRLR0;
        TXD_DRIVE_EDGE_t              TXD_DRIVE_EDGE;
    };

    static XIP_SSI_t & XIP_SSI = (*(XIP_SSI_t *)0x18000000);
    static XIP_SSI_t & XIP_SSI_XOR = (*(XIP_SSI_t *)0x18001000);
    static XIP_SSI_t & XIP_SSI_SET = (*(XIP_SSI_t *)0x18002000);
    static XIP_SSI_t & XIP_SSI_CLR = (*(XIP_SSI_t *)0x18003000);

} // _XIP_SSI_

namespace _SYSINFO_  {

    // JEDEC JEP-106 compliant chip identifier.
    // Reset value: 0x00000000
    BEGIN_TYPE(CHIP_ID_t, uint32_t)
        ADD_BITFIELD_RO(REVISION, 28, 4)
        ADD_BITFIELD_RO(PART, 12, 16)
        ADD_BITFIELD_RO(MANUFACTURER, 0, 12)
    END_TYPE()

    // Platform register. Allows software to know what environment it is running in.
    // Reset value: 0x00000000
    BEGIN_TYPE(PLATFORM_t, uint32_t)
        ADD_BITFIELD_RO(ASIC, 1, 1)
        ADD_BITFIELD_RO(FPGA, 0, 1)
    END_TYPE()

    // Git hash of the chip source. Used to identify chip version.
    // Reset value: 0x00000000
    typedef uint32_t GITREF_RP2040_t;

    struct SYSINFO_t {
        CHIP_ID_t                     CHIP_ID;
        PLATFORM_t                    PLATFORM;
        uint32_t                      reserved0[14];
        GITREF_RP2040_t               GITREF_RP2040;
    };

    static SYSINFO_t & SYSINFO = (*(SYSINFO_t *)0x40000000);
    static SYSINFO_t & SYSINFO_XOR = (*(SYSINFO_t *)0x40001000);
    static SYSINFO_t & SYSINFO_SET = (*(SYSINFO_t *)0x40002000);
    static SYSINFO_t & SYSINFO_CLR = (*(SYSINFO_t *)0x40003000);

} // _SYSINFO_

// Register block for various chip control signals
namespace _SYSCFG_  {

    // Processor core 0 NMI source mask
    // Set a bit high to enable NMI from that IRQ
    // Reset value: 0x00000000
    typedef uint32_t PROC0_NMI_MASK_t;

    // Processor core 1 NMI source mask
    // Set a bit high to enable NMI from that IRQ
    // Reset value: 0x00000000
    typedef uint32_t PROC1_NMI_MASK_t;

    // Configuration for processors
    // Reset value: 0x10000000
    BEGIN_TYPE(PROC_CONFIG_t, uint32_t)
        // Configure proc1 DAP instance ID.
        // Recommend that this is NOT changed until you require debug access in multi-chip environment
        // WARNING: do not set to 15 as this is reserved for RescueDP
        ADD_BITFIELD_RW(PROC1_DAP_INSTID, 28, 4)
        // Configure proc0 DAP instance ID.
        // Recommend that this is NOT changed until you require debug access in multi-chip environment
        // WARNING: do not set to 15 as this is reserved for RescueDP
        ADD_BITFIELD_RW(PROC0_DAP_INSTID, 24, 4)
        // Indication that proc1 has halted
        ADD_BITFIELD_RO(PROC1_HALTED, 1, 1)
        // Indication that proc0 has halted
        ADD_BITFIELD_RO(PROC0_HALTED, 0, 1)
    END_TYPE()

    // For each bit, if 1, bypass the input synchronizer between that GPIO
    // and the GPIO input register in the SIO. The input synchronizers should
    // generally be unbypassed, to avoid injecting metastabilities into processors.
    // If you're feeling brave, you can bypass to save two cycles of input
    // latency. This register applies to GPIO 0...29.
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC_IN_SYNC_BYPASS_t, uint32_t)
        ADD_BITFIELD_RW(PROC_IN_SYNC_BYPASS, 0, 30)
    END_TYPE()

    // For each bit, if 1, bypass the input synchronizer between that GPIO
    // and the GPIO input register in the SIO. The input synchronizers should
    // generally be unbypassed, to avoid injecting metastabilities into processors.
    // If you're feeling brave, you can bypass to save two cycles of input
    // latency. This register applies to GPIO 30...35 (the QSPI IOs).
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC_IN_SYNC_BYPASS_HI_t, uint32_t)
        ADD_BITFIELD_RW(PROC_IN_SYNC_BYPASS_HI, 0, 6)
    END_TYPE()

    // Directly control the SWD debug port of either processor
    // Reset value: 0x00000066
    BEGIN_TYPE(DBGFORCE_t, uint32_t)
        // Attach processor 1 debug port to syscfg controls, and disconnect it from external SWD pads.
        ADD_BITFIELD_RW(PROC1_ATTACH, 7, 1)
        // Directly drive processor 1 SWCLK, if PROC1_ATTACH is set
        ADD_BITFIELD_RW(PROC1_SWCLK, 6, 1)
        // Directly drive processor 1 SWDIO input, if PROC1_ATTACH is set
        ADD_BITFIELD_RW(PROC1_SWDI, 5, 1)
        // Observe the value of processor 1 SWDIO output.
        ADD_BITFIELD_RO(PROC1_SWDO, 4, 1)
        // Attach processor 0 debug port to syscfg controls, and disconnect it from external SWD pads.
        ADD_BITFIELD_RW(PROC0_ATTACH, 3, 1)
        // Directly drive processor 0 SWCLK, if PROC0_ATTACH is set
        ADD_BITFIELD_RW(PROC0_SWCLK, 2, 1)
        // Directly drive processor 0 SWDIO input, if PROC0_ATTACH is set
        ADD_BITFIELD_RW(PROC0_SWDI, 1, 1)
        // Observe the value of processor 0 SWDIO output.
        ADD_BITFIELD_RO(PROC0_SWDO, 0, 1)
    END_TYPE()

    // Control power downs to memories. Set high to power down memories.
    // Use with extreme caution
    // Reset value: 0x00000000
    BEGIN_TYPE(MEMPOWERDOWN_t, uint32_t)
        ADD_BITFIELD_RW(ROM, 7, 1)
        ADD_BITFIELD_RW(USB, 6, 1)
        ADD_BITFIELD_RW(SRAM5, 5, 1)
        ADD_BITFIELD_RW(SRAM4, 4, 1)
        ADD_BITFIELD_RW(SRAM3, 3, 1)
        ADD_BITFIELD_RW(SRAM2, 2, 1)
        ADD_BITFIELD_RW(SRAM1, 1, 1)
        ADD_BITFIELD_RW(SRAM0, 0, 1)
    END_TYPE()

    struct SYSCFG_t {
        PROC0_NMI_MASK_t              PROC0_NMI_MASK;
        PROC1_NMI_MASK_t              PROC1_NMI_MASK;
        PROC_CONFIG_t                 PROC_CONFIG;
        PROC_IN_SYNC_BYPASS_t         PROC_IN_SYNC_BYPASS;
        PROC_IN_SYNC_BYPASS_HI_t      PROC_IN_SYNC_BYPASS_HI;
        DBGFORCE_t                    DBGFORCE;
        MEMPOWERDOWN_t                MEMPOWERDOWN;
    };

    static SYSCFG_t & SYSCFG = (*(SYSCFG_t *)0x40004000);
    static SYSCFG_t & SYSCFG_XOR = (*(SYSCFG_t *)0x40005000);
    static SYSCFG_t & SYSCFG_SET = (*(SYSCFG_t *)0x40006000);
    static SYSCFG_t & SYSCFG_CLR = (*(SYSCFG_t *)0x40007000);

} // _SYSCFG_

namespace _CLOCKS_  {

    // Clock control, can be changed on-the-fly (except for auxsrc)
    // Reset value: 0x00000000
    BEGIN_TYPE(CLK_GPOUT0_CTRL_t, uint32_t)
        // An edge on this signal shifts the phase of the output by 1 cycle of the input clock
        // This can be done at any time
        ADD_BITFIELD_RW(NUDGE, 20, 1)
        // This delays the enable signal by up to 3 cycles of the input clock
        // This must be set before the clock is enabled to have any effect
        ADD_BITFIELD_RW(PHASE, 16, 2)
        // Enables duty cycle correction for odd divisors
        ADD_BITFIELD_RW(DC50, 12, 1)
        // Starts and stops the clock generator cleanly
        ADD_BITFIELD_RW(ENABLE, 11, 1)
        // Asynchronously kills the clock generator
        ADD_BITFIELD_RW(KILL, 10, 1)
        // Selects the auxiliary clock source, will glitch when switching
        ADD_BITFIELD_RW(AUXSRC, 5, 4)
    END_TYPE()

    static const uint32_t CLK_GPOUT0_CTRL_AUXSRC__clksrc_pll_sys = 0;
    static const uint32_t CLK_GPOUT0_CTRL_AUXSRC__clksrc_gpin0 = 1;
    static const uint32_t CLK_GPOUT0_CTRL_AUXSRC__clksrc_gpin1 = 2;
    static const uint32_t CLK_GPOUT0_CTRL_AUXSRC__clksrc_pll_usb = 3;
    static const uint32_t CLK_GPOUT0_CTRL_AUXSRC__rosc_clksrc = 4;
    static const uint32_t CLK_GPOUT0_CTRL_AUXSRC__xosc_clksrc = 5;
    static const uint32_t CLK_GPOUT0_CTRL_AUXSRC__clk_sys = 6;
    static const uint32_t CLK_GPOUT0_CTRL_AUXSRC__clk_usb = 7;
    static const uint32_t CLK_GPOUT0_CTRL_AUXSRC__clk_adc = 8;
    static const uint32_t CLK_GPOUT0_CTRL_AUXSRC__clk_rtc = 9;
    static const uint32_t CLK_GPOUT0_CTRL_AUXSRC__clk_ref = 10;

    // Clock divisor, can be changed on-the-fly
    // Reset value: 0x00000100
    BEGIN_TYPE(CLK_GPOUT0_DIV_t, uint32_t)
        // Integer component of the divisor, 0 -> divide by 2^16
        ADD_BITFIELD_RW(INT, 8, 24)
        // Fractional component of the divisor
        ADD_BITFIELD_RW(FRAC, 0, 8)
    END_TYPE()

    // Indicates which SRC is currently selected by the glitchless mux (one-hot).
    // This slice does not have a glitchless mux (only the AUX_SRC field is present, not SRC) so this register is hardwired to 0x1.
    // Reset value: 0x00000001
    typedef uint32_t CLK_GPOUT0_SELECTED_t;

    // Clock control, can be changed on-the-fly (except for auxsrc)
    // Reset value: 0x00000000
    BEGIN_TYPE(CLK_GPOUT1_CTRL_t, uint32_t)
        // An edge on this signal shifts the phase of the output by 1 cycle of the input clock
        // This can be done at any time
        ADD_BITFIELD_RW(NUDGE, 20, 1)
        // This delays the enable signal by up to 3 cycles of the input clock
        // This must be set before the clock is enabled to have any effect
        ADD_BITFIELD_RW(PHASE, 16, 2)
        // Enables duty cycle correction for odd divisors
        ADD_BITFIELD_RW(DC50, 12, 1)
        // Starts and stops the clock generator cleanly
        ADD_BITFIELD_RW(ENABLE, 11, 1)
        // Asynchronously kills the clock generator
        ADD_BITFIELD_RW(KILL, 10, 1)
        // Selects the auxiliary clock source, will glitch when switching
        ADD_BITFIELD_RW(AUXSRC, 5, 4)
    END_TYPE()

    static const uint32_t CLK_GPOUT1_CTRL_AUXSRC__clksrc_pll_sys = 0;
    static const uint32_t CLK_GPOUT1_CTRL_AUXSRC__clksrc_gpin0 = 1;
    static const uint32_t CLK_GPOUT1_CTRL_AUXSRC__clksrc_gpin1 = 2;
    static const uint32_t CLK_GPOUT1_CTRL_AUXSRC__clksrc_pll_usb = 3;
    static const uint32_t CLK_GPOUT1_CTRL_AUXSRC__rosc_clksrc = 4;
    static const uint32_t CLK_GPOUT1_CTRL_AUXSRC__xosc_clksrc = 5;
    static const uint32_t CLK_GPOUT1_CTRL_AUXSRC__clk_sys = 6;
    static const uint32_t CLK_GPOUT1_CTRL_AUXSRC__clk_usb = 7;
    static const uint32_t CLK_GPOUT1_CTRL_AUXSRC__clk_adc = 8;
    static const uint32_t CLK_GPOUT1_CTRL_AUXSRC__clk_rtc = 9;
    static const uint32_t CLK_GPOUT1_CTRL_AUXSRC__clk_ref = 10;

    // Clock divisor, can be changed on-the-fly
    // Reset value: 0x00000100
    BEGIN_TYPE(CLK_GPOUT1_DIV_t, uint32_t)
        // Integer component of the divisor, 0 -> divide by 2^16
        ADD_BITFIELD_RW(INT, 8, 24)
        // Fractional component of the divisor
        ADD_BITFIELD_RW(FRAC, 0, 8)
    END_TYPE()

    // Indicates which SRC is currently selected by the glitchless mux (one-hot).
    // This slice does not have a glitchless mux (only the AUX_SRC field is present, not SRC) so this register is hardwired to 0x1.
    // Reset value: 0x00000001
    typedef uint32_t CLK_GPOUT1_SELECTED_t;

    // Clock control, can be changed on-the-fly (except for auxsrc)
    // Reset value: 0x00000000
    BEGIN_TYPE(CLK_GPOUT2_CTRL_t, uint32_t)
        // An edge on this signal shifts the phase of the output by 1 cycle of the input clock
        // This can be done at any time
        ADD_BITFIELD_RW(NUDGE, 20, 1)
        // This delays the enable signal by up to 3 cycles of the input clock
        // This must be set before the clock is enabled to have any effect
        ADD_BITFIELD_RW(PHASE, 16, 2)
        // Enables duty cycle correction for odd divisors
        ADD_BITFIELD_RW(DC50, 12, 1)
        // Starts and stops the clock generator cleanly
        ADD_BITFIELD_RW(ENABLE, 11, 1)
        // Asynchronously kills the clock generator
        ADD_BITFIELD_RW(KILL, 10, 1)
        // Selects the auxiliary clock source, will glitch when switching
        ADD_BITFIELD_RW(AUXSRC, 5, 4)
    END_TYPE()

    static const uint32_t CLK_GPOUT2_CTRL_AUXSRC__clksrc_pll_sys = 0;
    static const uint32_t CLK_GPOUT2_CTRL_AUXSRC__clksrc_gpin0 = 1;
    static const uint32_t CLK_GPOUT2_CTRL_AUXSRC__clksrc_gpin1 = 2;
    static const uint32_t CLK_GPOUT2_CTRL_AUXSRC__clksrc_pll_usb = 3;
    static const uint32_t CLK_GPOUT2_CTRL_AUXSRC__rosc_clksrc_ph = 4;
    static const uint32_t CLK_GPOUT2_CTRL_AUXSRC__xosc_clksrc = 5;
    static const uint32_t CLK_GPOUT2_CTRL_AUXSRC__clk_sys = 6;
    static const uint32_t CLK_GPOUT2_CTRL_AUXSRC__clk_usb = 7;
    static const uint32_t CLK_GPOUT2_CTRL_AUXSRC__clk_adc = 8;
    static const uint32_t CLK_GPOUT2_CTRL_AUXSRC__clk_rtc = 9;
    static const uint32_t CLK_GPOUT2_CTRL_AUXSRC__clk_ref = 10;

    // Clock divisor, can be changed on-the-fly
    // Reset value: 0x00000100
    BEGIN_TYPE(CLK_GPOUT2_DIV_t, uint32_t)
        // Integer component of the divisor, 0 -> divide by 2^16
        ADD_BITFIELD_RW(INT, 8, 24)
        // Fractional component of the divisor
        ADD_BITFIELD_RW(FRAC, 0, 8)
    END_TYPE()

    // Indicates which SRC is currently selected by the glitchless mux (one-hot).
    // This slice does not have a glitchless mux (only the AUX_SRC field is present, not SRC) so this register is hardwired to 0x1.
    // Reset value: 0x00000001
    typedef uint32_t CLK_GPOUT2_SELECTED_t;

    // Clock control, can be changed on-the-fly (except for auxsrc)
    // Reset value: 0x00000000
    BEGIN_TYPE(CLK_GPOUT3_CTRL_t, uint32_t)
        // An edge on this signal shifts the phase of the output by 1 cycle of the input clock
        // This can be done at any time
        ADD_BITFIELD_RW(NUDGE, 20, 1)
        // This delays the enable signal by up to 3 cycles of the input clock
        // This must be set before the clock is enabled to have any effect
        ADD_BITFIELD_RW(PHASE, 16, 2)
        // Enables duty cycle correction for odd divisors
        ADD_BITFIELD_RW(DC50, 12, 1)
        // Starts and stops the clock generator cleanly
        ADD_BITFIELD_RW(ENABLE, 11, 1)
        // Asynchronously kills the clock generator
        ADD_BITFIELD_RW(KILL, 10, 1)
        // Selects the auxiliary clock source, will glitch when switching
        ADD_BITFIELD_RW(AUXSRC, 5, 4)
    END_TYPE()

    static const uint32_t CLK_GPOUT3_CTRL_AUXSRC__clksrc_pll_sys = 0;
    static const uint32_t CLK_GPOUT3_CTRL_AUXSRC__clksrc_gpin0 = 1;
    static const uint32_t CLK_GPOUT3_CTRL_AUXSRC__clksrc_gpin1 = 2;
    static const uint32_t CLK_GPOUT3_CTRL_AUXSRC__clksrc_pll_usb = 3;
    static const uint32_t CLK_GPOUT3_CTRL_AUXSRC__rosc_clksrc_ph = 4;
    static const uint32_t CLK_GPOUT3_CTRL_AUXSRC__xosc_clksrc = 5;
    static const uint32_t CLK_GPOUT3_CTRL_AUXSRC__clk_sys = 6;
    static const uint32_t CLK_GPOUT3_CTRL_AUXSRC__clk_usb = 7;
    static const uint32_t CLK_GPOUT3_CTRL_AUXSRC__clk_adc = 8;
    static const uint32_t CLK_GPOUT3_CTRL_AUXSRC__clk_rtc = 9;
    static const uint32_t CLK_GPOUT3_CTRL_AUXSRC__clk_ref = 10;

    // Clock divisor, can be changed on-the-fly
    // Reset value: 0x00000100
    BEGIN_TYPE(CLK_GPOUT3_DIV_t, uint32_t)
        // Integer component of the divisor, 0 -> divide by 2^16
        ADD_BITFIELD_RW(INT, 8, 24)
        // Fractional component of the divisor
        ADD_BITFIELD_RW(FRAC, 0, 8)
    END_TYPE()

    // Indicates which SRC is currently selected by the glitchless mux (one-hot).
    // This slice does not have a glitchless mux (only the AUX_SRC field is present, not SRC) so this register is hardwired to 0x1.
    // Reset value: 0x00000001
    typedef uint32_t CLK_GPOUT3_SELECTED_t;

    // Clock control, can be changed on-the-fly (except for auxsrc)
    // Reset value: 0x00000000
    BEGIN_TYPE(CLK_REF_CTRL_t, uint32_t)
        // Selects the auxiliary clock source, will glitch when switching
        ADD_BITFIELD_RW(AUXSRC, 5, 2)
        // Selects the clock source glitchlessly, can be changed on-the-fly
        ADD_BITFIELD_RW(SRC, 0, 2)
    END_TYPE()

    static const uint32_t CLK_REF_CTRL_AUXSRC__clksrc_pll_usb = 0;
    static const uint32_t CLK_REF_CTRL_AUXSRC__clksrc_gpin0 = 1;
    static const uint32_t CLK_REF_CTRL_AUXSRC__clksrc_gpin1 = 2;
    static const uint32_t CLK_REF_CTRL_SRC__rosc_clksrc_ph = 0;
    static const uint32_t CLK_REF_CTRL_SRC__clksrc_clk_ref_aux = 1;
    static const uint32_t CLK_REF_CTRL_SRC__xosc_clksrc = 2;

    // Clock divisor, can be changed on-the-fly
    // Reset value: 0x00000100
    BEGIN_TYPE(CLK_REF_DIV_t, uint32_t)
        // Integer component of the divisor, 0 -> divide by 2^16
        ADD_BITFIELD_RW(INT, 8, 2)
    END_TYPE()

    // Indicates which SRC is currently selected by the glitchless mux (one-hot).
    // The glitchless multiplexer does not switch instantaneously (to avoid glitches), so software should poll this register to wait for the switch to complete. This register contains one decoded bit for each of the clock sources enumerated in the CTRL SRC field. At most one of these bits will be set at any time, indicating that clock is currently present at the output of the glitchless mux. Whilst switching is in progress, this register may briefly show all-0s.
    // Reset value: 0x00000001
    typedef uint32_t CLK_REF_SELECTED_t;

    // Clock control, can be changed on-the-fly (except for auxsrc)
    // Reset value: 0x00000000
    BEGIN_TYPE(CLK_SYS_CTRL_t, uint32_t)
        // Selects the auxiliary clock source, will glitch when switching
        ADD_BITFIELD_RW(AUXSRC, 5, 3)
        // Selects the clock source glitchlessly, can be changed on-the-fly
        ADD_BITFIELD_RW(SRC, 0, 1)
    END_TYPE()

    static const uint32_t CLK_SYS_CTRL_AUXSRC__clksrc_pll_sys = 0;
    static const uint32_t CLK_SYS_CTRL_AUXSRC__clksrc_pll_usb = 1;
    static const uint32_t CLK_SYS_CTRL_AUXSRC__rosc_clksrc = 2;
    static const uint32_t CLK_SYS_CTRL_AUXSRC__xosc_clksrc = 3;
    static const uint32_t CLK_SYS_CTRL_AUXSRC__clksrc_gpin0 = 4;
    static const uint32_t CLK_SYS_CTRL_AUXSRC__clksrc_gpin1 = 5;
    static const uint32_t CLK_SYS_CTRL_SRC__clk_ref = 0;
    static const uint32_t CLK_SYS_CTRL_SRC__clksrc_clk_sys_aux = 1;

    // Clock divisor, can be changed on-the-fly
    // Reset value: 0x00000100
    BEGIN_TYPE(CLK_SYS_DIV_t, uint32_t)
        // Integer component of the divisor, 0 -> divide by 2^16
        ADD_BITFIELD_RW(INT, 8, 24)
        // Fractional component of the divisor
        ADD_BITFIELD_RW(FRAC, 0, 8)
    END_TYPE()

    // Indicates which SRC is currently selected by the glitchless mux (one-hot).
    // The glitchless multiplexer does not switch instantaneously (to avoid glitches), so software should poll this register to wait for the switch to complete. This register contains one decoded bit for each of the clock sources enumerated in the CTRL SRC field. At most one of these bits will be set at any time, indicating that clock is currently present at the output of the glitchless mux. Whilst switching is in progress, this register may briefly show all-0s.
    // Reset value: 0x00000001
    typedef uint32_t CLK_SYS_SELECTED_t;

    // Clock control, can be changed on-the-fly (except for auxsrc)
    // Reset value: 0x00000000
    BEGIN_TYPE(CLK_PERI_CTRL_t, uint32_t)
        // Starts and stops the clock generator cleanly
        ADD_BITFIELD_RW(ENABLE, 11, 1)
        // Asynchronously kills the clock generator
        ADD_BITFIELD_RW(KILL, 10, 1)
        // Selects the auxiliary clock source, will glitch when switching
        ADD_BITFIELD_RW(AUXSRC, 5, 3)
    END_TYPE()

    static const uint32_t CLK_PERI_CTRL_AUXSRC__clk_sys = 0;
    static const uint32_t CLK_PERI_CTRL_AUXSRC__clksrc_pll_sys = 1;
    static const uint32_t CLK_PERI_CTRL_AUXSRC__clksrc_pll_usb = 2;
    static const uint32_t CLK_PERI_CTRL_AUXSRC__rosc_clksrc_ph = 3;
    static const uint32_t CLK_PERI_CTRL_AUXSRC__xosc_clksrc = 4;
    static const uint32_t CLK_PERI_CTRL_AUXSRC__clksrc_gpin0 = 5;
    static const uint32_t CLK_PERI_CTRL_AUXSRC__clksrc_gpin1 = 6;

    // Indicates which SRC is currently selected by the glitchless mux (one-hot).
    // This slice does not have a glitchless mux (only the AUX_SRC field is present, not SRC) so this register is hardwired to 0x1.
    // Reset value: 0x00000001
    typedef uint32_t CLK_PERI_SELECTED_t;

    // Clock control, can be changed on-the-fly (except for auxsrc)
    // Reset value: 0x00000000
    BEGIN_TYPE(CLK_USB_CTRL_t, uint32_t)
        // An edge on this signal shifts the phase of the output by 1 cycle of the input clock
        // This can be done at any time
        ADD_BITFIELD_RW(NUDGE, 20, 1)
        // This delays the enable signal by up to 3 cycles of the input clock
        // This must be set before the clock is enabled to have any effect
        ADD_BITFIELD_RW(PHASE, 16, 2)
        // Starts and stops the clock generator cleanly
        ADD_BITFIELD_RW(ENABLE, 11, 1)
        // Asynchronously kills the clock generator
        ADD_BITFIELD_RW(KILL, 10, 1)
        // Selects the auxiliary clock source, will glitch when switching
        ADD_BITFIELD_RW(AUXSRC, 5, 3)
    END_TYPE()

    static const uint32_t CLK_USB_CTRL_AUXSRC__clksrc_pll_usb = 0;
    static const uint32_t CLK_USB_CTRL_AUXSRC__clksrc_pll_sys = 1;
    static const uint32_t CLK_USB_CTRL_AUXSRC__rosc_clksrc_ph = 2;
    static const uint32_t CLK_USB_CTRL_AUXSRC__xosc_clksrc = 3;
    static const uint32_t CLK_USB_CTRL_AUXSRC__clksrc_gpin0 = 4;
    static const uint32_t CLK_USB_CTRL_AUXSRC__clksrc_gpin1 = 5;

    // Clock divisor, can be changed on-the-fly
    // Reset value: 0x00000100
    BEGIN_TYPE(CLK_USB_DIV_t, uint32_t)
        // Integer component of the divisor, 0 -> divide by 2^16
        ADD_BITFIELD_RW(INT, 8, 2)
    END_TYPE()

    // Indicates which SRC is currently selected by the glitchless mux (one-hot).
    // This slice does not have a glitchless mux (only the AUX_SRC field is present, not SRC) so this register is hardwired to 0x1.
    // Reset value: 0x00000001
    typedef uint32_t CLK_USB_SELECTED_t;

    // Clock control, can be changed on-the-fly (except for auxsrc)
    // Reset value: 0x00000000
    BEGIN_TYPE(CLK_ADC_CTRL_t, uint32_t)
        // An edge on this signal shifts the phase of the output by 1 cycle of the input clock
        // This can be done at any time
        ADD_BITFIELD_RW(NUDGE, 20, 1)
        // This delays the enable signal by up to 3 cycles of the input clock
        // This must be set before the clock is enabled to have any effect
        ADD_BITFIELD_RW(PHASE, 16, 2)
        // Starts and stops the clock generator cleanly
        ADD_BITFIELD_RW(ENABLE, 11, 1)
        // Asynchronously kills the clock generator
        ADD_BITFIELD_RW(KILL, 10, 1)
        // Selects the auxiliary clock source, will glitch when switching
        ADD_BITFIELD_RW(AUXSRC, 5, 3)
    END_TYPE()

    static const uint32_t CLK_ADC_CTRL_AUXSRC__clksrc_pll_usb = 0;
    static const uint32_t CLK_ADC_CTRL_AUXSRC__clksrc_pll_sys = 1;
    static const uint32_t CLK_ADC_CTRL_AUXSRC__rosc_clksrc_ph = 2;
    static const uint32_t CLK_ADC_CTRL_AUXSRC__xosc_clksrc = 3;
    static const uint32_t CLK_ADC_CTRL_AUXSRC__clksrc_gpin0 = 4;
    static const uint32_t CLK_ADC_CTRL_AUXSRC__clksrc_gpin1 = 5;

    // Clock divisor, can be changed on-the-fly
    // Reset value: 0x00000100
    BEGIN_TYPE(CLK_ADC_DIV_t, uint32_t)
        // Integer component of the divisor, 0 -> divide by 2^16
        ADD_BITFIELD_RW(INT, 8, 2)
    END_TYPE()

    // Indicates which SRC is currently selected by the glitchless mux (one-hot).
    // This slice does not have a glitchless mux (only the AUX_SRC field is present, not SRC) so this register is hardwired to 0x1.
    // Reset value: 0x00000001
    typedef uint32_t CLK_ADC_SELECTED_t;

    // Clock control, can be changed on-the-fly (except for auxsrc)
    // Reset value: 0x00000000
    BEGIN_TYPE(CLK_RTC_CTRL_t, uint32_t)
        // An edge on this signal shifts the phase of the output by 1 cycle of the input clock
        // This can be done at any time
        ADD_BITFIELD_RW(NUDGE, 20, 1)
        // This delays the enable signal by up to 3 cycles of the input clock
        // This must be set before the clock is enabled to have any effect
        ADD_BITFIELD_RW(PHASE, 16, 2)
        // Starts and stops the clock generator cleanly
        ADD_BITFIELD_RW(ENABLE, 11, 1)
        // Asynchronously kills the clock generator
        ADD_BITFIELD_RW(KILL, 10, 1)
        // Selects the auxiliary clock source, will glitch when switching
        ADD_BITFIELD_RW(AUXSRC, 5, 3)
    END_TYPE()

    static const uint32_t CLK_RTC_CTRL_AUXSRC__clksrc_pll_usb = 0;
    static const uint32_t CLK_RTC_CTRL_AUXSRC__clksrc_pll_sys = 1;
    static const uint32_t CLK_RTC_CTRL_AUXSRC__rosc_clksrc_ph = 2;
    static const uint32_t CLK_RTC_CTRL_AUXSRC__xosc_clksrc = 3;
    static const uint32_t CLK_RTC_CTRL_AUXSRC__clksrc_gpin0 = 4;
    static const uint32_t CLK_RTC_CTRL_AUXSRC__clksrc_gpin1 = 5;

    // Clock divisor, can be changed on-the-fly
    // Reset value: 0x00000100
    BEGIN_TYPE(CLK_RTC_DIV_t, uint32_t)
        // Integer component of the divisor, 0 -> divide by 2^16
        ADD_BITFIELD_RW(INT, 8, 24)
        // Fractional component of the divisor
        ADD_BITFIELD_RW(FRAC, 0, 8)
    END_TYPE()

    // Indicates which SRC is currently selected by the glitchless mux (one-hot).
    // This slice does not have a glitchless mux (only the AUX_SRC field is present, not SRC) so this register is hardwired to 0x1.
    // Reset value: 0x00000001
    typedef uint32_t CLK_RTC_SELECTED_t;

    // Reset value: 0x000000ff
    BEGIN_TYPE(CLK_SYS_RESUS_CTRL_t, uint32_t)
        // For clearing the resus after the fault that triggered it has been corrected
        ADD_BITFIELD_RW(CLEAR, 16, 1)
        // Force a resus, for test purposes only
        ADD_BITFIELD_RW(FRCE, 12, 1)
        // Enable resus
        ADD_BITFIELD_RW(ENABLE, 8, 1)
        // This is expressed as a number of clk_ref cycles
        // and must be >= 2x clk_ref_freq/min_clk_tst_freq
        ADD_BITFIELD_RW(TIMEOUT, 0, 8)
    END_TYPE()

    // Reset value: 0x00000000
    BEGIN_TYPE(CLK_SYS_RESUS_STATUS_t, uint32_t)
        // Clock has been resuscitated, correct the error then send ctrl_clear=1
        ADD_BITFIELD_RO(RESUSSED, 0, 1)
    END_TYPE()

    // Reference clock frequency in kHz
    // Reset value: 0x00000000
    BEGIN_TYPE(FC0_REF_KHZ_t, uint32_t)
        ADD_BITFIELD_RW(FC0_REF_KHZ, 0, 20)
    END_TYPE()

    // Minimum pass frequency in kHz. This is optional. Set to 0 if you are not using the pass/fail flags
    // Reset value: 0x00000000
    BEGIN_TYPE(FC0_MIN_KHZ_t, uint32_t)
        ADD_BITFIELD_RW(FC0_MIN_KHZ, 0, 25)
    END_TYPE()

    // Maximum pass frequency in kHz. This is optional. Set to 0x1ffffff if you are not using the pass/fail flags
    // Reset value: 0x01ffffff
    BEGIN_TYPE(FC0_MAX_KHZ_t, uint32_t)
        ADD_BITFIELD_RW(FC0_MAX_KHZ, 0, 25)
    END_TYPE()

    // Delays the start of frequency counting to allow the mux to settle
    // Delay is measured in multiples of the reference clock period
    // Reset value: 0x00000001
    BEGIN_TYPE(FC0_DELAY_t, uint32_t)
        ADD_BITFIELD_RW(FC0_DELAY, 0, 3)
    END_TYPE()

    // The test interval is 0.98us * 2**interval, but let's call it 1us * 2**interval
    // The default gives a test interval of 250us
    // Reset value: 0x00000008
    BEGIN_TYPE(FC0_INTERVAL_t, uint32_t)
        ADD_BITFIELD_RW(FC0_INTERVAL, 0, 4)
    END_TYPE()

    // Clock sent to frequency counter, set to 0 when not required
    // Writing to this register initiates the frequency count
    // Reset value: 0x00000000
    BEGIN_TYPE(FC0_SRC_t, uint32_t)
        ADD_BITFIELD_RW(FC0_SRC, 0, 8)
    END_TYPE()

    static const uint32_t FC0_SRC_FC0_SRC__NULL = 0;
    static const uint32_t FC0_SRC_FC0_SRC__pll_sys_clksrc_primary = 1;
    static const uint32_t FC0_SRC_FC0_SRC__pll_usb_clksrc_primary = 2;
    static const uint32_t FC0_SRC_FC0_SRC__rosc_clksrc = 3;
    static const uint32_t FC0_SRC_FC0_SRC__rosc_clksrc_ph = 4;
    static const uint32_t FC0_SRC_FC0_SRC__xosc_clksrc = 5;
    static const uint32_t FC0_SRC_FC0_SRC__clksrc_gpin0 = 6;
    static const uint32_t FC0_SRC_FC0_SRC__clksrc_gpin1 = 7;
    static const uint32_t FC0_SRC_FC0_SRC__clk_ref = 8;
    static const uint32_t FC0_SRC_FC0_SRC__clk_sys = 9;
    static const uint32_t FC0_SRC_FC0_SRC__clk_peri = 10;
    static const uint32_t FC0_SRC_FC0_SRC__clk_usb = 11;
    static const uint32_t FC0_SRC_FC0_SRC__clk_adc = 12;
    static const uint32_t FC0_SRC_FC0_SRC__clk_rtc = 13;

    // Frequency counter status
    // Reset value: 0x00000000
    BEGIN_TYPE(FC0_STATUS_t, uint32_t)
        // Test clock stopped during test
        ADD_BITFIELD_RO(DIED, 28, 1)
        // Test clock faster than expected, only valid when status_done=1
        ADD_BITFIELD_RO(FAST, 24, 1)
        // Test clock slower than expected, only valid when status_done=1
        ADD_BITFIELD_RO(SLOW, 20, 1)
        // Test failed
        ADD_BITFIELD_RO(FAIL, 16, 1)
        // Waiting for test clock to start
        ADD_BITFIELD_RO(WAITING, 12, 1)
        // Test running
        ADD_BITFIELD_RO(RUNNING, 8, 1)
        // Test complete
        ADD_BITFIELD_RO(DONE, 4, 1)
        // Test passed
        ADD_BITFIELD_RO(PASS, 0, 1)
    END_TYPE()

    // Result of frequency measurement, only valid when status_done=1
    // Reset value: 0x00000000
    BEGIN_TYPE(FC0_RESULT_t, uint32_t)
        ADD_BITFIELD_RO(KHZ, 5, 25)
        ADD_BITFIELD_RO(FRAC, 0, 5)
    END_TYPE()

    // enable clock in wake mode
    // Reset value: 0xffffffff
    BEGIN_TYPE(WAKE_EN0_t, uint32_t)
        ADD_BITFIELD_RW(clk_sys_sram3, 31, 1)
        ADD_BITFIELD_RW(clk_sys_sram2, 30, 1)
        ADD_BITFIELD_RW(clk_sys_sram1, 29, 1)
        ADD_BITFIELD_RW(clk_sys_sram0, 28, 1)
        ADD_BITFIELD_RW(clk_sys_spi1, 27, 1)
        ADD_BITFIELD_RW(clk_peri_spi1, 26, 1)
        ADD_BITFIELD_RW(clk_sys_spi0, 25, 1)
        ADD_BITFIELD_RW(clk_peri_spi0, 24, 1)
        ADD_BITFIELD_RW(clk_sys_sio, 23, 1)
        ADD_BITFIELD_RW(clk_sys_rtc, 22, 1)
        ADD_BITFIELD_RW(clk_rtc_rtc, 21, 1)
        ADD_BITFIELD_RW(clk_sys_rosc, 20, 1)
        ADD_BITFIELD_RW(clk_sys_rom, 19, 1)
        ADD_BITFIELD_RW(clk_sys_resets, 18, 1)
        ADD_BITFIELD_RW(clk_sys_pwm, 17, 1)
        ADD_BITFIELD_RW(clk_sys_psm, 16, 1)
        ADD_BITFIELD_RW(clk_sys_pll_usb, 15, 1)
        ADD_BITFIELD_RW(clk_sys_pll_sys, 14, 1)
        ADD_BITFIELD_RW(clk_sys_pio1, 13, 1)
        ADD_BITFIELD_RW(clk_sys_pio0, 12, 1)
        ADD_BITFIELD_RW(clk_sys_pads, 11, 1)
        ADD_BITFIELD_RW(clk_sys_vreg_and_chip_reset, 10, 1)
        ADD_BITFIELD_RW(clk_sys_jtag, 9, 1)
        ADD_BITFIELD_RW(clk_sys_io, 8, 1)
        ADD_BITFIELD_RW(clk_sys_i2c1, 7, 1)
        ADD_BITFIELD_RW(clk_sys_i2c0, 6, 1)
        ADD_BITFIELD_RW(clk_sys_dma, 5, 1)
        ADD_BITFIELD_RW(clk_sys_busfabric, 4, 1)
        ADD_BITFIELD_RW(clk_sys_busctrl, 3, 1)
        ADD_BITFIELD_RW(clk_sys_adc, 2, 1)
        ADD_BITFIELD_RW(clk_adc_adc, 1, 1)
        ADD_BITFIELD_RW(clk_sys_clocks, 0, 1)
    END_TYPE()

    // enable clock in wake mode
    // Reset value: 0x00007fff
    BEGIN_TYPE(WAKE_EN1_t, uint32_t)
        ADD_BITFIELD_RW(clk_sys_xosc, 14, 1)
        ADD_BITFIELD_RW(clk_sys_xip, 13, 1)
        ADD_BITFIELD_RW(clk_sys_watchdog, 12, 1)
        ADD_BITFIELD_RW(clk_usb_usbctrl, 11, 1)
        ADD_BITFIELD_RW(clk_sys_usbctrl, 10, 1)
        ADD_BITFIELD_RW(clk_sys_uart1, 9, 1)
        ADD_BITFIELD_RW(clk_peri_uart1, 8, 1)
        ADD_BITFIELD_RW(clk_sys_uart0, 7, 1)
        ADD_BITFIELD_RW(clk_peri_uart0, 6, 1)
        ADD_BITFIELD_RW(clk_sys_timer, 5, 1)
        ADD_BITFIELD_RW(clk_sys_tbman, 4, 1)
        ADD_BITFIELD_RW(clk_sys_sysinfo, 3, 1)
        ADD_BITFIELD_RW(clk_sys_syscfg, 2, 1)
        ADD_BITFIELD_RW(clk_sys_sram5, 1, 1)
        ADD_BITFIELD_RW(clk_sys_sram4, 0, 1)
    END_TYPE()

    // enable clock in sleep mode
    // Reset value: 0xffffffff
    BEGIN_TYPE(SLEEP_EN0_t, uint32_t)
        ADD_BITFIELD_RW(clk_sys_sram3, 31, 1)
        ADD_BITFIELD_RW(clk_sys_sram2, 30, 1)
        ADD_BITFIELD_RW(clk_sys_sram1, 29, 1)
        ADD_BITFIELD_RW(clk_sys_sram0, 28, 1)
        ADD_BITFIELD_RW(clk_sys_spi1, 27, 1)
        ADD_BITFIELD_RW(clk_peri_spi1, 26, 1)
        ADD_BITFIELD_RW(clk_sys_spi0, 25, 1)
        ADD_BITFIELD_RW(clk_peri_spi0, 24, 1)
        ADD_BITFIELD_RW(clk_sys_sio, 23, 1)
        ADD_BITFIELD_RW(clk_sys_rtc, 22, 1)
        ADD_BITFIELD_RW(clk_rtc_rtc, 21, 1)
        ADD_BITFIELD_RW(clk_sys_rosc, 20, 1)
        ADD_BITFIELD_RW(clk_sys_rom, 19, 1)
        ADD_BITFIELD_RW(clk_sys_resets, 18, 1)
        ADD_BITFIELD_RW(clk_sys_pwm, 17, 1)
        ADD_BITFIELD_RW(clk_sys_psm, 16, 1)
        ADD_BITFIELD_RW(clk_sys_pll_usb, 15, 1)
        ADD_BITFIELD_RW(clk_sys_pll_sys, 14, 1)
        ADD_BITFIELD_RW(clk_sys_pio1, 13, 1)
        ADD_BITFIELD_RW(clk_sys_pio0, 12, 1)
        ADD_BITFIELD_RW(clk_sys_pads, 11, 1)
        ADD_BITFIELD_RW(clk_sys_vreg_and_chip_reset, 10, 1)
        ADD_BITFIELD_RW(clk_sys_jtag, 9, 1)
        ADD_BITFIELD_RW(clk_sys_io, 8, 1)
        ADD_BITFIELD_RW(clk_sys_i2c1, 7, 1)
        ADD_BITFIELD_RW(clk_sys_i2c0, 6, 1)
        ADD_BITFIELD_RW(clk_sys_dma, 5, 1)
        ADD_BITFIELD_RW(clk_sys_busfabric, 4, 1)
        ADD_BITFIELD_RW(clk_sys_busctrl, 3, 1)
        ADD_BITFIELD_RW(clk_sys_adc, 2, 1)
        ADD_BITFIELD_RW(clk_adc_adc, 1, 1)
        ADD_BITFIELD_RW(clk_sys_clocks, 0, 1)
    END_TYPE()

    // enable clock in sleep mode
    // Reset value: 0x00007fff
    BEGIN_TYPE(SLEEP_EN1_t, uint32_t)
        ADD_BITFIELD_RW(clk_sys_xosc, 14, 1)
        ADD_BITFIELD_RW(clk_sys_xip, 13, 1)
        ADD_BITFIELD_RW(clk_sys_watchdog, 12, 1)
        ADD_BITFIELD_RW(clk_usb_usbctrl, 11, 1)
        ADD_BITFIELD_RW(clk_sys_usbctrl, 10, 1)
        ADD_BITFIELD_RW(clk_sys_uart1, 9, 1)
        ADD_BITFIELD_RW(clk_peri_uart1, 8, 1)
        ADD_BITFIELD_RW(clk_sys_uart0, 7, 1)
        ADD_BITFIELD_RW(clk_peri_uart0, 6, 1)
        ADD_BITFIELD_RW(clk_sys_timer, 5, 1)
        ADD_BITFIELD_RW(clk_sys_tbman, 4, 1)
        ADD_BITFIELD_RW(clk_sys_sysinfo, 3, 1)
        ADD_BITFIELD_RW(clk_sys_syscfg, 2, 1)
        ADD_BITFIELD_RW(clk_sys_sram5, 1, 1)
        ADD_BITFIELD_RW(clk_sys_sram4, 0, 1)
    END_TYPE()

    // indicates the state of the clock enable
    // Reset value: 0x00000000
    BEGIN_TYPE(ENABLED0_t, uint32_t)
        ADD_BITFIELD_RO(clk_sys_sram3, 31, 1)
        ADD_BITFIELD_RO(clk_sys_sram2, 30, 1)
        ADD_BITFIELD_RO(clk_sys_sram1, 29, 1)
        ADD_BITFIELD_RO(clk_sys_sram0, 28, 1)
        ADD_BITFIELD_RO(clk_sys_spi1, 27, 1)
        ADD_BITFIELD_RO(clk_peri_spi1, 26, 1)
        ADD_BITFIELD_RO(clk_sys_spi0, 25, 1)
        ADD_BITFIELD_RO(clk_peri_spi0, 24, 1)
        ADD_BITFIELD_RO(clk_sys_sio, 23, 1)
        ADD_BITFIELD_RO(clk_sys_rtc, 22, 1)
        ADD_BITFIELD_RO(clk_rtc_rtc, 21, 1)
        ADD_BITFIELD_RO(clk_sys_rosc, 20, 1)
        ADD_BITFIELD_RO(clk_sys_rom, 19, 1)
        ADD_BITFIELD_RO(clk_sys_resets, 18, 1)
        ADD_BITFIELD_RO(clk_sys_pwm, 17, 1)
        ADD_BITFIELD_RO(clk_sys_psm, 16, 1)
        ADD_BITFIELD_RO(clk_sys_pll_usb, 15, 1)
        ADD_BITFIELD_RO(clk_sys_pll_sys, 14, 1)
        ADD_BITFIELD_RO(clk_sys_pio1, 13, 1)
        ADD_BITFIELD_RO(clk_sys_pio0, 12, 1)
        ADD_BITFIELD_RO(clk_sys_pads, 11, 1)
        ADD_BITFIELD_RO(clk_sys_vreg_and_chip_reset, 10, 1)
        ADD_BITFIELD_RO(clk_sys_jtag, 9, 1)
        ADD_BITFIELD_RO(clk_sys_io, 8, 1)
        ADD_BITFIELD_RO(clk_sys_i2c1, 7, 1)
        ADD_BITFIELD_RO(clk_sys_i2c0, 6, 1)
        ADD_BITFIELD_RO(clk_sys_dma, 5, 1)
        ADD_BITFIELD_RO(clk_sys_busfabric, 4, 1)
        ADD_BITFIELD_RO(clk_sys_busctrl, 3, 1)
        ADD_BITFIELD_RO(clk_sys_adc, 2, 1)
        ADD_BITFIELD_RO(clk_adc_adc, 1, 1)
        ADD_BITFIELD_RO(clk_sys_clocks, 0, 1)
    END_TYPE()

    // indicates the state of the clock enable
    // Reset value: 0x00000000
    BEGIN_TYPE(ENABLED1_t, uint32_t)
        ADD_BITFIELD_RO(clk_sys_xosc, 14, 1)
        ADD_BITFIELD_RO(clk_sys_xip, 13, 1)
        ADD_BITFIELD_RO(clk_sys_watchdog, 12, 1)
        ADD_BITFIELD_RO(clk_usb_usbctrl, 11, 1)
        ADD_BITFIELD_RO(clk_sys_usbctrl, 10, 1)
        ADD_BITFIELD_RO(clk_sys_uart1, 9, 1)
        ADD_BITFIELD_RO(clk_peri_uart1, 8, 1)
        ADD_BITFIELD_RO(clk_sys_uart0, 7, 1)
        ADD_BITFIELD_RO(clk_peri_uart0, 6, 1)
        ADD_BITFIELD_RO(clk_sys_timer, 5, 1)
        ADD_BITFIELD_RO(clk_sys_tbman, 4, 1)
        ADD_BITFIELD_RO(clk_sys_sysinfo, 3, 1)
        ADD_BITFIELD_RO(clk_sys_syscfg, 2, 1)
        ADD_BITFIELD_RO(clk_sys_sram5, 1, 1)
        ADD_BITFIELD_RO(clk_sys_sram4, 0, 1)
    END_TYPE()

    // Raw Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR_t, uint32_t)
        ADD_BITFIELD_RO(CLK_SYS_RESUS, 0, 1)
    END_TYPE()

    // Interrupt Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(INTE_t, uint32_t)
        ADD_BITFIELD_RW(CLK_SYS_RESUS, 0, 1)
    END_TYPE()

    // Interrupt Force
    // Reset value: 0x00000000
    BEGIN_TYPE(INTF_t, uint32_t)
        ADD_BITFIELD_RW(CLK_SYS_RESUS, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing
    // Reset value: 0x00000000
    BEGIN_TYPE(INTS_t, uint32_t)
        ADD_BITFIELD_RO(CLK_SYS_RESUS, 0, 1)
    END_TYPE()

    struct CLOCKS_t {
        CLK_GPOUT0_CTRL_t             CLK_GPOUT0_CTRL;
        CLK_GPOUT0_DIV_t              CLK_GPOUT0_DIV;
        CLK_GPOUT0_SELECTED_t         CLK_GPOUT0_SELECTED;
        CLK_GPOUT1_CTRL_t             CLK_GPOUT1_CTRL;
        CLK_GPOUT1_DIV_t              CLK_GPOUT1_DIV;
        CLK_GPOUT1_SELECTED_t         CLK_GPOUT1_SELECTED;
        CLK_GPOUT2_CTRL_t             CLK_GPOUT2_CTRL;
        CLK_GPOUT2_DIV_t              CLK_GPOUT2_DIV;
        CLK_GPOUT2_SELECTED_t         CLK_GPOUT2_SELECTED;
        CLK_GPOUT3_CTRL_t             CLK_GPOUT3_CTRL;
        CLK_GPOUT3_DIV_t              CLK_GPOUT3_DIV;
        CLK_GPOUT3_SELECTED_t         CLK_GPOUT3_SELECTED;
        CLK_REF_CTRL_t                CLK_REF_CTRL;
        CLK_REF_DIV_t                 CLK_REF_DIV;
        CLK_REF_SELECTED_t            CLK_REF_SELECTED;
        CLK_SYS_CTRL_t                CLK_SYS_CTRL;
        CLK_SYS_DIV_t                 CLK_SYS_DIV;
        CLK_SYS_SELECTED_t            CLK_SYS_SELECTED;
        CLK_PERI_CTRL_t               CLK_PERI_CTRL;
        uint32_t                      reserved0;
        CLK_PERI_SELECTED_t           CLK_PERI_SELECTED;
        CLK_USB_CTRL_t                CLK_USB_CTRL;
        CLK_USB_DIV_t                 CLK_USB_DIV;
        CLK_USB_SELECTED_t            CLK_USB_SELECTED;
        CLK_ADC_CTRL_t                CLK_ADC_CTRL;
        CLK_ADC_DIV_t                 CLK_ADC_DIV;
        CLK_ADC_SELECTED_t            CLK_ADC_SELECTED;
        CLK_RTC_CTRL_t                CLK_RTC_CTRL;
        CLK_RTC_DIV_t                 CLK_RTC_DIV;
        CLK_RTC_SELECTED_t            CLK_RTC_SELECTED;
        CLK_SYS_RESUS_CTRL_t          CLK_SYS_RESUS_CTRL;
        CLK_SYS_RESUS_STATUS_t        CLK_SYS_RESUS_STATUS;
        FC0_REF_KHZ_t                 FC0_REF_KHZ;
        FC0_MIN_KHZ_t                 FC0_MIN_KHZ;
        FC0_MAX_KHZ_t                 FC0_MAX_KHZ;
        FC0_DELAY_t                   FC0_DELAY;
        FC0_INTERVAL_t                FC0_INTERVAL;
        FC0_SRC_t                     FC0_SRC;
        FC0_STATUS_t                  FC0_STATUS;
        FC0_RESULT_t                  FC0_RESULT;
        WAKE_EN0_t                    WAKE_EN0;
        WAKE_EN1_t                    WAKE_EN1;
        SLEEP_EN0_t                   SLEEP_EN0;
        SLEEP_EN1_t                   SLEEP_EN1;
        ENABLED0_t                    ENABLED0;
        ENABLED1_t                    ENABLED1;
        INTR_t                        INTR;
        INTE_t                        INTE;
        INTF_t                        INTF;
        INTS_t                        INTS;
    };

    static CLOCKS_t & CLOCKS = (*(CLOCKS_t *)0x40008000);
    static CLOCKS_t & CLOCKS_XOR = (*(CLOCKS_t *)0x40009000);
    static CLOCKS_t & CLOCKS_SET = (*(CLOCKS_t *)0x4000a000);
    static CLOCKS_t & CLOCKS_CLR = (*(CLOCKS_t *)0x4000b000);

} // _CLOCKS_

namespace _RESETS_  {

    // Reset control. If a bit is set it means the peripheral is in reset. 0 means the peripheral's reset is deasserted.
    // Reset value: 0x01ffffff
    BEGIN_TYPE(RESET_t, uint32_t)
        ADD_BITFIELD_RW(usbctrl, 24, 1)
        ADD_BITFIELD_RW(uart1, 23, 1)
        ADD_BITFIELD_RW(uart0, 22, 1)
        ADD_BITFIELD_RW(timer, 21, 1)
        ADD_BITFIELD_RW(tbman, 20, 1)
        ADD_BITFIELD_RW(sysinfo, 19, 1)
        ADD_BITFIELD_RW(syscfg, 18, 1)
        ADD_BITFIELD_RW(spi1, 17, 1)
        ADD_BITFIELD_RW(spi0, 16, 1)
        ADD_BITFIELD_RW(rtc, 15, 1)
        ADD_BITFIELD_RW(pwm, 14, 1)
        ADD_BITFIELD_RW(pll_usb, 13, 1)
        ADD_BITFIELD_RW(pll_sys, 12, 1)
        ADD_BITFIELD_RW(pio1, 11, 1)
        ADD_BITFIELD_RW(pio0, 10, 1)
        ADD_BITFIELD_RW(pads_qspi, 9, 1)
        ADD_BITFIELD_RW(pads_bank0, 8, 1)
        ADD_BITFIELD_RW(jtag, 7, 1)
        ADD_BITFIELD_RW(io_qspi, 6, 1)
        ADD_BITFIELD_RW(io_bank0, 5, 1)
        ADD_BITFIELD_RW(i2c1, 4, 1)
        ADD_BITFIELD_RW(i2c0, 3, 1)
        ADD_BITFIELD_RW(dma, 2, 1)
        ADD_BITFIELD_RW(busctrl, 1, 1)
        ADD_BITFIELD_RW(adc, 0, 1)
    END_TYPE()

    // Watchdog select. If a bit is set then the watchdog will reset this peripheral when the watchdog fires.
    // Reset value: 0x00000000
    BEGIN_TYPE(WDSEL_t, uint32_t)
        ADD_BITFIELD_RW(usbctrl, 24, 1)
        ADD_BITFIELD_RW(uart1, 23, 1)
        ADD_BITFIELD_RW(uart0, 22, 1)
        ADD_BITFIELD_RW(timer, 21, 1)
        ADD_BITFIELD_RW(tbman, 20, 1)
        ADD_BITFIELD_RW(sysinfo, 19, 1)
        ADD_BITFIELD_RW(syscfg, 18, 1)
        ADD_BITFIELD_RW(spi1, 17, 1)
        ADD_BITFIELD_RW(spi0, 16, 1)
        ADD_BITFIELD_RW(rtc, 15, 1)
        ADD_BITFIELD_RW(pwm, 14, 1)
        ADD_BITFIELD_RW(pll_usb, 13, 1)
        ADD_BITFIELD_RW(pll_sys, 12, 1)
        ADD_BITFIELD_RW(pio1, 11, 1)
        ADD_BITFIELD_RW(pio0, 10, 1)
        ADD_BITFIELD_RW(pads_qspi, 9, 1)
        ADD_BITFIELD_RW(pads_bank0, 8, 1)
        ADD_BITFIELD_RW(jtag, 7, 1)
        ADD_BITFIELD_RW(io_qspi, 6, 1)
        ADD_BITFIELD_RW(io_bank0, 5, 1)
        ADD_BITFIELD_RW(i2c1, 4, 1)
        ADD_BITFIELD_RW(i2c0, 3, 1)
        ADD_BITFIELD_RW(dma, 2, 1)
        ADD_BITFIELD_RW(busctrl, 1, 1)
        ADD_BITFIELD_RW(adc, 0, 1)
    END_TYPE()

    // Reset done. If a bit is set then a reset done signal has been returned by the peripheral. This indicates that the peripheral's registers are ready to be accessed.
    // Reset value: 0x00000000
    BEGIN_TYPE(RESET_DONE_t, uint32_t)
        ADD_BITFIELD_RO(usbctrl, 24, 1)
        ADD_BITFIELD_RO(uart1, 23, 1)
        ADD_BITFIELD_RO(uart0, 22, 1)
        ADD_BITFIELD_RO(timer, 21, 1)
        ADD_BITFIELD_RO(tbman, 20, 1)
        ADD_BITFIELD_RO(sysinfo, 19, 1)
        ADD_BITFIELD_RO(syscfg, 18, 1)
        ADD_BITFIELD_RO(spi1, 17, 1)
        ADD_BITFIELD_RO(spi0, 16, 1)
        ADD_BITFIELD_RO(rtc, 15, 1)
        ADD_BITFIELD_RO(pwm, 14, 1)
        ADD_BITFIELD_RO(pll_usb, 13, 1)
        ADD_BITFIELD_RO(pll_sys, 12, 1)
        ADD_BITFIELD_RO(pio1, 11, 1)
        ADD_BITFIELD_RO(pio0, 10, 1)
        ADD_BITFIELD_RO(pads_qspi, 9, 1)
        ADD_BITFIELD_RO(pads_bank0, 8, 1)
        ADD_BITFIELD_RO(jtag, 7, 1)
        ADD_BITFIELD_RO(io_qspi, 6, 1)
        ADD_BITFIELD_RO(io_bank0, 5, 1)
        ADD_BITFIELD_RO(i2c1, 4, 1)
        ADD_BITFIELD_RO(i2c0, 3, 1)
        ADD_BITFIELD_RO(dma, 2, 1)
        ADD_BITFIELD_RO(busctrl, 1, 1)
        ADD_BITFIELD_RO(adc, 0, 1)
    END_TYPE()

    struct RESETS_t {
        RESET_t                       RESET;
        WDSEL_t                       WDSEL;
        RESET_DONE_t                  RESET_DONE;
    };

    static RESETS_t & RESETS = (*(RESETS_t *)0x4000c000);
    static RESETS_t & RESETS_XOR = (*(RESETS_t *)0x4000d000);
    static RESETS_t & RESETS_SET = (*(RESETS_t *)0x4000e000);
    static RESETS_t & RESETS_CLR = (*(RESETS_t *)0x4000f000);

} // _RESETS_

namespace _PSM_  {

    // Force block out of reset (i.e. power it on)
    // Reset value: 0x00000000
    BEGIN_TYPE(FRCE_ON_t, uint32_t)
        ADD_BITFIELD_RW(proc1, 16, 1)
        ADD_BITFIELD_RW(proc0, 15, 1)
        ADD_BITFIELD_RW(sio, 14, 1)
        ADD_BITFIELD_RW(vreg_and_chip_reset, 13, 1)
        ADD_BITFIELD_RW(xip, 12, 1)
        ADD_BITFIELD_RW(sram5, 11, 1)
        ADD_BITFIELD_RW(sram4, 10, 1)
        ADD_BITFIELD_RW(sram3, 9, 1)
        ADD_BITFIELD_RW(sram2, 8, 1)
        ADD_BITFIELD_RW(sram1, 7, 1)
        ADD_BITFIELD_RW(sram0, 6, 1)
        ADD_BITFIELD_RW(rom, 5, 1)
        ADD_BITFIELD_RW(busfabric, 4, 1)
        ADD_BITFIELD_RW(resets, 3, 1)
        ADD_BITFIELD_RW(clocks, 2, 1)
        ADD_BITFIELD_RW(xosc, 1, 1)
        ADD_BITFIELD_RW(rosc, 0, 1)
    END_TYPE()

    // Force into reset (i.e. power it off)
    // Reset value: 0x00000000
    BEGIN_TYPE(FRCE_OFF_t, uint32_t)
        ADD_BITFIELD_RW(proc1, 16, 1)
        ADD_BITFIELD_RW(proc0, 15, 1)
        ADD_BITFIELD_RW(sio, 14, 1)
        ADD_BITFIELD_RW(vreg_and_chip_reset, 13, 1)
        ADD_BITFIELD_RW(xip, 12, 1)
        ADD_BITFIELD_RW(sram5, 11, 1)
        ADD_BITFIELD_RW(sram4, 10, 1)
        ADD_BITFIELD_RW(sram3, 9, 1)
        ADD_BITFIELD_RW(sram2, 8, 1)
        ADD_BITFIELD_RW(sram1, 7, 1)
        ADD_BITFIELD_RW(sram0, 6, 1)
        ADD_BITFIELD_RW(rom, 5, 1)
        ADD_BITFIELD_RW(busfabric, 4, 1)
        ADD_BITFIELD_RW(resets, 3, 1)
        ADD_BITFIELD_RW(clocks, 2, 1)
        ADD_BITFIELD_RW(xosc, 1, 1)
        ADD_BITFIELD_RW(rosc, 0, 1)
    END_TYPE()

    // Set to 1 if this peripheral should be reset when the watchdog fires.
    // Reset value: 0x00000000
    BEGIN_TYPE(WDSEL_t, uint32_t)
        ADD_BITFIELD_RW(proc1, 16, 1)
        ADD_BITFIELD_RW(proc0, 15, 1)
        ADD_BITFIELD_RW(sio, 14, 1)
        ADD_BITFIELD_RW(vreg_and_chip_reset, 13, 1)
        ADD_BITFIELD_RW(xip, 12, 1)
        ADD_BITFIELD_RW(sram5, 11, 1)
        ADD_BITFIELD_RW(sram4, 10, 1)
        ADD_BITFIELD_RW(sram3, 9, 1)
        ADD_BITFIELD_RW(sram2, 8, 1)
        ADD_BITFIELD_RW(sram1, 7, 1)
        ADD_BITFIELD_RW(sram0, 6, 1)
        ADD_BITFIELD_RW(rom, 5, 1)
        ADD_BITFIELD_RW(busfabric, 4, 1)
        ADD_BITFIELD_RW(resets, 3, 1)
        ADD_BITFIELD_RW(clocks, 2, 1)
        ADD_BITFIELD_RW(xosc, 1, 1)
        ADD_BITFIELD_RW(rosc, 0, 1)
    END_TYPE()

    // Indicates the peripheral's registers are ready to access.
    // Reset value: 0x00000000
    BEGIN_TYPE(DONE_t, uint32_t)
        ADD_BITFIELD_RO(proc1, 16, 1)
        ADD_BITFIELD_RO(proc0, 15, 1)
        ADD_BITFIELD_RO(sio, 14, 1)
        ADD_BITFIELD_RO(vreg_and_chip_reset, 13, 1)
        ADD_BITFIELD_RO(xip, 12, 1)
        ADD_BITFIELD_RO(sram5, 11, 1)
        ADD_BITFIELD_RO(sram4, 10, 1)
        ADD_BITFIELD_RO(sram3, 9, 1)
        ADD_BITFIELD_RO(sram2, 8, 1)
        ADD_BITFIELD_RO(sram1, 7, 1)
        ADD_BITFIELD_RO(sram0, 6, 1)
        ADD_BITFIELD_RO(rom, 5, 1)
        ADD_BITFIELD_RO(busfabric, 4, 1)
        ADD_BITFIELD_RO(resets, 3, 1)
        ADD_BITFIELD_RO(clocks, 2, 1)
        ADD_BITFIELD_RO(xosc, 1, 1)
        ADD_BITFIELD_RO(rosc, 0, 1)
    END_TYPE()

    struct PSM_t {
        FRCE_ON_t                     FRCE_ON;
        FRCE_OFF_t                    FRCE_OFF;
        WDSEL_t                       WDSEL;
        DONE_t                        DONE;
    };

    static PSM_t & PSM = (*(PSM_t *)0x40010000);
    static PSM_t & PSM_XOR = (*(PSM_t *)0x40011000);
    static PSM_t & PSM_SET = (*(PSM_t *)0x40012000);
    static PSM_t & PSM_CLR = (*(PSM_t *)0x40013000);

} // _PSM_

namespace _IO_BANK0_  {

    // GPIO status
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_STATUS_t, uint32_t)
        // interrupt to processors, after override is applied
        ADD_BITFIELD_RO(IRQTOPROC, 26, 1)
        // interrupt from pad before override is applied
        ADD_BITFIELD_RO(IRQFROMPAD, 24, 1)
        // input signal to peripheral, after override is applied
        ADD_BITFIELD_RO(INTOPERI, 19, 1)
        // input signal from pad, before override is applied
        ADD_BITFIELD_RO(INFROMPAD, 17, 1)
        // output enable to pad after register override is applied
        ADD_BITFIELD_RO(OETOPAD, 13, 1)
        // output enable from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OEFROMPERI, 12, 1)
        // output signal to pad after register override is applied
        ADD_BITFIELD_RO(OUTTOPAD, 9, 1)
        // output signal from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OUTFROMPERI, 8, 1)
    END_TYPE()

    // GPIO control including function select and overrides.
    // Reset value: 0x0000001f
    BEGIN_TYPE(GPIO_CTRL_t, uint32_t)
        ADD_BITFIELD_RW(IRQOVER, 28, 2)
        ADD_BITFIELD_RW(INOVER, 16, 2)
        ADD_BITFIELD_RW(OEOVER, 12, 2)
        ADD_BITFIELD_RW(OUTOVER, 8, 2)
        // 0-31 -> selects pin function according to the gpio table
        // 31 == NULL
        ADD_BITFIELD_RW(FUNCSEL, 0, 5)
    END_TYPE()

    // don't invert the interrupt
    static const uint32_t GPIO_CTRL_IRQOVER__NORMAL = 0;
    // invert the interrupt
    static const uint32_t GPIO_CTRL_IRQOVER__INVERT = 1;
    // drive interrupt low
    static const uint32_t GPIO_CTRL_IRQOVER__LOW = 2;
    // drive interrupt high
    static const uint32_t GPIO_CTRL_IRQOVER__HIGH = 3;
    // don't invert the peri input
    static const uint32_t GPIO_CTRL_INOVER__NORMAL = 0;
    // invert the peri input
    static const uint32_t GPIO_CTRL_INOVER__INVERT = 1;
    // drive peri input low
    static const uint32_t GPIO_CTRL_INOVER__LOW = 2;
    // drive peri input high
    static const uint32_t GPIO_CTRL_INOVER__HIGH = 3;
    // drive output enable from peripheral signal selected by funcsel
    static const uint32_t GPIO_CTRL_OEOVER__NORMAL = 0;
    // drive output enable from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_CTRL_OEOVER__INVERT = 1;
    // disable output
    static const uint32_t GPIO_CTRL_OEOVER__DISABLE = 2;
    // enable output
    static const uint32_t GPIO_CTRL_OEOVER__ENABLE = 3;
    // drive output from peripheral signal selected by funcsel
    static const uint32_t GPIO_CTRL_OUTOVER__NORMAL = 0;
    // drive output from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_CTRL_OUTOVER__INVERT = 1;
    // drive output low
    static const uint32_t GPIO_CTRL_OUTOVER__LOW = 2;
    // drive output high
    static const uint32_t GPIO_CTRL_OUTOVER__HIGH = 3;
    static const uint32_t GPIO_CTRL_FUNCSEL__jtag = 0;
    static const uint32_t GPIO_CTRL_FUNCSEL__spi = 1;
    static const uint32_t GPIO_CTRL_FUNCSEL__uart = 2;
    static const uint32_t GPIO_CTRL_FUNCSEL__i2c = 3;
    static const uint32_t GPIO_CTRL_FUNCSEL__pwm = 4;
    static const uint32_t GPIO_CTRL_FUNCSEL__sio = 5;
    static const uint32_t GPIO_CTRL_FUNCSEL__pio0 = 6;
    static const uint32_t GPIO_CTRL_FUNCSEL__pio1 = 7;
    static const uint32_t GPIO_CTRL_FUNCSEL__clock = 8;
    static const uint32_t GPIO_CTRL_FUNCSEL__usb = 9;
    static const uint32_t GPIO_CTRL_FUNCSEL__null = 31;

    // Raw Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR0_t, uint32_t)
        ADD_BITFIELD_RW(GPIO7_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO7_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RO(GPIO7_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RO(GPIO7_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RO(GPIO6_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RO(GPIO6_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO5_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO5_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO4_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO4_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO3_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO3_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO2_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO2_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO1_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO1_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO0_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO0_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Raw Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR1_t, uint32_t)
        ADD_BITFIELD_RW(GPIO15_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO15_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RO(GPIO15_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RO(GPIO15_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RO(GPIO14_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RO(GPIO14_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO13_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO13_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO12_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO12_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO11_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO11_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO10_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO10_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO9_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO9_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO8_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO8_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Raw Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR2_t, uint32_t)
        ADD_BITFIELD_RW(GPIO23_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO23_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RO(GPIO23_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RO(GPIO23_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RO(GPIO22_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RO(GPIO22_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO21_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO21_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO20_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO20_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO19_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO19_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO18_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO18_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO17_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO17_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO16_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO16_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Raw Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR3_t, uint32_t)
        ADD_BITFIELD_RW(GPIO29_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO29_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO29_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO29_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO28_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO28_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO27_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO27_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO26_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO26_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO25_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO25_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO24_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO24_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTE0_t, uint32_t)
        ADD_BITFIELD_RW(GPIO7_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO7_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO7_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO7_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO6_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO6_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO5_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO5_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO4_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO4_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO3_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO3_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO2_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO2_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO1_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO1_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO0_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO0_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTE1_t, uint32_t)
        ADD_BITFIELD_RW(GPIO15_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO15_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO15_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO15_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO14_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO14_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO13_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO13_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO12_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO12_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO11_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO11_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO10_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO10_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO9_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO9_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO8_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO8_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTE2_t, uint32_t)
        ADD_BITFIELD_RW(GPIO23_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO23_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO23_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO23_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO22_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO22_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO21_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO21_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO20_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO20_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO19_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO19_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO18_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO18_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO17_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO17_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO16_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO16_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTE3_t, uint32_t)
        ADD_BITFIELD_RW(GPIO29_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO29_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO29_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO29_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO28_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO28_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO27_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO27_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO26_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO26_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO25_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO25_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO24_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO24_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTF0_t, uint32_t)
        ADD_BITFIELD_RW(GPIO7_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO7_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO7_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO7_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO6_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO6_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO5_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO5_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO4_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO4_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO3_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO3_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO2_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO2_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO1_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO1_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO0_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO0_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTF1_t, uint32_t)
        ADD_BITFIELD_RW(GPIO15_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO15_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO15_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO15_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO14_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO14_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO13_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO13_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO12_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO12_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO11_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO11_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO10_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO10_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO9_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO9_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO8_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO8_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTF2_t, uint32_t)
        ADD_BITFIELD_RW(GPIO23_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO23_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO23_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO23_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO22_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO22_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO21_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO21_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO20_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO20_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO19_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO19_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO18_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO18_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO17_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO17_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO16_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO16_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTF3_t, uint32_t)
        ADD_BITFIELD_RW(GPIO29_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO29_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO29_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO29_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO28_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO28_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO27_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO27_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO26_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO26_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO25_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO25_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO24_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO24_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTS0_t, uint32_t)
        ADD_BITFIELD_RO(GPIO7_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RO(GPIO7_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RO(GPIO7_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RO(GPIO7_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RO(GPIO6_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RO(GPIO6_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RO(GPIO6_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RO(GPIO6_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RO(GPIO5_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO5_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO5_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO5_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO4_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO4_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO4_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO4_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO3_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO3_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO3_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO3_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO2_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO2_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO2_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO2_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO1_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO1_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO1_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO1_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO0_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO0_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO0_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO0_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTS1_t, uint32_t)
        ADD_BITFIELD_RO(GPIO15_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RO(GPIO15_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RO(GPIO15_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RO(GPIO15_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RO(GPIO14_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RO(GPIO14_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RO(GPIO14_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RO(GPIO14_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RO(GPIO13_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO13_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO13_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO13_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO12_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO12_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO12_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO12_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO11_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO11_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO11_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO11_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO10_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO10_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO10_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO10_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO9_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO9_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO9_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO9_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO8_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO8_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO8_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO8_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTS2_t, uint32_t)
        ADD_BITFIELD_RO(GPIO23_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RO(GPIO23_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RO(GPIO23_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RO(GPIO23_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RO(GPIO22_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RO(GPIO22_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RO(GPIO22_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RO(GPIO22_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RO(GPIO21_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO21_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO21_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO21_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO20_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO20_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO20_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO20_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO19_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO19_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO19_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO19_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO18_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO18_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO18_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO18_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO17_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO17_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO17_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO17_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO16_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO16_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO16_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO16_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTS3_t, uint32_t)
        ADD_BITFIELD_RO(GPIO29_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO29_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO29_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO29_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO28_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO28_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO28_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO28_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO27_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO27_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO27_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO27_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO26_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO26_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO26_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO26_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO25_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO25_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO25_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO25_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO24_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO24_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO24_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO24_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTE0_t, uint32_t)
        ADD_BITFIELD_RW(GPIO7_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO7_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO7_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO7_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO6_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO6_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO5_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO5_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO4_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO4_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO3_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO3_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO2_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO2_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO1_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO1_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO0_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO0_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTE1_t, uint32_t)
        ADD_BITFIELD_RW(GPIO15_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO15_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO15_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO15_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO14_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO14_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO13_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO13_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO12_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO12_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO11_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO11_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO10_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO10_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO9_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO9_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO8_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO8_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTE2_t, uint32_t)
        ADD_BITFIELD_RW(GPIO23_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO23_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO23_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO23_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO22_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO22_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO21_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO21_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO20_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO20_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO19_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO19_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO18_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO18_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO17_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO17_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO16_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO16_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTE3_t, uint32_t)
        ADD_BITFIELD_RW(GPIO29_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO29_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO29_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO29_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO28_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO28_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO27_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO27_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO26_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO26_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO25_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO25_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO24_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO24_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTF0_t, uint32_t)
        ADD_BITFIELD_RW(GPIO7_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO7_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO7_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO7_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO6_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO6_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO5_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO5_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO4_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO4_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO3_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO3_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO2_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO2_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO1_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO1_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO0_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO0_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTF1_t, uint32_t)
        ADD_BITFIELD_RW(GPIO15_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO15_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO15_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO15_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO14_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO14_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO13_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO13_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO12_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO12_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO11_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO11_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO10_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO10_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO9_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO9_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO8_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO8_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTF2_t, uint32_t)
        ADD_BITFIELD_RW(GPIO23_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO23_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO23_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO23_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO22_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO22_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO21_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO21_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO20_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO20_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO19_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO19_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO18_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO18_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO17_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO17_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO16_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO16_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTF3_t, uint32_t)
        ADD_BITFIELD_RW(GPIO29_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO29_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO29_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO29_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO28_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO28_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO27_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO27_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO26_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO26_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO25_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO25_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO24_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO24_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTS0_t, uint32_t)
        ADD_BITFIELD_RO(GPIO7_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RO(GPIO7_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RO(GPIO7_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RO(GPIO7_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RO(GPIO6_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RO(GPIO6_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RO(GPIO6_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RO(GPIO6_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RO(GPIO5_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO5_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO5_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO5_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO4_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO4_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO4_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO4_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO3_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO3_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO3_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO3_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO2_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO2_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO2_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO2_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO1_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO1_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO1_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO1_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO0_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO0_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO0_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO0_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTS1_t, uint32_t)
        ADD_BITFIELD_RO(GPIO15_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RO(GPIO15_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RO(GPIO15_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RO(GPIO15_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RO(GPIO14_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RO(GPIO14_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RO(GPIO14_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RO(GPIO14_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RO(GPIO13_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO13_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO13_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO13_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO12_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO12_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO12_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO12_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO11_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO11_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO11_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO11_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO10_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO10_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO10_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO10_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO9_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO9_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO9_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO9_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO8_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO8_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO8_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO8_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTS2_t, uint32_t)
        ADD_BITFIELD_RO(GPIO23_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RO(GPIO23_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RO(GPIO23_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RO(GPIO23_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RO(GPIO22_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RO(GPIO22_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RO(GPIO22_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RO(GPIO22_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RO(GPIO21_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO21_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO21_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO21_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO20_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO20_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO20_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO20_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO19_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO19_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO19_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO19_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO18_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO18_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO18_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO18_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO17_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO17_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO17_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO17_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO16_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO16_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO16_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO16_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTS3_t, uint32_t)
        ADD_BITFIELD_RO(GPIO29_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO29_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO29_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO29_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO28_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO28_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO28_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO28_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO27_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO27_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO27_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO27_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO26_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO26_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO26_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO26_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO25_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO25_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO25_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO25_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO24_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO24_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO24_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO24_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTE0_t, uint32_t)
        ADD_BITFIELD_RW(GPIO7_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO7_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO7_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO7_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO6_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO6_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO5_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO5_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO4_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO4_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO3_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO3_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO2_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO2_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO1_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO1_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO0_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO0_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTE1_t, uint32_t)
        ADD_BITFIELD_RW(GPIO15_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO15_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO15_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO15_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO14_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO14_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO13_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO13_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO12_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO12_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO11_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO11_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO10_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO10_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO9_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO9_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO8_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO8_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTE2_t, uint32_t)
        ADD_BITFIELD_RW(GPIO23_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO23_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO23_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO23_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO22_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO22_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO21_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO21_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO20_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO20_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO19_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO19_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO18_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO18_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO17_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO17_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO16_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO16_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTE3_t, uint32_t)
        ADD_BITFIELD_RW(GPIO29_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO29_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO29_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO29_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO28_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO28_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO27_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO27_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO26_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO26_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO25_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO25_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO24_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO24_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTF0_t, uint32_t)
        ADD_BITFIELD_RW(GPIO7_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO7_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO7_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO7_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO6_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO6_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO6_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO5_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO5_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO5_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO4_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO4_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO4_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO3_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO3_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO3_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO2_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO2_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO2_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO1_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO1_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO1_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO0_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO0_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO0_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTF1_t, uint32_t)
        ADD_BITFIELD_RW(GPIO15_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO15_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO15_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO15_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO14_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO14_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO14_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO13_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO13_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO13_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO12_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO12_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO12_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO11_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO11_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO11_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO10_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO10_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO10_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO9_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO9_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO9_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO8_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO8_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO8_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTF2_t, uint32_t)
        ADD_BITFIELD_RW(GPIO23_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RW(GPIO23_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RW(GPIO23_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RW(GPIO23_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RW(GPIO22_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RW(GPIO22_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RW(GPIO22_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO21_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO21_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO21_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO20_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO20_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO20_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO19_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO19_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO19_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO18_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO18_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO18_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO17_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO17_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO17_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO16_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO16_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO16_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTF3_t, uint32_t)
        ADD_BITFIELD_RW(GPIO29_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO29_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO29_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO29_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO28_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO28_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO28_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO27_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO27_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO27_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO26_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO26_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO26_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO25_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO25_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO25_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO24_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO24_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO24_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTS0_t, uint32_t)
        ADD_BITFIELD_RO(GPIO7_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RO(GPIO7_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RO(GPIO7_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RO(GPIO7_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RO(GPIO6_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RO(GPIO6_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RO(GPIO6_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RO(GPIO6_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RO(GPIO5_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO5_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO5_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO5_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO4_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO4_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO4_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO4_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO3_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO3_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO3_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO3_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO2_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO2_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO2_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO2_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO1_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO1_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO1_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO1_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO0_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO0_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO0_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO0_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTS1_t, uint32_t)
        ADD_BITFIELD_RO(GPIO15_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RO(GPIO15_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RO(GPIO15_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RO(GPIO15_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RO(GPIO14_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RO(GPIO14_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RO(GPIO14_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RO(GPIO14_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RO(GPIO13_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO13_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO13_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO13_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO12_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO12_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO12_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO12_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO11_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO11_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO11_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO11_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO10_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO10_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO10_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO10_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO9_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO9_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO9_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO9_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO8_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO8_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO8_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO8_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTS2_t, uint32_t)
        ADD_BITFIELD_RO(GPIO23_EDGE_HIGH, 31, 1)
        ADD_BITFIELD_RO(GPIO23_EDGE_LOW, 30, 1)
        ADD_BITFIELD_RO(GPIO23_LEVEL_HIGH, 29, 1)
        ADD_BITFIELD_RO(GPIO23_LEVEL_LOW, 28, 1)
        ADD_BITFIELD_RO(GPIO22_EDGE_HIGH, 27, 1)
        ADD_BITFIELD_RO(GPIO22_EDGE_LOW, 26, 1)
        ADD_BITFIELD_RO(GPIO22_LEVEL_HIGH, 25, 1)
        ADD_BITFIELD_RO(GPIO22_LEVEL_LOW, 24, 1)
        ADD_BITFIELD_RO(GPIO21_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO21_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO21_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO21_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO20_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO20_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO20_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO20_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO19_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO19_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO19_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO19_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO18_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO18_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO18_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO18_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO17_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO17_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO17_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO17_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO16_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO16_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO16_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO16_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTS3_t, uint32_t)
        ADD_BITFIELD_RO(GPIO29_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO29_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO29_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO29_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO28_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO28_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO28_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO28_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO27_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO27_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO27_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO27_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO26_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO26_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO26_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO26_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO25_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO25_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO25_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO25_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO24_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO24_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO24_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO24_LEVEL_LOW, 0, 1)
    END_TYPE()

    struct IO_BANK0_t {
        GPIO_STATUS_t                 GPIO0_STATUS;
        GPIO_CTRL_t                   GPIO0_CTRL;
        GPIO_STATUS_t                 GPIO1_STATUS;
        GPIO_CTRL_t                   GPIO1_CTRL;
        GPIO_STATUS_t                 GPIO2_STATUS;
        GPIO_CTRL_t                   GPIO2_CTRL;
        GPIO_STATUS_t                 GPIO3_STATUS;
        GPIO_CTRL_t                   GPIO3_CTRL;
        GPIO_STATUS_t                 GPIO4_STATUS;
        GPIO_CTRL_t                   GPIO4_CTRL;
        GPIO_STATUS_t                 GPIO5_STATUS;
        GPIO_CTRL_t                   GPIO5_CTRL;
        GPIO_STATUS_t                 GPIO6_STATUS;
        GPIO_CTRL_t                   GPIO6_CTRL;
        GPIO_STATUS_t                 GPIO7_STATUS;
        GPIO_CTRL_t                   GPIO7_CTRL;
        GPIO_STATUS_t                 GPIO8_STATUS;
        GPIO_CTRL_t                   GPIO8_CTRL;
        GPIO_STATUS_t                 GPIO9_STATUS;
        GPIO_CTRL_t                   GPIO9_CTRL;
        GPIO_STATUS_t                 GPIO10_STATUS;
        GPIO_CTRL_t                   GPIO10_CTRL;
        GPIO_STATUS_t                 GPIO11_STATUS;
        GPIO_CTRL_t                   GPIO11_CTRL;
        GPIO_STATUS_t                 GPIO12_STATUS;
        GPIO_CTRL_t                   GPIO12_CTRL;
        GPIO_STATUS_t                 GPIO13_STATUS;
        GPIO_CTRL_t                   GPIO13_CTRL;
        GPIO_STATUS_t                 GPIO14_STATUS;
        GPIO_CTRL_t                   GPIO14_CTRL;
        GPIO_STATUS_t                 GPIO15_STATUS;
        GPIO_CTRL_t                   GPIO15_CTRL;
        GPIO_STATUS_t                 GPIO16_STATUS;
        GPIO_CTRL_t                   GPIO16_CTRL;
        GPIO_STATUS_t                 GPIO17_STATUS;
        GPIO_CTRL_t                   GPIO17_CTRL;
        GPIO_STATUS_t                 GPIO18_STATUS;
        GPIO_CTRL_t                   GPIO18_CTRL;
        GPIO_STATUS_t                 GPIO19_STATUS;
        GPIO_CTRL_t                   GPIO19_CTRL;
        GPIO_STATUS_t                 GPIO20_STATUS;
        GPIO_CTRL_t                   GPIO20_CTRL;
        GPIO_STATUS_t                 GPIO21_STATUS;
        GPIO_CTRL_t                   GPIO21_CTRL;
        GPIO_STATUS_t                 GPIO22_STATUS;
        GPIO_CTRL_t                   GPIO22_CTRL;
        GPIO_STATUS_t                 GPIO23_STATUS;
        GPIO_CTRL_t                   GPIO23_CTRL;
        GPIO_STATUS_t                 GPIO24_STATUS;
        GPIO_CTRL_t                   GPIO24_CTRL;
        GPIO_STATUS_t                 GPIO25_STATUS;
        GPIO_CTRL_t                   GPIO25_CTRL;
        GPIO_STATUS_t                 GPIO26_STATUS;
        GPIO_CTRL_t                   GPIO26_CTRL;
        GPIO_STATUS_t                 GPIO27_STATUS;
        GPIO_CTRL_t                   GPIO27_CTRL;
        GPIO_STATUS_t                 GPIO28_STATUS;
        GPIO_CTRL_t                   GPIO28_CTRL;
        GPIO_STATUS_t                 GPIO29_STATUS;
        GPIO_CTRL_t                   GPIO29_CTRL;
        INTR0_t                       INTR0;
        INTR1_t                       INTR1;
        INTR2_t                       INTR2;
        INTR3_t                       INTR3;
        PROC0_INTE0_t                 PROC0_INTE0;
        PROC0_INTE1_t                 PROC0_INTE1;
        PROC0_INTE2_t                 PROC0_INTE2;
        PROC0_INTE3_t                 PROC0_INTE3;
        PROC0_INTF0_t                 PROC0_INTF0;
        PROC0_INTF1_t                 PROC0_INTF1;
        PROC0_INTF2_t                 PROC0_INTF2;
        PROC0_INTF3_t                 PROC0_INTF3;
        PROC0_INTS0_t                 PROC0_INTS0;
        PROC0_INTS1_t                 PROC0_INTS1;
        PROC0_INTS2_t                 PROC0_INTS2;
        PROC0_INTS3_t                 PROC0_INTS3;
        PROC1_INTE0_t                 PROC1_INTE0;
        PROC1_INTE1_t                 PROC1_INTE1;
        PROC1_INTE2_t                 PROC1_INTE2;
        PROC1_INTE3_t                 PROC1_INTE3;
        PROC1_INTF0_t                 PROC1_INTF0;
        PROC1_INTF1_t                 PROC1_INTF1;
        PROC1_INTF2_t                 PROC1_INTF2;
        PROC1_INTF3_t                 PROC1_INTF3;
        PROC1_INTS0_t                 PROC1_INTS0;
        PROC1_INTS1_t                 PROC1_INTS1;
        PROC1_INTS2_t                 PROC1_INTS2;
        PROC1_INTS3_t                 PROC1_INTS3;
        DORMANT_WAKE_INTE0_t          DORMANT_WAKE_INTE0;
        DORMANT_WAKE_INTE1_t          DORMANT_WAKE_INTE1;
        DORMANT_WAKE_INTE2_t          DORMANT_WAKE_INTE2;
        DORMANT_WAKE_INTE3_t          DORMANT_WAKE_INTE3;
        DORMANT_WAKE_INTF0_t          DORMANT_WAKE_INTF0;
        DORMANT_WAKE_INTF1_t          DORMANT_WAKE_INTF1;
        DORMANT_WAKE_INTF2_t          DORMANT_WAKE_INTF2;
        DORMANT_WAKE_INTF3_t          DORMANT_WAKE_INTF3;
        DORMANT_WAKE_INTS0_t          DORMANT_WAKE_INTS0;
        DORMANT_WAKE_INTS1_t          DORMANT_WAKE_INTS1;
        DORMANT_WAKE_INTS2_t          DORMANT_WAKE_INTS2;
        DORMANT_WAKE_INTS3_t          DORMANT_WAKE_INTS3;
    };

    static IO_BANK0_t & IO_BANK0 = (*(IO_BANK0_t *)0x40014000);
    static IO_BANK0_t & IO_BANK0_XOR = (*(IO_BANK0_t *)0x40015000);
    static IO_BANK0_t & IO_BANK0_SET = (*(IO_BANK0_t *)0x40016000);
    static IO_BANK0_t & IO_BANK0_CLR = (*(IO_BANK0_t *)0x40017000);

} // _IO_BANK0_

namespace _IO_QSPI_  {

    // GPIO status
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_QSPI_SCLK_STATUS_t, uint32_t)
        // interrupt to processors, after override is applied
        ADD_BITFIELD_RO(IRQTOPROC, 26, 1)
        // interrupt from pad before override is applied
        ADD_BITFIELD_RO(IRQFROMPAD, 24, 1)
        // input signal to peripheral, after override is applied
        ADD_BITFIELD_RO(INTOPERI, 19, 1)
        // input signal from pad, before override is applied
        ADD_BITFIELD_RO(INFROMPAD, 17, 1)
        // output enable to pad after register override is applied
        ADD_BITFIELD_RO(OETOPAD, 13, 1)
        // output enable from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OEFROMPERI, 12, 1)
        // output signal to pad after register override is applied
        ADD_BITFIELD_RO(OUTTOPAD, 9, 1)
        // output signal from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OUTFROMPERI, 8, 1)
    END_TYPE()

    // GPIO control including function select and overrides.
    // Reset value: 0x0000001f
    BEGIN_TYPE(GPIO_QSPI_SCLK_CTRL_t, uint32_t)
        ADD_BITFIELD_RW(IRQOVER, 28, 2)
        ADD_BITFIELD_RW(INOVER, 16, 2)
        ADD_BITFIELD_RW(OEOVER, 12, 2)
        ADD_BITFIELD_RW(OUTOVER, 8, 2)
        // 0-31 -> selects pin function according to the gpio table
        // 31 == NULL
        ADD_BITFIELD_RW(FUNCSEL, 0, 5)
    END_TYPE()

    // don't invert the interrupt
    static const uint32_t GPIO_QSPI_SCLK_CTRL_IRQOVER__NORMAL = 0;
    // invert the interrupt
    static const uint32_t GPIO_QSPI_SCLK_CTRL_IRQOVER__INVERT = 1;
    // drive interrupt low
    static const uint32_t GPIO_QSPI_SCLK_CTRL_IRQOVER__LOW = 2;
    // drive interrupt high
    static const uint32_t GPIO_QSPI_SCLK_CTRL_IRQOVER__HIGH = 3;
    // don't invert the peri input
    static const uint32_t GPIO_QSPI_SCLK_CTRL_INOVER__NORMAL = 0;
    // invert the peri input
    static const uint32_t GPIO_QSPI_SCLK_CTRL_INOVER__INVERT = 1;
    // drive peri input low
    static const uint32_t GPIO_QSPI_SCLK_CTRL_INOVER__LOW = 2;
    // drive peri input high
    static const uint32_t GPIO_QSPI_SCLK_CTRL_INOVER__HIGH = 3;
    // drive output enable from peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SCLK_CTRL_OEOVER__NORMAL = 0;
    // drive output enable from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SCLK_CTRL_OEOVER__INVERT = 1;
    // disable output
    static const uint32_t GPIO_QSPI_SCLK_CTRL_OEOVER__DISABLE = 2;
    // enable output
    static const uint32_t GPIO_QSPI_SCLK_CTRL_OEOVER__ENABLE = 3;
    // drive output from peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SCLK_CTRL_OUTOVER__NORMAL = 0;
    // drive output from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SCLK_CTRL_OUTOVER__INVERT = 1;
    // drive output low
    static const uint32_t GPIO_QSPI_SCLK_CTRL_OUTOVER__LOW = 2;
    // drive output high
    static const uint32_t GPIO_QSPI_SCLK_CTRL_OUTOVER__HIGH = 3;
    static const uint32_t GPIO_QSPI_SCLK_CTRL_FUNCSEL__xip_sclk = 0;
    static const uint32_t GPIO_QSPI_SCLK_CTRL_FUNCSEL__sio_30 = 5;
    static const uint32_t GPIO_QSPI_SCLK_CTRL_FUNCSEL__null = 31;

    // GPIO status
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_QSPI_SS_STATUS_t, uint32_t)
        // interrupt to processors, after override is applied
        ADD_BITFIELD_RO(IRQTOPROC, 26, 1)
        // interrupt from pad before override is applied
        ADD_BITFIELD_RO(IRQFROMPAD, 24, 1)
        // input signal to peripheral, after override is applied
        ADD_BITFIELD_RO(INTOPERI, 19, 1)
        // input signal from pad, before override is applied
        ADD_BITFIELD_RO(INFROMPAD, 17, 1)
        // output enable to pad after register override is applied
        ADD_BITFIELD_RO(OETOPAD, 13, 1)
        // output enable from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OEFROMPERI, 12, 1)
        // output signal to pad after register override is applied
        ADD_BITFIELD_RO(OUTTOPAD, 9, 1)
        // output signal from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OUTFROMPERI, 8, 1)
    END_TYPE()

    // GPIO control including function select and overrides.
    // Reset value: 0x0000001f
    BEGIN_TYPE(GPIO_QSPI_SS_CTRL_t, uint32_t)
        ADD_BITFIELD_RW(IRQOVER, 28, 2)
        ADD_BITFIELD_RW(INOVER, 16, 2)
        ADD_BITFIELD_RW(OEOVER, 12, 2)
        ADD_BITFIELD_RW(OUTOVER, 8, 2)
        // 0-31 -> selects pin function according to the gpio table
        // 31 == NULL
        ADD_BITFIELD_RW(FUNCSEL, 0, 5)
    END_TYPE()

    // don't invert the interrupt
    static const uint32_t GPIO_QSPI_SS_CTRL_IRQOVER__NORMAL = 0;
    // invert the interrupt
    static const uint32_t GPIO_QSPI_SS_CTRL_IRQOVER__INVERT = 1;
    // drive interrupt low
    static const uint32_t GPIO_QSPI_SS_CTRL_IRQOVER__LOW = 2;
    // drive interrupt high
    static const uint32_t GPIO_QSPI_SS_CTRL_IRQOVER__HIGH = 3;
    // don't invert the peri input
    static const uint32_t GPIO_QSPI_SS_CTRL_INOVER__NORMAL = 0;
    // invert the peri input
    static const uint32_t GPIO_QSPI_SS_CTRL_INOVER__INVERT = 1;
    // drive peri input low
    static const uint32_t GPIO_QSPI_SS_CTRL_INOVER__LOW = 2;
    // drive peri input high
    static const uint32_t GPIO_QSPI_SS_CTRL_INOVER__HIGH = 3;
    // drive output enable from peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SS_CTRL_OEOVER__NORMAL = 0;
    // drive output enable from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SS_CTRL_OEOVER__INVERT = 1;
    // disable output
    static const uint32_t GPIO_QSPI_SS_CTRL_OEOVER__DISABLE = 2;
    // enable output
    static const uint32_t GPIO_QSPI_SS_CTRL_OEOVER__ENABLE = 3;
    // drive output from peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SS_CTRL_OUTOVER__NORMAL = 0;
    // drive output from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SS_CTRL_OUTOVER__INVERT = 1;
    // drive output low
    static const uint32_t GPIO_QSPI_SS_CTRL_OUTOVER__LOW = 2;
    // drive output high
    static const uint32_t GPIO_QSPI_SS_CTRL_OUTOVER__HIGH = 3;
    static const uint32_t GPIO_QSPI_SS_CTRL_FUNCSEL__xip_ss_n = 0;
    static const uint32_t GPIO_QSPI_SS_CTRL_FUNCSEL__sio_31 = 5;
    static const uint32_t GPIO_QSPI_SS_CTRL_FUNCSEL__null = 31;

    // GPIO status
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_QSPI_SD0_STATUS_t, uint32_t)
        // interrupt to processors, after override is applied
        ADD_BITFIELD_RO(IRQTOPROC, 26, 1)
        // interrupt from pad before override is applied
        ADD_BITFIELD_RO(IRQFROMPAD, 24, 1)
        // input signal to peripheral, after override is applied
        ADD_BITFIELD_RO(INTOPERI, 19, 1)
        // input signal from pad, before override is applied
        ADD_BITFIELD_RO(INFROMPAD, 17, 1)
        // output enable to pad after register override is applied
        ADD_BITFIELD_RO(OETOPAD, 13, 1)
        // output enable from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OEFROMPERI, 12, 1)
        // output signal to pad after register override is applied
        ADD_BITFIELD_RO(OUTTOPAD, 9, 1)
        // output signal from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OUTFROMPERI, 8, 1)
    END_TYPE()

    // GPIO control including function select and overrides.
    // Reset value: 0x0000001f
    BEGIN_TYPE(GPIO_QSPI_SD0_CTRL_t, uint32_t)
        ADD_BITFIELD_RW(IRQOVER, 28, 2)
        ADD_BITFIELD_RW(INOVER, 16, 2)
        ADD_BITFIELD_RW(OEOVER, 12, 2)
        ADD_BITFIELD_RW(OUTOVER, 8, 2)
        // 0-31 -> selects pin function according to the gpio table
        // 31 == NULL
        ADD_BITFIELD_RW(FUNCSEL, 0, 5)
    END_TYPE()

    // don't invert the interrupt
    static const uint32_t GPIO_QSPI_SD0_CTRL_IRQOVER__NORMAL = 0;
    // invert the interrupt
    static const uint32_t GPIO_QSPI_SD0_CTRL_IRQOVER__INVERT = 1;
    // drive interrupt low
    static const uint32_t GPIO_QSPI_SD0_CTRL_IRQOVER__LOW = 2;
    // drive interrupt high
    static const uint32_t GPIO_QSPI_SD0_CTRL_IRQOVER__HIGH = 3;
    // don't invert the peri input
    static const uint32_t GPIO_QSPI_SD0_CTRL_INOVER__NORMAL = 0;
    // invert the peri input
    static const uint32_t GPIO_QSPI_SD0_CTRL_INOVER__INVERT = 1;
    // drive peri input low
    static const uint32_t GPIO_QSPI_SD0_CTRL_INOVER__LOW = 2;
    // drive peri input high
    static const uint32_t GPIO_QSPI_SD0_CTRL_INOVER__HIGH = 3;
    // drive output enable from peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD0_CTRL_OEOVER__NORMAL = 0;
    // drive output enable from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD0_CTRL_OEOVER__INVERT = 1;
    // disable output
    static const uint32_t GPIO_QSPI_SD0_CTRL_OEOVER__DISABLE = 2;
    // enable output
    static const uint32_t GPIO_QSPI_SD0_CTRL_OEOVER__ENABLE = 3;
    // drive output from peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD0_CTRL_OUTOVER__NORMAL = 0;
    // drive output from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD0_CTRL_OUTOVER__INVERT = 1;
    // drive output low
    static const uint32_t GPIO_QSPI_SD0_CTRL_OUTOVER__LOW = 2;
    // drive output high
    static const uint32_t GPIO_QSPI_SD0_CTRL_OUTOVER__HIGH = 3;
    static const uint32_t GPIO_QSPI_SD0_CTRL_FUNCSEL__xip_sd0 = 0;
    static const uint32_t GPIO_QSPI_SD0_CTRL_FUNCSEL__sio_32 = 5;
    static const uint32_t GPIO_QSPI_SD0_CTRL_FUNCSEL__null = 31;

    // GPIO status
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_QSPI_SD1_STATUS_t, uint32_t)
        // interrupt to processors, after override is applied
        ADD_BITFIELD_RO(IRQTOPROC, 26, 1)
        // interrupt from pad before override is applied
        ADD_BITFIELD_RO(IRQFROMPAD, 24, 1)
        // input signal to peripheral, after override is applied
        ADD_BITFIELD_RO(INTOPERI, 19, 1)
        // input signal from pad, before override is applied
        ADD_BITFIELD_RO(INFROMPAD, 17, 1)
        // output enable to pad after register override is applied
        ADD_BITFIELD_RO(OETOPAD, 13, 1)
        // output enable from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OEFROMPERI, 12, 1)
        // output signal to pad after register override is applied
        ADD_BITFIELD_RO(OUTTOPAD, 9, 1)
        // output signal from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OUTFROMPERI, 8, 1)
    END_TYPE()

    // GPIO control including function select and overrides.
    // Reset value: 0x0000001f
    BEGIN_TYPE(GPIO_QSPI_SD1_CTRL_t, uint32_t)
        ADD_BITFIELD_RW(IRQOVER, 28, 2)
        ADD_BITFIELD_RW(INOVER, 16, 2)
        ADD_BITFIELD_RW(OEOVER, 12, 2)
        ADD_BITFIELD_RW(OUTOVER, 8, 2)
        // 0-31 -> selects pin function according to the gpio table
        // 31 == NULL
        ADD_BITFIELD_RW(FUNCSEL, 0, 5)
    END_TYPE()

    // don't invert the interrupt
    static const uint32_t GPIO_QSPI_SD1_CTRL_IRQOVER__NORMAL = 0;
    // invert the interrupt
    static const uint32_t GPIO_QSPI_SD1_CTRL_IRQOVER__INVERT = 1;
    // drive interrupt low
    static const uint32_t GPIO_QSPI_SD1_CTRL_IRQOVER__LOW = 2;
    // drive interrupt high
    static const uint32_t GPIO_QSPI_SD1_CTRL_IRQOVER__HIGH = 3;
    // don't invert the peri input
    static const uint32_t GPIO_QSPI_SD1_CTRL_INOVER__NORMAL = 0;
    // invert the peri input
    static const uint32_t GPIO_QSPI_SD1_CTRL_INOVER__INVERT = 1;
    // drive peri input low
    static const uint32_t GPIO_QSPI_SD1_CTRL_INOVER__LOW = 2;
    // drive peri input high
    static const uint32_t GPIO_QSPI_SD1_CTRL_INOVER__HIGH = 3;
    // drive output enable from peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD1_CTRL_OEOVER__NORMAL = 0;
    // drive output enable from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD1_CTRL_OEOVER__INVERT = 1;
    // disable output
    static const uint32_t GPIO_QSPI_SD1_CTRL_OEOVER__DISABLE = 2;
    // enable output
    static const uint32_t GPIO_QSPI_SD1_CTRL_OEOVER__ENABLE = 3;
    // drive output from peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD1_CTRL_OUTOVER__NORMAL = 0;
    // drive output from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD1_CTRL_OUTOVER__INVERT = 1;
    // drive output low
    static const uint32_t GPIO_QSPI_SD1_CTRL_OUTOVER__LOW = 2;
    // drive output high
    static const uint32_t GPIO_QSPI_SD1_CTRL_OUTOVER__HIGH = 3;
    static const uint32_t GPIO_QSPI_SD1_CTRL_FUNCSEL__xip_sd1 = 0;
    static const uint32_t GPIO_QSPI_SD1_CTRL_FUNCSEL__sio_33 = 5;
    static const uint32_t GPIO_QSPI_SD1_CTRL_FUNCSEL__null = 31;

    // GPIO status
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_QSPI_SD2_STATUS_t, uint32_t)
        // interrupt to processors, after override is applied
        ADD_BITFIELD_RO(IRQTOPROC, 26, 1)
        // interrupt from pad before override is applied
        ADD_BITFIELD_RO(IRQFROMPAD, 24, 1)
        // input signal to peripheral, after override is applied
        ADD_BITFIELD_RO(INTOPERI, 19, 1)
        // input signal from pad, before override is applied
        ADD_BITFIELD_RO(INFROMPAD, 17, 1)
        // output enable to pad after register override is applied
        ADD_BITFIELD_RO(OETOPAD, 13, 1)
        // output enable from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OEFROMPERI, 12, 1)
        // output signal to pad after register override is applied
        ADD_BITFIELD_RO(OUTTOPAD, 9, 1)
        // output signal from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OUTFROMPERI, 8, 1)
    END_TYPE()

    // GPIO control including function select and overrides.
    // Reset value: 0x0000001f
    BEGIN_TYPE(GPIO_QSPI_SD2_CTRL_t, uint32_t)
        ADD_BITFIELD_RW(IRQOVER, 28, 2)
        ADD_BITFIELD_RW(INOVER, 16, 2)
        ADD_BITFIELD_RW(OEOVER, 12, 2)
        ADD_BITFIELD_RW(OUTOVER, 8, 2)
        // 0-31 -> selects pin function according to the gpio table
        // 31 == NULL
        ADD_BITFIELD_RW(FUNCSEL, 0, 5)
    END_TYPE()

    // don't invert the interrupt
    static const uint32_t GPIO_QSPI_SD2_CTRL_IRQOVER__NORMAL = 0;
    // invert the interrupt
    static const uint32_t GPIO_QSPI_SD2_CTRL_IRQOVER__INVERT = 1;
    // drive interrupt low
    static const uint32_t GPIO_QSPI_SD2_CTRL_IRQOVER__LOW = 2;
    // drive interrupt high
    static const uint32_t GPIO_QSPI_SD2_CTRL_IRQOVER__HIGH = 3;
    // don't invert the peri input
    static const uint32_t GPIO_QSPI_SD2_CTRL_INOVER__NORMAL = 0;
    // invert the peri input
    static const uint32_t GPIO_QSPI_SD2_CTRL_INOVER__INVERT = 1;
    // drive peri input low
    static const uint32_t GPIO_QSPI_SD2_CTRL_INOVER__LOW = 2;
    // drive peri input high
    static const uint32_t GPIO_QSPI_SD2_CTRL_INOVER__HIGH = 3;
    // drive output enable from peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD2_CTRL_OEOVER__NORMAL = 0;
    // drive output enable from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD2_CTRL_OEOVER__INVERT = 1;
    // disable output
    static const uint32_t GPIO_QSPI_SD2_CTRL_OEOVER__DISABLE = 2;
    // enable output
    static const uint32_t GPIO_QSPI_SD2_CTRL_OEOVER__ENABLE = 3;
    // drive output from peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD2_CTRL_OUTOVER__NORMAL = 0;
    // drive output from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD2_CTRL_OUTOVER__INVERT = 1;
    // drive output low
    static const uint32_t GPIO_QSPI_SD2_CTRL_OUTOVER__LOW = 2;
    // drive output high
    static const uint32_t GPIO_QSPI_SD2_CTRL_OUTOVER__HIGH = 3;
    static const uint32_t GPIO_QSPI_SD2_CTRL_FUNCSEL__xip_sd2 = 0;
    static const uint32_t GPIO_QSPI_SD2_CTRL_FUNCSEL__sio_34 = 5;
    static const uint32_t GPIO_QSPI_SD2_CTRL_FUNCSEL__null = 31;

    // GPIO status
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_QSPI_SD3_STATUS_t, uint32_t)
        // interrupt to processors, after override is applied
        ADD_BITFIELD_RO(IRQTOPROC, 26, 1)
        // interrupt from pad before override is applied
        ADD_BITFIELD_RO(IRQFROMPAD, 24, 1)
        // input signal to peripheral, after override is applied
        ADD_BITFIELD_RO(INTOPERI, 19, 1)
        // input signal from pad, before override is applied
        ADD_BITFIELD_RO(INFROMPAD, 17, 1)
        // output enable to pad after register override is applied
        ADD_BITFIELD_RO(OETOPAD, 13, 1)
        // output enable from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OEFROMPERI, 12, 1)
        // output signal to pad after register override is applied
        ADD_BITFIELD_RO(OUTTOPAD, 9, 1)
        // output signal from selected peripheral, before register override is applied
        ADD_BITFIELD_RO(OUTFROMPERI, 8, 1)
    END_TYPE()

    // GPIO control including function select and overrides.
    // Reset value: 0x0000001f
    BEGIN_TYPE(GPIO_QSPI_SD3_CTRL_t, uint32_t)
        ADD_BITFIELD_RW(IRQOVER, 28, 2)
        ADD_BITFIELD_RW(INOVER, 16, 2)
        ADD_BITFIELD_RW(OEOVER, 12, 2)
        ADD_BITFIELD_RW(OUTOVER, 8, 2)
        // 0-31 -> selects pin function according to the gpio table
        // 31 == NULL
        ADD_BITFIELD_RW(FUNCSEL, 0, 5)
    END_TYPE()

    // don't invert the interrupt
    static const uint32_t GPIO_QSPI_SD3_CTRL_IRQOVER__NORMAL = 0;
    // invert the interrupt
    static const uint32_t GPIO_QSPI_SD3_CTRL_IRQOVER__INVERT = 1;
    // drive interrupt low
    static const uint32_t GPIO_QSPI_SD3_CTRL_IRQOVER__LOW = 2;
    // drive interrupt high
    static const uint32_t GPIO_QSPI_SD3_CTRL_IRQOVER__HIGH = 3;
    // don't invert the peri input
    static const uint32_t GPIO_QSPI_SD3_CTRL_INOVER__NORMAL = 0;
    // invert the peri input
    static const uint32_t GPIO_QSPI_SD3_CTRL_INOVER__INVERT = 1;
    // drive peri input low
    static const uint32_t GPIO_QSPI_SD3_CTRL_INOVER__LOW = 2;
    // drive peri input high
    static const uint32_t GPIO_QSPI_SD3_CTRL_INOVER__HIGH = 3;
    // drive output enable from peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD3_CTRL_OEOVER__NORMAL = 0;
    // drive output enable from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD3_CTRL_OEOVER__INVERT = 1;
    // disable output
    static const uint32_t GPIO_QSPI_SD3_CTRL_OEOVER__DISABLE = 2;
    // enable output
    static const uint32_t GPIO_QSPI_SD3_CTRL_OEOVER__ENABLE = 3;
    // drive output from peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD3_CTRL_OUTOVER__NORMAL = 0;
    // drive output from inverse of peripheral signal selected by funcsel
    static const uint32_t GPIO_QSPI_SD3_CTRL_OUTOVER__INVERT = 1;
    // drive output low
    static const uint32_t GPIO_QSPI_SD3_CTRL_OUTOVER__LOW = 2;
    // drive output high
    static const uint32_t GPIO_QSPI_SD3_CTRL_OUTOVER__HIGH = 3;
    static const uint32_t GPIO_QSPI_SD3_CTRL_FUNCSEL__xip_sd3 = 0;
    static const uint32_t GPIO_QSPI_SD3_CTRL_FUNCSEL__sio_35 = 5;
    static const uint32_t GPIO_QSPI_SD3_CTRL_FUNCSEL__null = 31;

    // Raw Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR_t, uint32_t)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTE_t, uint32_t)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTF_t, uint32_t)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for proc0
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC0_INTS_t, uint32_t)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTE_t, uint32_t)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTF_t, uint32_t)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for proc1
    // Reset value: 0x00000000
    BEGIN_TYPE(PROC1_INTS_t, uint32_t)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Enable for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTE_t, uint32_t)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt Force for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTF_t, uint32_t)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD3_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD2_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD1_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SD0_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SS_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RW(GPIO_QSPI_SCLK_LEVEL_LOW, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for dormant_wake
    // Reset value: 0x00000000
    BEGIN_TYPE(DORMANT_WAKE_INTS_t, uint32_t)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_EDGE_HIGH, 23, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_EDGE_LOW, 22, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_LEVEL_HIGH, 21, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD3_LEVEL_LOW, 20, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_EDGE_HIGH, 19, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_EDGE_LOW, 18, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_LEVEL_HIGH, 17, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD2_LEVEL_LOW, 16, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_EDGE_HIGH, 15, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_EDGE_LOW, 14, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_LEVEL_HIGH, 13, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD1_LEVEL_LOW, 12, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_EDGE_HIGH, 11, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_EDGE_LOW, 10, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_LEVEL_HIGH, 9, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SD0_LEVEL_LOW, 8, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_EDGE_HIGH, 7, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_EDGE_LOW, 6, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_LEVEL_HIGH, 5, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SS_LEVEL_LOW, 4, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_EDGE_HIGH, 3, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_EDGE_LOW, 2, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_LEVEL_HIGH, 1, 1)
        ADD_BITFIELD_RO(GPIO_QSPI_SCLK_LEVEL_LOW, 0, 1)
    END_TYPE()

    struct IO_QSPI_t {
        GPIO_QSPI_SCLK_STATUS_t       GPIO_QSPI_SCLK_STATUS;
        GPIO_QSPI_SCLK_CTRL_t         GPIO_QSPI_SCLK_CTRL;
        GPIO_QSPI_SS_STATUS_t         GPIO_QSPI_SS_STATUS;
        GPIO_QSPI_SS_CTRL_t           GPIO_QSPI_SS_CTRL;
        GPIO_QSPI_SD0_STATUS_t        GPIO_QSPI_SD0_STATUS;
        GPIO_QSPI_SD0_CTRL_t          GPIO_QSPI_SD0_CTRL;
        GPIO_QSPI_SD1_STATUS_t        GPIO_QSPI_SD1_STATUS;
        GPIO_QSPI_SD1_CTRL_t          GPIO_QSPI_SD1_CTRL;
        GPIO_QSPI_SD2_STATUS_t        GPIO_QSPI_SD2_STATUS;
        GPIO_QSPI_SD2_CTRL_t          GPIO_QSPI_SD2_CTRL;
        GPIO_QSPI_SD3_STATUS_t        GPIO_QSPI_SD3_STATUS;
        GPIO_QSPI_SD3_CTRL_t          GPIO_QSPI_SD3_CTRL;
        INTR_t                        INTR;
        PROC0_INTE_t                  PROC0_INTE;
        PROC0_INTF_t                  PROC0_INTF;
        PROC0_INTS_t                  PROC0_INTS;
        PROC1_INTE_t                  PROC1_INTE;
        PROC1_INTF_t                  PROC1_INTF;
        PROC1_INTS_t                  PROC1_INTS;
        DORMANT_WAKE_INTE_t           DORMANT_WAKE_INTE;
        DORMANT_WAKE_INTF_t           DORMANT_WAKE_INTF;
        DORMANT_WAKE_INTS_t           DORMANT_WAKE_INTS;
    };

    static IO_QSPI_t & IO_QSPI = (*(IO_QSPI_t *)0x40018000);
    static IO_QSPI_t & IO_QSPI_XOR = (*(IO_QSPI_t *)0x40019000);
    static IO_QSPI_t & IO_QSPI_SET = (*(IO_QSPI_t *)0x4001a000);
    static IO_QSPI_t & IO_QSPI_CLR = (*(IO_QSPI_t *)0x4001b000);

} // _IO_QSPI_

namespace _PADS_BANK0_  {

    // Voltage select. Per bank control
    // Reset value: 0x00000000
    BEGIN_TYPE(VOLTAGE_SELECT_t, uint32_t)
        ADD_BITFIELD_RW(VOLTAGE_SELECT, 0, 1)
    END_TYPE()

    // Set voltage to 3.3V (DVDD >= 2V5)
    static const uint32_t VOLTAGE_SELECT_VOLTAGE_SELECT__3v3 = 0;
    // Set voltage to 1.8V (DVDD <= 1V8)
    static const uint32_t VOLTAGE_SELECT_VOLTAGE_SELECT__1v8 = 1;

    // Pad control register
    // Reset value: 0x00000056
    BEGIN_TYPE(GPIO_t, uint32_t)
        // Output disable. Has priority over output enable from peripherals
        ADD_BITFIELD_RW(OD, 7, 1)
        // Input enable
        ADD_BITFIELD_RW(IE, 6, 1)
        // Drive strength.
        ADD_BITFIELD_RW(DRIVE, 4, 2)
        // Pull up enable
        ADD_BITFIELD_RW(PUE, 3, 1)
        // Pull down enable
        ADD_BITFIELD_RW(PDE, 2, 1)
        // Enable schmitt trigger
        ADD_BITFIELD_RW(SCHMITT, 1, 1)
        // Slew rate control. 1 = Fast, 0 = Slow
        ADD_BITFIELD_RW(SLEWFAST, 0, 1)
    END_TYPE()

    static const uint32_t GPIO_DRIVE__2mA = 0;
    static const uint32_t GPIO_DRIVE__4mA = 1;
    static const uint32_t GPIO_DRIVE__8mA = 2;
    static const uint32_t GPIO_DRIVE__12mA = 3;

    // Pad control register
    // Reset value: 0x000000da
    BEGIN_TYPE(SWCLK_t, uint32_t)
        // Output disable. Has priority over output enable from peripherals
        ADD_BITFIELD_RW(OD, 7, 1)
        // Input enable
        ADD_BITFIELD_RW(IE, 6, 1)
        // Drive strength.
        ADD_BITFIELD_RW(DRIVE, 4, 2)
        // Pull up enable
        ADD_BITFIELD_RW(PUE, 3, 1)
        // Pull down enable
        ADD_BITFIELD_RW(PDE, 2, 1)
        // Enable schmitt trigger
        ADD_BITFIELD_RW(SCHMITT, 1, 1)
        // Slew rate control. 1 = Fast, 0 = Slow
        ADD_BITFIELD_RW(SLEWFAST, 0, 1)
    END_TYPE()

    static const uint32_t SWCLK_DRIVE__2mA = 0;
    static const uint32_t SWCLK_DRIVE__4mA = 1;
    static const uint32_t SWCLK_DRIVE__8mA = 2;
    static const uint32_t SWCLK_DRIVE__12mA = 3;

    // Pad control register
    // Reset value: 0x0000005a
    BEGIN_TYPE(SWD_t, uint32_t)
        // Output disable. Has priority over output enable from peripherals
        ADD_BITFIELD_RW(OD, 7, 1)
        // Input enable
        ADD_BITFIELD_RW(IE, 6, 1)
        // Drive strength.
        ADD_BITFIELD_RW(DRIVE, 4, 2)
        // Pull up enable
        ADD_BITFIELD_RW(PUE, 3, 1)
        // Pull down enable
        ADD_BITFIELD_RW(PDE, 2, 1)
        // Enable schmitt trigger
        ADD_BITFIELD_RW(SCHMITT, 1, 1)
        // Slew rate control. 1 = Fast, 0 = Slow
        ADD_BITFIELD_RW(SLEWFAST, 0, 1)
    END_TYPE()

    static const uint32_t SWD_DRIVE__2mA = 0;
    static const uint32_t SWD_DRIVE__4mA = 1;
    static const uint32_t SWD_DRIVE__8mA = 2;
    static const uint32_t SWD_DRIVE__12mA = 3;

    struct PADS_BANK0_t {
        VOLTAGE_SELECT_t              VOLTAGE_SELECT;
        GPIO_t                        GPIO[30];
        SWCLK_t                       SWCLK;
        SWD_t                         SWD;
    };

    static PADS_BANK0_t & PADS_BANK0 = (*(PADS_BANK0_t *)0x4001c000);
    static PADS_BANK0_t & PADS_BANK0_XOR = (*(PADS_BANK0_t *)0x4001d000);
    static PADS_BANK0_t & PADS_BANK0_SET = (*(PADS_BANK0_t *)0x4001e000);
    static PADS_BANK0_t & PADS_BANK0_CLR = (*(PADS_BANK0_t *)0x4001f000);

} // _PADS_BANK0_

namespace _PADS_QSPI_  {

    // Voltage select. Per bank control
    // Reset value: 0x00000000
    BEGIN_TYPE(VOLTAGE_SELECT_t, uint32_t)
        ADD_BITFIELD_RW(VOLTAGE_SELECT, 0, 1)
    END_TYPE()

    // Set voltage to 3.3V (DVDD >= 2V5)
    static const uint32_t VOLTAGE_SELECT_VOLTAGE_SELECT__3v3 = 0;
    // Set voltage to 1.8V (DVDD <= 1V8)
    static const uint32_t VOLTAGE_SELECT_VOLTAGE_SELECT__1v8 = 1;

    // Pad control register
    // Reset value: 0x00000056
    BEGIN_TYPE(GPIO_QSPI_SCLK_t, uint32_t)
        // Output disable. Has priority over output enable from peripherals
        ADD_BITFIELD_RW(OD, 7, 1)
        // Input enable
        ADD_BITFIELD_RW(IE, 6, 1)
        // Drive strength.
        ADD_BITFIELD_RW(DRIVE, 4, 2)
        // Pull up enable
        ADD_BITFIELD_RW(PUE, 3, 1)
        // Pull down enable
        ADD_BITFIELD_RW(PDE, 2, 1)
        // Enable schmitt trigger
        ADD_BITFIELD_RW(SCHMITT, 1, 1)
        // Slew rate control. 1 = Fast, 0 = Slow
        ADD_BITFIELD_RW(SLEWFAST, 0, 1)
    END_TYPE()

    static const uint32_t GPIO_QSPI_SCLK_DRIVE__2mA = 0;
    static const uint32_t GPIO_QSPI_SCLK_DRIVE__4mA = 1;
    static const uint32_t GPIO_QSPI_SCLK_DRIVE__8mA = 2;
    static const uint32_t GPIO_QSPI_SCLK_DRIVE__12mA = 3;

    // Pad control register
    // Reset value: 0x00000052
    BEGIN_TYPE(GPIO_QSPI_SD0_t, uint32_t)
        // Output disable. Has priority over output enable from peripherals
        ADD_BITFIELD_RW(OD, 7, 1)
        // Input enable
        ADD_BITFIELD_RW(IE, 6, 1)
        // Drive strength.
        ADD_BITFIELD_RW(DRIVE, 4, 2)
        // Pull up enable
        ADD_BITFIELD_RW(PUE, 3, 1)
        // Pull down enable
        ADD_BITFIELD_RW(PDE, 2, 1)
        // Enable schmitt trigger
        ADD_BITFIELD_RW(SCHMITT, 1, 1)
        // Slew rate control. 1 = Fast, 0 = Slow
        ADD_BITFIELD_RW(SLEWFAST, 0, 1)
    END_TYPE()

    static const uint32_t GPIO_QSPI_SD0_DRIVE__2mA = 0;
    static const uint32_t GPIO_QSPI_SD0_DRIVE__4mA = 1;
    static const uint32_t GPIO_QSPI_SD0_DRIVE__8mA = 2;
    static const uint32_t GPIO_QSPI_SD0_DRIVE__12mA = 3;

    // Pad control register
    // Reset value: 0x00000052
    BEGIN_TYPE(GPIO_QSPI_SD1_t, uint32_t)
        // Output disable. Has priority over output enable from peripherals
        ADD_BITFIELD_RW(OD, 7, 1)
        // Input enable
        ADD_BITFIELD_RW(IE, 6, 1)
        // Drive strength.
        ADD_BITFIELD_RW(DRIVE, 4, 2)
        // Pull up enable
        ADD_BITFIELD_RW(PUE, 3, 1)
        // Pull down enable
        ADD_BITFIELD_RW(PDE, 2, 1)
        // Enable schmitt trigger
        ADD_BITFIELD_RW(SCHMITT, 1, 1)
        // Slew rate control. 1 = Fast, 0 = Slow
        ADD_BITFIELD_RW(SLEWFAST, 0, 1)
    END_TYPE()

    static const uint32_t GPIO_QSPI_SD1_DRIVE__2mA = 0;
    static const uint32_t GPIO_QSPI_SD1_DRIVE__4mA = 1;
    static const uint32_t GPIO_QSPI_SD1_DRIVE__8mA = 2;
    static const uint32_t GPIO_QSPI_SD1_DRIVE__12mA = 3;

    // Pad control register
    // Reset value: 0x00000052
    BEGIN_TYPE(GPIO_QSPI_SD2_t, uint32_t)
        // Output disable. Has priority over output enable from peripherals
        ADD_BITFIELD_RW(OD, 7, 1)
        // Input enable
        ADD_BITFIELD_RW(IE, 6, 1)
        // Drive strength.
        ADD_BITFIELD_RW(DRIVE, 4, 2)
        // Pull up enable
        ADD_BITFIELD_RW(PUE, 3, 1)
        // Pull down enable
        ADD_BITFIELD_RW(PDE, 2, 1)
        // Enable schmitt trigger
        ADD_BITFIELD_RW(SCHMITT, 1, 1)
        // Slew rate control. 1 = Fast, 0 = Slow
        ADD_BITFIELD_RW(SLEWFAST, 0, 1)
    END_TYPE()

    static const uint32_t GPIO_QSPI_SD2_DRIVE__2mA = 0;
    static const uint32_t GPIO_QSPI_SD2_DRIVE__4mA = 1;
    static const uint32_t GPIO_QSPI_SD2_DRIVE__8mA = 2;
    static const uint32_t GPIO_QSPI_SD2_DRIVE__12mA = 3;

    // Pad control register
    // Reset value: 0x00000052
    BEGIN_TYPE(GPIO_QSPI_SD3_t, uint32_t)
        // Output disable. Has priority over output enable from peripherals
        ADD_BITFIELD_RW(OD, 7, 1)
        // Input enable
        ADD_BITFIELD_RW(IE, 6, 1)
        // Drive strength.
        ADD_BITFIELD_RW(DRIVE, 4, 2)
        // Pull up enable
        ADD_BITFIELD_RW(PUE, 3, 1)
        // Pull down enable
        ADD_BITFIELD_RW(PDE, 2, 1)
        // Enable schmitt trigger
        ADD_BITFIELD_RW(SCHMITT, 1, 1)
        // Slew rate control. 1 = Fast, 0 = Slow
        ADD_BITFIELD_RW(SLEWFAST, 0, 1)
    END_TYPE()

    static const uint32_t GPIO_QSPI_SD3_DRIVE__2mA = 0;
    static const uint32_t GPIO_QSPI_SD3_DRIVE__4mA = 1;
    static const uint32_t GPIO_QSPI_SD3_DRIVE__8mA = 2;
    static const uint32_t GPIO_QSPI_SD3_DRIVE__12mA = 3;

    // Pad control register
    // Reset value: 0x0000005a
    BEGIN_TYPE(GPIO_QSPI_SS_t, uint32_t)
        // Output disable. Has priority over output enable from peripherals
        ADD_BITFIELD_RW(OD, 7, 1)
        // Input enable
        ADD_BITFIELD_RW(IE, 6, 1)
        // Drive strength.
        ADD_BITFIELD_RW(DRIVE, 4, 2)
        // Pull up enable
        ADD_BITFIELD_RW(PUE, 3, 1)
        // Pull down enable
        ADD_BITFIELD_RW(PDE, 2, 1)
        // Enable schmitt trigger
        ADD_BITFIELD_RW(SCHMITT, 1, 1)
        // Slew rate control. 1 = Fast, 0 = Slow
        ADD_BITFIELD_RW(SLEWFAST, 0, 1)
    END_TYPE()

    static const uint32_t GPIO_QSPI_SS_DRIVE__2mA = 0;
    static const uint32_t GPIO_QSPI_SS_DRIVE__4mA = 1;
    static const uint32_t GPIO_QSPI_SS_DRIVE__8mA = 2;
    static const uint32_t GPIO_QSPI_SS_DRIVE__12mA = 3;

    struct PADS_QSPI_t {
        VOLTAGE_SELECT_t              VOLTAGE_SELECT;
        GPIO_QSPI_SCLK_t              GPIO_QSPI_SCLK;
        GPIO_QSPI_SD0_t               GPIO_QSPI_SD0;
        GPIO_QSPI_SD1_t               GPIO_QSPI_SD1;
        GPIO_QSPI_SD2_t               GPIO_QSPI_SD2;
        GPIO_QSPI_SD3_t               GPIO_QSPI_SD3;
        GPIO_QSPI_SS_t                GPIO_QSPI_SS;
    };

    static PADS_QSPI_t & PADS_QSPI = (*(PADS_QSPI_t *)0x40020000);
    static PADS_QSPI_t & PADS_QSPI_XOR = (*(PADS_QSPI_t *)0x40021000);
    static PADS_QSPI_t & PADS_QSPI_SET = (*(PADS_QSPI_t *)0x40022000);
    static PADS_QSPI_t & PADS_QSPI_CLR = (*(PADS_QSPI_t *)0x40023000);

} // _PADS_QSPI_

// Controls the crystal oscillator
namespace _XOSC_  {

    // Crystal Oscillator Control
    // Reset value: 0x00000000
    BEGIN_TYPE(CTRL_t, uint32_t)
        // On power-up this field is initialised to DISABLE and the chip runs from the ROSC.
        // If the chip has subsequently been programmed to run from the XOSC then setting this field to DISABLE may lock-up the chip. If this is a concern then run the clk_ref from the ROSC and enable the clk_sys RESUS feature.
        // The 12-bit code is intended to give some protection against accidental writes. An invalid setting will enable the oscillator.
        ADD_BITFIELD_RW(ENABLE, 12, 12)
        // Frequency range. This resets to 0xAA0 and cannot be changed.
        ADD_BITFIELD_RW(FREQ_RANGE, 0, 12)
    END_TYPE()

    static const uint32_t CTRL_ENABLE__DISABLE = 3358;
    static const uint32_t CTRL_ENABLE__ENABLE = 4011;
    static const uint32_t CTRL_FREQ_RANGE__1_15MHZ = 2720;
    static const uint32_t CTRL_FREQ_RANGE__RESERVED_1 = 2721;
    static const uint32_t CTRL_FREQ_RANGE__RESERVED_2 = 2722;
    static const uint32_t CTRL_FREQ_RANGE__RESERVED_3 = 2723;

    // Crystal Oscillator Status
    // Reset value: 0x00000000
    BEGIN_TYPE(STATUS_t, uint32_t)
        // Oscillator is running and stable
        ADD_BITFIELD_RO(STABLE, 31, 1)
        // An invalid value has been written to CTRL_ENABLE or CTRL_FREQ_RANGE or DORMANT
        ADD_BITFIELD_RW(BADWRITE, 24, 1)
        // Oscillator is enabled but not necessarily running and stable, resets to 0
        ADD_BITFIELD_RO(ENABLED, 12, 1)
        // The current frequency range setting, always reads 0
        ADD_BITFIELD_RO(FREQ_RANGE, 0, 2)
    END_TYPE()

    static const uint32_t STATUS_FREQ_RANGE__1_15MHZ = 0;
    static const uint32_t STATUS_FREQ_RANGE__RESERVED_1 = 1;
    static const uint32_t STATUS_FREQ_RANGE__RESERVED_2 = 2;
    static const uint32_t STATUS_FREQ_RANGE__RESERVED_3 = 3;

    // Crystal Oscillator pause control
    // This is used to save power by pausing the XOSC
    // On power-up this field is initialised to WAKE
    // An invalid write will also select WAKE
    // WARNING: stop the PLLs before selecting dormant mode
    // WARNING: setup the irq before selecting dormant mode
    // Reset value: 0x00000000
    typedef uint32_t DORMANT_t;

    // Controls the startup delay
    // Reset value: 0x000000c4
    BEGIN_TYPE(STARTUP_t, uint32_t)
        // Multiplies the startup_delay by 4. This is of little value to the user given that the delay can be programmed directly.
        ADD_BITFIELD_RW(X4, 20, 1)
        // in multiples of 256*xtal_period. The reset value of 0xc4 corresponds to approx 50 000 cycles.
        ADD_BITFIELD_RW(DELAY, 0, 14)
    END_TYPE()

    // A down counter running at the xosc frequency which counts to zero and stops.
    // To start the counter write a non-zero value.
    // Can be used for short software pauses when setting up time sensitive hardware.
    // Reset value: 0x00000000
    BEGIN_TYPE(COUNT_t, uint32_t)
        ADD_BITFIELD_RW(COUNT, 0, 8)
    END_TYPE()

    struct XOSC_t {
        CTRL_t                        CTRL;
        STATUS_t                      STATUS;
        DORMANT_t                     DORMANT;
        STARTUP_t                     STARTUP;
        uint32_t                      reserved0[3];
        COUNT_t                       COUNT;
    };

    static XOSC_t & XOSC = (*(XOSC_t *)0x40024000);
    static XOSC_t & XOSC_XOR = (*(XOSC_t *)0x40025000);
    static XOSC_t & XOSC_SET = (*(XOSC_t *)0x40026000);
    static XOSC_t & XOSC_CLR = (*(XOSC_t *)0x40027000);

} // _XOSC_

namespace _PLL_SYS_  {

    // Control and Status
    // GENERAL CONSTRAINTS:
    // Reference clock frequency min=5MHz, max=800MHz
    // Feedback divider min=16, max=320
    // VCO frequency min=750MHz, max=1600MHz
    // Reset value: 0x00000001
    BEGIN_TYPE(CS_t, uint32_t)
        // PLL is locked
        ADD_BITFIELD_RO(LOCK, 31, 1)
        // Passes the reference clock to the output instead of the divided VCO. The VCO continues to run so the user can switch between the reference clock and the divided VCO but the output will glitch when doing so.
        ADD_BITFIELD_RW(BYPASS, 8, 1)
        // Divides the PLL input reference clock.
        // Behaviour is undefined for div=0.
        // PLL output will be unpredictable during refdiv changes, wait for lock=1 before using it.
        ADD_BITFIELD_RW(REFDIV, 0, 6)
    END_TYPE()

    // Controls the PLL power modes.
    // Reset value: 0x0000002d
    BEGIN_TYPE(PWR_t, uint32_t)
        // PLL VCO powerdown
        // To save power set high when PLL output not required or bypass=1.
        ADD_BITFIELD_RW(VCOPD, 5, 1)
        // PLL post divider powerdown
        // To save power set high when PLL output not required or bypass=1.
        ADD_BITFIELD_RW(POSTDIVPD, 3, 1)
        // PLL DSM powerdown
        // Nothing is achieved by setting this low.
        ADD_BITFIELD_RW(DSMPD, 2, 1)
        // PLL powerdown
        // To save power set high when PLL output not required.
        ADD_BITFIELD_RW(PD, 0, 1)
    END_TYPE()

    // Feedback divisor
    // (note: this PLL does not support fractional division)
    // Reset value: 0x00000000
    BEGIN_TYPE(FBDIV_INT_t, uint32_t)
        // see ctrl reg description for constraints
        ADD_BITFIELD_RW(FBDIV_INT, 0, 12)
    END_TYPE()

    // Controls the PLL post dividers for the primary output
    // (note: this PLL does not have a secondary output)
    // the primary output is driven from VCO divided by postdiv1*postdiv2
    // Reset value: 0x00077000
    BEGIN_TYPE(PRIM_t, uint32_t)
        // divide by 1-7
        ADD_BITFIELD_RW(POSTDIV1, 16, 3)
        // divide by 1-7
        ADD_BITFIELD_RW(POSTDIV2, 12, 3)
    END_TYPE()

    struct PLL_SYS_t {
        CS_t                          CS;
        PWR_t                         PWR;
        FBDIV_INT_t                   FBDIV_INT;
        PRIM_t                        PRIM;
    };

    static PLL_SYS_t & PLL_SYS = (*(PLL_SYS_t *)0x40028000);
    static PLL_SYS_t & PLL_SYS_XOR = (*(PLL_SYS_t *)0x40029000);
    static PLL_SYS_t & PLL_SYS_SET = (*(PLL_SYS_t *)0x4002a000);
    static PLL_SYS_t & PLL_SYS_CLR = (*(PLL_SYS_t *)0x4002b000);

} // _PLL_SYS_


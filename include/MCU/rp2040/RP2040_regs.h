///////////////////////////////////////////////////////////////////////////
// This file was generated with svd2cpp, source file was RP2040_regs.svd
// DO NOT EDIT - CHANGES MIGHT BE OVERWRITTEN !!
///////////////////////////////////////////////////////////////////////////
//
#include "bitfield_defs.h"

// addressUnitBits: 8
// vendor: Raspberry Pi
// name: RP2040
// Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
// 
// SPDX-License-Identifier: BSD-3-Clause
// version: 0.1
// width: 32
// cpu
//   name: CM0PLUS
//   revision: r0p1
//   endian: little
//   mpuPresent: true
//   fpuPresent: false
//   nvicPrioBits: 2
//   vtorPresent: 1
//   vendorSystickConfig: false
//   deviceNumInterrupts: 26

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

    static XIP_CTRL_t & XIP_CTRL     = (*(XIP_CTRL_t *)0x14000000);
    static XIP_CTRL_t & XIP_CTRL_XOR = (*(XIP_CTRL_t *)0x14001000);
    static XIP_CTRL_t & XIP_CTRL_SET = (*(XIP_CTRL_t *)0x14002000);
    static XIP_CTRL_t & XIP_CTRL_CLR = (*(XIP_CTRL_t *)0x14003000);

} // _XIP_CTRL_

// DW_apb_ssi has the following features:
// * APB interface – Allows for easy integration into a DesignWare Synthesizable Components for AMBA 2 implementation.
// * APB3 and APB4 protocol support.
// * Scalable APB data bus width – Supports APB data bus widths of 8, 16, and 32 bits.
// * Serial-master or serial-slave operation – Enables serial communication with serial-master or serial-slave peripheral devices.
// * Programmable Dual/Quad/Octal SPI support in Master Mode.
// * Dual Data Rate (DDR) and Read Data Strobe (RDS) Support - Enables the DW_apb_ssi master to perform operations with the device in DDR and RDS modes when working in Dual/Quad/Octal mode of operation.
// * Data Mask Support - Enables the DW_apb_ssi to selectively update the bytes in the device. This feature is applicable only in enhanced SPI modes.
// * eXecute-In-Place (XIP) support - Enables the DW_apb_ssi master to behave as a memory mapped I/O and fetches the data from the device based on the APB read request. This feature is applicable only in enhanced SPI modes.
// * DMA Controller Interface – Enables the DW_apb_ssi to interface to a DMA controller over the bus using a handshaking interface for transfer requests.
// * Independent masking of interrupts – Master collision, transmit FIFO overflow, transmit FIFO empty, receive FIFO full, receive FIFO underflow, and receive FIFO overflow interrupts can all be masked independently.
// * Multi-master contention detection – Informs the processor of multiple serial-master accesses on the serial bus.
// * Bypass of meta-stability flip-flops for synchronous clocks – When the APB clock (pclk) and the DW_apb_ssi serial clock (ssi_clk) are synchronous, meta-stable flip-flops are not used when transferring control signals across these clock domains.
// * Programmable delay on the sample time of the received serial data bit (rxd); enables programmable control of routing delays resulting in higher serial data-bit rates.
// * Programmable features:
// - Serial interface operation – Choice of Motorola SPI, Texas Instruments Synchronous Serial Protocol or National Semiconductor Microwire.
// - Clock bit-rate – Dynamic control of the serial bit rate of the data transfer; used in only serial-master mode of operation.
// - Data Item size (4 to 32 bits) – Item size of each data transfer under the control of the programmer.
// * Configured features:
// - FIFO depth – 16 words deep. The FIFO width is fixed at 32 bits.
// - 1 slave select output.
// - Hardware slave-select – Dedicated hardware slave-select line.
// - Combined interrupt line - one combined interrupt line from the DW_apb_ssi to the interrupt controller.
// - Interrupt polarity – active high interrupt lines.
// - Serial clock polarity – low serial-clock polarity directly after reset.
// - Serial clock phase – capture on first edge of serial-clock directly after reset.
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

    static XIP_SSI_t & XIP_SSI     = (*(XIP_SSI_t *)0x18000000);
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

    static SYSINFO_t & SYSINFO     = (*(SYSINFO_t *)0x40000000);
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

    static SYSCFG_t & SYSCFG     = (*(SYSCFG_t *)0x40004000);
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

    static CLOCKS_t & CLOCKS     = (*(CLOCKS_t *)0x40008000);
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

    static RESETS_t & RESETS     = (*(RESETS_t *)0x4000c000);
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

    static PSM_t & PSM     = (*(PSM_t *)0x40010000);
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

    static IO_BANK0_t & IO_BANK0     = (*(IO_BANK0_t *)0x40014000);
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

    static IO_QSPI_t & IO_QSPI     = (*(IO_QSPI_t *)0x40018000);
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

    static PADS_BANK0_t & PADS_BANK0     = (*(PADS_BANK0_t *)0x4001c000);
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

    static PADS_QSPI_t & PADS_QSPI     = (*(PADS_QSPI_t *)0x40020000);
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

    static XOSC_t & XOSC     = (*(XOSC_t *)0x40024000);
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

    static PLL_SYS_t & PLL_SYS     = (*(PLL_SYS_t *)0x40028000);
    static PLL_SYS_t & PLL_SYS_XOR = (*(PLL_SYS_t *)0x40029000);
    static PLL_SYS_t & PLL_SYS_SET = (*(PLL_SYS_t *)0x4002a000);
    static PLL_SYS_t & PLL_SYS_CLR = (*(PLL_SYS_t *)0x4002b000);

} // _PLL_SYS_

namespace _PLL_USB_  {

    static _PLL_SYS_::PLL_SYS_t & PLL_USB     = (*(_PLL_SYS_::PLL_SYS_t *)0x4002c000);
    static _PLL_SYS_::PLL_SYS_t & PLL_USB_XOR = (*(_PLL_SYS_::PLL_SYS_t *)0x4002d000);
    static _PLL_SYS_::PLL_SYS_t & PLL_USB_SET = (*(_PLL_SYS_::PLL_SYS_t *)0x4002e000);
    static _PLL_SYS_::PLL_SYS_t & PLL_USB_CLR = (*(_PLL_SYS_::PLL_SYS_t *)0x4002f000);

} // _PLL_USB_

// Register block for busfabric control signals and performance counters
namespace _BUSCTRL_  {

    // Set the priority of each master for bus arbitration.
    // Reset value: 0x00000000
    BEGIN_TYPE(BUS_PRIORITY_t, uint32_t)
        // 0 - low priority, 1 - high priority
        ADD_BITFIELD_RW(DMA_W, 12, 1)
        // 0 - low priority, 1 - high priority
        ADD_BITFIELD_RW(DMA_R, 8, 1)
        // 0 - low priority, 1 - high priority
        ADD_BITFIELD_RW(PROC1, 4, 1)
        // 0 - low priority, 1 - high priority
        ADD_BITFIELD_RW(PROC0, 0, 1)
    END_TYPE()

    // Bus priority acknowledge
    // Reset value: 0x00000000
    BEGIN_TYPE(BUS_PRIORITY_ACK_t, uint32_t)
        // Goes to 1 once all arbiters have registered the new global priority levels.
        // Arbiters update their local priority when servicing a new nonsequential access.
        // In normal circumstances this will happen almost immediately.
        ADD_BITFIELD_RO(BUS_PRIORITY_ACK, 0, 1)
    END_TYPE()

    // Bus fabric performance counter 0
    // Reset value: 0x00000000
    BEGIN_TYPE(PERFCTR0_t, uint32_t)
        // Busfabric saturating performance counter 0
        // Count some event signal from the busfabric arbiters.
        // Write any value to clear. Select an event to count using PERFSEL0
        ADD_BITFIELD_RW(PERFCTR0, 0, 24)
    END_TYPE()

    // Bus fabric performance event select for PERFCTR0
    // Reset value: 0x0000001f
    BEGIN_TYPE(PERFSEL0_t, uint32_t)
        // Select an event for PERFCTR0. Count either contested accesses, or all accesses, on a downstream port of the main crossbar.
        ADD_BITFIELD_RW(PERFSEL0, 0, 5)
    END_TYPE()

    static const uint32_t PERFSEL0_PERFSEL0__apb_contested = 0;
    static const uint32_t PERFSEL0_PERFSEL0__apb = 1;
    static const uint32_t PERFSEL0_PERFSEL0__fastperi_contested = 2;
    static const uint32_t PERFSEL0_PERFSEL0__fastperi = 3;
    static const uint32_t PERFSEL0_PERFSEL0__sram5_contested = 4;
    static const uint32_t PERFSEL0_PERFSEL0__sram5 = 5;
    static const uint32_t PERFSEL0_PERFSEL0__sram4_contested = 6;
    static const uint32_t PERFSEL0_PERFSEL0__sram4 = 7;
    static const uint32_t PERFSEL0_PERFSEL0__sram3_contested = 8;
    static const uint32_t PERFSEL0_PERFSEL0__sram3 = 9;
    static const uint32_t PERFSEL0_PERFSEL0__sram2_contested = 10;
    static const uint32_t PERFSEL0_PERFSEL0__sram2 = 11;
    static const uint32_t PERFSEL0_PERFSEL0__sram1_contested = 12;
    static const uint32_t PERFSEL0_PERFSEL0__sram1 = 13;
    static const uint32_t PERFSEL0_PERFSEL0__sram0_contested = 14;
    static const uint32_t PERFSEL0_PERFSEL0__sram0 = 15;
    static const uint32_t PERFSEL0_PERFSEL0__xip_main_contested = 16;
    static const uint32_t PERFSEL0_PERFSEL0__xip_main = 17;
    static const uint32_t PERFSEL0_PERFSEL0__rom_contested = 18;
    static const uint32_t PERFSEL0_PERFSEL0__rom = 19;

    // Bus fabric performance counter 1
    // Reset value: 0x00000000
    BEGIN_TYPE(PERFCTR1_t, uint32_t)
        // Busfabric saturating performance counter 1
        // Count some event signal from the busfabric arbiters.
        // Write any value to clear. Select an event to count using PERFSEL1
        ADD_BITFIELD_RW(PERFCTR1, 0, 24)
    END_TYPE()

    // Bus fabric performance event select for PERFCTR1
    // Reset value: 0x0000001f
    BEGIN_TYPE(PERFSEL1_t, uint32_t)
        // Select an event for PERFCTR1. Count either contested accesses, or all accesses, on a downstream port of the main crossbar.
        ADD_BITFIELD_RW(PERFSEL1, 0, 5)
    END_TYPE()

    static const uint32_t PERFSEL1_PERFSEL1__apb_contested = 0;
    static const uint32_t PERFSEL1_PERFSEL1__apb = 1;
    static const uint32_t PERFSEL1_PERFSEL1__fastperi_contested = 2;
    static const uint32_t PERFSEL1_PERFSEL1__fastperi = 3;
    static const uint32_t PERFSEL1_PERFSEL1__sram5_contested = 4;
    static const uint32_t PERFSEL1_PERFSEL1__sram5 = 5;
    static const uint32_t PERFSEL1_PERFSEL1__sram4_contested = 6;
    static const uint32_t PERFSEL1_PERFSEL1__sram4 = 7;
    static const uint32_t PERFSEL1_PERFSEL1__sram3_contested = 8;
    static const uint32_t PERFSEL1_PERFSEL1__sram3 = 9;
    static const uint32_t PERFSEL1_PERFSEL1__sram2_contested = 10;
    static const uint32_t PERFSEL1_PERFSEL1__sram2 = 11;
    static const uint32_t PERFSEL1_PERFSEL1__sram1_contested = 12;
    static const uint32_t PERFSEL1_PERFSEL1__sram1 = 13;
    static const uint32_t PERFSEL1_PERFSEL1__sram0_contested = 14;
    static const uint32_t PERFSEL1_PERFSEL1__sram0 = 15;
    static const uint32_t PERFSEL1_PERFSEL1__xip_main_contested = 16;
    static const uint32_t PERFSEL1_PERFSEL1__xip_main = 17;
    static const uint32_t PERFSEL1_PERFSEL1__rom_contested = 18;
    static const uint32_t PERFSEL1_PERFSEL1__rom = 19;

    // Bus fabric performance counter 2
    // Reset value: 0x00000000
    BEGIN_TYPE(PERFCTR2_t, uint32_t)
        // Busfabric saturating performance counter 2
        // Count some event signal from the busfabric arbiters.
        // Write any value to clear. Select an event to count using PERFSEL2
        ADD_BITFIELD_RW(PERFCTR2, 0, 24)
    END_TYPE()

    // Bus fabric performance event select for PERFCTR2
    // Reset value: 0x0000001f
    BEGIN_TYPE(PERFSEL2_t, uint32_t)
        // Select an event for PERFCTR2. Count either contested accesses, or all accesses, on a downstream port of the main crossbar.
        ADD_BITFIELD_RW(PERFSEL2, 0, 5)
    END_TYPE()

    static const uint32_t PERFSEL2_PERFSEL2__apb_contested = 0;
    static const uint32_t PERFSEL2_PERFSEL2__apb = 1;
    static const uint32_t PERFSEL2_PERFSEL2__fastperi_contested = 2;
    static const uint32_t PERFSEL2_PERFSEL2__fastperi = 3;
    static const uint32_t PERFSEL2_PERFSEL2__sram5_contested = 4;
    static const uint32_t PERFSEL2_PERFSEL2__sram5 = 5;
    static const uint32_t PERFSEL2_PERFSEL2__sram4_contested = 6;
    static const uint32_t PERFSEL2_PERFSEL2__sram4 = 7;
    static const uint32_t PERFSEL2_PERFSEL2__sram3_contested = 8;
    static const uint32_t PERFSEL2_PERFSEL2__sram3 = 9;
    static const uint32_t PERFSEL2_PERFSEL2__sram2_contested = 10;
    static const uint32_t PERFSEL2_PERFSEL2__sram2 = 11;
    static const uint32_t PERFSEL2_PERFSEL2__sram1_contested = 12;
    static const uint32_t PERFSEL2_PERFSEL2__sram1 = 13;
    static const uint32_t PERFSEL2_PERFSEL2__sram0_contested = 14;
    static const uint32_t PERFSEL2_PERFSEL2__sram0 = 15;
    static const uint32_t PERFSEL2_PERFSEL2__xip_main_contested = 16;
    static const uint32_t PERFSEL2_PERFSEL2__xip_main = 17;
    static const uint32_t PERFSEL2_PERFSEL2__rom_contested = 18;
    static const uint32_t PERFSEL2_PERFSEL2__rom = 19;

    // Bus fabric performance counter 3
    // Reset value: 0x00000000
    BEGIN_TYPE(PERFCTR3_t, uint32_t)
        // Busfabric saturating performance counter 3
        // Count some event signal from the busfabric arbiters.
        // Write any value to clear. Select an event to count using PERFSEL3
        ADD_BITFIELD_RW(PERFCTR3, 0, 24)
    END_TYPE()

    // Bus fabric performance event select for PERFCTR3
    // Reset value: 0x0000001f
    BEGIN_TYPE(PERFSEL3_t, uint32_t)
        // Select an event for PERFCTR3. Count either contested accesses, or all accesses, on a downstream port of the main crossbar.
        ADD_BITFIELD_RW(PERFSEL3, 0, 5)
    END_TYPE()

    static const uint32_t PERFSEL3_PERFSEL3__apb_contested = 0;
    static const uint32_t PERFSEL3_PERFSEL3__apb = 1;
    static const uint32_t PERFSEL3_PERFSEL3__fastperi_contested = 2;
    static const uint32_t PERFSEL3_PERFSEL3__fastperi = 3;
    static const uint32_t PERFSEL3_PERFSEL3__sram5_contested = 4;
    static const uint32_t PERFSEL3_PERFSEL3__sram5 = 5;
    static const uint32_t PERFSEL3_PERFSEL3__sram4_contested = 6;
    static const uint32_t PERFSEL3_PERFSEL3__sram4 = 7;
    static const uint32_t PERFSEL3_PERFSEL3__sram3_contested = 8;
    static const uint32_t PERFSEL3_PERFSEL3__sram3 = 9;
    static const uint32_t PERFSEL3_PERFSEL3__sram2_contested = 10;
    static const uint32_t PERFSEL3_PERFSEL3__sram2 = 11;
    static const uint32_t PERFSEL3_PERFSEL3__sram1_contested = 12;
    static const uint32_t PERFSEL3_PERFSEL3__sram1 = 13;
    static const uint32_t PERFSEL3_PERFSEL3__sram0_contested = 14;
    static const uint32_t PERFSEL3_PERFSEL3__sram0 = 15;
    static const uint32_t PERFSEL3_PERFSEL3__xip_main_contested = 16;
    static const uint32_t PERFSEL3_PERFSEL3__xip_main = 17;
    static const uint32_t PERFSEL3_PERFSEL3__rom_contested = 18;
    static const uint32_t PERFSEL3_PERFSEL3__rom = 19;

    struct BUSCTRL_t {
        BUS_PRIORITY_t                BUS_PRIORITY;
        BUS_PRIORITY_ACK_t            BUS_PRIORITY_ACK;
        PERFCTR0_t                    PERFCTR0;
        PERFSEL0_t                    PERFSEL0;
        PERFCTR1_t                    PERFCTR1;
        PERFSEL1_t                    PERFSEL1;
        PERFCTR2_t                    PERFCTR2;
        PERFSEL2_t                    PERFSEL2;
        PERFCTR3_t                    PERFCTR3;
        PERFSEL3_t                    PERFSEL3;
    };

    static BUSCTRL_t & BUSCTRL     = (*(BUSCTRL_t *)0x40030000);
    static BUSCTRL_t & BUSCTRL_XOR = (*(BUSCTRL_t *)0x40031000);
    static BUSCTRL_t & BUSCTRL_SET = (*(BUSCTRL_t *)0x40032000);
    static BUSCTRL_t & BUSCTRL_CLR = (*(BUSCTRL_t *)0x40033000);

} // _BUSCTRL_

namespace _UART0_  {

    // Data Register, UARTDR
    // Reset value: 0x00000000
    BEGIN_TYPE(UARTDR_t, uint32_t)
        // Overrun error. This bit is set to 1 if data is received and the receive FIFO is already full. This is cleared to 0 once there is an empty space in the FIFO and a new character can be written to it.
        ADD_BITFIELD_RO(OE, 11, 1)
        // Break error. This bit is set to 1 if a break condition was detected, indicating that the received data input was held LOW for longer than a full-word transmission time (defined as start, data, parity and stop bits). In FIFO mode, this error is associated with the character at the top of the FIFO. When a break occurs, only one 0 character is loaded into the FIFO. The next character is only enabled after the receive data input goes to a 1 (marking state), and the next valid start bit is received.
        ADD_BITFIELD_RO(BE, 10, 1)
        // Parity error. When set to 1, it indicates that the parity of the received data character does not match the parity that the EPS and SPS bits in the Line Control Register, UARTLCR_H. In FIFO mode, this error is associated with the character at the top of the FIFO.
        ADD_BITFIELD_RO(PE, 9, 1)
        // Framing error. When set to 1, it indicates that the received character did not have a valid stop bit (a valid stop bit is 1). In FIFO mode, this error is associated with the character at the top of the FIFO.
        ADD_BITFIELD_RO(FE, 8, 1)
        // Receive (read) data character. Transmit (write) data character.
        ADD_BITFIELD_RW(DATA, 0, 8)
    END_TYPE()

    // Receive Status Register/Error Clear Register, UARTRSR/UARTECR
    // Reset value: 0x00000000
    BEGIN_TYPE(UARTRSR_t, uint32_t)
        // Overrun error. This bit is set to 1 if data is received and the FIFO is already full. This bit is cleared to 0 by a write to UARTECR. The FIFO contents remain valid because no more data is written when the FIFO is full, only the contents of the shift register are overwritten. The CPU must now read the data, to empty the FIFO.
        ADD_BITFIELD_RW(OE, 3, 1)
        // Break error. This bit is set to 1 if a break condition was detected, indicating that the received data input was held LOW for longer than a full-word transmission time (defined as start, data, parity, and stop bits). This bit is cleared to 0 after a write to UARTECR. In FIFO mode, this error is associated with the character at the top of the FIFO. When a break occurs, only one 0 character is loaded into the FIFO. The next character is only enabled after the receive data input goes to a 1 (marking state) and the next valid start bit is received.
        ADD_BITFIELD_RW(BE, 2, 1)
        // Parity error. When set to 1, it indicates that the parity of the received data character does not match the parity that the EPS and SPS bits in the Line Control Register, UARTLCR_H. This bit is cleared to 0 by a write to UARTECR. In FIFO mode, this error is associated with the character at the top of the FIFO.
        ADD_BITFIELD_RW(PE, 1, 1)
        // Framing error. When set to 1, it indicates that the received character did not have a valid stop bit (a valid stop bit is 1). This bit is cleared to 0 by a write to UARTECR. In FIFO mode, this error is associated with the character at the top of the FIFO.
        ADD_BITFIELD_RW(FE, 0, 1)
    END_TYPE()

    // Flag Register, UARTFR
    // Reset value: 0x00000090
    BEGIN_TYPE(UARTFR_t, uint32_t)
        // Ring indicator. This bit is the complement of the UART ring indicator, nUARTRI, modem status input. That is, the bit is 1 when nUARTRI is LOW.
        ADD_BITFIELD_RO(RI, 8, 1)
        // Transmit FIFO empty. The meaning of this bit depends on the state of the FEN bit in the Line Control Register, UARTLCR_H. If the FIFO is disabled, this bit is set when the transmit holding register is empty. If the FIFO is enabled, the TXFE bit is set when the transmit FIFO is empty. This bit does not indicate if there is data in the transmit shift register.
        ADD_BITFIELD_RO(TXFE, 7, 1)
        // Receive FIFO full. The meaning of this bit depends on the state of the FEN bit in the UARTLCR_H Register. If the FIFO is disabled, this bit is set when the receive holding register is full. If the FIFO is enabled, the RXFF bit is set when the receive FIFO is full.
        ADD_BITFIELD_RO(RXFF, 6, 1)
        // Transmit FIFO full. The meaning of this bit depends on the state of the FEN bit in the UARTLCR_H Register. If the FIFO is disabled, this bit is set when the transmit holding register is full. If the FIFO is enabled, the TXFF bit is set when the transmit FIFO is full.
        ADD_BITFIELD_RO(TXFF, 5, 1)
        // Receive FIFO empty. The meaning of this bit depends on the state of the FEN bit in the UARTLCR_H Register. If the FIFO is disabled, this bit is set when the receive holding register is empty. If the FIFO is enabled, the RXFE bit is set when the receive FIFO is empty.
        ADD_BITFIELD_RO(RXFE, 4, 1)
        // UART busy. If this bit is set to 1, the UART is busy transmitting data. This bit remains set until the complete byte, including all the stop bits, has been sent from the shift register. This bit is set as soon as the transmit FIFO becomes non-empty, regardless of whether the UART is enabled or not.
        ADD_BITFIELD_RO(BUSY, 3, 1)
        // Data carrier detect. This bit is the complement of the UART data carrier detect, nUARTDCD, modem status input. That is, the bit is 1 when nUARTDCD is LOW.
        ADD_BITFIELD_RO(DCD, 2, 1)
        // Data set ready. This bit is the complement of the UART data set ready, nUARTDSR, modem status input. That is, the bit is 1 when nUARTDSR is LOW.
        ADD_BITFIELD_RO(DSR, 1, 1)
        // Clear to send. This bit is the complement of the UART clear to send, nUARTCTS, modem status input. That is, the bit is 1 when nUARTCTS is LOW.
        ADD_BITFIELD_RO(CTS, 0, 1)
    END_TYPE()

    // IrDA Low-Power Counter Register, UARTILPR
    // Reset value: 0x00000000
    BEGIN_TYPE(UARTILPR_t, uint32_t)
        // 8-bit low-power divisor value. These bits are cleared to 0 at reset.
        ADD_BITFIELD_RW(ILPDVSR, 0, 8)
    END_TYPE()

    // Integer Baud Rate Register, UARTIBRD
    // Reset value: 0x00000000
    BEGIN_TYPE(UARTIBRD_t, uint32_t)
        // The integer baud rate divisor. These bits are cleared to 0 on reset.
        ADD_BITFIELD_RW(BAUD_DIVINT, 0, 16)
    END_TYPE()

    // Fractional Baud Rate Register, UARTFBRD
    // Reset value: 0x00000000
    BEGIN_TYPE(UARTFBRD_t, uint32_t)
        // The fractional baud rate divisor. These bits are cleared to 0 on reset.
        ADD_BITFIELD_RW(BAUD_DIVFRAC, 0, 6)
    END_TYPE()

    // Line Control Register, UARTLCR_H
    // Reset value: 0x00000000
    BEGIN_TYPE(UARTLCR_H_t, uint32_t)
        // Stick parity select. 0 = stick parity is disabled 1 = either: * if the EPS bit is 0 then the parity bit is transmitted and checked as a 1 * if the EPS bit is 1 then the parity bit is transmitted and checked as a 0. This bit has no effect when the PEN bit disables parity checking and generation.
        ADD_BITFIELD_RW(SPS, 7, 1)
        // Word length. These bits indicate the number of data bits transmitted or received in a frame as follows: b11 = 8 bits b10 = 7 bits b01 = 6 bits b00 = 5 bits.
        ADD_BITFIELD_RW(WLEN, 5, 2)
        // Enable FIFOs: 0 = FIFOs are disabled (character mode) that is, the FIFOs become 1-byte-deep holding registers 1 = transmit and receive FIFO buffers are enabled (FIFO mode).
        ADD_BITFIELD_RW(FEN, 4, 1)
        // Two stop bits select. If this bit is set to 1, two stop bits are transmitted at the end of the frame. The receive logic does not check for two stop bits being received.
        ADD_BITFIELD_RW(STP2, 3, 1)
        // Even parity select. Controls the type of parity the UART uses during transmission and reception: 0 = odd parity. The UART generates or checks for an odd number of 1s in the data and parity bits. 1 = even parity. The UART generates or checks for an even number of 1s in the data and parity bits. This bit has no effect when the PEN bit disables parity checking and generation.
        ADD_BITFIELD_RW(EPS, 2, 1)
        // Parity enable: 0 = parity is disabled and no parity bit added to the data frame 1 = parity checking and generation is enabled.
        ADD_BITFIELD_RW(PEN, 1, 1)
        // Send break. If this bit is set to 1, a low-level is continually output on the UARTTXD output, after completing transmission of the current character. For the proper execution of the break command, the software must set this bit for at least two complete frames. For normal use, this bit must be cleared to 0.
        ADD_BITFIELD_RW(BRK, 0, 1)
    END_TYPE()

    // Control Register, UARTCR
    // Reset value: 0x00000300
    BEGIN_TYPE(UARTCR_t, uint32_t)
        // CTS hardware flow control enable. If this bit is set to 1, CTS hardware flow control is enabled. Data is only transmitted when the nUARTCTS signal is asserted.
        ADD_BITFIELD_RW(CTSEN, 15, 1)
        // RTS hardware flow control enable. If this bit is set to 1, RTS hardware flow control is enabled. Data is only requested when there is space in the receive FIFO for it to be received.
        ADD_BITFIELD_RW(RTSEN, 14, 1)
        // This bit is the complement of the UART Out2 (nUARTOut2) modem status output. That is, when the bit is programmed to a 1, the output is 0. For DTE this can be used as Ring Indicator (RI).
        ADD_BITFIELD_RW(OUT2, 13, 1)
        // This bit is the complement of the UART Out1 (nUARTOut1) modem status output. That is, when the bit is programmed to a 1 the output is 0. For DTE this can be used as Data Carrier Detect (DCD).
        ADD_BITFIELD_RW(OUT1, 12, 1)
        // Request to send. This bit is the complement of the UART request to send, nUARTRTS, modem status output. That is, when the bit is programmed to a 1 then nUARTRTS is LOW.
        ADD_BITFIELD_RW(RTS, 11, 1)
        // Data transmit ready. This bit is the complement of the UART data transmit ready, nUARTDTR, modem status output. That is, when the bit is programmed to a 1 then nUARTDTR is LOW.
        ADD_BITFIELD_RW(DTR, 10, 1)
        // Receive enable. If this bit is set to 1, the receive section of the UART is enabled. Data reception occurs for either UART signals or SIR signals depending on the setting of the SIREN bit. When the UART is disabled in the middle of reception, it completes the current character before stopping.
        ADD_BITFIELD_RW(RXE, 9, 1)
        // Transmit enable. If this bit is set to 1, the transmit section of the UART is enabled. Data transmission occurs for either UART signals, or SIR signals depending on the setting of the SIREN bit. When the UART is disabled in the middle of transmission, it completes the current character before stopping.
        ADD_BITFIELD_RW(TXE, 8, 1)
        // Loopback enable. If this bit is set to 1 and the SIREN bit is set to 1 and the SIRTEST bit in the Test Control Register, UARTTCR is set to 1, then the nSIROUT path is inverted, and fed through to the SIRIN path. The SIRTEST bit in the test register must be set to 1 to override the normal half-duplex SIR operation. This must be the requirement for accessing the test registers during normal operation, and SIRTEST must be cleared to 0 when loopback testing is finished. This feature reduces the amount of external coupling required during system test. If this bit is set to 1, and the SIRTEST bit is set to 0, the UARTTXD path is fed through to the UARTRXD path. In either SIR mode or UART mode, when this bit is set, the modem outputs are also fed through to the modem inputs. This bit is cleared to 0 on reset, to disable loopback.
        ADD_BITFIELD_RW(LBE, 7, 1)
        // SIR low-power IrDA mode. This bit selects the IrDA encoding mode. If this bit is cleared to 0, low-level bits are transmitted as an active high pulse with a width of 3 / 16th of the bit period. If this bit is set to 1, low-level bits are transmitted with a pulse width that is 3 times the period of the IrLPBaud16 input signal, regardless of the selected bit rate. Setting this bit uses less power, but might reduce transmission distances.
        ADD_BITFIELD_RW(SIRLP, 2, 1)
        // SIR enable: 0 = IrDA SIR ENDEC is disabled. nSIROUT remains LOW (no light pulse generated), and signal transitions on SIRIN have no effect. 1 = IrDA SIR ENDEC is enabled. Data is transmitted and received on nSIROUT and SIRIN. UARTTXD remains HIGH, in the marking state. Signal transitions on UARTRXD or modem status inputs have no effect. This bit has no effect if the UARTEN bit disables the UART.
        ADD_BITFIELD_RW(SIREN, 1, 1)
        // UART enable: 0 = UART is disabled. If the UART is disabled in the middle of transmission or reception, it completes the current character before stopping. 1 = the UART is enabled. Data transmission and reception occurs for either UART signals or SIR signals depending on the setting of the SIREN bit.
        ADD_BITFIELD_RW(UARTEN, 0, 1)
    END_TYPE()

    // Interrupt FIFO Level Select Register, UARTIFLS
    // Reset value: 0x00000012
    BEGIN_TYPE(UARTIFLS_t, uint32_t)
        // Receive interrupt FIFO level select. The trigger points for the receive interrupt are as follows: b000 = Receive FIFO becomes >= 1 / 8 full b001 = Receive FIFO becomes >= 1 / 4 full b010 = Receive FIFO becomes >= 1 / 2 full b011 = Receive FIFO becomes >= 3 / 4 full b100 = Receive FIFO becomes >= 7 / 8 full b101-b111 = reserved.
        ADD_BITFIELD_RW(RXIFLSEL, 3, 3)
        // Transmit interrupt FIFO level select. The trigger points for the transmit interrupt are as follows: b000 = Transmit FIFO becomes <= 1 / 8 full b001 = Transmit FIFO becomes <= 1 / 4 full b010 = Transmit FIFO becomes <= 1 / 2 full b011 = Transmit FIFO becomes <= 3 / 4 full b100 = Transmit FIFO becomes <= 7 / 8 full b101-b111 = reserved.
        ADD_BITFIELD_RW(TXIFLSEL, 0, 3)
    END_TYPE()

    // Interrupt Mask Set/Clear Register, UARTIMSC
    // Reset value: 0x00000000
    BEGIN_TYPE(UARTIMSC_t, uint32_t)
        // Overrun error interrupt mask. A read returns the current mask for the UARTOEINTR interrupt. On a write of 1, the mask of the UARTOEINTR interrupt is set. A write of 0 clears the mask.
        ADD_BITFIELD_RW(OEIM, 10, 1)
        // Break error interrupt mask. A read returns the current mask for the UARTBEINTR interrupt. On a write of 1, the mask of the UARTBEINTR interrupt is set. A write of 0 clears the mask.
        ADD_BITFIELD_RW(BEIM, 9, 1)
        // Parity error interrupt mask. A read returns the current mask for the UARTPEINTR interrupt. On a write of 1, the mask of the UARTPEINTR interrupt is set. A write of 0 clears the mask.
        ADD_BITFIELD_RW(PEIM, 8, 1)
        // Framing error interrupt mask. A read returns the current mask for the UARTFEINTR interrupt. On a write of 1, the mask of the UARTFEINTR interrupt is set. A write of 0 clears the mask.
        ADD_BITFIELD_RW(FEIM, 7, 1)
        // Receive timeout interrupt mask. A read returns the current mask for the UARTRTINTR interrupt. On a write of 1, the mask of the UARTRTINTR interrupt is set. A write of 0 clears the mask.
        ADD_BITFIELD_RW(RTIM, 6, 1)
        // Transmit interrupt mask. A read returns the current mask for the UARTTXINTR interrupt. On a write of 1, the mask of the UARTTXINTR interrupt is set. A write of 0 clears the mask.
        ADD_BITFIELD_RW(TXIM, 5, 1)
        // Receive interrupt mask. A read returns the current mask for the UARTRXINTR interrupt. On a write of 1, the mask of the UARTRXINTR interrupt is set. A write of 0 clears the mask.
        ADD_BITFIELD_RW(RXIM, 4, 1)
        // nUARTDSR modem interrupt mask. A read returns the current mask for the UARTDSRINTR interrupt. On a write of 1, the mask of the UARTDSRINTR interrupt is set. A write of 0 clears the mask.
        ADD_BITFIELD_RW(DSRMIM, 3, 1)
        // nUARTDCD modem interrupt mask. A read returns the current mask for the UARTDCDINTR interrupt. On a write of 1, the mask of the UARTDCDINTR interrupt is set. A write of 0 clears the mask.
        ADD_BITFIELD_RW(DCDMIM, 2, 1)
        // nUARTCTS modem interrupt mask. A read returns the current mask for the UARTCTSINTR interrupt. On a write of 1, the mask of the UARTCTSINTR interrupt is set. A write of 0 clears the mask.
        ADD_BITFIELD_RW(CTSMIM, 1, 1)
        // nUARTRI modem interrupt mask. A read returns the current mask for the UARTRIINTR interrupt. On a write of 1, the mask of the UARTRIINTR interrupt is set. A write of 0 clears the mask.
        ADD_BITFIELD_RW(RIMIM, 0, 1)
    END_TYPE()

    // Raw Interrupt Status Register, UARTRIS
    // Reset value: 0x00000000
    BEGIN_TYPE(UARTRIS_t, uint32_t)
        // Overrun error interrupt status. Returns the raw interrupt state of the UARTOEINTR interrupt.
        ADD_BITFIELD_RO(OERIS, 10, 1)
        // Break error interrupt status. Returns the raw interrupt state of the UARTBEINTR interrupt.
        ADD_BITFIELD_RO(BERIS, 9, 1)
        // Parity error interrupt status. Returns the raw interrupt state of the UARTPEINTR interrupt.
        ADD_BITFIELD_RO(PERIS, 8, 1)
        // Framing error interrupt status. Returns the raw interrupt state of the UARTFEINTR interrupt.
        ADD_BITFIELD_RO(FERIS, 7, 1)
        // Receive timeout interrupt status. Returns the raw interrupt state of the UARTRTINTR interrupt. a
        ADD_BITFIELD_RO(RTRIS, 6, 1)
        // Transmit interrupt status. Returns the raw interrupt state of the UARTTXINTR interrupt.
        ADD_BITFIELD_RO(TXRIS, 5, 1)
        // Receive interrupt status. Returns the raw interrupt state of the UARTRXINTR interrupt.
        ADD_BITFIELD_RO(RXRIS, 4, 1)
        // nUARTDSR modem interrupt status. Returns the raw interrupt state of the UARTDSRINTR interrupt.
        ADD_BITFIELD_RO(DSRRMIS, 3, 1)
        // nUARTDCD modem interrupt status. Returns the raw interrupt state of the UARTDCDINTR interrupt.
        ADD_BITFIELD_RO(DCDRMIS, 2, 1)
        // nUARTCTS modem interrupt status. Returns the raw interrupt state of the UARTCTSINTR interrupt.
        ADD_BITFIELD_RO(CTSRMIS, 1, 1)
        // nUARTRI modem interrupt status. Returns the raw interrupt state of the UARTRIINTR interrupt.
        ADD_BITFIELD_RO(RIRMIS, 0, 1)
    END_TYPE()

    // Masked Interrupt Status Register, UARTMIS
    // Reset value: 0x00000000
    BEGIN_TYPE(UARTMIS_t, uint32_t)
        // Overrun error masked interrupt status. Returns the masked interrupt state of the UARTOEINTR interrupt.
        ADD_BITFIELD_RO(OEMIS, 10, 1)
        // Break error masked interrupt status. Returns the masked interrupt state of the UARTBEINTR interrupt.
        ADD_BITFIELD_RO(BEMIS, 9, 1)
        // Parity error masked interrupt status. Returns the masked interrupt state of the UARTPEINTR interrupt.
        ADD_BITFIELD_RO(PEMIS, 8, 1)
        // Framing error masked interrupt status. Returns the masked interrupt state of the UARTFEINTR interrupt.
        ADD_BITFIELD_RO(FEMIS, 7, 1)
        // Receive timeout masked interrupt status. Returns the masked interrupt state of the UARTRTINTR interrupt.
        ADD_BITFIELD_RO(RTMIS, 6, 1)
        // Transmit masked interrupt status. Returns the masked interrupt state of the UARTTXINTR interrupt.
        ADD_BITFIELD_RO(TXMIS, 5, 1)
        // Receive masked interrupt status. Returns the masked interrupt state of the UARTRXINTR interrupt.
        ADD_BITFIELD_RO(RXMIS, 4, 1)
        // nUARTDSR modem masked interrupt status. Returns the masked interrupt state of the UARTDSRINTR interrupt.
        ADD_BITFIELD_RO(DSRMMIS, 3, 1)
        // nUARTDCD modem masked interrupt status. Returns the masked interrupt state of the UARTDCDINTR interrupt.
        ADD_BITFIELD_RO(DCDMMIS, 2, 1)
        // nUARTCTS modem masked interrupt status. Returns the masked interrupt state of the UARTCTSINTR interrupt.
        ADD_BITFIELD_RO(CTSMMIS, 1, 1)
        // nUARTRI modem masked interrupt status. Returns the masked interrupt state of the UARTRIINTR interrupt.
        ADD_BITFIELD_RO(RIMMIS, 0, 1)
    END_TYPE()

    // Interrupt Clear Register, UARTICR
    // Reset value: 0x00000000
    BEGIN_TYPE(UARTICR_t, uint32_t)
        // Overrun error interrupt clear. Clears the UARTOEINTR interrupt.
        ADD_BITFIELD_RW(OEIC, 10, 1)
        // Break error interrupt clear. Clears the UARTBEINTR interrupt.
        ADD_BITFIELD_RW(BEIC, 9, 1)
        // Parity error interrupt clear. Clears the UARTPEINTR interrupt.
        ADD_BITFIELD_RW(PEIC, 8, 1)
        // Framing error interrupt clear. Clears the UARTFEINTR interrupt.
        ADD_BITFIELD_RW(FEIC, 7, 1)
        // Receive timeout interrupt clear. Clears the UARTRTINTR interrupt.
        ADD_BITFIELD_RW(RTIC, 6, 1)
        // Transmit interrupt clear. Clears the UARTTXINTR interrupt.
        ADD_BITFIELD_RW(TXIC, 5, 1)
        // Receive interrupt clear. Clears the UARTRXINTR interrupt.
        ADD_BITFIELD_RW(RXIC, 4, 1)
        // nUARTDSR modem interrupt clear. Clears the UARTDSRINTR interrupt.
        ADD_BITFIELD_RW(DSRMIC, 3, 1)
        // nUARTDCD modem interrupt clear. Clears the UARTDCDINTR interrupt.
        ADD_BITFIELD_RW(DCDMIC, 2, 1)
        // nUARTCTS modem interrupt clear. Clears the UARTCTSINTR interrupt.
        ADD_BITFIELD_RW(CTSMIC, 1, 1)
        // nUARTRI modem interrupt clear. Clears the UARTRIINTR interrupt.
        ADD_BITFIELD_RW(RIMIC, 0, 1)
    END_TYPE()

    // DMA Control Register, UARTDMACR
    // Reset value: 0x00000000
    BEGIN_TYPE(UARTDMACR_t, uint32_t)
        // DMA on error. If this bit is set to 1, the DMA receive request outputs, UARTRXDMASREQ or UARTRXDMABREQ, are disabled when the UART error interrupt is asserted.
        ADD_BITFIELD_RW(DMAONERR, 2, 1)
        // Transmit DMA enable. If this bit is set to 1, DMA for the transmit FIFO is enabled.
        ADD_BITFIELD_RW(TXDMAE, 1, 1)
        // Receive DMA enable. If this bit is set to 1, DMA for the receive FIFO is enabled.
        ADD_BITFIELD_RW(RXDMAE, 0, 1)
    END_TYPE()

    // UARTPeriphID0 Register
    // Reset value: 0x00000011
    BEGIN_TYPE(UARTPERIPHID0_t, uint32_t)
        // These bits read back as 0x11
        ADD_BITFIELD_RO(PARTNUMBER0, 0, 8)
    END_TYPE()

    // UARTPeriphID1 Register
    // Reset value: 0x00000010
    BEGIN_TYPE(UARTPERIPHID1_t, uint32_t)
        // These bits read back as 0x1
        ADD_BITFIELD_RO(DESIGNER0, 4, 4)
        // These bits read back as 0x0
        ADD_BITFIELD_RO(PARTNUMBER1, 0, 4)
    END_TYPE()

    // UARTPeriphID2 Register
    // Reset value: 0x00000034
    BEGIN_TYPE(UARTPERIPHID2_t, uint32_t)
        // This field depends on the revision of the UART: r1p0 0x0 r1p1 0x1 r1p3 0x2 r1p4 0x2 r1p5 0x3
        ADD_BITFIELD_RO(REVISION, 4, 4)
        // These bits read back as 0x4
        ADD_BITFIELD_RO(DESIGNER1, 0, 4)
    END_TYPE()

    // UARTPeriphID3 Register
    // Reset value: 0x00000000
    BEGIN_TYPE(UARTPERIPHID3_t, uint32_t)
        // These bits read back as 0x00
        ADD_BITFIELD_RO(CONFIGURATION, 0, 8)
    END_TYPE()

    // UARTPCellID0 Register
    // Reset value: 0x0000000d
    BEGIN_TYPE(UARTPCELLID0_t, uint32_t)
        // These bits read back as 0x0D
        ADD_BITFIELD_RO(UARTPCELLID0, 0, 8)
    END_TYPE()

    // UARTPCellID1 Register
    // Reset value: 0x000000f0
    BEGIN_TYPE(UARTPCELLID1_t, uint32_t)
        // These bits read back as 0xF0
        ADD_BITFIELD_RO(UARTPCELLID1, 0, 8)
    END_TYPE()

    // UARTPCellID2 Register
    // Reset value: 0x00000005
    BEGIN_TYPE(UARTPCELLID2_t, uint32_t)
        // These bits read back as 0x05
        ADD_BITFIELD_RO(UARTPCELLID2, 0, 8)
    END_TYPE()

    // UARTPCellID3 Register
    // Reset value: 0x000000b1
    BEGIN_TYPE(UARTPCELLID3_t, uint32_t)
        // These bits read back as 0xB1
        ADD_BITFIELD_RO(UARTPCELLID3, 0, 8)
    END_TYPE()

    struct UART0_t {
        UARTDR_t                      UARTDR;
        UARTRSR_t                     UARTRSR;
        uint32_t                      reserved0[4];
        UARTFR_t                      UARTFR;
        uint32_t                      reserved1;
        UARTILPR_t                    UARTILPR;
        UARTIBRD_t                    UARTIBRD;
        UARTFBRD_t                    UARTFBRD;
        UARTLCR_H_t                   UARTLCR_H;
        UARTCR_t                      UARTCR;
        UARTIFLS_t                    UARTIFLS;
        UARTIMSC_t                    UARTIMSC;
        UARTRIS_t                     UARTRIS;
        UARTMIS_t                     UARTMIS;
        UARTICR_t                     UARTICR;
        UARTDMACR_t                   UARTDMACR;
        uint32_t                      reserved2[997];
        UARTPERIPHID0_t               UARTPERIPHID0;
        UARTPERIPHID1_t               UARTPERIPHID1;
        UARTPERIPHID2_t               UARTPERIPHID2;
        UARTPERIPHID3_t               UARTPERIPHID3;
        UARTPCELLID0_t                UARTPCELLID0;
        UARTPCELLID1_t                UARTPCELLID1;
        UARTPCELLID2_t                UARTPCELLID2;
        UARTPCELLID3_t                UARTPCELLID3;
    };

    static UART0_t & UART0     = (*(UART0_t *)0x40034000);
    static UART0_t & UART0_XOR = (*(UART0_t *)0x40035000);
    static UART0_t & UART0_SET = (*(UART0_t *)0x40036000);
    static UART0_t & UART0_CLR = (*(UART0_t *)0x40037000);

} // _UART0_

namespace _UART1_  {

    static _UART0_::UART0_t & UART1     = (*(_UART0_::UART0_t *)0x40038000);
    static _UART0_::UART0_t & UART1_XOR = (*(_UART0_::UART0_t *)0x40039000);
    static _UART0_::UART0_t & UART1_SET = (*(_UART0_::UART0_t *)0x4003a000);
    static _UART0_::UART0_t & UART1_CLR = (*(_UART0_::UART0_t *)0x4003b000);

} // _UART1_

namespace _SPI0_  {

    // Control register 0, SSPCR0 on page 3-4
    // Reset value: 0x00000000
    BEGIN_TYPE(SSPCR0_t, uint32_t)
        // Serial clock rate. The value SCR is used to generate the transmit and receive bit rate of the PrimeCell SSP. The bit rate is: F SSPCLK CPSDVSR x (1+SCR) where CPSDVSR is an even value from 2-254, programmed through the SSPCPSR register and SCR is a value from 0-255.
        ADD_BITFIELD_RW(SCR, 8, 8)
        // SSPCLKOUT phase, applicable to Motorola SPI frame format only. See Motorola SPI frame format on page 2-10.
        ADD_BITFIELD_RW(SPH, 7, 1)
        // SSPCLKOUT polarity, applicable to Motorola SPI frame format only. See Motorola SPI frame format on page 2-10.
        ADD_BITFIELD_RW(SPO, 6, 1)
        // Frame format: 00 Motorola SPI frame format. 01 TI synchronous serial frame format. 10 National Microwire frame format. 11 Reserved, undefined operation.
        ADD_BITFIELD_RW(FRF, 4, 2)
        // Data Size Select: 0000 Reserved, undefined operation. 0001 Reserved, undefined operation. 0010 Reserved, undefined operation. 0011 4-bit data. 0100 5-bit data. 0101 6-bit data. 0110 7-bit data. 0111 8-bit data. 1000 9-bit data. 1001 10-bit data. 1010 11-bit data. 1011 12-bit data. 1100 13-bit data. 1101 14-bit data. 1110 15-bit data. 1111 16-bit data.
        ADD_BITFIELD_RW(DSS, 0, 4)
    END_TYPE()

    // Control register 1, SSPCR1 on page 3-5
    // Reset value: 0x00000000
    BEGIN_TYPE(SSPCR1_t, uint32_t)
        // Slave-mode output disable. This bit is relevant only in the slave mode, MS=1. In multiple-slave systems, it is possible for an PrimeCell SSP master to broadcast a message to all slaves in the system while ensuring that only one slave drives data onto its serial output line. In such systems the RXD lines from multiple slaves could be tied together. To operate in such systems, the SOD bit can be set if the PrimeCell SSP slave is not supposed to drive the SSPTXD line: 0 SSP can drive the SSPTXD output in slave mode. 1 SSP must not drive the SSPTXD output in slave mode.
        ADD_BITFIELD_RW(SOD, 3, 1)
        // Master or slave mode select. This bit can be modified only when the PrimeCell SSP is disabled, SSE=0: 0 Device configured as master, default. 1 Device configured as slave.
        ADD_BITFIELD_RW(MS, 2, 1)
        // Synchronous serial port enable: 0 SSP operation disabled. 1 SSP operation enabled.
        ADD_BITFIELD_RW(SSE, 1, 1)
        // Loop back mode: 0 Normal serial port operation enabled. 1 Output of transmit serial shifter is connected to input of receive serial shifter internally.
        ADD_BITFIELD_RW(LBM, 0, 1)
    END_TYPE()

    // Data register, SSPDR on page 3-6
    // Reset value: 0x00000000
    BEGIN_TYPE(SSPDR_t, uint32_t)
        // Transmit/Receive FIFO: Read Receive FIFO. Write Transmit FIFO. You must right-justify data when the PrimeCell SSP is programmed for a data size that is less than 16 bits. Unused bits at the top are ignored by transmit logic. The receive logic automatically right-justifies.
        ADD_BITFIELD_RW(DATA, 0, 16)
    END_TYPE()

    // Status register, SSPSR on page 3-7
    // Reset value: 0x00000003
    BEGIN_TYPE(SSPSR_t, uint32_t)
        // PrimeCell SSP busy flag, RO: 0 SSP is idle. 1 SSP is currently transmitting and/or receiving a frame or the transmit FIFO is not empty.
        ADD_BITFIELD_RO(BSY, 4, 1)
        // Receive FIFO full, RO: 0 Receive FIFO is not full. 1 Receive FIFO is full.
        ADD_BITFIELD_RO(RFF, 3, 1)
        // Receive FIFO not empty, RO: 0 Receive FIFO is empty. 1 Receive FIFO is not empty.
        ADD_BITFIELD_RO(RNE, 2, 1)
        // Transmit FIFO not full, RO: 0 Transmit FIFO is full. 1 Transmit FIFO is not full.
        ADD_BITFIELD_RO(TNF, 1, 1)
        // Transmit FIFO empty, RO: 0 Transmit FIFO is not empty. 1 Transmit FIFO is empty.
        ADD_BITFIELD_RO(TFE, 0, 1)
    END_TYPE()

    // Clock prescale register, SSPCPSR on page 3-8
    // Reset value: 0x00000000
    BEGIN_TYPE(SSPCPSR_t, uint32_t)
        // Clock prescale divisor. Must be an even number from 2-254, depending on the frequency of SSPCLK. The least significant bit always returns zero on reads.
        ADD_BITFIELD_RW(CPSDVSR, 0, 8)
    END_TYPE()

    // Interrupt mask set or clear register, SSPIMSC on page 3-9
    // Reset value: 0x00000000
    BEGIN_TYPE(SSPIMSC_t, uint32_t)
        // Transmit FIFO interrupt mask: 0 Transmit FIFO half empty or less condition interrupt is masked. 1 Transmit FIFO half empty or less condition interrupt is not masked.
        ADD_BITFIELD_RW(TXIM, 3, 1)
        // Receive FIFO interrupt mask: 0 Receive FIFO half full or less condition interrupt is masked. 1 Receive FIFO half full or less condition interrupt is not masked.
        ADD_BITFIELD_RW(RXIM, 2, 1)
        // Receive timeout interrupt mask: 0 Receive FIFO not empty and no read prior to timeout period interrupt is masked. 1 Receive FIFO not empty and no read prior to timeout period interrupt is not masked.
        ADD_BITFIELD_RW(RTIM, 1, 1)
        // Receive overrun interrupt mask: 0 Receive FIFO written to while full condition interrupt is masked. 1 Receive FIFO written to while full condition interrupt is not masked.
        ADD_BITFIELD_RW(RORIM, 0, 1)
    END_TYPE()

    // Raw interrupt status register, SSPRIS on page 3-10
    // Reset value: 0x00000008
    BEGIN_TYPE(SSPRIS_t, uint32_t)
        // Gives the raw interrupt state, prior to masking, of the SSPTXINTR interrupt
        ADD_BITFIELD_RO(TXRIS, 3, 1)
        // Gives the raw interrupt state, prior to masking, of the SSPRXINTR interrupt
        ADD_BITFIELD_RO(RXRIS, 2, 1)
        // Gives the raw interrupt state, prior to masking, of the SSPRTINTR interrupt
        ADD_BITFIELD_RO(RTRIS, 1, 1)
        // Gives the raw interrupt state, prior to masking, of the SSPRORINTR interrupt
        ADD_BITFIELD_RO(RORRIS, 0, 1)
    END_TYPE()

    // Masked interrupt status register, SSPMIS on page 3-11
    // Reset value: 0x00000000
    BEGIN_TYPE(SSPMIS_t, uint32_t)
        // Gives the transmit FIFO masked interrupt state, after masking, of the SSPTXINTR interrupt
        ADD_BITFIELD_RO(TXMIS, 3, 1)
        // Gives the receive FIFO masked interrupt state, after masking, of the SSPRXINTR interrupt
        ADD_BITFIELD_RO(RXMIS, 2, 1)
        // Gives the receive timeout masked interrupt state, after masking, of the SSPRTINTR interrupt
        ADD_BITFIELD_RO(RTMIS, 1, 1)
        // Gives the receive over run masked interrupt status, after masking, of the SSPRORINTR interrupt
        ADD_BITFIELD_RO(RORMIS, 0, 1)
    END_TYPE()

    // Interrupt clear register, SSPICR on page 3-11
    // Reset value: 0x00000000
    BEGIN_TYPE(SSPICR_t, uint32_t)
        // Clears the SSPRTINTR interrupt
        ADD_BITFIELD_RW(RTIC, 1, 1)
        // Clears the SSPRORINTR interrupt
        ADD_BITFIELD_RW(RORIC, 0, 1)
    END_TYPE()

    // DMA control register, SSPDMACR on page 3-12
    // Reset value: 0x00000000
    BEGIN_TYPE(SSPDMACR_t, uint32_t)
        // Transmit DMA Enable. If this bit is set to 1, DMA for the transmit FIFO is enabled.
        ADD_BITFIELD_RW(TXDMAE, 1, 1)
        // Receive DMA Enable. If this bit is set to 1, DMA for the receive FIFO is enabled.
        ADD_BITFIELD_RW(RXDMAE, 0, 1)
    END_TYPE()

    // Peripheral identification registers, SSPPeriphID0-3 on page 3-13
    // Reset value: 0x00000022
    BEGIN_TYPE(SSPPERIPHID0_t, uint32_t)
        // These bits read back as 0x22
        ADD_BITFIELD_RO(PARTNUMBER0, 0, 8)
    END_TYPE()

    // Peripheral identification registers, SSPPeriphID0-3 on page 3-13
    // Reset value: 0x00000010
    BEGIN_TYPE(SSPPERIPHID1_t, uint32_t)
        // These bits read back as 0x1
        ADD_BITFIELD_RO(DESIGNER0, 4, 4)
        // These bits read back as 0x0
        ADD_BITFIELD_RO(PARTNUMBER1, 0, 4)
    END_TYPE()

    // Peripheral identification registers, SSPPeriphID0-3 on page 3-13
    // Reset value: 0x00000034
    BEGIN_TYPE(SSPPERIPHID2_t, uint32_t)
        // These bits return the peripheral revision
        ADD_BITFIELD_RO(REVISION, 4, 4)
        // These bits read back as 0x4
        ADD_BITFIELD_RO(DESIGNER1, 0, 4)
    END_TYPE()

    // Peripheral identification registers, SSPPeriphID0-3 on page 3-13
    // Reset value: 0x00000000
    BEGIN_TYPE(SSPPERIPHID3_t, uint32_t)
        // These bits read back as 0x00
        ADD_BITFIELD_RO(CONFIGURATION, 0, 8)
    END_TYPE()

    // PrimeCell identification registers, SSPPCellID0-3 on page 3-16
    // Reset value: 0x0000000d
    BEGIN_TYPE(SSPPCELLID0_t, uint32_t)
        // These bits read back as 0x0D
        ADD_BITFIELD_RO(SSPPCELLID0, 0, 8)
    END_TYPE()

    // PrimeCell identification registers, SSPPCellID0-3 on page 3-16
    // Reset value: 0x000000f0
    BEGIN_TYPE(SSPPCELLID1_t, uint32_t)
        // These bits read back as 0xF0
        ADD_BITFIELD_RO(SSPPCELLID1, 0, 8)
    END_TYPE()

    // PrimeCell identification registers, SSPPCellID0-3 on page 3-16
    // Reset value: 0x00000005
    BEGIN_TYPE(SSPPCELLID2_t, uint32_t)
        // These bits read back as 0x05
        ADD_BITFIELD_RO(SSPPCELLID2, 0, 8)
    END_TYPE()

    // PrimeCell identification registers, SSPPCellID0-3 on page 3-16
    // Reset value: 0x000000b1
    BEGIN_TYPE(SSPPCELLID3_t, uint32_t)
        // These bits read back as 0xB1
        ADD_BITFIELD_RO(SSPPCELLID3, 0, 8)
    END_TYPE()

    struct SPI0_t {
        SSPCR0_t                      SSPCR0;
        SSPCR1_t                      SSPCR1;
        SSPDR_t                       SSPDR;
        SSPSR_t                       SSPSR;
        SSPCPSR_t                     SSPCPSR;
        SSPIMSC_t                     SSPIMSC;
        SSPRIS_t                      SSPRIS;
        SSPMIS_t                      SSPMIS;
        SSPICR_t                      SSPICR;
        SSPDMACR_t                    SSPDMACR;
        uint32_t                      reserved0[1006];
        SSPPERIPHID0_t                SSPPERIPHID0;
        SSPPERIPHID1_t                SSPPERIPHID1;
        SSPPERIPHID2_t                SSPPERIPHID2;
        SSPPERIPHID3_t                SSPPERIPHID3;
        SSPPCELLID0_t                 SSPPCELLID0;
        SSPPCELLID1_t                 SSPPCELLID1;
        SSPPCELLID2_t                 SSPPCELLID2;
        SSPPCELLID3_t                 SSPPCELLID3;
    };

    static SPI0_t & SPI0     = (*(SPI0_t *)0x4003c000);
    static SPI0_t & SPI0_XOR = (*(SPI0_t *)0x4003d000);
    static SPI0_t & SPI0_SET = (*(SPI0_t *)0x4003e000);
    static SPI0_t & SPI0_CLR = (*(SPI0_t *)0x4003f000);

} // _SPI0_

namespace _SPI1_  {

    static _SPI0_::SPI0_t & SPI1     = (*(_SPI0_::SPI0_t *)0x40040000);
    static _SPI0_::SPI0_t & SPI1_XOR = (*(_SPI0_::SPI0_t *)0x40041000);
    static _SPI0_::SPI0_t & SPI1_SET = (*(_SPI0_::SPI0_t *)0x40042000);
    static _SPI0_::SPI0_t & SPI1_CLR = (*(_SPI0_::SPI0_t *)0x40043000);

} // _SPI1_

// DW_apb_i2c address block
// 
// List of configuration constants for the Synopsys I2C hardware (you may see references to these in I2C register header; these are *fixed* values, set at hardware design time):
// 
// IC_ULTRA_FAST_MODE ................ 0x0
// IC_UFM_TBUF_CNT_DEFAULT ........... 0x8
// IC_UFM_SCL_LOW_COUNT .............. 0x0008
// IC_UFM_SCL_HIGH_COUNT ............. 0x0006
// IC_TX_TL .......................... 0x0
// IC_TX_CMD_BLOCK ................... 0x1
// IC_HAS_DMA ........................ 0x1
// IC_HAS_ASYNC_FIFO ................. 0x0
// IC_SMBUS_ARP ...................... 0x0
// IC_FIRST_DATA_BYTE_STATUS ......... 0x1
// IC_INTR_IO ........................ 0x1
// IC_MASTER_MODE .................... 0x1
// IC_DEFAULT_ACK_GENERAL_CALL ....... 0x1
// IC_INTR_POL ....................... 0x1
// IC_OPTIONAL_SAR ................... 0x0
// IC_DEFAULT_TAR_SLAVE_ADDR ......... 0x055
// IC_DEFAULT_SLAVE_ADDR ............. 0x055
// IC_DEFAULT_HS_SPKLEN .............. 0x1
// IC_FS_SCL_HIGH_COUNT .............. 0x0006
// IC_HS_SCL_LOW_COUNT ............... 0x0008
// IC_DEVICE_ID_VALUE ................ 0x0
// IC_10BITADDR_MASTER ............... 0x0
// IC_CLK_FREQ_OPTIMIZATION .......... 0x0
// IC_DEFAULT_FS_SPKLEN .............. 0x7
// IC_ADD_ENCODED_PARAMS ............. 0x0
// IC_DEFAULT_SDA_HOLD ............... 0x000001
// IC_DEFAULT_SDA_SETUP .............. 0x64
// IC_AVOID_RX_FIFO_FLUSH_ON_TX_ABRT . 0x0
// IC_CLOCK_PERIOD ................... 100
// IC_EMPTYFIFO_HOLD_MASTER_EN ....... 1
// IC_RESTART_EN ..................... 0x1
// IC_TX_CMD_BLOCK_DEFAULT ........... 0x0
// IC_BUS_CLEAR_FEATURE .............. 0x0
// IC_CAP_LOADING .................... 100
// IC_FS_SCL_LOW_COUNT ............... 0x000d
// APB_DATA_WIDTH .................... 32
// IC_SDA_STUCK_TIMEOUT_DEFAULT ...... 0xffffffff
// IC_SLV_DATA_NACK_ONLY ............. 0x1
// IC_10BITADDR_SLAVE ................ 0x0
// IC_CLK_TYPE ....................... 0x0
// IC_SMBUS_UDID_MSB ................. 0x0
// IC_SMBUS_SUSPEND_ALERT ............ 0x0
// IC_HS_SCL_HIGH_COUNT .............. 0x0006
// IC_SLV_RESTART_DET_EN ............. 0x1
// IC_SMBUS .......................... 0x0
// IC_OPTIONAL_SAR_DEFAULT ........... 0x0
// IC_PERSISTANT_SLV_ADDR_DEFAULT .... 0x0
// IC_USE_COUNTS ..................... 0x0
// IC_RX_BUFFER_DEPTH ................ 16
// IC_SCL_STUCK_TIMEOUT_DEFAULT ...... 0xffffffff
// IC_RX_FULL_HLD_BUS_EN ............. 0x1
// IC_SLAVE_DISABLE .................. 0x1
// IC_RX_TL .......................... 0x0
// IC_DEVICE_ID ...................... 0x0
// IC_HC_COUNT_VALUES ................ 0x0
// I2C_DYNAMIC_TAR_UPDATE ............ 0
// IC_SMBUS_CLK_LOW_MEXT_DEFAULT ..... 0xffffffff
// IC_SMBUS_CLK_LOW_SEXT_DEFAULT ..... 0xffffffff
// IC_HS_MASTER_CODE ................. 0x1
// IC_SMBUS_RST_IDLE_CNT_DEFAULT ..... 0xffff
// IC_SMBUS_UDID_LSB_DEFAULT ......... 0xffffffff
// IC_SS_SCL_HIGH_COUNT .............. 0x0028
// IC_SS_SCL_LOW_COUNT ............... 0x002f
// IC_MAX_SPEED_MODE ................. 0x2
// IC_STAT_FOR_CLK_STRETCH ........... 0x0
// IC_STOP_DET_IF_MASTER_ACTIVE ...... 0x0
// IC_DEFAULT_UFM_SPKLEN ............. 0x1
// IC_TX_BUFFER_DEPTH ................ 16
namespace _I2C0_  {

    // I2C Control Register. This register can be written only when the DW_apb_i2c is disabled, which corresponds to the IC_ENABLE[0] register being set to 0. Writes at other times have no effect.
    // 
    // Read/Write Access: - bit 10 is read only. - bit 11 is read only - bit 16 is read only - bit 17 is read only - bits 18 and 19 are read only.
    // Reset value: 0x00000065
    BEGIN_TYPE(IC_CON_t, uint32_t)
        // Master issues the STOP_DET interrupt irrespective of whether master is active or not
        ADD_BITFIELD_RO(STOP_DET_IF_MASTER_ACTIVE, 10, 1)
        // This bit controls whether DW_apb_i2c should hold the bus when the Rx FIFO is physically full to its RX_BUFFER_DEPTH, as described in the IC_RX_FULL_HLD_BUS_EN parameter.
        // 
        // Reset value: 0x0.
        ADD_BITFIELD_RW(RX_FIFO_FULL_HLD_CTRL, 9, 1)
        // This bit controls the generation of the TX_EMPTY interrupt, as described in the IC_RAW_INTR_STAT register.
        // 
        // Reset value: 0x0.
        ADD_BITFIELD_RW(TX_EMPTY_CTRL, 8, 1)
        // In slave mode: - 1'b1:  issues the STOP_DET interrupt only when it is addressed. - 1'b0:  issues the STOP_DET irrespective of whether it's addressed or not. Reset value: 0x0
        // 
        // NOTE: During a general call address, this slave does not issue the STOP_DET interrupt if STOP_DET_IF_ADDRESSED = 1'b1, even if the slave responds to the general call address by generating ACK. The STOP_DET interrupt is generated only when the transmitted address matches the slave address (SAR).
        ADD_BITFIELD_RW(STOP_DET_IFADDRESSED, 7, 1)
        // This bit controls whether I2C has its slave disabled, which means once the presetn signal is applied, then this bit is set and the slave is disabled.
        // 
        // If this bit is set (slave is disabled), DW_apb_i2c functions only as a master and does not perform any action that requires a slave.
        // 
        // NOTE: Software should ensure that if this bit is written with 0, then bit 0 should also be written with a 0.
        ADD_BITFIELD_RW(IC_SLAVE_DISABLE, 6, 1)
        // Determines whether RESTART conditions may be sent when acting as a master. Some older slaves do not support handling RESTART conditions; however, RESTART conditions are used in several DW_apb_i2c operations. When RESTART is disabled, the master is prohibited from performing the following functions: - Sending a START BYTE - Performing any high-speed mode operation - High-speed mode operation - Performing direction changes in combined format mode - Performing a read operation with a 10-bit address By replacing RESTART condition followed by a STOP and a subsequent START condition, split operations are broken down into multiple DW_apb_i2c transfers. If the above operations are performed, it will result in setting bit 6 (TX_ABRT) of the IC_RAW_INTR_STAT register.
        // 
        // Reset value: ENABLED
        ADD_BITFIELD_RW(IC_RESTART_EN, 5, 1)
        // Controls whether the DW_apb_i2c starts its transfers in 7- or 10-bit addressing mode when acting as a master. - 0: 7-bit addressing - 1: 10-bit addressing
        ADD_BITFIELD_RW(IC_10BITADDR_MASTER, 4, 1)
        // When acting as a slave, this bit controls whether the DW_apb_i2c responds to 7- or 10-bit addresses. - 0: 7-bit addressing. The DW_apb_i2c ignores transactions that involve 10-bit addressing; for 7-bit addressing, only the lower 7 bits of the IC_SAR register are compared. - 1: 10-bit addressing. The DW_apb_i2c responds to only 10-bit addressing transfers that match the full 10 bits of the IC_SAR register.
        ADD_BITFIELD_RW(IC_10BITADDR_SLAVE, 3, 1)
        // These bits control at which speed the DW_apb_i2c operates; its setting is relevant only if one is operating the DW_apb_i2c in master mode. Hardware protects against illegal values being programmed by software. These bits must be programmed appropriately for slave mode also, as it is used to capture correct value of spike filter as per the speed mode.
        // 
        // This register should be programmed only with a value in the range of 1 to IC_MAX_SPEED_MODE; otherwise, hardware updates this register with the value of IC_MAX_SPEED_MODE.
        // 
        // 1: standard mode (100 kbit/s)
        // 
        // 2: fast mode (<=400 kbit/s) or fast mode plus (<=1000Kbit/s)
        // 
        // 3: high speed mode (3.4 Mbit/s)
        // 
        // Note: This field is not applicable when IC_ULTRA_FAST_MODE=1
        ADD_BITFIELD_RW(SPEED, 1, 2)
        // This bit controls whether the DW_apb_i2c master is enabled.
        // 
        // NOTE: Software should ensure that if this bit is written with '1' then bit 6 should also be written with a '1'.
        ADD_BITFIELD_RW(MASTER_MODE, 0, 1)
    END_TYPE()

    // Overflow when RX_FIFO is full
    static const uint32_t IC_CON_RX_FIFO_FULL_HLD_CTRL__DISABLED = 0;
    // Hold bus when RX_FIFO is full
    static const uint32_t IC_CON_RX_FIFO_FULL_HLD_CTRL__ENABLED = 1;
    // Default behaviour of TX_EMPTY interrupt
    static const uint32_t IC_CON_TX_EMPTY_CTRL__DISABLED = 0;
    // Controlled generation of TX_EMPTY interrupt
    static const uint32_t IC_CON_TX_EMPTY_CTRL__ENABLED = 1;
    // slave issues STOP_DET intr always
    static const uint32_t IC_CON_STOP_DET_IFADDRESSED__DISABLED = 0;
    // slave issues STOP_DET intr only if addressed
    static const uint32_t IC_CON_STOP_DET_IFADDRESSED__ENABLED = 1;
    // Slave mode is enabled
    static const uint32_t IC_CON_IC_SLAVE_DISABLE__SLAVE_ENABLED = 0;
    // Slave mode is disabled
    static const uint32_t IC_CON_IC_SLAVE_DISABLE__SLAVE_DISABLED = 1;
    // Master restart disabled
    static const uint32_t IC_CON_IC_RESTART_EN__DISABLED = 0;
    // Master restart enabled
    static const uint32_t IC_CON_IC_RESTART_EN__ENABLED = 1;
    // Master 7Bit addressing mode
    static const uint32_t IC_CON_IC_10BITADDR_MASTER__ADDR_7BITS = 0;
    // Master 10Bit addressing mode
    static const uint32_t IC_CON_IC_10BITADDR_MASTER__ADDR_10BITS = 1;
    // Slave 7Bit addressing
    static const uint32_t IC_CON_IC_10BITADDR_SLAVE__ADDR_7BITS = 0;
    // Slave 10Bit addressing
    static const uint32_t IC_CON_IC_10BITADDR_SLAVE__ADDR_10BITS = 1;
    // Standard Speed mode of operation
    static const uint32_t IC_CON_SPEED__STANDARD = 1;
    // Fast or Fast Plus mode of operation
    static const uint32_t IC_CON_SPEED__FAST = 2;
    // High Speed mode of operation
    static const uint32_t IC_CON_SPEED__HIGH = 3;
    // Master mode is disabled
    static const uint32_t IC_CON_MASTER_MODE__DISABLED = 0;
    // Master mode is enabled
    static const uint32_t IC_CON_MASTER_MODE__ENABLED = 1;

    // I2C Target Address Register
    // 
    // This register is 12 bits wide, and bits 31:12 are reserved. This register can be written to only when IC_ENABLE[0] is set to 0.
    // 
    // Note: If the software or application is aware that the DW_apb_i2c is not using the TAR address for the pending commands in the Tx FIFO, then it is possible to update the TAR address even while the Tx FIFO has entries (IC_STATUS[2]= 0). - It is not necessary to perform any write to this register if DW_apb_i2c is enabled as an I2C slave only.
    // Reset value: 0x00000055
    BEGIN_TYPE(IC_TAR_t, uint32_t)
        // This bit indicates whether software performs a Device-ID or General Call or START BYTE command. - 0: ignore bit 10 GC_OR_START and use IC_TAR normally - 1: perform special I2C command as specified in Device_ID or GC_OR_START bit Reset value: 0x0
        ADD_BITFIELD_RW(SPECIAL, 11, 1)
        // If bit 11 (SPECIAL) is set to 1 and bit 13(Device-ID) is set to 0, then this bit indicates whether a General Call or START byte command is to be performed by the DW_apb_i2c. - 0: General Call Address - after issuing a General Call, only writes may be performed. Attempting to issue a read command results in setting bit 6 (TX_ABRT) of the IC_RAW_INTR_STAT register. The DW_apb_i2c remains in General Call mode until the SPECIAL bit value (bit 11) is cleared. - 1: START BYTE Reset value: 0x0
        ADD_BITFIELD_RW(GC_OR_START, 10, 1)
        // This is the target address for any master transaction. When transmitting a General Call, these bits are ignored. To generate a START BYTE, the CPU needs to write only once into these bits.
        // 
        // If the IC_TAR and IC_SAR are the same, loopback exists but the FIFOs are shared between master and slave, so full loopback is not feasible. Only one direction loopback mode is supported (simplex), not duplex. A master cannot transmit to itself; it can transmit to only a slave.
        ADD_BITFIELD_RW(IC_TAR, 0, 10)
    END_TYPE()

    // Disables programming of GENERAL_CALL or START_BYTE transmission
    static const uint32_t IC_TAR_SPECIAL__DISABLED = 0;
    // Enables programming of GENERAL_CALL or START_BYTE transmission
    static const uint32_t IC_TAR_SPECIAL__ENABLED = 1;
    // GENERAL_CALL byte transmission
    static const uint32_t IC_TAR_GC_OR_START__GENERAL_CALL = 0;
    // START byte transmission
    static const uint32_t IC_TAR_GC_OR_START__START_BYTE = 1;

    // I2C Slave Address Register
    // Reset value: 0x00000055
    BEGIN_TYPE(IC_SAR_t, uint32_t)
        // The IC_SAR holds the slave address when the I2C is operating as a slave. For 7-bit addressing, only IC_SAR[6:0] is used.
        // 
        // This register can be written only when the I2C interface is disabled, which corresponds to the IC_ENABLE[0] register being set to 0. Writes at other times have no effect.
        // 
        // Note: The default values cannot be any of the reserved address locations: that is, 0x00 to 0x07, or 0x78 to 0x7f. The correct operation of the device is not guaranteed if you program the IC_SAR or IC_TAR to a reserved value. Refer to <<table_I2C_firstbyte_bit_defs>> for a complete list of these reserved values.
        ADD_BITFIELD_RW(IC_SAR, 0, 10)
    END_TYPE()

    // I2C Rx/Tx Data Buffer and Command Register; this is the register the CPU writes to when filling the TX FIFO and the CPU reads from when retrieving bytes from RX FIFO.
    // 
    // The size of the register changes as follows:
    // 
    // Write: - 11 bits when IC_EMPTYFIFO_HOLD_MASTER_EN=1 - 9 bits when IC_EMPTYFIFO_HOLD_MASTER_EN=0 Read: - 12 bits when IC_FIRST_DATA_BYTE_STATUS = 1 - 8 bits when IC_FIRST_DATA_BYTE_STATUS = 0 Note: In order for the DW_apb_i2c to continue acknowledging reads, a read command should be written for every byte that is to be received; otherwise the DW_apb_i2c will stop acknowledging.
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_DATA_CMD_t, uint32_t)
        // Indicates the first data byte received after the address phase for receive transfer in Master receiver or Slave receiver mode.
        // 
        // Reset value : 0x0
        // 
        // NOTE:  In case of APB_DATA_WIDTH=8,
        // 
        // 1. The user has to perform two APB Reads to IC_DATA_CMD in order to get status on 11 bit.
        // 
        // 2. In order to read the 11 bit, the user has to perform the first data byte read [7:0] (offset 0x10) and then perform the second read [15:8] (offset 0x11) in order to know the status of 11 bit (whether the data received in previous read is a first data byte or not).
        // 
        // 3. The 11th bit is an optional read field, user can ignore 2nd byte read [15:8] (offset 0x11) if not interested in FIRST_DATA_BYTE status.
        ADD_BITFIELD_RO(FIRST_DATA_BYTE, 11, 1)
        // This bit controls whether a RESTART is issued before the byte is sent or received.
        // 
        // 1 - If IC_RESTART_EN is 1, a RESTART is issued before the data is sent/received (according to the value of CMD), regardless of whether or not the transfer direction is changing from the previous command; if IC_RESTART_EN is 0, a STOP followed by a START is issued instead.
        // 
        // 0 - If IC_RESTART_EN is 1, a RESTART is issued only if the transfer direction is changing from the previous command; if IC_RESTART_EN is 0, a STOP followed by a START is issued instead.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RW(RESTART, 10, 1)
        // This bit controls whether a STOP is issued after the byte is sent or received.
        // 
        // - 1 - STOP is issued after this byte, regardless of whether or not the Tx FIFO is empty. If the Tx FIFO is not empty, the master immediately tries to start a new transfer by issuing a START and arbitrating for the bus. - 0 - STOP is not issued after this byte, regardless of whether or not the Tx FIFO is empty. If the Tx FIFO is not empty, the master continues the current transfer by sending/receiving data bytes according to the value of the CMD bit. If the Tx FIFO is empty, the master holds the SCL line low and stalls the bus until a new command is available in the Tx FIFO. Reset value: 0x0
        ADD_BITFIELD_RW(STOP, 9, 1)
        // This bit controls whether a read or a write is performed. This bit does not control the direction when the DW_apb_i2con acts as a slave. It controls only the direction when it acts as a master.
        // 
        // When a command is entered in the TX FIFO, this bit distinguishes the write and read commands. In slave-receiver mode, this bit is a 'don't care' because writes to this register are not required. In slave-transmitter mode, a '0' indicates that the data in IC_DATA_CMD is to be transmitted.
        // 
        // When programming this bit, you should remember the following: attempting to perform a read operation after a General Call command has been sent results in a TX_ABRT interrupt (bit 6 of the IC_RAW_INTR_STAT register), unless bit 11 (SPECIAL) in the IC_TAR register has been cleared. If a '1' is written to this bit after receiving a RD_REQ interrupt, then a TX_ABRT interrupt occurs.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RW(CMD, 8, 1)
        // This register contains the data to be transmitted or received on the I2C bus. If you are writing to this register and want to perform a read, bits 7:0 (DAT) are ignored by the DW_apb_i2c. However, when you read this register, these bits return the value of data received on the DW_apb_i2c interface.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RW(DAT, 0, 8)
    END_TYPE()

    // Sequential data byte received
    static const uint32_t IC_DATA_CMD_FIRST_DATA_BYTE__INACTIVE = 0;
    // Non sequential data byte received
    static const uint32_t IC_DATA_CMD_FIRST_DATA_BYTE__ACTIVE = 1;
    // Don't Issue RESTART before this command
    static const uint32_t IC_DATA_CMD_RESTART__DISABLE = 0;
    // Issue RESTART before this command
    static const uint32_t IC_DATA_CMD_RESTART__ENABLE = 1;
    // Don't Issue STOP after this command
    static const uint32_t IC_DATA_CMD_STOP__DISABLE = 0;
    // Issue STOP after this command
    static const uint32_t IC_DATA_CMD_STOP__ENABLE = 1;
    // Master Write Command
    static const uint32_t IC_DATA_CMD_CMD__WRITE = 0;
    // Master Read Command
    static const uint32_t IC_DATA_CMD_CMD__READ = 1;

    // Standard Speed I2C Clock SCL High Count Register
    // Reset value: 0x00000028
    BEGIN_TYPE(IC_SS_SCL_HCNT_t, uint32_t)
        // This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock high-period count for standard speed. For more information, refer to 'IC_CLK Frequency Configuration'.
        // 
        // This register can be written only when the I2C interface is disabled which corresponds to the IC_ENABLE[0] register being set to 0. Writes at other times have no effect.
        // 
        // The minimum valid value is 6; hardware prevents values less than this being written, and if attempted results in 6 being set. For designs with APB_DATA_WIDTH = 8, the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first. Then the upper byte is programmed.
        // 
        // NOTE: This register must not be programmed to a value higher than 65525, because DW_apb_i2c uses a 16-bit counter to flag an I2C bus idle condition when this counter reaches a value of IC_SS_SCL_HCNT + 10.
        ADD_BITFIELD_RW(IC_SS_SCL_HCNT, 0, 16)
    END_TYPE()

    // Standard Speed I2C Clock SCL Low Count Register
    // Reset value: 0x0000002f
    BEGIN_TYPE(IC_SS_SCL_LCNT_t, uint32_t)
        // This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock low period count for standard speed. For more information, refer to 'IC_CLK Frequency Configuration'
        // 
        // This register can be written only when the I2C interface is disabled which corresponds to the IC_ENABLE[0] register being set to 0. Writes at other times have no effect.
        // 
        // The minimum valid value is 8; hardware prevents values less than this being written, and if attempted, results in 8 being set. For designs with APB_DATA_WIDTH = 8, the order of programming is important to ensure the correct operation of DW_apb_i2c. The lower byte must be programmed first, and then the upper byte is programmed.
        ADD_BITFIELD_RW(IC_SS_SCL_LCNT, 0, 16)
    END_TYPE()

    // Fast Mode or Fast Mode Plus I2C Clock SCL High Count Register
    // Reset value: 0x00000006
    BEGIN_TYPE(IC_FS_SCL_HCNT_t, uint32_t)
        // This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock high-period count for fast mode or fast mode plus. It is used in high-speed mode to send the Master Code and START BYTE or General CALL. For more information, refer to 'IC_CLK Frequency Configuration'.
        // 
        // This register goes away and becomes read-only returning 0s if IC_MAX_SPEED_MODE = standard. This register can be written only when the I2C interface is disabled, which corresponds to the IC_ENABLE[0] register being set to 0. Writes at other times have no effect.
        // 
        // The minimum valid value is 6; hardware prevents values less than this being written, and if attempted results in 6 being set. For designs with APB_DATA_WIDTH == 8 the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first. Then the upper byte is programmed.
        ADD_BITFIELD_RW(IC_FS_SCL_HCNT, 0, 16)
    END_TYPE()

    // Fast Mode or Fast Mode Plus I2C Clock SCL Low Count Register
    // Reset value: 0x0000000d
    BEGIN_TYPE(IC_FS_SCL_LCNT_t, uint32_t)
        // This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock low period count for fast speed. It is used in high-speed mode to send the Master Code and START BYTE or General CALL. For more information, refer to 'IC_CLK Frequency Configuration'.
        // 
        // This register goes away and becomes read-only returning 0s if IC_MAX_SPEED_MODE = standard.
        // 
        // This register can be written only when the I2C interface is disabled, which corresponds to the IC_ENABLE[0] register being set to 0. Writes at other times have no effect.
        // 
        // The minimum valid value is 8; hardware prevents values less than this being written, and if attempted results in 8 being set. For designs with APB_DATA_WIDTH = 8 the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first. Then the upper byte is programmed. If the value is less than 8 then the count value gets changed to 8.
        ADD_BITFIELD_RW(IC_FS_SCL_LCNT, 0, 16)
    END_TYPE()

    // I2C Interrupt Status Register
    // 
    // Each bit in this register has a corresponding mask bit in the IC_INTR_MASK register. These bits are cleared by reading the matching interrupt clear register. The unmasked raw versions of these bits are available in the IC_RAW_INTR_STAT register.
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_INTR_STAT_t, uint32_t)
        // See IC_RAW_INTR_STAT for a detailed description of R_RESTART_DET bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_RESTART_DET, 12, 1)
        // See IC_RAW_INTR_STAT for a detailed description of R_GEN_CALL bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_GEN_CALL, 11, 1)
        // See IC_RAW_INTR_STAT for a detailed description of R_START_DET bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_START_DET, 10, 1)
        // See IC_RAW_INTR_STAT for a detailed description of R_STOP_DET bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_STOP_DET, 9, 1)
        // See IC_RAW_INTR_STAT for a detailed description of R_ACTIVITY bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_ACTIVITY, 8, 1)
        // See IC_RAW_INTR_STAT for a detailed description of R_RX_DONE bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_RX_DONE, 7, 1)
        // See IC_RAW_INTR_STAT for a detailed description of R_TX_ABRT bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_TX_ABRT, 6, 1)
        // See IC_RAW_INTR_STAT for a detailed description of R_RD_REQ bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_RD_REQ, 5, 1)
        // See IC_RAW_INTR_STAT for a detailed description of R_TX_EMPTY bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_TX_EMPTY, 4, 1)
        // See IC_RAW_INTR_STAT for a detailed description of R_TX_OVER bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_TX_OVER, 3, 1)
        // See IC_RAW_INTR_STAT for a detailed description of R_RX_FULL bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_RX_FULL, 2, 1)
        // See IC_RAW_INTR_STAT for a detailed description of R_RX_OVER bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_RX_OVER, 1, 1)
        // See IC_RAW_INTR_STAT for a detailed description of R_RX_UNDER bit.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(R_RX_UNDER, 0, 1)
    END_TYPE()

    // R_RESTART_DET interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_RESTART_DET__INACTIVE = 0;
    // R_RESTART_DET interrupt is active
    static const uint32_t IC_INTR_STAT_R_RESTART_DET__ACTIVE = 1;
    // R_GEN_CALL interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_GEN_CALL__INACTIVE = 0;
    // R_GEN_CALL interrupt is active
    static const uint32_t IC_INTR_STAT_R_GEN_CALL__ACTIVE = 1;
    // R_START_DET interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_START_DET__INACTIVE = 0;
    // R_START_DET interrupt is active
    static const uint32_t IC_INTR_STAT_R_START_DET__ACTIVE = 1;
    // R_STOP_DET interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_STOP_DET__INACTIVE = 0;
    // R_STOP_DET interrupt is active
    static const uint32_t IC_INTR_STAT_R_STOP_DET__ACTIVE = 1;
    // R_ACTIVITY interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_ACTIVITY__INACTIVE = 0;
    // R_ACTIVITY interrupt is active
    static const uint32_t IC_INTR_STAT_R_ACTIVITY__ACTIVE = 1;
    // R_RX_DONE interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_RX_DONE__INACTIVE = 0;
    // R_RX_DONE interrupt is active
    static const uint32_t IC_INTR_STAT_R_RX_DONE__ACTIVE = 1;
    // R_TX_ABRT interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_TX_ABRT__INACTIVE = 0;
    // R_TX_ABRT interrupt is active
    static const uint32_t IC_INTR_STAT_R_TX_ABRT__ACTIVE = 1;
    // R_RD_REQ interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_RD_REQ__INACTIVE = 0;
    // R_RD_REQ interrupt is active
    static const uint32_t IC_INTR_STAT_R_RD_REQ__ACTIVE = 1;
    // R_TX_EMPTY interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_TX_EMPTY__INACTIVE = 0;
    // R_TX_EMPTY interrupt is active
    static const uint32_t IC_INTR_STAT_R_TX_EMPTY__ACTIVE = 1;
    // R_TX_OVER interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_TX_OVER__INACTIVE = 0;
    // R_TX_OVER interrupt is active
    static const uint32_t IC_INTR_STAT_R_TX_OVER__ACTIVE = 1;
    // R_RX_FULL interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_RX_FULL__INACTIVE = 0;
    // R_RX_FULL interrupt is active
    static const uint32_t IC_INTR_STAT_R_RX_FULL__ACTIVE = 1;
    // R_RX_OVER interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_RX_OVER__INACTIVE = 0;
    // R_RX_OVER interrupt is active
    static const uint32_t IC_INTR_STAT_R_RX_OVER__ACTIVE = 1;
    // RX_UNDER interrupt is inactive
    static const uint32_t IC_INTR_STAT_R_RX_UNDER__INACTIVE = 0;
    // RX_UNDER interrupt is active
    static const uint32_t IC_INTR_STAT_R_RX_UNDER__ACTIVE = 1;

    // I2C Interrupt Mask Register.
    // 
    // These bits mask their corresponding interrupt status bits. This register is active low; a value of 0 masks the interrupt, whereas a value of 1 unmasks the interrupt.
    // Reset value: 0x000008ff
    BEGIN_TYPE(IC_INTR_MASK_t, uint32_t)
        // This bit masks the R_RESTART_DET interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RW(M_RESTART_DET, 12, 1)
        // This bit masks the R_GEN_CALL interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x1
        ADD_BITFIELD_RW(M_GEN_CALL, 11, 1)
        // This bit masks the R_START_DET interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RW(M_START_DET, 10, 1)
        // This bit masks the R_STOP_DET interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RW(M_STOP_DET, 9, 1)
        // This bit masks the R_ACTIVITY interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RW(M_ACTIVITY, 8, 1)
        // This bit masks the R_RX_DONE interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x1
        ADD_BITFIELD_RW(M_RX_DONE, 7, 1)
        // This bit masks the R_TX_ABRT interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x1
        ADD_BITFIELD_RW(M_TX_ABRT, 6, 1)
        // This bit masks the R_RD_REQ interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x1
        ADD_BITFIELD_RW(M_RD_REQ, 5, 1)
        // This bit masks the R_TX_EMPTY interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x1
        ADD_BITFIELD_RW(M_TX_EMPTY, 4, 1)
        // This bit masks the R_TX_OVER interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x1
        ADD_BITFIELD_RW(M_TX_OVER, 3, 1)
        // This bit masks the R_RX_FULL interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x1
        ADD_BITFIELD_RW(M_RX_FULL, 2, 1)
        // This bit masks the R_RX_OVER interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x1
        ADD_BITFIELD_RW(M_RX_OVER, 1, 1)
        // This bit masks the R_RX_UNDER interrupt in IC_INTR_STAT register.
        // 
        // Reset value: 0x1
        ADD_BITFIELD_RW(M_RX_UNDER, 0, 1)
    END_TYPE()

    // RESTART_DET interrupt is masked
    static const uint32_t IC_INTR_MASK_M_RESTART_DET__ENABLED = 0;
    // RESTART_DET interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_RESTART_DET__DISABLED = 1;
    // GEN_CALL interrupt is masked
    static const uint32_t IC_INTR_MASK_M_GEN_CALL__ENABLED = 0;
    // GEN_CALL interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_GEN_CALL__DISABLED = 1;
    // START_DET interrupt is masked
    static const uint32_t IC_INTR_MASK_M_START_DET__ENABLED = 0;
    // START_DET interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_START_DET__DISABLED = 1;
    // STOP_DET interrupt is masked
    static const uint32_t IC_INTR_MASK_M_STOP_DET__ENABLED = 0;
    // STOP_DET interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_STOP_DET__DISABLED = 1;
    // ACTIVITY interrupt is masked
    static const uint32_t IC_INTR_MASK_M_ACTIVITY__ENABLED = 0;
    // ACTIVITY interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_ACTIVITY__DISABLED = 1;
    // RX_DONE interrupt is masked
    static const uint32_t IC_INTR_MASK_M_RX_DONE__ENABLED = 0;
    // RX_DONE interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_RX_DONE__DISABLED = 1;
    // TX_ABORT interrupt is masked
    static const uint32_t IC_INTR_MASK_M_TX_ABRT__ENABLED = 0;
    // TX_ABORT interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_TX_ABRT__DISABLED = 1;
    // RD_REQ interrupt is masked
    static const uint32_t IC_INTR_MASK_M_RD_REQ__ENABLED = 0;
    // RD_REQ interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_RD_REQ__DISABLED = 1;
    // TX_EMPTY interrupt is masked
    static const uint32_t IC_INTR_MASK_M_TX_EMPTY__ENABLED = 0;
    // TX_EMPTY interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_TX_EMPTY__DISABLED = 1;
    // TX_OVER interrupt is masked
    static const uint32_t IC_INTR_MASK_M_TX_OVER__ENABLED = 0;
    // TX_OVER interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_TX_OVER__DISABLED = 1;
    // RX_FULL interrupt is masked
    static const uint32_t IC_INTR_MASK_M_RX_FULL__ENABLED = 0;
    // RX_FULL interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_RX_FULL__DISABLED = 1;
    // RX_OVER interrupt is masked
    static const uint32_t IC_INTR_MASK_M_RX_OVER__ENABLED = 0;
    // RX_OVER interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_RX_OVER__DISABLED = 1;
    // RX_UNDER interrupt is masked
    static const uint32_t IC_INTR_MASK_M_RX_UNDER__ENABLED = 0;
    // RX_UNDER interrupt is unmasked
    static const uint32_t IC_INTR_MASK_M_RX_UNDER__DISABLED = 1;

    // I2C Raw Interrupt Status Register
    // 
    // Unlike the IC_INTR_STAT register, these bits are not masked so they always show the true status of the DW_apb_i2c.
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_RAW_INTR_STAT_t, uint32_t)
        // Indicates whether a RESTART condition has occurred on the I2C interface when DW_apb_i2c is operating in Slave mode and the slave is being addressed. Enabled only when IC_SLV_RESTART_DET_EN=1.
        // 
        // Note: However, in high-speed mode or during a START BYTE transfer, the RESTART comes before the address field as per the I2C protocol. In this case, the slave is not the addressed slave when the RESTART is issued, therefore DW_apb_i2c does not generate the RESTART_DET interrupt.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(RESTART_DET, 12, 1)
        // Set only when a General Call address is received and it is acknowledged. It stays set until it is cleared either by disabling DW_apb_i2c or when the CPU reads bit 0 of the IC_CLR_GEN_CALL register. DW_apb_i2c stores the received data in the Rx buffer.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(GEN_CALL, 11, 1)
        // Indicates whether a START or RESTART condition has occurred on the I2C interface regardless of whether DW_apb_i2c is operating in slave or master mode.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(START_DET, 10, 1)
        // Indicates whether a STOP condition has occurred on the I2C interface regardless of whether DW_apb_i2c is operating in slave or master mode.
        // 
        // In Slave Mode: - If IC_CON[7]=1'b1  (STOP_DET_IFADDRESSED), the STOP_DET interrupt will be issued only if slave is addressed. Note: During a general call address, this slave does not issue a STOP_DET interrupt if STOP_DET_IF_ADDRESSED=1'b1, even if the slave responds to the general call address by generating ACK. The STOP_DET interrupt is generated only when the transmitted address matches the slave address (SAR). - If IC_CON[7]=1'b0 (STOP_DET_IFADDRESSED), the STOP_DET interrupt is issued irrespective of whether it is being addressed. In Master Mode: - If IC_CON[10]=1'b1  (STOP_DET_IF_MASTER_ACTIVE),the STOP_DET interrupt will be issued only if Master is active. - If IC_CON[10]=1'b0  (STOP_DET_IFADDRESSED),the STOP_DET interrupt will be issued irrespective of whether master is active or not. Reset value: 0x0
        ADD_BITFIELD_RO(STOP_DET, 9, 1)
        // This bit captures DW_apb_i2c activity and stays set until it is cleared. There are four ways to clear it: - Disabling the DW_apb_i2c - Reading the IC_CLR_ACTIVITY register - Reading the IC_CLR_INTR register - System reset Once this bit is set, it stays set unless one of the four methods is used to clear it. Even if the DW_apb_i2c module is idle, this bit remains set until cleared, indicating that there was activity on the bus.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(ACTIVITY, 8, 1)
        // When the DW_apb_i2c is acting as a slave-transmitter, this bit is set to 1 if the master does not acknowledge a transmitted byte. This occurs on the last byte of the transmission, indicating that the transmission is done.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(RX_DONE, 7, 1)
        // This bit indicates if DW_apb_i2c, as an I2C transmitter, is unable to complete the intended actions on the contents of the transmit FIFO. This situation can occur both as an I2C master or an I2C slave, and is referred to as a 'transmit abort'. When this bit is set to 1, the IC_TX_ABRT_SOURCE register indicates the reason why the transmit abort takes places.
        // 
        // Note:  The DW_apb_i2c flushes/resets/empties the TX_FIFO and RX_FIFO whenever there is a transmit abort caused by any of the events tracked by the IC_TX_ABRT_SOURCE register. The FIFOs remains in this flushed state until the register IC_CLR_TX_ABRT is read. Once this read is performed, the Tx FIFO is then ready to accept more data bytes from the APB interface.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(TX_ABRT, 6, 1)
        // This bit is set to 1 when DW_apb_i2c is acting as a slave and another I2C master is attempting to read data from DW_apb_i2c. The DW_apb_i2c holds the I2C bus in a wait state (SCL=0) until this interrupt is serviced, which means that the slave has been addressed by a remote master that is asking for data to be transferred. The processor must respond to this interrupt and then write the requested data to the IC_DATA_CMD register. This bit is set to 0 just after the processor reads the IC_CLR_RD_REQ register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(RD_REQ, 5, 1)
        // The behavior of the TX_EMPTY interrupt status differs based on the TX_EMPTY_CTRL selection in the IC_CON register. - When TX_EMPTY_CTRL = 0: This bit is set to 1 when the transmit buffer is at or below the threshold value set in the IC_TX_TL register. - When TX_EMPTY_CTRL = 1: This bit is set to 1 when the transmit buffer is at or below the threshold value set in the IC_TX_TL register and the transmission of the address/data from the internal shift register for the most recently popped command is completed. It is automatically cleared by hardware when the buffer level goes above the threshold. When IC_ENABLE[0] is set to 0, the TX FIFO is flushed and held in reset. There the TX FIFO looks like it has no data within it, so this bit is set to 1, provided there is activity in the master or slave state machines. When there is no longer any activity, then with ic_en=0, this bit is set to 0.
        // 
        // Reset value: 0x0.
        ADD_BITFIELD_RO(TX_EMPTY, 4, 1)
        // Set during transmit if the transmit buffer is filled to IC_TX_BUFFER_DEPTH and the processor attempts to issue another I2C command by writing to the IC_DATA_CMD register. When the module is disabled, this bit keeps its level until the master or slave state machines go into idle, and when ic_en goes to 0, this interrupt is cleared.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(TX_OVER, 3, 1)
        // Set when the receive buffer reaches or goes above the RX_TL threshold in the IC_RX_TL register. It is automatically cleared by hardware when buffer level goes below the threshold. If the module is disabled (IC_ENABLE[0]=0), the RX FIFO is flushed and held in reset; therefore the RX FIFO is not full. So this bit is cleared once the IC_ENABLE bit 0 is programmed with a 0, regardless of the activity that continues.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(RX_FULL, 2, 1)
        // Set if the receive buffer is completely filled to IC_RX_BUFFER_DEPTH and an additional byte is received from an external I2C device. The DW_apb_i2c acknowledges this, but any data bytes received after the FIFO is full are lost. If the module is disabled (IC_ENABLE[0]=0), this bit keeps its level until the master or slave state machines go into idle, and when ic_en goes to 0, this interrupt is cleared.
        // 
        // Note:  If bit 9 of the IC_CON register (RX_FIFO_FULL_HLD_CTRL) is programmed to HIGH, then the RX_OVER interrupt never occurs, because the Rx FIFO never overflows.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(RX_OVER, 1, 1)
        // Set if the processor attempts to read the receive buffer when it is empty by reading from the IC_DATA_CMD register. If the module is disabled (IC_ENABLE[0]=0), this bit keeps its level until the master or slave state machines go into idle, and when ic_en goes to 0, this interrupt is cleared.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(RX_UNDER, 0, 1)
    END_TYPE()

    // RESTART_DET interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_RESTART_DET__INACTIVE = 0;
    // RESTART_DET interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_RESTART_DET__ACTIVE = 1;
    // GEN_CALL interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_GEN_CALL__INACTIVE = 0;
    // GEN_CALL interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_GEN_CALL__ACTIVE = 1;
    // START_DET interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_START_DET__INACTIVE = 0;
    // START_DET interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_START_DET__ACTIVE = 1;
    // STOP_DET interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_STOP_DET__INACTIVE = 0;
    // STOP_DET interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_STOP_DET__ACTIVE = 1;
    // RAW_INTR_ACTIVITY interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_ACTIVITY__INACTIVE = 0;
    // RAW_INTR_ACTIVITY interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_ACTIVITY__ACTIVE = 1;
    // RX_DONE interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_RX_DONE__INACTIVE = 0;
    // RX_DONE interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_RX_DONE__ACTIVE = 1;
    // TX_ABRT interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_TX_ABRT__INACTIVE = 0;
    // TX_ABRT interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_TX_ABRT__ACTIVE = 1;
    // RD_REQ interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_RD_REQ__INACTIVE = 0;
    // RD_REQ interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_RD_REQ__ACTIVE = 1;
    // TX_EMPTY interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_TX_EMPTY__INACTIVE = 0;
    // TX_EMPTY interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_TX_EMPTY__ACTIVE = 1;
    // TX_OVER interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_TX_OVER__INACTIVE = 0;
    // TX_OVER interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_TX_OVER__ACTIVE = 1;
    // RX_FULL interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_RX_FULL__INACTIVE = 0;
    // RX_FULL interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_RX_FULL__ACTIVE = 1;
    // RX_OVER interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_RX_OVER__INACTIVE = 0;
    // RX_OVER interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_RX_OVER__ACTIVE = 1;
    // RX_UNDER interrupt is inactive
    static const uint32_t IC_RAW_INTR_STAT_RX_UNDER__INACTIVE = 0;
    // RX_UNDER interrupt is active
    static const uint32_t IC_RAW_INTR_STAT_RX_UNDER__ACTIVE = 1;

    // I2C Receive FIFO Threshold Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_RX_TL_t, uint32_t)
        // Receive FIFO Threshold Level.
        // 
        // Controls the level of entries (or above) that triggers the RX_FULL interrupt (bit 2 in IC_RAW_INTR_STAT register). The valid range is 0-255, with the additional restriction that hardware does not allow this value to be set to a value larger than the depth of the buffer. If an attempt is made to do that, the actual value set will be the maximum depth of the buffer. A value of 0 sets the threshold for 1 entry, and a value of 255 sets the threshold for 256 entries.
        ADD_BITFIELD_RW(RX_TL, 0, 8)
    END_TYPE()

    // I2C Transmit FIFO Threshold Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_TX_TL_t, uint32_t)
        // Transmit FIFO Threshold Level.
        // 
        // Controls the level of entries (or below) that trigger the TX_EMPTY interrupt (bit 4 in IC_RAW_INTR_STAT register). The valid range is 0-255, with the additional restriction that it may not be set to value larger than the depth of the buffer. If an attempt is made to do that, the actual value set will be the maximum depth of the buffer. A value of 0 sets the threshold for 0 entries, and a value of 255 sets the threshold for 255 entries.
        ADD_BITFIELD_RW(TX_TL, 0, 8)
    END_TYPE()

    // Clear Combined and Individual Interrupt Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_CLR_INTR_t, uint32_t)
        // Read this register to clear the combined interrupt, all individual interrupts, and the IC_TX_ABRT_SOURCE register. This bit does not clear hardware clearable interrupts but software clearable interrupts. Refer to Bit 9 of the IC_TX_ABRT_SOURCE register for an exception to clearing IC_TX_ABRT_SOURCE.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(CLR_INTR, 0, 1)
    END_TYPE()

    // Clear RX_UNDER Interrupt Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_CLR_RX_UNDER_t, uint32_t)
        // Read this register to clear the RX_UNDER interrupt (bit 0) of the IC_RAW_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(CLR_RX_UNDER, 0, 1)
    END_TYPE()

    // Clear RX_OVER Interrupt Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_CLR_RX_OVER_t, uint32_t)
        // Read this register to clear the RX_OVER interrupt (bit 1) of the IC_RAW_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(CLR_RX_OVER, 0, 1)
    END_TYPE()

    // Clear TX_OVER Interrupt Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_CLR_TX_OVER_t, uint32_t)
        // Read this register to clear the TX_OVER interrupt (bit 3) of the IC_RAW_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(CLR_TX_OVER, 0, 1)
    END_TYPE()

    // Clear RD_REQ Interrupt Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_CLR_RD_REQ_t, uint32_t)
        // Read this register to clear the RD_REQ interrupt (bit 5) of the IC_RAW_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(CLR_RD_REQ, 0, 1)
    END_TYPE()

    // Clear TX_ABRT Interrupt Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_CLR_TX_ABRT_t, uint32_t)
        // Read this register to clear the TX_ABRT interrupt (bit 6) of the IC_RAW_INTR_STAT register, and the IC_TX_ABRT_SOURCE register. This also releases the TX FIFO from the flushed/reset state, allowing more writes to the TX FIFO. Refer to Bit 9 of the IC_TX_ABRT_SOURCE register for an exception to clearing IC_TX_ABRT_SOURCE.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(CLR_TX_ABRT, 0, 1)
    END_TYPE()

    // Clear RX_DONE Interrupt Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_CLR_RX_DONE_t, uint32_t)
        // Read this register to clear the RX_DONE interrupt (bit 7) of the IC_RAW_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(CLR_RX_DONE, 0, 1)
    END_TYPE()

    // Clear ACTIVITY Interrupt Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_CLR_ACTIVITY_t, uint32_t)
        // Reading this register clears the ACTIVITY interrupt if the I2C is not active anymore. If the I2C module is still active on the bus, the ACTIVITY interrupt bit continues to be set. It is automatically cleared by hardware if the module is disabled and if there is no further activity on the bus. The value read from this register to get status of the ACTIVITY interrupt (bit 8) of the IC_RAW_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(CLR_ACTIVITY, 0, 1)
    END_TYPE()

    // Clear STOP_DET Interrupt Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_CLR_STOP_DET_t, uint32_t)
        // Read this register to clear the STOP_DET interrupt (bit 9) of the IC_RAW_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(CLR_STOP_DET, 0, 1)
    END_TYPE()

    // Clear START_DET Interrupt Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_CLR_START_DET_t, uint32_t)
        // Read this register to clear the START_DET interrupt (bit 10) of the IC_RAW_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(CLR_START_DET, 0, 1)
    END_TYPE()

    // Clear GEN_CALL Interrupt Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_CLR_GEN_CALL_t, uint32_t)
        // Read this register to clear the GEN_CALL interrupt (bit 11) of IC_RAW_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(CLR_GEN_CALL, 0, 1)
    END_TYPE()

    // I2C Enable Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_ENABLE_t, uint32_t)
        // In Master mode: - 1'b1: Blocks the transmission of data on I2C bus even if Tx FIFO has data to transmit. - 1'b0: The transmission of data starts on I2C bus automatically, as soon as the first data is available in the Tx FIFO. Note: To block the execution of Master commands, set the TX_CMD_BLOCK bit only when Tx FIFO is empty (IC_STATUS[2]==1) and Master is in Idle state (IC_STATUS[5] == 0). Any further commands put in the Tx FIFO are not executed until TX_CMD_BLOCK bit is unset. Reset value:  IC_TX_CMD_BLOCK_DEFAULT
        ADD_BITFIELD_RW(TX_CMD_BLOCK, 2, 1)
        // When set, the controller initiates the transfer abort. - 0: ABORT not initiated or ABORT done - 1: ABORT operation in progress The software can abort the I2C transfer in master mode by setting this bit. The software can set this bit only when ENABLE is already set; otherwise, the controller ignores any write to ABORT bit. The software cannot clear the ABORT bit once set. In response to an ABORT, the controller issues a STOP and flushes the Tx FIFO after completing the current transfer, then sets the TX_ABORT interrupt after the abort operation. The ABORT bit is cleared automatically after the abort operation.
        // 
        // For a detailed description on how to abort I2C transfers, refer to 'Aborting I2C Transfers'.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RW(ABORT, 1, 1)
        // Controls whether the DW_apb_i2c is enabled. - 0: Disables DW_apb_i2c (TX and RX FIFOs are held in an erased state) - 1: Enables DW_apb_i2c Software can disable DW_apb_i2c while it is active. However, it is important that care be taken to ensure that DW_apb_i2c is disabled properly. A recommended procedure is described in 'Disabling DW_apb_i2c'.
        // 
        // When DW_apb_i2c is disabled, the following occurs: - The TX FIFO and RX FIFO get flushed. - Status bits in the IC_INTR_STAT register are still active until DW_apb_i2c goes into IDLE state. If the module is transmitting, it stops as well as deletes the contents of the transmit buffer after the current transfer is complete. If the module is receiving, the DW_apb_i2c stops the current transfer at the end of the current byte and does not acknowledge the transfer.
        // 
        // In systems with asynchronous pclk and ic_clk when IC_CLK_TYPE parameter set to asynchronous (1), there is a two ic_clk delay when enabling or disabling the DW_apb_i2c. For a detailed description on how to disable DW_apb_i2c, refer to 'Disabling DW_apb_i2c'
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RW(ENABLE, 0, 1)
    END_TYPE()

    // Tx Command execution not blocked
    static const uint32_t IC_ENABLE_TX_CMD_BLOCK__NOT_BLOCKED = 0;
    // Tx Command execution blocked
    static const uint32_t IC_ENABLE_TX_CMD_BLOCK__BLOCKED = 1;
    // ABORT operation not in progress
    static const uint32_t IC_ENABLE_ABORT__DISABLE = 0;
    // ABORT operation in progress
    static const uint32_t IC_ENABLE_ABORT__ENABLED = 1;
    // I2C is disabled
    static const uint32_t IC_ENABLE_ENABLE__DISABLED = 0;
    // I2C is enabled
    static const uint32_t IC_ENABLE_ENABLE__ENABLED = 1;

    // I2C Status Register
    // 
    // This is a read-only register used to indicate the current transfer status and FIFO status. The status register may be read at any time. None of the bits in this register request an interrupt.
    // 
    // When the I2C is disabled by writing 0 in bit 0 of the IC_ENABLE register: - Bits 1 and 2 are set to 1 - Bits 3 and 10 are set to 0 When the master or slave state machines goes to idle and ic_en=0: - Bits 5 and 6 are set to 0
    // Reset value: 0x00000006
    BEGIN_TYPE(IC_STATUS_t, uint32_t)
        // Slave FSM Activity Status. When the Slave Finite State Machine (FSM) is not in the IDLE state, this bit is set. - 0: Slave FSM is in IDLE state so the Slave part of DW_apb_i2c is not Active - 1: Slave FSM is not in IDLE state so the Slave part of DW_apb_i2c is Active Reset value: 0x0
        ADD_BITFIELD_RO(SLV_ACTIVITY, 6, 1)
        // Master FSM Activity Status. When the Master Finite State Machine (FSM) is not in the IDLE state, this bit is set. - 0: Master FSM is in IDLE state so the Master part of DW_apb_i2c is not Active - 1: Master FSM is not in IDLE state so the Master part of DW_apb_i2c is Active Note: IC_STATUS[0]-that is, ACTIVITY bit-is the OR of SLV_ACTIVITY and MST_ACTIVITY bits.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(MST_ACTIVITY, 5, 1)
        // Receive FIFO Completely Full. When the receive FIFO is completely full, this bit is set. When the receive FIFO contains one or more empty location, this bit is cleared. - 0: Receive FIFO is not full - 1: Receive FIFO is full Reset value: 0x0
        ADD_BITFIELD_RO(RFF, 4, 1)
        // Receive FIFO Not Empty. This bit is set when the receive FIFO contains one or more entries; it is cleared when the receive FIFO is empty. - 0: Receive FIFO is empty - 1: Receive FIFO is not empty Reset value: 0x0
        ADD_BITFIELD_RO(RFNE, 3, 1)
        // Transmit FIFO Completely Empty. When the transmit FIFO is completely empty, this bit is set. When it contains one or more valid entries, this bit is cleared. This bit field does not request an interrupt. - 0: Transmit FIFO is not empty - 1: Transmit FIFO is empty Reset value: 0x1
        ADD_BITFIELD_RO(TFE, 2, 1)
        // Transmit FIFO Not Full. Set when the transmit FIFO contains one or more empty locations, and is cleared when the FIFO is full. - 0: Transmit FIFO is full - 1: Transmit FIFO is not full Reset value: 0x1
        ADD_BITFIELD_RO(TFNF, 1, 1)
        // I2C Activity Status. Reset value: 0x0
        ADD_BITFIELD_RO(ACTIVITY, 0, 1)
    END_TYPE()

    // Slave is idle
    static const uint32_t IC_STATUS_SLV_ACTIVITY__IDLE = 0;
    // Slave not idle
    static const uint32_t IC_STATUS_SLV_ACTIVITY__ACTIVE = 1;
    // Master is idle
    static const uint32_t IC_STATUS_MST_ACTIVITY__IDLE = 0;
    // Master not idle
    static const uint32_t IC_STATUS_MST_ACTIVITY__ACTIVE = 1;
    // Rx FIFO not full
    static const uint32_t IC_STATUS_RFF__NOT_FULL = 0;
    // Rx FIFO is full
    static const uint32_t IC_STATUS_RFF__FULL = 1;
    // Rx FIFO is empty
    static const uint32_t IC_STATUS_RFNE__EMPTY = 0;
    // Rx FIFO not empty
    static const uint32_t IC_STATUS_RFNE__NOT_EMPTY = 1;
    // Tx FIFO not empty
    static const uint32_t IC_STATUS_TFE__NON_EMPTY = 0;
    // Tx FIFO is empty
    static const uint32_t IC_STATUS_TFE__EMPTY = 1;
    // Tx FIFO is full
    static const uint32_t IC_STATUS_TFNF__FULL = 0;
    // Tx FIFO not full
    static const uint32_t IC_STATUS_TFNF__NOT_FULL = 1;
    // I2C is idle
    static const uint32_t IC_STATUS_ACTIVITY__INACTIVE = 0;
    // I2C is active
    static const uint32_t IC_STATUS_ACTIVITY__ACTIVE = 1;

    // I2C Transmit FIFO Level Register This register contains the number of valid data entries in the transmit FIFO buffer. It is cleared whenever: - The I2C is disabled - There is a transmit abort - that is, TX_ABRT bit is set in the IC_RAW_INTR_STAT register - The slave bulk transmit mode is aborted The register increments whenever data is placed into the transmit FIFO and decrements when data is taken from the transmit FIFO.
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_TXFLR_t, uint32_t)
        // Transmit FIFO Level. Contains the number of valid data entries in the transmit FIFO.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(TXFLR, 0, 5)
    END_TYPE()

    // I2C Receive FIFO Level Register This register contains the number of valid data entries in the receive FIFO buffer. It is cleared whenever: - The I2C is disabled - Whenever there is a transmit abort caused by any of the events tracked in IC_TX_ABRT_SOURCE The register increments whenever data is placed into the receive FIFO and decrements when data is taken from the receive FIFO.
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_RXFLR_t, uint32_t)
        // Receive FIFO Level. Contains the number of valid data entries in the receive FIFO.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(RXFLR, 0, 5)
    END_TYPE()

    // I2C SDA Hold Time Length Register
    // 
    // The bits [15:0] of this register are used to control the hold time of SDA during transmit in both slave and master mode (after SCL goes from HIGH to LOW).
    // 
    // The bits [23:16] of this register are used to extend the SDA transition (if any) whenever SCL is HIGH in the receiver in either master or slave mode.
    // 
    // Writes to this register succeed only when IC_ENABLE[0]=0.
    // 
    // The values in this register are in units of ic_clk period. The value programmed in IC_SDA_TX_HOLD must be greater than the minimum hold time in each mode (one cycle in master mode, seven cycles in slave mode) for the value to be implemented.
    // 
    // The programmed SDA hold time during transmit (IC_SDA_TX_HOLD) cannot exceed at any time the duration of the low part of scl. Therefore the programmed value cannot be larger than N_SCL_LOW-2, where N_SCL_LOW is the duration of the low part of the scl period measured in ic_clk cycles.
    // Reset value: 0x00000001
    BEGIN_TYPE(IC_SDA_HOLD_t, uint32_t)
        // Sets the required SDA hold time in units of ic_clk period, when DW_apb_i2c acts as a receiver.
        // 
        // Reset value: IC_DEFAULT_SDA_HOLD[23:16].
        ADD_BITFIELD_RW(IC_SDA_RX_HOLD, 16, 8)
        // Sets the required SDA hold time in units of ic_clk period, when DW_apb_i2c acts as a transmitter.
        // 
        // Reset value: IC_DEFAULT_SDA_HOLD[15:0].
        ADD_BITFIELD_RW(IC_SDA_TX_HOLD, 0, 16)
    END_TYPE()

    // I2C Transmit Abort Source Register
    // 
    // This register has 32 bits that indicate the source of the TX_ABRT bit. Except for Bit 9, this register is cleared whenever the IC_CLR_TX_ABRT register or the IC_CLR_INTR register is read. To clear Bit 9, the source of the ABRT_SBYTE_NORSTRT must be fixed first; RESTART must be enabled (IC_CON[5]=1), the SPECIAL bit must be cleared (IC_TAR[11]), or the GC_OR_START bit must be cleared (IC_TAR[10]).
    // 
    // Once the source of the ABRT_SBYTE_NORSTRT is fixed, then this bit can be cleared in the same manner as other bits in this register. If the source of the ABRT_SBYTE_NORSTRT is not fixed before attempting to clear this bit, Bit 9 clears for one cycle and is then re-asserted.
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_TX_ABRT_SOURCE_t, uint32_t)
        // This field indicates the number of Tx FIFO Data Commands which are flushed due to TX_ABRT interrupt. It is cleared whenever I2C is disabled.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master-Transmitter or Slave-Transmitter
        ADD_BITFIELD_RO(TX_FLUSH_CNT, 23, 9)
        // This is a master-mode-only bit. Master has detected the transfer abort (IC_ENABLE[1])
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master-Transmitter
        ADD_BITFIELD_RO(ABRT_USER_ABRT, 16, 1)
        // 1: When the processor side responds to a slave mode request for data to be transmitted to a remote master and user writes a 1 in CMD (bit 8) of IC_DATA_CMD register.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Slave-Transmitter
        ADD_BITFIELD_RO(ABRT_SLVRD_INTX, 15, 1)
        // This field indicates that a Slave has lost the bus while transmitting data to a remote master. IC_TX_ABRT_SOURCE[12] is set at the same time. Note:  Even though the slave never 'owns' the bus, something could go wrong on the bus. This is a fail safe check. For instance, during a data transmission at the low-to-high transition of SCL, if what is on the data bus is not what is supposed to be transmitted, then DW_apb_i2c no longer own the bus.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Slave-Transmitter
        ADD_BITFIELD_RO(ABRT_SLV_ARBLOST, 14, 1)
        // This field specifies that the Slave has received a read command and some data exists in the TX FIFO, so the slave issues a TX_ABRT interrupt to flush old data in TX FIFO.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Slave-Transmitter
        ADD_BITFIELD_RO(ABRT_SLVFLUSH_TXFIFO, 13, 1)
        // This field specifies that the Master has lost arbitration, or if IC_TX_ABRT_SOURCE[14] is also set, then the slave transmitter has lost arbitration.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master-Transmitter or Slave-Transmitter
        ADD_BITFIELD_RO(ARB_LOST, 12, 1)
        // This field indicates that the User tries to initiate a Master operation with the Master mode disabled.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master-Transmitter or Master-Receiver
        ADD_BITFIELD_RO(ABRT_MASTER_DIS, 11, 1)
        // This field indicates that the restart is disabled (IC_RESTART_EN bit (IC_CON[5]) =0) and the master sends a read command in 10-bit addressing mode.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master-Receiver
        ADD_BITFIELD_RO(ABRT_10B_RD_NORSTRT, 10, 1)
        // To clear Bit 9, the source of the ABRT_SBYTE_NORSTRT must be fixed first; restart must be enabled (IC_CON[5]=1), the SPECIAL bit must be cleared (IC_TAR[11]), or the GC_OR_START bit must be cleared (IC_TAR[10]). Once the source of the ABRT_SBYTE_NORSTRT is fixed, then this bit can be cleared in the same manner as other bits in this register. If the source of the ABRT_SBYTE_NORSTRT is not fixed before attempting to clear this bit, bit 9 clears for one cycle and then gets reasserted. When this field is set to 1, the restart is disabled (IC_RESTART_EN bit (IC_CON[5]) =0) and the user is trying to send a START Byte.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master
        ADD_BITFIELD_RO(ABRT_SBYTE_NORSTRT, 9, 1)
        // This field indicates that the restart is disabled (IC_RESTART_EN bit (IC_CON[5]) =0) and the user is trying to use the master to transfer data in High Speed mode.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master-Transmitter or Master-Receiver
        ADD_BITFIELD_RO(ABRT_HS_NORSTRT, 8, 1)
        // This field indicates that the Master has sent a START Byte and the START Byte was acknowledged (wrong behavior).
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master
        ADD_BITFIELD_RO(ABRT_SBYTE_ACKDET, 7, 1)
        // This field indicates that the Master is in High Speed mode and the High Speed Master code was acknowledged (wrong behavior).
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master
        ADD_BITFIELD_RO(ABRT_HS_ACKDET, 6, 1)
        // This field indicates that DW_apb_i2c in the master mode has sent a General Call but the user programmed the byte following the General Call to be a read from the bus (IC_DATA_CMD[9] is set to 1).
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master-Transmitter
        ADD_BITFIELD_RO(ABRT_GCALL_READ, 5, 1)
        // This field indicates that DW_apb_i2c in master mode has sent a General Call and no slave on the bus acknowledged the General Call.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master-Transmitter
        ADD_BITFIELD_RO(ABRT_GCALL_NOACK, 4, 1)
        // This field indicates the master-mode only bit. When the master receives an acknowledgement for the address, but when it sends data byte(s) following the address, it did not receive an acknowledge from the remote slave(s).
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master-Transmitter
        ADD_BITFIELD_RO(ABRT_TXDATA_NOACK, 3, 1)
        // This field indicates that the Master is in 10-bit address mode and that the second address byte of the 10-bit address was not acknowledged by any slave.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master-Transmitter or Master-Receiver
        ADD_BITFIELD_RO(ABRT_10ADDR2_NOACK, 2, 1)
        // This field indicates that the Master is in 10-bit address mode and the first 10-bit address byte was not acknowledged by any slave.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master-Transmitter or Master-Receiver
        ADD_BITFIELD_RO(ABRT_10ADDR1_NOACK, 1, 1)
        // This field indicates that the Master is in 7-bit addressing mode and the address sent was not acknowledged by any slave.
        // 
        // Reset value: 0x0
        // 
        // Role of DW_apb_i2c:  Master-Transmitter or Master-Receiver
        ADD_BITFIELD_RO(ABRT_7B_ADDR_NOACK, 0, 1)
    END_TYPE()

    // Transfer abort detected by master- scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_USER_ABRT__ABRT_USER_ABRT_VOID = 0;
    // Transfer abort detected by master
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_USER_ABRT__ABRT_USER_ABRT_GENERATED = 1;
    // Slave trying to transmit to remote master in read mode- scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_SLVRD_INTX__ABRT_SLVRD_INTX_VOID = 0;
    // Slave trying to transmit to remote master in read mode
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_SLVRD_INTX__ABRT_SLVRD_INTX_GENERATED = 1;
    // Slave lost arbitration to remote master- scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST__ABRT_SLV_ARBLOST_VOID = 0;
    // Slave lost arbitration to remote master
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST__ABRT_SLV_ARBLOST_GENERATED = 1;
    // Slave flushes existing data in TX-FIFO upon getting read command- scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO__ABRT_SLVFLUSH_TXFIFO_VOID = 0;
    // Slave flushes existing data in TX-FIFO upon getting read command
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO__ABRT_SLVFLUSH_TXFIFO_GENERATED = 1;
    // Master or Slave-Transmitter lost arbitration- scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ARB_LOST__ABRT_LOST_VOID = 0;
    // Master or Slave-Transmitter lost arbitration
    static const uint32_t IC_TX_ABRT_SOURCE_ARB_LOST__ABRT_LOST_GENERATED = 1;
    // User initiating master operation when MASTER disabled- scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_MASTER_DIS__ABRT_MASTER_DIS_VOID = 0;
    // User initiating master operation when MASTER disabled
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_MASTER_DIS__ABRT_MASTER_DIS_GENERATED = 1;
    // Master not trying to read in 10Bit addressing mode when RESTART disabled
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT__ABRT_10B_RD_VOID = 0;
    // Master trying to read in 10Bit addressing mode when RESTART disabled
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT__ABRT_10B_RD_GENERATED = 1;
    // User trying to send START byte when RESTART disabled- scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT__ABRT_SBYTE_NORSTRT_VOID = 0;
    // User trying to send START byte when RESTART disabled
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT__ABRT_SBYTE_NORSTRT_GENERATED = 1;
    // User trying to switch Master to HS mode when RESTART disabled- scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_HS_NORSTRT__ABRT_HS_NORSTRT_VOID = 0;
    // User trying to switch Master to HS mode when RESTART disabled
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_HS_NORSTRT__ABRT_HS_NORSTRT_GENERATED = 1;
    // ACK detected for START byte- scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET__ABRT_SBYTE_ACKDET_VOID = 0;
    // ACK detected for START byte
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET__ABRT_SBYTE_ACKDET_GENERATED = 1;
    // HS Master code ACKed in HS Mode- scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_HS_ACKDET__ABRT_HS_ACK_VOID = 0;
    // HS Master code ACKed in HS Mode
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_HS_ACKDET__ABRT_HS_ACK_GENERATED = 1;
    // GCALL is followed by read from bus-scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_GCALL_READ__ABRT_GCALL_READ_VOID = 0;
    // GCALL is followed by read from bus
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_GCALL_READ__ABRT_GCALL_READ_GENERATED = 1;
    // GCALL not ACKed by any slave-scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_GCALL_NOACK__ABRT_GCALL_NOACK_VOID = 0;
    // GCALL not ACKed by any slave
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_GCALL_NOACK__ABRT_GCALL_NOACK_GENERATED = 1;
    // Transmitted data non-ACKed by addressed slave-scenario not present
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK__ABRT_TXDATA_NOACK_VOID = 0;
    // Transmitted data not ACKed by addressed slave
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK__ABRT_TXDATA_NOACK_GENERATED = 1;
    // This abort is not generated
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK__INACTIVE = 0;
    // Byte 2 of 10Bit Address not ACKed by any slave
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK__ACTIVE = 1;
    // This abort is not generated
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK__INACTIVE = 0;
    // Byte 1 of 10Bit Address not ACKed by any slave
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK__ACTIVE = 1;
    // This abort is not generated
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK__INACTIVE = 0;
    // This abort is generated because of NOACK for 7-bit address
    static const uint32_t IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK__ACTIVE = 1;

    // Generate Slave Data NACK Register
    // 
    // The register is used to generate a NACK for the data part of a transfer when DW_apb_i2c is acting as a slave-receiver. This register only exists when the IC_SLV_DATA_NACK_ONLY parameter is set to 1. When this parameter disabled, this register does not exist and writing to the register's address has no effect.
    // 
    // A write can occur on this register if both of the following conditions are met: - DW_apb_i2c is disabled (IC_ENABLE[0] = 0) - Slave part is inactive (IC_STATUS[6] = 0) Note: The IC_STATUS[6] is a register read-back location for the internal slv_activity signal; the user should poll this before writing the ic_slv_data_nack_only bit.
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_SLV_DATA_NACK_ONLY_t, uint32_t)
        // Generate NACK. This NACK generation only occurs when DW_apb_i2c is a slave-receiver. If this register is set to a value of 1, it can only generate a NACK after a data byte is received; hence, the data transfer is aborted and the data received is not pushed to the receive buffer.
        // 
        // When the register is set to a value of 0, it generates NACK/ACK, depending on normal criteria. - 1: generate NACK after data byte received - 0: generate NACK/ACK normally Reset value: 0x0
        ADD_BITFIELD_RW(NACK, 0, 1)
    END_TYPE()

    // Slave receiver generates NACK normally
    static const uint32_t IC_SLV_DATA_NACK_ONLY_NACK__DISABLED = 0;
    // Slave receiver generates NACK upon data reception only
    static const uint32_t IC_SLV_DATA_NACK_ONLY_NACK__ENABLED = 1;

    // DMA Control Register
    // 
    // The register is used to enable the DMA Controller interface operation. There is a separate bit for transmit and receive. This can be programmed regardless of the state of IC_ENABLE.
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_DMA_CR_t, uint32_t)
        // Transmit DMA Enable. This bit enables/disables the transmit FIFO DMA channel. Reset value: 0x0
        ADD_BITFIELD_RW(TDMAE, 1, 1)
        // Receive DMA Enable. This bit enables/disables the receive FIFO DMA channel. Reset value: 0x0
        ADD_BITFIELD_RW(RDMAE, 0, 1)
    END_TYPE()

    // transmit FIFO DMA channel disabled
    static const uint32_t IC_DMA_CR_TDMAE__DISABLED = 0;
    // Transmit FIFO DMA channel enabled
    static const uint32_t IC_DMA_CR_TDMAE__ENABLED = 1;
    // Receive FIFO DMA channel disabled
    static const uint32_t IC_DMA_CR_RDMAE__DISABLED = 0;
    // Receive FIFO DMA channel enabled
    static const uint32_t IC_DMA_CR_RDMAE__ENABLED = 1;

    // DMA Transmit Data Level Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_DMA_TDLR_t, uint32_t)
        // Transmit Data Level. This bit field controls the level at which a DMA request is made by the transmit logic. It is equal to the watermark level; that is, the dma_tx_req signal is generated when the number of valid data entries in the transmit FIFO is equal to or below this field value, and TDMAE = 1.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RW(DMATDL, 0, 4)
    END_TYPE()

    // I2C Receive Data Level Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_DMA_RDLR_t, uint32_t)
        // Receive Data Level. This bit field controls the level at which a DMA request is made by the receive logic. The watermark level = DMARDL+1; that is, dma_rx_req is generated when the number of valid data entries in the receive FIFO is equal to or more than this field value + 1, and RDMAE =1. For instance, when DMARDL is 0, then dma_rx_req is asserted when 1 or more data entries are present in the receive FIFO.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RW(DMARDL, 0, 4)
    END_TYPE()

    // I2C SDA Setup Register
    // 
    // This register controls the amount of time delay (in terms of number of ic_clk clock periods) introduced in the rising edge of SCL - relative to SDA changing - when DW_apb_i2c services a read request in a slave-transmitter operation. The relevant I2C requirement is tSU:DAT (note 4) as detailed in the I2C Bus Specification. This register must be programmed with a value equal to or greater than 2.
    // 
    // Writes to this register succeed only when IC_ENABLE[0] = 0.
    // 
    // Note: The length of setup time is calculated using [(IC_SDA_SETUP - 1) * (ic_clk_period)], so if the user requires 10 ic_clk periods of setup time, they should program a value of 11. The IC_SDA_SETUP register is only used by the DW_apb_i2c when operating as a slave transmitter.
    // Reset value: 0x00000064
    BEGIN_TYPE(IC_SDA_SETUP_t, uint32_t)
        // SDA Setup. It is recommended that if the required delay is 1000ns, then for an ic_clk frequency of 10 MHz, IC_SDA_SETUP should be programmed to a value of 11. IC_SDA_SETUP must be programmed with a minimum value of 2.
        ADD_BITFIELD_RW(SDA_SETUP, 0, 8)
    END_TYPE()

    // I2C ACK General Call Register
    // 
    // The register controls whether DW_apb_i2c responds with a ACK or NACK when it receives an I2C General Call address.
    // 
    // This register is applicable only when the DW_apb_i2c is in slave mode.
    // Reset value: 0x00000001
    BEGIN_TYPE(IC_ACK_GENERAL_CALL_t, uint32_t)
        // ACK General Call. When set to 1, DW_apb_i2c responds with a ACK (by asserting ic_data_oe) when it receives a General Call. Otherwise, DW_apb_i2c responds with a NACK (by negating ic_data_oe).
        ADD_BITFIELD_RW(ACK_GEN_CALL, 0, 1)
    END_TYPE()

    // Generate NACK for a General Call
    static const uint32_t IC_ACK_GENERAL_CALL_ACK_GEN_CALL__DISABLED = 0;
    // Generate ACK for a General Call
    static const uint32_t IC_ACK_GENERAL_CALL_ACK_GEN_CALL__ENABLED = 1;

    // I2C Enable Status Register
    // 
    // The register is used to report the DW_apb_i2c hardware status when the IC_ENABLE[0] register is set from 1 to 0; that is, when DW_apb_i2c is disabled.
    // 
    // If IC_ENABLE[0] has been set to 1, bits 2:1 are forced to 0, and bit 0 is forced to 1.
    // 
    // If IC_ENABLE[0] has been set to 0, bits 2:1 is only be valid as soon as bit 0 is read as '0'.
    // 
    // Note: When IC_ENABLE[0] has been set to 0, a delay occurs for bit 0 to be read as 0 because disabling the DW_apb_i2c depends on I2C bus activities.
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_ENABLE_STATUS_t, uint32_t)
        // Slave Received Data Lost. This bit indicates if a Slave-Receiver operation has been aborted with at least one data byte received from an I2C transfer due to the setting bit 0 of IC_ENABLE from 1 to 0. When read as 1, DW_apb_i2c is deemed to have been actively engaged in an aborted I2C transfer (with matching address) and the data phase of the I2C transfer has been entered, even though a data byte has been responded with a NACK.
        // 
        // Note:  If the remote I2C master terminates the transfer with a STOP condition before the DW_apb_i2c has a chance to NACK a transfer, and IC_ENABLE[0] has been set to 0, then this bit is also set to 1.
        // 
        // When read as 0, DW_apb_i2c is deemed to have been disabled without being actively involved in the data phase of a Slave-Receiver transfer.
        // 
        // Note:  The CPU can safely read this bit when IC_EN (bit 0) is read as 0.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(SLV_RX_DATA_LOST, 2, 1)
        // Slave Disabled While Busy (Transmit, Receive). This bit indicates if a potential or active Slave operation has been aborted due to the setting bit 0 of the IC_ENABLE register from 1 to 0. This bit is set when the CPU writes a 0 to the IC_ENABLE register while:
        // 
        // (a) DW_apb_i2c is receiving the address byte of the Slave-Transmitter operation from a remote master;
        // 
        // OR,
        // 
        // (b) address and data bytes of the Slave-Receiver operation from a remote master.
        // 
        // When read as 1, DW_apb_i2c is deemed to have forced a NACK during any part of an I2C transfer, irrespective of whether the I2C address matches the slave address set in DW_apb_i2c (IC_SAR register) OR if the transfer is completed before IC_ENABLE is set to 0 but has not taken effect.
        // 
        // Note:  If the remote I2C master terminates the transfer with a STOP condition before the DW_apb_i2c has a chance to NACK a transfer, and IC_ENABLE[0] has been set to 0, then this bit will also be set to 1.
        // 
        // When read as 0, DW_apb_i2c is deemed to have been disabled when there is master activity, or when the I2C bus is idle.
        // 
        // Note:  The CPU can safely read this bit when IC_EN (bit 0) is read as 0.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(SLV_DISABLED_WHILE_BUSY, 1, 1)
        // ic_en Status. This bit always reflects the value driven on the output port ic_en. - When read as 1, DW_apb_i2c is deemed to be in an enabled state. - When read as 0, DW_apb_i2c is deemed completely inactive. Note:  The CPU can safely read this bit anytime. When this bit is read as 0, the CPU can safely read SLV_RX_DATA_LOST (bit 2) and SLV_DISABLED_WHILE_BUSY (bit 1).
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(IC_EN, 0, 1)
    END_TYPE()

    // Slave RX Data is not lost
    static const uint32_t IC_ENABLE_STATUS_SLV_RX_DATA_LOST__INACTIVE = 0;
    // Slave RX Data is lost
    static const uint32_t IC_ENABLE_STATUS_SLV_RX_DATA_LOST__ACTIVE = 1;
    // Slave is disabled when it is idle
    static const uint32_t IC_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY__INACTIVE = 0;
    // Slave is disabled when it is active
    static const uint32_t IC_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY__ACTIVE = 1;
    // I2C disabled
    static const uint32_t IC_ENABLE_STATUS_IC_EN__DISABLED = 0;
    // I2C enabled
    static const uint32_t IC_ENABLE_STATUS_IC_EN__ENABLED = 1;

    // I2C SS, FS or FM+ spike suppression limit
    // 
    // This register is used to store the duration, measured in ic_clk cycles, of the longest spike that is filtered out by the spike suppression logic when the component is operating in SS, FS or FM+ modes. The relevant I2C requirement is tSP (table 4) as detailed in the I2C Bus Specification. This register must be programmed with a minimum value of 1.
    // Reset value: 0x00000007
    BEGIN_TYPE(IC_FS_SPKLEN_t, uint32_t)
        // This register must be set before any I2C bus transaction can take place to ensure stable operation. This register sets the duration, measured in ic_clk cycles, of the longest spike in the SCL or SDA lines that will be filtered out by the spike suppression logic. This register can be written only when the I2C interface is disabled which corresponds to the IC_ENABLE[0] register being set to 0. Writes at other times have no effect. The minimum valid value is 1; hardware prevents values less than this being written, and if attempted results in 1 being set. or more information, refer to 'Spike Suppression'.
        ADD_BITFIELD_RW(IC_FS_SPKLEN, 0, 8)
    END_TYPE()

    // Clear RESTART_DET Interrupt Register
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_CLR_RESTART_DET_t, uint32_t)
        // Read this register to clear the RESTART_DET interrupt (bit 12) of IC_RAW_INTR_STAT register.
        // 
        // Reset value: 0x0
        ADD_BITFIELD_RO(CLR_RESTART_DET, 0, 1)
    END_TYPE()

    // Component Parameter Register 1
    // 
    // Note This register is not implemented and therefore reads as 0. If it was implemented it would be a constant read-only register that contains encoded information about the component's parameter settings. Fields shown below are the settings for those parameters
    // Reset value: 0x00000000
    BEGIN_TYPE(IC_COMP_PARAM_1_t, uint32_t)
        // TX Buffer Depth = 16
        ADD_BITFIELD_RO(TX_BUFFER_DEPTH, 16, 8)
        // RX Buffer Depth = 16
        ADD_BITFIELD_RO(RX_BUFFER_DEPTH, 8, 8)
        // Encoded parameters not visible
        ADD_BITFIELD_RO(ADD_ENCODED_PARAMS, 7, 1)
        // DMA handshaking signals are enabled
        ADD_BITFIELD_RO(HAS_DMA, 6, 1)
        // COMBINED Interrupt outputs
        ADD_BITFIELD_RO(INTR_IO, 5, 1)
        // Programmable count values for each mode.
        ADD_BITFIELD_RO(HC_COUNT_VALUES, 4, 1)
        // MAX SPEED MODE = FAST MODE
        ADD_BITFIELD_RO(MAX_SPEED_MODE, 2, 2)
        // APB data bus width is 32 bits
        ADD_BITFIELD_RO(APB_DATA_WIDTH, 0, 2)
    END_TYPE()

    // I2C Component Version Register
    // Reset value: 0x3230312a
    BEGIN_TYPE(IC_COMP_VERSION_t, uint32_t)
        ADD_BITFIELD_RO(IC_COMP_VERSION, 0, 32)
    END_TYPE()

    // I2C Component Type Register
    // Reset value: 0x44570140
    BEGIN_TYPE(IC_COMP_TYPE_t, uint32_t)
        // Designware Component Type number = 0x44_57_01_40. This assigned unique hex value is constant and is derived from the two ASCII letters 'DW' followed by a 16-bit unsigned number.
        ADD_BITFIELD_RO(IC_COMP_TYPE, 0, 32)
    END_TYPE()

    struct I2C0_t {
        IC_CON_t                      IC_CON;
        IC_TAR_t                      IC_TAR;
        IC_SAR_t                      IC_SAR;
        uint32_t                      reserved0;
        IC_DATA_CMD_t                 IC_DATA_CMD;
        IC_SS_SCL_HCNT_t              IC_SS_SCL_HCNT;
        IC_SS_SCL_LCNT_t              IC_SS_SCL_LCNT;
        IC_FS_SCL_HCNT_t              IC_FS_SCL_HCNT;
        IC_FS_SCL_LCNT_t              IC_FS_SCL_LCNT;
        uint32_t                      reserved1[2];
        IC_INTR_STAT_t                IC_INTR_STAT;
        IC_INTR_MASK_t                IC_INTR_MASK;
        IC_RAW_INTR_STAT_t            IC_RAW_INTR_STAT;
        IC_RX_TL_t                    IC_RX_TL;
        IC_TX_TL_t                    IC_TX_TL;
        IC_CLR_INTR_t                 IC_CLR_INTR;
        IC_CLR_RX_UNDER_t             IC_CLR_RX_UNDER;
        IC_CLR_RX_OVER_t              IC_CLR_RX_OVER;
        IC_CLR_TX_OVER_t              IC_CLR_TX_OVER;
        IC_CLR_RD_REQ_t               IC_CLR_RD_REQ;
        IC_CLR_TX_ABRT_t              IC_CLR_TX_ABRT;
        IC_CLR_RX_DONE_t              IC_CLR_RX_DONE;
        IC_CLR_ACTIVITY_t             IC_CLR_ACTIVITY;
        IC_CLR_STOP_DET_t             IC_CLR_STOP_DET;
        IC_CLR_START_DET_t            IC_CLR_START_DET;
        IC_CLR_GEN_CALL_t             IC_CLR_GEN_CALL;
        IC_ENABLE_t                   IC_ENABLE;
        IC_STATUS_t                   IC_STATUS;
        IC_TXFLR_t                    IC_TXFLR;
        IC_RXFLR_t                    IC_RXFLR;
        IC_SDA_HOLD_t                 IC_SDA_HOLD;
        IC_TX_ABRT_SOURCE_t           IC_TX_ABRT_SOURCE;
        IC_SLV_DATA_NACK_ONLY_t       IC_SLV_DATA_NACK_ONLY;
        IC_DMA_CR_t                   IC_DMA_CR;
        IC_DMA_TDLR_t                 IC_DMA_TDLR;
        IC_DMA_RDLR_t                 IC_DMA_RDLR;
        IC_SDA_SETUP_t                IC_SDA_SETUP;
        IC_ACK_GENERAL_CALL_t         IC_ACK_GENERAL_CALL;
        IC_ENABLE_STATUS_t            IC_ENABLE_STATUS;
        IC_FS_SPKLEN_t                IC_FS_SPKLEN;
        uint32_t                      reserved2;
        IC_CLR_RESTART_DET_t          IC_CLR_RESTART_DET;
        uint32_t                      reserved3[18];
        IC_COMP_PARAM_1_t             IC_COMP_PARAM_1;
        IC_COMP_VERSION_t             IC_COMP_VERSION;
        IC_COMP_TYPE_t                IC_COMP_TYPE;
    };

    static I2C0_t & I2C0     = (*(I2C0_t *)0x40044000);
    static I2C0_t & I2C0_XOR = (*(I2C0_t *)0x40045000);
    static I2C0_t & I2C0_SET = (*(I2C0_t *)0x40046000);
    static I2C0_t & I2C0_CLR = (*(I2C0_t *)0x40047000);

} // _I2C0_

namespace _I2C1_  {

    static _I2C0_::I2C0_t & I2C1     = (*(_I2C0_::I2C0_t *)0x40048000);
    static _I2C0_::I2C0_t & I2C1_XOR = (*(_I2C0_::I2C0_t *)0x40049000);
    static _I2C0_::I2C0_t & I2C1_SET = (*(_I2C0_::I2C0_t *)0x4004a000);
    static _I2C0_::I2C0_t & I2C1_CLR = (*(_I2C0_::I2C0_t *)0x4004b000);

} // _I2C1_

// Control and data interface to SAR ADC
namespace _ADC_  {

    // ADC Control and Status
    // Reset value: 0x00000000
    BEGIN_TYPE(CS_t, uint32_t)
        // Round-robin sampling. 1 bit per channel. Set all bits to 0 to disable.
        // Otherwise, the ADC will cycle through each enabled channel in a round-robin fashion.
        // The first channel to be sampled will be the one currently indicated by AINSEL.
        // AINSEL will be updated after each conversion with the newly-selected channel.
        ADD_BITFIELD_RW(RROBIN, 16, 5)
        // Select analog mux input. Updated automatically in round-robin mode.
        ADD_BITFIELD_RW(AINSEL, 12, 3)
        // Some past ADC conversion encountered an error. Write 1 to clear.
        ADD_BITFIELD_RW(ERR_STICKY, 10, 1)
        // The most recent ADC conversion encountered an error; result is undefined or noisy.
        ADD_BITFIELD_RO(ERR, 9, 1)
        // 1 if the ADC is ready to start a new conversion. Implies any previous conversion has completed.
        // 0 whilst conversion in progress.
        ADD_BITFIELD_RO(READY, 8, 1)
        // Continuously perform conversions whilst this bit is 1. A new conversion will start immediately after the previous finishes.
        ADD_BITFIELD_RW(START_MANY, 3, 1)
        // Start a single conversion. Self-clearing. Ignored if start_many is asserted.
        ADD_BITFIELD_RW(START_ONCE, 2, 1)
        // Power on temperature sensor. 1 - enabled. 0 - disabled.
        ADD_BITFIELD_RW(TS_EN, 1, 1)
        // Power on ADC and enable its clock.
        // 1 - enabled. 0 - disabled.
        ADD_BITFIELD_RW(EN, 0, 1)
    END_TYPE()

    // Result of most recent ADC conversion
    // Reset value: 0x00000000
    BEGIN_TYPE(RESULT_t, uint32_t)
        ADD_BITFIELD_RO(RESULT, 0, 12)
    END_TYPE()

    // FIFO control and status
    // Reset value: 0x00000000
    BEGIN_TYPE(FCS_t, uint32_t)
        // DREQ/IRQ asserted when level >= threshold
        ADD_BITFIELD_RW(THRESH, 24, 4)
        // The number of conversion results currently waiting in the FIFO
        ADD_BITFIELD_RO(LEVEL, 16, 4)
        // 1 if the FIFO has been overflowed. Write 1 to clear.
        ADD_BITFIELD_RW(OVER, 11, 1)
        // 1 if the FIFO has been underflowed. Write 1 to clear.
        ADD_BITFIELD_RW(UNDER, 10, 1)
        ADD_BITFIELD_RO(FULL, 9, 1)
        ADD_BITFIELD_RO(EMPTY, 8, 1)
        // If 1: assert DMA requests when FIFO contains data
        ADD_BITFIELD_RW(DREQ_EN, 3, 1)
        // If 1: conversion error bit appears in the FIFO alongside the result
        ADD_BITFIELD_RW(ERR, 2, 1)
        // If 1: FIFO results are right-shifted to be one byte in size. Enables DMA to byte buffers.
        ADD_BITFIELD_RW(SHIFT, 1, 1)
        // If 1: write result to the FIFO after each conversion.
        ADD_BITFIELD_RW(EN, 0, 1)
    END_TYPE()

    // Conversion result FIFO
    // Reset value: 0x00000000
    BEGIN_TYPE(FIFO_t, uint32_t)
        // 1 if this particular sample experienced a conversion error. Remains in the same location if the sample is shifted.
        ADD_BITFIELD_RO(ERR, 15, 1)
        ADD_BITFIELD_RO(VAL, 0, 12)
    END_TYPE()

    // Clock divider. If non-zero, CS_START_MANY will start conversions
    // at regular intervals rather than back-to-back.
    // The divider is reset when either of these fields are written.
    // Total period is 1 + INT + FRAC / 256
    // Reset value: 0x00000000
    BEGIN_TYPE(DIV_t, uint32_t)
        // Integer part of clock divisor.
        ADD_BITFIELD_RW(INT, 8, 16)
        // Fractional part of clock divisor. First-order delta-sigma.
        ADD_BITFIELD_RW(FRAC, 0, 8)
    END_TYPE()

    // Raw Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR_t, uint32_t)
        // Triggered when the sample FIFO reaches a certain level.
        // This level can be programmed via the FCS_THRESH field.
        ADD_BITFIELD_RO(FIFO, 0, 1)
    END_TYPE()

    // Interrupt Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(INTE_t, uint32_t)
        // Triggered when the sample FIFO reaches a certain level.
        // This level can be programmed via the FCS_THRESH field.
        ADD_BITFIELD_RW(FIFO, 0, 1)
    END_TYPE()

    // Interrupt Force
    // Reset value: 0x00000000
    BEGIN_TYPE(INTF_t, uint32_t)
        // Triggered when the sample FIFO reaches a certain level.
        // This level can be programmed via the FCS_THRESH field.
        ADD_BITFIELD_RW(FIFO, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing
    // Reset value: 0x00000000
    BEGIN_TYPE(INTS_t, uint32_t)
        // Triggered when the sample FIFO reaches a certain level.
        // This level can be programmed via the FCS_THRESH field.
        ADD_BITFIELD_RO(FIFO, 0, 1)
    END_TYPE()

    struct ADC_t {
        CS_t                          CS;
        RESULT_t                      RESULT;
        FCS_t                         FCS;
        FIFO_t                        FIFO;
        DIV_t                         DIV;
        INTR_t                        INTR;
        INTE_t                        INTE;
        INTF_t                        INTF;
        INTS_t                        INTS;
    };

    static ADC_t & ADC     = (*(ADC_t *)0x4004c000);
    static ADC_t & ADC_XOR = (*(ADC_t *)0x4004d000);
    static ADC_t & ADC_SET = (*(ADC_t *)0x4004e000);
    static ADC_t & ADC_CLR = (*(ADC_t *)0x4004f000);

} // _ADC_

// Simple PWM
namespace _PWM_  {

    // Control and status register
    // Reset value: 0x00000000
    BEGIN_TYPE(CH_CSR_t, uint32_t)
        // Advance the phase of the counter by 1 count, while it is running.
        // Self-clearing. Write a 1, and poll until low. Counter must be running
        // at less than full speed (div_int + div_frac / 16 > 1)
        ADD_BITFIELD_RW(PH_ADV, 7, 1)
        // Retard the phase of the counter by 1 count, while it is running.
        // Self-clearing. Write a 1, and poll until low. Counter must be running.
        ADD_BITFIELD_RW(PH_RET, 6, 1)
        ADD_BITFIELD_RW(DIVMODE, 4, 2)
        // Invert output B
        ADD_BITFIELD_RW(B_INV, 3, 1)
        // Invert output A
        ADD_BITFIELD_RW(A_INV, 2, 1)
        // 1: Enable phase-correct modulation. 0: Trailing-edge
        ADD_BITFIELD_RW(PH_CORRECT, 1, 1)
        // Enable the PWM channel.
        ADD_BITFIELD_RW(EN, 0, 1)
    END_TYPE()

    // Free-running counting at rate dictated by fractional divider
    static const uint32_t CH_CSR_DIVMODE__div = 0;
    // Fractional divider operation is gated by the PWM B pin.
    static const uint32_t CH_CSR_DIVMODE__level = 1;
    // Counter advances with each rising edge of the PWM B pin.
    static const uint32_t CH_CSR_DIVMODE__rise = 2;
    // Counter advances with each falling edge of the PWM B pin.
    static const uint32_t CH_CSR_DIVMODE__fall = 3;

    // INT and FRAC form a fixed-point fractional number.
    // Counting rate is system clock frequency divided by this number.
    // Fractional division uses simple 1st-order sigma-delta.
    // Reset value: 0x00000010
    BEGIN_TYPE(CH_DIV_t, uint32_t)
        ADD_BITFIELD_RW(INT, 4, 8)
        ADD_BITFIELD_RW(FRAC, 0, 4)
    END_TYPE()

    // Direct access to the PWM counter
    // Reset value: 0x00000000
    BEGIN_TYPE(CH_CTR_t, uint32_t)
        ADD_BITFIELD_RW(CTR, 0, 16)
    END_TYPE()

    // Counter compare values
    // Reset value: 0x00000000
    BEGIN_TYPE(CH_CC_t, uint32_t)
        ADD_BITFIELD_RW(B, 16, 16)
        ADD_BITFIELD_RW(A, 0, 16)
    END_TYPE()

    // Counter wrap value
    // Reset value: 0x0000ffff
    BEGIN_TYPE(CH_TOP_t, uint32_t)
        ADD_BITFIELD_RW(TOP, 0, 16)
    END_TYPE()

    // This register aliases the CSR_EN bits for all channels.
    // Writing to this register allows multiple channels to be enabled
    // or disabled simultaneously, so they can run in perfect sync.
    // For each channel, there is only one physical EN register bit,
    // which can be accessed through here or CHx_CSR.
    // Reset value: 0x00000000
    BEGIN_TYPE(EN_t, uint32_t)
        ADD_BITFIELD_RW(CH7, 7, 1)
        ADD_BITFIELD_RW(CH6, 6, 1)
        ADD_BITFIELD_RW(CH5, 5, 1)
        ADD_BITFIELD_RW(CH4, 4, 1)
        ADD_BITFIELD_RW(CH3, 3, 1)
        ADD_BITFIELD_RW(CH2, 2, 1)
        ADD_BITFIELD_RW(CH1, 1, 1)
        ADD_BITFIELD_RW(CH0, 0, 1)
    END_TYPE()

    // Raw Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR_t, uint32_t)
        ADD_BITFIELD_RW(CH7, 7, 1)
        ADD_BITFIELD_RW(CH6, 6, 1)
        ADD_BITFIELD_RW(CH5, 5, 1)
        ADD_BITFIELD_RW(CH4, 4, 1)
        ADD_BITFIELD_RW(CH3, 3, 1)
        ADD_BITFIELD_RW(CH2, 2, 1)
        ADD_BITFIELD_RW(CH1, 1, 1)
        ADD_BITFIELD_RW(CH0, 0, 1)
    END_TYPE()

    // Interrupt Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(INTE_t, uint32_t)
        ADD_BITFIELD_RW(CH7, 7, 1)
        ADD_BITFIELD_RW(CH6, 6, 1)
        ADD_BITFIELD_RW(CH5, 5, 1)
        ADD_BITFIELD_RW(CH4, 4, 1)
        ADD_BITFIELD_RW(CH3, 3, 1)
        ADD_BITFIELD_RW(CH2, 2, 1)
        ADD_BITFIELD_RW(CH1, 1, 1)
        ADD_BITFIELD_RW(CH0, 0, 1)
    END_TYPE()

    // Interrupt Force
    // Reset value: 0x00000000
    BEGIN_TYPE(INTF_t, uint32_t)
        ADD_BITFIELD_RW(CH7, 7, 1)
        ADD_BITFIELD_RW(CH6, 6, 1)
        ADD_BITFIELD_RW(CH5, 5, 1)
        ADD_BITFIELD_RW(CH4, 4, 1)
        ADD_BITFIELD_RW(CH3, 3, 1)
        ADD_BITFIELD_RW(CH2, 2, 1)
        ADD_BITFIELD_RW(CH1, 1, 1)
        ADD_BITFIELD_RW(CH0, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing
    // Reset value: 0x00000000
    BEGIN_TYPE(INTS_t, uint32_t)
        ADD_BITFIELD_RO(CH7, 7, 1)
        ADD_BITFIELD_RO(CH6, 6, 1)
        ADD_BITFIELD_RO(CH5, 5, 1)
        ADD_BITFIELD_RO(CH4, 4, 1)
        ADD_BITFIELD_RO(CH3, 3, 1)
        ADD_BITFIELD_RO(CH2, 2, 1)
        ADD_BITFIELD_RO(CH1, 1, 1)
        ADD_BITFIELD_RO(CH0, 0, 1)
    END_TYPE()

    struct PWM_t {
        CH_CSR_t                      CH0_CSR;
        CH_DIV_t                      CH0_DIV;
        CH_CTR_t                      CH0_CTR;
        CH_CC_t                       CH0_CC;
        CH_TOP_t                      CH0_TOP;
        CH_CSR_t                      CH1_CSR;
        CH_DIV_t                      CH1_DIV;
        CH_CTR_t                      CH1_CTR;
        CH_CC_t                       CH1_CC;
        CH_TOP_t                      CH1_TOP;
        CH_CSR_t                      CH2_CSR;
        CH_DIV_t                      CH2_DIV;
        CH_CTR_t                      CH2_CTR;
        CH_CC_t                       CH2_CC;
        CH_TOP_t                      CH2_TOP;
        CH_CSR_t                      CH3_CSR;
        CH_DIV_t                      CH3_DIV;
        CH_CTR_t                      CH3_CTR;
        CH_CC_t                       CH3_CC;
        CH_TOP_t                      CH3_TOP;
        CH_CSR_t                      CH4_CSR;
        CH_DIV_t                      CH4_DIV;
        CH_CTR_t                      CH4_CTR;
        CH_CC_t                       CH4_CC;
        CH_TOP_t                      CH4_TOP;
        CH_CSR_t                      CH5_CSR;
        CH_DIV_t                      CH5_DIV;
        CH_CTR_t                      CH5_CTR;
        CH_CC_t                       CH5_CC;
        CH_TOP_t                      CH5_TOP;
        CH_CSR_t                      CH6_CSR;
        CH_DIV_t                      CH6_DIV;
        CH_CTR_t                      CH6_CTR;
        CH_CC_t                       CH6_CC;
        CH_TOP_t                      CH6_TOP;
        CH_CSR_t                      CH7_CSR;
        CH_DIV_t                      CH7_DIV;
        CH_CTR_t                      CH7_CTR;
        CH_CC_t                       CH7_CC;
        CH_TOP_t                      CH7_TOP;
        EN_t                          EN;
        INTR_t                        INTR;
        INTE_t                        INTE;
        INTF_t                        INTF;
        INTS_t                        INTS;
    };

    static PWM_t & PWM     = (*(PWM_t *)0x40050000);
    static PWM_t & PWM_XOR = (*(PWM_t *)0x40051000);
    static PWM_t & PWM_SET = (*(PWM_t *)0x40052000);
    static PWM_t & PWM_CLR = (*(PWM_t *)0x40053000);

} // _PWM_

// Controls time and alarms
// time is a 64 bit value indicating the time in usec since power-on
// timeh is the top 32 bits of time & timel is the bottom 32 bits
// to change time write to timelw before timehw
// to read time read from timelr before timehr
// An alarm is set by setting alarm_enable and writing to the corresponding alarm register
// When an alarm is pending, the corresponding alarm_running signal will be high
// An alarm can be cancelled before it has finished by clearing the alarm_enable
// When an alarm fires, the corresponding alarm_irq is set and alarm_running is cleared
// To clear the interrupt write a 1 to the corresponding alarm_irq
namespace _TIMER_  {

    // Write to bits 63:32 of time
    // always write timelw before timehw
    // Reset value: 0x00000000
    typedef uint32_t TIMEHW_t;

    // Write to bits 31:0 of time
    // writes do not get copied to time until timehw is written
    // Reset value: 0x00000000
    typedef uint32_t TIMELW_t;

    // Read from bits 63:32 of time
    // always read timelr before timehr
    // Reset value: 0x00000000
    typedef uint32_t TIMEHR_t;

    // Read from bits 31:0 of time
    // Reset value: 0x00000000
    typedef uint32_t TIMELR_t;

    // Arm alarm 0, and configure the time it will fire.
    // Once armed, the alarm fires when TIMER_ALARM0 == TIMELR.
    // The alarm will disarm itself once it fires, and can
    // be disarmed early using the ARMED status register.
    // Reset value: 0x00000000
    typedef uint32_t ALARM0_t;

    // Arm alarm 1, and configure the time it will fire.
    // Once armed, the alarm fires when TIMER_ALARM1 == TIMELR.
    // The alarm will disarm itself once it fires, and can
    // be disarmed early using the ARMED status register.
    // Reset value: 0x00000000
    typedef uint32_t ALARM1_t;

    // Arm alarm 2, and configure the time it will fire.
    // Once armed, the alarm fires when TIMER_ALARM2 == TIMELR.
    // The alarm will disarm itself once it fires, and can
    // be disarmed early using the ARMED status register.
    // Reset value: 0x00000000
    typedef uint32_t ALARM2_t;

    // Arm alarm 3, and configure the time it will fire.
    // Once armed, the alarm fires when TIMER_ALARM3 == TIMELR.
    // The alarm will disarm itself once it fires, and can
    // be disarmed early using the ARMED status register.
    // Reset value: 0x00000000
    typedef uint32_t ALARM3_t;

    // Indicates the armed/disarmed status of each alarm.
    // A write to the corresponding ALARMx register arms the alarm.
    // Alarms automatically disarm upon firing, but writing ones here
    // will disarm immediately without waiting to fire.
    // Reset value: 0x00000000
    BEGIN_TYPE(ARMED_t, uint32_t)
        ADD_BITFIELD_RW(ARMED, 0, 4)
    END_TYPE()

    // Raw read from bits 63:32 of time (no side effects)
    // Reset value: 0x00000000
    typedef uint32_t TIMERAWH_t;

    // Raw read from bits 31:0 of time (no side effects)
    // Reset value: 0x00000000
    typedef uint32_t TIMERAWL_t;

    // Set bits high to enable pause when the corresponding debug ports are active
    // Reset value: 0x00000007
    BEGIN_TYPE(DBGPAUSE_t, uint32_t)
        // Pause when processor 1 is in debug mode
        ADD_BITFIELD_RW(DBG1, 2, 1)
        // Pause when processor 0 is in debug mode
        ADD_BITFIELD_RW(DBG0, 1, 1)
    END_TYPE()

    // Set high to pause the timer
    // Reset value: 0x00000000
    BEGIN_TYPE(PAUSE_t, uint32_t)
        ADD_BITFIELD_RW(PAUSE, 0, 1)
    END_TYPE()

    // Raw Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR_t, uint32_t)
        ADD_BITFIELD_RW(ALARM_3, 3, 1)
        ADD_BITFIELD_RW(ALARM_2, 2, 1)
        ADD_BITFIELD_RW(ALARM_1, 1, 1)
        ADD_BITFIELD_RW(ALARM_0, 0, 1)
    END_TYPE()

    // Interrupt Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(INTE_t, uint32_t)
        ADD_BITFIELD_RW(ALARM_3, 3, 1)
        ADD_BITFIELD_RW(ALARM_2, 2, 1)
        ADD_BITFIELD_RW(ALARM_1, 1, 1)
        ADD_BITFIELD_RW(ALARM_0, 0, 1)
    END_TYPE()

    // Interrupt Force
    // Reset value: 0x00000000
    BEGIN_TYPE(INTF_t, uint32_t)
        ADD_BITFIELD_RW(ALARM_3, 3, 1)
        ADD_BITFIELD_RW(ALARM_2, 2, 1)
        ADD_BITFIELD_RW(ALARM_1, 1, 1)
        ADD_BITFIELD_RW(ALARM_0, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing
    // Reset value: 0x00000000
    BEGIN_TYPE(INTS_t, uint32_t)
        ADD_BITFIELD_RO(ALARM_3, 3, 1)
        ADD_BITFIELD_RO(ALARM_2, 2, 1)
        ADD_BITFIELD_RO(ALARM_1, 1, 1)
        ADD_BITFIELD_RO(ALARM_0, 0, 1)
    END_TYPE()

    struct TIMER_t {
        TIMEHW_t                      TIMEHW;
        TIMELW_t                      TIMELW;
        TIMEHR_t                      TIMEHR;
        TIMELR_t                      TIMELR;
        ALARM0_t                      ALARM0;
        ALARM1_t                      ALARM1;
        ALARM2_t                      ALARM2;
        ALARM3_t                      ALARM3;
        ARMED_t                       ARMED;
        TIMERAWH_t                    TIMERAWH;
        TIMERAWL_t                    TIMERAWL;
        DBGPAUSE_t                    DBGPAUSE;
        PAUSE_t                       PAUSE;
        INTR_t                        INTR;
        INTE_t                        INTE;
        INTF_t                        INTF;
        INTS_t                        INTS;
    };

    static TIMER_t & TIMER     = (*(TIMER_t *)0x40054000);
    static TIMER_t & TIMER_XOR = (*(TIMER_t *)0x40055000);
    static TIMER_t & TIMER_SET = (*(TIMER_t *)0x40056000);
    static TIMER_t & TIMER_CLR = (*(TIMER_t *)0x40057000);

} // _TIMER_

namespace _WATCHDOG_  {

    // Watchdog control
    // The rst_wdsel register determines which subsystems are reset when the watchdog is triggered.
    // The watchdog can be triggered in software.
    // Reset value: 0x07000000
    BEGIN_TYPE(CTRL_t, uint32_t)
        // Trigger a watchdog reset
        ADD_BITFIELD_RW(TRIGGER, 31, 1)
        // When not enabled the watchdog timer is paused
        ADD_BITFIELD_RW(ENABLE, 30, 1)
        // Pause the watchdog timer when processor 1 is in debug mode
        ADD_BITFIELD_RW(PAUSE_DBG1, 26, 1)
        // Pause the watchdog timer when processor 0 is in debug mode
        ADD_BITFIELD_RW(PAUSE_DBG0, 25, 1)
        // Pause the watchdog timer when JTAG is accessing the bus fabric
        ADD_BITFIELD_RW(PAUSE_JTAG, 24, 1)
        // Indicates the number of ticks / 2 (see errata RP2040-E1) before a watchdog reset will be triggered
        ADD_BITFIELD_RO(TIME, 0, 24)
    END_TYPE()

    // Load the watchdog timer. The maximum setting is 0xffffff which corresponds to 0xffffff / 2 ticks before triggering a watchdog reset (see errata RP2040-E1).
    // Reset value: 0x00000000
    BEGIN_TYPE(LOAD_t, uint32_t)
        ADD_BITFIELD_WO(LOAD, 0, 24)
    END_TYPE()

    // Logs the reason for the last reset. Both bits are zero for the case of a hardware reset.
    // Reset value: 0x00000000
    BEGIN_TYPE(REASON_t, uint32_t)
        ADD_BITFIELD_RO(FORCE, 1, 1)
        ADD_BITFIELD_RO(TIMER, 0, 1)
    END_TYPE()

    // Scratch register. Information persists through soft reset of the chip.
    // Reset value: 0x00000000
    typedef uint32_t SCRATCH_t;

    // Controls the tick generator
    // Reset value: 0x00000200
    BEGIN_TYPE(TICK_t, uint32_t)
        // Count down timer: the remaining number clk_tick cycles before the next tick is generated.
        ADD_BITFIELD_RO(COUNT, 11, 9)
        // Is the tick generator running?
        ADD_BITFIELD_RO(RUNNING, 10, 1)
        // start / stop tick generation
        ADD_BITFIELD_RW(ENABLE, 9, 1)
        // Total number of clk_tick cycles before the next tick.
        ADD_BITFIELD_RW(CYCLES, 0, 9)
    END_TYPE()

    struct WATCHDOG_t {
        CTRL_t                        CTRL;
        LOAD_t                        LOAD;
        REASON_t                      REASON;
        SCRATCH_t                     SCRATCH[8];
        TICK_t                        TICK;
    };

    static WATCHDOG_t & WATCHDOG     = (*(WATCHDOG_t *)0x40058000);
    static WATCHDOG_t & WATCHDOG_XOR = (*(WATCHDOG_t *)0x40059000);
    static WATCHDOG_t & WATCHDOG_SET = (*(WATCHDOG_t *)0x4005a000);
    static WATCHDOG_t & WATCHDOG_CLR = (*(WATCHDOG_t *)0x4005b000);

} // _WATCHDOG_

// Register block to control RTC
namespace _RTC_  {

    // Divider minus 1 for the 1 second counter. Safe to change the value when RTC is not enabled.
    // Reset value: 0x00000000
    BEGIN_TYPE(CLKDIV_M1_t, uint32_t)
        ADD_BITFIELD_RW(CLKDIV_M1, 0, 16)
    END_TYPE()

    // RTC setup register 0
    // Reset value: 0x00000000
    BEGIN_TYPE(SETUP_0_t, uint32_t)
        // Year
        ADD_BITFIELD_RW(YEAR, 12, 12)
        // Month (1..12)
        ADD_BITFIELD_RW(MONTH, 8, 4)
        // Day of the month (1..31)
        ADD_BITFIELD_RW(DAY, 0, 5)
    END_TYPE()

    // RTC setup register 1
    // Reset value: 0x00000000
    BEGIN_TYPE(SETUP_1_t, uint32_t)
        // Day of the week: 1-Monday...0-Sunday ISO 8601 mod 7
        ADD_BITFIELD_RW(DOTW, 24, 3)
        // Hours
        ADD_BITFIELD_RW(HOUR, 16, 5)
        // Minutes
        ADD_BITFIELD_RW(MIN, 8, 6)
        // Seconds
        ADD_BITFIELD_RW(SEC, 0, 6)
    END_TYPE()

    // RTC Control and status
    // Reset value: 0x00000000
    BEGIN_TYPE(CTRL_t, uint32_t)
        // If set, leapyear is forced off.
        // Useful for years divisible by 100 but not by 400
        ADD_BITFIELD_RW(FORCE_NOTLEAPYEAR, 8, 1)
        // Load RTC
        ADD_BITFIELD_RW(LOAD, 4, 1)
        // RTC enabled (running)
        ADD_BITFIELD_RO(RTC_ACTIVE, 1, 1)
        // Enable RTC
        ADD_BITFIELD_RW(RTC_ENABLE, 0, 1)
    END_TYPE()

    // Interrupt setup register 0
    // Reset value: 0x00000000
    BEGIN_TYPE(IRQ_SETUP_0_t, uint32_t)
        ADD_BITFIELD_RO(MATCH_ACTIVE, 29, 1)
        // Global match enable. Don't change any other value while this one is enabled
        ADD_BITFIELD_RW(MATCH_ENA, 28, 1)
        // Enable year matching
        ADD_BITFIELD_RW(YEAR_ENA, 26, 1)
        // Enable month matching
        ADD_BITFIELD_RW(MONTH_ENA, 25, 1)
        // Enable day matching
        ADD_BITFIELD_RW(DAY_ENA, 24, 1)
        // Year
        ADD_BITFIELD_RW(YEAR, 12, 12)
        // Month (1..12)
        ADD_BITFIELD_RW(MONTH, 8, 4)
        // Day of the month (1..31)
        ADD_BITFIELD_RW(DAY, 0, 5)
    END_TYPE()

    // Interrupt setup register 1
    // Reset value: 0x00000000
    BEGIN_TYPE(IRQ_SETUP_1_t, uint32_t)
        // Enable day of the week matching
        ADD_BITFIELD_RW(DOTW_ENA, 31, 1)
        // Enable hour matching
        ADD_BITFIELD_RW(HOUR_ENA, 30, 1)
        // Enable minute matching
        ADD_BITFIELD_RW(MIN_ENA, 29, 1)
        // Enable second matching
        ADD_BITFIELD_RW(SEC_ENA, 28, 1)
        // Day of the week
        ADD_BITFIELD_RW(DOTW, 24, 3)
        // Hours
        ADD_BITFIELD_RW(HOUR, 16, 5)
        // Minutes
        ADD_BITFIELD_RW(MIN, 8, 6)
        // Seconds
        ADD_BITFIELD_RW(SEC, 0, 6)
    END_TYPE()

    // RTC register 1.
    // Reset value: 0x00000000
    BEGIN_TYPE(RTC_1_t, uint32_t)
        // Year
        ADD_BITFIELD_RO(YEAR, 12, 12)
        // Month (1..12)
        ADD_BITFIELD_RO(MONTH, 8, 4)
        // Day of the month (1..31)
        ADD_BITFIELD_RO(DAY, 0, 5)
    END_TYPE()

    // RTC register 0
    // Read this before RTC 1!
    // Reset value: 0x00000000
    BEGIN_TYPE(RTC_0_t, uint32_t)
        // Day of the week
        ADD_BITFIELD_RO(DOTW, 24, 3)
        // Hours
        ADD_BITFIELD_RO(HOUR, 16, 5)
        // Minutes
        ADD_BITFIELD_RO(MIN, 8, 6)
        // Seconds
        ADD_BITFIELD_RO(SEC, 0, 6)
    END_TYPE()

    // Raw Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR_t, uint32_t)
        ADD_BITFIELD_RO(RTC, 0, 1)
    END_TYPE()

    // Interrupt Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(INTE_t, uint32_t)
        ADD_BITFIELD_RW(RTC, 0, 1)
    END_TYPE()

    // Interrupt Force
    // Reset value: 0x00000000
    BEGIN_TYPE(INTF_t, uint32_t)
        ADD_BITFIELD_RW(RTC, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing
    // Reset value: 0x00000000
    BEGIN_TYPE(INTS_t, uint32_t)
        ADD_BITFIELD_RO(RTC, 0, 1)
    END_TYPE()

    struct RTC_t {
        CLKDIV_M1_t                   CLKDIV_M1;
        SETUP_0_t                     SETUP_0;
        SETUP_1_t                     SETUP_1;
        CTRL_t                        CTRL;
        IRQ_SETUP_0_t                 IRQ_SETUP_0;
        IRQ_SETUP_1_t                 IRQ_SETUP_1;
        RTC_1_t                       RTC_1;
        RTC_0_t                       RTC_0;
        INTR_t                        INTR;
        INTE_t                        INTE;
        INTF_t                        INTF;
        INTS_t                        INTS;
    };

    static RTC_t & RTC     = (*(RTC_t *)0x4005c000);
    static RTC_t & RTC_XOR = (*(RTC_t *)0x4005d000);
    static RTC_t & RTC_SET = (*(RTC_t *)0x4005e000);
    static RTC_t & RTC_CLR = (*(RTC_t *)0x4005f000);

} // _RTC_

namespace _ROSC_  {

    // Ring Oscillator control
    // Reset value: 0x00000aa0
    BEGIN_TYPE(CTRL_t, uint32_t)
        // On power-up this field is initialised to ENABLE
        // The system clock must be switched to another source before setting this field to DISABLE otherwise the chip will lock up
        // The 12-bit code is intended to give some protection against accidental writes. An invalid setting will enable the oscillator.
        ADD_BITFIELD_RW(ENABLE, 12, 12)
        // Controls the number of delay stages in the ROSC ring
        // LOW uses stages 0 to 7
        // MEDIUM uses stages 0 to 5
        // HIGH uses stages 0 to 3
        // TOOHIGH uses stages 0 to 1 and should not be used because its frequency exceeds design specifications
        // The clock output will not glitch when changing the range up one step at a time
        // The clock output will glitch when changing the range down
        // Note: the values here are gray coded which is why HIGH comes before TOOHIGH
        ADD_BITFIELD_RW(FREQ_RANGE, 0, 12)
    END_TYPE()

    static const uint32_t CTRL_ENABLE__DISABLE = 3358;
    static const uint32_t CTRL_ENABLE__ENABLE = 4011;
    static const uint32_t CTRL_FREQ_RANGE__LOW = 4004;
    static const uint32_t CTRL_FREQ_RANGE__MEDIUM = 4005;
    static const uint32_t CTRL_FREQ_RANGE__HIGH = 4007;
    static const uint32_t CTRL_FREQ_RANGE__TOOHIGH = 4006;

    // The FREQA & FREQB registers control the frequency by controlling the drive strength of each stage
    // The drive strength has 4 levels determined by the number of bits set
    // Increasing the number of bits set increases the drive strength and increases the oscillation frequency
    // 0 bits set is the default drive strength
    // 1 bit set doubles the drive strength
    // 2 bits set triples drive strength
    // 3 bits set quadruples drive strength
    // Reset value: 0x00000000
    BEGIN_TYPE(FREQA_t, uint32_t)
        // Set to 0x9696 to apply the settings
        // Any other value in this field will set all drive strengths to 0
        ADD_BITFIELD_RW(PASSWD, 16, 16)
        // Stage 3 drive strength
        ADD_BITFIELD_RW(DS3, 12, 3)
        // Stage 2 drive strength
        ADD_BITFIELD_RW(DS2, 8, 3)
        // Stage 1 drive strength
        ADD_BITFIELD_RW(DS1, 4, 3)
        // Stage 0 drive strength
        ADD_BITFIELD_RW(DS0, 0, 3)
    END_TYPE()

    static const uint32_t FREQA_PASSWD__PASS = 38550;

    // For a detailed description see freqa register
    // Reset value: 0x00000000
    BEGIN_TYPE(FREQB_t, uint32_t)
        // Set to 0x9696 to apply the settings
        // Any other value in this field will set all drive strengths to 0
        ADD_BITFIELD_RW(PASSWD, 16, 16)
        // Stage 7 drive strength
        ADD_BITFIELD_RW(DS7, 12, 3)
        // Stage 6 drive strength
        ADD_BITFIELD_RW(DS6, 8, 3)
        // Stage 5 drive strength
        ADD_BITFIELD_RW(DS5, 4, 3)
        // Stage 4 drive strength
        ADD_BITFIELD_RW(DS4, 0, 3)
    END_TYPE()

    static const uint32_t FREQB_PASSWD__PASS = 38550;

    // Ring Oscillator pause control
    // This is used to save power by pausing the ROSC
    // On power-up this field is initialised to WAKE
    // An invalid write will also select WAKE
    // Warning: setup the irq before selecting dormant mode
    // Reset value: 0x00000000
    typedef uint32_t DORMANT_t;

    // Controls the output divider
    // Reset value: 0x00000000
    BEGIN_TYPE(DIV_t, uint32_t)
        // set to 0xaa0 + div where
        // div = 0 divides by 32
        // div = 1-31 divides by div
        // any other value sets div=31
        // this register resets to div=16
        ADD_BITFIELD_RW(DIV, 0, 12)
    END_TYPE()

    static const uint32_t DIV_DIV__PASS = 2720;

    // Controls the phase shifted output
    // Reset value: 0x00000008
    BEGIN_TYPE(PHASE_t, uint32_t)
        // set to 0xaa
        // any other value enables the output with shift=0
        ADD_BITFIELD_RW(PASSWD, 4, 8)
        // enable the phase-shifted output
        // this can be changed on-the-fly
        ADD_BITFIELD_RW(ENABLE, 3, 1)
        // invert the phase-shifted output
        // this is ignored when div=1
        ADD_BITFIELD_RW(FLIP, 2, 1)
        // phase shift the phase-shifted output by SHIFT input clocks
        // this can be changed on-the-fly
        // must be set to 0 before setting div=1
        ADD_BITFIELD_RW(SHIFT, 0, 2)
    END_TYPE()

    // Ring Oscillator Status
    // Reset value: 0x00000000
    BEGIN_TYPE(STATUS_t, uint32_t)
        // Oscillator is running and stable
        ADD_BITFIELD_RO(STABLE, 31, 1)
        // An invalid value has been written to CTRL_ENABLE or CTRL_FREQ_RANGE or FREQA or FREQB or DIV or PHASE or DORMANT
        ADD_BITFIELD_RW(BADWRITE, 24, 1)
        // post-divider is running
        // this resets to 0 but transitions to 1 during chip startup
        ADD_BITFIELD_RO(DIV_RUNNING, 16, 1)
        // Oscillator is enabled but not necessarily running and stable
        // this resets to 0 but transitions to 1 during chip startup
        ADD_BITFIELD_RO(ENABLED, 12, 1)
    END_TYPE()

    // This just reads the state of the oscillator output so randomness is compromised if the ring oscillator is stopped or run at a harmonic of the bus frequency
    // Reset value: 0x00000001
    BEGIN_TYPE(RANDOMBIT_t, uint32_t)
        ADD_BITFIELD_RO(RANDOMBIT, 0, 1)
    END_TYPE()

    // A down counter running at the ROSC frequency which counts to zero and stops.
    // To start the counter write a non-zero value.
    // Can be used for short software pauses when setting up time sensitive hardware.
    // Reset value: 0x00000000
    BEGIN_TYPE(COUNT_t, uint32_t)
        ADD_BITFIELD_RW(COUNT, 0, 8)
    END_TYPE()

    struct ROSC_t {
        CTRL_t                        CTRL;
        FREQA_t                       FREQA;
        FREQB_t                       FREQB;
        DORMANT_t                     DORMANT;
        DIV_t                         DIV;
        PHASE_t                       PHASE;
        STATUS_t                      STATUS;
        RANDOMBIT_t                   RANDOMBIT;
        COUNT_t                       COUNT;
    };

    static ROSC_t & ROSC     = (*(ROSC_t *)0x40060000);
    static ROSC_t & ROSC_XOR = (*(ROSC_t *)0x40061000);
    static ROSC_t & ROSC_SET = (*(ROSC_t *)0x40062000);
    static ROSC_t & ROSC_CLR = (*(ROSC_t *)0x40063000);

} // _ROSC_

// control and status for on-chip voltage regulator and chip level reset subsystem
namespace _VREG_AND_CHIP_RESET_  {

    // Voltage regulator control and status
    // Reset value: 0x000000b1
    BEGIN_TYPE(VREG_t, uint32_t)
        // regulation status
        // 0=not in regulation, 1=in regulation
        ADD_BITFIELD_RO(ROK, 12, 1)
        // output voltage select
        // 0000 to 0101 - 0.80V
        // 0110         - 0.85V
        // 0111         - 0.90V
        // 1000         - 0.95V
        // 1001         - 1.00V
        // 1010         - 1.05V
        // 1011         - 1.10V (default)
        // 1100         - 1.15V
        // 1101         - 1.20V
        // 1110         - 1.25V
        // 1111         - 1.30V
        ADD_BITFIELD_RW(VSEL, 4, 4)
        // high impedance mode select
        // 0=not in high impedance mode, 1=in high impedance mode
        ADD_BITFIELD_RW(HIZ, 1, 1)
        // enable
        // 0=not enabled, 1=enabled
        ADD_BITFIELD_RW(EN, 0, 1)
    END_TYPE()

    // brown-out detection control
    // Reset value: 0x00000091
    BEGIN_TYPE(BOD_t, uint32_t)
        // threshold select
        // 0000 - 0.473V
        // 0001 - 0.516V
        // 0010 - 0.559V
        // 0011 - 0.602V
        // 0100 - 0.645V
        // 0101 - 0.688V
        // 0110 - 0.731V
        // 0111 - 0.774V
        // 1000 - 0.817V
        // 1001 - 0.860V (default)
        // 1010 - 0.903V
        // 1011 - 0.946V
        // 1100 - 0.989V
        // 1101 - 1.032V
        // 1110 - 1.075V
        // 1111 - 1.118V
        ADD_BITFIELD_RW(VSEL, 4, 4)
        // enable
        // 0=not enabled, 1=enabled
        ADD_BITFIELD_RW(EN, 0, 1)
    END_TYPE()

    // Chip reset control and status
    // Reset value: 0x00000000
    BEGIN_TYPE(CHIP_RESET_t, uint32_t)
        // This is set by psm_restart from the debugger.
        // Its purpose is to branch bootcode to a safe mode when the debugger has issued a psm_restart in order to recover from a boot lock-up.
        // In the safe mode the debugger can repair the boot code, clear this flag then reboot the processor.
        ADD_BITFIELD_RW(PSM_RESTART_FLAG, 24, 1)
        // Last reset was from the debug port
        ADD_BITFIELD_RO(HAD_PSM_RESTART, 20, 1)
        // Last reset was from the RUN pin
        ADD_BITFIELD_RO(HAD_RUN, 16, 1)
        // Last reset was from the power-on reset or brown-out detection blocks
        ADD_BITFIELD_RO(HAD_POR, 8, 1)
    END_TYPE()

    struct VREG_AND_CHIP_RESET_t {
        VREG_t                        VREG;
        BOD_t                         BOD;
        CHIP_RESET_t                  CHIP_RESET;
    };

    static VREG_AND_CHIP_RESET_t & VREG_AND_CHIP_RESET     = (*(VREG_AND_CHIP_RESET_t *)0x40064000);
    static VREG_AND_CHIP_RESET_t & VREG_AND_CHIP_RESET_XOR = (*(VREG_AND_CHIP_RESET_t *)0x40065000);
    static VREG_AND_CHIP_RESET_t & VREG_AND_CHIP_RESET_SET = (*(VREG_AND_CHIP_RESET_t *)0x40066000);
    static VREG_AND_CHIP_RESET_t & VREG_AND_CHIP_RESET_CLR = (*(VREG_AND_CHIP_RESET_t *)0x40067000);

} // _VREG_AND_CHIP_RESET_

// Testbench manager. Allows the programmer to know what platform their software is running on.
namespace _TBMAN_  {

    // Indicates the type of platform in use
    // Reset value: 0x00000005
    BEGIN_TYPE(PLATFORM_t, uint32_t)
        // Indicates the platform is an FPGA
        ADD_BITFIELD_RO(FPGA, 1, 1)
        // Indicates the platform is an ASIC
        ADD_BITFIELD_RO(ASIC, 0, 1)
    END_TYPE()

    struct TBMAN_t {
        PLATFORM_t                    PLATFORM;
    };

    static TBMAN_t & TBMAN     = (*(TBMAN_t *)0x4006c000);
    static TBMAN_t & TBMAN_XOR = (*(TBMAN_t *)0x4006d000);
    static TBMAN_t & TBMAN_SET = (*(TBMAN_t *)0x4006e000);
    static TBMAN_t & TBMAN_CLR = (*(TBMAN_t *)0x4006f000);

} // _TBMAN_

// DMA with separate read and write masters
namespace _DMA_  {

    // DMA Channel 0 Read Address pointer
    // This register updates automatically each time a read completes. The current value is the next address to be read by this channel.
    // Reset value: 0x00000000
    typedef uint32_t CH_READ_ADDR_t;

    // DMA Channel 0 Write Address pointer
    // This register updates automatically each time a write completes. The current value is the next address to be written by this channel.
    // Reset value: 0x00000000
    typedef uint32_t CH_WRITE_ADDR_t;

    // DMA Channel 0 Transfer Count
    // Program the number of bus transfers a channel will perform before halting. Note that, if transfers are larger than one byte in size, this is not equal to the number of bytes transferred (see CTRL_DATA_SIZE).
    // 
    // When the channel is active, reading this register shows the number of transfers remaining, updating automatically each time a write transfer completes.
    // 
    // Writing this register sets the RELOAD value for the transfer counter. Each time this channel is triggered, the RELOAD value is copied into the live transfer counter. The channel can be started multiple times, and will perform the same number of transfers each time, as programmed by most recent write.
    // 
    // The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT is used as a trigger, the written value is used immediately as the length of the new transfer sequence, as well as being written to RELOAD.
    // Reset value: 0x00000000
    typedef uint32_t CH_TRANS_COUNT_t;

    // DMA Channel 0 Control and Status
    // Reset value: 0x00000000
    BEGIN_TYPE(CH_CTRL_TRIG_t, uint32_t)
        // Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel halts when it encounters any bus error, and always raises its channel IRQ flag.
        ADD_BITFIELD_RO(AHB_ERROR, 31, 1)
        // If 1, the channel received a read bus error. Write one to clear.
        // READ_ADDR shows the approximate address where the bus error was encountered (will not to be earlier, or more than 3 transfers later)
        ADD_BITFIELD_RW(READ_ERROR, 30, 1)
        // If 1, the channel received a write bus error. Write one to clear.
        // WRITE_ADDR shows the approximate address where the bus error was encountered (will not to be earlier, or more than 5 transfers later)
        ADD_BITFIELD_RW(WRITE_ERROR, 29, 1)
        // This flag goes high when the channel starts a new transfer sequence, and low when the last transfer of that sequence completes. Clearing EN while BUSY is high pauses the channel, and BUSY will stay high while paused.
        // 
        // To terminate a sequence early (and clear the BUSY flag), see CHAN_ABORT.
        ADD_BITFIELD_RO(BUSY, 24, 1)
        // If 1, this channel's data transfers are visible to the sniff hardware, and each transfer will advance the state of the checksum. This only applies if the sniff hardware is enabled, and has this channel selected.
        // 
        // This allows checksum to be enabled or disabled on a per-control- block basis.
        ADD_BITFIELD_RW(SNIFF_EN, 23, 1)
        // Apply byte-swap transformation to DMA data.
        // For byte data, this has no effect. For halfword data, the two bytes of each halfword are swapped. For word data, the four bytes of each word are swapped to reverse order.
        ADD_BITFIELD_RW(BSWAP, 22, 1)
        // In QUIET mode, the channel does not generate IRQs at the end of every transfer block. Instead, an IRQ is raised when NULL is written to a trigger register, indicating the end of a control block chain.
        // 
        // This reduces the number of interrupts to be serviced by the CPU when transferring a DMA chain of many small control blocks.
        ADD_BITFIELD_RW(IRQ_QUIET, 21, 1)
        // Select a Transfer Request signal.
        // The channel uses the transfer request signal to pace its data transfer rate. Sources for TREQ signals are internal (TIMERS) or external (DREQ, a Data Request from the system).
        // 0x0 to 0x3a -> select DREQ n as TREQ
        ADD_BITFIELD_RW(TREQ_SEL, 15, 6)
        // When this channel completes, it will trigger the channel indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this channel)_.
        ADD_BITFIELD_RW(CHAIN_TO, 11, 4)
        // Select whether RING_SIZE applies to read or write addresses.
        // If 0, read addresses are wrapped on a (1 << RING_SIZE) boundary. If 1, write addresses are wrapped.
        ADD_BITFIELD_RW(RING_SEL, 10, 1)
        // Size of address wrap region. If 0, don't wrap. For values n > 0, only the lower n bits of the address will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned ring buffers.
        // 
        // Ring sizes between 2 and 32768 bytes are possible. This can apply to either read or write addresses, based on value of RING_SEL.
        ADD_BITFIELD_RW(RING_SIZE, 6, 4)
        // If 1, the write address increments with each transfer. If 0, each write is directed to the same, initial address.
        // 
        // Generally this should be disabled for memory-to-peripheral transfers.
        ADD_BITFIELD_RW(INCR_WRITE, 5, 1)
        // If 1, the read address increments with each transfer. If 0, each read is directed to the same, initial address.
        // 
        // Generally this should be disabled for peripheral-to-memory transfers.
        ADD_BITFIELD_RW(INCR_READ, 4, 1)
        // Set the size of each bus transfer (byte/halfword/word). READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes) with each transfer.
        ADD_BITFIELD_RW(DATA_SIZE, 2, 2)
        // HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in each scheduling round, all high priority channels are considered first, and then only a single low priority channel, before returning to the high priority channels.
        // 
        // This only affects the order in which the DMA schedules channels. The DMA's bus priority is not changed. If the DMA is not saturated then a low priority channel will see no loss of throughput.
        ADD_BITFIELD_RW(HIGH_PRIORITY, 1, 1)
        // DMA Channel Enable.
        // When 1, the channel will respond to triggering events, which will cause it to become BUSY and start transferring data. When 0, the channel will ignore triggers, stop issuing transfers, and pause the current transfer sequence (i.e. BUSY will remain high if already high)
        ADD_BITFIELD_RW(EN, 0, 1)
    END_TYPE()

    // Select Timer 0 as TREQ
    static const uint32_t CH_CTRL_TRIG_TREQ_SEL__TIMER0 = 59;
    // Select Timer 1 as TREQ
    static const uint32_t CH_CTRL_TRIG_TREQ_SEL__TIMER1 = 60;
    // Select Timer 2 as TREQ (Optional)
    static const uint32_t CH_CTRL_TRIG_TREQ_SEL__TIMER2 = 61;
    // Select Timer 3 as TREQ (Optional)
    static const uint32_t CH_CTRL_TRIG_TREQ_SEL__TIMER3 = 62;
    // Permanent request, for unpaced transfers.
    static const uint32_t CH_CTRL_TRIG_TREQ_SEL__PERMANENT = 63;
    static const uint32_t CH_CTRL_TRIG_RING_SIZE__RING_NONE = 0;
    static const uint32_t CH_CTRL_TRIG_DATA_SIZE__SIZE_BYTE = 0;
    static const uint32_t CH_CTRL_TRIG_DATA_SIZE__SIZE_HALFWORD = 1;
    static const uint32_t CH_CTRL_TRIG_DATA_SIZE__SIZE_WORD = 2;

    // Alias for channel 0 CTRL register
    // Reset value: 0x00000000
    typedef uint32_t CH_AL1_CTRL_t;

    // Alias for channel 0 READ_ADDR register
    // Reset value: 0x00000000
    typedef uint32_t CH_AL1_READ_ADDR_t;

    // Alias for channel 0 WRITE_ADDR register
    // Reset value: 0x00000000
    typedef uint32_t CH_AL1_WRITE_ADDR_t;

    // Alias for channel 0 TRANS_COUNT register
    // This is a trigger register (0xc). Writing a nonzero value will
    // reload the channel counter and start the channel.
    // Reset value: 0x00000000
    typedef uint32_t CH_AL1_TRANS_COUNT_TRIG_t;

    // Alias for channel 0 CTRL register
    // Reset value: 0x00000000
    typedef uint32_t CH_AL2_CTRL_t;

    // Alias for channel 0 TRANS_COUNT register
    // Reset value: 0x00000000
    typedef uint32_t CH_AL2_TRANS_COUNT_t;

    // Alias for channel 0 READ_ADDR register
    // Reset value: 0x00000000
    typedef uint32_t CH_AL2_READ_ADDR_t;

    // Alias for channel 0 WRITE_ADDR register
    // This is a trigger register (0xc). Writing a nonzero value will
    // reload the channel counter and start the channel.
    // Reset value: 0x00000000
    typedef uint32_t CH_AL2_WRITE_ADDR_TRIG_t;

    // Alias for channel 0 CTRL register
    // Reset value: 0x00000000
    typedef uint32_t CH_AL3_CTRL_t;

    // Alias for channel 0 WRITE_ADDR register
    // Reset value: 0x00000000
    typedef uint32_t CH_AL3_WRITE_ADDR_t;

    // Alias for channel 0 TRANS_COUNT register
    // Reset value: 0x00000000
    typedef uint32_t CH_AL3_TRANS_COUNT_t;

    // Alias for channel 0 READ_ADDR register
    // This is a trigger register (0xc). Writing a nonzero value will
    // reload the channel counter and start the channel.
    // Reset value: 0x00000000
    typedef uint32_t CH_AL3_READ_ADDR_TRIG_t;

    // Interrupt Status (raw)
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR_t, uint32_t)
        // Raw interrupt status for DMA Channels 0..15. Bit n corresponds to channel n. Ignores any masking or forcing. Channel interrupts can be cleared by writing a bit mask to INTR, INTS0 or INTS1.
        // 
        // Channel interrupts can be routed to either of two system-level IRQs based on INTE0 and INTE1.
        // 
        // This can be used vector different channel interrupts to different ISRs: this might be done to allow NVIC IRQ preemption for more time-critical channels, or to spread IRQ load across different cores.
        // 
        // It is also valid to ignore this behaviour and just use INTE0/INTS0/IRQ 0.
        ADD_BITFIELD_RO(INTR, 0, 16)
    END_TYPE()

    // Interrupt Enables for IRQ 0
    // Reset value: 0x00000000
    BEGIN_TYPE(INTE0_t, uint32_t)
        // Set bit n to pass interrupts from channel n to DMA IRQ 0.
        ADD_BITFIELD_RW(INTE0, 0, 16)
    END_TYPE()

    // Force Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTF0_t, uint32_t)
        // Write 1s to force the corresponding bits in INTE0. The interrupt remains asserted until INTF0 is cleared.
        ADD_BITFIELD_RW(INTF0, 0, 16)
    END_TYPE()

    // Interrupt Status for IRQ 0
    // Reset value: 0x00000000
    BEGIN_TYPE(INTS0_t, uint32_t)
        // Indicates active channel interrupt requests which are currently causing IRQ 0 to be asserted.
        // Channel interrupts can be cleared by writing a bit mask here.
        ADD_BITFIELD_RW(INTS0, 0, 16)
    END_TYPE()

    // Interrupt Enables for IRQ 1
    // Reset value: 0x00000000
    BEGIN_TYPE(INTE1_t, uint32_t)
        // Set bit n to pass interrupts from channel n to DMA IRQ 1.
        ADD_BITFIELD_RW(INTE1, 0, 16)
    END_TYPE()

    // Force Interrupts for IRQ 1
    // Reset value: 0x00000000
    BEGIN_TYPE(INTF1_t, uint32_t)
        // Write 1s to force the corresponding bits in INTE0. The interrupt remains asserted until INTF0 is cleared.
        ADD_BITFIELD_RW(INTF1, 0, 16)
    END_TYPE()

    // Interrupt Status (masked) for IRQ 1
    // Reset value: 0x00000000
    BEGIN_TYPE(INTS1_t, uint32_t)
        // Indicates active channel interrupt requests which are currently causing IRQ 1 to be asserted.
        // Channel interrupts can be cleared by writing a bit mask here.
        ADD_BITFIELD_RW(INTS1, 0, 16)
    END_TYPE()

    // Pacing (X/Y) Fractional Timer
    // The pacing timer produces TREQ assertions at a rate set by ((X/Y) * sys_clk). This equation is evaluated every sys_clk cycles and therefore can only generate TREQs at a rate of 1 per sys_clk (i.e. permanent TREQ) or less.
    // Reset value: 0x00000000
    BEGIN_TYPE(TIMER_t, uint32_t)
        // Pacing Timer Dividend. Specifies the X value for the (X/Y) fractional timer.
        ADD_BITFIELD_RW(X, 16, 16)
        // Pacing Timer Divisor. Specifies the Y value for the (X/Y) fractional timer.
        ADD_BITFIELD_RW(Y, 0, 16)
    END_TYPE()

    // Trigger one or more channels simultaneously
    // Reset value: 0x00000000
    BEGIN_TYPE(MULTI_CHAN_TRIGGER_t, uint32_t)
        // Each bit in this register corresponds to a DMA channel. Writing a 1 to the relevant bit is the same as writing to that channel's trigger register; the channel will start if it is currently enabled and not already busy.
        ADD_BITFIELD_RW(MULTI_CHAN_TRIGGER, 0, 16)
    END_TYPE()

    // Sniffer Control
    // Reset value: 0x00000000
    BEGIN_TYPE(SNIFF_CTRL_t, uint32_t)
        // If set, the result appears inverted (bitwise complement) when read. This does not affect the way the checksum is calculated; the result is transformed on-the-fly between the result register and the bus.
        ADD_BITFIELD_RW(OUT_INV, 11, 1)
        // If set, the result appears bit-reversed when read. This does not affect the way the checksum is calculated; the result is transformed on-the-fly between the result register and the bus.
        ADD_BITFIELD_RW(OUT_REV, 10, 1)
        // Locally perform a byte reverse on the sniffed data, before feeding into checksum.
        // 
        // Note that the sniff hardware is downstream of the DMA channel byteswap performed in the read master: if channel CTRL_BSWAP and SNIFF_CTRL_BSWAP are both enabled, their effects cancel from the sniffer's point of view.
        ADD_BITFIELD_RW(BSWAP, 9, 1)
        ADD_BITFIELD_RW(CALC, 5, 4)
        // DMA channel for Sniffer to observe
        ADD_BITFIELD_RW(DMACH, 1, 4)
        // Enable sniffer
        ADD_BITFIELD_RW(EN, 0, 1)
    END_TYPE()

    // Calculate a CRC-32 (IEEE802.3 polynomial)
    static const uint32_t SNIFF_CTRL_CALC__CRC32 = 0;
    // Calculate a CRC-32 (IEEE802.3 polynomial) with bit reversed data
    static const uint32_t SNIFF_CTRL_CALC__CRC32R = 1;
    // Calculate a CRC-16-CCITT
    static const uint32_t SNIFF_CTRL_CALC__CRC16 = 2;
    // Calculate a CRC-16-CCITT with bit reversed data
    static const uint32_t SNIFF_CTRL_CALC__CRC16R = 3;
    // XOR reduction over all data. == 1 if the total 1 population count is odd.
    static const uint32_t SNIFF_CTRL_CALC__EVEN = 14;
    // Calculate a simple 32-bit checksum (addition with a 32 bit accumulator)
    static const uint32_t SNIFF_CTRL_CALC__SUM = 15;

    // Data accumulator for sniff hardware
    // Write an initial seed value here before starting a DMA transfer on the channel indicated by SNIFF_CTRL_DMACH. The hardware will update this register each time it observes a read from the indicated channel. Once the channel completes, the final result can be read from this register.
    // Reset value: 0x00000000
    typedef uint32_t SNIFF_DATA_t;

    // Debug RAF, WAF, TDF levels
    // Reset value: 0x00000000
    BEGIN_TYPE(FIFO_LEVELS_t, uint32_t)
        // Current Read-Address-FIFO fill level
        ADD_BITFIELD_RO(RAF_LVL, 16, 8)
        // Current Write-Address-FIFO fill level
        ADD_BITFIELD_RO(WAF_LVL, 8, 8)
        // Current Transfer-Data-FIFO fill level
        ADD_BITFIELD_RO(TDF_LVL, 0, 8)
    END_TYPE()

    // Abort an in-progress transfer sequence on one or more channels
    // Reset value: 0x00000000
    BEGIN_TYPE(CHAN_ABORT_t, uint32_t)
        // Each bit corresponds to a channel. Writing a 1 aborts whatever transfer sequence is in progress on that channel. The bit will remain high until any in-flight transfers have been flushed through the address and data FIFOs.
        // 
        // After writing, this register must be polled until it returns all-zero. Until this point, it is unsafe to restart the channel.
        ADD_BITFIELD_RW(CHAN_ABORT, 0, 16)
    END_TYPE()

    // The number of channels this DMA instance is equipped with. This DMA supports up to 16 hardware channels, but can be configured with as few as one, to minimise silicon area.
    // Reset value: 0x00000000
    BEGIN_TYPE(N_CHANNELS_t, uint32_t)
        ADD_BITFIELD_RO(N_CHANNELS, 0, 5)
    END_TYPE()

    // Read: get channel DREQ counter (i.e. how many accesses the DMA expects it can perform on the peripheral without overflow/underflow. Write any value: clears the counter, and cause channel to re-initiate DREQ handshake.
    // Reset value: 0x00000000
    BEGIN_TYPE(CH_DBG_CTDREQ_t, uint32_t)
        ADD_BITFIELD_RW(DBG_CTDREQ, 0, 6)
    END_TYPE()

    // Read to get channel TRANS_COUNT reload value, i.e. the length of the next transfer
    // Reset value: 0x00000000
    typedef uint32_t CH_DBG_TCR_t;

    struct DMA_t {
        CH_READ_ADDR_t                CH0_READ_ADDR;
        CH_WRITE_ADDR_t               CH0_WRITE_ADDR;
        CH_TRANS_COUNT_t              CH0_TRANS_COUNT;
        CH_CTRL_TRIG_t                CH0_CTRL_TRIG;
        CH_AL1_CTRL_t                 CH0_AL1_CTRL;
        CH_AL1_READ_ADDR_t            CH0_AL1_READ_ADDR;
        CH_AL1_WRITE_ADDR_t           CH0_AL1_WRITE_ADDR;
        CH_AL1_TRANS_COUNT_TRIG_t     CH0_AL1_TRANS_COUNT_TRIG;
        CH_AL2_CTRL_t                 CH0_AL2_CTRL;
        CH_AL2_TRANS_COUNT_t          CH0_AL2_TRANS_COUNT;
        CH_AL2_READ_ADDR_t            CH0_AL2_READ_ADDR;
        CH_AL2_WRITE_ADDR_TRIG_t      CH0_AL2_WRITE_ADDR_TRIG;
        CH_AL3_CTRL_t                 CH0_AL3_CTRL;
        CH_AL3_WRITE_ADDR_t           CH0_AL3_WRITE_ADDR;
        CH_AL3_TRANS_COUNT_t          CH0_AL3_TRANS_COUNT;
        CH_AL3_READ_ADDR_TRIG_t       CH0_AL3_READ_ADDR_TRIG;
        CH_READ_ADDR_t                CH1_READ_ADDR;
        CH_WRITE_ADDR_t               CH1_WRITE_ADDR;
        CH_TRANS_COUNT_t              CH1_TRANS_COUNT;
        CH_CTRL_TRIG_t                CH1_CTRL_TRIG;
        CH_AL1_CTRL_t                 CH1_AL1_CTRL;
        CH_AL1_READ_ADDR_t            CH1_AL1_READ_ADDR;
        CH_AL1_WRITE_ADDR_t           CH1_AL1_WRITE_ADDR;
        CH_AL1_TRANS_COUNT_TRIG_t     CH1_AL1_TRANS_COUNT_TRIG;
        CH_AL2_CTRL_t                 CH1_AL2_CTRL;
        CH_AL2_TRANS_COUNT_t          CH1_AL2_TRANS_COUNT;
        CH_AL2_READ_ADDR_t            CH1_AL2_READ_ADDR;
        CH_AL2_WRITE_ADDR_TRIG_t      CH1_AL2_WRITE_ADDR_TRIG;
        CH_AL3_CTRL_t                 CH1_AL3_CTRL;
        CH_AL3_WRITE_ADDR_t           CH1_AL3_WRITE_ADDR;
        CH_AL3_TRANS_COUNT_t          CH1_AL3_TRANS_COUNT;
        CH_AL3_READ_ADDR_TRIG_t       CH1_AL3_READ_ADDR_TRIG;
        CH_READ_ADDR_t                CH2_READ_ADDR;
        CH_WRITE_ADDR_t               CH2_WRITE_ADDR;
        CH_TRANS_COUNT_t              CH2_TRANS_COUNT;
        CH_CTRL_TRIG_t                CH2_CTRL_TRIG;
        CH_AL1_CTRL_t                 CH2_AL1_CTRL;
        CH_AL1_READ_ADDR_t            CH2_AL1_READ_ADDR;
        CH_AL1_WRITE_ADDR_t           CH2_AL1_WRITE_ADDR;
        CH_AL1_TRANS_COUNT_TRIG_t     CH2_AL1_TRANS_COUNT_TRIG;
        CH_AL2_CTRL_t                 CH2_AL2_CTRL;
        CH_AL2_TRANS_COUNT_t          CH2_AL2_TRANS_COUNT;
        CH_AL2_READ_ADDR_t            CH2_AL2_READ_ADDR;
        CH_AL2_WRITE_ADDR_TRIG_t      CH2_AL2_WRITE_ADDR_TRIG;
        CH_AL3_CTRL_t                 CH2_AL3_CTRL;
        CH_AL3_WRITE_ADDR_t           CH2_AL3_WRITE_ADDR;
        CH_AL3_TRANS_COUNT_t          CH2_AL3_TRANS_COUNT;
        CH_AL3_READ_ADDR_TRIG_t       CH2_AL3_READ_ADDR_TRIG;
        CH_READ_ADDR_t                CH3_READ_ADDR;
        CH_WRITE_ADDR_t               CH3_WRITE_ADDR;
        CH_TRANS_COUNT_t              CH3_TRANS_COUNT;
        CH_CTRL_TRIG_t                CH3_CTRL_TRIG;
        CH_AL1_CTRL_t                 CH3_AL1_CTRL;
        CH_AL1_READ_ADDR_t            CH3_AL1_READ_ADDR;
        CH_AL1_WRITE_ADDR_t           CH3_AL1_WRITE_ADDR;
        CH_AL1_TRANS_COUNT_TRIG_t     CH3_AL1_TRANS_COUNT_TRIG;
        CH_AL2_CTRL_t                 CH3_AL2_CTRL;
        CH_AL2_TRANS_COUNT_t          CH3_AL2_TRANS_COUNT;
        CH_AL2_READ_ADDR_t            CH3_AL2_READ_ADDR;
        CH_AL2_WRITE_ADDR_TRIG_t      CH3_AL2_WRITE_ADDR_TRIG;
        CH_AL3_CTRL_t                 CH3_AL3_CTRL;
        CH_AL3_WRITE_ADDR_t           CH3_AL3_WRITE_ADDR;
        CH_AL3_TRANS_COUNT_t          CH3_AL3_TRANS_COUNT;
        CH_AL3_READ_ADDR_TRIG_t       CH3_AL3_READ_ADDR_TRIG;
        CH_READ_ADDR_t                CH4_READ_ADDR;
        CH_WRITE_ADDR_t               CH4_WRITE_ADDR;
        CH_TRANS_COUNT_t              CH4_TRANS_COUNT;
        CH_CTRL_TRIG_t                CH4_CTRL_TRIG;
        CH_AL1_CTRL_t                 CH4_AL1_CTRL;
        CH_AL1_READ_ADDR_t            CH4_AL1_READ_ADDR;
        CH_AL1_WRITE_ADDR_t           CH4_AL1_WRITE_ADDR;
        CH_AL1_TRANS_COUNT_TRIG_t     CH4_AL1_TRANS_COUNT_TRIG;
        CH_AL2_CTRL_t                 CH4_AL2_CTRL;
        CH_AL2_TRANS_COUNT_t          CH4_AL2_TRANS_COUNT;
        CH_AL2_READ_ADDR_t            CH4_AL2_READ_ADDR;
        CH_AL2_WRITE_ADDR_TRIG_t      CH4_AL2_WRITE_ADDR_TRIG;
        CH_AL3_CTRL_t                 CH4_AL3_CTRL;
        CH_AL3_WRITE_ADDR_t           CH4_AL3_WRITE_ADDR;
        CH_AL3_TRANS_COUNT_t          CH4_AL3_TRANS_COUNT;
        CH_AL3_READ_ADDR_TRIG_t       CH4_AL3_READ_ADDR_TRIG;
        CH_READ_ADDR_t                CH5_READ_ADDR;
        CH_WRITE_ADDR_t               CH5_WRITE_ADDR;
        CH_TRANS_COUNT_t              CH5_TRANS_COUNT;
        CH_CTRL_TRIG_t                CH5_CTRL_TRIG;
        CH_AL1_CTRL_t                 CH5_AL1_CTRL;
        CH_AL1_READ_ADDR_t            CH5_AL1_READ_ADDR;
        CH_AL1_WRITE_ADDR_t           CH5_AL1_WRITE_ADDR;
        CH_AL1_TRANS_COUNT_TRIG_t     CH5_AL1_TRANS_COUNT_TRIG;
        CH_AL2_CTRL_t                 CH5_AL2_CTRL;
        CH_AL2_TRANS_COUNT_t          CH5_AL2_TRANS_COUNT;
        CH_AL2_READ_ADDR_t            CH5_AL2_READ_ADDR;
        CH_AL2_WRITE_ADDR_TRIG_t      CH5_AL2_WRITE_ADDR_TRIG;
        CH_AL3_CTRL_t                 CH5_AL3_CTRL;
        CH_AL3_WRITE_ADDR_t           CH5_AL3_WRITE_ADDR;
        CH_AL3_TRANS_COUNT_t          CH5_AL3_TRANS_COUNT;
        CH_AL3_READ_ADDR_TRIG_t       CH5_AL3_READ_ADDR_TRIG;
        CH_READ_ADDR_t                CH6_READ_ADDR;
        CH_WRITE_ADDR_t               CH6_WRITE_ADDR;
        CH_TRANS_COUNT_t              CH6_TRANS_COUNT;
        CH_CTRL_TRIG_t                CH6_CTRL_TRIG;
        CH_AL1_CTRL_t                 CH6_AL1_CTRL;
        CH_AL1_READ_ADDR_t            CH6_AL1_READ_ADDR;
        CH_AL1_WRITE_ADDR_t           CH6_AL1_WRITE_ADDR;
        CH_AL1_TRANS_COUNT_TRIG_t     CH6_AL1_TRANS_COUNT_TRIG;
        CH_AL2_CTRL_t                 CH6_AL2_CTRL;
        CH_AL2_TRANS_COUNT_t          CH6_AL2_TRANS_COUNT;
        CH_AL2_READ_ADDR_t            CH6_AL2_READ_ADDR;
        CH_AL2_WRITE_ADDR_TRIG_t      CH6_AL2_WRITE_ADDR_TRIG;
        CH_AL3_CTRL_t                 CH6_AL3_CTRL;
        CH_AL3_WRITE_ADDR_t           CH6_AL3_WRITE_ADDR;
        CH_AL3_TRANS_COUNT_t          CH6_AL3_TRANS_COUNT;
        CH_AL3_READ_ADDR_TRIG_t       CH6_AL3_READ_ADDR_TRIG;
        CH_READ_ADDR_t                CH7_READ_ADDR;
        CH_WRITE_ADDR_t               CH7_WRITE_ADDR;
        CH_TRANS_COUNT_t              CH7_TRANS_COUNT;
        CH_CTRL_TRIG_t                CH7_CTRL_TRIG;
        CH_AL1_CTRL_t                 CH7_AL1_CTRL;
        CH_AL1_READ_ADDR_t            CH7_AL1_READ_ADDR;
        CH_AL1_WRITE_ADDR_t           CH7_AL1_WRITE_ADDR;
        CH_AL1_TRANS_COUNT_TRIG_t     CH7_AL1_TRANS_COUNT_TRIG;
        CH_AL2_CTRL_t                 CH7_AL2_CTRL;
        CH_AL2_TRANS_COUNT_t          CH7_AL2_TRANS_COUNT;
        CH_AL2_READ_ADDR_t            CH7_AL2_READ_ADDR;
        CH_AL2_WRITE_ADDR_TRIG_t      CH7_AL2_WRITE_ADDR_TRIG;
        CH_AL3_CTRL_t                 CH7_AL3_CTRL;
        CH_AL3_WRITE_ADDR_t           CH7_AL3_WRITE_ADDR;
        CH_AL3_TRANS_COUNT_t          CH7_AL3_TRANS_COUNT;
        CH_AL3_READ_ADDR_TRIG_t       CH7_AL3_READ_ADDR_TRIG;
        CH_READ_ADDR_t                CH8_READ_ADDR;
        CH_WRITE_ADDR_t               CH8_WRITE_ADDR;
        CH_TRANS_COUNT_t              CH8_TRANS_COUNT;
        CH_CTRL_TRIG_t                CH8_CTRL_TRIG;
        CH_AL1_CTRL_t                 CH8_AL1_CTRL;
        CH_AL1_READ_ADDR_t            CH8_AL1_READ_ADDR;
        CH_AL1_WRITE_ADDR_t           CH8_AL1_WRITE_ADDR;
        CH_AL1_TRANS_COUNT_TRIG_t     CH8_AL1_TRANS_COUNT_TRIG;
        CH_AL2_CTRL_t                 CH8_AL2_CTRL;
        CH_AL2_TRANS_COUNT_t          CH8_AL2_TRANS_COUNT;
        CH_AL2_READ_ADDR_t            CH8_AL2_READ_ADDR;
        CH_AL2_WRITE_ADDR_TRIG_t      CH8_AL2_WRITE_ADDR_TRIG;
        CH_AL3_CTRL_t                 CH8_AL3_CTRL;
        CH_AL3_WRITE_ADDR_t           CH8_AL3_WRITE_ADDR;
        CH_AL3_TRANS_COUNT_t          CH8_AL3_TRANS_COUNT;
        CH_AL3_READ_ADDR_TRIG_t       CH8_AL3_READ_ADDR_TRIG;
        CH_READ_ADDR_t                CH9_READ_ADDR;
        CH_WRITE_ADDR_t               CH9_WRITE_ADDR;
        CH_TRANS_COUNT_t              CH9_TRANS_COUNT;
        CH_CTRL_TRIG_t                CH9_CTRL_TRIG;
        CH_AL1_CTRL_t                 CH9_AL1_CTRL;
        CH_AL1_READ_ADDR_t            CH9_AL1_READ_ADDR;
        CH_AL1_WRITE_ADDR_t           CH9_AL1_WRITE_ADDR;
        CH_AL1_TRANS_COUNT_TRIG_t     CH9_AL1_TRANS_COUNT_TRIG;
        CH_AL2_CTRL_t                 CH9_AL2_CTRL;
        CH_AL2_TRANS_COUNT_t          CH9_AL2_TRANS_COUNT;
        CH_AL2_READ_ADDR_t            CH9_AL2_READ_ADDR;
        CH_AL2_WRITE_ADDR_TRIG_t      CH9_AL2_WRITE_ADDR_TRIG;
        CH_AL3_CTRL_t                 CH9_AL3_CTRL;
        CH_AL3_WRITE_ADDR_t           CH9_AL3_WRITE_ADDR;
        CH_AL3_TRANS_COUNT_t          CH9_AL3_TRANS_COUNT;
        CH_AL3_READ_ADDR_TRIG_t       CH9_AL3_READ_ADDR_TRIG;
        CH_READ_ADDR_t                CH10_READ_ADDR;
        CH_WRITE_ADDR_t               CH10_WRITE_ADDR;
        CH_TRANS_COUNT_t              CH10_TRANS_COUNT;
        CH_CTRL_TRIG_t                CH10_CTRL_TRIG;
        CH_AL1_CTRL_t                 CH10_AL1_CTRL;
        CH_AL1_READ_ADDR_t            CH10_AL1_READ_ADDR;
        CH_AL1_WRITE_ADDR_t           CH10_AL1_WRITE_ADDR;
        CH_AL1_TRANS_COUNT_TRIG_t     CH10_AL1_TRANS_COUNT_TRIG;
        CH_AL2_CTRL_t                 CH10_AL2_CTRL;
        CH_AL2_TRANS_COUNT_t          CH10_AL2_TRANS_COUNT;
        CH_AL2_READ_ADDR_t            CH10_AL2_READ_ADDR;
        CH_AL2_WRITE_ADDR_TRIG_t      CH10_AL2_WRITE_ADDR_TRIG;
        CH_AL3_CTRL_t                 CH10_AL3_CTRL;
        CH_AL3_WRITE_ADDR_t           CH10_AL3_WRITE_ADDR;
        CH_AL3_TRANS_COUNT_t          CH10_AL3_TRANS_COUNT;
        CH_AL3_READ_ADDR_TRIG_t       CH10_AL3_READ_ADDR_TRIG;
        CH_READ_ADDR_t                CH11_READ_ADDR;
        CH_WRITE_ADDR_t               CH11_WRITE_ADDR;
        CH_TRANS_COUNT_t              CH11_TRANS_COUNT;
        CH_CTRL_TRIG_t                CH11_CTRL_TRIG;
        CH_AL1_CTRL_t                 CH11_AL1_CTRL;
        CH_AL1_READ_ADDR_t            CH11_AL1_READ_ADDR;
        CH_AL1_WRITE_ADDR_t           CH11_AL1_WRITE_ADDR;
        CH_AL1_TRANS_COUNT_TRIG_t     CH11_AL1_TRANS_COUNT_TRIG;
        CH_AL2_CTRL_t                 CH11_AL2_CTRL;
        CH_AL2_TRANS_COUNT_t          CH11_AL2_TRANS_COUNT;
        CH_AL2_READ_ADDR_t            CH11_AL2_READ_ADDR;
        CH_AL2_WRITE_ADDR_TRIG_t      CH11_AL2_WRITE_ADDR_TRIG;
        CH_AL3_CTRL_t                 CH11_AL3_CTRL;
        CH_AL3_WRITE_ADDR_t           CH11_AL3_WRITE_ADDR;
        CH_AL3_TRANS_COUNT_t          CH11_AL3_TRANS_COUNT;
        CH_AL3_READ_ADDR_TRIG_t       CH11_AL3_READ_ADDR_TRIG;
        uint32_t                      reserved0[64];
        INTR_t                        INTR;
        INTE0_t                       INTE0;
        INTF0_t                       INTF0;
        INTS0_t                       INTS0;
        uint32_t                      reserved1;
        INTE1_t                       INTE1;
        INTF1_t                       INTF1;
        INTS1_t                       INTS1;
        TIMER_t                       TIMER[4];
        MULTI_CHAN_TRIGGER_t          MULTI_CHAN_TRIGGER;
        SNIFF_CTRL_t                  SNIFF_CTRL;
        SNIFF_DATA_t                  SNIFF_DATA;
        uint32_t                      reserved2;
        FIFO_LEVELS_t                 FIFO_LEVELS;
        CHAN_ABORT_t                  CHAN_ABORT;
        N_CHANNELS_t                  N_CHANNELS;
        uint32_t                      reserved3[237];
        CH_DBG_CTDREQ_t               CH0_DBG_CTDREQ;
        CH_DBG_TCR_t                  CH0_DBG_TCR;
        uint32_t                      reserved4[14];
        CH_DBG_CTDREQ_t               CH1_DBG_CTDREQ;
        CH_DBG_TCR_t                  CH1_DBG_TCR;
        uint32_t                      reserved5[14];
        CH_DBG_CTDREQ_t               CH2_DBG_CTDREQ;
        CH_DBG_TCR_t                  CH2_DBG_TCR;
        uint32_t                      reserved6[14];
        CH_DBG_CTDREQ_t               CH3_DBG_CTDREQ;
        CH_DBG_TCR_t                  CH3_DBG_TCR;
        uint32_t                      reserved7[14];
        CH_DBG_CTDREQ_t               CH4_DBG_CTDREQ;
        CH_DBG_TCR_t                  CH4_DBG_TCR;
        uint32_t                      reserved8[14];
        CH_DBG_CTDREQ_t               CH5_DBG_CTDREQ;
        CH_DBG_TCR_t                  CH5_DBG_TCR;
        uint32_t                      reserved9[14];
        CH_DBG_CTDREQ_t               CH6_DBG_CTDREQ;
        CH_DBG_TCR_t                  CH6_DBG_TCR;
        uint32_t                      reserved10[14];
        CH_DBG_CTDREQ_t               CH7_DBG_CTDREQ;
        CH_DBG_TCR_t                  CH7_DBG_TCR;
        uint32_t                      reserved11[14];
        CH_DBG_CTDREQ_t               CH8_DBG_CTDREQ;
        CH_DBG_TCR_t                  CH8_DBG_TCR;
        uint32_t                      reserved12[14];
        CH_DBG_CTDREQ_t               CH9_DBG_CTDREQ;
        CH_DBG_TCR_t                  CH9_DBG_TCR;
        uint32_t                      reserved13[14];
        CH_DBG_CTDREQ_t               CH10_DBG_CTDREQ;
        CH_DBG_TCR_t                  CH10_DBG_TCR;
        uint32_t                      reserved14[14];
        CH_DBG_CTDREQ_t               CH11_DBG_CTDREQ;
        CH_DBG_TCR_t                  CH11_DBG_TCR;
    };

    static DMA_t & DMA     = (*(DMA_t *)0x50000000);
    static DMA_t & DMA_XOR = (*(DMA_t *)0x50001000);
    static DMA_t & DMA_SET = (*(DMA_t *)0x50002000);
    static DMA_t & DMA_CLR = (*(DMA_t *)0x50003000);

} // _DMA_

// DPRAM layout for USB device.
namespace _USBCTRL_DPRAM_  {

    // Bytes 0-3 of the SETUP packet from the host.
    // Reset value: 0x00000000
    BEGIN_TYPE(SETUP_PACKET_LOW_t, uint32_t)
        ADD_BITFIELD_RW(WVALUE, 16, 16)
        ADD_BITFIELD_RW(BREQUEST, 8, 8)
        ADD_BITFIELD_RW(BMREQUESTTYPE, 0, 8)
    END_TYPE()

    // Bytes 4-7 of the setup packet from the host.
    // Reset value: 0x00000000
    BEGIN_TYPE(SETUP_PACKET_HIGH_t, uint32_t)
        ADD_BITFIELD_RW(WLENGTH, 16, 16)
        ADD_BITFIELD_RW(WINDEX, 0, 16)
    END_TYPE()

    // Reset value: 0x00000000
    BEGIN_TYPE(EP_CONTROL_t, uint32_t)
        // Enable this endpoint. The device will not reply to any packets for this endpoint if this bit is not set.
        ADD_BITFIELD_RW(ENABLE, 31, 1)
        // This endpoint is double buffered.
        ADD_BITFIELD_RW(DOUBLE_BUFFERED, 30, 1)
        // Trigger an interrupt each time a buffer is done.
        ADD_BITFIELD_RW(INTERRUPT_PER_BUFF, 29, 1)
        // Trigger an interrupt each time both buffers are done. Only valid in double buffered mode.
        ADD_BITFIELD_RW(INTERRUPT_PER_DOUBLE_BUFF, 28, 1)
        ADD_BITFIELD_RW(ENDPOINT_TYPE, 26, 2)
        // Trigger an interrupt if a STALL is sent. Intended for debug only.
        ADD_BITFIELD_RW(INTERRUPT_ON_STALL, 17, 1)
        // Trigger an interrupt if a NAK is sent. Intended for debug only.
        ADD_BITFIELD_RW(INTERRUPT_ON_NAK, 16, 1)
        // 64 byte aligned buffer address for this EP (bits 0-5 are ignored). Relative to the start of the DPRAM.
        ADD_BITFIELD_RW(BUFFER_ADDRESS, 0, 16)
    END_TYPE()

    static const uint32_t EP_CONTROL_ENDPOINT_TYPE__Control = 0;
    static const uint32_t EP_CONTROL_ENDPOINT_TYPE__Isochronous = 1;
    static const uint32_t EP_CONTROL_ENDPOINT_TYPE__Bulk = 2;
    static const uint32_t EP_CONTROL_ENDPOINT_TYPE__Interrupt = 3;

    // Buffer control for both buffers of an endpoint. Fields ending in a _1 are for buffer 1.
    // Fields ending in a _0 are for buffer 0. Buffer 1 controls are only valid if the endpoint is in double buffered mode.
    // Reset value: 0x00000000
    BEGIN_TYPE(EP_BUFFER_CONTROL_t, uint32_t)
        // Buffer 1 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. The host will set it when it has filled the buffer with data.
        ADD_BITFIELD_RW(FULL_1, 31, 1)
        // Buffer 1 is the last buffer of the transfer.
        ADD_BITFIELD_RW(LAST_1, 30, 1)
        // The data pid of buffer 1.
        ADD_BITFIELD_RW(PID_1, 29, 1)
        // The number of bytes buffer 1 is offset from buffer 0 in Isochronous mode. Only valid in double buffered mode for an Isochronous endpoint.
        // For a non Isochronous endpoint the offset is always 64 bytes.
        ADD_BITFIELD_RW(DOUBLE_BUFFER_ISO_OFFSET, 27, 2)
        // Buffer 1 is available. This bit is set to indicate the buffer can be used by the controller. The controller clears the available bit when writing the status back.
        ADD_BITFIELD_RW(AVAILABLE_1, 26, 1)
        // The length of the data in buffer 1.
        ADD_BITFIELD_RW(LENGTH_1, 16, 10)
        // Buffer 0 is full. For an IN transfer (TX to the host) the bit is set to indicate the data is valid. For an OUT transfer (RX from the host) this bit should be left as a 0. The host will set it when it has filled the buffer with data.
        ADD_BITFIELD_RW(FULL_0, 15, 1)
        // Buffer 0 is the last buffer of the transfer.
        ADD_BITFIELD_RW(LAST_0, 14, 1)
        // The data pid of buffer 0.
        ADD_BITFIELD_RW(PID_0, 13, 1)
        // Reset the buffer selector to buffer 0.
        ADD_BITFIELD_RW(RESET, 12, 1)
        // Reply with a stall (valid for both buffers).
        ADD_BITFIELD_RW(STALL, 11, 1)
        // Buffer 0 is available. This bit is set to indicate the buffer can be used by the controller. The controller clears the available bit when writing the status back.
        ADD_BITFIELD_RW(AVAILABLE_0, 10, 1)
        // The length of the data in buffer 0.
        ADD_BITFIELD_RW(LENGTH_0, 0, 10)
    END_TYPE()

    static const uint32_t EP_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET__128 = 0;
    static const uint32_t EP_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET__256 = 1;
    static const uint32_t EP_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET__512 = 2;
    static const uint32_t EP_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET__1024 = 3;

    struct USBCTRL_DPRAM_t {
        SETUP_PACKET_LOW_t            SETUP_PACKET_LOW;
        SETUP_PACKET_HIGH_t           SETUP_PACKET_HIGH;
        EP_CONTROL_t                  EP1_IN_CONTROL;
        EP_CONTROL_t                  EP1_OUT_CONTROL;
        EP_CONTROL_t                  EP2_IN_CONTROL;
        EP_CONTROL_t                  EP2_OUT_CONTROL;
        EP_CONTROL_t                  EP3_IN_CONTROL;
        EP_CONTROL_t                  EP3_OUT_CONTROL;
        EP_CONTROL_t                  EP4_IN_CONTROL;
        EP_CONTROL_t                  EP4_OUT_CONTROL;
        EP_CONTROL_t                  EP5_IN_CONTROL;
        EP_CONTROL_t                  EP5_OUT_CONTROL;
        EP_CONTROL_t                  EP6_IN_CONTROL;
        EP_CONTROL_t                  EP6_OUT_CONTROL;
        EP_CONTROL_t                  EP7_IN_CONTROL;
        EP_CONTROL_t                  EP7_OUT_CONTROL;
        EP_CONTROL_t                  EP8_IN_CONTROL;
        EP_CONTROL_t                  EP8_OUT_CONTROL;
        EP_CONTROL_t                  EP9_IN_CONTROL;
        EP_CONTROL_t                  EP9_OUT_CONTROL;
        EP_CONTROL_t                  EP10_IN_CONTROL;
        EP_CONTROL_t                  EP10_OUT_CONTROL;
        EP_CONTROL_t                  EP11_IN_CONTROL;
        EP_CONTROL_t                  EP11_OUT_CONTROL;
        EP_CONTROL_t                  EP12_IN_CONTROL;
        EP_CONTROL_t                  EP12_OUT_CONTROL;
        EP_CONTROL_t                  EP13_IN_CONTROL;
        EP_CONTROL_t                  EP13_OUT_CONTROL;
        EP_CONTROL_t                  EP14_IN_CONTROL;
        EP_CONTROL_t                  EP14_OUT_CONTROL;
        EP_CONTROL_t                  EP15_IN_CONTROL;
        EP_CONTROL_t                  EP15_OUT_CONTROL;
        EP_BUFFER_CONTROL_t           EP0_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP0_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP1_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP1_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP2_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP2_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP3_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP3_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP4_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP4_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP5_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP5_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP6_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP6_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP7_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP7_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP8_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP8_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP9_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP9_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP10_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP10_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP11_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP11_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP12_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP12_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP13_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP13_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP14_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP14_OUT_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP15_IN_BUFFER_CONTROL;
        EP_BUFFER_CONTROL_t           EP15_OUT_BUFFER_CONTROL;
    };

    static USBCTRL_DPRAM_t & USBCTRL_DPRAM     = (*(USBCTRL_DPRAM_t *)0x50100000);
    static USBCTRL_DPRAM_t & USBCTRL_DPRAM_XOR = (*(USBCTRL_DPRAM_t *)0x50101000);
    static USBCTRL_DPRAM_t & USBCTRL_DPRAM_SET = (*(USBCTRL_DPRAM_t *)0x50102000);
    static USBCTRL_DPRAM_t & USBCTRL_DPRAM_CLR = (*(USBCTRL_DPRAM_t *)0x50103000);

} // _USBCTRL_DPRAM_

// USB FS/LS controller device registers
namespace _USBCTRL_REGS_  {

    // Device address and endpoint control
    // Reset value: 0x00000000
    BEGIN_TYPE(ADDR_ENDP_t, uint32_t)
        // Device endpoint to send data to. Only valid for HOST mode.
        ADD_BITFIELD_RW(ENDPOINT, 16, 4)
        // In device mode, the address that the device should respond to. Set in response to a SET_ADDR setup packet from the host. In host mode set to the address of the device to communicate with.
        ADD_BITFIELD_RW(ADDRESS, 0, 7)
    END_TYPE()

    // Interrupt endpoint 1. Only valid for HOST mode.
    // Reset value: 0x00000000
    BEGIN_TYPE(ADDR_ENDP__t, uint32_t)
        // Interrupt EP requires preamble (is a low speed device on a full speed hub)
        ADD_BITFIELD_RW(INTEP_PREAMBLE, 26, 1)
        // Direction of the interrupt endpoint. In=0, Out=1
        ADD_BITFIELD_RW(INTEP_DIR, 25, 1)
        // Endpoint number of the interrupt endpoint
        ADD_BITFIELD_RW(ENDPOINT, 16, 4)
        // Device address
        ADD_BITFIELD_RW(ADDRESS, 0, 7)
    END_TYPE()

    // Main control register
    // Reset value: 0x00000000
    BEGIN_TYPE(MAIN_CTRL_t, uint32_t)
        // Reduced timings for simulation
        ADD_BITFIELD_RW(SIM_TIMING, 31, 1)
        // Device mode = 0, Host mode = 1
        ADD_BITFIELD_RW(HOST_NDEVICE, 1, 1)
        // Enable controller
        ADD_BITFIELD_RW(CONTROLLER_EN, 0, 1)
    END_TYPE()

    // Set the SOF (Start of Frame) frame number in the host controller. The SOF packet is sent every 1ms and the host will increment the frame number by 1 each time.
    // Reset value: 0x00000000
    BEGIN_TYPE(SOF_WR_t, uint32_t)
        ADD_BITFIELD_WO(COUNT, 0, 11)
    END_TYPE()

    // Read the last SOF (Start of Frame) frame number seen. In device mode the last SOF received from the host. In host mode the last SOF sent by the host.
    // Reset value: 0x00000000
    BEGIN_TYPE(SOF_RD_t, uint32_t)
        ADD_BITFIELD_RO(COUNT, 0, 11)
    END_TYPE()

    // SIE control register
    // Reset value: 0x00000000
    BEGIN_TYPE(SIE_CTRL_t, uint32_t)
        // Device: Set bit in EP_STATUS_STALL_NAK when EP0 sends a STALL
        ADD_BITFIELD_RW(EP0_INT_STALL, 31, 1)
        // Device: EP0 single buffered = 0, double buffered = 1
        ADD_BITFIELD_RW(EP0_DOUBLE_BUF, 30, 1)
        // Device: Set bit in BUFF_STATUS for every buffer completed on EP0
        ADD_BITFIELD_RW(EP0_INT_1BUF, 29, 1)
        // Device: Set bit in BUFF_STATUS for every 2 buffers completed on EP0
        ADD_BITFIELD_RW(EP0_INT_2BUF, 28, 1)
        // Device: Set bit in EP_STATUS_STALL_NAK when EP0 sends a NAK
        ADD_BITFIELD_RW(EP0_INT_NAK, 27, 1)
        // Direct bus drive enable
        ADD_BITFIELD_RW(DIRECT_EN, 26, 1)
        // Direct control of DP
        ADD_BITFIELD_RW(DIRECT_DP, 25, 1)
        // Direct control of DM
        ADD_BITFIELD_RW(DIRECT_DM, 24, 1)
        // Power down bus transceiver
        ADD_BITFIELD_RW(TRANSCEIVER_PD, 18, 1)
        // Device: Pull-up strength (0=1K2, 1=2k3)
        ADD_BITFIELD_RW(RPU_OPT, 17, 1)
        // Device: Enable pull up resistor
        ADD_BITFIELD_RW(PULLUP_EN, 16, 1)
        // Host: Enable pull down resistors
        ADD_BITFIELD_RW(PULLDOWN_EN, 15, 1)
        // Host: Reset bus
        ADD_BITFIELD_RW(RESET_BUS, 13, 1)
        // Device: Remote wakeup. Device can initiate its own resume after suspend.
        ADD_BITFIELD_RW(RESUME, 12, 1)
        // Host: Enable VBUS
        ADD_BITFIELD_RW(VBUS_EN, 11, 1)
        // Host: Enable keep alive packet (for low speed bus)
        ADD_BITFIELD_RW(KEEP_ALIVE_EN, 10, 1)
        // Host: Enable SOF generation (for full speed bus)
        ADD_BITFIELD_RW(SOF_EN, 9, 1)
        // Host: Delay packet(s) until after SOF
        ADD_BITFIELD_RW(SOF_SYNC, 8, 1)
        // Host: Preable enable for LS device on FS hub
        ADD_BITFIELD_RW(PREAMBLE_EN, 6, 1)
        // Host: Stop transaction
        ADD_BITFIELD_RW(STOP_TRANS, 4, 1)
        // Host: Receive transaction (IN to host)
        ADD_BITFIELD_RW(RECEIVE_DATA, 3, 1)
        // Host: Send transaction (OUT from host)
        ADD_BITFIELD_RW(SEND_DATA, 2, 1)
        // Host: Send Setup packet
        ADD_BITFIELD_RW(SEND_SETUP, 1, 1)
        // Host: Start transaction
        ADD_BITFIELD_RW(START_TRANS, 0, 1)
    END_TYPE()

    // SIE status register
    // Reset value: 0x00000000
    BEGIN_TYPE(SIE_STATUS_t, uint32_t)
        // Data Sequence Error.
        // 
        // The device can raise a sequence error in the following conditions:
        // 
        // * A SETUP packet is received followed by a DATA1 packet (data phase should always be DATA0) * An OUT packet is received from the host but doesn't match the data pid in the buffer control register read from DPSRAM
        // 
        // The host can raise a data sequence error in the following conditions:
        // 
        // * An IN packet from the device has the wrong data PID
        ADD_BITFIELD_RW(DATA_SEQ_ERROR, 31, 1)
        // ACK received. Raised by both host and device.
        ADD_BITFIELD_RW(ACK_REC, 30, 1)
        // Host: STALL received
        ADD_BITFIELD_RW(STALL_REC, 29, 1)
        // Host: NAK received
        ADD_BITFIELD_RW(NAK_REC, 28, 1)
        // RX timeout is raised by both the host and device if an ACK is not received in the maximum time specified by the USB spec.
        ADD_BITFIELD_RW(RX_TIMEOUT, 27, 1)
        // RX overflow is raised by the Serial RX engine if the incoming data is too fast.
        ADD_BITFIELD_RW(RX_OVERFLOW, 26, 1)
        // Bit Stuff Error. Raised by the Serial RX engine.
        ADD_BITFIELD_RW(BIT_STUFF_ERROR, 25, 1)
        // CRC Error. Raised by the Serial RX engine.
        ADD_BITFIELD_RW(CRC_ERROR, 24, 1)
        // Device: bus reset received
        ADD_BITFIELD_RW(BUS_RESET, 19, 1)
        // Transaction complete.
        // 
        // Raised by device if:
        // 
        // * An IN or OUT packet is sent with the `LAST_BUFF` bit set in the buffer control register
        // 
        // Raised by host if:
        // 
        // * A setup packet is sent when no data in or data out transaction follows * An IN packet is received and the `LAST_BUFF` bit is set in the buffer control register * An IN packet is received with zero length * An OUT packet is sent and the `LAST_BUFF` bit is set
        ADD_BITFIELD_RW(TRANS_COMPLETE, 18, 1)
        // Device: Setup packet received
        ADD_BITFIELD_RW(SETUP_REC, 17, 1)
        // Device: connected
        ADD_BITFIELD_RW(CONNECTED, 16, 1)
        // Host: Device has initiated a remote resume. Device: host has initiated a resume.
        ADD_BITFIELD_RW(RESUME, 11, 1)
        // VBUS over current detected
        ADD_BITFIELD_RO(VBUS_OVER_CURR, 10, 1)
        // Host: device speed. Disconnected = 00, LS = 01, FS = 10
        ADD_BITFIELD_RW(SPEED, 8, 2)
        // Bus in suspended state. Valid for device and host. Host and device will go into suspend if neither Keep Alive / SOF frames are enabled.
        ADD_BITFIELD_RW(SUSPENDED, 4, 1)
        // USB bus line state
        ADD_BITFIELD_RO(LINE_STATE, 2, 2)
        // Device: VBUS Detected
        ADD_BITFIELD_RO(VBUS_DETECTED, 0, 1)
    END_TYPE()

    // interrupt endpoint control register
    // Reset value: 0x00000000
    BEGIN_TYPE(INT_EP_CTRL_t, uint32_t)
        // Host: Enable interrupt endpoint 1 -> 15
        ADD_BITFIELD_RW(INT_EP_ACTIVE, 1, 15)
    END_TYPE()

    // Buffer status register. A bit set here indicates that a buffer has completed on the endpoint (if the buffer interrupt is enabled). It is possible for 2 buffers to be completed, so clearing the buffer status bit may instantly re set it on the next clock cycle.
    // Reset value: 0x00000000
    BEGIN_TYPE(BUFF_STATUS_t, uint32_t)
        ADD_BITFIELD_RW(EP15_OUT, 31, 1)
        ADD_BITFIELD_RW(EP15_IN, 30, 1)
        ADD_BITFIELD_RW(EP14_OUT, 29, 1)
        ADD_BITFIELD_RW(EP14_IN, 28, 1)
        ADD_BITFIELD_RW(EP13_OUT, 27, 1)
        ADD_BITFIELD_RW(EP13_IN, 26, 1)
        ADD_BITFIELD_RW(EP12_OUT, 25, 1)
        ADD_BITFIELD_RW(EP12_IN, 24, 1)
        ADD_BITFIELD_RW(EP11_OUT, 23, 1)
        ADD_BITFIELD_RW(EP11_IN, 22, 1)
        ADD_BITFIELD_RW(EP10_OUT, 21, 1)
        ADD_BITFIELD_RW(EP10_IN, 20, 1)
        ADD_BITFIELD_RW(EP9_OUT, 19, 1)
        ADD_BITFIELD_RW(EP9_IN, 18, 1)
        ADD_BITFIELD_RW(EP8_OUT, 17, 1)
        ADD_BITFIELD_RW(EP8_IN, 16, 1)
        ADD_BITFIELD_RW(EP7_OUT, 15, 1)
        ADD_BITFIELD_RW(EP7_IN, 14, 1)
        ADD_BITFIELD_RW(EP6_OUT, 13, 1)
        ADD_BITFIELD_RW(EP6_IN, 12, 1)
        ADD_BITFIELD_RW(EP5_OUT, 11, 1)
        ADD_BITFIELD_RW(EP5_IN, 10, 1)
        ADD_BITFIELD_RW(EP4_OUT, 9, 1)
        ADD_BITFIELD_RW(EP4_IN, 8, 1)
        ADD_BITFIELD_RW(EP3_OUT, 7, 1)
        ADD_BITFIELD_RW(EP3_IN, 6, 1)
        ADD_BITFIELD_RW(EP2_OUT, 5, 1)
        ADD_BITFIELD_RW(EP2_IN, 4, 1)
        ADD_BITFIELD_RW(EP1_OUT, 3, 1)
        ADD_BITFIELD_RW(EP1_IN, 2, 1)
        ADD_BITFIELD_RW(EP0_OUT, 1, 1)
        ADD_BITFIELD_RW(EP0_IN, 0, 1)
    END_TYPE()

    // Which of the double buffers should be handled. Only valid if using an interrupt per buffer (i.e. not per 2 buffers). Not valid for host interrupt endpoint polling because they are only single buffered.
    // Reset value: 0x00000000
    BEGIN_TYPE(BUFF_CPU_SHOULD_HANDLE_t, uint32_t)
        ADD_BITFIELD_RO(EP15_OUT, 31, 1)
        ADD_BITFIELD_RO(EP15_IN, 30, 1)
        ADD_BITFIELD_RO(EP14_OUT, 29, 1)
        ADD_BITFIELD_RO(EP14_IN, 28, 1)
        ADD_BITFIELD_RO(EP13_OUT, 27, 1)
        ADD_BITFIELD_RO(EP13_IN, 26, 1)
        ADD_BITFIELD_RO(EP12_OUT, 25, 1)
        ADD_BITFIELD_RO(EP12_IN, 24, 1)
        ADD_BITFIELD_RO(EP11_OUT, 23, 1)
        ADD_BITFIELD_RO(EP11_IN, 22, 1)
        ADD_BITFIELD_RO(EP10_OUT, 21, 1)
        ADD_BITFIELD_RO(EP10_IN, 20, 1)
        ADD_BITFIELD_RO(EP9_OUT, 19, 1)
        ADD_BITFIELD_RO(EP9_IN, 18, 1)
        ADD_BITFIELD_RO(EP8_OUT, 17, 1)
        ADD_BITFIELD_RO(EP8_IN, 16, 1)
        ADD_BITFIELD_RO(EP7_OUT, 15, 1)
        ADD_BITFIELD_RO(EP7_IN, 14, 1)
        ADD_BITFIELD_RO(EP6_OUT, 13, 1)
        ADD_BITFIELD_RO(EP6_IN, 12, 1)
        ADD_BITFIELD_RO(EP5_OUT, 11, 1)
        ADD_BITFIELD_RO(EP5_IN, 10, 1)
        ADD_BITFIELD_RO(EP4_OUT, 9, 1)
        ADD_BITFIELD_RO(EP4_IN, 8, 1)
        ADD_BITFIELD_RO(EP3_OUT, 7, 1)
        ADD_BITFIELD_RO(EP3_IN, 6, 1)
        ADD_BITFIELD_RO(EP2_OUT, 5, 1)
        ADD_BITFIELD_RO(EP2_IN, 4, 1)
        ADD_BITFIELD_RO(EP1_OUT, 3, 1)
        ADD_BITFIELD_RO(EP1_IN, 2, 1)
        ADD_BITFIELD_RO(EP0_OUT, 1, 1)
        ADD_BITFIELD_RO(EP0_IN, 0, 1)
    END_TYPE()

    // Device only: Can be set to ignore the buffer control register for this endpoint in case you would like to revoke a buffer. A NAK will be sent for every access to the endpoint until this bit is cleared. A corresponding bit in `EP_ABORT_DONE` is set when it is safe to modify the buffer control register.
    // Reset value: 0x00000000
    BEGIN_TYPE(EP_ABORT_t, uint32_t)
        ADD_BITFIELD_RW(EP15_OUT, 31, 1)
        ADD_BITFIELD_RW(EP15_IN, 30, 1)
        ADD_BITFIELD_RW(EP14_OUT, 29, 1)
        ADD_BITFIELD_RW(EP14_IN, 28, 1)
        ADD_BITFIELD_RW(EP13_OUT, 27, 1)
        ADD_BITFIELD_RW(EP13_IN, 26, 1)
        ADD_BITFIELD_RW(EP12_OUT, 25, 1)
        ADD_BITFIELD_RW(EP12_IN, 24, 1)
        ADD_BITFIELD_RW(EP11_OUT, 23, 1)
        ADD_BITFIELD_RW(EP11_IN, 22, 1)
        ADD_BITFIELD_RW(EP10_OUT, 21, 1)
        ADD_BITFIELD_RW(EP10_IN, 20, 1)
        ADD_BITFIELD_RW(EP9_OUT, 19, 1)
        ADD_BITFIELD_RW(EP9_IN, 18, 1)
        ADD_BITFIELD_RW(EP8_OUT, 17, 1)
        ADD_BITFIELD_RW(EP8_IN, 16, 1)
        ADD_BITFIELD_RW(EP7_OUT, 15, 1)
        ADD_BITFIELD_RW(EP7_IN, 14, 1)
        ADD_BITFIELD_RW(EP6_OUT, 13, 1)
        ADD_BITFIELD_RW(EP6_IN, 12, 1)
        ADD_BITFIELD_RW(EP5_OUT, 11, 1)
        ADD_BITFIELD_RW(EP5_IN, 10, 1)
        ADD_BITFIELD_RW(EP4_OUT, 9, 1)
        ADD_BITFIELD_RW(EP4_IN, 8, 1)
        ADD_BITFIELD_RW(EP3_OUT, 7, 1)
        ADD_BITFIELD_RW(EP3_IN, 6, 1)
        ADD_BITFIELD_RW(EP2_OUT, 5, 1)
        ADD_BITFIELD_RW(EP2_IN, 4, 1)
        ADD_BITFIELD_RW(EP1_OUT, 3, 1)
        ADD_BITFIELD_RW(EP1_IN, 2, 1)
        ADD_BITFIELD_RW(EP0_OUT, 1, 1)
        ADD_BITFIELD_RW(EP0_IN, 0, 1)
    END_TYPE()

    // Device only: Used in conjunction with `EP_ABORT`. Set once an endpoint is idle so the programmer knows it is safe to modify the buffer control register.
    // Reset value: 0x00000000
    BEGIN_TYPE(EP_ABORT_DONE_t, uint32_t)
        ADD_BITFIELD_RW(EP15_OUT, 31, 1)
        ADD_BITFIELD_RW(EP15_IN, 30, 1)
        ADD_BITFIELD_RW(EP14_OUT, 29, 1)
        ADD_BITFIELD_RW(EP14_IN, 28, 1)
        ADD_BITFIELD_RW(EP13_OUT, 27, 1)
        ADD_BITFIELD_RW(EP13_IN, 26, 1)
        ADD_BITFIELD_RW(EP12_OUT, 25, 1)
        ADD_BITFIELD_RW(EP12_IN, 24, 1)
        ADD_BITFIELD_RW(EP11_OUT, 23, 1)
        ADD_BITFIELD_RW(EP11_IN, 22, 1)
        ADD_BITFIELD_RW(EP10_OUT, 21, 1)
        ADD_BITFIELD_RW(EP10_IN, 20, 1)
        ADD_BITFIELD_RW(EP9_OUT, 19, 1)
        ADD_BITFIELD_RW(EP9_IN, 18, 1)
        ADD_BITFIELD_RW(EP8_OUT, 17, 1)
        ADD_BITFIELD_RW(EP8_IN, 16, 1)
        ADD_BITFIELD_RW(EP7_OUT, 15, 1)
        ADD_BITFIELD_RW(EP7_IN, 14, 1)
        ADD_BITFIELD_RW(EP6_OUT, 13, 1)
        ADD_BITFIELD_RW(EP6_IN, 12, 1)
        ADD_BITFIELD_RW(EP5_OUT, 11, 1)
        ADD_BITFIELD_RW(EP5_IN, 10, 1)
        ADD_BITFIELD_RW(EP4_OUT, 9, 1)
        ADD_BITFIELD_RW(EP4_IN, 8, 1)
        ADD_BITFIELD_RW(EP3_OUT, 7, 1)
        ADD_BITFIELD_RW(EP3_IN, 6, 1)
        ADD_BITFIELD_RW(EP2_OUT, 5, 1)
        ADD_BITFIELD_RW(EP2_IN, 4, 1)
        ADD_BITFIELD_RW(EP1_OUT, 3, 1)
        ADD_BITFIELD_RW(EP1_IN, 2, 1)
        ADD_BITFIELD_RW(EP0_OUT, 1, 1)
        ADD_BITFIELD_RW(EP0_IN, 0, 1)
    END_TYPE()

    // Device: this bit must be set in conjunction with the `STALL` bit in the buffer control register to send a STALL on EP0. The device controller clears these bits when a SETUP packet is received because the USB spec requires that a STALL condition is cleared when a SETUP packet is received.
    // Reset value: 0x00000000
    BEGIN_TYPE(EP_STALL_ARM_t, uint32_t)
        ADD_BITFIELD_RW(EP0_OUT, 1, 1)
        ADD_BITFIELD_RW(EP0_IN, 0, 1)
    END_TYPE()

    // Used by the host controller. Sets the wait time in microseconds before trying again if the device replies with a NAK.
    // Reset value: 0x00100010
    BEGIN_TYPE(NAK_POLL_t, uint32_t)
        // NAK polling interval for a full speed device
        ADD_BITFIELD_RW(DELAY_FS, 16, 10)
        // NAK polling interval for a low speed device
        ADD_BITFIELD_RW(DELAY_LS, 0, 10)
    END_TYPE()

    // Device: bits are set when the `IRQ_ON_NAK` or `IRQ_ON_STALL` bits are set. For EP0 this comes from `SIE_CTRL`. For all other endpoints it comes from the endpoint control register.
    // Reset value: 0x00000000
    BEGIN_TYPE(EP_STATUS_STALL_NAK_t, uint32_t)
        ADD_BITFIELD_RW(EP15_OUT, 31, 1)
        ADD_BITFIELD_RW(EP15_IN, 30, 1)
        ADD_BITFIELD_RW(EP14_OUT, 29, 1)
        ADD_BITFIELD_RW(EP14_IN, 28, 1)
        ADD_BITFIELD_RW(EP13_OUT, 27, 1)
        ADD_BITFIELD_RW(EP13_IN, 26, 1)
        ADD_BITFIELD_RW(EP12_OUT, 25, 1)
        ADD_BITFIELD_RW(EP12_IN, 24, 1)
        ADD_BITFIELD_RW(EP11_OUT, 23, 1)
        ADD_BITFIELD_RW(EP11_IN, 22, 1)
        ADD_BITFIELD_RW(EP10_OUT, 21, 1)
        ADD_BITFIELD_RW(EP10_IN, 20, 1)
        ADD_BITFIELD_RW(EP9_OUT, 19, 1)
        ADD_BITFIELD_RW(EP9_IN, 18, 1)
        ADD_BITFIELD_RW(EP8_OUT, 17, 1)
        ADD_BITFIELD_RW(EP8_IN, 16, 1)
        ADD_BITFIELD_RW(EP7_OUT, 15, 1)
        ADD_BITFIELD_RW(EP7_IN, 14, 1)
        ADD_BITFIELD_RW(EP6_OUT, 13, 1)
        ADD_BITFIELD_RW(EP6_IN, 12, 1)
        ADD_BITFIELD_RW(EP5_OUT, 11, 1)
        ADD_BITFIELD_RW(EP5_IN, 10, 1)
        ADD_BITFIELD_RW(EP4_OUT, 9, 1)
        ADD_BITFIELD_RW(EP4_IN, 8, 1)
        ADD_BITFIELD_RW(EP3_OUT, 7, 1)
        ADD_BITFIELD_RW(EP3_IN, 6, 1)
        ADD_BITFIELD_RW(EP2_OUT, 5, 1)
        ADD_BITFIELD_RW(EP2_IN, 4, 1)
        ADD_BITFIELD_RW(EP1_OUT, 3, 1)
        ADD_BITFIELD_RW(EP1_IN, 2, 1)
        ADD_BITFIELD_RW(EP0_OUT, 1, 1)
        ADD_BITFIELD_RW(EP0_IN, 0, 1)
    END_TYPE()

    // Where to connect the USB controller. Should be to_phy by default.
    // Reset value: 0x00000000
    BEGIN_TYPE(USB_MUXING_t, uint32_t)
        ADD_BITFIELD_RW(SOFTCON, 3, 1)
        ADD_BITFIELD_RW(TO_DIGITAL_PAD, 2, 1)
        ADD_BITFIELD_RW(TO_EXTPHY, 1, 1)
        ADD_BITFIELD_RW(TO_PHY, 0, 1)
    END_TYPE()

    // Overrides for the power signals in the event that the VBUS signals are not hooked up to GPIO. Set the value of the override and then the override enable to switch over to the override value.
    // Reset value: 0x00000000
    BEGIN_TYPE(USB_PWR_t, uint32_t)
        ADD_BITFIELD_RW(OVERCURR_DETECT_EN, 5, 1)
        ADD_BITFIELD_RW(OVERCURR_DETECT, 4, 1)
        ADD_BITFIELD_RW(VBUS_DETECT_OVERRIDE_EN, 3, 1)
        ADD_BITFIELD_RW(VBUS_DETECT, 2, 1)
        ADD_BITFIELD_RW(VBUS_EN_OVERRIDE_EN, 1, 1)
        ADD_BITFIELD_RW(VBUS_EN, 0, 1)
    END_TYPE()

    // This register allows for direct control of the USB phy. Use in conjunction with usbphy_direct_override register to enable each override bit.
    // Reset value: 0x00000000
    BEGIN_TYPE(USBPHY_DIRECT_t, uint32_t)
        // DM over voltage
        ADD_BITFIELD_RO(DM_OVV, 22, 1)
        // DP over voltage
        ADD_BITFIELD_RO(DP_OVV, 21, 1)
        // DM overcurrent
        ADD_BITFIELD_RO(DM_OVCN, 20, 1)
        // DP overcurrent
        ADD_BITFIELD_RO(DP_OVCN, 19, 1)
        // DPM pin state
        ADD_BITFIELD_RO(RX_DM, 18, 1)
        // DPP pin state
        ADD_BITFIELD_RO(RX_DP, 17, 1)
        // Differential RX
        ADD_BITFIELD_RO(RX_DD, 16, 1)
        // TX_DIFFMODE=0: Single ended mode
        // TX_DIFFMODE=1: Differential drive mode (TX_DM, TX_DM_OE ignored)
        ADD_BITFIELD_RW(TX_DIFFMODE, 15, 1)
        // TX_FSSLEW=0: Low speed slew rate
        // TX_FSSLEW=1: Full speed slew rate
        ADD_BITFIELD_RW(TX_FSSLEW, 14, 1)
        // TX power down override (if override enable is set). 1 = powered down.
        ADD_BITFIELD_RW(TX_PD, 13, 1)
        // RX power down override (if override enable is set). 1 = powered down.
        ADD_BITFIELD_RW(RX_PD, 12, 1)
        // Output data. TX_DIFFMODE=1, Ignored
        // TX_DIFFMODE=0, Drives DPM only. TX_DM_OE=1 to enable drive. DPM=TX_DM
        ADD_BITFIELD_RW(TX_DM, 11, 1)
        // Output data. If TX_DIFFMODE=1, Drives DPP/DPM diff pair. TX_DP_OE=1 to enable drive. DPP=TX_DP, DPM=~TX_DP
        // If TX_DIFFMODE=0, Drives DPP only. TX_DP_OE=1 to enable drive. DPP=TX_DP
        ADD_BITFIELD_RW(TX_DP, 10, 1)
        // Output enable. If TX_DIFFMODE=1, Ignored.
        // If TX_DIFFMODE=0, OE for DPM only. 0 - DPM in Hi-Z state; 1 - DPM driving
        ADD_BITFIELD_RW(TX_DM_OE, 9, 1)
        // Output enable. If TX_DIFFMODE=1, OE for DPP/DPM diff pair. 0 - DPP/DPM in Hi-Z state; 1 - DPP/DPM driving
        // If TX_DIFFMODE=0, OE for DPP only. 0 - DPP in Hi-Z state; 1 - DPP driving
        ADD_BITFIELD_RW(TX_DP_OE, 8, 1)
        // DM pull down enable
        ADD_BITFIELD_RW(DM_PULLDN_EN, 6, 1)
        // DM pull up enable
        ADD_BITFIELD_RW(DM_PULLUP_EN, 5, 1)
        // Enable the second DM pull up resistor. 0 - Pull = Rpu2; 1 - Pull = Rpu1 + Rpu2
        ADD_BITFIELD_RW(DM_PULLUP_HISEL, 4, 1)
        // DP pull down enable
        ADD_BITFIELD_RW(DP_PULLDN_EN, 2, 1)
        // DP pull up enable
        ADD_BITFIELD_RW(DP_PULLUP_EN, 1, 1)
        // Enable the second DP pull up resistor. 0 - Pull = Rpu2; 1 - Pull = Rpu1 + Rpu2
        ADD_BITFIELD_RW(DP_PULLUP_HISEL, 0, 1)
    END_TYPE()

    // Override enable for each control in usbphy_direct
    // Reset value: 0x00000000
    BEGIN_TYPE(USBPHY_DIRECT_OVERRIDE_t, uint32_t)
        ADD_BITFIELD_RW(TX_DIFFMODE_OVERRIDE_EN, 15, 1)
        ADD_BITFIELD_RW(DM_PULLUP_OVERRIDE_EN, 12, 1)
        ADD_BITFIELD_RW(TX_FSSLEW_OVERRIDE_EN, 11, 1)
        ADD_BITFIELD_RW(TX_PD_OVERRIDE_EN, 10, 1)
        ADD_BITFIELD_RW(RX_PD_OVERRIDE_EN, 9, 1)
        ADD_BITFIELD_RW(TX_DM_OVERRIDE_EN, 8, 1)
        ADD_BITFIELD_RW(TX_DP_OVERRIDE_EN, 7, 1)
        ADD_BITFIELD_RW(TX_DM_OE_OVERRIDE_EN, 6, 1)
        ADD_BITFIELD_RW(TX_DP_OE_OVERRIDE_EN, 5, 1)
        ADD_BITFIELD_RW(DM_PULLDN_EN_OVERRIDE_EN, 4, 1)
        ADD_BITFIELD_RW(DP_PULLDN_EN_OVERRIDE_EN, 3, 1)
        ADD_BITFIELD_RW(DP_PULLUP_EN_OVERRIDE_EN, 2, 1)
        ADD_BITFIELD_RW(DM_PULLUP_HISEL_OVERRIDE_EN, 1, 1)
        ADD_BITFIELD_RW(DP_PULLUP_HISEL_OVERRIDE_EN, 0, 1)
    END_TYPE()

    // Used to adjust trim values of USB phy pull down resistors.
    // Reset value: 0x00001f1f
    BEGIN_TYPE(USBPHY_TRIM_t, uint32_t)
        // Value to drive to USB PHY
        // DM pulldown resistor trim control
        // Experimental data suggests that the reset value will work, but this register allows adjustment if required
        ADD_BITFIELD_RW(DM_PULLDN_TRIM, 8, 5)
        // Value to drive to USB PHY
        // DP pulldown resistor trim control
        // Experimental data suggests that the reset value will work, but this register allows adjustment if required
        ADD_BITFIELD_RW(DP_PULLDN_TRIM, 0, 5)
    END_TYPE()

    // Raw Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR_t, uint32_t)
        // Raised when any bit in EP_STATUS_STALL_NAK is set. Clear by clearing all bits in EP_STATUS_STALL_NAK.
        ADD_BITFIELD_RO(EP_STALL_NAK, 19, 1)
        // Raised when any bit in ABORT_DONE is set. Clear by clearing all bits in ABORT_DONE.
        ADD_BITFIELD_RO(ABORT_DONE, 18, 1)
        // Set every time the device receives a SOF (Start of Frame) packet. Cleared by reading SOF_RD
        ADD_BITFIELD_RO(DEV_SOF, 17, 1)
        // Device. Source: SIE_STATUS.SETUP_REC
        ADD_BITFIELD_RO(SETUP_REQ, 16, 1)
        // Set when the device receives a resume from the host. Cleared by writing to SIE_STATUS.RESUME
        ADD_BITFIELD_RO(DEV_RESUME_FROM_HOST, 15, 1)
        // Set when the device suspend state changes. Cleared by writing to SIE_STATUS.SUSPENDED
        ADD_BITFIELD_RO(DEV_SUSPEND, 14, 1)
        // Set when the device connection state changes. Cleared by writing to SIE_STATUS.CONNECTED
        ADD_BITFIELD_RO(DEV_CONN_DIS, 13, 1)
        // Source: SIE_STATUS.BUS_RESET
        ADD_BITFIELD_RO(BUS_RESET, 12, 1)
        // Source: SIE_STATUS.VBUS_DETECTED
        ADD_BITFIELD_RO(VBUS_DETECT, 11, 1)
        // Source: SIE_STATUS.STALL_REC
        ADD_BITFIELD_RO(STALL, 10, 1)
        // Source: SIE_STATUS.CRC_ERROR
        ADD_BITFIELD_RO(ERROR_CRC, 9, 1)
        // Source: SIE_STATUS.BIT_STUFF_ERROR
        ADD_BITFIELD_RO(ERROR_BIT_STUFF, 8, 1)
        // Source: SIE_STATUS.RX_OVERFLOW
        ADD_BITFIELD_RO(ERROR_RX_OVERFLOW, 7, 1)
        // Source: SIE_STATUS.RX_TIMEOUT
        ADD_BITFIELD_RO(ERROR_RX_TIMEOUT, 6, 1)
        // Source: SIE_STATUS.DATA_SEQ_ERROR
        ADD_BITFIELD_RO(ERROR_DATA_SEQ, 5, 1)
        // Raised when any bit in BUFF_STATUS is set. Clear by clearing all bits in BUFF_STATUS.
        ADD_BITFIELD_RO(BUFF_STATUS, 4, 1)
        // Raised every time SIE_STATUS.TRANS_COMPLETE is set. Clear by writing to this bit.
        ADD_BITFIELD_RO(TRANS_COMPLETE, 3, 1)
        // Host: raised every time the host sends a SOF (Start of Frame). Cleared by reading SOF_RD
        ADD_BITFIELD_RO(HOST_SOF, 2, 1)
        // Host: raised when a device wakes up the host. Cleared by writing to SIE_STATUS.RESUME
        ADD_BITFIELD_RO(HOST_RESUME, 1, 1)
        // Host: raised when a device is connected or disconnected (i.e. when SIE_STATUS.SPEED changes). Cleared by writing to SIE_STATUS.SPEED
        ADD_BITFIELD_RO(HOST_CONN_DIS, 0, 1)
    END_TYPE()

    // Interrupt Enable
    // Reset value: 0x00000000
    BEGIN_TYPE(INTE_t, uint32_t)
        // Raised when any bit in EP_STATUS_STALL_NAK is set. Clear by clearing all bits in EP_STATUS_STALL_NAK.
        ADD_BITFIELD_RW(EP_STALL_NAK, 19, 1)
        // Raised when any bit in ABORT_DONE is set. Clear by clearing all bits in ABORT_DONE.
        ADD_BITFIELD_RW(ABORT_DONE, 18, 1)
        // Set every time the device receives a SOF (Start of Frame) packet. Cleared by reading SOF_RD
        ADD_BITFIELD_RW(DEV_SOF, 17, 1)
        // Device. Source: SIE_STATUS.SETUP_REC
        ADD_BITFIELD_RW(SETUP_REQ, 16, 1)
        // Set when the device receives a resume from the host. Cleared by writing to SIE_STATUS.RESUME
        ADD_BITFIELD_RW(DEV_RESUME_FROM_HOST, 15, 1)
        // Set when the device suspend state changes. Cleared by writing to SIE_STATUS.SUSPENDED
        ADD_BITFIELD_RW(DEV_SUSPEND, 14, 1)
        // Set when the device connection state changes. Cleared by writing to SIE_STATUS.CONNECTED
        ADD_BITFIELD_RW(DEV_CONN_DIS, 13, 1)
        // Source: SIE_STATUS.BUS_RESET
        ADD_BITFIELD_RW(BUS_RESET, 12, 1)
        // Source: SIE_STATUS.VBUS_DETECTED
        ADD_BITFIELD_RW(VBUS_DETECT, 11, 1)
        // Source: SIE_STATUS.STALL_REC
        ADD_BITFIELD_RW(STALL, 10, 1)
        // Source: SIE_STATUS.CRC_ERROR
        ADD_BITFIELD_RW(ERROR_CRC, 9, 1)
        // Source: SIE_STATUS.BIT_STUFF_ERROR
        ADD_BITFIELD_RW(ERROR_BIT_STUFF, 8, 1)
        // Source: SIE_STATUS.RX_OVERFLOW
        ADD_BITFIELD_RW(ERROR_RX_OVERFLOW, 7, 1)
        // Source: SIE_STATUS.RX_TIMEOUT
        ADD_BITFIELD_RW(ERROR_RX_TIMEOUT, 6, 1)
        // Source: SIE_STATUS.DATA_SEQ_ERROR
        ADD_BITFIELD_RW(ERROR_DATA_SEQ, 5, 1)
        // Raised when any bit in BUFF_STATUS is set. Clear by clearing all bits in BUFF_STATUS.
        ADD_BITFIELD_RW(BUFF_STATUS, 4, 1)
        // Raised every time SIE_STATUS.TRANS_COMPLETE is set. Clear by writing to this bit.
        ADD_BITFIELD_RW(TRANS_COMPLETE, 3, 1)
        // Host: raised every time the host sends a SOF (Start of Frame). Cleared by reading SOF_RD
        ADD_BITFIELD_RW(HOST_SOF, 2, 1)
        // Host: raised when a device wakes up the host. Cleared by writing to SIE_STATUS.RESUME
        ADD_BITFIELD_RW(HOST_RESUME, 1, 1)
        // Host: raised when a device is connected or disconnected (i.e. when SIE_STATUS.SPEED changes). Cleared by writing to SIE_STATUS.SPEED
        ADD_BITFIELD_RW(HOST_CONN_DIS, 0, 1)
    END_TYPE()

    // Interrupt Force
    // Reset value: 0x00000000
    BEGIN_TYPE(INTF_t, uint32_t)
        // Raised when any bit in EP_STATUS_STALL_NAK is set. Clear by clearing all bits in EP_STATUS_STALL_NAK.
        ADD_BITFIELD_RW(EP_STALL_NAK, 19, 1)
        // Raised when any bit in ABORT_DONE is set. Clear by clearing all bits in ABORT_DONE.
        ADD_BITFIELD_RW(ABORT_DONE, 18, 1)
        // Set every time the device receives a SOF (Start of Frame) packet. Cleared by reading SOF_RD
        ADD_BITFIELD_RW(DEV_SOF, 17, 1)
        // Device. Source: SIE_STATUS.SETUP_REC
        ADD_BITFIELD_RW(SETUP_REQ, 16, 1)
        // Set when the device receives a resume from the host. Cleared by writing to SIE_STATUS.RESUME
        ADD_BITFIELD_RW(DEV_RESUME_FROM_HOST, 15, 1)
        // Set when the device suspend state changes. Cleared by writing to SIE_STATUS.SUSPENDED
        ADD_BITFIELD_RW(DEV_SUSPEND, 14, 1)
        // Set when the device connection state changes. Cleared by writing to SIE_STATUS.CONNECTED
        ADD_BITFIELD_RW(DEV_CONN_DIS, 13, 1)
        // Source: SIE_STATUS.BUS_RESET
        ADD_BITFIELD_RW(BUS_RESET, 12, 1)
        // Source: SIE_STATUS.VBUS_DETECTED
        ADD_BITFIELD_RW(VBUS_DETECT, 11, 1)
        // Source: SIE_STATUS.STALL_REC
        ADD_BITFIELD_RW(STALL, 10, 1)
        // Source: SIE_STATUS.CRC_ERROR
        ADD_BITFIELD_RW(ERROR_CRC, 9, 1)
        // Source: SIE_STATUS.BIT_STUFF_ERROR
        ADD_BITFIELD_RW(ERROR_BIT_STUFF, 8, 1)
        // Source: SIE_STATUS.RX_OVERFLOW
        ADD_BITFIELD_RW(ERROR_RX_OVERFLOW, 7, 1)
        // Source: SIE_STATUS.RX_TIMEOUT
        ADD_BITFIELD_RW(ERROR_RX_TIMEOUT, 6, 1)
        // Source: SIE_STATUS.DATA_SEQ_ERROR
        ADD_BITFIELD_RW(ERROR_DATA_SEQ, 5, 1)
        // Raised when any bit in BUFF_STATUS is set. Clear by clearing all bits in BUFF_STATUS.
        ADD_BITFIELD_RW(BUFF_STATUS, 4, 1)
        // Raised every time SIE_STATUS.TRANS_COMPLETE is set. Clear by writing to this bit.
        ADD_BITFIELD_RW(TRANS_COMPLETE, 3, 1)
        // Host: raised every time the host sends a SOF (Start of Frame). Cleared by reading SOF_RD
        ADD_BITFIELD_RW(HOST_SOF, 2, 1)
        // Host: raised when a device wakes up the host. Cleared by writing to SIE_STATUS.RESUME
        ADD_BITFIELD_RW(HOST_RESUME, 1, 1)
        // Host: raised when a device is connected or disconnected (i.e. when SIE_STATUS.SPEED changes). Cleared by writing to SIE_STATUS.SPEED
        ADD_BITFIELD_RW(HOST_CONN_DIS, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing
    // Reset value: 0x00000000
    BEGIN_TYPE(INTS_t, uint32_t)
        // Raised when any bit in EP_STATUS_STALL_NAK is set. Clear by clearing all bits in EP_STATUS_STALL_NAK.
        ADD_BITFIELD_RO(EP_STALL_NAK, 19, 1)
        // Raised when any bit in ABORT_DONE is set. Clear by clearing all bits in ABORT_DONE.
        ADD_BITFIELD_RO(ABORT_DONE, 18, 1)
        // Set every time the device receives a SOF (Start of Frame) packet. Cleared by reading SOF_RD
        ADD_BITFIELD_RO(DEV_SOF, 17, 1)
        // Device. Source: SIE_STATUS.SETUP_REC
        ADD_BITFIELD_RO(SETUP_REQ, 16, 1)
        // Set when the device receives a resume from the host. Cleared by writing to SIE_STATUS.RESUME
        ADD_BITFIELD_RO(DEV_RESUME_FROM_HOST, 15, 1)
        // Set when the device suspend state changes. Cleared by writing to SIE_STATUS.SUSPENDED
        ADD_BITFIELD_RO(DEV_SUSPEND, 14, 1)
        // Set when the device connection state changes. Cleared by writing to SIE_STATUS.CONNECTED
        ADD_BITFIELD_RO(DEV_CONN_DIS, 13, 1)
        // Source: SIE_STATUS.BUS_RESET
        ADD_BITFIELD_RO(BUS_RESET, 12, 1)
        // Source: SIE_STATUS.VBUS_DETECTED
        ADD_BITFIELD_RO(VBUS_DETECT, 11, 1)
        // Source: SIE_STATUS.STALL_REC
        ADD_BITFIELD_RO(STALL, 10, 1)
        // Source: SIE_STATUS.CRC_ERROR
        ADD_BITFIELD_RO(ERROR_CRC, 9, 1)
        // Source: SIE_STATUS.BIT_STUFF_ERROR
        ADD_BITFIELD_RO(ERROR_BIT_STUFF, 8, 1)
        // Source: SIE_STATUS.RX_OVERFLOW
        ADD_BITFIELD_RO(ERROR_RX_OVERFLOW, 7, 1)
        // Source: SIE_STATUS.RX_TIMEOUT
        ADD_BITFIELD_RO(ERROR_RX_TIMEOUT, 6, 1)
        // Source: SIE_STATUS.DATA_SEQ_ERROR
        ADD_BITFIELD_RO(ERROR_DATA_SEQ, 5, 1)
        // Raised when any bit in BUFF_STATUS is set. Clear by clearing all bits in BUFF_STATUS.
        ADD_BITFIELD_RO(BUFF_STATUS, 4, 1)
        // Raised every time SIE_STATUS.TRANS_COMPLETE is set. Clear by writing to this bit.
        ADD_BITFIELD_RO(TRANS_COMPLETE, 3, 1)
        // Host: raised every time the host sends a SOF (Start of Frame). Cleared by reading SOF_RD
        ADD_BITFIELD_RO(HOST_SOF, 2, 1)
        // Host: raised when a device wakes up the host. Cleared by writing to SIE_STATUS.RESUME
        ADD_BITFIELD_RO(HOST_RESUME, 1, 1)
        // Host: raised when a device is connected or disconnected (i.e. when SIE_STATUS.SPEED changes). Cleared by writing to SIE_STATUS.SPEED
        ADD_BITFIELD_RO(HOST_CONN_DIS, 0, 1)
    END_TYPE()

    struct USBCTRL_REGS_t {
        ADDR_ENDP_t                   ADDR_ENDP;
        ADDR_ENDP__t                  ADDR_ENDP_1;
        ADDR_ENDP__t                  ADDR_ENDP_2;
        ADDR_ENDP__t                  ADDR_ENDP_3;
        ADDR_ENDP__t                  ADDR_ENDP_4;
        ADDR_ENDP__t                  ADDR_ENDP_5;
        ADDR_ENDP__t                  ADDR_ENDP_6;
        ADDR_ENDP__t                  ADDR_ENDP_7;
        ADDR_ENDP__t                  ADDR_ENDP_8;
        ADDR_ENDP__t                  ADDR_ENDP_9;
        ADDR_ENDP__t                  ADDR_ENDP_10;
        ADDR_ENDP__t                  ADDR_ENDP_11;
        ADDR_ENDP__t                  ADDR_ENDP_12;
        ADDR_ENDP__t                  ADDR_ENDP_13;
        ADDR_ENDP__t                  ADDR_ENDP_14;
        ADDR_ENDP__t                  ADDR_ENDP_15;
        MAIN_CTRL_t                   MAIN_CTRL;
        SOF_WR_t                      SOF_WR;
        SOF_RD_t                      SOF_RD;
        SIE_CTRL_t                    SIE_CTRL;
        SIE_STATUS_t                  SIE_STATUS;
        INT_EP_CTRL_t                 INT_EP_CTRL;
        BUFF_STATUS_t                 BUFF_STATUS;
        BUFF_CPU_SHOULD_HANDLE_t      BUFF_CPU_SHOULD_HANDLE;
        EP_ABORT_t                    EP_ABORT;
        EP_ABORT_DONE_t               EP_ABORT_DONE;
        EP_STALL_ARM_t                EP_STALL_ARM;
        NAK_POLL_t                    NAK_POLL;
        EP_STATUS_STALL_NAK_t         EP_STATUS_STALL_NAK;
        USB_MUXING_t                  USB_MUXING;
        USB_PWR_t                     USB_PWR;
        USBPHY_DIRECT_t               USBPHY_DIRECT;
        USBPHY_DIRECT_OVERRIDE_t      USBPHY_DIRECT_OVERRIDE;
        USBPHY_TRIM_t                 USBPHY_TRIM;
        uint32_t                      reserved0;
        INTR_t                        INTR;
        INTE_t                        INTE;
        INTF_t                        INTF;
        INTS_t                        INTS;
    };

    static USBCTRL_REGS_t & USBCTRL_REGS     = (*(USBCTRL_REGS_t *)0x50110000);
    static USBCTRL_REGS_t & USBCTRL_REGS_XOR = (*(USBCTRL_REGS_t *)0x50111000);
    static USBCTRL_REGS_t & USBCTRL_REGS_SET = (*(USBCTRL_REGS_t *)0x50112000);
    static USBCTRL_REGS_t & USBCTRL_REGS_CLR = (*(USBCTRL_REGS_t *)0x50113000);

} // _USBCTRL_REGS_

// Programmable IO block
namespace _PIO0_  {

    // PIO control register
    // Reset value: 0x00000000
    BEGIN_TYPE(CTRL_t, uint32_t)
        // Restart a state machine's clock divider from an initial phase of 0. Clock dividers are free-running, so once started, their output (including fractional jitter) is completely determined by the integer/fractional divisor configured in SMx_CLKDIV. This means that, if multiple clock dividers with the same divisor are restarted simultaneously, by writing multiple 1 bits to this field, the execution clocks of those state machines will run in precise lockstep.
        // 
        // Note that setting/clearing SM_ENABLE does not stop the clock divider from running, so once multiple state machines' clocks are synchronised, it is safe to disable/reenable a state machine, whilst keeping the clock dividers in sync.
        // 
        // Note also that CLKDIV_RESTART can be written to whilst the state machine is running, and this is useful to resynchronise clock dividers after the divisors (SMx_CLKDIV) have been changed on-the-fly.
        ADD_BITFIELD_RW(CLKDIV_RESTART, 8, 4)
        // Write 1 to instantly clear internal SM state which may be otherwise difficult to access and will affect future execution.
        // 
        // Specifically, the following are cleared: input and output shift counters; the contents of the input shift register; the delay counter; the waiting-on-IRQ state; any stalled instruction written to SMx_INSTR or run by OUT/MOV EXEC; any pin write left asserted due to OUT_STICKY.
        ADD_BITFIELD_RW(SM_RESTART, 4, 4)
        // Enable/disable each of the four state machines by writing 1/0 to each of these four bits. When disabled, a state machine will cease executing instructions, except those written directly to SMx_INSTR by the system. Multiple bits can be set/cleared at once to run/halt multiple state machines simultaneously.
        ADD_BITFIELD_RW(SM_ENABLE, 0, 4)
    END_TYPE()

    // FIFO status register
    // Reset value: 0x0f000f00
    BEGIN_TYPE(FSTAT_t, uint32_t)
        // State machine TX FIFO is empty
        ADD_BITFIELD_RO(TXEMPTY, 24, 4)
        // State machine TX FIFO is full
        ADD_BITFIELD_RO(TXFULL, 16, 4)
        // State machine RX FIFO is empty
        ADD_BITFIELD_RO(RXEMPTY, 8, 4)
        // State machine RX FIFO is full
        ADD_BITFIELD_RO(RXFULL, 0, 4)
    END_TYPE()

    // FIFO debug register
    // Reset value: 0x00000000
    BEGIN_TYPE(FDEBUG_t, uint32_t)
        // State machine has stalled on empty TX FIFO during a blocking PULL, or an OUT with autopull enabled. Write 1 to clear.
        ADD_BITFIELD_RW(TXSTALL, 24, 4)
        // TX FIFO overflow (i.e. write-on-full by the system) has occurred. Write 1 to clear. Note that write-on-full does not alter the state or contents of the FIFO in any way, but the data that the system attempted to write is dropped, so if this flag is set, your software has quite likely dropped some data on the floor.
        ADD_BITFIELD_RW(TXOVER, 16, 4)
        // RX FIFO underflow (i.e. read-on-empty by the system) has occurred. Write 1 to clear. Note that read-on-empty does not perturb the state of the FIFO in any way, but the data returned by reading from an empty FIFO is undefined, so this flag generally only becomes set due to some kind of software error.
        ADD_BITFIELD_RW(RXUNDER, 8, 4)
        // State machine has stalled on full RX FIFO during a blocking PUSH, or an IN with autopush enabled. This flag is also set when a nonblocking PUSH to a full FIFO took place, in which case the state machine has dropped data. Write 1 to clear.
        ADD_BITFIELD_RW(RXSTALL, 0, 4)
    END_TYPE()

    // FIFO levels
    // Reset value: 0x00000000
    BEGIN_TYPE(FLEVEL_t, uint32_t)
        ADD_BITFIELD_RO(RX3, 28, 4)
        ADD_BITFIELD_RO(TX3, 24, 4)
        ADD_BITFIELD_RO(RX2, 20, 4)
        ADD_BITFIELD_RO(TX2, 16, 4)
        ADD_BITFIELD_RO(RX1, 12, 4)
        ADD_BITFIELD_RO(TX1, 8, 4)
        ADD_BITFIELD_RO(RX0, 4, 4)
        ADD_BITFIELD_RO(TX0, 0, 4)
    END_TYPE()

    // Direct write access to the TX FIFO for a state machine. Each write pushes one word to the FIFO. Attempting to write to a full FIFO has no effect on the FIFO state or contents, and sets the sticky FDEBUG_TXOVER error flag for this FIFO.
    // Reset value: 0x00000000
    typedef uint32_t TXF_t;

    // Direct read access to the RX FIFO for a state machine. Each read pops one word from the FIFO. Attempting to read from an empty FIFO has no effect on the FIFO state, and sets the sticky FDEBUG_RXUNDER error flag for this FIFO. The data returned to the system on a read from an empty FIFO is undefined.
    // Reset value: 0x00000000
    typedef uint32_t RXF_t;

    // State machine IRQ flags register. Write 1 to clear. There are 8 state machine IRQ flags, which can be set, cleared, and waited on by the state machines. There's no fixed association between flags and state machines -- any state machine can use any flag.
    // 
    // Any of the 8 flags can be used for timing synchronisation between state machines, using IRQ and WAIT instructions. The lower four of these flags are also routed out to system-level interrupt requests, alongside FIFO status interrupts -- see e.g. IRQ0_INTE.
    // Reset value: 0x00000000
    BEGIN_TYPE(IRQ_t, uint32_t)
        ADD_BITFIELD_RW(IRQ, 0, 8)
    END_TYPE()

    // Writing a 1 to each of these bits will forcibly assert the corresponding IRQ. Note this is different to the INTF register: writing here affects PIO internal state. INTF just asserts the processor-facing IRQ signal for testing ISRs, and is not visible to the state machines.
    // Reset value: 0x00000000
    BEGIN_TYPE(IRQ_FORCE_t, uint32_t)
        ADD_BITFIELD_WO(IRQ_FORCE, 0, 8)
    END_TYPE()

    // There is a 2-flipflop synchronizer on each GPIO input, which protects PIO logic from metastabilities. This increases input delay, and for fast synchronous IO (e.g. SPI) these synchronizers may need to be bypassed. Each bit in this register corresponds to one GPIO.
    // 0 -> input is synchronized (default)
    // 1 -> synchronizer is bypassed
    // If in doubt, leave this register as all zeroes.
    // Reset value: 0x00000000
    typedef uint32_t INPUT_SYNC_BYPASS_t;

    // Read to sample the pad output values PIO is currently driving to the GPIOs. On RP2040 there are 30 GPIOs, so the two most significant bits are hardwired to 0.
    // Reset value: 0x00000000
    typedef uint32_t DBG_PADOUT_t;

    // Read to sample the pad output enables (direction) PIO is currently driving to the GPIOs. On RP2040 there are 30 GPIOs, so the two most significant bits are hardwired to 0.
    // Reset value: 0x00000000
    typedef uint32_t DBG_PADOE_t;

    // The PIO hardware has some free parameters that may vary between chip products.
    // These should be provided in the chip datasheet, but are also exposed here.
    // Reset value: 0x00000000
    BEGIN_TYPE(DBG_CFGINFO_t, uint32_t)
        // The size of the instruction memory, measured in units of one instruction
        ADD_BITFIELD_RO(IMEM_SIZE, 16, 6)
        // The number of state machines this PIO instance is equipped with.
        ADD_BITFIELD_RO(SM_COUNT, 8, 4)
        // The depth of the state machine TX/RX FIFOs, measured in words.
        // Joining fifos via SHIFTCTRL_FJOIN gives one FIFO with double
        // this depth.
        ADD_BITFIELD_RO(FIFO_DEPTH, 0, 6)
    END_TYPE()

    // Write-only access to instruction memory
    // Reset value: 0x00000000
    BEGIN_TYPE(INSTR_MEM_t, uint32_t)
        ADD_BITFIELD_WO(INSTR, 0, 16)
    END_TYPE()

    // Clock divisor register for state machine 0
    // Frequency = clock freq / (CLKDIV_INT + CLKDIV_FRAC / 256)
    // Reset value: 0x00010000
    BEGIN_TYPE(SM_CLKDIV_t, uint32_t)
        // Effective frequency is sysclk/(int + frac/256).
        // Value of 0 is interpreted as 65536. If INT is 0, FRAC must also be 0.
        ADD_BITFIELD_RW(INT, 16, 16)
        // Fractional part of clock divisor
        ADD_BITFIELD_RW(FRAC, 8, 8)
    END_TYPE()

    // Execution/behavioural settings for state machine 0
    // Reset value: 0x0001f000
    BEGIN_TYPE(SM_EXECCTRL_t, uint32_t)
        // If 1, an instruction written to SMx_INSTR is stalled, and latched by the state machine. Will clear to 0 once this instruction completes.
        ADD_BITFIELD_RO(EXEC_STALLED, 31, 1)
        // If 1, the MSB of the Delay/Side-set instruction field is used as side-set enable, rather than a side-set data bit. This allows instructions to perform side-set optionally, rather than on every instruction, but the maximum possible side-set width is reduced from 5 to 4. Note that the value of PINCTRL_SIDESET_COUNT is inclusive of this enable bit.
        ADD_BITFIELD_RW(SIDE_EN, 30, 1)
        // If 1, side-set data is asserted to pin directions, instead of pin values
        ADD_BITFIELD_RW(SIDE_PINDIR, 29, 1)
        // The GPIO number to use as condition for JMP PIN. Unaffected by input mapping.
        ADD_BITFIELD_RW(JMP_PIN, 24, 5)
        // Which data bit to use for inline OUT enable
        ADD_BITFIELD_RW(OUT_EN_SEL, 19, 5)
        // If 1, use a bit of OUT data as an auxiliary write enable
        // When used in conjunction with OUT_STICKY, writes with an enable of 0 will
        // deassert the latest pin write. This can create useful masking/override behaviour
        // due to the priority ordering of state machine pin writes (SM0 < SM1 < ...)
        ADD_BITFIELD_RW(INLINE_OUT_EN, 18, 1)
        // Continuously assert the most recent OUT/SET to the pins
        ADD_BITFIELD_RW(OUT_STICKY, 17, 1)
        // After reaching this address, execution is wrapped to wrap_bottom.
        // If the instruction is a jump, and the jump condition is true, the jump takes priority.
        ADD_BITFIELD_RW(WRAP_TOP, 12, 5)
        // After reaching wrap_top, execution is wrapped to this address.
        ADD_BITFIELD_RW(WRAP_BOTTOM, 7, 5)
        // Comparison used for the MOV x, STATUS instruction.
        ADD_BITFIELD_RW(STATUS_SEL, 4, 1)
        // Comparison level for the MOV x, STATUS instruction
        ADD_BITFIELD_RW(STATUS_N, 0, 4)
    END_TYPE()

    // All-ones if TX FIFO level < N, otherwise all-zeroes
    static const uint32_t SM_EXECCTRL_STATUS_SEL__TXLEVEL = 0;
    // All-ones if RX FIFO level < N, otherwise all-zeroes
    static const uint32_t SM_EXECCTRL_STATUS_SEL__RXLEVEL = 1;

    // Control behaviour of the input/output shift registers for state machine 0
    // Reset value: 0x000c0000
    BEGIN_TYPE(SM_SHIFTCTRL_t, uint32_t)
        // When 1, RX FIFO steals the TX FIFO's storage, and becomes twice as deep.
        // TX FIFO is disabled as a result (always reads as both full and empty).
        // FIFOs are flushed when this bit is changed.
        ADD_BITFIELD_RW(FJOIN_RX, 31, 1)
        // When 1, TX FIFO steals the RX FIFO's storage, and becomes twice as deep.
        // RX FIFO is disabled as a result (always reads as both full and empty).
        // FIFOs are flushed when this bit is changed.
        ADD_BITFIELD_RW(FJOIN_TX, 30, 1)
        // Number of bits shifted out of OSR before autopull, or conditional pull (PULL IFEMPTY), will take place.
        // Write 0 for value of 32.
        ADD_BITFIELD_RW(PULL_THRESH, 25, 5)
        // Number of bits shifted into ISR before autopush, or conditional push (PUSH IFFULL), will take place.
        // Write 0 for value of 32.
        ADD_BITFIELD_RW(PUSH_THRESH, 20, 5)
        // 1 = shift out of output shift register to right. 0 = to left.
        ADD_BITFIELD_RW(OUT_SHIFTDIR, 19, 1)
        // 1 = shift input shift register to right (data enters from left). 0 = to left.
        ADD_BITFIELD_RW(IN_SHIFTDIR, 18, 1)
        // Pull automatically when the output shift register is emptied, i.e. on or following an OUT instruction which causes the output shift counter to reach or exceed PULL_THRESH.
        ADD_BITFIELD_RW(AUTOPULL, 17, 1)
        // Push automatically when the input shift register is filled, i.e. on an IN instruction which causes the input shift counter to reach or exceed PUSH_THRESH.
        ADD_BITFIELD_RW(AUTOPUSH, 16, 1)
    END_TYPE()

    // Current instruction address of state machine 0
    // Reset value: 0x00000000
    BEGIN_TYPE(SM_ADDR_t, uint32_t)
        ADD_BITFIELD_RO(ADDR, 0, 5)
    END_TYPE()

    // Read to see the instruction currently addressed by state machine 0's program counter
    // Write to execute an instruction immediately (including jumps) and then resume execution.
    // Reset value: 0x00000000
    BEGIN_TYPE(SM_INSTR_t, uint32_t)
        ADD_BITFIELD_RW(INSTR, 0, 16)
    END_TYPE()

    // State machine pin control
    // Reset value: 0x14000000
    BEGIN_TYPE(SM_PINCTRL_t, uint32_t)
        // The number of MSBs of the Delay/Side-set instruction field which are used for side-set. Inclusive of the enable bit, if present. Minimum of 0 (all delay bits, no side-set) and maximum of 5 (all side-set, no delay).
        ADD_BITFIELD_RW(SIDESET_COUNT, 29, 3)
        // The number of pins asserted by a SET. In the range 0 to 5 inclusive.
        ADD_BITFIELD_RW(SET_COUNT, 26, 3)
        // The number of pins asserted by an OUT PINS, OUT PINDIRS or MOV PINS instruction. In the range 0 to 32 inclusive.
        ADD_BITFIELD_RW(OUT_COUNT, 20, 6)
        // The pin which is mapped to the least-significant bit of a state machine's IN data bus. Higher-numbered pins are mapped to consecutively more-significant data bits, with a modulo of 32 applied to pin number.
        ADD_BITFIELD_RW(IN_BASE, 15, 5)
        // The lowest-numbered pin that will be affected by a side-set operation. The MSBs of an instruction's side-set/delay field (up to 5, determined by SIDESET_COUNT) are used for side-set data, with the remaining LSBs used for delay. The least-significant bit of the side-set portion is the bit written to this pin, with more-significant bits written to higher-numbered pins.
        ADD_BITFIELD_RW(SIDESET_BASE, 10, 5)
        // The lowest-numbered pin that will be affected by a SET PINS or SET PINDIRS instruction. The data written to this pin is the least-significant bit of the SET data.
        ADD_BITFIELD_RW(SET_BASE, 5, 5)
        // The lowest-numbered pin that will be affected by an OUT PINS, OUT PINDIRS or MOV PINS instruction. The data written to this pin will always be the least-significant bit of the OUT or MOV data.
        ADD_BITFIELD_RW(OUT_BASE, 0, 5)
    END_TYPE()

    // Raw Interrupts
    // Reset value: 0x00000000
    BEGIN_TYPE(INTR_t, uint32_t)
        ADD_BITFIELD_RO(SM3, 11, 1)
        ADD_BITFIELD_RO(SM2, 10, 1)
        ADD_BITFIELD_RO(SM1, 9, 1)
        ADD_BITFIELD_RO(SM0, 8, 1)
        ADD_BITFIELD_RO(SM3_TXNFULL, 7, 1)
        ADD_BITFIELD_RO(SM2_TXNFULL, 6, 1)
        ADD_BITFIELD_RO(SM1_TXNFULL, 5, 1)
        ADD_BITFIELD_RO(SM0_TXNFULL, 4, 1)
        ADD_BITFIELD_RO(SM3_RXNEMPTY, 3, 1)
        ADD_BITFIELD_RO(SM2_RXNEMPTY, 2, 1)
        ADD_BITFIELD_RO(SM1_RXNEMPTY, 1, 1)
        ADD_BITFIELD_RO(SM0_RXNEMPTY, 0, 1)
    END_TYPE()

    // Interrupt Enable for irq0
    // Reset value: 0x00000000
    BEGIN_TYPE(IRQ0_INTE_t, uint32_t)
        ADD_BITFIELD_RW(SM3, 11, 1)
        ADD_BITFIELD_RW(SM2, 10, 1)
        ADD_BITFIELD_RW(SM1, 9, 1)
        ADD_BITFIELD_RW(SM0, 8, 1)
        ADD_BITFIELD_RW(SM3_TXNFULL, 7, 1)
        ADD_BITFIELD_RW(SM2_TXNFULL, 6, 1)
        ADD_BITFIELD_RW(SM1_TXNFULL, 5, 1)
        ADD_BITFIELD_RW(SM0_TXNFULL, 4, 1)
        ADD_BITFIELD_RW(SM3_RXNEMPTY, 3, 1)
        ADD_BITFIELD_RW(SM2_RXNEMPTY, 2, 1)
        ADD_BITFIELD_RW(SM1_RXNEMPTY, 1, 1)
        ADD_BITFIELD_RW(SM0_RXNEMPTY, 0, 1)
    END_TYPE()

    // Interrupt Force for irq0
    // Reset value: 0x00000000
    BEGIN_TYPE(IRQ0_INTF_t, uint32_t)
        ADD_BITFIELD_RW(SM3, 11, 1)
        ADD_BITFIELD_RW(SM2, 10, 1)
        ADD_BITFIELD_RW(SM1, 9, 1)
        ADD_BITFIELD_RW(SM0, 8, 1)
        ADD_BITFIELD_RW(SM3_TXNFULL, 7, 1)
        ADD_BITFIELD_RW(SM2_TXNFULL, 6, 1)
        ADD_BITFIELD_RW(SM1_TXNFULL, 5, 1)
        ADD_BITFIELD_RW(SM0_TXNFULL, 4, 1)
        ADD_BITFIELD_RW(SM3_RXNEMPTY, 3, 1)
        ADD_BITFIELD_RW(SM2_RXNEMPTY, 2, 1)
        ADD_BITFIELD_RW(SM1_RXNEMPTY, 1, 1)
        ADD_BITFIELD_RW(SM0_RXNEMPTY, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for irq0
    // Reset value: 0x00000000
    BEGIN_TYPE(IRQ0_INTS_t, uint32_t)
        ADD_BITFIELD_RO(SM3, 11, 1)
        ADD_BITFIELD_RO(SM2, 10, 1)
        ADD_BITFIELD_RO(SM1, 9, 1)
        ADD_BITFIELD_RO(SM0, 8, 1)
        ADD_BITFIELD_RO(SM3_TXNFULL, 7, 1)
        ADD_BITFIELD_RO(SM2_TXNFULL, 6, 1)
        ADD_BITFIELD_RO(SM1_TXNFULL, 5, 1)
        ADD_BITFIELD_RO(SM0_TXNFULL, 4, 1)
        ADD_BITFIELD_RO(SM3_RXNEMPTY, 3, 1)
        ADD_BITFIELD_RO(SM2_RXNEMPTY, 2, 1)
        ADD_BITFIELD_RO(SM1_RXNEMPTY, 1, 1)
        ADD_BITFIELD_RO(SM0_RXNEMPTY, 0, 1)
    END_TYPE()

    // Interrupt Enable for irq1
    // Reset value: 0x00000000
    BEGIN_TYPE(IRQ1_INTE_t, uint32_t)
        ADD_BITFIELD_RW(SM3, 11, 1)
        ADD_BITFIELD_RW(SM2, 10, 1)
        ADD_BITFIELD_RW(SM1, 9, 1)
        ADD_BITFIELD_RW(SM0, 8, 1)
        ADD_BITFIELD_RW(SM3_TXNFULL, 7, 1)
        ADD_BITFIELD_RW(SM2_TXNFULL, 6, 1)
        ADD_BITFIELD_RW(SM1_TXNFULL, 5, 1)
        ADD_BITFIELD_RW(SM0_TXNFULL, 4, 1)
        ADD_BITFIELD_RW(SM3_RXNEMPTY, 3, 1)
        ADD_BITFIELD_RW(SM2_RXNEMPTY, 2, 1)
        ADD_BITFIELD_RW(SM1_RXNEMPTY, 1, 1)
        ADD_BITFIELD_RW(SM0_RXNEMPTY, 0, 1)
    END_TYPE()

    // Interrupt Force for irq1
    // Reset value: 0x00000000
    BEGIN_TYPE(IRQ1_INTF_t, uint32_t)
        ADD_BITFIELD_RW(SM3, 11, 1)
        ADD_BITFIELD_RW(SM2, 10, 1)
        ADD_BITFIELD_RW(SM1, 9, 1)
        ADD_BITFIELD_RW(SM0, 8, 1)
        ADD_BITFIELD_RW(SM3_TXNFULL, 7, 1)
        ADD_BITFIELD_RW(SM2_TXNFULL, 6, 1)
        ADD_BITFIELD_RW(SM1_TXNFULL, 5, 1)
        ADD_BITFIELD_RW(SM0_TXNFULL, 4, 1)
        ADD_BITFIELD_RW(SM3_RXNEMPTY, 3, 1)
        ADD_BITFIELD_RW(SM2_RXNEMPTY, 2, 1)
        ADD_BITFIELD_RW(SM1_RXNEMPTY, 1, 1)
        ADD_BITFIELD_RW(SM0_RXNEMPTY, 0, 1)
    END_TYPE()

    // Interrupt status after masking & forcing for irq1
    // Reset value: 0x00000000
    BEGIN_TYPE(IRQ1_INTS_t, uint32_t)
        ADD_BITFIELD_RO(SM3, 11, 1)
        ADD_BITFIELD_RO(SM2, 10, 1)
        ADD_BITFIELD_RO(SM1, 9, 1)
        ADD_BITFIELD_RO(SM0, 8, 1)
        ADD_BITFIELD_RO(SM3_TXNFULL, 7, 1)
        ADD_BITFIELD_RO(SM2_TXNFULL, 6, 1)
        ADD_BITFIELD_RO(SM1_TXNFULL, 5, 1)
        ADD_BITFIELD_RO(SM0_TXNFULL, 4, 1)
        ADD_BITFIELD_RO(SM3_RXNEMPTY, 3, 1)
        ADD_BITFIELD_RO(SM2_RXNEMPTY, 2, 1)
        ADD_BITFIELD_RO(SM1_RXNEMPTY, 1, 1)
        ADD_BITFIELD_RO(SM0_RXNEMPTY, 0, 1)
    END_TYPE()

    struct PIO0_t {
        CTRL_t                        CTRL;
        FSTAT_t                       FSTAT;
        FDEBUG_t                      FDEBUG;
        FLEVEL_t                      FLEVEL;
        TXF_t                         TXF[4];
        RXF_t                         RXF[4];
        IRQ_t                         IRQ;
        IRQ_FORCE_t                   IRQ_FORCE;
        INPUT_SYNC_BYPASS_t           INPUT_SYNC_BYPASS;
        DBG_PADOUT_t                  DBG_PADOUT;
        DBG_PADOE_t                   DBG_PADOE;
        DBG_CFGINFO_t                 DBG_CFGINFO;
        INSTR_MEM_t                   INSTR_MEM[32];
        SM_CLKDIV_t                   SM0_CLKDIV;
        SM_EXECCTRL_t                 SM0_EXECCTRL;
        SM_SHIFTCTRL_t                SM0_SHIFTCTRL;
        SM_ADDR_t                     SM0_ADDR;
        SM_INSTR_t                    SM0_INSTR;
        SM_PINCTRL_t                  SM0_PINCTRL;
        SM_CLKDIV_t                   SM1_CLKDIV;
        SM_EXECCTRL_t                 SM1_EXECCTRL;
        SM_SHIFTCTRL_t                SM1_SHIFTCTRL;
        SM_ADDR_t                     SM1_ADDR;
        SM_INSTR_t                    SM1_INSTR;
        SM_PINCTRL_t                  SM1_PINCTRL;
        SM_CLKDIV_t                   SM2_CLKDIV;
        SM_EXECCTRL_t                 SM2_EXECCTRL;
        SM_SHIFTCTRL_t                SM2_SHIFTCTRL;
        SM_ADDR_t                     SM2_ADDR;
        SM_INSTR_t                    SM2_INSTR;
        SM_PINCTRL_t                  SM2_PINCTRL;
        SM_CLKDIV_t                   SM3_CLKDIV;
        SM_EXECCTRL_t                 SM3_EXECCTRL;
        SM_SHIFTCTRL_t                SM3_SHIFTCTRL;
        SM_ADDR_t                     SM3_ADDR;
        SM_INSTR_t                    SM3_INSTR;
        SM_PINCTRL_t                  SM3_PINCTRL;
        INTR_t                        INTR;
        IRQ0_INTE_t                   IRQ0_INTE;
        IRQ0_INTF_t                   IRQ0_INTF;
        IRQ0_INTS_t                   IRQ0_INTS;
        IRQ1_INTE_t                   IRQ1_INTE;
        IRQ1_INTF_t                   IRQ1_INTF;
        IRQ1_INTS_t                   IRQ1_INTS;
    };

    static PIO0_t & PIO0     = (*(PIO0_t *)0x50200000);
    static PIO0_t & PIO0_XOR = (*(PIO0_t *)0x50201000);
    static PIO0_t & PIO0_SET = (*(PIO0_t *)0x50202000);
    static PIO0_t & PIO0_CLR = (*(PIO0_t *)0x50203000);

} // _PIO0_

namespace _PIO1_  {

    static _PIO0_::PIO0_t & PIO1     = (*(_PIO0_::PIO0_t *)0x50300000);
    static _PIO0_::PIO0_t & PIO1_XOR = (*(_PIO0_::PIO0_t *)0x50301000);
    static _PIO0_::PIO0_t & PIO1_SET = (*(_PIO0_::PIO0_t *)0x50302000);
    static _PIO0_::PIO0_t & PIO1_CLR = (*(_PIO0_::PIO0_t *)0x50303000);

} // _PIO1_

// Single-cycle IO block
// Provides core-local and inter-core hardware for the two processors, with single-cycle access.
namespace _SIO_  {

    // Processor core identifier
    // Value is 0 when read from processor core 0, and 1 when read from processor core 1.
    // Reset value: 0x00000000
    typedef uint32_t CPUID_t;

    // Input value for GPIO pins
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_IN_t, uint32_t)
        // Input value for GPIO0...29
        ADD_BITFIELD_RO(GPIO_IN, 0, 30)
    END_TYPE()

    // Input value for QSPI pins
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_HI_IN_t, uint32_t)
        // Input value on QSPI IO in order 0..5: SCLK, SSn, SD0, SD1, SD2, SD3
        ADD_BITFIELD_RO(GPIO_HI_IN, 0, 6)
    END_TYPE()

    // GPIO output value
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_OUT_t, uint32_t)
        // Set output level (1/0 -> high/low) for GPIO0...29.
        // Reading back gives the last value written, NOT the input value from the pins.
        // If core 0 and core 1 both write to GPIO_OUT simultaneously (or to a SET/CLR/XOR alias),
        // the result is as though the write from core 0 took place first,
        // and the write from core 1 was then applied to that intermediate result.
        ADD_BITFIELD_RW(GPIO_OUT, 0, 30)
    END_TYPE()

    // GPIO output value set
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_OUT_SET_t, uint32_t)
        // Perform an atomic bit-set on GPIO_OUT, i.e. `GPIO_OUT |= wdata`
        ADD_BITFIELD_WO(GPIO_OUT_SET, 0, 30)
    END_TYPE()

    // GPIO output value clear
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_OUT_CLR_t, uint32_t)
        // Perform an atomic bit-clear on GPIO_OUT, i.e. `GPIO_OUT &= ~wdata`
        ADD_BITFIELD_WO(GPIO_OUT_CLR, 0, 30)
    END_TYPE()

    // GPIO output value XOR
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_OUT_XOR_t, uint32_t)
        // Perform an atomic bitwise XOR on GPIO_OUT, i.e. `GPIO_OUT ^= wdata`
        ADD_BITFIELD_WO(GPIO_OUT_XOR, 0, 30)
    END_TYPE()

    // GPIO output enable
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_OE_t, uint32_t)
        // Set output enable (1/0 -> output/input) for GPIO0...29.
        // Reading back gives the last value written.
        // If core 0 and core 1 both write to GPIO_OE simultaneously (or to a SET/CLR/XOR alias),
        // the result is as though the write from core 0 took place first,
        // and the write from core 1 was then applied to that intermediate result.
        ADD_BITFIELD_RW(GPIO_OE, 0, 30)
    END_TYPE()

    // GPIO output enable set
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_OE_SET_t, uint32_t)
        // Perform an atomic bit-set on GPIO_OE, i.e. `GPIO_OE |= wdata`
        ADD_BITFIELD_WO(GPIO_OE_SET, 0, 30)
    END_TYPE()

    // GPIO output enable clear
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_OE_CLR_t, uint32_t)
        // Perform an atomic bit-clear on GPIO_OE, i.e. `GPIO_OE &= ~wdata`
        ADD_BITFIELD_WO(GPIO_OE_CLR, 0, 30)
    END_TYPE()

    // GPIO output enable XOR
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_OE_XOR_t, uint32_t)
        // Perform an atomic bitwise XOR on GPIO_OE, i.e. `GPIO_OE ^= wdata`
        ADD_BITFIELD_WO(GPIO_OE_XOR, 0, 30)
    END_TYPE()

    // QSPI output value
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_HI_OUT_t, uint32_t)
        // Set output level (1/0 -> high/low) for QSPI IO0...5.
        // Reading back gives the last value written, NOT the input value from the pins.
        // If core 0 and core 1 both write to GPIO_HI_OUT simultaneously (or to a SET/CLR/XOR alias),
        // the result is as though the write from core 0 took place first,
        // and the write from core 1 was then applied to that intermediate result.
        ADD_BITFIELD_RW(GPIO_HI_OUT, 0, 6)
    END_TYPE()

    // QSPI output value set
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_HI_OUT_SET_t, uint32_t)
        // Perform an atomic bit-set on GPIO_HI_OUT, i.e. `GPIO_HI_OUT |= wdata`
        ADD_BITFIELD_WO(GPIO_HI_OUT_SET, 0, 6)
    END_TYPE()

    // QSPI output value clear
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_HI_OUT_CLR_t, uint32_t)
        // Perform an atomic bit-clear on GPIO_HI_OUT, i.e. `GPIO_HI_OUT &= ~wdata`
        ADD_BITFIELD_WO(GPIO_HI_OUT_CLR, 0, 6)
    END_TYPE()

    // QSPI output value XOR
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_HI_OUT_XOR_t, uint32_t)
        // Perform an atomic bitwise XOR on GPIO_HI_OUT, i.e. `GPIO_HI_OUT ^= wdata`
        ADD_BITFIELD_WO(GPIO_HI_OUT_XOR, 0, 6)
    END_TYPE()

    // QSPI output enable
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_HI_OE_t, uint32_t)
        // Set output enable (1/0 -> output/input) for QSPI IO0...5.
        // Reading back gives the last value written.
        // If core 0 and core 1 both write to GPIO_HI_OE simultaneously (or to a SET/CLR/XOR alias),
        // the result is as though the write from core 0 took place first,
        // and the write from core 1 was then applied to that intermediate result.
        ADD_BITFIELD_RW(GPIO_HI_OE, 0, 6)
    END_TYPE()

    // QSPI output enable set
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_HI_OE_SET_t, uint32_t)
        // Perform an atomic bit-set on GPIO_HI_OE, i.e. `GPIO_HI_OE |= wdata`
        ADD_BITFIELD_WO(GPIO_HI_OE_SET, 0, 6)
    END_TYPE()

    // QSPI output enable clear
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_HI_OE_CLR_t, uint32_t)
        // Perform an atomic bit-clear on GPIO_HI_OE, i.e. `GPIO_HI_OE &= ~wdata`
        ADD_BITFIELD_WO(GPIO_HI_OE_CLR, 0, 6)
    END_TYPE()

    // QSPI output enable XOR
    // Reset value: 0x00000000
    BEGIN_TYPE(GPIO_HI_OE_XOR_t, uint32_t)
        // Perform an atomic bitwise XOR on GPIO_HI_OE, i.e. `GPIO_HI_OE ^= wdata`
        ADD_BITFIELD_WO(GPIO_HI_OE_XOR, 0, 6)
    END_TYPE()

    // Status register for inter-core FIFOs (mailboxes).
    // There is one FIFO in the core 0 -> core 1 direction, and one core 1 -> core 0. Both are 32 bits wide and 8 words deep.
    // Core 0 can see the read side of the 1->0 FIFO (RX), and the write side of 0->1 FIFO (TX).
    // Core 1 can see the read side of the 0->1 FIFO (RX), and the write side of 1->0 FIFO (TX).
    // The SIO IRQ for each core is the logical OR of the VLD, WOF and ROE fields of its FIFO_ST register.
    // Reset value: 0x00000002
    BEGIN_TYPE(FIFO_ST_t, uint32_t)
        // Sticky flag indicating the RX FIFO was read when empty. This read was ignored by the FIFO.
        ADD_BITFIELD_RW(ROE, 3, 1)
        // Sticky flag indicating the TX FIFO was written when full. This write was ignored by the FIFO.
        ADD_BITFIELD_RW(WOF, 2, 1)
        // Value is 1 if this core's TX FIFO is not full (i.e. if FIFO_WR is ready for more data)
        ADD_BITFIELD_RO(RDY, 1, 1)
        // Value is 1 if this core's RX FIFO is not empty (i.e. if FIFO_RD is valid)
        ADD_BITFIELD_RO(VLD, 0, 1)
    END_TYPE()

    // Write access to this core's TX FIFO
    // Reset value: 0x00000000
    typedef uint32_t FIFO_WR_t;

    // Read access to this core's RX FIFO
    // Reset value: 0x00000000
    typedef uint32_t FIFO_RD_t;

    // Spinlock state
    // A bitmap containing the state of all 32 spinlocks (1=locked).
    // Mainly intended for debugging.
    // Reset value: 0x00000000
    typedef uint32_t SPINLOCK_ST_t;

    // Divider unsigned dividend
    // Write to the DIVIDEND operand of the divider, i.e. the p in `p / q`.
    // Any operand write starts a new calculation. The results appear in QUOTIENT, REMAINDER.
    // UDIVIDEND/SDIVIDEND are aliases of the same internal register. The U alias starts an
    // unsigned calculation, and the S alias starts a signed calculation.
    // Reset value: 0x00000000
    typedef uint32_t DIV_UDIVIDEND_t;

    // Divider unsigned divisor
    // Write to the DIVISOR operand of the divider, i.e. the q in `p / q`.
    // Any operand write starts a new calculation. The results appear in QUOTIENT, REMAINDER.
    // UDIVISOR/SDIVISOR are aliases of the same internal register. The U alias starts an
    // unsigned calculation, and the S alias starts a signed calculation.
    // Reset value: 0x00000000
    typedef uint32_t DIV_UDIVISOR_t;

    // Divider signed dividend
    // The same as UDIVIDEND, but starts a signed calculation, rather than unsigned.
    // Reset value: 0x00000000
    typedef uint32_t DIV_SDIVIDEND_t;

    // Divider signed divisor
    // The same as UDIVISOR, but starts a signed calculation, rather than unsigned.
    // Reset value: 0x00000000
    typedef uint32_t DIV_SDIVISOR_t;

    // Divider result quotient
    // The result of `DIVIDEND / DIVISOR` (division). Contents undefined while CSR_READY is low.
    // For signed calculations, QUOTIENT is negative when the signs of DIVIDEND and DIVISOR differ.
    // This register can be written to directly, for context save/restore purposes. This halts any
    // in-progress calculation and sets the CSR_READY and CSR_DIRTY flags.
    // Reading from QUOTIENT clears the CSR_DIRTY flag, so should read results in the order
    // REMAINDER, QUOTIENT if CSR_DIRTY is used.
    // Reset value: 0x00000000
    typedef uint32_t DIV_QUOTIENT_t;

    // Divider result remainder
    // The result of `DIVIDEND % DIVISOR` (modulo). Contents undefined while CSR_READY is low.
    // For signed calculations, REMAINDER is negative only when DIVIDEND is negative.
    // This register can be written to directly, for context save/restore purposes. This halts any
    // in-progress calculation and sets the CSR_READY and CSR_DIRTY flags.
    // Reset value: 0x00000000
    typedef uint32_t DIV_REMAINDER_t;

    // Control and status register for divider.
    // Reset value: 0x00000001
    BEGIN_TYPE(DIV_CSR_t, uint32_t)
        // Changes to 1 when any register is written, and back to 0 when QUOTIENT is read.
        // Software can use this flag to make save/restore more efficient (skip if not DIRTY).
        // If the flag is used in this way, it's recommended to either read QUOTIENT only,
        // or REMAINDER and then QUOTIENT, to prevent data loss on context switch.
        ADD_BITFIELD_RO(DIRTY, 1, 1)
        // Reads as 0 when a calculation is in progress, 1 otherwise.
        // Writing an operand (xDIVIDEND, xDIVISOR) will immediately start a new calculation, no
        // matter if one is already in progress.
        // Writing to a result register will immediately terminate any in-progress calculation
        // and set the READY and DIRTY flags.
        ADD_BITFIELD_RO(READY, 0, 1)
    END_TYPE()

    // Read/write access to accumulator 0
    // Reset value: 0x00000000
    typedef uint32_t INTERP0_ACCUM0_t;

    // Read/write access to accumulator 1
    // Reset value: 0x00000000
    typedef uint32_t INTERP0_ACCUM1_t;

    // Read/write access to BASE0 register.
    // Reset value: 0x00000000
    typedef uint32_t INTERP0_BASE0_t;

    // Read/write access to BASE1 register.
    // Reset value: 0x00000000
    typedef uint32_t INTERP0_BASE1_t;

    // Read/write access to BASE2 register.
    // Reset value: 0x00000000
    typedef uint32_t INTERP0_BASE2_t;

    // Read LANE0 result, and simultaneously write lane results to both accumulators (POP).
    // Reset value: 0x00000000
    typedef uint32_t INTERP0_POP_LANE0_t;

    // Read LANE1 result, and simultaneously write lane results to both accumulators (POP).
    // Reset value: 0x00000000
    typedef uint32_t INTERP0_POP_LANE1_t;

    // Read FULL result, and simultaneously write lane results to both accumulators (POP).
    // Reset value: 0x00000000
    typedef uint32_t INTERP0_POP_FULL_t;

    // Read LANE0 result, without altering any internal state (PEEK).
    // Reset value: 0x00000000
    typedef uint32_t INTERP0_PEEK_LANE0_t;

    // Read LANE1 result, without altering any internal state (PEEK).
    // Reset value: 0x00000000
    typedef uint32_t INTERP0_PEEK_LANE1_t;

    // Read FULL result, without altering any internal state (PEEK).
    // Reset value: 0x00000000
    typedef uint32_t INTERP0_PEEK_FULL_t;

    // Control register for lane 0
    // Reset value: 0x00000000
    BEGIN_TYPE(INTERP0_CTRL_LANE0_t, uint32_t)
        // Set if either OVERF0 or OVERF1 is set.
        ADD_BITFIELD_RO(OVERF, 25, 1)
        // Indicates if any masked-off MSBs in ACCUM1 are set.
        ADD_BITFIELD_RO(OVERF1, 24, 1)
        // Indicates if any masked-off MSBs in ACCUM0 are set.
        ADD_BITFIELD_RO(OVERF0, 23, 1)
        // Only present on INTERP0 on each core. If BLEND mode is enabled:
        // - LANE1 result is a linear interpolation between BASE0 and BASE1, controlled
        // by the 8 LSBs of lane 1 shift and mask value (a fractional number between
        // 0 and 255/256ths)
        // - LANE0 result does not have BASE0 added (yields only the 8 LSBs of lane 1 shift+mask value)
        // - FULL result does not have lane 1 shift+mask value added (BASE2 + lane 0 shift+mask)
        // LANE1 SIGNED flag controls whether the interpolation is signed or unsigned.
        ADD_BITFIELD_RW(BLEND, 21, 1)
        // ORed into bits 29:28 of the lane result presented to the processor on the bus.
        // No effect on the internal 32-bit datapath. Handy for using a lane to generate sequence
        // of pointers into flash or SRAM.
        ADD_BITFIELD_RW(FORCE_MSB, 19, 2)
        // If 1, mask + shift is bypassed for LANE0 result. This does not affect FULL result.
        ADD_BITFIELD_RW(ADD_RAW, 18, 1)
        // If 1, feed the opposite lane's result into this lane's accumulator on POP.
        ADD_BITFIELD_RW(CROSS_RESULT, 17, 1)
        // If 1, feed the opposite lane's accumulator into this lane's shift + mask hardware.
        // Takes effect even if ADD_RAW is set (the CROSS_INPUT mux is before the shift+mask bypass)
        ADD_BITFIELD_RW(CROSS_INPUT, 16, 1)
        // If SIGNED is set, the shifted and masked accumulator value is sign-extended to 32 bits
        // before adding to BASE0, and LANE0 PEEK/POP appear extended to 32 bits when read by processor.
        ADD_BITFIELD_RW(SIGNED, 15, 1)
        // The most-significant bit allowed to pass by the mask (inclusive)
        // Setting MSB < LSB may cause chip to turn inside-out
        ADD_BITFIELD_RW(MASK_MSB, 10, 5)
        // The least-significant bit allowed to pass by the mask (inclusive)
        ADD_BITFIELD_RW(MASK_LSB, 5, 5)
        // Logical right-shift applied to accumulator before masking
        ADD_BITFIELD_RW(SHIFT, 0, 5)
    END_TYPE()

    // Control register for lane 1
    // Reset value: 0x00000000
    BEGIN_TYPE(INTERP0_CTRL_LANE1_t, uint32_t)
        // ORed into bits 29:28 of the lane result presented to the processor on the bus.
        // No effect on the internal 32-bit datapath. Handy for using a lane to generate sequence
        // of pointers into flash or SRAM.
        ADD_BITFIELD_RW(FORCE_MSB, 19, 2)
        // If 1, mask + shift is bypassed for LANE1 result. This does not affect FULL result.
        ADD_BITFIELD_RW(ADD_RAW, 18, 1)
        // If 1, feed the opposite lane's result into this lane's accumulator on POP.
        ADD_BITFIELD_RW(CROSS_RESULT, 17, 1)
        // If 1, feed the opposite lane's accumulator into this lane's shift + mask hardware.
        // Takes effect even if ADD_RAW is set (the CROSS_INPUT mux is before the shift+mask bypass)
        ADD_BITFIELD_RW(CROSS_INPUT, 16, 1)
        // If SIGNED is set, the shifted and masked accumulator value is sign-extended to 32 bits
        // before adding to BASE1, and LANE1 PEEK/POP appear extended to 32 bits when read by processor.
        ADD_BITFIELD_RW(SIGNED, 15, 1)
        // The most-significant bit allowed to pass by the mask (inclusive)
        // Setting MSB < LSB may cause chip to turn inside-out
        ADD_BITFIELD_RW(MASK_MSB, 10, 5)
        // The least-significant bit allowed to pass by the mask (inclusive)
        ADD_BITFIELD_RW(MASK_LSB, 5, 5)
        // Logical right-shift applied to accumulator before masking
        ADD_BITFIELD_RW(SHIFT, 0, 5)
    END_TYPE()

    // Values written here are atomically added to ACCUM0
    // Reading yields lane 0's raw shift and mask value (BASE0 not added).
    // Reset value: 0x00000000
    BEGIN_TYPE(INTERP0_ACCUM0_ADD_t, uint32_t)
        ADD_BITFIELD_RW(INTERP0_ACCUM0_ADD, 0, 24)
    END_TYPE()

    // Values written here are atomically added to ACCUM1
    // Reading yields lane 1's raw shift and mask value (BASE1 not added).
    // Reset value: 0x00000000
    BEGIN_TYPE(INTERP0_ACCUM1_ADD_t, uint32_t)
        ADD_BITFIELD_RW(INTERP0_ACCUM1_ADD, 0, 24)
    END_TYPE()

    // On write, the lower 16 bits go to BASE0, upper bits to BASE1 simultaneously.
    // Each half is sign-extended to 32 bits if that lane's SIGNED flag is set.
    // Reset value: 0x00000000
    typedef uint32_t INTERP0_BASE_1AND0_t;

    // Read/write access to accumulator 0
    // Reset value: 0x00000000
    typedef uint32_t INTERP1_ACCUM0_t;

    // Read/write access to accumulator 1
    // Reset value: 0x00000000
    typedef uint32_t INTERP1_ACCUM1_t;

    // Read/write access to BASE0 register.
    // Reset value: 0x00000000
    typedef uint32_t INTERP1_BASE0_t;

    // Read/write access to BASE1 register.
    // Reset value: 0x00000000
    typedef uint32_t INTERP1_BASE1_t;

    // Read/write access to BASE2 register.
    // Reset value: 0x00000000
    typedef uint32_t INTERP1_BASE2_t;

    // Read LANE0 result, and simultaneously write lane results to both accumulators (POP).
    // Reset value: 0x00000000
    typedef uint32_t INTERP1_POP_LANE0_t;

    // Read LANE1 result, and simultaneously write lane results to both accumulators (POP).
    // Reset value: 0x00000000
    typedef uint32_t INTERP1_POP_LANE1_t;

    // Read FULL result, and simultaneously write lane results to both accumulators (POP).
    // Reset value: 0x00000000
    typedef uint32_t INTERP1_POP_FULL_t;

    // Read LANE0 result, without altering any internal state (PEEK).
    // Reset value: 0x00000000
    typedef uint32_t INTERP1_PEEK_LANE0_t;

    // Read LANE1 result, without altering any internal state (PEEK).
    // Reset value: 0x00000000
    typedef uint32_t INTERP1_PEEK_LANE1_t;

    // Read FULL result, without altering any internal state (PEEK).
    // Reset value: 0x00000000
    typedef uint32_t INTERP1_PEEK_FULL_t;

    // Control register for lane 0
    // Reset value: 0x00000000
    BEGIN_TYPE(INTERP1_CTRL_LANE0_t, uint32_t)
        // Set if either OVERF0 or OVERF1 is set.
        ADD_BITFIELD_RO(OVERF, 25, 1)
        // Indicates if any masked-off MSBs in ACCUM1 are set.
        ADD_BITFIELD_RO(OVERF1, 24, 1)
        // Indicates if any masked-off MSBs in ACCUM0 are set.
        ADD_BITFIELD_RO(OVERF0, 23, 1)
        // Only present on INTERP1 on each core. If CLAMP mode is enabled:
        // - LANE0 result is shifted and masked ACCUM0, clamped by a lower bound of
        // BASE0 and an upper bound of BASE1.
        // - Signedness of these comparisons is determined by LANE0_CTRL_SIGNED
        ADD_BITFIELD_RW(CLAMP, 22, 1)
        // ORed into bits 29:28 of the lane result presented to the processor on the bus.
        // No effect on the internal 32-bit datapath. Handy for using a lane to generate sequence
        // of pointers into flash or SRAM.
        ADD_BITFIELD_RW(FORCE_MSB, 19, 2)
        // If 1, mask + shift is bypassed for LANE0 result. This does not affect FULL result.
        ADD_BITFIELD_RW(ADD_RAW, 18, 1)
        // If 1, feed the opposite lane's result into this lane's accumulator on POP.
        ADD_BITFIELD_RW(CROSS_RESULT, 17, 1)
        // If 1, feed the opposite lane's accumulator into this lane's shift + mask hardware.
        // Takes effect even if ADD_RAW is set (the CROSS_INPUT mux is before the shift+mask bypass)
        ADD_BITFIELD_RW(CROSS_INPUT, 16, 1)
        // If SIGNED is set, the shifted and masked accumulator value is sign-extended to 32 bits
        // before adding to BASE0, and LANE0 PEEK/POP appear extended to 32 bits when read by processor.
        ADD_BITFIELD_RW(SIGNED, 15, 1)
        // The most-significant bit allowed to pass by the mask (inclusive)
        // Setting MSB < LSB may cause chip to turn inside-out
        ADD_BITFIELD_RW(MASK_MSB, 10, 5)
        // The least-significant bit allowed to pass by the mask (inclusive)
        ADD_BITFIELD_RW(MASK_LSB, 5, 5)
        // Logical right-shift applied to accumulator before masking
        ADD_BITFIELD_RW(SHIFT, 0, 5)
    END_TYPE()

    // Control register for lane 1
    // Reset value: 0x00000000
    BEGIN_TYPE(INTERP1_CTRL_LANE1_t, uint32_t)
        // ORed into bits 29:28 of the lane result presented to the processor on the bus.
        // No effect on the internal 32-bit datapath. Handy for using a lane to generate sequence
        // of pointers into flash or SRAM.
        ADD_BITFIELD_RW(FORCE_MSB, 19, 2)
        // If 1, mask + shift is bypassed for LANE1 result. This does not affect FULL result.
        ADD_BITFIELD_RW(ADD_RAW, 18, 1)
        // If 1, feed the opposite lane's result into this lane's accumulator on POP.
        ADD_BITFIELD_RW(CROSS_RESULT, 17, 1)
        // If 1, feed the opposite lane's accumulator into this lane's shift + mask hardware.
        // Takes effect even if ADD_RAW is set (the CROSS_INPUT mux is before the shift+mask bypass)
        ADD_BITFIELD_RW(CROSS_INPUT, 16, 1)
        // If SIGNED is set, the shifted and masked accumulator value is sign-extended to 32 bits
        // before adding to BASE1, and LANE1 PEEK/POP appear extended to 32 bits when read by processor.
        ADD_BITFIELD_RW(SIGNED, 15, 1)
        // The most-significant bit allowed to pass by the mask (inclusive)
        // Setting MSB < LSB may cause chip to turn inside-out
        ADD_BITFIELD_RW(MASK_MSB, 10, 5)
        // The least-significant bit allowed to pass by the mask (inclusive)
        ADD_BITFIELD_RW(MASK_LSB, 5, 5)
        // Logical right-shift applied to accumulator before masking
        ADD_BITFIELD_RW(SHIFT, 0, 5)
    END_TYPE()

    // Values written here are atomically added to ACCUM0
    // Reading yields lane 0's raw shift and mask value (BASE0 not added).
    // Reset value: 0x00000000
    BEGIN_TYPE(INTERP1_ACCUM0_ADD_t, uint32_t)
        ADD_BITFIELD_RW(INTERP1_ACCUM0_ADD, 0, 24)
    END_TYPE()

    // Values written here are atomically added to ACCUM1
    // Reading yields lane 1's raw shift and mask value (BASE1 not added).
    // Reset value: 0x00000000
    BEGIN_TYPE(INTERP1_ACCUM1_ADD_t, uint32_t)
        ADD_BITFIELD_RW(INTERP1_ACCUM1_ADD, 0, 24)
    END_TYPE()

    // On write, the lower 16 bits go to BASE0, upper bits to BASE1 simultaneously.
    // Each half is sign-extended to 32 bits if that lane's SIGNED flag is set.
    // Reset value: 0x00000000
    typedef uint32_t INTERP1_BASE_1AND0_t;

    // Reading from a spinlock address will:
    // - Return 0 if lock is already locked
    // - Otherwise return nonzero, and simultaneously claim the lock
    // 
    // Writing (any value) releases the lock.
    // If core 0 and core 1 attempt to claim the same lock simultaneously, core 0 wins.
    // The value returned on success is 0x1 << lock number.
    // Reset value: 0x00000000
    typedef uint32_t SPINLOCK_t;

    struct SIO_t {
        CPUID_t                       CPUID;
        GPIO_IN_t                     GPIO_IN;
        GPIO_HI_IN_t                  GPIO_HI_IN;
        uint32_t                      reserved0;
        GPIO_OUT_t                    GPIO_OUT;
        GPIO_OUT_SET_t                GPIO_OUT_SET;
        GPIO_OUT_CLR_t                GPIO_OUT_CLR;
        GPIO_OUT_XOR_t                GPIO_OUT_XOR;
        GPIO_OE_t                     GPIO_OE;
        GPIO_OE_SET_t                 GPIO_OE_SET;
        GPIO_OE_CLR_t                 GPIO_OE_CLR;
        GPIO_OE_XOR_t                 GPIO_OE_XOR;
        GPIO_HI_OUT_t                 GPIO_HI_OUT;
        GPIO_HI_OUT_SET_t             GPIO_HI_OUT_SET;
        GPIO_HI_OUT_CLR_t             GPIO_HI_OUT_CLR;
        GPIO_HI_OUT_XOR_t             GPIO_HI_OUT_XOR;
        GPIO_HI_OE_t                  GPIO_HI_OE;
        GPIO_HI_OE_SET_t              GPIO_HI_OE_SET;
        GPIO_HI_OE_CLR_t              GPIO_HI_OE_CLR;
        GPIO_HI_OE_XOR_t              GPIO_HI_OE_XOR;
        FIFO_ST_t                     FIFO_ST;
        FIFO_WR_t                     FIFO_WR;
        FIFO_RD_t                     FIFO_RD;
        SPINLOCK_ST_t                 SPINLOCK_ST;
        DIV_UDIVIDEND_t               DIV_UDIVIDEND;
        DIV_UDIVISOR_t                DIV_UDIVISOR;
        DIV_SDIVIDEND_t               DIV_SDIVIDEND;
        DIV_SDIVISOR_t                DIV_SDIVISOR;
        DIV_QUOTIENT_t                DIV_QUOTIENT;
        DIV_REMAINDER_t               DIV_REMAINDER;
        DIV_CSR_t                     DIV_CSR;
        uint32_t                      reserved1;
        INTERP0_ACCUM0_t              INTERP0_ACCUM0;
        INTERP0_ACCUM1_t              INTERP0_ACCUM1;
        INTERP0_BASE0_t               INTERP0_BASE0;
        INTERP0_BASE1_t               INTERP0_BASE1;
        INTERP0_BASE2_t               INTERP0_BASE2;
        INTERP0_POP_LANE0_t           INTERP0_POP_LANE0;
        INTERP0_POP_LANE1_t           INTERP0_POP_LANE1;
        INTERP0_POP_FULL_t            INTERP0_POP_FULL;
        INTERP0_PEEK_LANE0_t          INTERP0_PEEK_LANE0;
        INTERP0_PEEK_LANE1_t          INTERP0_PEEK_LANE1;
        INTERP0_PEEK_FULL_t           INTERP0_PEEK_FULL;
        INTERP0_CTRL_LANE0_t          INTERP0_CTRL_LANE0;
        INTERP0_CTRL_LANE1_t          INTERP0_CTRL_LANE1;
        INTERP0_ACCUM0_ADD_t          INTERP0_ACCUM0_ADD;
        INTERP0_ACCUM1_ADD_t          INTERP0_ACCUM1_ADD;
        INTERP0_BASE_1AND0_t          INTERP0_BASE_1AND0;
        INTERP1_ACCUM0_t              INTERP1_ACCUM0;
        INTERP1_ACCUM1_t              INTERP1_ACCUM1;
        INTERP1_BASE0_t               INTERP1_BASE0;
        INTERP1_BASE1_t               INTERP1_BASE1;
        INTERP1_BASE2_t               INTERP1_BASE2;
        INTERP1_POP_LANE0_t           INTERP1_POP_LANE0;
        INTERP1_POP_LANE1_t           INTERP1_POP_LANE1;
        INTERP1_POP_FULL_t            INTERP1_POP_FULL;
        INTERP1_PEEK_LANE0_t          INTERP1_PEEK_LANE0;
        INTERP1_PEEK_LANE1_t          INTERP1_PEEK_LANE1;
        INTERP1_PEEK_FULL_t           INTERP1_PEEK_FULL;
        INTERP1_CTRL_LANE0_t          INTERP1_CTRL_LANE0;
        INTERP1_CTRL_LANE1_t          INTERP1_CTRL_LANE1;
        INTERP1_ACCUM0_ADD_t          INTERP1_ACCUM0_ADD;
        INTERP1_ACCUM1_ADD_t          INTERP1_ACCUM1_ADD;
        INTERP1_BASE_1AND0_t          INTERP1_BASE_1AND0;
        SPINLOCK_t                    SPINLOCK[32];
    };

    static SIO_t & SIO     = (*(SIO_t *)0xd0000000);

} // _SIO_

namespace _PPB_  {

    // Use the SysTick Control and Status Register to enable the SysTick features.
    // Reset value: 0x00000000
    BEGIN_TYPE(SYST_CSR_t, uint32_t)
        // Returns 1 if timer counted to 0 since last time this was read. Clears on read by application or debugger.
        ADD_BITFIELD_RO(COUNTFLAG, 16, 1)
        // SysTick clock source. Always reads as one if SYST_CALIB reports NOREF.
        // Selects the SysTick timer clock source:
        // 0 = External reference clock.
        // 1 = Processor clock.
        ADD_BITFIELD_RW(CLKSOURCE, 2, 1)
        // Enables SysTick exception request:
        // 0 = Counting down to zero does not assert the SysTick exception request.
        // 1 = Counting down to zero to asserts the SysTick exception request.
        ADD_BITFIELD_RW(TICKINT, 1, 1)
        // Enable SysTick counter:
        // 0 = Counter disabled.
        // 1 = Counter enabled.
        ADD_BITFIELD_RW(ENABLE, 0, 1)
    END_TYPE()

    // Use the SysTick Reload Value Register to specify the start value to load into the current value register when the counter reaches 0. It can be any value between 0 and 0x00FFFFFF. A start value of 0 is possible, but has no effect because the SysTick interrupt and COUNTFLAG are activated when counting from 1 to 0. The reset value of this register is UNKNOWN.
    // To generate a multi-shot timer with a period of N processor clock cycles, use a RELOAD value of N-1. For example, if the SysTick interrupt is required every 100 clock pulses, set RELOAD to 99.
    // Reset value: 0x00000000
    BEGIN_TYPE(SYST_RVR_t, uint32_t)
        // Value to load into the SysTick Current Value Register when the counter reaches 0.
        ADD_BITFIELD_RW(RELOAD, 0, 24)
    END_TYPE()

    // Use the SysTick Current Value Register to find the current value in the register. The reset value of this register is UNKNOWN.
    // Reset value: 0x00000000
    BEGIN_TYPE(SYST_CVR_t, uint32_t)
        // Reads return the current value of the SysTick counter. This register is write-clear. Writing to it with any value clears the register to 0. Clearing this register also clears the COUNTFLAG bit of the SysTick Control and Status Register.
        ADD_BITFIELD_RW(CURRENT, 0, 24)
    END_TYPE()

    // Use the SysTick Calibration Value Register to enable software to scale to any required speed using divide and multiply.
    // Reset value: 0x00000000
    BEGIN_TYPE(SYST_CALIB_t, uint32_t)
        // If reads as 1, the Reference clock is not provided - the CLKSOURCE bit of the SysTick Control and Status register will be forced to 1 and cannot be cleared to 0.
        ADD_BITFIELD_RO(NOREF, 31, 1)
        // If reads as 1, the calibration value for 10ms is inexact (due to clock frequency).
        ADD_BITFIELD_RO(SKEW, 30, 1)
        // An optional Reload value to be used for 10ms (100Hz) timing, subject to system clock skew errors. If the value reads as 0, the calibration value is not known.
        ADD_BITFIELD_RO(TENMS, 0, 24)
    END_TYPE()

    // Use the Interrupt Set-Enable Register to enable interrupts and determine which interrupts are currently enabled.
    // If a pending interrupt is enabled, the NVIC activates the interrupt based on its priority. If an interrupt is not enabled, asserting its interrupt signal changes the interrupt state to pending, but the NVIC never activates the interrupt, regardless of its priority.
    // Reset value: 0x00000000
    BEGIN_TYPE(NVIC_ISER_t, uint32_t)
        // Interrupt set-enable bits.
        // Write:
        // 0 = No effect.
        // 1 = Enable interrupt.
        // Read:
        // 0 = Interrupt disabled.
        // 1 = Interrupt enabled.
        ADD_BITFIELD_RW(SETENA, 0, 32)
    END_TYPE()

    // Use the Interrupt Clear-Enable Registers to disable interrupts and determine which interrupts are currently enabled.
    // Reset value: 0x00000000
    BEGIN_TYPE(NVIC_ICER_t, uint32_t)
        // Interrupt clear-enable bits.
        // Write:
        // 0 = No effect.
        // 1 = Disable interrupt.
        // Read:
        // 0 = Interrupt disabled.
        // 1 = Interrupt enabled.
        ADD_BITFIELD_RW(CLRENA, 0, 32)
    END_TYPE()

    // The NVIC_ISPR forces interrupts into the pending state, and shows which interrupts are pending.
    // Reset value: 0x00000000
    BEGIN_TYPE(NVIC_ISPR_t, uint32_t)
        // Interrupt set-pending bits.
        // Write:
        // 0 = No effect.
        // 1 = Changes interrupt state to pending.
        // Read:
        // 0 = Interrupt is not pending.
        // 1 = Interrupt is pending.
        // Note: Writing 1 to the NVIC_ISPR bit corresponding to:
        // An interrupt that is pending has no effect.
        // A disabled interrupt sets the state of that interrupt to pending.
        ADD_BITFIELD_RW(SETPEND, 0, 32)
    END_TYPE()

    // Use the Interrupt Clear-Pending Register to clear pending interrupts and determine which interrupts are currently pending.
    // Reset value: 0x00000000
    BEGIN_TYPE(NVIC_ICPR_t, uint32_t)
        // Interrupt clear-pending bits.
        // Write:
        // 0 = No effect.
        // 1 = Removes pending state and interrupt.
        // Read:
        // 0 = Interrupt is not pending.
        // 1 = Interrupt is pending.
        ADD_BITFIELD_RW(CLRPEND, 0, 32)
    END_TYPE()

    // Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. 0 is the highest priority, and 3 is the lowest.
    // Note: Writing 1 to an NVIC_ICPR bit does not affect the active state of the corresponding interrupt.
    // These registers are only word-accessible
    // Reset value: 0x00000000
    BEGIN_TYPE(NVIC_IPR0_t, uint32_t)
        // Priority of interrupt 3
        ADD_BITFIELD_RW(IP_3, 30, 2)
        // Priority of interrupt 2
        ADD_BITFIELD_RW(IP_2, 22, 2)
        // Priority of interrupt 1
        ADD_BITFIELD_RW(IP_1, 14, 2)
        // Priority of interrupt 0
        ADD_BITFIELD_RW(IP_0, 6, 2)
    END_TYPE()

    // Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. 0 is the highest priority, and 3 is the lowest.
    // Reset value: 0x00000000
    BEGIN_TYPE(NVIC_IPR1_t, uint32_t)
        // Priority of interrupt 7
        ADD_BITFIELD_RW(IP_7, 30, 2)
        // Priority of interrupt 6
        ADD_BITFIELD_RW(IP_6, 22, 2)
        // Priority of interrupt 5
        ADD_BITFIELD_RW(IP_5, 14, 2)
        // Priority of interrupt 4
        ADD_BITFIELD_RW(IP_4, 6, 2)
    END_TYPE()

    // Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. 0 is the highest priority, and 3 is the lowest.
    // Reset value: 0x00000000
    BEGIN_TYPE(NVIC_IPR2_t, uint32_t)
        // Priority of interrupt 11
        ADD_BITFIELD_RW(IP_11, 30, 2)
        // Priority of interrupt 10
        ADD_BITFIELD_RW(IP_10, 22, 2)
        // Priority of interrupt 9
        ADD_BITFIELD_RW(IP_9, 14, 2)
        // Priority of interrupt 8
        ADD_BITFIELD_RW(IP_8, 6, 2)
    END_TYPE()

    // Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. 0 is the highest priority, and 3 is the lowest.
    // Reset value: 0x00000000
    BEGIN_TYPE(NVIC_IPR3_t, uint32_t)
        // Priority of interrupt 15
        ADD_BITFIELD_RW(IP_15, 30, 2)
        // Priority of interrupt 14
        ADD_BITFIELD_RW(IP_14, 22, 2)
        // Priority of interrupt 13
        ADD_BITFIELD_RW(IP_13, 14, 2)
        // Priority of interrupt 12
        ADD_BITFIELD_RW(IP_12, 6, 2)
    END_TYPE()

    // Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. 0 is the highest priority, and 3 is the lowest.
    // Reset value: 0x00000000
    BEGIN_TYPE(NVIC_IPR4_t, uint32_t)
        // Priority of interrupt 19
        ADD_BITFIELD_RW(IP_19, 30, 2)
        // Priority of interrupt 18
        ADD_BITFIELD_RW(IP_18, 22, 2)
        // Priority of interrupt 17
        ADD_BITFIELD_RW(IP_17, 14, 2)
        // Priority of interrupt 16
        ADD_BITFIELD_RW(IP_16, 6, 2)
    END_TYPE()

    // Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. 0 is the highest priority, and 3 is the lowest.
    // Reset value: 0x00000000
    BEGIN_TYPE(NVIC_IPR5_t, uint32_t)
        // Priority of interrupt 23
        ADD_BITFIELD_RW(IP_23, 30, 2)
        // Priority of interrupt 22
        ADD_BITFIELD_RW(IP_22, 22, 2)
        // Priority of interrupt 21
        ADD_BITFIELD_RW(IP_21, 14, 2)
        // Priority of interrupt 20
        ADD_BITFIELD_RW(IP_20, 6, 2)
    END_TYPE()

    // Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. 0 is the highest priority, and 3 is the lowest.
    // Reset value: 0x00000000
    BEGIN_TYPE(NVIC_IPR6_t, uint32_t)
        // Priority of interrupt 27
        ADD_BITFIELD_RW(IP_27, 30, 2)
        // Priority of interrupt 26
        ADD_BITFIELD_RW(IP_26, 22, 2)
        // Priority of interrupt 25
        ADD_BITFIELD_RW(IP_25, 14, 2)
        // Priority of interrupt 24
        ADD_BITFIELD_RW(IP_24, 6, 2)
    END_TYPE()

    // Use the Interrupt Priority Registers to assign a priority from 0 to 3 to each of the available interrupts. 0 is the highest priority, and 3 is the lowest.
    // Reset value: 0x00000000
    BEGIN_TYPE(NVIC_IPR7_t, uint32_t)
        // Priority of interrupt 31
        ADD_BITFIELD_RW(IP_31, 30, 2)
        // Priority of interrupt 30
        ADD_BITFIELD_RW(IP_30, 22, 2)
        // Priority of interrupt 29
        ADD_BITFIELD_RW(IP_29, 14, 2)
        // Priority of interrupt 28
        ADD_BITFIELD_RW(IP_28, 6, 2)
    END_TYPE()

    // Read the CPU ID Base Register to determine: the ID number of the processor core, the version number of the processor core, the implementation details of the processor core.
    // Reset value: 0x410cc601
    BEGIN_TYPE(CPUID_t, uint32_t)
        // Implementor code: 0x41 = ARM
        ADD_BITFIELD_RO(IMPLEMENTER, 24, 8)
        // Major revision number n in the rnpm revision status:
        // 0x0 = Revision 0.
        ADD_BITFIELD_RO(VARIANT, 20, 4)
        // Constant that defines the architecture of the processor:
        // 0xC = ARMv6-M architecture.
        ADD_BITFIELD_RO(ARCHITECTURE, 16, 4)
        // Number of processor within family: 0xC60 = Cortex-M0+
        ADD_BITFIELD_RO(PARTNO, 4, 12)
        // Minor revision number m in the rnpm revision status:
        // 0x1 = Patch 1.
        ADD_BITFIELD_RO(REVISION, 0, 4)
    END_TYPE()

    // Use the Interrupt Control State Register to set a pending Non-Maskable Interrupt (NMI), set or clear a pending PendSV, set or clear a pending SysTick, check for pending exceptions, check the vector number of the highest priority pended exception, check the vector number of the active exception.
    // Reset value: 0x00000000
    BEGIN_TYPE(ICSR_t, uint32_t)
        // Setting this bit will activate an NMI. Since NMI is the highest priority exception, it will activate as soon as it is registered.
        // NMI set-pending bit.
        // Write:
        // 0 = No effect.
        // 1 = Changes NMI exception state to pending.
        // Read:
        // 0 = NMI exception is not pending.
        // 1 = NMI exception is pending.
        // Because NMI is the highest-priority exception, normally the processor enters the NMI
        // exception handler as soon as it detects a write of 1 to this bit. Entering the handler then clears
        // this bit to 0. This means a read of this bit by the NMI exception handler returns 1 only if the
        // NMI signal is reasserted while the processor is executing that handler.
        ADD_BITFIELD_RW(NMIPENDSET, 31, 1)
        // PendSV set-pending bit.
        // Write:
        // 0 = No effect.
        // 1 = Changes PendSV exception state to pending.
        // Read:
        // 0 = PendSV exception is not pending.
        // 1 = PendSV exception is pending.
        // Writing 1 to this bit is the only way to set the PendSV exception state to pending.
        ADD_BITFIELD_RW(PENDSVSET, 28, 1)
        // PendSV clear-pending bit.
        // Write:
        // 0 = No effect.
        // 1 = Removes the pending state from the PendSV exception.
        ADD_BITFIELD_RW(PENDSVCLR, 27, 1)
        // SysTick exception set-pending bit.
        // Write:
        // 0 = No effect.
        // 1 = Changes SysTick exception state to pending.
        // Read:
        // 0 = SysTick exception is not pending.
        // 1 = SysTick exception is pending.
        ADD_BITFIELD_RW(PENDSTSET, 26, 1)
        // SysTick exception clear-pending bit.
        // Write:
        // 0 = No effect.
        // 1 = Removes the pending state from the SysTick exception.
        // This bit is WO. On a register read its value is Unknown.
        ADD_BITFIELD_RW(PENDSTCLR, 25, 1)
        // The system can only access this bit when the core is halted. It indicates that a pending interrupt is to be taken in the next running cycle. If C_MASKINTS is clear in the Debug Halting Control and Status Register, the interrupt is serviced.
        ADD_BITFIELD_RO(ISRPREEMPT, 23, 1)
        // External interrupt pending flag
        ADD_BITFIELD_RO(ISRPENDING, 22, 1)
        // Indicates the exception number for the highest priority pending exception: 0 = no pending exceptions. Non zero = The pending state includes the effect of memory-mapped enable and mask registers. It does not include the PRIMASK special-purpose register qualifier.
        ADD_BITFIELD_RO(VECTPENDING, 12, 9)
        // Active exception number field. Reset clears the VECTACTIVE field.
        ADD_BITFIELD_RO(VECTACTIVE, 0, 9)
    END_TYPE()

    // The VTOR holds the vector table offset address.
    // Reset value: 0x00000000
    BEGIN_TYPE(VTOR_t, uint32_t)
        // Bits [31:8] of the indicate the vector table offset address.
        ADD_BITFIELD_RW(TBLOFF, 8, 24)
    END_TYPE()

    // Use the Application Interrupt and Reset Control Register to: determine data endianness, clear all active state information from debug halt mode, request a system reset.
    // Reset value: 0x00000000
    BEGIN_TYPE(AIRCR_t, uint32_t)
        // Register key:
        // Reads as Unknown
        // On writes, write 0x05FA to VECTKEY, otherwise the write is ignored.
        ADD_BITFIELD_RW(VECTKEY, 16, 16)
        // Data endianness implemented:
        // 0 = Little-endian.
        ADD_BITFIELD_RO(ENDIANESS, 15, 1)
        // Writing 1 to this bit causes the SYSRESETREQ signal to the outer system to be asserted to request a reset. The intention is to force a large system reset of all major components except for debug. The C_HALT bit in the DHCSR is cleared as a result of the system reset requested. The debugger does not lose contact with the device.
        ADD_BITFIELD_RW(SYSRESETREQ, 2, 1)
        // Clears all active state information for fixed and configurable exceptions. This bit: is self-clearing, can only be set by the DAP when the core is halted.  When set: clears all active exception status of the processor, forces a return to Thread mode, forces an IPSR of 0. A debugger must re-initialize the stack.
        ADD_BITFIELD_RW(VECTCLRACTIVE, 1, 1)
    END_TYPE()

    // System Control Register. Use the System Control Register for power-management functions: signal to the system when the processor can enter a low power state, control how the processor enters and exits low power states.
    // Reset value: 0x00000000
    BEGIN_TYPE(SCR_t, uint32_t)
        // Send Event on Pending bit:
        // 0 = Only enabled interrupts or events can wakeup the processor, disabled interrupts are excluded.
        // 1 = Enabled events and all interrupts, including disabled interrupts, can wakeup the processor.
        // When an event or interrupt becomes pending, the event signal wakes up the processor from WFE. If the
        // processor is not waiting for an event, the event is registered and affects the next WFE.
        // The processor also wakes up on execution of an SEV instruction or an external event.
        ADD_BITFIELD_RW(SEVONPEND, 4, 1)
        // Controls whether the processor uses sleep or deep sleep as its low power mode:
        // 0 = Sleep.
        // 1 = Deep sleep.
        ADD_BITFIELD_RW(SLEEPDEEP, 2, 1)
        // Indicates sleep-on-exit when returning from Handler mode to Thread mode:
        // 0 = Do not sleep when returning to Thread mode.
        // 1 = Enter sleep, or deep sleep, on return from an ISR to Thread mode.
        // Setting this bit to 1 enables an interrupt driven application to avoid returning to an empty main application.
        ADD_BITFIELD_RW(SLEEPONEXIT, 1, 1)
    END_TYPE()

    // The Configuration and Control Register permanently enables stack alignment and causes unaligned accesses to result in a Hard Fault.
    // Reset value: 0x00000000
    BEGIN_TYPE(CCR_t, uint32_t)
        // Always reads as one, indicates 8-byte stack alignment on exception entry. On exception entry, the processor uses bit[9] of the stacked PSR to indicate the stack alignment. On return from the exception it uses this stacked bit to restore the correct stack alignment.
        ADD_BITFIELD_RO(STKALIGN, 9, 1)
        // Always reads as one, indicates that all unaligned accesses generate a HardFault.
        ADD_BITFIELD_RO(UNALIGN_TRP, 3, 1)
    END_TYPE()

    // System handlers are a special class of exception handler that can have their priority set to any of the priority levels. Use the System Handler Priority Register 2 to set the priority of SVCall.
    // Reset value: 0x00000000
    BEGIN_TYPE(SHPR2_t, uint32_t)
        // Priority of system handler 11, SVCall
        ADD_BITFIELD_RW(PRI_11, 30, 2)
    END_TYPE()

    // System handlers are a special class of exception handler that can have their priority set to any of the priority levels. Use the System Handler Priority Register 3 to set the priority of PendSV and SysTick.
    // Reset value: 0x00000000
    BEGIN_TYPE(SHPR3_t, uint32_t)
        // Priority of system handler 15, SysTick
        ADD_BITFIELD_RW(PRI_15, 30, 2)
        // Priority of system handler 14, PendSV
        ADD_BITFIELD_RW(PRI_14, 22, 2)
    END_TYPE()

    // Use the System Handler Control and State Register to determine or clear the pending status of SVCall.
    // Reset value: 0x00000000
    BEGIN_TYPE(SHCSR_t, uint32_t)
        // Reads as 1 if SVCall is Pending.  Write 1 to set pending SVCall, write 0 to clear pending SVCall.
        ADD_BITFIELD_RW(SVCALLPENDED, 15, 1)
    END_TYPE()

    // Read the MPU Type Register to determine if the processor implements an MPU, and how many regions the MPU supports.
    // Reset value: 0x00000800
    BEGIN_TYPE(MPU_TYPE_t, uint32_t)
        // Instruction region. Reads as zero as ARMv6-M only supports a unified MPU.
        ADD_BITFIELD_RO(IREGION, 16, 8)
        // Number of regions supported by the MPU.
        ADD_BITFIELD_RO(DREGION, 8, 8)
        // Indicates support for separate instruction and data address maps. Reads as 0 as ARMv6-M only supports a unified MPU.
        ADD_BITFIELD_RO(SEPARATE, 0, 1)
    END_TYPE()

    // Use the MPU Control Register to enable and disable the MPU, and to control whether the default memory map is enabled as a background region for privileged accesses, and whether the MPU is enabled for HardFaults and NMIs.
    // Reset value: 0x00000000
    BEGIN_TYPE(MPU_CTRL_t, uint32_t)
        // Controls whether the default memory map is enabled as a background region for privileged accesses. This bit is ignored when ENABLE is clear.
        // 0 = If the MPU is enabled, disables use of the default memory map. Any memory access to a location not
        // covered by any enabled region causes a fault.
        // 1 = If the MPU is enabled, enables use of the default memory map as a background region for privileged software accesses.
        // When enabled, the background region acts as if it is region number -1. Any region that is defined and enabled has priority over this default map.
        ADD_BITFIELD_RW(PRIVDEFENA, 2, 1)
        // Controls the use of the MPU for HardFaults and NMIs. Setting this bit when ENABLE is clear results in UNPREDICTABLE behaviour.
        // When the MPU is enabled:
        // 0 = MPU is disabled during HardFault and NMI handlers, regardless of the value of the ENABLE bit.
        // 1 = the MPU is enabled during HardFault and NMI handlers.
        ADD_BITFIELD_RW(HFNMIENA, 1, 1)
        // Enables the MPU. If the MPU is disabled, privileged and unprivileged accesses use the default memory map.
        // 0 = MPU disabled.
        // 1 = MPU enabled.
        ADD_BITFIELD_RW(ENABLE, 0, 1)
    END_TYPE()

    // Use the MPU Region Number Register to select the region currently accessed by MPU_RBAR and MPU_RASR.
    // Reset value: 0x00000000
    BEGIN_TYPE(MPU_RNR_t, uint32_t)
        // Indicates the MPU region referenced by the MPU_RBAR and MPU_RASR registers.
        // The MPU supports 8 memory regions, so the permitted values of this field are 0-7.
        ADD_BITFIELD_RW(REGION, 0, 4)
    END_TYPE()

    // Read the MPU Region Base Address Register to determine the base address of the region identified by MPU_RNR. Write to update the base address of said region or that of a specified region, with whose number MPU_RNR will also be updated.
    // Reset value: 0x00000000
    BEGIN_TYPE(MPU_RBAR_t, uint32_t)
        // Base address of the region.
        ADD_BITFIELD_RW(ADDR, 8, 24)
        // On writes, indicates whether the write must update the base address of the region identified by the REGION field, updating the MPU_RNR to indicate this new region.
        // Write:
        // 0 = MPU_RNR not changed, and the processor:
        // Updates the base address for the region specified in the MPU_RNR.
        // Ignores the value of the REGION field.
        // 1 = The processor:
        // Updates the value of the MPU_RNR to the value of the REGION field.
        // Updates the base address for the region specified in the REGION field.
        // Always reads as zero.
        ADD_BITFIELD_RW(VALID, 4, 1)
        // On writes, specifies the number of the region whose base address to update provided VALID is set written as 1. On reads, returns bits [3:0] of MPU_RNR.
        ADD_BITFIELD_RW(REGION, 0, 4)
    END_TYPE()

    // Use the MPU Region Attribute and Size Register to define the size, access behaviour and memory type of the region identified by MPU_RNR, and enable that region.
    // Reset value: 0x00000000
    BEGIN_TYPE(MPU_RASR_t, uint32_t)
        // The MPU Region Attribute field. Use to define the region attribute control.
        // 28 = XN: Instruction access disable bit:
        // 0 = Instruction fetches enabled.
        // 1 = Instruction fetches disabled.
        // 26:24 = AP: Access permission field
        // 18 = S: Shareable bit
        // 17 = C: Cacheable bit
        // 16 = B: Bufferable bit
        ADD_BITFIELD_RW(ATTRS, 16, 16)
        // Subregion Disable. For regions of 256 bytes or larger, each bit of this field controls whether one of the eight equal subregions is enabled.
        ADD_BITFIELD_RW(SRD, 8, 8)
        // Indicates the region size. Region size in bytes = 2^(SIZE+1). The minimum permitted value is 7 (b00111) = 256Bytes
        ADD_BITFIELD_RW(SIZE, 1, 5)
        // Enables the region.
        ADD_BITFIELD_RW(ENABLE, 0, 1)
    END_TYPE()

    struct PPB_t {
        uint32_t                      reserved0[14340];
        SYST_CSR_t                    SYST_CSR;
        SYST_RVR_t                    SYST_RVR;
        SYST_CVR_t                    SYST_CVR;
        SYST_CALIB_t                  SYST_CALIB;
        uint32_t                      reserved1[56];
        NVIC_ISER_t                   NVIC_ISER;
        uint32_t                      reserved2[31];
        NVIC_ICER_t                   NVIC_ICER;
        uint32_t                      reserved3[31];
        NVIC_ISPR_t                   NVIC_ISPR;
        uint32_t                      reserved4[31];
        NVIC_ICPR_t                   NVIC_ICPR;
        uint32_t                      reserved5[95];
        NVIC_IPR0_t                   NVIC_IPR0;
        NVIC_IPR1_t                   NVIC_IPR1;
        NVIC_IPR2_t                   NVIC_IPR2;
        NVIC_IPR3_t                   NVIC_IPR3;
        NVIC_IPR4_t                   NVIC_IPR4;
        NVIC_IPR5_t                   NVIC_IPR5;
        NVIC_IPR6_t                   NVIC_IPR6;
        NVIC_IPR7_t                   NVIC_IPR7;
        uint32_t                      reserved6[568];
        CPUID_t                       CPUID;
        ICSR_t                        ICSR;
        VTOR_t                        VTOR;
        AIRCR_t                       AIRCR;
        SCR_t                         SCR;
        CCR_t                         CCR;
        uint32_t                      reserved7;
        SHPR2_t                       SHPR2;
        SHPR3_t                       SHPR3;
        SHCSR_t                       SHCSR;
        uint32_t                      reserved8[26];
        MPU_TYPE_t                    MPU_TYPE;
        MPU_CTRL_t                    MPU_CTRL;
        MPU_RNR_t                     MPU_RNR;
        MPU_RBAR_t                    MPU_RBAR;
        MPU_RASR_t                    MPU_RASR;
    };

    static PPB_t & PPB     = (*(PPB_t *)0xe0000000);

} // _PPB_


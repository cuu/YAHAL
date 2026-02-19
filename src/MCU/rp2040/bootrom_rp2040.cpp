//
// Created by andreas on 01.01.26.
//

#include "bootrom_rp2040.h"
#include "RP2040.h"

using namespace _IO_QSPI_;
using namespace _XIP_SSI_;

// Static members
bootrom_rp2040::rom_header_t *  bootrom_rp2040::_rom_header {0x00000000};
uint8_t bootrom_rp2040::_rx_buffer[13] {0};
uint8_t bootrom_rp2040::_tx_buffer[13] {0};

std::array<uint8_t, 8> COPY_TO_RAM bootrom_rp2040::read_unique_id() {

    // Memory barrier
    asm volatile("" : : : "memory");

    bootrom_rp2040::connect_internal_flash();
    bootrom_rp2040::flash_exit_xip();

    // Activate CS line
    IO_QSPI.GPIO_QSPI_SS_CTRL.OUTOVER = GPIO_QSPI_SS_CTRL_OUTOVER__LOW;

    for (int i=0; i < 13; ++i) _rx_buffer[i] = _tx_buffer[i] = 0;
    _tx_buffer[0] = 0x4b;
    size_t tx_idx = 0;
    size_t rx_idx = 0;
    while (tx_idx < 13 || rx_idx < 13) {
        if (XIP_SSI.SR.TFNF) {
            XIP_SSI.DR0 = _tx_buffer[tx_idx++];
        }
        if (XIP_SSI.SR.RFNE) {
            _rx_buffer[rx_idx++] = XIP_SSI.DR0;
        }
    }
    // Deactivate CS line
    IO_QSPI.GPIO_QSPI_SS_CTRL.OUTOVER = GPIO_QSPI_SS_CTRL_OUTOVER__HIGH;

    bootrom_rp2040::flash_flush_cache();
    bootrom_rp2040::flash_enter_cmd_xip();

    // Copy the last 8 bytes from the receive-buffer
    // 1 byte cmd + 4 bytes dummy + 8 bytes serial ID
    std::array<uint8_t, 8> arr {0};
    for(int i=5; i < 13; ++i) arr[i-5] = _rx_buffer[i];
    return arr;
}

std::array<char, 17> bootrom_rp2040::read_unique_id_string() {
    auto id = read_unique_id();
    std::array<char, 17> res {0};
    size_t res_index = 0;
    for(uint8_t & c : id) {
        uint8_t n = (c >> 4);
        res[res_index++] = n > 9 ? n+'A'-10 : n+'0';
        n = c & 0xf;
        res[res_index++] = n > 9 ? n+'A'-10 : n+'0';
    }
    return res;
}

/*
 * pio_rp2040.h
 *
 *  Created on: 25.12.2022
 *      Author: andreas
 */

#ifndef _PIO_RP2040_H_
#define _PIO_RP2040_H_

#include <cstdint>
#include "RP2040.h"

using namespace _PIO0_;

//////////////////////////////////////////////////////////////
// enums and methods to generate state machine instructions //
//////////////////////////////////////////////////////////////
enum class jmp_cond_t : uint16_t {
    always       = 0,
    Xzero        = 1,
    Xdec         = 2,
    Yzero        = 3,
    Ydec         = 4,
    XnotY        = 5,
    PIN          = 6,
    OSRnot_empty = 7
};

inline uint16_t op_JMP(uint8_t    delay_sideset,
                       jmp_cond_t cond,
                       uint8_t    addr) {
    return 0x0000 |
           ((delay_sideset & 0x1f)      << 8) |
           (static_cast<uint16_t>(cond) << 5) |
           (addr & 0x1f);
}

inline bool is_JMP(uint16_t opcode) {
    return (opcode & 0xe000) == 0;
}

enum class wait_pol_t : uint16_t {
    wait_for_1   = 1,
    wait_for_0   = 0
};

enum class wait_src_t : uint16_t {
    GPIO         = 0,
    PIN          = 1,
    IRQ          = 2
};

inline uint16_t op_WAIT(uint8_t    delay_sideset,
                        wait_pol_t polarity,
                        wait_src_t source,
                        uint8_t    index) {
    return 0x2000 |
           ((delay_sideset & 0x1f)          << 8) |
           (static_cast<uint16_t>(polarity) << 7) |
           (static_cast<uint16_t>(source)   << 5) |
           (index & 0x1f);
}

enum class in_src_t : uint16_t {
    PINS         = 0,
    X            = 1,
    Y            = 2,
    ZEROS        = 3,
    ISR          = 6,
    OSR          = 7
};

inline uint16_t op_IN(uint8_t  delay_sideset,
                      in_src_t src,
                      uint8_t  bitcount) {
    return 0x4000 |
           ((delay_sideset & 0x1f)     << 8) |
           (static_cast<uint16_t>(src) << 5) |
           (bitcount & 0x1f);
}

enum class out_dest_t : uint16_t {
    PINS         = 0,
    X            = 1,
    Y            = 2,
    ZEROS        = 3,
    PINDIRS      = 4,
    PC           = 5,
    ISR          = 6,
    EXEC         = 7
};

inline uint16_t op_OUT(uint8_t    delay_sideset,
                       out_dest_t dest,
                       uint8_t    bitcount) {
    return 0x6000 |
           ((delay_sideset & 0x1f)      << 8) |
           (static_cast<uint16_t>(dest) << 5) |
           (bitcount & 0x1f);
}

const uint16_t IFFULL = 0x40;
const uint16_t BLOCK  = 0x20;

inline uint16_t op_PUSH(uint8_t  delay_sideset,
                        uint16_t flags) {
    return 0x8000 |
           ((delay_sideset & 0x1f) << 8) |
           flags;
}

inline uint16_t op_PULL(uint8_t  delay_sideset,
                        uint16_t flags) {
    return 0x8080 |
           ((delay_sideset & 0x1f) << 8) |
           flags;
}

enum class mov_dest_t : uint16_t {
    PINS         = 0,
    X            = 1,
    Y            = 2,
    EXEC         = 4,
    PC           = 5,
    ISR          = 6,
    OSR          = 7
};

enum class mov_op_t : uint16_t {
    NONE         = 0,
    INVERT       = 1,
    BIT_REVERSE  = 2
};

enum class mov_src_t : uint16_t {
    PINS         = 0,
    X            = 1,
    Y            = 2,
    ZEROS        = 3,
    STATUS       = 5,
    ISR          = 6,
    OSR          = 7
};

inline uint16_t op_MOV(uint8_t    delay_sideset,
                       mov_dest_t dest,
                       mov_op_t   op,
                       mov_src_t  src) {
    return 0xa000 |
           ((delay_sideset & 0x1f)      << 8) |
           (static_cast<uint16_t>(dest) << 5) |
           (static_cast<uint16_t>(op)   << 3) |
           (static_cast<uint16_t>(src));
}

const uint32_t CLR  = 0x40;
const uint32_t WAIT = 0x20;

inline uint16_t op_IRQ(uint8_t  delay_sideset,
                       uint16_t flags,
                       uint8_t  index) {
    return 0xc000 |
           ((delay_sideset & 0x1f) << 8) |
           flags |
           (index & 0x1f);
}

enum class set_dest_t : uint16_t {
    PINS         = 0,
    X            = 1,
    Y            = 2,
    PINDIRS      = 4
};

inline uint16_t op_SET(uint8_t    delay_sideset,
                       set_dest_t dest,
                       uint8_t    data) {
    return 0xe000 |
            ((delay_sideset & 0x1f)      << 8) |
            (static_cast<uint16_t>(dest) << 5) |
            (data & 0x1f);
}

struct SM_regs {
    SM_CLKDIV_t                   SM_CLKDIV;
    SM_EXECCTRL_t                 SM_EXECCTRL;
    SM_SHIFTCTRL_t                SM_SHIFTCTRL;
    SM_ADDR_t                     SM_ADDR;
    SM_INSTR_t                    SM_INSTR;
    SM_PINCTRL_t                  SM_PINCTRL;

    void init() {
        // Initialize SM registers with reset values;
        SM_CLKDIV                 = 0;
        SM_CLKDIV.INT             = 1;
        SM_EXECCTRL               = 0;
        SM_EXECCTRL.WRAP_TOP      = 0x1f;
        SM_SHIFTCTRL              = 0;
        SM_SHIFTCTRL.OUT_SHIFTDIR = 1;
        SM_SHIFTCTRL.IN_SHIFTDIR  = 1;
        SM_PINCTRL                = 0;
        SM_PINCTRL.SET_COUNT      = 5;
    }
};

struct SM {
    PIO0_t  &   pio;
    PIO0_t  &   pio_set;
    PIO0_t  &   pio_clr;
    uint8_t     sm_index;
    uint8_t     load_addr;
    SM_regs &   regs;

    SM(PIO0_t & p, PIO0_t & ps, PIO0_t & pc,
       uint8_t i, uint8_t l, SM_regs & r)
    : pio(p), pio_set(ps), pio_clr(pc),
      sm_index(i), load_addr(l), regs(r) {
        regs.init();
    }

    inline void execute(uint16_t instruction) {
        regs.SM_INSTR = instruction;
    }

    void setRegister(out_dest_t reg, uint32_t val) {
        // Remember current configuration
        bool en = isEnabled();
        disable();
        uint8_t out_base  = regs.SM_PINCTRL.OUT_BASE;
        uint8_t out_count = regs.SM_PINCTRL.OUT_COUNT;
        // Write full 32 bits
        regs.SM_PINCTRL.OUT_BASE  = 0;
        regs.SM_PINCTRL.OUT_COUNT = 32;
        // Empty the TX Fifo
        while(pio.FLEVEL & (0xf << (sm_index << 3))) {
            execute( op_PULL(0, 0) );
        }
        // Write value to TX Fifo first, then write it to destination
        writeTxFifo(val);
        execute( op_PULL(0, 0)      );
        execute( op_OUT (0, reg, 0) );
        // Restore original state
        regs.SM_PINCTRL.OUT_BASE  = out_base;
        regs.SM_PINCTRL.OUT_COUNT = out_count;
        if (en) enable();
    }

    void setClock(uint32_t hz) {
        regs.SM_CLKDIV.INT = 125000000 / hz;
        uint64_t frac = ((125000000 % hz) << 8);
        frac /= hz;
        regs.SM_CLKDIV.FRAC = frac;
    }

    inline bool TxFifoFull() {
        return pio.FSTAT.TXFULL & (1 << sm_index);
    }
    void writeTxFifo(uint32_t val) {
        while(pio.FSTAT.TXFULL & (1 << sm_index)) ;
        pio.TXF[sm_index] = val;
    }

    void setWrap(uint8_t bottom, uint8_t top) {
        regs.SM_EXECCTRL.WRAP_BOTTOM = bottom + load_addr;
        regs.SM_EXECCTRL.WRAP_TOP    = top    + load_addr;
    }

    void enable() {
        pio_set.CTRL.SM_ENABLE = (1 << sm_index);
    }

    void disable() {
        pio_clr.CTRL.SM_ENABLE = (1 << sm_index);
    }

    bool isEnabled() {
        return pio.CTRL.SM_ENABLE & (1 << sm_index);
    }

};


struct pio_program {
    const uint16_t  *instructions;
    uint8_t         length;
    int8_t          origin; // required instruction memory origin or -1
};

class pio_rp2040 {
public:
    virtual ~pio_rp2040();

    static pio_rp2040 pio0;
    static pio_rp2040 pio1;

    SM loadProgram(const pio_program & prgm);

private:
    pio_rp2040(PIO0_t & pio);
    PIO0_t &    _pio;
    PIO0_t &    _pio_xor;
    PIO0_t &    _pio_set;
    PIO0_t &    _pio_clr;
    uint8_t     _next_free_addr;
    SM_regs *   _sm_regbanks;
};

#endif // _PIO_RP2040_H_

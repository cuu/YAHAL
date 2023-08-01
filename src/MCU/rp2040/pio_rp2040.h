/*
 * pio_rp2040.h
 *
 *  Created on: 25.12.2022
 *      Author: andreas
 */

#ifndef _PIO_RP2040_H_
#define _PIO_RP2040_H_

#include "RP2040.h"
using namespace _PIO0_;

#include <cstdint>
#include <functional>
using std::function;

// enums and methods to generate state machine instructions

/////////
// JMP //
/////////
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

//////////
// WAIT //
//////////
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

////////
// IN //
////////
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

/////////
// OUT //
/////////
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

//////////
// PUSH //
//////////
const uint16_t IFFULL = 0x40;
const uint16_t BLOCK  = 0x20;

inline uint16_t op_PUSH(uint8_t  delay_sideset,
                        uint16_t flags) {
    return 0x8000 |
           ((delay_sideset & 0x1f) << 8) |
           flags;
}

//////////
// PULL //
//////////
inline uint16_t op_PULL(uint8_t  delay_sideset,
                        uint16_t flags) {
    return 0x8080 |
           ((delay_sideset & 0x1f) << 8) |
           flags;
}

/////////
// MOV //
/////////
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

/////////
// IRQ //
/////////
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

/////////
// SET //
/////////
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

// Struct to mirror the registers of a single SM.
// Will be used inside the SM struct (see below).
struct SM_regs {
    SM_CLKDIV_t       SM_CLKDIV;
    SM_EXECCTRL_t     SM_EXECCTRL;
    SM_SHIFTCTRL_t    SM_SHIFTCTRL;
    SM_ADDR_t         SM_ADDR;
    SM_INSTR_t        SM_INSTR;
    SM_PINCTRL_t      SM_PINCTRL;
    // Initialize SM registers with reset values;
    void init();
};

// Struct for a single SM.
struct SM {
    PIO0_t  &   pio;
    PIO0_t  &   pio_set;
    PIO0_t  &   pio_clr;
    uint8_t     pio_index;
    uint8_t     sm_index;
    uint8_t     load_addr;
    SM_regs &   regs;

    SM(PIO0_t & p, PIO0_t & ps, PIO0_t & pc, uint8_t pi,
       uint8_t smi, uint8_t l, SM_regs & r)
    : pio(p), pio_set(ps), pio_clr(pc), pio_index(pi),
      sm_index(smi), load_addr(l), regs(r) {
        regs.init();
    }

    // Execute a single PIO instruction
    inline void execute(uint16_t instruction) {
        regs.SM_INSTR = instruction;
    }

    // Set a PIO register. Default is to write a 32-bit word,
    // but offset and size can be specified to only change
    // specific bits. Any register which is handled by the
    // OUT instruction can be used.
    void setRegister(out_dest_t reg, uint32_t val,
                     uint8_t offset = 0, uint8_t size = 32);

    // Set the PIO clock
    void setClock(uint32_t hz);

    // Check if TX FIFO is full.
    inline bool TxFifoFull() {
        return pio.FSTAT.TXFULL & (1 << sm_index);
    }

    // Check if TX FIFO is empty.
    inline bool TxFifoEmpty() {
        return pio.FSTAT.TXEMPTY & (1 << sm_index);
    }

    // Write a 32 bit value to the TX FIFO
    inline void writeTxFifo(uint32_t val) {
        while(TxFifoFull()) ;
        pio.TXF[sm_index] = val;
    }

    // Set the WRAP addresses. Parameters are relative to
    // the load address!
    inline void setWrap(uint8_t bottom, uint8_t top) {
        regs.SM_EXECCTRL.WRAP_BOTTOM = bottom + load_addr;
        regs.SM_EXECCTRL.WRAP_TOP    = top    + load_addr;
    }

    // Enable the SM
    inline void enable() {
        pio_set.CTRL.SM_ENABLE = (1 << sm_index);
    }

    // Disable the SM
    inline void disable() {
        pio_clr.CTRL.SM_ENABLE = (1 << sm_index);
    }

    // Check if SM is enabled
    inline bool isEnabled() {
        return pio.CTRL.SM_ENABLE & (1 << sm_index);
    }

    void attachIrq(function<void()> handler);
    void enableIrq();
    void disableIrq();

    void attachTXNFULLIrq(function<void()> handler);
    void enableTXNFULLIrq();
    void disableTXNFULLIrq();

    void attachRXNEMPTYIrq(function<void()> handler);
    void enableRXNEMPTYIrq();
    void disableRXNEMPTYIrq();
};

// Struct for a PIO programm (used in the generated code
// of the PIO assembler)
struct pio_program {
    const uint16_t  *instructions;
    uint8_t         length;
    int8_t          origin; // required instruction memory origin or -1
};

// PIO control class
class pio_rp2040 {
public:
    virtual ~pio_rp2040();

    // The two static PIO singletons
    static pio_rp2040 pio0;
    static pio_rp2040 pio1;

    SM* loadProgram(const pio_program & prgm);

    static function<void()> _handler_pio0[12];
    static function<void()> _handler_pio1[12];

private:
    pio_rp2040(PIO0_t & pio, uint8_t pio_index);
    PIO0_t &    _pio;
    PIO0_t &    _pio_xor;
    PIO0_t &    _pio_set;
    PIO0_t &    _pio_clr;
    uint8_t     _pio_index;
    uint8_t     _next_free_addr;
    SM_regs *   _sm_regbanks;
    bool        _in_use[4];

};

#endif // _PIO_RP2040_H_

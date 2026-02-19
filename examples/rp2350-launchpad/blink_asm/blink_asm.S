                @ ---------------------------------------------
                @           This file is part of
                @      _  _   __    _   _    __    __
                @     ( \/ ) /__\  ( )_( )  /__\  (  )
                @      \  / /(__)\  ) _ (  /(__)\  )(__
                @      (__)(__)(__)(_) (_)(__)(__)(____)
                @
                @     Yet Another HW Abstraction Library
                @      Copyright (C) Andreas Terstegge
                @      BSD Licensed (see file LICENSE)
                @
                @ ---------------------------------------------
                @
                @ A simple blink example in GNU ARM assembler
                @ using the red LED (GPIO 38) on the RP2350 LP.
                @ The delay is implemented with a simple delay
                @ loop.

                .syntax unified                 @ use unified assembler syntax
                .thumb                          @ generate thumb machine code
                .text                           @ put the following code in the text (code) section
                .type main, function

                .func
gpio_init:      ldr         r1, PAD_CTRL38      @ load r1 with the address of GPIO38 pad control register
                mov         r2, 0
                str         r2, [r1]            @ disable pullup/pulldown resistors and reset ISO

                ldr         r1, GPIO38_CTRL     @ load r1 with the address of the GPIO38_CTRL register
                mov         r2, 5               @ 5 is SIO mode
                str         r2, [r1]            @ Set GPIO38 to SIO mode

                ldr         r1, GPIO_HI_OE_SET  @ load addr of register GPIO_HI_OE_SET
                mov         r2, 1               @ Create a mask for GPIO 38
                lsls        r2, 38-32           @ (1 << (38-32)) in register R2
                                                @ We have to subtract 32 from the shift value
                                                @ because GPIO_HI_* registers handle GPIOs 32-47
                                                @ in their lower 16 bits!

                str         r2, [r1]            @ Enable GPIO 38 for output
                bx          lr                  @ return from subroutine
                .endfunc

                @ This subroutine is a simple down-counting
                @ loop, which produces a small delay. The
                @ start counter value is stored at COUNTER

                .align  4                       @ make sure we are on a word boundary,
                .func
delay:          ldr         r4, COUNTER         @ load r4 with counter value
tmp1:           subs        r4, #1              @ decrement counter
                bne         tmp1                @ jump to Delay1 if not zero
                bx          lr                  @ return from subroutine
                .endfunc

                .global main                    @ make the label 'main' global, so the
                                                @ linker can find this symbol (as the
                                                @ starting point of the program!)
                .func
main:           bl          gpio_init           @ Call subroutine GPIO_Init
                ldr         r1, GPIO_HI_OUT_XOR @ load r1 with address of register GPIO_HI_OUT_XOR
                movs        r2, 1               @ Create a mask for GPIO 38
                lsls        r2, 38-32           @ (1 << (38-32)) in register R2
loop:           str         r2, [r1]            @ Toggle output bit
                bl          delay               @ call delay subroutine
                b           loop                @ jump back to loop:
                .endfunc

                @ .equ defines an alias for a given name.
                @ Start of peripheral memory region
                .equ    PERI_REGION, 0x40000000

                @ .word X stores the 32-bit value X into
                @ flash memory. Here we store some address values,
                @ which we later need for indirect addressing

                .align 4
                @ store the delay counter (approx. 500ms delay at 200 MHz)
COUNTER:        .word   500 * 66500

                @ PADS BANK0 Registers
                .equ    PADS_BANK0_BASE, PERI_REGION + 0x38000
                .equ    PAD_CTRL_PD_ENABLE, 2
                .equ    PAD_CTRL_PU_ENABLE, 3
                .equ    PAD_CTRL_ISO, 8
                #define PAD_CTRL(x) (PADS_BANK0_BASE + (x*4) + 4)
PAD_CTRL38:     .word   PAD_CTRL(38)

                @ IO BANK0 Registers
                .equ    IO_BANK0_BASE,   PERI_REGION + 0x28000
                #define GPIO_STATUS(x)  (IO_BANK0_BASE + (x*8))
                #define GPIO_CTRL(x)    (IO_BANK0_BASE + (x*8) + 4)
GPIO38_STATUS:  .word   GPIO_STATUS(38)
GPIO38_CTRL:    .word   GPIO_CTRL(38)

                @ SIO Registers
                .equ    SIO_BASE,  0xd0000000

                @ These are the adresses of SIO registers for the 'lower'
                @ GPIOs (0-31). Every bit in each register controls a GPIO
                @ with the same numer as the bit position (bit 0..31 -> GPIO0-31)
GPIO_IN:        .word   SIO_BASE + 0x04
GPIO_OUT:       .word   SIO_BASE + 0x10
GPIO_OUT_SET:   .word   SIO_BASE + 0x18
GPIO_OUT_CLR:   .word   SIO_BASE + 0x20
GPIO_OUT_XOR:   .word   SIO_BASE + 0x28
GPIO_OE:        .word   SIO_BASE + 0x30
GPIO_OE_SET:    .word   SIO_BASE + 0x38
GPIO_OE_CLR:    .word   SIO_BASE + 0x40
GPIO_OE_XOR:    .word   SIO_BASE + 0x48

                @ These are the adresses of SIO registers for the 'higher'
                @ GPIOs (32-47). Only the lower 16 bits of every register are
                @ used (RP2350B has only 48 GPIO pins). bit 0 in these registers
                @ controls GPIO32, bit 1 controls GPIO 33, ...
GPIO_HI_IN:     .word   SIO_BASE + 0x08
GPIO_HI_OUT:    .word   SIO_BASE + 0x14
GPIO_HI_OUT_SET:.word   SIO_BASE + 0x1c
GPIO_HI_OUT_CLR:.word   SIO_BASE + 0x24
GPIO_HI_OUT_XOR:.word   SIO_BASE + 0x2c
GPIO_HI_OE:     .word   SIO_BASE + 0x34
GPIO_HI_OE_SET: .word   SIO_BASE + 0x3c
GPIO_HI_OE_CLR: .word   SIO_BASE + 0x44
GPIO_HI_OE_XOR: .word   SIO_BASE + 0x4c

                @ end of assembeler file
                .end

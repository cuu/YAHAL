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
                @ using the red LED on GPIO 13 on the RP2040.
                @ The delay is implemented with a simple delay
                @ loop.

                .syntax unified                 @ use unified assembler syntax
                .thumb                          @ generate thumb machine code
                .text                           @ put the following code in the text (code) section

                .func
gpio_init:      ldr         r1, GPIO13_CTRL     @ load r1 with the word located atGPIO13_CTRL
                movs        r2, 5               @ 5 is SIO mode
                str         r2, [r1]            @ store back P1SEL1

                ldr         r1, GPIO_OE_SET
                movs        r2, 1
                lsls        r2, 13
                str         r2, [r1]
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
                ldr         r1, GPIO_OUT_XOR    @ load r1 with address of P1OUT
                movs        r2, 1
                lsls        r2, 13
loop:           str         r2, [r1]            @ store P1OUT
                bl          delay               @ call delay subroutine
                b           loop                @ jump back to loop:
                .endfunc

                @ .equ defines an alias for a given name.
                @ Start of peripheral memory region
                .equ    PERI_REGION, 0x40000000

                @ .word X stores the value 32-bit value X into
                @ flash memory. Here we store some address values,
                @ which we later need for indirect addressing

                .align 4
                @ store the delay counter
COUNTER:        .word   41666 * 500      @ approx. 500ms delay counter value at 125 MHz

                @ PADS BANK0 Registers
                .equ    PADS_BANK0_BASE, PERI_REGION + 0x1c000
                .equ    PAD_CTRL_PD_ENABLE, 2
                .equ    PAD_CTRL_PU_ENABLE, 3
                #define PAD_CTRL(x) (PADS_BANK0_BASE + (x << 2) + 4)
PAD_CTRL13:     .word   PAD_CTRL(13)

                @ IO BANK0 Registers
                .equ    IO_BANK0_BASE,   PERI_REGION + 0x14000
                #define GPIO_STATUS(x)  (IO_BANK0_BASE + (x << 3))
                #define GPIO_CTRL(x)    (IO_BANK0_BASE + (x << 3) + 4)
GPIO13_STATUS:  .word   GPIO_STATUS(13)
GPIO13_CTRL:    .word   GPIO_CTRL(13)

                @ SIO Registers
                .equ    SIO_BASE,  0xd0000000
GPIO_IN:        .word   SIO_BASE + 0x04
GPIO_OUT:       .word   SIO_BASE + 0x10
GPIO_OUT_SET:   .word   SIO_BASE + 0x14
GPIO_OUT_CLR:   .word   SIO_BASE + 0x18
GPIO_OUT_XOR:   .word   SIO_BASE + 0x1c
GPIO_OE:        .word   SIO_BASE + 0x20
GPIO_OE_SET:    .word   SIO_BASE + 0x24
GPIO_OE_CLR:    .word   SIO_BASE + 0x28
GPIO_OE_XOR:    .word   SIO_BASE + 0x2c

                @ end of assembeler file
                .end

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
@ using the red LED on Port 1 pin 0.
@ The delay is implemented with a simple delay
@ loop (if the CPU clock is set to 3MHz, then
@ 1000 iterations of the delay function last
@ approx 1 ms, see code below).

            .syntax unified         @ use unified assembler syntax
            .thumb                  @ generate thumb machine code
            .text                   @ put the following code in the text (code) section
                                    
            @ .equ defines an alias for a given name.
            @ It is comparable to #define in C/C++
            @
            @ Start of peripheral memory region
            .equ    PERI_REGION, 0x40000000
            @ Start of Port Module
            .equ    PORT_MODULE, PERI_REGION + 0x4C00

            @ Some BIT definitions so the code gets more readable
            .equ    BIT0, 0x01
            .equ    BIT1, 0x02
            .equ    BIT2, 0x04
            .equ    BIT3, 0x08
            .equ    BIT4, 0x10
            .equ    BIT5, 0x20
            .equ    BIT6, 0x40
            .equ    BIT7, 0x80

            @ .word X stores the value 32-bit value X into
            @ flash memory. Here we store some address values,
            @ which we later need for indirect addressing
P1IN:       .word   PORT_MODULE     @ Port 1 Input
P1OUT:      .word   PORT_MODULE+2   @ Port 1 Output
P1DIR:      .word   PORT_MODULE+4   @ Port 1 Direction
P1REN:      .word   PORT_MODULE+6   @ Port 1 Resistor Enable
P1SEL0:     .word   PORT_MODULE+10  @ Port 1 Select 0
P1SEL1:     .word   PORT_MODULE+12  @ Port 1 Select 1

             @ store the delay counter
COUNTER:    .word   1000 * 500      @ 500ms delay counter value at 3MHz


            @ This subroutine sets P1.0 as gpio (SEL0 and SEL1
            @ bits are cleared). Since the default value for
            @ SEL0 and SEL1 is zero, this step could have been
            @ skipped. After that, bit 0 in P1DIR is set to 1,
            @ so that P1.0 is working as a gpio output.
            
GPIO_Init:  ldr     r1, P1SEL0      @ load r1 with the word at
                                    @ address P1SEL0
            ldrb    r0, [r1]        @ load r0 with the byte pointed
                                    @ to by r1 (indirect addressing)
            bic     r0, BIT0        @ clear bit 0
            strb    r0, [r1]        @ store byte in r0 to the address
                                    @ pointed to by r1

            ldrb    r0, [r1, #2]    @ load r0 with the byte pointed to
                                    @ by r1+2 (indirect addressing with offset)
                                    @ this will load P1SEL1 into r0
            bic     r0, BIT0        @ clear bit 0
            strb    r0, [r1, #2]    @ store back P1SEL1

            ldr     r1, P1DIR       @ load r1 with address of P1DIR    
            ldrb    r0, [r1]
            orr     r0, BIT0        @ set bit 0 -> P1.0 is in output direction
            strb    r0, [r1]
            bx      lr              @ return from subroutine

            @ This subroutine is a simple down-counting
            @ loop, which produces a small delay. The
            @ start counter value is stored at COUNTER

            .align  4               @ make sure we are on a word boundary,
                                    @ so that no extra CPU cycles are added!
                                    @ 1000 iterations last approx. 1 ms
                                    @ when the CPU clock is 3 MHz

Delay:      ldr     r4, COUNTER     @ load r4 with counter value
Delay1:     subs    r4, #1          @ decrement counter
            bne     Delay1          @ jump to Delay1 if not zero
            bx      lr              @ return from subroutine

            .global main            @ make the label 'main' global, so the
                                    @ linker can find this symbol (as the
                                    @ starting point of the program!)

main:       nop                     @ NOP = No OPeration. This is necessary if
                                    @ we want to step into GPIO_Init during
                                    @ debugging (hack ;)...
            bl      GPIO_Init       @ Call subroutine GPIO_Init
            ldr     r1, P1OUT       @ load r1 with address of P1OUT

loop:       ldrb    r0, [r1]        @ load P1OUT
            eor     r0, BIT0        @ toggle bit 0 (with XOR trick...)
            strb    r0, [r1]        @ store P1OUT
            bl      Delay           @ call delay subroutine
            b       loop            @ jump back to loop:

            .end                    @ end of assembeler file


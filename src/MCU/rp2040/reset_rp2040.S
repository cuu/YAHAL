// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
// Low-level reset code for the RP2040 Launchpad
//
// This code will
//  - Check wether the image is a COPY_TO_xxx image, and relocates
//    the image if necessary
//  - Sets the VTOR register
//  - Jumps to the C++-part of the reset routine (Reset_Handler)
//
// The following boot scenarios for the RP2040 Launchpad are supported:
//
// 1.) Normal flash image
//     OpenOcd upload:  Works, target is reset and enters reset_handler
//                      via bootrom and boot2.
//     OpenOcd debug:   Works, targer is reset and enters reset_handler
//                      via bootrom and boot2.
//     UF2 upload:      Works
//
// 2.) Image linked with COPY_TO_RAM
//     OpenOcd upload:  Works, target is reset and enters reset_handler
//                      via bootrom and boot2.
//     OpenOcd debug:   Works, targer is reset and enters reset_handler
//                      via bootrom and boot2.
//     UF2 upload:      Works
//
// 3.) Images linked with LOAD_INTO_RAM
//     OpenOcd upload:  Works, target is not reset and resumes at 0x20000001.
//     OpenOcd debug:   Needs special debugger setup, reset is not allowed.
//     UF2 upload:      Works

#define VTOR_REG        0xe000ed08

            .syntax unified
            .thumb
            .section .reset,"ax"
            .global reset_handler
            .global _elf_entry_point

            // This is a fake vector table to start the
            // reset_handler, in case this code is put right
            // at the beginning of the flash (0x10000000).
            .word   __StackTop
            .word   reset_handler

            .thumb_func
reset_handler:

            // Check if we have to relocate the image
            ldr     r0, =__image_load__
            ldr     r1, =__image_start__
            cmp     r0, r1
            beq     no_copy

            // Copy the complete image (.text, .rodata, .data)
            // to the runtime memory area in RAM
copy_loop:  ldr     r2, =__image_end__
            ldmia   r0!, {r3}
            stmia   r1!, {r3}
            cmp     r1, r2
            blo     copy_loop

            // Set the ISR vector offset register (VTOR)
no_copy:    ldr     r0, =__vector_start__
            ldr     r1, =VTOR_REG
            str     r0, [r1]

            // Finally jump to the C++-based part of
            // the reset handler, which will initialize
            // the system and jump to main(). Use a long
            // jump here in case the jump target is in RAM
            ldr     r0, =Reset_Handler
            blx     r0

            // We should never get here, but just in case
            // run into an endless loop
endless:    b       endless


            // If the image is enteres via the _elf_entry_point,
            // take a loop through the bootrom, to make sure the
            // flash and other related things are initialized
            .thumb_func
_elf_entry_point:
            // Set the ISR vector offset register (VTOR)
            movs    r0, #0
            ldr     r1, =VTOR_REG
            str     r0, [r1]
            // r1=initial SP, r2=reset handler of bootrom
            ldmia   r0!, {r1, r2}
            msr     msp, r1
            blx     r2
            // We should never get here, but just in case
            // run into an endless loop
            b       endless

            .end

/**************************************/
/* rp2040-launchpad GCC linker script */
/**************************************/

MEMORY
{
    FLASH(rx)      : ORIGIN = 0x10000000, LENGTH = 4096k
    RAM(rwx)       : ORIGIN = 0x20000000, LENGTH = 512k
    SCRATCH_X(rwx) : ORIGIN = 0x20080000, LENGTH = 4k
    SCRATCH_Y(rwx) : ORIGIN = 0x20081000, LENGTH = 4k
}

/********************/
/* ELF entry point. */
/********************/
ENTRY(_elf_entry_point)

SECTIONS
{
    /***************************/
    /* Second stage bootloader */
    /***************************/
    .boot2 : {
        __boot2_start__ = .;
        KEEP (*(.boot2))
        __boot2_end__ = .;
    } > FLASH

    ASSERT(__boot2_end__ - __boot2_start__ == 256,
        "ERROR: Pico second stage bootloader must be 256 bytes in size")

    /********/
    /* Code */
    /********/
    .text : {
        KEEP (*(.isr_vector))
        *(.text.*)

        *(SORT(.ctors.*))
        *(.ctors)
        *(SORT(.dtors.*))
        *(.dtors)

        KEEP (*(.init))
        KEEP (*(.fini))

        __preinit_array_start = .;
        KEEP (*(.preinit_array*))
        __preinit_array_end = .;

        __init_array_start = .;
        KEEP (*(.init_array*))
        __init_array_end = .;

        __fini_array_start = .;
        KEEP (*(.fini_array*))
        __fini_array_end = .;

    } > FLASH

    /*************************/
    /* Exception information */
    /*************************/
    .ARM.extab : {
        KEEP (*(.ARM.extab* .gnu.linkonce.armextab.*))
    } > FLASH

    .ARM.exidx : {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > FLASH

    /******************/
    /* Read-only data */
    /******************/
    .rodata : {
        *(.rodata)
        *(.rodata.*)
    } > FLASH
    
    /***********************************/
    /* .copy.table used by cmsis_gcc.h */
    /***********************************/
    .copy.table : {
        . = ALIGN(8);
        __copy_table_start__ = .;
        LONG (__data_load__)
        LONG (__data_start__)
        LONG (__data_end__ - __data_start__)
        __copy_table_end__ = .;
    } > FLASH

    /***********************************/
    /* .zero.table used by cmsis_gcc.h */
    /***********************************/
    .zero.table : {
        . = ALIGN(8);
        __zero_table_start__ = .;
        LONG (__bss_start__)
        LONG (__bss_end__ - __bss_start__)
        __zero_table_end__ = .;
    } > FLASH

    __etext = .;    /* end of .text-like segments */

    /****************************************/
    /* data which needs to be copied to RAM */
    /****************************************/
    .data : {
        . = ALIGN (4);
        __data_load__  = LOADADDR(.data);
        __data_start__ = .;
        *(.vtable)
        *(.move_to_ram*)
        *(.data*)
        . = ALIGN (4);
        __data_end__ = .;
    } > RAM AT> FLASH

    /***************************************/
    /* uninizialized data (will be zeroed) */
    /***************************************/
    .bss : {
        . = ALIGN (4);
        __bss_start__ = .;
        *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.bss*)))
        *(COMMON)
        . = ALIGN (4);
        __bss_end__ = .;
    } > RAM

    __end__ = .;    /* end of written RAM */
    end = __end__;

    /********/
    /* heap */
    /********/
    .heap (NOLOAD): {
        __heap_start__ = .;
        __HeapBase = .;
        *(.heap*)
        __heap_end__ = .;
        __HeapLimit = ORIGIN(RAM) + LENGTH(RAM) - 1;
    } > RAM

    /*********/
    /* stack */
    /*********/
    .stack1 (NOLOAD): {
        *(.stack1*)
    } > SCRATCH_X

    .stack (NOLOAD): {
        *(.stack*)
    } > SCRATCH_Y

    /* Lower stack limit */
    __StackLimit = ORIGIN(RAM) + LENGTH(RAM);
    /* Higher stack limits */
    __StackXTop = ORIGIN(SCRATCH_X) + LENGTH(SCRATCH_X);
    __StackYTop = ORIGIN(SCRATCH_Y) + LENGTH(SCRATCH_Y);
    __StackTop  = __StackYTop;
    PROVIDE(__stack = __StackTop);
}

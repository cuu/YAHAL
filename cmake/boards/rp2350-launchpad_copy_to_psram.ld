/**************************************/
/* rp2350 launchpad GCC linker script */
/**************************************/

MEMORY
{
    FLASH(rx)      : ORIGIN = 0x10000000, LENGTH = 8192k
    PSRAM(rwx)     : ORIGIN = 0x11000000, LENGTH = 8192k
    RAM(rwx)       : ORIGIN = 0x20000000, LENGTH = 512k
    SCRATCH_X(rwx) : ORIGIN = 0x20080000, LENGTH = 4k
    SCRATCH_Y(rwx) : ORIGIN = 0x20081000, LENGTH = 4k
}

ENTRY(_elf_entry_point)

SECTIONS
{
    /* In a COPY_TO_PSRAM scenario, the reset handler */
    /* will handle the copying to RAM. It will copy   */
    /* from __image_load__ to the memory area         */
    /* from __image_start__ to __image_end__          */

    .flashtext : {
        KEEP (*(.reset))
    } > FLASH

    /********/
    /* Code */
    /********/
    .text : {
        . = ALIGN(4);
        __image_load__  = LOADADDR(.text);
        __image_start__ = .;

        /* We always begin with the ISR vector */
        __vector_start__ = .;
        KEEP (*(.isr_vector))

        . = ALIGN(4);
        KEEP (*(.boot_blocks))
        . = ALIGN(4);

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

    } > PSRAM AT> FLASH

    /*************************/
    /* Exception information */
    /*************************/
    .ARM.extab : {
        KEEP (*(.ARM.extab* .gnu.linkonce.armextab.*))
    } > PSRAM AT> FLASH

    .ARM.exidx : {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > PSRAM AT> FLASH

    /******************/
    /* Read-only data */
    /******************/
    .rodata : {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4);
    } > PSRAM AT> FLASH

    /********************************************/
    /* .copy.table used by cmsis_gcc.h          */
    /* The CMSIS code handling the copy tables  */
    /* copies uint32_t values, so the start/end */
    /* values have to be aligned and the size   */
    /* has to be divided by 4.                  */
    /********************************************/
    .copy.table : {
        . = ALIGN(4);
        __copy_table_start__ = .;
        __copy_table_end__ = .;
    } > PSRAM AT> FLASH

    /***********************************/
    /* .zero.table used by cmsis_gcc.h */
    /***********************************/
    .zero.table : {
        . = ALIGN(4);
        __zero_table_start__ = .;
        LONG  (__bss_start__)
        LONG ((__bss_end__ - __bss_start__)/4)
        __zero_table_end__ = .;
    } > PSRAM AT> FLASH

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
    } > PSRAM AT> FLASH

    __image_end__ = .;

    /***************************************/
    /* uninizialized data (will be zeroed) */
    /***************************************/
    .bss (NOLOAD): {
        . = ALIGN (4);
        __bss_start__ = .;
        *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.bss*)))
        *(COMMON)
        . = ALIGN (4);
        __bss_end__ = .;
    } > PSRAM

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
    .stack.x (NOLOAD): {
        *(.stack.x*)
    } > SCRATCH_X

    .stack.y (NOLOAD): {
        *(.stack.y*)
    } > SCRATCH_Y

    /* Lower stack limit */
    __StackLimit = ORIGIN(RAM) + LENGTH(RAM);
    /* Higher stack limits */
    __StackXTop = ORIGIN(SCRATCH_X) + LENGTH(SCRATCH_X);
    __StackYTop = ORIGIN(SCRATCH_Y) + LENGTH(SCRATCH_Y);
    __StackTop  = __StackLimit;
    PROVIDE(__stack = __StackTop);
}

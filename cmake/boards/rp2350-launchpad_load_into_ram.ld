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

/********************/
/* ELF entry point. */
/********************/
ENTRY(_elf_entry_point)

SECTIONS
{
    /********/
    /* Code */
    /********/
    .text : {
        KEEP (*(.reset))
        . = ALIGN(4);
        KEEP (*(.boot_blocks))
        . = ALIGN(256);
        __vector_start__ = .;
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

    } > RAM

    /*************************/
    /* Exception information */
    /*************************/
    .ARM.extab : {
        KEEP (*(.ARM.extab* .gnu.linkonce.armextab.*))
    } > RAM

    .ARM.exidx : {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > RAM

    /******************/
    /* Read-only data */
    /******************/
    .rodata : {
        *(.rodata)
        *(.rodata.*)
    } > RAM
    
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
        LONG  (__ps_data_load__)
        LONG  (__ps_data_start__)
        LONG ((__ps_data_end__ - __ps_data_start__)/4)
        __copy_table_end__ = .;
    } > RAM

    /***********************************/
    /* .zero.table used by cmsis_gcc.h */
    /***********************************/
    .zero.table : {
        . = ALIGN(4);
        __zero_table_start__ = .;
        LONG  (__bss_start__)
        LONG ((__bss_end__ - __bss_start__)/4)
        LONG  (__ps_bss_start__)
        LONG ((__ps_bss_end__ - __ps_bss_start__)/4)
        __zero_table_end__ = .;
    } > RAM

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
    } > RAM

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
    } > RAM

    __end__ = .;    /* end of written RAM */
    end = __end__;

    /******************************************/
    /* data which needs to be copied to PSRAM */
    /******************************************/
    .ps_data : {
        . = ALIGN (4);
        __ps_data_load__  = LOADADDR(.ps_data);
        __ps_data_start__ = .;
        *(.ps_data)
        . = ALIGN (4);
        __ps_data_end__ = .;
    } > PSRAM AT> FLASH

    /************************************************/
    /* uninizialized data in PSRAM (will be zeroed) */
    /************************************************/
    .ps_bss (NOLOAD): {
        . = ALIGN (4);
        __ps_bss_start__ = .;
        *(.ps_bss)
        . = ALIGN (4);
        __ps_bss_end__ = .;
    } > PSRAM

    /****************************************************/
    /* uninizialized data in PSRAM (will not be zeroed) */
    /****************************************************/
    .ps_noload (NOLOAD): {
        . = ALIGN (4);
        *(.ps_noload)
    } > PSRAM

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

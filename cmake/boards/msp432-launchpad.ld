/*********************************/
/* MSP432P401R GCC linker script */
/*********************************/

MEMORY
{
    FLASH(rx) : ORIGIN = 0x00000000, LENGTH = 0x00040000
    RAM  (rw) : ORIGIN = 0x20000000, LENGTH = 0x00010000
}

/********************/
/* ELF entry point. */
/********************/
ENTRY(Reset_Handler)

SECTIONS {

    /********/
    /* Code */
    /********/
    .text : {
        KEEP (*(.intvecs))
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
    .stack (NOLOAD) : ALIGN(0x8) {
        _stack = .;
        *(.stack)
    } > RAM

    __StackTop = ORIGIN(RAM) + LENGTH(RAM);
    PROVIDE(__stack = __StackTop);
}

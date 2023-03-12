MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 1024K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    .data : AT(ADDR(.text) + SIZEOF(.text))
    {
        _data = .;
        _ldata = LOADADDR (.data);
        *(vtable)
        *(.data*)
        _edata = .;
    } > SRAM

    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM

    /* Heap and stack section definitions */
    _heap = ORIGIN(SRAM) + LENGTH(SRAM);
    _stack = ORIGIN(SRAM);
    .heap (COPY):
    {
        . = ALIGN(8);
        __end__ = .;
    } > SRAM
    __HeapBase = ALIGN(_heap - 0x100);
    __HeapLimit = .;
    __StackTop = ORIGIN(SRAM) + LENGTH(SRAM);
}

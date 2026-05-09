ENTRY(Reset_Handler)

/* Stack top */
_estack = ORIGIN(SRAM) + LENGTH(SRAM);

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K
  SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
  /* Code + Read-only data */
  .text :
  {
    *(.isr_vector)
    *(.text*)
    *(.rodata*)
    *(.init)
    *(.fini)

    . = ALIGN(4);
    _etext = .;
  } > FLASH

  /* Load address of data (VERY IMPORTANT) */
  _la_data = LOADADDR(.data);

  /* Initialized data (FLASH → SRAM) */
  .data :
  {
    _sdata = .;
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } > SRAM AT > FLASH

  /* Uninitialized data */
  .bss :
  {
    _sbss = .;
    __bss_start__ = _sbss;

    *(.bss*)
    *(COMMON)

    _ebss = .;
    __bss_end__ = _ebss;

    . = ALIGN(4);
  } > SRAM

  /* End of RAM */
  _end = .;
  end = .;
  __end__ = .;
}
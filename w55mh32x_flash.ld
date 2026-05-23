/*
*****************************************************************************
**
**  File        : w55mh32x_flash.ld
**
**  Abstract    : Linker script for WIZnet W55MH32X (W55MH32L and W55MH32Q)
**                216MHz Cortex-M3, 1024K Flash, 96K RAM.
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : WIZnet W55MH32L (LQFP100) / W55MH32Q (QFN68)
**                - Both share identical memory map.
**                - Cortex-M3 core
**                - Flash: 1024 KB @ 0x08000000 (4KB page size)
**                - SRAM : 96 KB @ 0x20000000
**
**  Toolchain   : GNU Arm Embedded (arm-none-eabi-gcc)
**
**  Reference   : W55MH32 Datasheet V1.0.0 §1.1 (memory configuration)
**                W55MH32 User Manual V1.0.0 §4.3 (JLink XML — confirms
**                  WorkRAMAddr=0x20000000, Size=0x00018000,
**                  Flash Base=0x08000000, MaxSize=0x00100000)
**                startup_w55mh32_gcc.s (required symbols: _sidata, _sdata,
**                  _edata, _sbss, _ebss, _estack)
**
**  Distribution: This file is provided AS-IS, without warranty.
**                Based on the standard ARM CMSIS / STM32-style linker script
**                template, customized for W55MH32 memory map.
**
*****************************************************************************
*/

/* Entry Point */
ENTRY(Reset_Handler)

/* ---------------------------------------------------------------------------
 * Stack and Heap sizes
 * Adjust these values according to your application needs.
 * The KEIL default for W55MH32 reference code is:
 *   Stack_Size = 0x1000  (4 KB)
 *   Heap_Size  = 0x10000 (64 KB) -- but this is quite large; reduce if needed
 * --------------------------------------------------------------------------- */
_Min_Heap_Size  = 0x2000;   /*  8 KB heap   - adjust to taste */
_Min_Stack_Size = 0x1000;   /*  4 KB stack  - matches KEIL default */

/* ---------------------------------------------------------------------------
 * Memory regions
 *
 *   FLASH : Internal flash memory, code execution region.
 *   RAM   : Internal SRAM, data + stack + heap.
 *
 * If you want to reserve a section of flash for a bootloader, change
 * FLASH ORIGIN/LENGTH accordingly (e.g. for an app that lives at
 * 0x08008000, use ORIGIN = 0x08008000, LENGTH = 1024K - 32K).
 * --------------------------------------------------------------------------- */
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 1024K
  RAM   (xrw)     : ORIGIN = 0x20000000, LENGTH = 96K
}

/* Highest address of the user mode stack (top of RAM) */
_estack = ORIGIN(RAM) + LENGTH(RAM);    /* = 0x20018000 */

/* ---------------------------------------------------------------------------
 * Output sections
 * --------------------------------------------------------------------------- */
SECTIONS
{
  /* ------------------------------------------------------------------------
   * .isr_vector  : ARM Cortex-M vector table (must be at 0x08000000)
   * ------------------------------------------------------------------------ */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))   /* startup file's vector table */
    . = ALIGN(4);
  } >FLASH

  /* ------------------------------------------------------------------------
   * .text  : program code and read-only data
   * ------------------------------------------------------------------------ */
  .text :
  {
    . = ALIGN(4);
    *(.text)               /* .text sections (code) */
    *(.text*)              /* .text* sections (code) */
    *(.glue_7)             /* glue arm to thumb code */
    *(.glue_7t)            /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;            /* define a global symbol at end of code */
  } >FLASH

  /* ------------------------------------------------------------------------
   * .rodata  : read-only data (constants, strings)
   * ------------------------------------------------------------------------ */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  /* ARM exception/unwinding tables (used by some libraries even in C) */
  .ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  /* Constructors and destructors (C++ / __attribute__((constructor))) */
  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* ------------------------------------------------------------------------
   * .data  : initialized data
   *          Stored in FLASH (LMA), copied to RAM (VMA) by Reset_Handler.
   *          Reset_Handler uses _sidata, _sdata, _edata to do the copy.
   * ------------------------------------------------------------------------ */
  _sidata = LOADADDR(.data);

  .data :
  {
    . = ALIGN(4);
    _sdata = .;            /* create a global symbol at data start */
    *(.data)
    *(.data*)

    . = ALIGN(4);
    _edata = .;            /* define a global symbol at data end */
  } >RAM AT> FLASH

  /* ------------------------------------------------------------------------
   * .bss  : uninitialized data
   *         Zeroed by Reset_Handler using _sbss and _ebss.
   * ------------------------------------------------------------------------ */
  . = ALIGN(4);
  .bss :
  {
    _sbss = .;             /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;             /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM

  /* ------------------------------------------------------------------------
   * ._user_heap_stack  : reserve space for heap and stack, and verify
   *                      that there is enough RAM left.
   *                      The actual stack lives at the TOP of RAM (_estack).
   * ------------------------------------------------------------------------ */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}

/**
 * @file    w55mh32_it.c
 * @brief   Default Cortex-M3 system exception handlers.
 *          Fault handlers spin to keep the failing state visible to the debugger.
 */
#include "w55mh32_it.h"
#include "main.h"

void NMI_Handler(void)         { }
void HardFault_Handler(void)   { while (1) { } }
void MemManage_Handler(void)   { while (1) { } }
void BusFault_Handler(void)    { while (1) { } }
void UsageFault_Handler(void)  { while (1) { } }
void SVC_Handler(void)         { }
void DebugMon_Handler(void)    { }
void PendSV_Handler(void)      { }

void SysTick_Handler(void)
{
    /* Increment a tick base here if one is added. */
}

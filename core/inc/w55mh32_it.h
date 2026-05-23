/**
 * @file    w55mh32_it.h
 * @brief   Cortex-M3 system exception and peripheral IRQ handler prototypes.
 *          Names must match the vector table in startup_w55mh32.s.
 */
#ifndef __W55MH32_IT_H
#define __W55MH32_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Cortex-M3 system exception handlers */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

/* Peripheral IRQ handler prototypes are added here when peripherals are enabled. */

#ifdef __cplusplus
}
#endif

#endif /* __W55MH32_IT_H */

/**
 * @file    w55mh32_it.c
 * @brief   Default Cortex-M3 system exception handlers.
 *          Fault handlers spin to keep the failing state visible to the debugger.
 */
#include "w55mh32_it.h"
#include "main.h"

/**
 * @brief Non-Maskable Interrupt handler. Empty default — NMI is rarely
 *        wired on this MCU; override if a clock-security or watchdog
 *        source needs servicing.
 */
void NMI_Handler(void)
{

}

/**
 * @brief Hard fault handler. Spins forever so the failing register
 *        state stays visible under the debugger; fault analysis is
 *        expected to happen via the Cortex-Debug Peripheral View.
 */
void HardFault_Handler(void)
{
    while (1) { }
}

/**
 * @brief Memory management fault handler. Spins forever; same debug
 *        rationale as HardFault_Handler.
 */
void MemManage_Handler(void)
{
    while (1) { }
}

/**
 * @brief Bus fault handler (invalid bus access). Spins forever; same
 *        debug rationale as HardFault_Handler.
 */
void BusFault_Handler(void)
{
    while (1) { }
}

/**
 * @brief Usage fault handler (undefined instruction, illegal state,
 *        division by zero, ...). Spins forever for debugger inspection.
 */
void UsageFault_Handler(void)
{
    while (1) { }
}

/**
 * @brief Supervisor call handler (raised by the SVC instruction).
 *        Empty default; populate when introducing an RTOS or
 *        privileged-mode service layer.
 */
void SVC_Handler(void)
{

}

/**
 * @brief Debug monitor handler (DWT/ITM debug events). Empty default;
 *        only relevant when running with a debug monitor instead of
 *        halting-mode debug.
 */
void DebugMon_Handler(void)
{

}

/**
 * @brief Pendable service handler (typically driven by an RTOS for
 *        context switch). Empty default; the RTOS port will override
 *        this with its scheduler tail-chain.
 */
void PendSV_Handler(void)
{

}

/**
 * @brief SysTick timer handler. Fires at the rate programmed in
 *        SysTick_Config(); a tick counter or RTOS tick should be
 *        incremented here when one is added.
 */
void SysTick_Handler(void)
{
    /* Increment a tick base here if one is added. */
}

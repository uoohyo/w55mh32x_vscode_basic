/**
 ******************************************************************************
 * @file           : w55mh32_it.c
 * @brief          : Default Cortex-M3 system exception handlers.
 *                   Fault handlers spin to keep the failing state visible to the debugger.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 uoohyo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "w55mh32_it.h"
#include "main.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/* Function -----------------------------------------------------------------*/
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

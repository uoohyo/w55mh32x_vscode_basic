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

/**
  * @brief This function handles WWDG interrupt.
  * @param  None
  * @retval None
  */
void WWDG_IRQHandler(void)
{

}

/**
  * @brief This function handles PVD through EXTI line detection interrupt.
  * @param  None
  * @retval None
  */
void PVD_IRQHandler(void)
{

}

/**
  * @brief This function handles Tamper interrupt.
  * @param  None
  * @retval None
  */
void TAMPER_IRQHandler(void)
{

}

/**
  * @brief This function handles RTC global interrupt.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{

}

/**
  * @brief This function handles FLASH global interrupt.
  * @param  None
  * @retval None
  */
void FLASH_IRQHandler(void)
{

}

/**
  * @brief This function handles RCC global interrupt.
  * @param  None
  * @retval None
  */
void RCC_IRQHandler(void)
{

}

/**
  * @brief This function handles EXTI Line0 interrupt.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{

}

/**
  * @brief This function handles EXTI Line1 interrupt.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{

}

/**
  * @brief This function handles EXTI Line2 interrupt.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{

}

/**
  * @brief This function handles EXTI Line3 interrupt.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{

}

/**
  * @brief This function handles EXTI Line4 interrupt.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{

}

/**
  * @brief This function handles DMA1 Channel1 global interrupt.
  * @param  None
  * @retval None
  */
void DMA1_Channel1_IRQHandler(void)
{

}

/**
  * @brief This function handles DMA1 Channel2 global interrupt.
  * @param  None
  * @retval None
  */
void DMA1_Channel2_IRQHandler(void)
{

}

/**
  * @brief This function handles DMA1 Channel3 global interrupt.
  * @param  None
  * @retval None
  */
void DMA1_Channel3_IRQHandler(void)
{

}

/**
  * @brief This function handles DMA1 Channel4 global interrupt.
  * @param  None
  * @retval None
  */
void DMA1_Channel4_IRQHandler(void)
{

}

/**
  * @brief This function handles DMA1 Channel5 global interrupt.
  * @param  None
  * @retval None
  */
void DMA1_Channel5_IRQHandler(void)
{

}

/**
  * @brief This function handles DMA1 Channel6 global interrupt.
  * @param  None
  * @retval None
  */
void DMA1_Channel6_IRQHandler(void)
{

}

/**
  * @brief This function handles DMA1 Channel7 global interrupt.
  * @param  None
  * @retval None
  */
void DMA1_Channel7_IRQHandler(void)
{

}

/**
  * @brief This function handles ADC1 and ADC2 global interrupts.
  * @param  None
  * @retval None
  */
void ADC1_2_IRQHandler(void)
{

}

/**
  * @brief This function handles USB High Priority or CAN1 TX interrupts.
  * @param  None
  * @retval None
  */
void USB_HP_CAN1_TX_IRQHandler(void)
{

}

/**
  * @brief This function handles USB Low Priority or CAN1 RX0 interrupts.
  * @param  None
  * @retval None
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{

}

/**
  * @brief This function handles CAN1 RX1 interrupt.
  * @param  None
  * @retval None
  */
void CAN1_RX1_IRQHandler(void)
{

}

/**
  * @brief This function handles CAN1 SCE interrupt.
  * @param  None
  * @retval None
  */
void CAN1_SCE_IRQHandler(void)
{

}

/**
  * @brief This function handles EXTI Line[9:5] interrupts.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM1 Break or TIM9 global interrupts.
  * @param  None
  * @retval None
  */
void TIM1_BRK_TIM9_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM1 Update or TIM10 global interrupts.
  * @param  None
  * @retval None
  */
void TIM1_UP_TIM10_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM1 Trigger and Commutation or TIM11 global interrupts.
  * @param  None
  * @retval None
  */
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM1 Capture Compare interrupt.
  * @param  None
  * @retval None
  */
void TIM1_CC_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM2 global interrupt.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM3 global interrupt.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM4 global interrupt.
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler(void)
{

}

/**
  * @brief This function handles I2C1 Event interrupt.
  * @param  None
  * @retval None
  */
void I2C1_EV_IRQHandler(void)
{

}

/**
  * @brief This function handles I2C1 Error interrupt.
  * @param  None
  * @retval None
  */
void I2C1_ER_IRQHandler(void)
{

}

/**
  * @brief This function handles I2C2 Event interrupt.
  * @param  None
  * @retval None
  */
void I2C2_EV_IRQHandler(void)
{

}

/**
  * @brief This function handles I2C2 Error interrupt.
  * @param  None
  * @retval None
  */
void I2C2_ER_IRQHandler(void)
{

}

/**
  * @brief This function handles SPI1 global interrupt.
  * @param  None
  * @retval None
  */
void SPI1_IRQHandler(void)
{

}

/**
  * @brief This function handles SPI2 global interrupt.
  * @param  None
  * @retval None
  */
void SPI2_IRQHandler(void)
{

}

/**
  * @brief This function handles USART1 global interrupt.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{

}

/**
  * @brief This function handles USART2 global interrupt.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{

}

/**
  * @brief This function handles USART3 global interrupt.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{

}

/**
  * @brief This function handles EXTI Line[15:10] interrupts.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{

}

/**
  * @brief This function handles RTC Alarm through EXTI line interrupt.
  * @param  None
  * @retval None
  */
void RTCAlarm_IRQHandler(void)
{

}

/**
  * @brief This function handles USB Wakeup from suspend through EXTI line interrupt.
  * @param  None
  * @retval None
  */
void USBWakeUp_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM8 Break or TIM12 global interrupts.
  * @param  None
  * @retval None
  */
void TIM8_BRK_TIM12_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM8 Update or TIM13 global interrupts.
  * @param  None
  * @retval None
  */
void TIM8_UP_TIM13_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM8 Trigger and Commutation or TIM14 global interrupts.
  * @param  None
  * @retval None
  */
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM8 Capture Compare interrupt.
  * @param  None
  * @retval None
  */
void TIM8_CC_IRQHandler(void)
{

}

/**
  * @brief This function handles ADC3 global interrupt.
  * @param  None
  * @retval None
  */
void ADC3_IRQHandler(void)
{

}

/**
  * @brief This function handles FSMC global interrupt.
  * @param  None
  * @retval None
  */
void FSMC_IRQHandler(void)
{

}

/**
  * @brief This function handles SDIO global interrupt.
  * @param  None
  * @retval None
  */
void SDIO_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM5 global interrupt.
  * @param  None
  * @retval None
  */
void TIM5_IRQHandler(void)
{

}

/**
  * @brief This function handles SPI3 global interrupt.
  * @param  None
  * @retval None
  */
void SPI3_IRQHandler(void)
{

}

/**
  * @brief This function handles UART4 global interrupt.
  * @param  None
  * @retval None
  */
void UART4_IRQHandler(void)
{

}

/**
  * @brief This function handles UART5 global interrupt.
  * @param  None
  * @retval None
  */
void UART5_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM6 global interrupt.
  * @param  None
  * @retval None
  */
void TIM6_IRQHandler(void)
{

}

/**
  * @brief This function handles TIM7 global interrupt.
  * @param  None
  * @retval None
  */
void TIM7_IRQHandler(void)
{

}

/**
  * @brief This function handles DMA2 Channel1 global interrupt.
  * @param  None
  * @retval None
  */
void DMA2_Channel1_IRQHandler(void)
{

}

/**
  * @brief This function handles DMA2 Channel2 global interrupt.
  * @param  None
  * @retval None
  */
void DMA2_Channel2_IRQHandler(void)
{

}

/**
  * @brief This function handles DMA2 Channel3 global interrupt.
  * @param  None
  * @retval None
  */
void DMA2_Channel3_IRQHandler(void)
{

}

/**
  * @brief This function handles DMA2 Channel4 and Channel5 global interrupts.
  * @param  None
  * @retval None
  */
void DMA2_Channel4_5_IRQHandler(void)
{

}

/**
  * @brief This function handles SYMC interrupt.
  * @param  None
  * @retval None
  */
void SYMC_IRQHandler(void)
{

}

/**
  * @brief This function handles RNG interrupt.
  * @param  None
  * @retval None
  */
void RNG_IRQHandler(void)
{

}

/**
  * @brief This function handles SENSOR interrupt.
  * @param  None
  * @retval None
  */
void SENSOR_IRQHandler(void)
{

}

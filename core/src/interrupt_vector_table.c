/**
 ******************************************************************************
 * @file           : interrupt_vector_table.c
 * @brief          : Interrupt vector table for W55MH32.
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
#include <stdint.h>

/* Typedef -------------------------------------------------------------------*/
typedef void (*irq_handler_t)(void);

/* Define --------------------------------------------------------------------*/
/* W55MH32 high-density boot-in-RAM marker; the bootloader reads this 32-bit
 * sentinel at offset 0x1E0 of the vector table to decide whether to remap
 * SRAM to address 0x00000000 instead of flash. */
#define BOOTRAM_MAGIC   (0xF1E0F85FU)

/* Variables -----------------------------------------------------------------*/
extern uint32_t _estack;               /* Top of stack — provided by linker script */

/* Function ------------------------------------------------------------------*/
extern void Reset_Handler(void);       /* Defined in startup_w55mh32.s */

/* Weak system exception handlers. Spin so the failing state stays visible to
 * the debugger; an application may override any of these with a strong
 * definition (see core/src/w55mh32_it.c for the project-level overrides). */
__attribute__((weak)) void NMI_Handler(void)        { while (1) { } }
__attribute__((weak)) void HardFault_Handler(void)  { while (1) { } }
__attribute__((weak)) void MemManage_Handler(void)  { while (1) { } }
__attribute__((weak)) void BusFault_Handler(void)   { while (1) { } }
__attribute__((weak)) void UsageFault_Handler(void) { while (1) { } }
__attribute__((weak)) void SVC_Handler(void)        { while (1) { } }
__attribute__((weak)) void DebugMon_Handler(void)   { while (1) { } }
__attribute__((weak)) void PendSV_Handler(void)     { while (1) { } }
__attribute__((weak)) void SysTick_Handler(void)    { while (1) { } }

/* Weak peripheral IRQ handlers ([16]~[75], IRQ0~IRQ59). */
__attribute__((weak)) void WWDG_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void PVD_IRQHandler(void)                   { while (1) { } }
__attribute__((weak)) void TAMPER_IRQHandler(void)                { while (1) { } }
__attribute__((weak)) void RTC_IRQHandler(void)                   { while (1) { } }
__attribute__((weak)) void FLASH_IRQHandler(void)                 { while (1) { } }
__attribute__((weak)) void RCC_IRQHandler(void)                   { while (1) { } }
__attribute__((weak)) void EXTI0_IRQHandler(void)                 { while (1) { } }
__attribute__((weak)) void EXTI1_IRQHandler(void)                 { while (1) { } }
__attribute__((weak)) void EXTI2_IRQHandler(void)                 { while (1) { } }
__attribute__((weak)) void EXTI3_IRQHandler(void)                 { while (1) { } }
__attribute__((weak)) void EXTI4_IRQHandler(void)                 { while (1) { } }
__attribute__((weak)) void DMA1_Channel1_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void DMA1_Channel2_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void DMA1_Channel3_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void DMA1_Channel4_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void DMA1_Channel5_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void DMA1_Channel6_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void DMA1_Channel7_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void ADC1_2_IRQHandler(void)                { while (1) { } }
__attribute__((weak)) void USB_HP_CAN1_TX_IRQHandler(void)        { while (1) { } }
__attribute__((weak)) void USB_LP_CAN1_RX0_IRQHandler(void)       { while (1) { } }
__attribute__((weak)) void CAN1_RX1_IRQHandler(void)              { while (1) { } }
__attribute__((weak)) void CAN1_SCE_IRQHandler(void)              { while (1) { } }
__attribute__((weak)) void EXTI9_5_IRQHandler(void)               { while (1) { } }
__attribute__((weak)) void TIM1_BRK_TIM9_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void TIM1_UP_TIM10_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void TIM1_TRG_COM_TIM11_IRQHandler(void)    { while (1) { } }
__attribute__((weak)) void TIM1_CC_IRQHandler(void)               { while (1) { } }
__attribute__((weak)) void TIM2_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void TIM3_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void TIM4_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void I2C1_EV_IRQHandler(void)               { while (1) { } }
__attribute__((weak)) void I2C1_ER_IRQHandler(void)               { while (1) { } }
__attribute__((weak)) void I2C2_EV_IRQHandler(void)               { while (1) { } }
__attribute__((weak)) void I2C2_ER_IRQHandler(void)               { while (1) { } }
__attribute__((weak)) void SPI1_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void SPI2_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void USART1_IRQHandler(void)                { while (1) { } }
__attribute__((weak)) void USART2_IRQHandler(void)                { while (1) { } }
__attribute__((weak)) void USART3_IRQHandler(void)                { while (1) { } }
__attribute__((weak)) void EXTI15_10_IRQHandler(void)             { while (1) { } }
__attribute__((weak)) void RTCAlarm_IRQHandler(void)              { while (1) { } }
__attribute__((weak)) void USBWakeUp_IRQHandler(void)             { while (1) { } }
__attribute__((weak)) void TIM8_BRK_TIM12_IRQHandler(void)        { while (1) { } }
__attribute__((weak)) void TIM8_UP_TIM13_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void TIM8_TRG_COM_TIM14_IRQHandler(void)    { while (1) { } }
__attribute__((weak)) void TIM8_CC_IRQHandler(void)               { while (1) { } }
__attribute__((weak)) void ADC3_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void FSMC_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void SDIO_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void TIM5_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void SPI3_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void UART4_IRQHandler(void)                 { while (1) { } }
__attribute__((weak)) void UART5_IRQHandler(void)                 { while (1) { } }
__attribute__((weak)) void TIM6_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void TIM7_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void DMA2_Channel1_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void DMA2_Channel2_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void DMA2_Channel3_IRQHandler(void)         { while (1) { } }
__attribute__((weak)) void DMA2_Channel4_5_IRQHandler(void)       { while (1) { } }

/* Weak WIZnet-specific IRQ handlers (slots [84]~[86]). */
__attribute__((weak)) void SYMC_IRQHandler(void)                  { while (1) { } }
__attribute__((weak)) void RNG_IRQHandler(void)                   { while (1) { } }
__attribute__((weak)) void SENSOR_IRQHandler(void)                { while (1) { } }

/* Vector table — placed in the .isr_vector section so the linker script can
 * pin it at the start of flash. `used` keeps it from being garbage-collected
 * by `-Wl,--gc-sections`. Unlisted slots are zero-filled by the designated
 * initializer (reserved entries [7..10], [13], [76..83], [87..119]). */
__attribute__((section(".isr_vector"), used))
const irq_handler_t g_pfnVectors[] = {
    (irq_handler_t)(&_estack),         /* [0]   Initial stack pointer */
    Reset_Handler,                     /* [1]   Reset */
    NMI_Handler,                       /* [2]   NMI */
    HardFault_Handler,                 /* [3]   Hard fault */
    MemManage_Handler,                 /* [4]   MPU fault */
    BusFault_Handler,                  /* [5]   Bus fault */
    UsageFault_Handler,                /* [6]   Usage fault */
    0, 0, 0, 0,                        /* [7..10] Reserved */
    SVC_Handler,                       /* [11]  SVCall */
    DebugMon_Handler,                  /* [12]  Debug monitor */
    0,                                 /* [13]  Reserved */
    PendSV_Handler,                    /* [14]  PendSV */
    SysTick_Handler,                   /* [15]  SysTick */

    /* W55MH32 peripheral IRQs [16]..[75] */
    WWDG_IRQHandler,                   /* [16]  IRQ0  WWDG */
    PVD_IRQHandler,                    /* [17]  IRQ1  PVD */
    TAMPER_IRQHandler,                 /* [18]  IRQ2  Tamper */
    RTC_IRQHandler,                    /* [19]  IRQ3  RTC */
    FLASH_IRQHandler,                  /* [20]  IRQ4  Flash */
    RCC_IRQHandler,                    /* [21]  IRQ5  RCC */
    EXTI0_IRQHandler,                  /* [22]  IRQ6  EXTI0 */
    EXTI1_IRQHandler,                  /* [23]  IRQ7  EXTI1 */
    EXTI2_IRQHandler,                  /* [24]  IRQ8  EXTI2 */
    EXTI3_IRQHandler,                  /* [25]  IRQ9  EXTI3 */
    EXTI4_IRQHandler,                  /* [26]  IRQ10 EXTI4 */
    DMA1_Channel1_IRQHandler,          /* [27]  IRQ11 DMA1 Ch1 */
    DMA1_Channel2_IRQHandler,          /* [28]  IRQ12 DMA1 Ch2 */
    DMA1_Channel3_IRQHandler,          /* [29]  IRQ13 DMA1 Ch3 */
    DMA1_Channel4_IRQHandler,          /* [30]  IRQ14 DMA1 Ch4 */
    DMA1_Channel5_IRQHandler,          /* [31]  IRQ15 DMA1 Ch5 */
    DMA1_Channel6_IRQHandler,          /* [32]  IRQ16 DMA1 Ch6 */
    DMA1_Channel7_IRQHandler,          /* [33]  IRQ17 DMA1 Ch7 */
    ADC1_2_IRQHandler,                 /* [34]  IRQ18 ADC1/2 */
    USB_HP_CAN1_TX_IRQHandler,         /* [35]  IRQ19 USB HP / CAN1 TX */
    USB_LP_CAN1_RX0_IRQHandler,        /* [36]  IRQ20 USB LP / CAN1 RX0 */
    CAN1_RX1_IRQHandler,               /* [37]  IRQ21 CAN1 RX1 */
    CAN1_SCE_IRQHandler,               /* [38]  IRQ22 CAN1 SCE */
    EXTI9_5_IRQHandler,                /* [39]  IRQ23 EXTI9..5 */
    TIM1_BRK_TIM9_IRQHandler,          /* [40]  IRQ24 TIM1 BRK / TIM9 */
    TIM1_UP_TIM10_IRQHandler,          /* [41]  IRQ25 TIM1 UP  / TIM10 */
    TIM1_TRG_COM_TIM11_IRQHandler,     /* [42]  IRQ26 TIM1 TRG / TIM11 */
    TIM1_CC_IRQHandler,                /* [43]  IRQ27 TIM1 CC */
    TIM2_IRQHandler,                   /* [44]  IRQ28 TIM2 */
    TIM3_IRQHandler,                   /* [45]  IRQ29 TIM3 */
    TIM4_IRQHandler,                   /* [46]  IRQ30 TIM4 */
    I2C1_EV_IRQHandler,                /* [47]  IRQ31 I2C1 EV */
    I2C1_ER_IRQHandler,                /* [48]  IRQ32 I2C1 ER */
    I2C2_EV_IRQHandler,                /* [49]  IRQ33 I2C2 EV */
    I2C2_ER_IRQHandler,                /* [50]  IRQ34 I2C2 ER */
    SPI1_IRQHandler,                   /* [51]  IRQ35 SPI1 */
    SPI2_IRQHandler,                   /* [52]  IRQ36 SPI2 */
    USART1_IRQHandler,                 /* [53]  IRQ37 USART1 */
    USART2_IRQHandler,                 /* [54]  IRQ38 USART2 */
    USART3_IRQHandler,                 /* [55]  IRQ39 USART3 */
    EXTI15_10_IRQHandler,              /* [56]  IRQ40 EXTI15..10 */
    RTCAlarm_IRQHandler,               /* [57]  IRQ41 RTC Alarm */
    USBWakeUp_IRQHandler,              /* [58]  IRQ42 USB Wakeup */
    TIM8_BRK_TIM12_IRQHandler,         /* [59]  IRQ43 TIM8 BRK / TIM12 */
    TIM8_UP_TIM13_IRQHandler,          /* [60]  IRQ44 TIM8 UP  / TIM13 */
    TIM8_TRG_COM_TIM14_IRQHandler,     /* [61]  IRQ45 TIM8 TRG / TIM14 */
    TIM8_CC_IRQHandler,                /* [62]  IRQ46 TIM8 CC */
    ADC3_IRQHandler,                   /* [63]  IRQ47 ADC3 */
    FSMC_IRQHandler,                   /* [64]  IRQ48 FSMC */
    SDIO_IRQHandler,                   /* [65]  IRQ49 SDIO */
    TIM5_IRQHandler,                   /* [66]  IRQ50 TIM5 */
    SPI3_IRQHandler,                   /* [67]  IRQ51 SPI3 */
    UART4_IRQHandler,                  /* [68]  IRQ52 UART4 */
    UART5_IRQHandler,                  /* [69]  IRQ53 UART5 */
    TIM6_IRQHandler,                   /* [70]  IRQ54 TIM6 */
    TIM7_IRQHandler,                   /* [71]  IRQ55 TIM7 */
    DMA2_Channel1_IRQHandler,          /* [72]  IRQ56 DMA2 Ch1 */
    DMA2_Channel2_IRQHandler,          /* [73]  IRQ57 DMA2 Ch2 */
    DMA2_Channel3_IRQHandler,          /* [74]  IRQ58 DMA2 Ch3 */
    DMA2_Channel4_5_IRQHandler,        /* [75]  IRQ59 DMA2 Ch4/5 */

    /* [76..83] Reserved — auto-filled with 0 by designated init below. */
    [84] = SYMC_IRQHandler,            /* [84]  WIZnet crypto */
    RNG_IRQHandler,                    /* [85]  WIZnet random */
    SENSOR_IRQHandler,                 /* [86]  WIZnet sensor */

    /* [87..119] Reserved — auto-filled with 0. */
    [120] = (irq_handler_t)BOOTRAM_MAGIC,  /* [120] Boot-in-RAM marker @ 0x1E0 */
};

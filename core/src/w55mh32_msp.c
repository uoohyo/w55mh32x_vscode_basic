/**
 * @file    w55mh32_msp.c
 * @brief   Board-Support / MSP layer: clock gating and GPIO AF wiring.
 *          All functions are weak defaults so the application can override
 *          them without touching template code.
 */
#include "w55mh32.h"

__attribute__((weak)) void BSP_Init(void)
{
    /* Default: nothing. Application overrides to enable peripherals. */
}

__attribute__((weak)) void BSP_GPIO_Init(void)
{
}

__attribute__((weak)) void BSP_USART_MspInit(USART_TypeDef *USARTx)
{
    (void)USARTx;
}

__attribute__((weak)) void BSP_SPI_MspInit(SPI_TypeDef *SPIx)
{
    (void)SPIx;
}

__attribute__((weak)) void BSP_I2C_MspInit(I2C_TypeDef *I2Cx)
{
    (void)I2Cx;
}

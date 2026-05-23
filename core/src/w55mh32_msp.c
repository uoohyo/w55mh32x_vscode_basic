/**
 ******************************************************************************
 * @file           : w55mh32_msp.c
 * @brief          : Board-Support / MSP layer: clock gating and GPIO AF wiring.
 *                   All functions are weak defaults so the application can override
 *                   them without touching template code.
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
#include "w55mh32.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/* Function -----------------------------------------------------------------*/
/**
 * @brief Board-level top-of-boot initialization hook. Called once from
 *        the application before the main loop to bring up board-specific
 *        peripherals (LEDs, debug UART, ...). Empty default — override
 *        in the application without touching this template file.
 */
__attribute__((weak)) void BSP_Init(void)
{
    /* Default: nothing. Application overrides to enable peripherals. */
}

/**
 * @brief Default GPIO pin / alternate-function mapping hook. Override
 *        in the application to enable GPIO clocks and configure pin
 *        modes / AF for the target board.
 */
__attribute__((weak)) void BSP_GPIO_Init(void)
{
}

/**
 * @brief MSP hook called by the application USART init path. Override
 *        to enable the USART instance's clock, configure its TX/RX pins,
 *        and (if used) install its NVIC priority.
 * @param USARTx USART peripheral instance the application is bringing
 *               up (e.g. USART1, USART2, ...).
 */
__attribute__((weak)) void BSP_USART_MspInit(USART_TypeDef *USARTx)
{
    (void)USARTx;
}

/**
 * @brief MSP hook called by the application SPI init path. Override
 *        to enable the SPI instance's clock, configure SCK/MISO/MOSI
 *        pins, and (if used) install its NVIC / DMA wiring.
 * @param SPIx SPI peripheral instance (e.g. SPI1, SPI2, ...).
 */
__attribute__((weak)) void BSP_SPI_MspInit(SPI_TypeDef *SPIx)
{
    (void)SPIx;
}

/**
 * @brief MSP hook called by the application I2C init path. Override
 *        to enable the I2C instance's clock, configure SCL/SDA pins
 *        (open-drain, AF), and (if used) install its NVIC / DMA wiring.
 * @param I2Cx I2C peripheral instance (e.g. I2C1, I2C2).
 */
__attribute__((weak)) void BSP_I2C_MspInit(I2C_TypeDef *I2Cx)
{
    (void)I2Cx;
}

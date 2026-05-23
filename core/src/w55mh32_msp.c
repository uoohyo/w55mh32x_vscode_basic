/**
 * @file    w55mh32_msp.c
 * @brief   Board-Support / MSP layer: clock gating and GPIO AF wiring.
 *          All functions are weak defaults so the application can override
 *          them without touching template code.
 */
#include "w55mh32.h"

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

/**
 * @file    main.c
 * @brief   Firmware entry point for the W55MH32 VS Code template.
 */
#include "main.h"
#include "w55mh32_it.h"

static void SystemClock_Config(void);

int main(void)
{
    /* SystemInit() ran from startup_w55mh32.s before main() — clocks are
     * already at the default configured in core/src/system_w55mh32.c.
     * Override below if a different PLL/HSE setup is required.
     */
    SystemClock_Config();

    /* TODO: board / peripheral initialization. */

    while (1)
    {
        /* TODO: application logic. */
    }
}

static void SystemClock_Config(void)
{
    /* Default: no override — rely on SystemInit() in system_w55mh32.c.
     * Replace with a custom RCC configuration when needed.
     */
}

void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
        /* Halt for debugger inspection. */
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    (void)file;
    (void)line;
    /* User can route this to a UART logger. */
}
#endif

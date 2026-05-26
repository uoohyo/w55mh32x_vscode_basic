/**
 ******************************************************************************
 * @file           : w55mh32_conf.h
 * @brief          : Module selector for the W55MH32 Standard Peripheral Library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W55MH32_CONF_H
#define __W55MH32_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "misc.h"
#include "w55mh32_adc.h"
#include "w55mh32_bkp.h"
#include "w55mh32_can.h"
#include "w55mh32_crc.h"
#include "w55mh32_dac.h"
#include "w55mh32_dbgmcu.h"
#include "w55mh32_dma.h"
#include "w55mh32_exti.h"
#include "w55mh32_flash.h"
#include "w55mh32_gpio.h"
#include "w55mh32_i2c.h"
#include "w55mh32_iwdg.h"
#include "w55mh32_otp.h"
#include "w55mh32_pwr.h"
#include "w55mh32_rcc.h"
#include "w55mh32_rtc.h"
#include "w55mh32_sdio.h"
#include "w55mh32_spi.h"
#include "w55mh32_tim.h"
#include "w55mh32_trng.h"
#include "w55mh32_usart.h"
#include "w55mh32_wwdg.h"
#include "w55mh32_wztoe.h"

/* Defines -------------------------------------------------------------------*/
#ifdef USE_FULL_ASSERT
  #define assert_param(expr) \
      ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
  void assert_failed(uint8_t *file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif

#endif /* __W55MH32_CONF_H */

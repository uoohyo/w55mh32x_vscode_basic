/**
 * @file    w55mh32_conf.h
 * @brief   Module selector for the W55MH32 Standard Peripheral Library.
 *
 * Vendor header w55mh32.h pulls this file in when USE_STDPERIPH_DRIVER
 * is defined.
 *
 * All SPL peripheral headers are enabled below by default to match the source
 * set in cmake/w55mh32/CMakeLists.txt. Comment out any driver you do not need.
 * Drivers with external dependencies (e.g. w55mh32_wztoe.h requires
 * wizchip_conf.h from WIZnet ioLibrary) are already active; add the
 * dependency before building if you use them.
 */
#ifndef __W55MH32_CONF_H
#define __W55MH32_CONF_H

/* Always-on core peripherals */
#include "misc.h"

/* Optional peripherals */
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

#ifdef USE_FULL_ASSERT
  #define assert_param(expr) \
      ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
  void assert_failed(uint8_t *file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif

#endif /* __W55MH32_CONF_H */

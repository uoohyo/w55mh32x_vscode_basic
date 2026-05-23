# INTERFACE library bundling W55MH32 CMSIS device + Standard Peripheral Library.
# Application targets pull this in via target_link_libraries(<app> PRIVATE w55mh32x_hal).

add_library(w55mh32x_hal INTERFACE)

target_sources(w55mh32x_hal INTERFACE
    # CMSIS / system — vendor copy kept under drivers/, link target lives in core/.
    ${CMAKE_SOURCE_DIR}/core/src/system_w55mh32.c

    # core_cm3.c (V1.30, 2009) is intentionally NOT listed. The header
    # core/inc/core_cm3.h is V3.20 (2013), and the V3.x CMSIS standard
    # moved every NVIC/SCB/SysTick/intrinsic helper to "__STATIC_INLINE"
    # in the header — the .c file is no longer expected at link time.
    # Building V1.30 .c against V3.20 .h also trips a GCC 12+ assembler
    # error on STREXB/STREXH (source = destination register). The file
    # itself is kept on disk as a vendor archive; only the build entry
    # is removed. See design doc §11 and task #13.

    # SPL — always-on core peripherals
    ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/misc.c
    ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_rcc.c
    ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_gpio.c

    # SPL — optional peripherals (uncomment per project needs)
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_adc.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_usart.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_spi.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_i2c.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_tim.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_dma.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_exti.c
    # ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/src/w55mh32_flash.c
)

target_include_directories(w55mh32x_hal INTERFACE
    ${CMAKE_SOURCE_DIR}/core/inc
    ${CMAKE_SOURCE_DIR}/drivers/W55MH32X_Driver/inc
    ${CMAKE_SOURCE_DIR}/drivers/CMSIS/Device/WIZnet/W55MH32X/inc
)

# USE_STDPERIPH_DRIVER  — required for w55mh32.h to pull in w55mh32_conf.h.
# W55MH32                — IntelliSense / external-tool discriminator only;
#                          the vendor header does not branch on it.
target_compile_definitions(w55mh32x_hal INTERFACE
    USE_STDPERIPH_DRIVER
    W55MH32
)

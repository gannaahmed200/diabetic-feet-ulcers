/* stm32f1xx_hal_conf.h — HAL module enable/disable for Smart Shoe project */
#ifndef __STM32F1xx_HAL_CONF_H
#define __STM32F1xx_HAL_CONF_H

/* ---- Enable only the HAL modules used by this project ---- */
#define HAL_MODULE_ENABLED
#define HAL_ADC_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED

/* ---- HSE/HSI oscillator values ---- */
#if !defined(HSE_VALUE)
  #define HSE_VALUE    8000000U   /*!< 8 MHz crystal on Blue Pill */
#endif
#if !defined(HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT  100U
#endif
#if !defined(HSI_VALUE)
  #define HSI_VALUE    8000000U
#endif
#if !defined(LSI_VALUE)
  #define LSI_VALUE    40000U
#endif
#if !defined(LSE_VALUE)
  #define LSE_VALUE    32768U
#endif
#if !defined(LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT  5000U
#endif

/* ---- Tick frequency ---- */
#define TICK_INT_PRIORITY   0x0FU
#define USE_RTOS            0U
#define PREFETCH_ENABLE     1U

/* ---- assert_param: required by HAL source files ---- */
#define assert_param(expr)  ((void)0U)   /* disable runtime checks for bare-metal */

/* ---- HAL module includes (order matters: dependencies first) ---- */
#ifdef HAL_CORTEX_MODULE_ENABLED
  #include "stm32f1xx_hal_cortex.h"
#endif
#ifdef HAL_RCC_MODULE_ENABLED
  #include "stm32f1xx_hal_rcc.h"
#endif
#ifdef HAL_FLASH_MODULE_ENABLED
  #include "stm32f1xx_hal_flash.h"
#endif
#ifdef HAL_GPIO_MODULE_ENABLED
  #include "stm32f1xx_hal_gpio.h"
#endif
#ifdef HAL_DMA_MODULE_ENABLED
  #include "stm32f1xx_hal_dma.h"   /* must come before ADC and UART */
#endif
#ifdef HAL_PWR_MODULE_ENABLED
  #include "stm32f1xx_hal_pwr.h"
#endif
#ifdef HAL_ADC_MODULE_ENABLED
  #include "stm32f1xx_hal_adc.h"
#endif
#ifdef HAL_TIM_MODULE_ENABLED
  #include "stm32f1xx_hal_tim.h"
#endif
#ifdef HAL_UART_MODULE_ENABLED
  #include "stm32f1xx_hal_uart.h"
#endif

#endif /* __STM32F1xx_HAL_CONF_H */

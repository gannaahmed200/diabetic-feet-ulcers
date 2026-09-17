/* Src/system_stm32f1xx.c — minimal system init for STM32F103C8T6 @ 8 MHz (HSI) */
#include "stm32f1xx_hal.h"

void Error_Handler(void);   /* forward declaration */

uint32_t SystemCoreClock = 8000000UL;

/* These tables are referenced by HAL_RCC functions */
const uint8_t AHBPrescTable[16U] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8U]  = {0, 0, 0, 0, 1, 2, 3, 4};

void SystemInit(void)
{
    /* FPU not present on M3 — nothing to do here.
     * Real clock config is done by SystemClock_Config() in main via HAL RCC APIs. */
    SCB->VTOR = FLASH_BASE; /* vector table at start of Flash */
}

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClkInitTypeDef clk = {0};

    /* Run directly off the internal 8 MHz HSI oscillator, no PLL.
     * No external crystal is wired on the schematic (OSC Frequency = 0
     * on the STM32 component in Proteus), so HSE must not be used here -
     * that was the bug: HAL_RCC_OscConfig() was silently timing out
     * waiting for a crystal that doesn't exist, leaving the chip on its
     * default clock while the firmware still assumed 72 MHz. */
    osc.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
    osc.HSIState             = RCC_HSI_ON;
    osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    osc.PLL.PLLState         = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&osc) != HAL_OK)
    {
        Error_Handler();
    }

    /* SYSCLK = HCLK = PCLK1 = PCLK2 = 8 MHz */
    clk.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                         RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk.SYSCLKSource   = RCC_SYSCLKSOURCE_HSI;
    clk.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV1;
    clk.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}

/* Minimal peripheral inits (stubs that CubeMX normally generates) */
void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef gpio = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();   /* needed for AF pin remapping on F1 */

    /* ── PA0–PA4 : Analog inputs (FSR × 3 + LM35 × 2 → ADC1 CH0–CH4) ───── */
    gpio.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                 GPIO_PIN_3 | GPIO_PIN_4;
    gpio.Mode  = GPIO_MODE_ANALOG;
    gpio.Pull  = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &gpio);

    /* ── PA8 : Buzzer / alert LED — push-pull output ─────────────────────── */
    gpio.Pin   = GPIO_PIN_8;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpio);

    /* ── PA9 : USART1_TX — alternate-function push-pull ──────────────────── */
    gpio.Pin   = GPIO_PIN_9;
    gpio.Mode  = GPIO_MODE_AF_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;   /* ≥ baud-rate × 16 for clean edges */
    HAL_GPIO_Init(GPIOA, &gpio);

    /* ── PA10 : USART1_RX — floating input (UART handles sampling) ───────── */
    gpio.Pin   = GPIO_PIN_10;
    gpio.Mode  = GPIO_MODE_INPUT;
    gpio.Pull  = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &gpio);

    /* ── PB0 : DHT11 data line — start as pull-up input;                 ─── */
    /*          DHT11 driver re-configures it dynamically as needed.          */
    gpio.Pin  = GPIO_PIN_0;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &gpio);
}

void MX_ADC1_Init(void)
{
    extern ADC_HandleTypeDef hadc1;
    __HAL_RCC_ADC1_CLK_ENABLE();
    hadc1.Instance                   = ADC1;
    hadc1.Init.ScanConvMode          = ADC_SCAN_DISABLE;
    hadc1.Init.ContinuousConvMode    = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion       = 1;
    HAL_ADC_Init(&hadc1);
    HAL_ADCEx_Calibration_Start(&hadc1);
}

void MX_USART1_UART_Init(void)
{
    extern UART_HandleTypeDef huart1;
    __HAL_RCC_USART1_CLK_ENABLE();
    huart1.Instance          = USART1;
    huart1.Init.BaudRate     = 9600;
    huart1.Init.WordLength   = UART_WORDLENGTH_8B;
    huart1.Init.StopBits     = UART_STOPBITS_1;
    huart1.Init.Parity       = UART_PARITY_NONE;
    huart1.Init.Mode         = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart1);
}

void Error_Handler(void)
{
    __disable_irq();
    while (1) { }
}

/* USER CODE BEGIN Header */
/*
 * ============================================================
 *  DIAGNOSTIC BLINK TEST — not the real firmware
 * ------------------------------------------------------------
 *  Purpose: isolate whether the MCU + clock + programming chain
 *  works at all, with zero dependency on ADC, UART, or DHT11.
 *
 *  If PA8 blinks (buzzer/LED toggles every 500ms) -> the chip,
 *  clock, power, reset, and .hex loading are ALL fine, and the
 *  real bug is specific to ADC/UART/DHT11 in the main firmware.
 *
 *  If PA8 does NOT blink -> the problem is more fundamental:
 *  power/reset/boot0 wiring, or the .hex isn't actually loading.
 * ============================================================
 */
/* USER CODE END Header */

#include "main.h"

void SystemClock_Config(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef gpio = {0};
    gpio.Pin   = GPIO_PIN_8;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpio);

    while (1)
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
        HAL_Delay(500);
    }
}

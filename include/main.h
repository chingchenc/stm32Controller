#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx_hal.h"

#define LED_PIN                                GPIO_PIN_5
#define LED_GPIO_PORT                          GPIOA
#define LED_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOA_CLK_ENABLE()

#define BUTTON_PIN                             GPIO_PIN_13
#define BUTTON_GPIO_PORT                       GPIOC
#define BUTTON_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOC_CLK_ENABLE()

#define USART2_TX_PIN                          GPIO_PIN_2
#define USART2_RX_PIN                          GPIO_PIN_3
#define USART2_CLK_ENABLE()                    __HAL_RCC_USART2_CLK_ENABLE();
#define USART2_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOA_CLK_ENABLE();

void SystemClock_Config(void);

#endif // MAIN_H
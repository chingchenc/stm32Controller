#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "main.h"

// c library
#include <string.h>
// cpp library
#include <vector>

#include "button.h"
#include "led.h"
#include "uart.h"

// if main.cpp is compiled as C++, the SysTick_Handler must be declared as extern "C"
#ifdef __cplusplus
extern "C" void SysTick_Handler(void);
#endif

namespace test {
    // Tests for LED and Button
    void Toggle();
    void PressOn();
    void PressOff();
    // Tests for UART
    void TransmitMsg();
    void ReceiveMsg();
}  // namespace test

UART_HandleTypeDef huart2;

LED led(LED_GPIO_PORT, LED_PIN);
Button button(BUTTON_GPIO_PORT, BUTTON_PIN);
UART uart(huart2);

int main(void) {
    test::Toggle();
    // test::PressOff();
    // test::PressOn();
    // test::TransmitMsg();
    // test::ReceiveMsg();
}

void test::Toggle() {
    int delay_time = 200;  // milliseconds
    HAL_Init();
    led.Init();
    button.Init();

    while (1) {
        led.Toggle();
        HAL_Delay(delay_time);
    }
}

void test::PressOn() {
    HAL_Init();
    led.Init();
    button.Init();

    while (1) {
        if (button.IsPressed()) {
            led.On();
        } else {
            led.Off();
        }
    }
}

void test::PressOff() {
    HAL_Init();
    led.Init();
    button.Init();

    while (1) {
        if (button.IsPressed()) {
            led.Off();
        } else {
            led.On();
        }
    }
}

void test::TransmitMsg() {
    int delay_time = 300;  // milliseconds
    char msg[] = "Hello from STM32 !\r\n";

    HAL_Init();
    /* setup system clock */
    SystemClock_Config();

    uart.Init(115200);
    uart.GPIO_Init();

    while (1) {
        uart.Transmit((uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
        HAL_Delay(delay_time);
    }
}

void test::ReceiveMsg() {
    HAL_Init();
    /* setup system clock */
    SystemClock_Config();

    led.Init();
    uart.Init(115200);
    uart.GPIO_Init();

    // receive 1 char from keyboard
    char rx;
    char msg_on[] = "LED ON\r\n";
    char msg_off[] = "LED OFF\r\n";

    while (1) {
        // receive 1 char from keyboard
        uart.Receive((uint8_t*)&rx, 1, HAL_MAX_DELAY);

        if (rx == '1') {
            led.On();
            uart.Transmit((uint8_t*)msg_on, strlen(msg_on), HAL_MAX_DELAY);
        } else if (rx == '0') {
            led.Off();
            uart.Transmit((uint8_t*)msg_off, strlen(msg_off), HAL_MAX_DELAY);
        }
    }
}

void SysTick_Handler(void) {
    // HAL_Delay needs this
    HAL_IncTick();
}

/* ===== System Clock Config ===== */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}
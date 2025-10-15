#include "main.h"
#include "uart.h"

void UART::Init(uint32_t baudRate) {
    USART2_CLK_ENABLE();  // enable UART2 clock
    _instance.Instance = USART2;
    _instance.Init.BaudRate = baudRate;
    _instance.Init.WordLength = UART_WORDLENGTH_8B;
    _instance.Init.StopBits = UART_STOPBITS_1;
    _instance.Init.Parity = UART_PARITY_NONE;
    _instance.Init.Mode = UART_MODE_TX_RX;
    _instance.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    _instance.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&_instance);
}

void UART::GPIO_Init() {
    // Initialize GPIO for the UART (PA2 TX, PA3 RX)
    USART2_GPIO_CLK_ENABLE();
    GPIO_InitStruct = {0};

    /* PA2 -> USART2_TX, PA3 -> USART2_RX */
    GPIO_InitStruct.Pin = USART2_TX_PIN | USART2_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;       // Alternate function push-pull
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;  // AF for USART2
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

HAL_StatusTypeDef UART::Transmit(const uint8_t* data, uint16_t size, uint32_t timeout) {
    return HAL_UART_Transmit(&_instance, const_cast<uint8_t*>(data), size, timeout);
}

HAL_StatusTypeDef UART::Receive(uint8_t* data, uint16_t size, uint32_t timeout) {
    return HAL_UART_Receive(&_instance, data, size, timeout);
}

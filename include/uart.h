#include "stm32f4xx_hal.h"

class UART {
public:
    UART(UART_HandleTypeDef& instance) : _instance(instance) {}
    void Init(uint32_t baudRate);
    void GPIO_Init();
    HAL_StatusTypeDef Transmit(const uint8_t* data, uint16_t size, uint32_t timeout);
    HAL_StatusTypeDef Receive(uint8_t* data, uint16_t size, uint32_t timeout);

private:
    UART_HandleTypeDef& _instance;
    GPIO_InitTypeDef GPIO_InitStruct;
};
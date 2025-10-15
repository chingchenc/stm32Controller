#include "stm32f4xx_hal.h"

class Button {
public:
    Button(GPIO_TypeDef* gpioPort, uint16_t gpioPin)
        : _gpioPort(gpioPort), _gpioPin(gpioPin) {}
    void Init();
    bool IsPressed();

private:
    GPIO_TypeDef* _gpioPort;
    uint16_t _gpioPin;
    GPIO_InitTypeDef GPIO_InitStruct;
};

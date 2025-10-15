#include "stm32f4xx_hal.h"

class LED {
public:
    LED(GPIO_TypeDef* gpioPort, uint16_t gpioPin) 
        : _gpioPort(gpioPort), _gpioPin(gpioPin) {}
    void Init();
    void Toggle();
    void On();
    void Off();

private:
    GPIO_TypeDef* _gpioPort;
    uint16_t _gpioPin;
    GPIO_InitTypeDef GPIO_InitStruct;
};
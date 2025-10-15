#include "main.h"
#include "button.h"

void Button::Init() {
    // Initialize GPIO for the button
    BUTTON_GPIO_CLK_ENABLE();
    GPIO_InitStruct.Pin = BUTTON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStruct);
}

bool Button::IsPressed() {
    return HAL_GPIO_ReadPin(_gpioPort, _gpioPin) == GPIO_PIN_RESET;
}
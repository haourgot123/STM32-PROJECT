#include "led_control.h"
void led_control(int index, int status)
{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0 << index,(GPIO_PinState)status);
}

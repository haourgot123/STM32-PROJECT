#ifndef HCSR04_H
#define HCSR04_H
#include "stm32f1xx_hal.h"
typedef enum
{
	HCSR04_IDLE_STATE, // state chua do dac 
	HCSR04_WAIT_RISING_STATE, // cho canh len 
	HCSR04_WAIT_FALLING_STATE, // cho canh xuong
	HCSR04_COMPLETE_STATE, // chuyen doi xong
}HCSR04_State;
void HC04_Handle(void);
void hc04_init(TIM_HandleTypeDef *_htim);
void HC04_Start(void);
#endif

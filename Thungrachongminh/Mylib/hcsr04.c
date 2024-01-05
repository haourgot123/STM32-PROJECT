#include "hcsr04.h"
TIM_HandleTypeDef *htim;
HCSR04_State hc04_state = HCSR04_IDLE_STATE;
void HC04_Complete_Callback(float kc);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(hc04_state)
	{
		case HCSR04_WAIT_RISING_STATE:
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) == 1)
			{
				htim->Instance->CNT =0;
				hc04_state = HCSR04_WAIT_FALLING_STATE;
				HAL_TIM_Base_Start(htim);
			}
			else
			{
				hc04_state = HCSR04_IDLE_STATE;
			}
			break;
		case HCSR04_WAIT_FALLING_STATE:
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) == 0)
			{
				HAL_TIM_Base_Stop(htim);
				hc04_state = HCSR04_COMPLETE_STATE;
			}
			else
			{
				hc04_state = HCSR04_IDLE_STATE;
			}
			break;
		default:
			break;
	}	
}
void HC04_Start()
{
	if(hc04_state == HCSR04_IDLE_STATE)
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,(GPIO_PinState)1);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,(GPIO_PinState)0);
		
		hc04_state = HCSR04_WAIT_RISING_STATE;
	}
}
__weak void HC04_Complete_Callback(float kc)
{
	//hien thi lcd
	// dieu dong co
	// mo cua
}
void HC04_Handle()
{
	if(hc04_state == HCSR04_COMPLETE_STATE)
	{
		//tinh toan khoang cach
		float kc = 0.017*htim->Instance->CNT;
		HC04_Complete_Callback(kc);
		hc04_state = HCSR04_IDLE_STATE;
	}
}
void hc04_init(TIM_HandleTypeDef *_htim)
{
	htim = _htim;
}

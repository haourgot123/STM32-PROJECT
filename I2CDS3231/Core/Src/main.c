/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "RTC_DS3231.h"
#include "LiquidCrystal_I2C.h"
#include "button.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */
LiquidCrystal_I2C hlcd;
RTC_Typedef hrtc1;
Button_Typedef button1;
Button_Typedef button2;
Button_Typedef button3;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t flag_button = 0;
uint32_t get_time = 0;
DATETIME time_setup;
typedef enum
{
	STATE_IDOL,
	SET_SECOND,
	SET_MIN,
	SET_HOUR,
	SET_DATE,
	SET_MONTH,
	SET_YEAR,
	SET_COMPLETE,
	SET_EXIST,
}SET_DATE_TIME;
SET_DATE_TIME set_dt;
void btn_press_timeout_callback(Button_Typedef *ButtonX)
{
	if(ButtonX == &button1)
	{
		set_dt = STATE_IDOL;
	}
}
void	btn_pressing_callback(Button_Typedef *ButtonX)
{
			if(ButtonX == &button1)
			{
				switch(set_dt)
				{
					case STATE_IDOL:
						set_dt = SET_SECOND;
					break;
					case SET_SECOND:
						set_dt = SET_MIN;
					break;
					case SET_MIN:
						set_dt = SET_HOUR;
					break;
					case SET_HOUR:
						set_dt = SET_DATE;
					break;
					case SET_DATE:
						set_dt = SET_MONTH;
					break;
					case SET_MONTH:
						set_dt = SET_YEAR;
					break;
					case SET_YEAR:
						set_dt = SET_COMPLETE;
					break;
					case SET_COMPLETE:
						set_dt = STATE_IDOL;
					default:
						break;
				}
			}
			else if(ButtonX == &button2)
			{
				flag_button = 1;
				
			}
			else if(ButtonX == &button3)
			{
				flag_button = 2;	
			}
}
void lcd_state_idol()
{
	lcd_set_cursor(&hlcd,0,0);
	lcd_printf(&hlcd,"DATE: %02d/%02d/%02d  ",hrtc1.date_time.date,hrtc1.date_time.month,hrtc1.date_time.year);
	lcd_set_cursor(&hlcd,1,0);
	lcd_printf(&hlcd,"TIME: %02d:%02d:%02d  ",hrtc1.date_time.hour,hrtc1.date_time.min,hrtc1.date_time.second);
}
void lcd_set_second()
{
	if(flag_button == 1)
	{
		if(time_setup.second == 59) time_setup.second = 0;
		else
		{
			time_setup.second = time_setup.second + 1;
		}
		flag_button = 0;
	}
	if(flag_button == 2)
	{
		if(time_setup.second == 0) time_setup.second = 59;
		else
		{
			time_setup.second = time_setup.second - 1;
		}
		flag_button = 0;
	}
	lcd_set_cursor(&hlcd,0,0);
	lcd_printf(&hlcd,"_CAP NHAT GIAY_");
	lcd_set_cursor(&hlcd,1,0);
	lcd_printf(&hlcd,"   GIAY: %02d   ",time_setup.second);
}
void lcd_set_minus()
{
	if(flag_button == 1)
	{
		if(time_setup.min == 59) time_setup.min = 0;
		else
		{
			time_setup.min = time_setup.min + 1;
		}
		flag_button = 0;
	}
	if(flag_button == 2)
	{
		if(time_setup.min == 0) time_setup.min = 59;
		else
		{
			time_setup.min = time_setup.min - 1;
		}
		flag_button = 0;
	}
	lcd_set_cursor(&hlcd,0,0);
	lcd_printf(&hlcd,"_CAP NHAT PHUT_");
	lcd_set_cursor(&hlcd,1,0);
	lcd_printf(&hlcd,"   PHUT: %02d   ",time_setup.min);
}
void lcd_set_hour()
{
	if(flag_button == 1)
	{
		if(time_setup.hour == 23) time_setup.hour = 0;
		else
		{
			time_setup.hour = time_setup.hour + 1;
		}
		flag_button = 0;
	}
	if(flag_button == 2)
	{
		if(time_setup.hour == 0) time_setup.hour = 23;
		else
		{
			time_setup.hour = time_setup.hour - 1;
		}
		flag_button = 0;
	}
	lcd_set_cursor(&hlcd,0,0);
	lcd_printf(&hlcd,"_CAP NHAT GIO_ ");
	lcd_set_cursor(&hlcd,1,0);
	lcd_printf(&hlcd,"    GIO: %02d   ",time_setup.hour);
}
void lcd_set_date()
{
	if(flag_button == 1)
	{
		if(time_setup.date == 31) time_setup.date = 1;
		else
		{
			time_setup.date = time_setup.date + 1;
		}
		flag_button = 0;
	}
	if(flag_button == 2)
	{
		if(time_setup.date == 1) time_setup.date = 31;
		else
		{
			time_setup.date = time_setup.date - 1;
		}
		flag_button = 0;
	}
	lcd_set_cursor(&hlcd,0,0);
	lcd_printf(&hlcd,"_CAP NHAT NGAY_");
	lcd_set_cursor(&hlcd,1,0);
	lcd_printf(&hlcd,"   DATE: %02d   ",time_setup.date);
}
void lcd_set_month()
{
	if(flag_button == 1)
	{
		if(time_setup.month == 12) time_setup.month = 1;
		else
		{
			time_setup.month = time_setup.month + 1;
		}
		flag_button = 0;
	}
	if(flag_button == 2)
	{
		if(time_setup.month == 1) time_setup.month = 12;
		else
		{
			time_setup.month = time_setup.month - 1;
		}
		flag_button = 0;
	}
	lcd_set_cursor(&hlcd,0,0);
	lcd_printf(&hlcd,"CAP NHAT THANG ");
	lcd_set_cursor(&hlcd,1,0);
	lcd_printf(&hlcd,"  THANG: %02d   ",time_setup.month);
}
void lcd_set_year()
{
	if(flag_button == 1)
	{
		if(time_setup.year == 99) time_setup.year = 0;
		else
		{
			time_setup.year = time_setup.year + 1;
		}
		flag_button = 0;
	}
	if(flag_button == 2)
	{
		if(time_setup.year == 0) time_setup.year = 99;
		else
		{
			time_setup.year = time_setup.year - 1;
		}
		flag_button = 0;
	}
	lcd_set_cursor(&hlcd,0,0);
	lcd_printf(&hlcd,"_CAP NHAT NAM_  ");
	lcd_set_cursor(&hlcd,1,0);
	lcd_printf(&hlcd,"   NAM: %02d    ",time_setup.year);
}
void lcd_complete()
{
	RTC_WriteTime(&hrtc1,&time_setup);
	lcd_set_cursor(&hlcd,0,0);
	lcd_printf(&hlcd,".....UPDATE.....");
	lcd_set_cursor(&hlcd,1,0);
	lcd_printf(&hlcd,"UPDATE_SUCESSFUL");
}
void LCD_Handle()
{
			switch(set_dt)
		{
			case STATE_IDOL:
				lcd_state_idol();
				break;
			case SET_SECOND:
				lcd_set_second();
				break;
			case SET_MIN:
				lcd_set_minus();
				break;
			case SET_HOUR:
				lcd_set_hour();
				break;
			case SET_DATE:
				lcd_set_date();
				break;
			case SET_MONTH:
				lcd_set_month();
				break;
			case SET_YEAR:
				lcd_set_year();
				break;
			case SET_COMPLETE:
				lcd_complete();
				break;
		}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	lcd_init(&hlcd,&hi2c1,LCD_ADDR_DEFAULT);
	RTC_Init(&hrtc1,&hi2c1);
	button_init(&button1,GPIOA,GPIO_PIN_0);
	button_init(&button2,GPIOA,GPIO_PIN_1);
	button_init(&button3,GPIOA,GPIO_PIN_2);
	// khoi tao gia tri bo dem thoi gian o lan dau tien 
//		hrtc1.date_time.second = 10;
//		hrtc1.date_time.min = 10;
//		hrtc1.date_time.hour = 8;
//		hrtc1.date_time.day = 3;
//		hrtc1.date_time.date = 12;
//		hrtc1.date_time.month = 9;
//		hrtc1.date_time.year= 23;
//		RTC_WriteTime(&hrtc1,&hrtc1.date_time);
		set_dt = STATE_IDOL;
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		
    /* USER CODE BEGIN 3 */
		if(HAL_GetTick() - get_time >= 1000)
		{
			RTC_ReadTime(&hrtc1,&hrtc1.date_time);
			get_time = HAL_GetTick();
		}
		LCD_Handle();
		button_handle(&button1);
		button_handle(&button2);
		button_handle(&button3);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PA0 PA1 PA2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

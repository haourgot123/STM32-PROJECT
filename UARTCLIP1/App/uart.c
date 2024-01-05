#include "uart.h"
#include "string.h"
#include "gettemperature_ci.h"
#include "cli_command.h"
#define MAX_DATA 100
UART_HandleTypeDef *huart;
char uart_buff[MAX_DATA];
static uint8_t uart_len = 0;
uint8_t uart_flag = 0;
void receive_data(uint8_t data_rx)
{
	if(data_rx =='\n') // nhan xong
	{
		uart_buff[uart_len++] = '\0';
		uart_flag = 1;
	}
	else // dang nhan 
	{
		uart_buff[uart_len++] = data_rx;
	}
}
void uart_handle()
{
	if(uart_flag)
	{
		cli_command_excute(uart_buff,uart_len);
		
		uart_len = 0;
		uart_flag = 0;
	}
}
void uart_init(UART_HandleTypeDef *uart)
{
	huart = uart;
}

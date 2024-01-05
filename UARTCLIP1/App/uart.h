#ifndef UART_H
#define UART_H
#include "stm32f1xx.h"
#include <stdint.h>
void receive_data(uint8_t c);
void uart_handle(void);
void uart_init(UART_HandleTypeDef *uart);

#endif

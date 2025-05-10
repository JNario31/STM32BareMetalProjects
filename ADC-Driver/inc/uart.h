#ifndef __UART_H__
#define __UART_H__
#include "stm32f4xx.h"
#include "stm32f446xx.h"
void uart_init(void);
void uart_write(int ch);
#endif
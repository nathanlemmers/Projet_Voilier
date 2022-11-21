#ifndef UART_H
#define UART_H

#include "stm32f10x.h"
#include "MyGPIO.h"



void UART_Config(USART_TypeDef * UART);
void UART_send_char(char caractere);
void UART_send_message(const char message[]);
char UART_getOctet(void);
void USART3_IRQHandler(void);

#endif


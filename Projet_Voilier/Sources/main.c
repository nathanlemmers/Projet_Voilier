
#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "UART.h"

void fonctionn(char caractere){
		
	}

int main (void)
{
	
UART_Config(USART3);
UART_confIT(&fonctionn);
	
	
	while (1) {
	}
}

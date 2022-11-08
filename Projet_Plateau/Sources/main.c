
#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "UART.h"
#include "Voiles.h"

void fonctionn(char caractere){
		
	}

int main (void)
{
	
UART_Config(USART3);
UART_confIT(&fonctionn);
Voiles_Init() ;
	
	while (1) {
		Voiles_Update() ;
	}
}

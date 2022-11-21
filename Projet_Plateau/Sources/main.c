
#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "UART.h"
#include "Plateau.h"



int main (void)
{

	Plateau_init();
	UART_Config(USART3);

	
	while(1){
	Plateau_set_vitesse(UART_getOctet());
	Plateau_Tourner();
	}
}

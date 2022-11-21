
#include "stm32f10x.h"
#include "Voiles.h"
#include "Plateau.h"
#include "UART.h"

void SysTick_Handler(){
	Plateau_set_vitesse(UART_getOctet());
	Voiles_Update() ;
}

int main (void)
{
	
	Voiles_Init() ;
	Plateau_init();
	UART_Config(USART3);
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE; 
	SysTick->CTRL |= SysTick_CTRL_TICKINT; 
	//SysTick->CTRL = 7 ;
	
	SysTick->LOAD = 14400000 ;
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 10);
	
	while (1) {
		Plateau_Tourner();
	}
}

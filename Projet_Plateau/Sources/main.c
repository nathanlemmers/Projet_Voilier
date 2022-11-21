
#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "UART.h"
#include "Plateau.h"

void SysTick_Handler(){
Plateau_set_vitesse(UART_getOctet());
}

int main (void)
{
	SysTick->CTRL |= SysTick_CTRL_ENABLE;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE; 
	SysTick->CTRL |= SysTick_CTRL_TICKINT; 
	//SysTick->CTRL = 7 ;
	
	SysTick->LOAD = 14400000 ;
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 10);
	
	
	Plateau_init();
	UART_Config(USART3);

	
	while(1){
	Plateau_Tourner();
	}
}

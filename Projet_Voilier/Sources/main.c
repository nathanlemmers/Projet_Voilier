
#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"


void configureIncrementalEncoder()
{
	MyGPIO_Struct_TypeDef TI1, TI2 ;
	TI1.GPIO = GPIOB ;
	TI1.GPIO_Conf = In_Floating ;
	TI1.GPIO_Pin = 6 ;
	MyGPIO_Init (&TI1) ;
	TI2.GPIO = GPIOB ;
	TI2.GPIO_Conf = In_Floating ;
	TI2.GPIO_Pin = 7 ;
	MyGPIO_Init (&TI2) ;
	
	
	MyTimer_Struct_TypeDef Timer4Config = {TIM4 , 0 , 360*4} ; 
	MyTimer_Base_Init(&Timer4Config);
	
	
	// TODO : mettre les bonnes valeurs (page 392)
	TIM4->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIM4->CCMR1 &= ~TIM_CCMR1_CC2S;
	TIM4->CCER &= ~TIM_CCER_CC1P ;
	TIM4->CCER &= ~TIM_CCER_CC1NP ;
	TIM4->CCMR1 &= ~TIM_CCMR1_IC1F ;
	TIM4->CCER &= ~TIM_CCER_CC2P ;
	TIM4->CCER &= ~TIM_CCER_CC2NP ;
	TIM4->CCMR1 &= ~TIM_CCMR1_IC2F ;
}

int main (void)
{
	
	
	while (1) {
	}
}

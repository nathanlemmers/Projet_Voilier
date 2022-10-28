#include "MyTimer.h"
#include "MyGPIO.h"

void (*handler)(void);

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * TimerSet )
{
	if (TimerSet->Timer == TIM1) {
		
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN ;
		
		TIM1->PSC = TimerSet->PSC ;
		TIM1->ARR = TimerSet->ARR ;
		TIM1->CR1 &= ~TIM_CR1_DIR ;
		
	} else if (TimerSet->Timer == TIM2) {
		
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN ;
		
		TIM2->PSC = TimerSet->PSC ;
		TIM2->ARR = TimerSet->ARR ;
		TIM2->CR1 &= ~TIM_CR1_DIR ;
		
	} else if (TimerSet->Timer == TIM3) {
		
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN ;
		
		TIM3->PSC = TimerSet->PSC ;
		TIM3->ARR = TimerSet->ARR ;
		TIM3->CR1 &= ~TIM_CR1_DIR ;
		
	} else if (TimerSet->Timer == TIM4) {
		
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN ;
		
		TIM4->PSC = TimerSet->PSC ;
		TIM4->ARR = TimerSet->ARR ;
		TIM4->CR1 &= ~TIM_CR1_DIR ;
		
	}
}


void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio , void (*IT_function) (void) )
{
	if (Timer == TIM1) {
			
		NVIC_EnableIRQ(TIM1_UP_IRQn) ;
		NVIC_SetPriority(TIM1_UP_IRQn, Prio) ;
		handler = IT_function ;
		
	} else if (Timer == TIM2) {
		
		NVIC_EnableIRQ(TIM2_IRQn) ;
		NVIC_SetPriority(TIM2_IRQn, Prio) ;
		handler = IT_function ;
		
	} else if (Timer == TIM3) {
		
		NVIC_EnableIRQ(TIM3_IRQn) ;
		NVIC_SetPriority(TIM3_IRQn, Prio) ;
		handler = IT_function ;
		
	} else if (Timer == TIM4) {
		
		NVIC_EnableIRQ(TIM4_IRQn) ;
		NVIC_SetPriority(TIM4_IRQn, Prio) ;
		handler = IT_function ;
		
	}
	
	Timer->DIER |= TIM_DIER_UIE ;
	
	/*
	NVIC->IP[28] = Prio << 4 ;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_28 ;
	*/
}

void TIM1_UP_IRQHandler (void)
{
	TIM1->SR &= ~(TIM_SR_UIF) ;
	(*handler)() ;
}

void TIM2_IRQHandler (void)
{
	TIM2->SR &= ~(TIM_SR_UIF) ;
	(*handler)() ;
}

void TIM3_IRQHandler (void)
{
	TIM3->SR &= ~(TIM_SR_UIF) ;
	(*handler)() ;
}

void TIM4_IRQHandler (void)
{
	TIM4->SR &= ~(TIM_SR_UIF) ;
	(*handler)() ;
}

void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ){
	
		if (Channel == 1) {
			
			//Timer->CCMR1 |= TIM_CCMR1_OC1M; // 0x70
			Timer->CCMR1 |= 0x60;
			Timer->CCMR1 |= TIM_CCMR1_OC1PE;
			
		} else if (Channel == 2) {
			
			//Timer->CCMR1 |= TIM_CCMR1_OC2M; // 0x7000
			Timer->CCMR1 |= 0x6000;
			Timer->CCMR1 |= TIM_CCMR1_OC2PE;
			
		} else if (Channel == 3) {
			
			//Timer->CCMR2 |= TIM_CCMR2_OC3M; // 0x70
			Timer->CCMR2 |= 0x60;
			Timer->CCMR2 |= TIM_CCMR2_OC3PE;
			
		} else if (Channel == 4) {
			
			//Timer->CCMR2 |= TIM_CCMR2_OC4M; // 0x7000
			Timer->CCMR2 |= 0x6000;
			Timer->CCMR2 |= TIM_CCMR2_OC4PE;
			
		}
		Timer->EGR |= TIM_EGR_UG;
		Timer->CCER |= TIM_CCER_CC1E ;
		if ( Timer == TIM1){
			Timer->BDTR |= TIM_BDTR_MOE ; // moe
		}
	
}

void MyTimer_PWM_Cycle ( TIM_TypeDef * Timer , char Channel , float ratio )
{
	if (Channel == 1) {
		Timer->CCR1 = (int)(ratio * Timer->ARR);
	} else if (Channel == 2) {
		Timer->CCR2 = (int)(ratio * Timer->ARR);
	} else if (Channel == 3) {
		Timer->CCR3 = (int)(ratio * Timer->ARR);
	} else if (Channel == 4) {
		Timer->CCR4 = (int)(ratio * Timer->ARR);
	}
}


void MyTimer_PWM_ToGPIO(TIM_TypeDef * Timer , char Channel) {

	MyGPIO_Struct_TypeDef PWM;
	PWM.GPIO_Conf= AltOut_Ppull	 ;
	
	if (Timer == TIM1) {
		if (Channel == 1) {
			PWM.GPIO = GPIOA ;
			PWM.GPIO_Pin = 8 ;
		}
		else if (Channel == 2) {
			PWM.GPIO = GPIOA ;
			PWM.GPIO_Pin = 9 ;
		}
		else if (Channel == 3) {
		PWM.GPIO = GPIOA ;
			PWM.GPIO_Pin = 10 ;
		}
		else if (Channel == 4) {
			PWM.GPIO = GPIOA ;
			PWM.GPIO_Pin = 11 ;
		}
	
	
	}
	else if (Timer==TIM2) {
		if (Channel==1) {
			PWM.GPIO = GPIOA ;
			PWM.GPIO_Pin= 0 ;
		}
		else if (Channel==2) {
			PWM.GPIO = GPIOA ;
			PWM.GPIO_Pin= 1 ;
		}
		else if (Channel==3) {
			PWM.GPIO = GPIOA ;
			PWM.GPIO_Pin= 2 ;
		}
		else if (Channel==4) {
			PWM.GPIO = GPIOA ;
			PWM.GPIO_Pin= 3 ;
		}
	
	
	}
	else if (Timer==TIM3) {
		if (Channel==1) {
			PWM.GPIO = GPIOA ;
			PWM.GPIO_Pin= 6 ;
		}
		else if (Channel==2) {
			PWM.GPIO = GPIOA ;
			PWM.GPIO_Pin= 7 ;
		}
		else if (Channel==3) {
			PWM.GPIO = GPIOB ;
			PWM.GPIO_Pin= 0 ;
		}
		else if (Channel==4) {
			PWM.GPIO = GPIOB ;
			PWM.GPIO_Pin= 1 ;
		}
	
	
	}
	else if (Timer==TIM4) {
		if (Channel==1) {
			PWM.GPIO = GPIOB ;
			PWM.GPIO_Pin= 6 ;
		}
		else if (Channel==2) {
			PWM.GPIO = GPIOB ;
			PWM.GPIO_Pin= 7 ;
		}
		else if (Channel==3) {
			PWM.GPIO = GPIOB ;
			PWM.GPIO_Pin= 8 ;
		}
		else if (Channel==4) {
			PWM.GPIO = GPIOB ;
			PWM.GPIO_Pin= 9 ;
		}
	}
	MyGPIO_Init(&PWM) ;
}

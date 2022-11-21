
#include "UART.h"

// txe  rxne  rxneie
signed char Octet;
USART_TypeDef * UART;

//void (*handlerUART)(char);

void UART_Config(USART_TypeDef * UART){

	MyGPIO_Struct_TypeDef gpioRX, gpioTX; 
	
	gpioRX.GPIO_Conf = In_Floating; 
	gpioTX.GPIO_Conf = AltOut_Ppull;
	
	gpioRX.GPIO = GPIOC;
	gpioRX.GPIO_Pin = 8 ;
	gpioTX.GPIO = GPIOC;
	gpioTX.GPIO_Pin = 9 ;
	
	MyGPIO_Init(&gpioRX);
	MyGPIO_Init(&gpioTX);
	
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN; // enable clock
	
	
	UART->CR1 &= ~(0x1 << 12); // UART->CR1 = (10<<USART_CR1_M) ;
	
	UART->CR1 |= (0x1 <<13);  //UART->CR1 = USART_CR1_UE ;s
	
	// -> on met à 0 les bits STOP (12 et 13) de CR2
	UART->CR2 &= ~((0x1<< 12) | (0x1 << 13));
	
	UART->BRR = 3750;
	
	UART->CR1 |= (0x1 << 3);  //UART->CR1 = USART_CR1_TE; enable transmission
	
	UART->SR |= USART_SR_TC ;
	
	UART->CR1 |= USART_CR1_RE; //enable reception //UART->CR1 |= (0x1<<2) ;
	
	UART->CR1 |= USART_CR1_RXNEIE ;
	// generate interuption USART_CR1 |= (1<<USART_CR1_RXNEIE);
	
	NVIC_EnableIRQ(USART3_IRQn);
	NVIC_SetPriority(USART3_IRQn, 10);
}




void USART3_IRQHandler(){

		Octet=(USART3->DR) ;
		USART3->SR &= ~USART_SR_RXNE; // rxne = 0

}

signed char UART_getOctet(void) {
	return Octet;
}

  





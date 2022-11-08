#include "stm32f10x.h"
#include "Mytimer.h"
#include "MyGPIO.h"
#include "UART.h"

// txe  rxne  rxneie
int recu ;
//interruption dr=recu 

USART_TypeDef * UART;

void UART_Config(USART_TypeDef * UART){

	MyGPIO_Struct_TypeDef gpioRX, gpioTX; 
	
	gpioRX.GPIO_Conf = AltOut_Ppull;
	gpioTX.GPIO_Conf = In_Floating;
	
	gpioRX.GPIO = GPIOC;
	gpioRX.GPIO_Pin = 8 ;
	gpioTX.GPIO = GPIOC;
	gpioTX.GPIO_Pin = 9 ;
	
	MyGPIO_Init(&gpioRX);
	MyGPIO_Init(&gpioTX);
	
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN; // enable clock
	
	
	UART->CR1 &= ~(0x1 << 12); // UART->CR1 = (10<<USART_CR1_M) ;
	
	// -> on met à 0 les bits STOP (12 et 13) de CR2
	UART->CR2 &= ~((0x1<< 12) | (0x1 << 13));
	
	UART->BRR = 3750;
	
	// generate interuption USART_CR1 |= (1<<USART_CR1_RXNEIE);
	
	UART->CR1 = USART_CR1_RE; //enable reception
	UART->CR1 = USART_CR1_TE; //enable transmission

	UART->CR1 = USART_CR1_UE ; //UART->CR1 |= (0x1 <<13);
	
	//aller voir les fonctionalites de TE (et pourquoi le mettre a 1)
	//pareil pour tc
	
}

/*
1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
2. Program the M bit in USART_CR1 to define the word length.
3. Program the number of stop bits in USART_CR2.
4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
place. Configure the DMA register as explained in multibuffer communication.
5. Select the desired baud rate = 50 using the USART_BRR register.
6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
for each data to be transmitted in case of single buffer.
8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
that the transmission of the last frame is complete. This is required for instance when
the USART is disabled or enters the Halt mode to avoid corrupting the last
transmission.*/

#include "MyGPIO.h"

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) {
	// On active l'horloge du GPIO
	if (GPIOStructPtr->GPIO == GPIOA) {
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ;
	} else if (GPIOStructPtr->GPIO == GPIOB) {
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ;
	} else if (GPIOStructPtr->GPIO == GPIOC) {
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ;
	} /* else if (GPIOStructPtr->GPIO == GPIOD) {
			RCC->APB2ENR |= RCC_APB2ENR_IOPDEN ;
	} else if (GPIOStructPtr->GPIO == GPIOE) {
			RCC->APB2ENR |= RCC_APB2ENR_IOPEEN ;
	} */
	
	// On change le mode du GPIO
	if (GPIOStructPtr->GPIO_Pin < 8) { // Pins 0 a 7
		
		if (GPIOStructPtr->GPIO_Conf == In_PullDown) {
			GPIOStructPtr->GPIO->CRL &= ~(0xf) << (4*GPIOStructPtr->GPIO_Pin) ;
			GPIOStructPtr->GPIO->CRL |= GPIOStructPtr->GPIO_Conf << (4*GPIOStructPtr->GPIO_Pin) ;
			GPIOStructPtr->GPIO->ODR &= ~(1 << GPIOStructPtr->GPIO_Pin) ;
		} else if (GPIOStructPtr->GPIO_Conf == In_PullUp) {
			GPIOStructPtr->GPIO->CRL &= ~(0xf) << (4*GPIOStructPtr->GPIO_Pin) ;
			GPIOStructPtr->GPIO->CRL |= In_PullDown << (4*GPIOStructPtr->GPIO_Pin) ;
			GPIOStructPtr->GPIO->ODR |= 1 << GPIOStructPtr->GPIO_Pin ;
		} else {
			GPIOStructPtr->GPIO->CRL &= ~(0xf) << (4*GPIOStructPtr->GPIO_Pin) ;
			GPIOStructPtr->GPIO->CRL |= GPIOStructPtr->GPIO_Conf << (4*GPIOStructPtr->GPIO_Pin) ;
		}
		
	} else { // Pins 8 a 15
		
		if (GPIOStructPtr->GPIO_Conf == In_PullDown) {
			GPIOStructPtr->GPIO->CRH &= ~(0xf) << (4*GPIOStructPtr->GPIO_Pin) ;
			GPIOStructPtr->GPIO->CRH |= GPIOStructPtr->GPIO_Conf << (4*(GPIOStructPtr->GPIO_Pin - 8)) ;
			GPIOStructPtr->GPIO->ODR &= ~(1 << GPIOStructPtr->GPIO_Pin) ;
		} else if (GPIOStructPtr->GPIO_Conf == In_PullUp) {
			GPIOStructPtr->GPIO->CRH &= ~(0xf) << (4*(GPIOStructPtr->GPIO_Pin - 8)) ;
			GPIOStructPtr->GPIO->CRH |= In_PullDown << (4*(GPIOStructPtr->GPIO_Pin - 8)) ;
			GPIOStructPtr->GPIO->ODR |= 1 << GPIOStructPtr->GPIO_Pin ;
		} else {
			GPIOStructPtr->GPIO->CRH &= ~(0xf) << (4*GPIOStructPtr->GPIO_Pin) ;
			GPIOStructPtr->GPIO->CRH |= GPIOStructPtr->GPIO_Conf << (4*(GPIOStructPtr->GPIO_Pin - 8)) ;
		}
	}
	
}
int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) { // renvoie 0 ou autre chose different de 0
	return (~GPIO->IDR & (1<<GPIO_Pin)) >> GPIO_Pin ;
}
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR |= 1 << GPIO_Pin ;
}
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR &= ~(1 << GPIO_Pin) ;
}
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR ^= 1 << GPIO_Pin ;
}

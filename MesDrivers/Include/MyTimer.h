#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"
typedef struct
{
TIM_TypeDef * Timer ; // TIM1 � TIM4
unsigned short ARR ;
unsigned short PSC ;
} MyTimer_Struct_TypeDef ;
/*
*****************************************************************************************
* @brief
* @param -> Param�tre sous forme d � une structure ( son adresse ) contenant les
informations de base
* @Note -> Fonction � lancer syst�matiquement avant d�aller plus en d�tail dans les
conf plus fines (PWM, codeur inc...)
*************************************************************************************************
*/
void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * TimerSet ) ;
#define MyTimer_Base_Start(Timer) (Timer->CR1|=TIM_CR1_CEN)
#define MyTimer_Base_Stop(Timer) (Timer->CR1&=~TIM_CR1_CEN)

/*
**************************************************************************************************
* @brief
* @param : - TIM_TypeDef * Timer : Timer concerne
- char Prio : de 0 a 15
* @Note : La fonction MyTimer_Base_Init doit avoir ete lancee au prealable
**************************************************************************************************
*/

void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio , void (*IT_function) (void) ) ;

/* *
* @brief
* @param . . . .
* @Note Active le channel sp�cifi� sur le timer sp�cifi�
* la gestion de la configuration I/O n�est pas faite dans cette fonction
* ni le r�glage de la p�riode de la PWM (ARR, PSC)
*/
void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ) ;
void MyTimer_PWM_Cycle ( TIM_TypeDef * Timer , char Channel , float ratio )  ;
void MyTimer_PWM_ToGPIO(TIM_TypeDef * Timer , char Channel) ;
void MyTimer_ConfigureIncrementalEncoder(void) ;

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> 16455d61396467b51de14ba31d185f509a174813

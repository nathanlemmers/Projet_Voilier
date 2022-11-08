#include "Ecoute.h"
#include "MyTimer.h"

//TODO : fichiers voiles.c/.h avec Ecoute_InitPWM() et  Ecoute_BorderEcoute(Girouette_GetAngle())
MyTimer_Struct_TypeDef Timer = {TIM2 , 59999 , 5} ;
	
void Ecoute_InitPWM()
{
	MyTimer_Base_Init (&Timer) ;
	MyTimer_PWM (Timer.Timer, 2) ;
	MyTimer_PWM_ToGPIO (Timer.Timer , 2) ;
	MyTimer_Base_Start (Timer.Timer) ;
}

void Ecoute_BorderEcoute(float angle)
{
	float ratio = angle/180. ;
	MyTimer_PWM_Cycle (Timer.Timer, 2, ratio) ;
}

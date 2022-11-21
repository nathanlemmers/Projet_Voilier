#include "Girouette.h"
#include "MyTimer.h"
#include "MyGPIO.h"

void Girouette_Init()
{
	MyTimer_ConfigureIncrementalEncoder() ;
	
	while(MyGPIO_Read(GPIOA, 0) != 0 ) ;
	TIM4->CNT = 0 ;
	
}

float Girouette_GetAngle()
{
	float angle = TIM4->CNT ;
	angle = angle / 4. ;
	if (angle>180.)
		angle = 360. - angle ;
	return angle ;
}

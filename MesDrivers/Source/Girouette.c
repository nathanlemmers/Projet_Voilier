#include "Girouette.h"


float Girouette_GetAngle()
	{
	float angle = TIM4->CNT ;
	angle = angle / 4 ;
	if (angle>180)
		angle = 360 - angle ;
	return angle ;
}


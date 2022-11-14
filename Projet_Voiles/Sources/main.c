
#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "Voiles.h"
#include "Accelerometre.h"


int main (void)
{
	
	Voiles_Init() ;
	
	while (1) {
		Voiles_Update() ;
	}
}


#include "stm32f10x.h"
#include "Voiles.h"

int main (void)
{
	
	Voiles_Init() ;
	
	while (1) {
		Voiles_Update() ;
	}
}

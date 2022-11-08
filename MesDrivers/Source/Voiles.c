#include "Voiles.h"

void Voiles_Init()
{
	Girouette_Init();
	Ecoute_InitPWM();
}

void Voiles_Update()
{
	// min servo pour girouette a 45° et max a 77°32
	Ecoute_BorderEcoute(45. + (32./180.) * Girouette_GetAngle());
}

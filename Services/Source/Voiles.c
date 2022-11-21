#include "Voiles.h"
#include "Girouette.h"
#include "Ecoute.h"
#include "Accelerometre.h"

void Voiles_Init()
{
	Girouette_Init() ;
	Ecoute_InitPWM() ;
	Accelerometre_Init() ;
}

void Voiles_Update()
{
	// min servo pour girouette a 45° et max a 77°32
	if (!Accelerometre_Flag()) {
		Ecoute_BorderEcoute(45. + (32./180.) * Girouette_GetAngle()) ;
	} else {
		Ecoute_BorderEcoute(45.) ;
	}
}

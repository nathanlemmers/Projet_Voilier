#include "Plateau.h" 
#include "MyGPIO.h"
#include "MyTimer.h"

int sens_horaire = 1 ;
int sens_anti_horaire = 0;
short vitesse ;

MyTimer_Struct_TypeDef PlateauTimer;
MyGPIO_Struct_TypeDef PlateauGPIO ;


void Plateau_set_sens(int sens){
	if (sens == 0) {
		MyGPIO_Set(PlateauGPIO.GPIO, PlateauGPIO.GPIO_Pin);
	}
	else if(sens == 1) {
		MyGPIO_Reset(PlateauGPIO.GPIO, PlateauGPIO.GPIO_Pin);
	}
}

void Plateau_set_vitesse(short speed){
	if (speed > 128 ){
		Plateau_set_sens(sens_anti_horaire);
		vitesse = (256 - speed)*100/128 ;
	}
	else if (speed < 128 ){
		Plateau_set_sens(sens_horaire);
		vitesse = speed*100/128 ;
	}
}


void Plateau_init(void){
	PlateauTimer.Timer = TIM3 ;
	PlateauTimer.PSC = 16;
	PlateauTimer.ARR = 224;
	
	MyTimer_Base_Init(&PlateauTimer);
	MyTimer_Base_Start(PlateauTimer.Timer);
	
	MyTimer_PWM(PlateauTimer.Timer, 2);
	MyTimer_PWM_Cycle(PlateauTimer.Timer, 2, 0);
	
	PlateauGPIO.GPIO = GPIOC;
	PlateauGPIO.GPIO_Conf = Out_Ppull ;
	PlateauGPIO.GPIO_Pin = 14;
	MyGPIO_Init(&PlateauGPIO);
	
	Plateau_set_sens(sens_anti_horaire);
}


void Plateau_Tourner(void){
MyTimer_PWM_Cycle(PlateauTimer.Timer, 2, vitesse);
}

void Plateau_Arret(void){
MyTimer_PWM_Cycle(PlateauTimer.Timer, 2, 0);
}



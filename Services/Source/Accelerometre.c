#include "Accelerometre.h"
#include "MySPI.h"

void Accelerometre_Init()
{
	char byte ;
	
	// Init du SPI
	MySPI_Init(SPI1) ;
	// MySPI_Init(SPI2) ;
	MySPI_Set_NSS() ;
	
	// Config registre POWER_CTL (0x2D)
	MySPI_Clear_NSS() ;
	byte = 0x2D ;
	MySPI_Send(byte) ;
	byte = 0x8 ; // 0b00001000
	MySPI_Send(byte) ;
	MySPI_Set_NSS() ;
	
	// Config registre BW_RATE (0x2C)
	MySPI_Clear_NSS() ;
	byte =  0x2C ;
	MySPI_Send(byte) ;
	byte = 0xA ; // 100 Hz
	MySPI_Send(byte) ;
	MySPI_Set_NSS() ;
	
	// Config registre DATA_FORMAT (0x31)
	MySPI_Clear_NSS() ;
	byte = 0x31 ;
	MySPI_Send(byte) ;
	byte = 0xB ; // 0b00001011
	MySPI_Send(byte) ;
	MySPI_Set_NSS() ;
}

int Accelerometre_Flag()
{
	char byte ;
	char values[4] ;
	int i ;
	short Y, Z ;
	
	MySPI_Clear_NSS() ;
	byte = (3 << 6) + 0x34 ; // 0b11 110010
	MySPI_Send(byte) ;
	for (i = 0 ; i < 4 ; i++)
		values[i] = MySPI_Read() ;
	MySPI_Set_NSS() ;
	
	Y = values[0] + (values[1] << 8) ;
	Z = values[2] + (values[3] << 8) ;
	
	if (Y < 0)
		Y = -Y ;
	
	return Y > Z ;
}

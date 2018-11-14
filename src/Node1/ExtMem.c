/*
 * ExtMem.c
 *
 
 */ 


#include "ExtMem.h"



void ExtMemInit(void)
{
	
	EMCUCR |= (1<<SRW11) | (0<<SRW10);
	MCUCR |= (1<<SRE);
	//SFIOR |= (1<<XMBK);
	
	SFIOR |= (1<<XMM2);
	//DDRA = 0xFF;
}
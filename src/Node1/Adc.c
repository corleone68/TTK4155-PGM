
#include "Adc.h"


void ADC_start(uint8_t channel)
{
	volatile char *ext_adc= (char *) 0x1400; // volatile--cannot be changed by software, for compiler
	
	
	if(channel == 1) *ext_adc = 0b00000100;
	else if(channel == 2) *ext_adc = 0b00000101;
	else if(channel == 3) *ext_adc = 0b00000110;
	else if(channel == 4) *ext_adc = 0b00000111;
	
}


uint8_t ADC_read(void)
{
	
	volatile char *ext_adc= (char *) 0x1400; // volatile--cannot be changed by software, for compiler
	
	return *ext_adc;	
}


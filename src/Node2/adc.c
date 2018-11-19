#include <avr/io.h>
#include "adc.h"


void initADC(void){
	ADMUX	|= (1 << REFS0); //reference voltage on AVCC 
	ADCSRA	|= (1 << ADPS2)|(1 << ADPS1); //ADC clock prescaler 64
	ADCSRA	|= (1 << ADEN); //enable ADC
    DDRF &= ~(1 << PF0); //set as A0 as input
}

uint16_t analogRead(uint8_t ch){
	
	ADMUX = (ADMUX & 0xF0) | (ch & 0x0F);//set channel
	ADCSRA |= (1<<ADSC); //start ADC conversion
	loop_until_bit_is_clear(ADCSRA,ADCS); //wait until done
	return ADC;
}

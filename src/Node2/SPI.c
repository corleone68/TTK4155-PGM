#include <avr/io.h>
#include "SPI.h"

void initSPI(){

	DDRB |= (1<<DDB0)|(1<< DDB7)|(1<<DDB1)|(1<<DDB2); // Set MOSI, SCK and SS output, all others input 
	SPCR |= (1<<MSTR)|(1<<SPR0)|(1<<SPE); // Enable Master, set clock rate fck/16 and enable SPI
	//SPCR = (1 << SPIE); //interrupt enable
	
	PORTB |= (1 << PB7); //Slave Select high, SPI Gabor
	PORTB |= (1 << PB0); //SPI Gabor
}


void transmitSPI(uint8_t data){

    SPDR = data; // starts sending
    loop_until_bit_is_set(SPSR,SPIF);
	 //waits until done
}

uint8_t receiveSPI(uint8_t data){
    SPDR = data; // starts sending
    loop_until_bit_is_set(SPSR,SPIF);
	return SPDR; //waits until done //return data register
}

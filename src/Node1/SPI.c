


#include "SPI.h"
#include "USART.h"
#include <avr/io.h>

void initSPI(void){


	SPCR = (1 << SPE)|(1 << MSTR)|(1 << SPR0);

	// Set MOSI, SCK and SS output
	DDRB = (1 << DDB5)|(1 << DDB7)|(1 << DDB4);
	printf("SPI init succesfull \n");
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

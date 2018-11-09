

#include <avr/io.h>
#include "SPI.h"
#include "MCP2515.h"
#include "CAN.h"
#include "USART.h"


void initSPI(void){

	/*DDR_SPI |= (1 << SS); // set SS output
	//PORTB |= (1 << SS);
	DDR_SPI  |= (1 << MOSI); // output on MOSI
	DDR_SPI  |= (1 << SCK); //output on SCK
	DDR_SPI  &= ~(1 << MISO); //input on MISO
	DDR_SPI |= (1 << SPI_SS); 
	PORTB |= (1<<DDB3); // Set pullup for MISO
	SPCR |= (1 << SPR0);  // clkdiv 16
	SPCR |= (1 << MSTR);  // clockmaster
	//SPCR |= (1 << CPHA);  //device set up on the leading edge
	SPCR |= (1 << SPE); //enable */
	
	DDRB |= (1 << DDB2) | (1 << DDB1) | (1 << DDB7) | (1 << DDB0);
	
	SPCR = (1 << SPR0) | (1 << SPE) | (1 << MSTR) | (1 << SPIE);
	
	PORTB |= (1 << PB7); //Slave Select high
	PORTB |= (1 << PB0);

	
	//printf("SPI init succesfull node 2 \n");
	
}

void transmitSPI(uint8_t data){

	SPDR = data; // starts sending
	loop_until_bit_is_set(SPSR,SPIF);
	//waits until done
}

uint8_t receiveSPI(uint8_t data){
	SPDR = data; // starts sending
	//loop_until_bit_is_set(SPSR,SPIF);
	while(!(SPSR & (1 << SPIF)));
	return SPDR; //waits until done //return data register
}



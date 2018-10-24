


#include "SPI.h"
#include "USART.h"
#include <avr/io.h>

void initSPI(void){

    DDR_SPI |= (1 << SS); // set SS output
    
    DDR_SPI  |= (1 << MOSI); // output on MOSI
    DDR_SPI  |= (1 << SCK); //output on SCK
    DDR_SPI  &= ~(1 << MISO); //input on MISO
    DDR_SPI |= (1 << CS);
    SPCR |= (1 << SPR0);  // clkdiv 16
    SPCR |= (1 << MSTR);  // clockmaster
    SPCR |= (1 << CPHA);  //device set up on the leading edge
	printf("SPI init succesfull");
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





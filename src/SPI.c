#include "SPI.h"
#include <avr/io.h>

void initSPI(void){

    DDRB |= (1 << DDB4); // set SS output
    SLAVE_DESELECT;    // start not selected
    
    DDRB  |= (1 << DDB5); // output on MOSI
    DDRB  |= (1 << DDB7); //output on SCK
    DDRB  |= (1 << DDB6); //output on MISO

    SPCR |= (1 << SPR0);  // clkdiv 8
    SPSR |= (1 << SPI2X); //clkdiv 8
    SPCR |= (1 << MSTR);  // clockmaster
    SPCR |= (1 << CPHA);  //device set up on the leading edge
    
    SPCR |= (1 << SPE); //enable
}

void transmitSPI(uint8_t data){

    SPDR = data; // starts sending
    loop_until_bit_is_set(SPSR,SPIF); //waits until done
}

uint8_t receiveSPI(void){
 transmitSPI(0);
 loop_until_bit_is_clear(SPSR, SPIF); //wait until transfer is completed 
    return SPDR; //return data register
}


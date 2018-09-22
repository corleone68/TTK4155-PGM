#include <avr/io.h>
#include "UART.h"
#include <util/setbaud.h>
#include <stdio.h>

void initUSART(void)
{
/* Set baud rate */
    /*UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    #if USE_2X
        UCSR0A |= (1 << U2X0);
    #else
        UCSR0A &= ~(1 << U2X0);
    #endif

    set_bit(UCSR0B,TXEN0);
    set_bit(UCSR0B,RXEN0);
    set_bit(UCSR0C,UCSZ01);
    set_bit(UCSR0C,UCSZ00);
   fdevopen(transmitByte, receiveByte);*/

    UBRR0H=0x00;
	UBRR0L=0x1F; // To set the Buad rate to 9600.. get value through above formulaF
	UCSR0B=(1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);
	UCSR0C=(1<<URSEL0) | (1<<UCSZ01) | (1<<UCSZ00) ;
	fdevopen(transmitByte, receiveByte);

}


void transmitByte(uint8_t data)
{
   loop_until_bit_is_set(UCSR0A,UDRE0) ;
   UDR0 = data;
}

uint8_t receiveByte(void)
{
    loop_until_bit_is_set(UCSR0A,RXC0);
    return UDR0;
}

void printString(const char myString[])
{
    uint8_t i = 0;
    while(myString[i])
    {
        transmitByte(myString[i]);
        i++;
    }
}

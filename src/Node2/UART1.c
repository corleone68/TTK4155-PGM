#include <avr/io.h>
#include "UART.h"
#include <stdio.h>

void initUART(void)
{

	UBRR0H = (unsigned char)(baud>>8); // Set baud rate
	UBRR0L = (unsigned char)baud;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Enabling receiver and transmitter
	UCSR0C = (1<<URSEL0) | (1<<UCSZ01) | (1<<UCSZ00) ; // set frame format
}


void transmitByte(uint8_t data)
{
   loop_until_bit_is_set(UCSR0A,UDRE0) ; // wait for empty transmit buffer
   UDR0 = data;
}

uint8_t receiveByte(void)
{
    loop_until_bit_is_set(UCSR0A,RXC0); // putting data into buffer and sending data
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

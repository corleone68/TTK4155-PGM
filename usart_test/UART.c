#include <avr/io.h>
#include "UART.h"
#include <stdio.h>

void initUSART( unsigned int ubrr )
{
/* Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);

fdevopen(&transmitByte, &receiveByte);
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

#include <avr/io.h>
#include "UART.h"
#include <util/setbaud.h>
#include <stdio.h>

void initUSART(void)
{
/* Set baud rate */
    UBRR0H = UBRRH_VALUE;
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

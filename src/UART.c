#include <avr/io.h>
#include "UART.h"
void initUSART( unsigned int ubrr )
{
/* Set baud rate */
UBRRH = (unsigned char)(ubrr>>8);
UBRRL = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSRB = (1<<RXEN)|(1<<TXEN);
/* Set frame format: 8data, 2stop bit */
UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}


void transmitByte(uint8_t data)
{
   loop_until_bit_is_set(UCSRA,UDRE) ;
   UDR = data;
}

uint8_t receiveByte(void)
{
    loop_until_bit_is_set(UCSRA,RXC);
    return UDR;
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

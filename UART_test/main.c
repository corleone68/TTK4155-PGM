/*
 */
#define F_CPU 4915200UL
#define BAUD 9600
//#define BRC 31
#include <avr/io.h>
#include <util/setbaud.h>
#include <util/delay.h>
#include "UART.h"

int main(void)
{

    initUSART();
    while(1)
    {
        PORTB = 0b00000001;
        printf("Hello this is a ..");

        printString("HELLO");
        transmitByte('8');
		_delay_ms(1000);
        PORTB = 0b00000000;
        _delay_ms(1000);
    }

    return 0;
}

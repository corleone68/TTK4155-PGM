/*
 */
#define F_CPU 4915200
#define BAUD 9600

#include <avr/io.h>
#include "UART.h"

int main(void)
{
    initUSART(9600);
    printString("USART is working!!");

    while(1)
    {
        ;
    }

    return 0;
}

/*
 */
 #define F_CPU 4915200UL
 #define BAUD 9600

#include <avr/io.h
#include "ADC.h"
#include "UART.h"
#include "SRAM.h"

int main(void)
{
    initUSART();
    init_ADC();
    // Insert code

    while(1){

        analogRead(joy_x);
       uint8_t value= readSRAM(ADC_ADDRESS);
        printf("%d",value);
    }


    return 0;
}

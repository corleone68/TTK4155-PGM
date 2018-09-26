 #define F_CPU 4915200UL
 #define BAUD 9600

#include <avr/io.h>
#include "ADC.h"
#include "UART.h"
#include "SRAM.h"
#include "joystick.h"
#include <util/setbaud.h>
#include <stdio.h>
#include <util/delay.h>
int main(void)
{
    initUSART();
    init_ADC();
    initSRAM();
    SRAM_test;
    while(1){

        uint8_t value = analogRead(joy_x);
        //transmitByte(value);

        printf("ADC value: %d", value);
        readJoystick();

        //transmitByte('8');
		//printf("Hello this is a ..");
		//uart_msg("8");
		//_delay_ms(1000);
    }


    return 0;
}

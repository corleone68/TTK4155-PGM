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
  
    Position val;
    while(1){

        uint8_t value = analogRead(joy_x);
        //transmitByte(value);
        
        printf("ADC value: %d", value);
        val = readJoystick();
        printf("x value is %d\n y value is %d\n", val -> x, val -> y);

        //transmitByte('8');
		//printf("Hello this is a ..");
		//uart_msg("8");
		//_delay_ms(1000);
    }


    return 0;
}

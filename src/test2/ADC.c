#ifndef F_CPU
    #define F_CPU 4915200
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"

uint8_t init_ADC(void)
{

    DDRE &= ~(1 << PE0); // set the interrupt
    return 0;
}


uint8_t analogRead(Device device)
{
    volatile uint8_t* ext_adc = (uint8_t*) 0x1400;

    switch(device){
          case joy_x:
                  *ext_adc = 0b00000100; //Single-ended MUX mode
                  break;
          case joy_y:
                  *ext_adc = 0b00000101;
                  break;
          case slider_r:
                  *ext_adc = 0b00000110;
                  break;
          case slider_l:
                  *ext_adc = 0b00000111;
                  break;
          default:
                  return(0);
    }
     loop_until_bit_is_clear(PINE,PE0); //When the interrupt is low we can read the data               }

    _delay_us(100);
    return *ext_adc;
}



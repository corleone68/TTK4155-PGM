 #define F_CPU 4915200UL

#include <avr/io.h>
#include "ADC.h"
#include "joystick.h"
#include <stdio.h>
#include <util/delay.h>
#include <math.h>

int map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

struct pos Joy_pos;
struct pos Slid_pos;
struct pos percentage;

void initJoystick(void)
{
	
	DDRB &= ~(1 << PB2);
	PORTB &= (1 << PB2);
}

struct pos readJoystick(void)
{
    Joy_pos.x = analogRead(joy_x);
    _delay_ms(10);
    Joy_pos.y = analogRead(joy_y);
    return Joy_pos;
}

struct pos joyPosition(void)
{
    struct pos current_pos = readJoystick();
    percentage.x = map(current_pos.x,0,255,-100,100);
    percentage.y = map(current_pos.y,0,255,-100,100);
    return percentage;
}

Direction joyDirection(void)
{
    struct pos current_pos = joyPosition();
    
    if((abs(current_pos.x) < 20 )&& (abs(current_pos.y) < 20))
       {
             return(NEUTRAL);
       }
    else if ((abs(current_pos.x)) > (abs(current_pos.y)))
    {
            if(current_pos.x > 20) 
                {
                   return(RIGHT);
                }
            else 
                {
                    return(LEFT);
                }
    }

    else if ((abs(current_pos.x)) < (abs(current_pos.y)))
        {
            if(current_pos.y > 20)
                {
                    return(UP);
                }
            else
                {
                return(DOWN);
                }
        }
}

uint8_t readButton(void)
{
    
	return (PINB & (1 << PB2)) == 0;
}



/*
 * Joystick.c
 *
 */ 
#include "joystick.h"
#include "ADC.h"
#include "stdlib.h"
#define F_CPU 4915200
#include "util/delay.h"
#define TRESHOLD 20
void calibrateJoystick(void)
{
		
		
		x_ref = analogRead(joy_x);
		
		
	
		y_ref = analogRead(joy_y);
}

void  readJoystick(struct joystickOutput *Out)
{
	
	
	
	Out-> joyPos.x = (analogRead(joy_x)-x_ref)*100/(255- x_ref);
	

	
	Out-> joyPos.x = (analogRead(joy_y)- y_ref)*100/(255- y_ref);
	
	
		if(Out -> joyPos.x >100) 
                Out -> joyPos.x = 100;
		else if(Out -> joyPos.x <-100) 
                Out -> joyPos.x = -100;
		if(Out -> joyPos.y >100)
                Out -> joyPos.y = 100;
		else if(Out -> joyPos.y  <-100)
                Out -> joyPos.y = -100;
	
	
	
	
	
	if (    abs(Out-> joyPos.x) <TRESHOLD) 
        Out-> joyDirection = NEUTRAL;
	else if ( Out-> joyPos.x >TRESHOLD)
        Out-> joyDirection = UP;
	else if ( Out-> joyPos.x <-TRESHOLD)
        Out-> joyDirection = DOWN;
	
	if (Out-> joyDirection == NEUTRAL)
	{
		if  (  Out->joyPos.y >TRESHOLD) 
            Out-> joyDirection = RIGHT;
		else if (  Out-> joyPos.y <-TRESHOLD)
            Out-> joyDirection = LEFT;
		
	}
	
}

uint8_t readSlider(uint8_t direction)
{
    
	if(direction == LEFT){
       value = analogRead(slider_l);
       return(value);
     } 	
    
	else 
       {
            value = analogRead(slider_r);
            return value;
        } 

}

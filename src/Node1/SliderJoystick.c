
#include "SliderJoystick.h"
#include "Adc.h"
#include "stdlib.h"
#define F_CPU 4915200
#include "util/delay.h"
#define TRESHOLD 12

#define bit_is_set(sfr, bit)  ((_SFR_BYTE(sfr)& _BV(bit)))


void JoystickCalibrate(void)
{
		ADC_start(3);
		_delay_us(60);
		//while(ADC_DONE_PIN & ADC_DONE);
		
		X_Neutral = ADC_read();
		//X_Neutral = 128;
		
		ADC_start(4);
		_delay_us(60);
		//while(ADC_DONE_PIN & ADC_DONE);
		Y_Neutral = ADC_read();
}

void JoystickRead(struct JoystickOutput *Out)
{
	
	ADC_start(3);
	_delay_us(60);
	//while(ADC_DONE_PIN & ADC_DONE);
	
	Out->JoyAnalogOut.X_axis = (ADC_read()-X_Neutral)*100/(255-X_Neutral);
	

	ADC_start(4);
	_delay_us(60);
	//while(ADC_DONE_PIN & ADC_DONE);
	Out->JoyAnalogOut.Y_axis = (ADC_read()-Y_Neutral)*100/(255-Y_Neutral);
	
	
		if(Out ->JoyAnalogOut.X_axis >100) Out ->JoyAnalogOut.X_axis = 100;
		else if(Out ->JoyAnalogOut.X_axis <-100) Out ->JoyAnalogOut.X_axis = -100;
		if(Out ->JoyAnalogOut.Y_axis >100) Out ->JoyAnalogOut.Y_axis = 100;
		else if(Out ->JoyAnalogOut.Y_axis <-100) Out ->JoyAnalogOut.Y_axis = -100;
	
	
	
	if (    abs(Out->JoyAnalogOut.X_axis) <TRESHOLD) Out->JoystickDigitalOut = NEUTRAL;
	else if ( Out->JoyAnalogOut.X_axis >TRESHOLD) Out->JoystickDigitalOut = UP;
	else if ( Out->JoyAnalogOut.X_axis <-TRESHOLD) Out->JoystickDigitalOut = DOWN;
	
	if (Out->JoystickDigitalOut == NEUTRAL)
	{
		if  (  Out->JoyAnalogOut.Y_axis >TRESHOLD) Out->JoystickDigitalOut = RIGHT;
		else if (  Out->JoyAnalogOut.Y_axis <-TRESHOLD) Out->JoystickDigitalOut = LEFT;
		
	}
	
}

uint8_t SliderRead(uint8_t Choice)
{
	if(Choice == LEFT)	ADC_start(1);
	else ADC_start(2);
	_delay_us(40);
	//while(ADC_DONE_PIN & ADC_DONE);
	
	return	ADC_read();

}

uint8_t read_left_Button(void)
	{
		if (bit_is_clear(PINB, PB2))
		{
			return(1);
		}
		else
		return 0;
	}
	
uint8_t read_right_Button(void)
	{
		if (bit_is_clear(PINB, PB3))
		{
			return(1);
		}
		else
		return 0;
	}
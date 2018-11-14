#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


// Headers

#define F_CPU 16000000
#include <util/delay.h>


#include "USART.h"
//#include "USART.c"
#include "CAN.h"
//#include "CAN.c"
#include "SPI.h"
//#include "SPI.c"
#include "MCP2515.h"
//#include "MCP2515.c"
#include "PWM.h"
#include "adc.h"
#include "ir.h"
#include "TWI_Master.h"
#include "motor.h"
//#include "motor.c"
#include "dac.h"
#include "solenoid.h"
#include "PID.h"



int8_t solenoid, x_axis, y_axis, right_slider, left_slider, left_button, right_button, game_mode, settings;
int servo_angle;

int main(void)
{
	
	USART_Init(MY_UBRR);
	fdevopen(&USART_Transmit, 0);
	
	adc_init();
	DAC_init();
	//sei();
	TWI_Master_Initialise();
	motor_init();
	PID_init();
	servo_init();
	solenoid_init();
	
	
	CAN_init(MODE_NORMAL);
	CAN_message receive;
	CAN_message send = {.id = 2, .length = 2, .data[0] = -200};
		
	//DAC_init();
	
	
	
	//DAC_write(0x52);
	
	
	while(1){
		_delay_ms(10);
		//DAC_write(100);
		//motor_set_speed(100);
		
		//......get values from node 1
		//_delay_ms(100);
		
		if (CAN_receive(&receive)){
			x_axis = receive.data[0];
			y_axis = receive.data[1];
			left_slider = receive.data[2];
			right_slider = receive.data[3];
			left_button = receive.data[4];
			right_button = receive.data[5];
			game_mode = receive.data[6];
			settings = receive.data[7];
			servo_set_angle(x_axis);
			motor_set_speed(y_axis);
			//DAC_write(100);
			
			
			printf("X_axis %d \n", x_axis);
			printf("Y_axis %d \n", y_axis);
			printf("Left slider %d \n", left_slider);
			printf("Right slider %d \n", right_slider);
			printf("left button %d \n", left_button);
			printf("right button %d \n", right_button);
			printf("game mode %d \n", game_mode);
			printf(" \n");
			
			}
			
		
		send.data[0] = 5;
		
		
		
		/*
		
		switch (game_mode){
			case 0:
				// menu
			break;
			
			case 1:
				PID_calibrate();
				send.data[0] = 1; // calibration done flag
			break;
			
			case 2:
				PID(right_slider);
				servo_set_angle(x_axis);
				send.data[1] = ir_get();
			break;
		
		}
		*/
		CAN_message_send(&send);
		
	}
	
}
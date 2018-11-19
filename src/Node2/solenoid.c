#include <avr/io.h>
#include <util/delay.h>
#include "solenoid.h"

//	Initilization of solenoid

void init_solenoid(){
	
	// Set solenoid as output
	DDRL	|= (1 << DDL0);		
	PORTL	|= (1 << PL0);		
}



//	Solenoid Single-shot									

void trigger_solenoid(int button_pressed, int device_fired){
	if (button_pressed == 1 || device_fired == 0) {
		PORTL &=~(1 << PL0);
	} else {
		PORTL |= (1 << PL0);
	}
}



//	Solenoid Automatic

void switch_solenoid(int button_pressed, int device_fired){
	if (button_pressed == 1 || device_fired == 0){
		PORTL &=~(1 << PL0);
		_delay_ms(40);
		PORTL |= (1 << PL0);
		_delay_ms(40);
	}
}

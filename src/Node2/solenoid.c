#include <avr/io.h>
#include <util/delay.h>
#include "solenoid.h"

//	Initilization of solenoid									*

void solenoid_init(){
	
	// Set solenoid as output
	DDRL	|= (1 << DDL0);		
	PORTL	|= (1 << PL0);		
}



//	Solenoid Single-shot										*

void solenoid_trigger(int button_pressed, int device_fired){
	if (button_pushed == 1 || gun_fired == 0) {
		PORTL &=~(1 << PL0);
	} else {
		PORTL |= (1 << PL0);
	}
}



//	Solenoid Automatic

void solenoid_toggle(int button_pressed, int device_fired){
	if (button_pushed == 1 || gun_fired == 0){
		PORTL &=~(1 << PL0);
		_delay_ms(40);
		PORTL |= (1 << PL0);
		_delay_ms(40);
	}
}

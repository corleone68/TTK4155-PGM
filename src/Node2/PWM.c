#include <avr/io.h>
#include <avr/interrupt.h>
#include "PWM.h"

void initializeServo(void){
	
	TCCR1A = (1<<COM1B1)|(1<<WGM11)|(1<<COM3B1); //set Fast-PWM
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS11);
	DDRB |= (1<<PB6); // set as output
	ICR1 = 40000; //top value
	OCR1B = 3000; //trigger value
	
	

void setAngle(int pos) {
	

	int16_t angle = (((-pos+100)*12)+1800);
	
	if (angle >= 4200) {
		OCR1B = 4200;
		} 
	else if (angle >= 1800) {
		OCR1B = 1800;
		} 
	else if ((angle >= 2850) && (angle <= 3400)) {
		OCR1B = 3000;
		} 
	else {
		OCR1B = angle;
	}
}

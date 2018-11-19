
#include "motor.h"



void initMotor(){
	
	DDRH |= (1 << PH4); // Enable motor
	
	DDRH |= (1 << PH5); // set encoder enable to out
	
	DDRH |= (1 << PH1); // Set direction pin to output
	
	DDRH |= (1 << PH5); //PB5 // Enable control for output enable. Remember: active low - !OE
	
	DDRH |= (1 << PH3); // Enable control for selection pin: SEL
	
	// Enable control for Reset pin: RST
	DDRH |= (1 << PH6);
	PORTH |= (1 << PH4);
	PORTH |= (1 << PH6);
	
	PORTH &= ~(1 << PH5); //Set !OE low to enable output of encoder.
	
	
}


void setDirection(motor_direction_t direction){
	switch (direction){
		case(LEFT): 
			PORTH &= ~(1 << PH1);
			break;
		case(RIGHT): 
			PORTH |= (1 << PH1);
			break;
	}
}

void setSpeed(int8_t speed){
	if(speed > 0){ //Limits speed based on direction
		setDirection(RIGHT);
		DAC_write(speed);
		
	} else{
		setDirection(LEFT);
		DAC_write(-speed);
	}
}

void PIDcontroller(uint8_t speed){
		DAC_write(speed);
}

void resetEncoder() { 
	PORTH &= ~(1 << PH6); // Set active low reset
	_delay_us(200);
	PORTH |= (1 << PH6); // Finish reset
}

uint16_t readEncoder(void){

	PORTH &= ~(1 << PH3); //Set SEL low to get high byte
	_delay_us(20);
	
	uint8_t high = PINK; //Read LSB
	
	PORTH |= (1 << PH3); //Set SEL high to get low byte
	_delay_us(20);
	
	uint8_t low = PINK; //Read MSB
	
	uint16_t encoder_value =  (high << 8) | low;
	
	return encoder_value;
}


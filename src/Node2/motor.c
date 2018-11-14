
#include "motor.h"



void motor_init(){
	
	
	// Enable motor
	DDRH |= (1 << PH4);
	PORTH |= (1 << PH4);
	
	
	// Set direction pin to output
	DDRH |= (1 << PH1);
	
	// Enable control for output enable. Remember: active low - !OE
	DDRB |= (1 << PB5);
	
	// Enable control for selection pin: SEL
	DDRH |= (1 << PH3);
	
	// Enable control for Reset pin: RST
	DDRH |= (1 << PH6);

	// Reset encoder
	motor_reset_encoder();
	
	// Set data bits to input:
	DDRK = 0x00;
	
}


void motor_set_dir(motor_direction_t direction){
	switch (direction){
		case(LEFT): 
			PORTH &= ~(1 << PH1);
			break;
		case(RIGHT): 
			PORTH |= (1 << PH1);
			break;
	}
}

void motor_set_speed(int8_t speed){
	if(speed > 0){ //Limits speed based on direction
		motor_set_dir(RIGHT);
		DAC_write(speed);
		
	} else{
		motor_set_dir(LEFT);
		DAC_write(-speed);
	}
}

void motor_set_speed_PID(uint8_t speed){
		DAC_write(speed);
}

void motor_reset_encoder() { 
	PORTH &= ~(1 << PH6); // Set active low reset
	_delay_us(200);
	PORTH |= (1 << PH6); // Finish reset
}

int16_t motor_encoder_read(void){

	//Set !OE low to enable output of encoder.
	PORTH &= ~(1 << PH5);
	
	//Set SEL low to get high byte
	PORTH &= ~(1 << PH3);
	_delay_us(20);
	
	//Read LSB
	uint8_t high = PINK; 
	
	//Set SEL high to get low byte
	PORTH |= (1 << PH3);
	_delay_us(20);
	
	//Read MSB
	uint8_t low = PINK;

	//Set !OE high to disable output of encoder
	PORTH |= (1 << PH5);
	
	int16_t encoder_value = (int16_t) ( (high << 8) | low);
	
	return encoder_value;
}

motor_encoder_test(void){
	printf("Encoder: %d\n", motor_encoder_read());
}

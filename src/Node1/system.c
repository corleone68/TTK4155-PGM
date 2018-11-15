#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"
#include "SliderJoystick.h"
#include "Adc.h"
#include "menu.h"
#include "CAN.h"


//***************************************************************
//	System logic variables init									*
//***************************************************************
struct JoystickOutput Joy;

can_message send = {.id = 1, .length = 8, .data[0] = -100};
can_message receive;

int score_overflow_counter = 0;

uint8_t gamemode = 0;		// Menu:0 - Calibration:1 - Game 2
uint8_t settings;	// bit0:Firemode (auto | single) - bit1:Controlmode (Joystick|Gun)
int score_counter = 0;		// Gamepoints based on duration
uint16_t score_top = 0;			// Topscore this session
uint8_t IR_flag;	// Failstate for the game, ok:0 - game over:1
uint8_t cal_flag;

void scoretimer_init() {
	TCCR1B |= (1<<CS10);	// 16-bit timer with no prescaler
	TCNT1 = 0;
	TIMSK |= (1<<TOIE1);	// Timer overflow interrupt enable
}

void system_loop() {

	// Game escape
	if ((gamemode == 2) && (read_left_Button()==0)) { // Checks switch sw1 on malfunctionboard
		gamemode = 0;
		MENU_end_game();
		MENU_init();
		score_counter = 0;
	}
	// Game failstate
	if ((gamemode == 2) && (IR_flag == 1)) {
		MENU_end_game();
		MENU_init();
		gamemode = 0;
		score_counter = 0;
	}


	// Joystick position update
	JoystickRead(&Joy);
	

	switch (gamemode) {
		case 0: // Gamemode: Menu
			MENU_navigate(Joy.JoystickDigitalOut, &gamemode, &settings, &score_top, score_counter);
			
		break;
		
		case 1: // Gamemode: Calibration
			//settings_guncalibration();
		break;

		case 2: // Gamemode: Game
			MENU_game(score_counter);

		break;
	}
	
	// Update of CAN values for node 2
	send.data[0] = Joy.JoyAnalogOut.X_axis;
	send.data[1] = Joy.JoyAnalogOut.Y_axis;
	send.data[2] = SliderRead(LEFT);
	send.data[3] = SliderRead(RIGHT);
	send.data[4] = read_left_Button();
	send.data[5] = read_right_Button();
	send.data[6] = gamemode;
	send.data[7] = settings;
	//send.data[8] = (~(PINB) & (1 << PB0));
	can_message_send(&send);
	printf("X_axis %d \n", send.data[0]);
	printf("Y_axis %d \n", send.data[1]);
	printf("Left slider %d \n", send.data[2]);
	printf("Right slider %d \n", send.data[3]);
	printf("left button %d \n", send.data[4]);
	printf("right button %d \n", send.data[5]);
	printf("game mode %d \n", send.data[6]);
	printf("score %d \n", score_counter);
	printf(" \n");
	
	if (can_receive(&receive)){
		cal_flag = receive.data[0];
		printf("cal flag: %d \n", receive.data[0]);
		IR_flag = receive.data[1];
	}
	
	printf("cal flag: %d \n", cal_flag);
	printf("IR_flag: %d \n", IR_flag);
	
	
	//_delay_ms(100);
	
	
}

// Interrupt based score timer
ISR(TIMER1_OVF_vect) {
	if(gamemode == 2) {
		score_overflow_counter++;
		if (score_overflow_counter > 30) {
			score_counter++;
			score_overflow_counter = 0;
		}
	}
}







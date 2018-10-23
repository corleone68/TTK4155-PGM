/*
 * Joystick.h

 */ 




#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <avr/io.h>

enum {NEUTRAL,LEFT,RIGHT,UP,DOWN} position;

uint8_t x_ref;
uint8_t y_ref;
uint8_t value;

struct joystickPosition{
	int8_t x;
	int8_t y;
	};

struct sliderOutput{
	uint8_t Left;
	uint8_t Right;
};

struct joystickOutput {
	struct joystickPosition joyPos;
	uint8_t joyDirection;
};


void readJoystick(struct joystickOutput *Out);
void calibrateJoystick(void);

uint8_t readSlider(uint8_t direction);


#endif /* JOYSTICK_H_ */

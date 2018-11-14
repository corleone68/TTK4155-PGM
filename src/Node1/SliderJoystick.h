


#ifndef SLIDERJOYSTICK_H_
#define SLIDERJOYSTICK_H_

#include <avr/io.h>


#define ADC_DONE (1<<PD2)
#define ADC_DONE_PIN PIND


enum {NEUTRAL,LEFT,RIGHT,UP,DOWN} position;

uint8_t X_Neutral;
uint8_t Y_Neutral;

struct JoystickAnalogOutput{
	int8_t X_axis;
	int8_t Y_axis;
	};

struct SliderOutput{
	uint8_t Left;
	uint8_t Right;
};

struct JoystickOutput {
	struct JoystickAnalogOutput JoyAnalogOut;
	uint8_t JoystickDigitalOut;
};


void JoystickRead(struct JoystickOutput *Out);
void JoystickCalibrate(void);
uint8_t read_left_Button(void);
uint8_t read_right_Button(void);

uint8_t SliderRead(uint8_t Choice);



#endif /* JOYSTICK_H_ */
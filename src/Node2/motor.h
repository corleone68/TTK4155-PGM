
#ifndef MOTOR_H_
#define MOTOR_H_



#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "dac.h"

typedef enum {LEFT, RIGHT} motor_direction_t;

void initMotor();
void setDirection(motor_direction_t direction);
void setSpeed(int8_t speed);
void PIDcontroller(uint8_t speed);
void motor_move(int16_t rot_diff, uint8_t power);
uint16_t readEncoder(void);
void resetEncoder();





#endif 

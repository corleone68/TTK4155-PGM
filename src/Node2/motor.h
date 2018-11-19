
#ifndef MOTOR_H_
#define MOTOR_H_



#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "dac.h"

typedef enum {LEFT, RIGHT} dir;

void initMotor();
void setDirection(dir direction);
void setSpeed(int8_t speed);
void PIDcontroller(uint8_t speed);
uint16_t readEncoder(void);
void resetEncoder();

#endif 


#ifndef PID_H_
#define PID_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "motor.h"
#include "PID.h"
#define SampleTime 0.016

#define Kp 1
#define Ki 10
#define Kd 0.01


static volatile uint8_t timer_flag = 0;
static double integral = 0;
static int16_t prev_error = 0;
static int16_t position_max;




void initializePID(void);
void PID(uint8_t ref);
void calibratePosition(void);
ISR(TIMER2_OVF_vect);

#endif 

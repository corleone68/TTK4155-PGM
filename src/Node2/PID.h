
#ifndef PID_H_
#define PID_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "motor.h"
#include "PID.h"

//Tuned PID gains
#define Kp 1
#define Ki 10
#define Kd 0.01

#define dt 0.016

static int16_t pos_max;
static int16_t pos_min = 0;
static double integral = 0;
static int16_t prev_error = 0;

static volatile uint8_t timer_flag = 0;

void PID_init(void);
void PID(uint8_t pos_ref);
void PID_calibrate(void);
ISR(TIMER2_OVF_vect);

#endif /* PID_H_ */
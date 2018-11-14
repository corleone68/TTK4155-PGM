
#ifndef MOTOR_H_
#define MOTOR_H_



#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "dac.h"
//#include "CAN.h"

typedef enum {LEFT, RIGHT} motor_direction_t;

void motor_init();
void motor_set_dir(motor_direction_t direction);
void motor_set_speed(int8_t speed);
void motor_set_speed_PID(uint8_t speed);
void motor_move(int16_t rot_diff, uint8_t power);
int16_t motor_encoder_read(void);
void motor_reset_encoder();
void motor_encoder_test(void);




#endif /* MOTOR_H_ */

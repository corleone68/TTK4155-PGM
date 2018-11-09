#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


// Headers

#define F_CPU 16000000
#include <util/delay.h>


#include "USART.h"
#include "CAN.h"
#include "CAN.c"
#include "SPI.h"
#include "SPI.c"
#include "MCP2515.h"
#include "PWM.h"
#include "adc.h"
#include "IR.h"
#include "TWI_Master.h"
#include "motor.h"
#include "dac.h"
#include "solenoid.h"
#include "pi_controller.h"
#include "reg_pid.h"
#include "timer.h"


int main(void)
{
	
	USART_Init(MY_UBRR);
	fdevopen(&USART_Transmit, 0);
	
	motor_init();
}

#ifndef CAN_H_
#define CAN_H_

#include "MCP2515.h"
#include "SPI.h"
#include <avr/io.h>
#include <avr/interrupt.h>


typedef struct can_message{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
}can_message;

static volatile uint8_t CAN_int_flag = 0;
void can_init(uint8_t mode);
void can_message_send(can_message* msg);
uint8_t can_data_receive(can_message* msg);
ISR(INT0_vect);


#endif /* CAN_H_ */

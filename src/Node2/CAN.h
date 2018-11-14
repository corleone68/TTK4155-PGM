
#ifndef CAN_H_
#define CAN_H_

#include "MCP2515.h"
//#include "USART.h"
#include <avr/io.h>
#include <avr/interrupt.h>


typedef struct CAN_message{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
}CAN_message;

static volatile uint8_t CAN_int_flag = 0;
void CAN_init(uint8_t mode);
void CAN_message_send(CAN_message* msg);
uint8_t CAN_receive(CAN_message* msg);
ISR(INT2_vect);


#endif /* CAN_H_ */
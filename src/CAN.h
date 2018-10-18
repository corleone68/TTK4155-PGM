#ifndef __CAN_H
#define __CAN_H
#include <avr/io.h>
#include "SPI.h"
#include "MCP2515.h"

typedef struct can_message{
            unsigned int id;
            uint8_t length;
            uint8_t data[8];
}Can_message;
void can_init(uint8_t mode);
void can_message_send(Can_message* msg);
int can_transmit_complete();
int can_error();
void can_int_clear();
int flag = 0;
#endif

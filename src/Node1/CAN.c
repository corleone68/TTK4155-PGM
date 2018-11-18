
#include "CAN.h"

void can_init(uint8_t mode){
	mcp2515_init(mode);

	cli(); // Disable global interrupts

	DDRD &= ~(1<<PD2);

	GICR |= (1 << INT0); // interupt PIN 12

	EMCUCR |= 1<<ISC11 | 1<<ISC01;			// Both trigger inputs at falling edge
	EMCUCR &= ~(1<<ISC10);
	EMCUCR &= ~(1<<ISC00);



	sei(); // Enable global interrupts

}
void can_message_send(can_message* msg){

	mcp2515_write(MCP_TXB0SIDH, (msg->id) >> 3); // Set message ID high bits
	mcp2515_write(MCP_TXB0SIDL, (msg->id) << 5); // Set message ID low bits
	mcp2515_write(MCP_TXB0DLC, (msg->length)); // Set data length

	for (uint8_t i = 0; i < msg->length; i++){
		mcp2515_write(MCP_TXB0D0+i, msg->data[i]); // Set data bits
	}
	mcp2515_request_to_send(MCP_RTS_TX0); // Sends data to TX0 buffer
}

uint8_t can_data_receive(can_message* msg){
	if (CAN_int_flag){
		msg->id = (mcp2515_read(MCP_RXB0SIDH) << 3| mcp2515_read(MCP_RXB0SIDL) >> 5); // Combine to complete message ID

		uint8_t length = mcp2515_read(MCP_RXB0DLC); // Read message data length
		msg->length = length;


		for (uint8_t i = 0; i < msg->length; i++){
			msg->data[i] = mcp2515_read(MCP_RXB0D0+i);  // Read data bits
		}
		mcp2515_bit_modify(MCP_CANINTF,0x01,0x00); // Reset interrupt flag
		CAN_int_flag = 0;
		return 1;
	}
	return 0;
}


ISR(INT0_vect){
	CAN_int_flag = 1;
}

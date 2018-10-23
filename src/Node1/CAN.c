


#include <avr/io.h>
#include "SPI.h"
#include "MCP2515.h"
#include "CAN.h"
#include "USART.h"
#include <avr/interrupt.h>


void can_init(uint8_t mode)
{
    mcp2515_init(mode);
    mcp2515_bit_modify(MCP_CANINTE, RX0IE, RX0IE);
    mcp2515_bit_modify(MCP_RXB0CTRL,MCP_NOFILTER, MCP_NOFILTER);

    MCUCR |= (0 << ISC01) | (0 << ISC00);
    GICR |= (1 << INT0);
	printf("can init succesfull");
    
}




void can_message_send(Can_message* msg)
{  // Standard mode
   //if(can_transmit_complete())
   
   mcp2515_write(MCP_TXB0SIDH, (msg -> id) >> 3); 
   mcp2515_write(MCP_TXB0SIDL, (msg -> id) << 5);

   mcp2515_write(MCP_TXB0DLC, msg -> length & 0b00001111); 
   
   uint8_t i;
   for(i=0; i < (msg -> length); i++)
    {
        mcp2515_write(MCP_TXB0D0 + i, msg -> data[i]);
    } 
    mcp2515_request_to_send(MCP_RTS_TX0);
    
   
}

int can_transmit_complete()
{
    if((MCP_TXB0CTRL & (1 << TXREQ))) return 0;
    else 
        return 1;
}

int can_error()
{
    if((MCP_TXB0CTRL & (1 << TXERR))) return 1;
    if((MCP_TXB0CTRL & (1 << MLOA)))  return 2;
    
    return 0;
}


Can_message can_data_receive()
{
   Can_message msg;
   
    msg.id = (mcp2515_read(MCP_RXB0SIDH) << 3 | mcp2515_read(MCP_RXB0SIDL) >> 5);
    msg.length = mcp2515_read(MCP_RXB0DLC) & 0b00001111; 
    uint8_t i;
    for (i=0; i < msg.length; i++)
    {
        msg.data[i] = mcp2515_read(MCP_RXB0D0 + i);
    }
    return msg;
}

void can_int_clear()
{
    mcp2515_bit_modify(MCP_CANINTF,0x01,0x00);
}

Can_message can_receive()
{   Can_message message;
    if(flag == 1) 
    {
        message = can_data_receive();
        flag = 0;
        return message;
    }
}


ISR(INT0_vect)
{   
    uint8_t int_stat = mcp2515_read(MCP_CANINTF);
    if(int_stat & MCP_RX0IF)
    {
        flag = 1;
        can_int_clear();
    }
}


    



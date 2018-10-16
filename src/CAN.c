#include <avr/io.h>
#include "SPI.h"
#include "MCP2515.h"
#include "CAN.h"






void can_message_send(Can_message* msg)
{  // Standard mode
   mcp2515_write(MCP_TXB0SIDH, (msg -> id) >> 3); 
   mcp2515_write(MCP_TXB0SIDL, (msg -> id) << 5);

   mcp2515_write(TXB0DLC, msg -> length); 
   
   uint8_t i;
   for(i=0; i < (msg -> length); i++)
    {
        mcp2515_write(MCP_TXB0D0 + i, msg -> data[i]);
    } 
    mcp2515_request_to_send(MCP_RTS_TX0);
   
}

int can_transmit_complete()
{
    if((MCP_TXB0CTRL & (1 << TXREQ)) return 0;
    else 
        return 1;
}

int can_error()
{
    if((MCP_TXB0CTRL & (1 << TXERR)) return 1;
    if((MCP_TXB0CTRL & (1 << MLOA))  return 2;
    
    return 0;
}


Can_message can_data_receive()
{
   Can_message msg;
   
    msg.id = (mcp2515_read(MCP_RXBOSIDH) << 3 | mcp2515_read(MCP_RXB0SIDL) >> 5);
    msg.length = mcp2515_read(MCP_RXB0DLC) & 0b00001111; 
    uint8_t i;
    for (i=0; i < msg.length; i++)
    {
        msg.data[i] = mcp2515_read(MCP_RXB0D0 + i);
    }
    return msg;
}
    

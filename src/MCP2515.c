#include "MCP2515.h"

void mcp2515_init(uint8_t mode)
{
    uint8_t value;
    uint8_t mask = 0b011100000;
    initSPI();
    mcp2515_reset();
    mcp2515_bit_modify(MCP_CANCTRL,mask,mode); //ex. mcp2515_bit_modify(MCP_CANCTRL,mask, MODE_LOOPBACK);
    
}


uint8_t mcp2515_read(uint8_t address)
{
    uint8_t result;
    SLAVE_SELECT;
    transmitSPI(MCP_READ);
    transmitSPI(address);
    result = receiveSPI();
    SLAVE_DESELECT;
    return result;
}

void mcp2515_reset(void)
{
    SLAVE_SELECT; // Selecting the device
    transmitSPI(MCP_RESET); // Sending the RESET instruction byte
    SLAVE_DESELECT; // Deselecting the device
}

void mcp2515_write(uint8_t address, uint8_t data)
{
    SLAVE_SELECT;
    transmitSPI(MCP_WRITE);
    transmitSPI(address);
    transmitSPI(data);
    SLAVE_DESELECT;
}

void mcp2515_request_to_send(uint8_t mcp_rts_TXn)   //MCP_RTS_TX0, MCP_RTS_TX1,	MCP_RTS_TX2, MCP_RTS_ALL	
{
    SLAVE_SELECT;
    transmitSPI(mcp_rts_TXn);
    SLAVE_DESELECT;
} 

                                                  
void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
    SLAVE_SELECT;
    transmitSPI(MCP_BITMOD);
    transmitSPI(address);
    transmitSPI(mask);
    transmitSPI(data);
    SLAVE_DESELECT;
}

uint8_t mcp2515_read_status(void)
{
    uint8_t result;
    SLAVE_SELECT;
    transmitSPI(MCP_READ_STATUS);
    result = receiveSPI();
    SLAVE_DESELECT;
    return result;
    
}


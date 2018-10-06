#include <avr/io.h>

#define SLAVE_SELECT PORTB &= ~(1 << PB4)
#define SLAVE_DESELECT PORTB |= (1 << PB4)

void initSPI(void);
void SPI_MasterTransmit(uint8_t data);

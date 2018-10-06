#include <avr/io.h>

#define SLAVE_SELECT PORTB &= ~(1 << PB4)
#define SLAVE_DESELECT PORTB |= (1 << PB4)

void initSPI(void);
void transmitSPI(uint8_t data);
uint8_t receiveSPI(void);

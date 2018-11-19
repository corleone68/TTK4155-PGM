
#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

#include <avr/io.h>

#define SLAVE_SELECT PORTB &= ~(1 << PB7)
#define SLAVE_DESELECT PORTB |= (1 << PB7)

void initSPI(void);
void transmitSPI(uint8_t data);
uint8_t receiveSPI(uint8_t data);






#endif /* SPI_H_ */

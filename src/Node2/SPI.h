

#include <avr/io.h>
#define DDR_SPI DDRB
#define SS  PB0
#define SCK PB1
#define MOSI PB2
#define MISO PB3
#define CS PB7
#define SLAVE_SELECT PORTB &= ~(1 << PB7)
#define SLAVE_DESELECT PORTB |= (1 << PB7)

void initSPI(void);
void transmitSPI(uint8_t data);
uint8_t receiveSPI(uint8_t data);




#include <avr/io.h>

void adc_init(void);
uint16_t adc_read(uint8_t channel);
#define ADC_ADDRESS  0x1400
#define SRAM_ADDRESS  0x1800
#define OLED_ADDRESS  0x1000
#include <avr/io.h>


void initSRAM(void);
void SRAM_test(void);
uint8_t readSRAM(uint16_t address);

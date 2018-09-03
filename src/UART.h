#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while(!test_bit(reg,bit))
#define loop_until_bit_is_clear( reg, bit) while(test_bit(eg,bit))

#ifndef BAUD
    #define BAUD 9600
#endif // BAUD

#ifndef F_CPU
    #define F_CPU 4915200
#endif // F_CPU

#ifndef USART_h
    #define USART_h
#endif // USART

#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>

void initUSART( unsigned int ubrr );
void transmitByte(uint8_t data);
uint8_t receiveByte(void);
void printString(const char myString[]);

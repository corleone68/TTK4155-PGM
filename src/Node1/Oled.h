/*
 * oled.h
 *
 * Created: 16.09.2014 14:21:30
 *  Author: milorads
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <avr/io.h>

void OledWriteCommand(uint8_t command);
void OledWriteData(uint8_t data);

void OledInit(void);
void OledHome(void);
void OledGotoLine(uint8_t line);
void OledClearLine(uint8_t line);
void OledClearDisplay(void);
void OledGoto(uint8_t row,uint8_t column);
void OledPrintCharacter(char character);
void OledPrintString(char *string);

typedef struct {
	int row, col;
} oled_position_t;

#endif /* OLED_H_ */



#include "Oled.h"
#include "Char.h"
//#include "C:\Users\Peter\Documents\Atmel Studio\6.2\GccApplication1\fonts.h"


volatile char *oled_command = (char *) 0x1000;  // this automatically sets WR signal of the microcontroller to low!!! 
volatile char *oled_data = (char *) 0x1200;

	

void OledWriteCommand(uint8_t command)
{
	*oled_command = command;

}
void OledWriteData(uint8_t data)
{
	*oled_data = data;
}


void OledInit() {
	
	 OledWriteCommand(0xae); // display off
	 OledWriteCommand(0xa1); //segment remap
	 OledWriteCommand(0xda); //common pads hardware: alternative
	 OledWriteCommand(0x12);
	 OledWriteCommand(0xc8); //common
	 
	 OledWriteCommand(0xa8); //multiplex ration mode:63
	 OledWriteCommand(0x3f);
	 OledWriteCommand(0xd5); //display
	 
	 OledWriteCommand(0x80);
	 OledWriteCommand(0x81); //contrast control
	 OledWriteCommand(0x50);
	 OledWriteCommand(0xd9); //set pre-charge period
	 OledWriteCommand(0x21);
	 OledWriteCommand(0x20); //Set Memory Addressing Mode
	 OledWriteCommand(0x00); //horizontal addressing
	
	 
	 OledWriteCommand(0xdb); //VCOM deselect level mode
	 OledWriteCommand(0x30);
	 OledWriteCommand(0xad); //master configuration
	 OledWriteCommand(0x00);
	 OledWriteCommand(0xa4); //out follows RAM content
	 OledWriteCommand(0xa6); //set normal display
	
     OledWriteCommand(0xaf); // display on
}


void OledGoto(uint8_t row,uint8_t column){

	OledWriteCommand(0x21); //set column address range
	OledWriteCommand(column);  // from set
	OledWriteCommand(0x7F); //to max

	OledWriteCommand(0x22); //set row address range
	OledWriteCommand(row);  // from set
	OledWriteCommand(0x07); //to max
	
}


void OledHome(){
	OledGoto(0,0); 
}
void OledGotoLine(uint8_t line){
	OledGoto(line,0);
}
void OledClearLine(uint8_t line){
	int i;
	
	OledGotoLine(line);
	for(i=0;i<127;i++) OledWriteData(0x00);

}

void OledClearDisplay(){
	int i;
	OledHome();
	for(i=0;i<1024;i++) OledWriteData(0x00);
	
}



void OledPrintCharacter(char Character){
	
	
	char OneCharacter[5]; int i = 0;
	Convert(OneCharacter, Character);
	
	for (i = 0; i<5; i++)
	{
		OledWriteData(OneCharacter[i]);
	}
}


void OledPrintString(char *string){

	while(*string){
		OledPrintCharacter(*string);
		string++;
	}
}


void OLED_print_arrow(){
	OledWriteData(0x3E);
	OledWriteData(0x1C);
	OledWriteData(0x08);
}
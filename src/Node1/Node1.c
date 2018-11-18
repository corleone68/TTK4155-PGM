
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Headers
//#define bit_is_set(sfr, bit)  ((_SFR_BYTE(sfr)& _BV(bit)))
#define F_CPU 4915200
#include <util/delay.h>


#include "Adc.h"
#include "SRAMtest.c"
#include "SRAMtest.h"
#include "UART.h"
#include "ExtMem.h"
#include "Oled.h"
#include "Char.h"
#include "menu.h"
#include "joystick1.h"
#include "CAN.c"
#include "CAN.h"
#include "SPI.c"
#include "SPI.h"
#include "MCP2515.h"
#include "system.h"
#include "system.c"
//--- Proto Type Declaration ---//

//void uart_init(void);      //--- Usart Initialize


//--- Main Program ---//

int main()
{

	initUART(MY_UBRR);
	ExtMemInit();
	scoretimer_init();

	sei();

	//DDRE &= ~(1 << PE0);

	calibrateJoystick();


	//struct JoystickOutput Joy;


	OledInit();
	OledClearDisplay();
	OledHome();
	MENU_init();


	initSPI();

	can_init(MODE_NORMAL);
	//Can_message send = {.id = 5, .length = 1, .data[0] = 95};
	//Can_message receive;


	while (1)
	{


		system_loop();


	}







}

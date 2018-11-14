/*
#ifndef MENU_H_
#define MENU_H_

#include <avr/io.h>

void ShowMenu(void);
void ShowMenuPointer(void);
void PrintPointer(void);
void MenuInit(void);
void ShowChoice(void);

uint8_t menupointer;


#endif  MENU_H_ */


#ifndef MENU_H_
#define MENU_H_

typedef struct menu_item_info menu_item_info_t;


typedef struct menu_item_info {
	char *name;
	menu_item_info_t *parent;
	menu_item_info_t *child[7];
	int child_num;
	uint8_t menu_flag;
};


void MENU_init( void );

void MENU_print_menu();

void MENU_end_game();

void MENU_game(int);

void MENU_select_item();

void MENU_navigate(uint8_t, uint8_t*, uint8_t*, uint16_t*, int);

void MENU_highlight_item( void );

void menu_val_init();


#endif /* MENU_H_ */
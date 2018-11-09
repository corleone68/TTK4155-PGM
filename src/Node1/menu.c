#include "menu.h"
#include "oled.h"
#include "SliderJoystick.h"

//Joy.JoystickDigitalOut

#include <stdlib.h>

menu_item_info_t main_menu, play_game, highscores, settings, beginner, basic, hard, clear_highscores;

menu_item_info_t main_menu ={
	//.name = malloc(20),
	.name = "Main menu",
	.parent = NULL,
	.child[0] = &play_game,
	.child[1] = &highscores,
	.child[2] = &settings,
	.child_num = 3,
};

menu_item_info_t play_game = {
	.name = "Play game",
	.parent = &main_menu,
	.child[0] = &beginner,
	.child[1] = &basic,
	.child[2] = &hard,
	.child_num = 3,
};

menu_item_info_t highscores ={
	.name = "High scores",
	.parent = &main_menu,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t settings ={
	.name = "Settings",
	.parent = &main_menu,
	.child[0] = &clear_highscores,
	.child_num = 1,
};

menu_item_info_t beginner = {
	.name = "Beginner",
	.parent = &play_game,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t basic = {
	.name = "Basic",
	.parent = &play_game,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t hard = {
	.name = "Hard",
	.parent = &play_game,
	.child[0] = NULL,
	.child_num = 0,
};

menu_item_info_t clear_highscores ={
	.name = "Clear Highscores",
	.parent = &settings,
	.child[0] = NULL,
	.child_num = 0,
};


menu_item_info_t *current_menu;
menu_item_info_t *current_child;
int line;



void MENU_init( void ){
	current_menu = &main_menu;
	current_child = main_menu.child[0];
	line = 1;
	MENU_print_menu();
	MENU_highlight_item();
	
	while(1){
		//MENU_select_item();
		MENU_navigate();
		//printf("Current line %d \n", line);
	}
	
}


void MENU_print_menu(){
	//printf("her\n");
	OledClearDisplay();
	OledPrintString(current_menu->name);
	if (current_child!= NULL){
		//MENU_highlight_item();
	}
	for (int i =0; i < current_menu->child_num; i++){
		
		OledGoto(i+1, 10);
		OledPrintString(current_menu->child[i]->name);
		
	}
}

/*
void MENU_select_item(){
	//int pressed = JOY_button();
	if (JOY_button() && current_child!= NULL){
		while(JOY_button()){}
		current_menu = current_child;
		current_child = current_child->child[0];
		line = 1;
		MENU_print_menu();
	}
}
*/


void MENU_navigate(){
	//uint8_t direction;
	struct JoystickOutput Joy;
	JoystickRead(&Joy);
	                  //JOY_direction_t dir = JOY_get_direction();
	                  //printf("Direction: %d \n", dir);
	
	uint8_t dir;
	dir = Joy.JoystickDigitalOut;
	//printf("Direction = %d \n", dir);
	switch (dir){
		
		case 4:
		//printf("LEFT \n");
		_delay_ms(200);
		//while(Joy.JoystickDigitalOut == 4){}
		if (current_menu->parent != NULL){
			line = 1;
			current_menu = current_menu->parent;
			current_child = current_menu->child[0];
			//printf("LEFT - Current line %d \n", line);
			MENU_print_menu();
		}
		break;
		
		case 2:
		//printf("UP \n");
		_delay_ms(200);
		//while(Joy.JoystickDigitalOut == 2){}
		
		if (line > 1){
			line = line - 1;
			current_child = current_menu->child[line - 1];
			//printf("UP - Current line %d \n", line);
			MENU_highlight_item();
		}
		break;
		
		case 1:
		//printf("DOWN \n");
		_delay_ms(200);
		//while(Joy.JoystickDigitalOut == 1){}
		
		if (line < current_menu->child_num){
			line = line + 1;
			current_child = current_menu->child[line - 1];
			printf("DOWN  \n");
			MENU_highlight_item();
		}
		break;
		
		case 3:
		printf("RIGHT \n");
		
		//while(Joy.JoystickDigitalOut == 3){}
		if (current_child!= NULL){
			_delay_ms(200);
			//while(Joy.JoystickDigitalOut == 3){}
			current_menu = current_child;
			current_child = current_child->child[0];
			line = 1;
			MENU_print_menu();
		}	
		break;
		
		
		default:
		break;
		
	}
}


void MENU_highlight_item( void )

{
	
	for (int i = 1; i < current_menu->child_num + 1; i++){
		OledGoto(i, 0);
		OledPrintString("  ");
	}
	
	
	OledGoto(line,0);
	OLED_print_arrow();
	
	
}

#define F_CPU 4915200
#include <util/delay.h>
#include <stdio.h>
#include "menu.h"
#include "oled.h"
#include "system.h"
#include "SliderJoystick.h"

//Joy.JoystickDigitalOut

#include <stdlib.h>

menu_item_info_t main_menu, play_game, highscores, settings, beginner, free_game, hard, clear_highscores, calibrate;

menu_item_info_t *current_menu;
menu_item_info_t *current_child;
int line = 1;
uint8_t menu_flag = 1;
uint8_t calibrate_flag = 0;

//***************************************************************
//	Menu external values retrieval								*
//***************************************************************


menu_item_info_t main_menu ={
	//.name = malloc(20),
	.name = "Main menu",
	.parent = NULL,
	.child[0] = &play_game,
	.child[1] = &highscores,
	.child[2] = &settings,
	.child_num = 3,
	.menu_flag = 1,
};

menu_item_info_t play_game = {
	.name = "Play game",
	.parent = &main_menu,
	.child[0] = &beginner,
	.child[1] = &hard,
	.child[2] = &free_game,
	.child_num = 3,
	.menu_flag = 2,
};

menu_item_info_t highscores ={
	.name = "High scores",
	.parent = &main_menu,
	.child[0] = NULL,
	.child_num = 0,
	.menu_flag = 3,
};

menu_item_info_t settings ={
	.name = "Settings",
	.parent = &main_menu,
	.child[0] = &clear_highscores,
	.child[1] = &calibrate,
	.child_num = 2,
	.menu_flag = 4,
};

menu_item_info_t beginner = {
	.name = "Beginner",
	.parent = &play_game,
	.child[0] = NULL,
	.child_num = 0,
	.menu_flag = 5,
};

menu_item_info_t hard = {
	.name = "Hard",
	.parent = &play_game,
	.child[0] = NULL,
	.child_num = 0,
	.menu_flag = 6,
};

menu_item_info_t free_game = {
	.name = "Free",
	.parent = &play_game,
	.child[0] = NULL,
	.child_num = 0,
	.menu_flag = 7,
};

menu_item_info_t clear_highscores = {  
	.name = "Clear Highscores",
	.parent = &settings,
	.child[0] = NULL,
	.child_num = 0,
	.menu_flag = 8,
};

menu_item_info_t calibrate = {
	.name = "Calibrate",
	.parent = &settings,
	.child[0] = NULL,
	.child_num = 0,
	.menu_flag = 9,
};


void MENU_end_game(){
	OledClearDisplay();
	OledGoto(3,15);
	OledPrintString("Game Over");	
}


void MENU_calibrate(){
	char str[7];
	for (int i=1; i < 101; i++)
	{
		OledClearDisplay();
		OledGoto(3,15);
		OledPrintString("Calibrating    %");
		sprintf(str,"%d", i);
		OledGoto(3,75);
		OledPrintString(str);
		_delay_ms(50);
	}
	_delay_ms(200);
	OledClearDisplay();
	OledGoto(3,15);
	OledPrintString("Calibration done!");
	_delay_ms(800);
}


void MENU_game(score){
	OledClearDisplay();
	OledGoto(0,40);
	OledPrintString("Play game");
	OledGoto(2,15);
	OledPrintString(current_menu->name);
	OledGoto(4,15);
	OledPrintString("Score: ");
	char str[7];
	sprintf(str,"%d", score);
	OledGoto(4,50);
	OledPrintString(str);
	// doplnit score
}

void MENU_init( void ){
	current_menu = &main_menu;
	current_child = main_menu.child[0];
	line = 1;
	MENU_print_menu();
	MENU_highlight_item();

}


void MENU_print_menu(){
	
	OledClearDisplay();
	OledPrintString(current_menu->name);
	if (current_child!= NULL){
		//MENU_highlight_item();
	}
	for (int i = 0; i < current_menu->child_num; i++){
		
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


void MENU_navigate(uint8_t dir, uint8_t *game_mode, uint8_t *sett, uint16_t *score_top, int score){


	switch (dir){
		
		case 4:
		//printf("LEFT \n");
		_delay_ms(200);
		if (current_menu->parent != NULL){
			line = 1;
			current_menu = current_menu->parent;
			current_child = current_menu->child[0];
			menu_flag = current_menu->menu_flag;
			
			
			MENU_print_menu();
			MENU_highlight_item();
			
			*game_mode = 0;
			//printf("current child: %d \n", child_flag);
		}
		break;
		
		case 2:
		//printf("UP \n");
		_delay_ms(200);
		
		if (line > 1){
			line = line - 1;
			current_child = current_menu->child[line - 1];
				
			MENU_highlight_item();
			
			*game_mode = 0;
			//printf("current child: %d \n", child_flag);
		}
		break;
		
		case 1:
		//printf("DOWN \n");
		_delay_ms(200);
		
		if (line < current_menu->child_num){
			line = line + 1;
			current_child = current_menu->child[line -1]; 
			MENU_highlight_item();
			
			*game_mode = 0;
			//printf("current child: %d \n", child_flag);
		}
		break;
		
		case 3:
		//printf("RIGHT \n");
		
		if (current_child!= NULL){
			_delay_ms(200);
			current_menu = current_child;
			current_child = current_child->child[0];
			line = 1;
			menu_flag = current_menu->menu_flag;
			MENU_print_menu();
			MENU_highlight_item();
			*game_mode = 0;
		
			switch (menu_flag){
				case 5: 
					MENU_game(score);
					*game_mode = 2;
					*sett = 1;
					//printf("play beginner \n");
				break;
				
				case 6:
					MENU_game(score);
					*game_mode = 2;
					*sett = 2;
					//printf("play hard \n");
				break;
				
				case 7:
					MENU_game(score);
					*game_mode = 2;
					*sett = 3;
					//printf("play free \n");
				break;
				
				case 3:
					*game_mode = 0;
					*sett = 0;
					//printf("zobraz highscore \n");
				break;
				
				case 9:
					*game_mode = 1;
					*sett = 0;
					MENU_calibrate();
					*game_mode = 0; // zmanit na podmienku calibrate flagu
					MENU_init();
				break;
				
				case 8:
					*game_mode = 0;
					*sett = 0;
					*score_top = 0;
					//printf("clear highscore \n");
				break;
				
			}
		
		break;
		
		default:
		
		break;
		}
	}
}

void MENU_highlight_item( void )

{
	
	for (int i = 1; i < current_menu->child_num + 1; i++){
		OledGoto(i, 0);
		OledPrintString("  ");
	}
	
	
	OledGoto(line,0);
	Oledprintarrow();
		
}

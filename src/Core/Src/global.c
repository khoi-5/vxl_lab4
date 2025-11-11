/*
 * global.c
 *
 *  Created on: Oct 15, 2025
 *      Author: DELL
 */

#include "global.h"

int status = INIT;
int count = 1;
int counter1 = 0;
int counter2 = 0;

//thoi gian truc x
int time_red_x = 5;
int time_green_x = 3;
int time_yellow_x = 2;

int time_red_new_x = 5;
int time_green_new_x = 3;
int time_yellow_new_x = 2;

//thoi gian truc y
int time_red_y = 5;
int time_green_y = 3;
int time_yellow_y = 2;

int time_red_new_y = 5;
int time_green_new_y = 3;
int time_yellow_new_y = 2;


int current_time_x = 0;
int current_time_y = 0;

int count_x=0;
int count_y=0;

void blinky_led2(void){
	if (isButton1Pressed(0) == 1){
	HAL_GPIO_TogglePin(SEG_1_GPIO_Port, SEG_1_Pin);
	}
}
void blinky_led3(void){
	HAL_GPIO_TogglePin(SEG_2_GPIO_Port, SEG_2_Pin);
}
void blinky_led4(void){
	HAL_GPIO_TogglePin(SEG_3_GPIO_Port, SEG_3_Pin);
}
void blinky_led5(void){
	HAL_GPIO_TogglePin(SEG_4_GPIO_Port, SEG_4_Pin);
}


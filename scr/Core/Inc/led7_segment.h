/*
 * led7_segment.h
 *
 *  Created on: Oct 15, 2025
 *      Author: DELL
 */

#ifndef INC_LED7_SEGMENT_H_
#define INC_LED7_SEGMENT_H_

#include "global.h"



static volatile uint8_t s_disp_X = 0;
static volatile uint8_t s_disp_Y = 0;

//static uint8_t s_counter_x = 0;
//static uint8_t s_counter_y = 0;



GPIO_TypeDef *SEG_PORTS[14];
uint16_t SEG_PINS[14];
GPIO_PinState LEDS_7SEG_state[10][7];
void set_7SEG_X(const GPIO_PinState *L_LEDS_X_state);
void set_7SEG_X_left(const GPIO_PinState *L_LEDS_X_state);
void set_7SEG_Y(const GPIO_PinState *L_LEDS_Y_state);
void set_7SEG_Y_left(const GPIO_PinState *L_LEDS_Y_state);
void displaySetting_Y(int time);
void displaySetting_X(int time);
void timer9_for_led_7();
void timer9_for_led_7x();
void timer9_for_led_7y();
void set_counter_for_traffic_light(int time1, int time2);


void display_set_X(uint8_t v);
void display_set_Y(uint8_t v);
uint8_t display_get_X(void);
uint8_t display_get_Y(void);

void off_7SEG_X(void);
void off_7SEG_Y(void);
void display_mode_auto(void);
void display_mode_edit_x(void);
void display_mode_edit_y(void);
void display_mode_set_off(void);

#endif /* INC_LED7_SEGMENT_H_ */

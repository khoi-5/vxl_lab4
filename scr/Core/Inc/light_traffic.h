/*
 * light_traffic.h
 *
 *  Created on: Oct 15, 2025
 *      Author: DELL
 */

#ifndef INC_LIGHT_TRAFFIC_H_
#define INC_LIGHT_TRAFFIC_H_

#include "global.h"

void led_red_and_yellow();
void led_yellow_and_red();
void led_red_and_green();
void led_green_and_red();
void blinking_led_red();
void blinking_led_green();
void blinking_led_yellow();
void blinking_red_x_green_y();
void blinking_red_x_yellow_y();
void blinking_green_x_red_y();
void blinking_yellow_x_red_y();
void blinking_green_y();
void blinking_yellow_y();
void blinking_red_y();
void blinking_green_x();
void blinking_yellow_x();
void blinking_red_x();
void init();
void init_time();
void set_new_time(void);
// ===== Set trạng thái sáng cố định =====
void set_red_x_green_y(void);
void set_red_x_yellow_y(void);
void set_green_x_red_y(void);
void set_yellow_x_red_y(void);


#endif /* INC_LIGHT_TRAFFIC_H_ */

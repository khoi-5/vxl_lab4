/*
 * fsm_auto.c
 *
 *  Created on: Oct 15, 2025
 *      Author: DELL
 */


#include "fsm_auto.h"


void button0_to_change_to_config(void){
    if (isButton1Pressed(0) == 1) {
        init();
        config_init_new_from_current();          // copy time -> time_new
        status = CON_RED_X;                      // bắt đầu ở RED_X
        setTimer(2, 250);                        // nhịp blink 250ms
        display_mode_edit_x();
    }
}

void button2_to_change_to_manual(){
    if (isButton1Pressed(2) == 1) {
        status = MAN_RED_GREEN;
        setTimer(2, 250);
        setTimer(9, SCAN);
        display_mode_set_off();
    }
}

void fsm_auto_run(void) {
    switch (status) {
    case INIT:
        setTimer(9, SCAN);

        display_mode_auto();

        status = RED_GREEN;
        setTimer(0, 1000);
        setTimer(1, time_green_y * 1000);
        set_counter_for_traffic_light(time_red_x, time_green_y);

        break;

    case RED_GREEN:
        led_red_and_green();

        if (timer_flag[0]) {
            if (count_x > 0) count_x--;
            if (count_y > 0) count_y--;
            setTimer(0, 1000);
        }
        if (timer_flag[1]) {
            status = RED_YELLOW;
            setTimer(0, 1000);
            setTimer(1, time_yellow_y * 1000);
            set_counter_for_traffic_light(time_yellow_y, time_yellow_y);
        }
        button0_to_change_to_config();
        button2_to_change_to_manual();
        break;

    case RED_YELLOW:
        led_red_and_yellow();

        if (timer_flag[0]) {
            if (count_x > 0) count_x--;
            if (count_y > 0) count_y--;
            setTimer(0, 1000);
        }
        if (timer_flag[1]) {
            status = GREEN_RED;
            setTimer(0, 1000);
            setTimer(1, time_green_x * 1000);
            set_counter_for_traffic_light(time_green_x, time_red_y);

        }
        button0_to_change_to_config();
        button2_to_change_to_manual();
        break;

    case GREEN_RED:
        led_green_and_red();

        if (timer_flag[0]) {
            if (count_x > 0) count_x--;
            if (count_y > 0) count_y--;
            setTimer(0, 1000);
        }
        if (timer_flag[1]) {
            status = YELLOW_RED;
            setTimer(0, 1000);
            setTimer(1, time_yellow_x * 1000);
            set_counter_for_traffic_light(time_yellow_x, time_yellow_x);

        }
        button0_to_change_to_config();
        button2_to_change_to_manual();
        break;

    case YELLOW_RED:
        led_yellow_and_red();

        if (timer_flag[0]) {
            if (count_x > 0) count_x--;
            if (count_y > 0) count_y--;
            setTimer(0, 1000);
        }
        if (timer_flag[1]) {
            status = RED_GREEN;
            setTimer(0, 1000);
            setTimer(1, time_green_y * 1000);
            set_counter_for_traffic_light(time_red_x, time_green_y);
        }
        button0_to_change_to_config();
        button2_to_change_to_manual();
        break;

    default:
        break;
    }
}




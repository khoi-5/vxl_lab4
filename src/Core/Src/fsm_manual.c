/*
 * fsm_control_run.c
 *
 *  Created on: Nov 1, 2025
 *      Author: DELL
 */

#include <fsm_manual.h>
void come_back_to_auto(void){
    if (isButton1Pressed(0) == 1) {
    	status = INIT;
    	display_mode_auto();
    }
}
void fsm_manual_run(void){
	timer9_for_led_7();
    switch (status) {
    case MAN_RED_GREEN:
        if (isButton1Pressed(2) == 1) {
        	status = MAN_RED_YELLOW;
        }
        come_back_to_auto();
        	set_red_x_green_y();

    	break;
    case MAN_RED_YELLOW:
        if (isButton1Pressed(2) == 1) {
        	status = MAN_GREEN_RED;
        }
        come_back_to_auto();
        set_red_x_yellow_y();

    	break;
    case MAN_GREEN_RED:
        if (isButton1Pressed(2) == 1) {
        	status = MAN_YELLOW_RED;
        }
        come_back_to_auto();
        set_red_x_green_y();


    	break;
    case MAN_YELLOW_RED:
        if (isButton1Pressed(2) == 1) {
        	status = MAN_RED_GREEN;
        }
        come_back_to_auto();
        set_yellow_x_red_y();


    	break;




    default:
        break;
    }
}

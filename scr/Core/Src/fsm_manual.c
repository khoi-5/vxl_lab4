/*
 * fsm_control_run.c
 *
 *  Created on: Nov 1, 2025
 *      Author: DELL
 */

#include <fsm_manual.h>
void fsm_manual_run(void){
    switch (status) {
    case MAN_RED_GREEN:
        if (isButton1Pressed(2) == 1) {
        	status = MAN_RED_YELLOW;
        }
        if (isButton1Pressed(0) == 1) {
        	status = RED_GREEN;
        	display_mode_auto();
        }
        	set_red_x_green_y();

    	break;
    case MAN_RED_YELLOW:
        if (isButton1Pressed(2) == 1) {
        	status = MAN_GREEN_RED;
        }
        if (isButton1Pressed(0) == 1) {
        	status = RED_GREEN;
        	display_mode_auto();
        }
        set_red_x_yellow_y();

    	break;
    case MAN_GREEN_RED:
        if (isButton1Pressed(2) == 1) {
        	status = MAN_YELLOW_RED;
        }
        if (isButton1Pressed(0) == 1) {
        	status = RED_GREEN;
        	display_mode_auto();
        }
        	set_red_x_green_y();


    	break;
    case MAN_YELLOW_RED:
        if (isButton1Pressed(2) == 1) {
        	status = MAN_RED_GREEN;
        }
        if (isButton1Pressed(0) == 1) {
        	status = RED_GREEN;
        	display_mode_auto();
        }
        	set_yellow_x_red_y();


    	break;




    default:
        break;
    }
}

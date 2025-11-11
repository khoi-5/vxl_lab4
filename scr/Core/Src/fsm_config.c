/*
 * fsm_config.c
 *
 *  Created on: Nov 1, 2025
 *      Author: DELL
 */


#include <fsm_config.h>


int inc99(int v){ v++; if (v > 99) v = 1; return v; }

// Copy time thật -> *_new khi vào config
void config_init_new_from_current(void){
    time_red_new_x    = time_red_x;
    time_green_new_x  = time_green_x;
    time_yellow_new_x = time_yellow_x;

    time_red_new_y    = time_red_y;
    time_green_new_y  = time_green_y;
    time_yellow_new_y = time_yellow_y;
}



void config_handle_button1_inc_new(void){
    if (!isButton1Pressed(1)) return;

    switch (status) {
    // --- Đang chỉnh trục X ---
    case CON_RED_X:
        // Tăng Đỏ X <-> Tăng Xanh Y (Logic cơ bản)
        time_red_new_x    = inc99(time_red_new_x);
        time_green_new_y  = inc99(time_green_new_y);
        break;

    case CON_GREEN_X:
        // Tăng Xanh X <-> Tăng Đỏ Y
        time_green_new_x  = inc99(time_green_new_x);
        time_red_new_y    = inc99(time_red_new_y);
        break;

    case CON_YELLOW_X:
        // Tăng Vàng X <-> Tăng Đỏ Y (Vàng X thuộc chu kỳ Xanh/Vàng X, đối diện với Đỏ Y)
        time_yellow_new_x = inc99(time_yellow_new_x);
        time_red_new_y    = inc99(time_red_new_y);
        break;

    // --- Đang chỉnh trục Y ---
    case CON_RED_Y:
        // Tăng Đỏ Y <-> Tăng Xanh X
        time_red_new_y    = inc99(time_red_new_y);
        time_green_new_x  = inc99(time_green_new_x);
        break;

    case CON_GREEN_Y:
        // Tăng Xanh Y <-> Tăng Đỏ X
        time_green_new_y  = inc99(time_green_new_y);
        time_red_new_x    = inc99(time_red_new_x);
        break;

    case CON_YELLOW_Y:
        // Tăng Vàng Y <-> Tăng Đỏ X (Vàng Y thuộc chu kỳ Xanh/Vàng Y, đối diện với Đỏ X)
        time_yellow_new_y = inc99(time_yellow_new_y);
        time_red_new_x    = inc99(time_red_new_x);
        break;

    default:
        break;
    }
}

// NÚT 2: commit *_new -> time_* thật theo state hiện tại
void config_handle_button2_commit(void){
    if (!isButton1Pressed(2)) return;
    switch (status) {
    case CON_RED_X:     time_red_x    = time_red_new_x;   time_green_y  = time_green_new_y;  break;
    case CON_GREEN_X:   time_green_x  = time_green_new_x; time_red_y    = time_red_new_y;    break;
    case CON_YELLOW_X:  time_yellow_x = time_yellow_new_x;time_red_y    = time_red_new_y;    break;
    case CON_RED_Y:     time_red_y    = time_red_new_y;   time_green_x  = time_green_new_x;  break;
    case CON_GREEN_Y:   time_green_y  = time_green_new_y; time_red_x    = time_red_new_x;    break;
    case CON_YELLOW_Y:  time_yellow_y = time_yellow_new_y;time_red_x    = time_red_new_x;    break;
    }
}
// Commit ngay lập tức cho state hiện tại (không cần nút)
static inline void config_commit_current_state_now(void){
	time_red_x    = time_red_new_x;
	time_green_x  = time_green_new_x;
	time_yellow_x = time_yellow_new_x;

	time_red_y    = time_red_new_y;
	time_green_y  = time_green_new_y;
	time_yellow_y = time_yellow_new_y;
}

// NÚT 0: chuyển state vòng 6; hết vòng -> về AUTO RED_GREEN
void config_handle_button0_next_state(void){
    if (!isButton1Pressed(0)) return; // one-shot

    init(); // clear LED trước khi đổi state

    switch (status) {
    case CON_RED_X:     status = CON_GREEN_X;   break;
    case CON_GREEN_X:   status = CON_YELLOW_X;  break;
    case CON_YELLOW_X:  display_mode_edit_y();status = CON_RED_Y;     break;
    case CON_RED_Y:     status = CON_GREEN_Y;   break;
    case CON_GREEN_Y:   status = CON_YELLOW_Y;  break;

    case CON_YELLOW_Y:
        set_new_time();
        status = RED_GREEN;
        setTimer(0, 1000);
        setTimer(1, time_green_y * 1000);
        set_counter_for_traffic_light(time_red_x, time_green_y);
        return;

    default:
        status = CON_RED_X;
        break;
    }

}
void timer2(){

    if (timer_flag[2]) {
        switch (status) {
        case CON_RED_X:     blinking_red_x();     break;
        case CON_GREEN_X:   blinking_green_x();   break;
        case CON_YELLOW_X:  blinking_yellow_x();  break;

        case CON_RED_Y:     blinking_red_y();     break;
        case CON_GREEN_Y:   blinking_green_y();   break;
        case CON_YELLOW_Y:  blinking_yellow_y();  break;
        }
        setTimer(2, 250);
    }

}

// Vòng lặp config
void fsm_config_run(void){
    switch (status) {
    case CON_RED_X:
        config_handle_button0_next_state();
        config_handle_button1_inc_new();
        config_handle_button2_commit();
        timer2();
    	break;
    case CON_GREEN_X:
        config_handle_button0_next_state();
        config_handle_button1_inc_new();
        config_handle_button2_commit();
        timer2();
    	break;
    case CON_YELLOW_X:
        config_handle_button0_next_state();
        config_handle_button1_inc_new();
        config_handle_button2_commit();
        timer2();
    	break;
    case CON_RED_Y:
        config_handle_button0_next_state();
        config_handle_button1_inc_new();
        config_handle_button2_commit();
        timer2();
    	break;
    case CON_GREEN_Y:
        config_handle_button0_next_state();
        config_handle_button1_inc_new();
        config_handle_button2_commit();
        timer2();
    	break;
    case CON_YELLOW_Y:
        config_handle_button0_next_state();
        config_handle_button1_inc_new();
        config_handle_button2_commit();
        timer2();
    	break;



    default:
        break;
    }
}

/*
 * led7_segment.c
 *
 *  Created on: Oct 15, 2025
 *      Author: DELL
 */

#include "led7_segment.h"
uint8_t enable_disp_x = 1;
uint8_t enable_disp_y = 1;
void off_7SEG_X(void){
    HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
    HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
}
void off_7SEG_Y(void){
    HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
    HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
}
void display_mode_auto(void){
    enable_disp_x = 1;
    enable_disp_y = 1;
}
void display_mode_edit_x(void){
    enable_disp_x = 1;
    enable_disp_y = 0;  // tắt Y
    off_7SEG_Y();
}
void display_mode_edit_y(void){
    enable_disp_x = 0;  // tắt X
    enable_disp_y = 1;
    off_7SEG_X();
}
void display_mode_set_off(void){
    enable_disp_x = 0;
    enable_disp_y = 0;
    off_7SEG_X();
    off_7SEG_Y();
}

GPIO_TypeDef *SEG_PORTS[14] = {
    SEG_0_GPIO_Port, SEG_1_GPIO_Port, SEG_2_GPIO_Port, SEG_3_GPIO_Port,
    SEG_4_GPIO_Port, SEG_5_GPIO_Port, SEG_6_GPIO_Port,

    SEG_7_GPIO_Port, SEG_8_GPIO_Port, SEG_9_GPIO_Port,SEG_10_GPIO_Port,
	SEG_11_GPIO_Port, SEG_12_GPIO_Port, SEG_13_GPIO_Port
};

uint16_t SEG_PINS[14] = {
    SEG_0_Pin, SEG_1_Pin, SEG_2_Pin, SEG_3_Pin, SEG_4_Pin, SEG_5_Pin, SEG_6_Pin,
    SEG_7_Pin, SEG_8_Pin, SEG_9_Pin, SEG_10_Pin, SEG_11_Pin, SEG_12_Pin, SEG_13_Pin
};

// Pattern 0..9 (giữ nguyên mức 0/1 theo mạch của bạn)
GPIO_PinState LEDS_7SEG_state[10][7] = {
    {0,0,0,0,0,0,1}, // 0
    {1,0,0,1,1,1,1}, // 1
    {0,0,1,0,0,1,0}, // 2
    {0,0,0,0,1,1,0}, // 3
    {1,0,0,1,1,0,0}, // 4
    {0,1,0,0,1,0,0}, // 5
    {0,1,0,0,0,0,0}, // 6
    {0,0,0,1,1,1,1}, // 7
    {0,0,0,0,0,0,0}, // 8
    {0,0,0,0,1,0,0}  // 9
};

// ----------------------
// Trục X: 0..6, EN0 = LEFT, EN1 = RIGHT
// ----------------------
void set_7SEG_X_left(const GPIO_PinState *L_LEDS_X_state) {
    // Bật bên trái (EN0), tắt bên phải (EN1)
    HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
    HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);

    // Ghi trạng thái cho 7 chân (0 đến 6)
    HAL_GPIO_WritePin(SEG_PORTS[0], SEG_PINS[0], L_LEDS_X_state[0]);
    HAL_GPIO_WritePin(SEG_PORTS[1], SEG_PINS[1], L_LEDS_X_state[1]);
    HAL_GPIO_WritePin(SEG_PORTS[2], SEG_PINS[2], L_LEDS_X_state[2]);
    HAL_GPIO_WritePin(SEG_PORTS[3], SEG_PINS[3], L_LEDS_X_state[3]);
    HAL_GPIO_WritePin(SEG_PORTS[4], SEG_PINS[4], L_LEDS_X_state[4]);
    HAL_GPIO_WritePin(SEG_PORTS[5], SEG_PINS[5], L_LEDS_X_state[5]);
    HAL_GPIO_WritePin(SEG_PORTS[6], SEG_PINS[6], L_LEDS_X_state[6]);
}

void set_7SEG_X(const GPIO_PinState *L_LEDS_X_state) {
    // Bật bên phải (EN1), tắt bên trái (EN0)
    HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
    HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);

    // Ghi trạng thái cho 7 chân (0 đến 6)
    HAL_GPIO_WritePin(SEG_PORTS[0], SEG_PINS[0], L_LEDS_X_state[0]);
    HAL_GPIO_WritePin(SEG_PORTS[1], SEG_PINS[1], L_LEDS_X_state[1]);
    HAL_GPIO_WritePin(SEG_PORTS[2], SEG_PINS[2], L_LEDS_X_state[2]);
    HAL_GPIO_WritePin(SEG_PORTS[3], SEG_PINS[3], L_LEDS_X_state[3]);
    HAL_GPIO_WritePin(SEG_PORTS[4], SEG_PINS[4], L_LEDS_X_state[4]);
    HAL_GPIO_WritePin(SEG_PORTS[5], SEG_PINS[5], L_LEDS_X_state[5]);
    HAL_GPIO_WritePin(SEG_PORTS[6], SEG_PINS[6], L_LEDS_X_state[6]);
}

// ----------------------
// Trục Y: 7..13, EN2 = LEFT, EN3 = RIGHT
// ----------------------
// ----------------------
void set_7SEG_Y_left(const GPIO_PinState *L_LEDS_Y_state) {
    // Bật bên trái (EN2), tắt bên phải (EN3)
    HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
    HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);

    // Ghi trạng thái cho 7 chân (7 đến 13)
    HAL_GPIO_WritePin(SEG_PORTS[7], SEG_PINS[7], L_LEDS_Y_state[0]);
    HAL_GPIO_WritePin(SEG_PORTS[8], SEG_PINS[8], L_LEDS_Y_state[1]);
    HAL_GPIO_WritePin(SEG_PORTS[9], SEG_PINS[9], L_LEDS_Y_state[2]);
    HAL_GPIO_WritePin(SEG_PORTS[10], SEG_PINS[10], L_LEDS_Y_state[3]);
    HAL_GPIO_WritePin(SEG_PORTS[11], SEG_PINS[11], L_LEDS_Y_state[4]);
    HAL_GPIO_WritePin(SEG_PORTS[12], SEG_PINS[12], L_LEDS_Y_state[5]);
    HAL_GPIO_WritePin(SEG_PORTS[13], SEG_PINS[13], L_LEDS_Y_state[6]);
}

void set_7SEG_Y(const GPIO_PinState *L_LEDS_Y_state) {
    // Bật bên phải (EN3), tắt bên trái (EN2)
    HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
    HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);

    // Ghi trạng thái cho 7 chân (7 đến 13)
    HAL_GPIO_WritePin(SEG_PORTS[7], SEG_PINS[7], L_LEDS_Y_state[0]);
    HAL_GPIO_WritePin(SEG_PORTS[8], SEG_PINS[8], L_LEDS_Y_state[1]);
    HAL_GPIO_WritePin(SEG_PORTS[9], SEG_PINS[9], L_LEDS_Y_state[2]);
    HAL_GPIO_WritePin(SEG_PORTS[10], SEG_PINS[10], L_LEDS_Y_state[3]);
    HAL_GPIO_WritePin(SEG_PORTS[11], SEG_PINS[11], L_LEDS_Y_state[4]);
    HAL_GPIO_WritePin(SEG_PORTS[12], SEG_PINS[12], L_LEDS_Y_state[5]);
    HAL_GPIO_WritePin(SEG_PORTS[13], SEG_PINS[13], L_LEDS_Y_state[6]);
}

// ----------------------
// Multiplex hiển thị (00..99)
// ----------------------
// counter1/counter2 là biến toàn cục bạn đã có sẵn
void displaySetting_Y(int time) {          // Cụm Y
    //if (time < 0) time = 0;
    //if (time > 99) time = 99;

    switch (counter1) {
    case 0:
        set_7SEG_Y_left(LEDS_7SEG_state[time / 10]); // hàng chục bên trái
        counter1 = 1;

        break;
    case 1:
        set_7SEG_Y(LEDS_7SEG_state[time % 10]);      // hàng đơn vị bên phải
        counter1 = 0;

        break;
    default:
        //counter1 = 0;
        break;
    }
}

void displaySetting_X(int time) {         // Cụm X
    //if (time < 0) time = 0;
    //if (time > 99) time = 99;


    switch (counter2) {
    case 0:

        set_7SEG_X_left(LEDS_7SEG_state[time / 10]); // hàng chục bên trái
        counter2 = 1;

        break;
    case 1:

        set_7SEG_X(LEDS_7SEG_state[time % 10]);      // hàng đơn vị bên phải
        counter2 = 0;

        break;
    default:
        //counter2 = 0;
        break;
    }
}

void timer9_for_led_7x(void){
    // Thực sự quét hiển thị theo cờ enable
    if (enable_disp_x) {
        switch (status) {
        case RED_GREEN:
        case RED_YELLOW:
        case GREEN_RED:
        case YELLOW_RED:
            displaySetting_X(count_x);
            break;

        case CON_RED_X:      displaySetting_X(time_red_new_x);     break;
        case CON_GREEN_X:    displaySetting_X(time_green_new_x);   break;
        case CON_YELLOW_X:   displaySetting_X(time_yellow_new_x);  break;

        case MAN_RED_GREEN:  /* off */  break;
        case MAN_RED_YELLOW: /* off */  break;
        case MAN_GREEN_RED:  /* off */  break;
        case MAN_YELLOW_RED: /* off */  break;

        default:
            displaySetting_X(count_x);
            break;
        }
    } else {
        off_7SEG_X();
    }
}
void timer9_for_led_7y(void){
    if (enable_disp_y) {
        switch (status) {
        case RED_GREEN:
        case RED_YELLOW:
        case GREEN_RED:
        case YELLOW_RED:
            displaySetting_Y(count_y);
            break;

        case CON_RED_Y:      displaySetting_Y(time_red_new_y);     break;
        case CON_GREEN_Y:    displaySetting_Y(time_green_new_y);   break;
        case CON_YELLOW_Y:   displaySetting_Y(time_yellow_new_y);  break;

        case MAN_RED_GREEN:  /* off */  break;
        case MAN_RED_YELLOW: /* off */  break;
        case MAN_GREEN_RED:  /* off */  break;
        case MAN_YELLOW_RED: /* off */  break;

        default:
            displaySetting_Y(count_y);
            break;
        }
    } else {
        off_7SEG_Y();
    }
}
void timer9_for_led_7(void){
    if (!timer_flag[9]) return;

    // Chọn dữ liệu muốn hiển thị theo trạng thái
    switch (status) {
    case RED_GREEN:
    case RED_YELLOW:
    case GREEN_RED:
    case YELLOW_RED:
        display_mode_auto();
        break;

    case CON_RED_X:    display_mode_edit_x();  break;
    case CON_GREEN_X:  display_mode_edit_x();  break;
    case CON_YELLOW_X: display_mode_edit_x();  break;

    case CON_RED_Y:    display_mode_edit_y();  break;
    case CON_GREEN_Y:  display_mode_edit_y();  break;
    case CON_YELLOW_Y: display_mode_edit_y();  break;

    case MAN_RED_GREEN:
    case MAN_RED_YELLOW:
    case MAN_GREEN_RED:
    case MAN_YELLOW_RED:
        display_mode_set_off();
        break;

    default:
        display_mode_auto();
        break;
    }
    timer9_for_led_7x();
    timer9_for_led_7y();
	setTimer(9, SCAN);

}
void set_counter_for_traffic_light(int time1, int time2){
	count_x = time1;
	count_y = time2;
}

void display_set_X(uint8_t v) {
    if (v > 99) v = 99;
    s_disp_X = v;
}
void display_set_Y(uint8_t v) {
    if (v > 99) v = 99;
    s_disp_Y = v;
}

// Optional nếu cần đọc lại
uint8_t display_get_X(void) { return s_disp_X; }
uint8_t display_get_Y(void) { return s_disp_Y; }



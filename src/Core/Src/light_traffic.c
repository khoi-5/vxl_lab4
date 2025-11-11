/*
 * light_traffic.c
 *
 *  Created on: Oct 15, 2025
 *      Author: DELL
 */


#include "light_traffic.h"


#define LED_ON   GPIO_PIN_SET
#define LED_OFF  GPIO_PIN_RESET
// ====== Config ======
#define NUM_LEDS      12
#define NUM_PATTERNS  4


#define ACTIVE   GPIO_PIN_SET
#define INACTIVE GPIO_PIN_RESET

// ====== LED Port/Pin Maps ======
GPIO_TypeDef *LED_PORTS[NUM_LEDS] = {
    LED_1_GPIO_Port,  LED_2_GPIO_Port,  LED_3_GPIO_Port,  LED_4_GPIO_Port,
    LED_5_GPIO_Port,  LED_6_GPIO_Port,  LED_7_GPIO_Port,  LED_8_GPIO_Port,
    LED_9_GPIO_Port,  LED_10_GPIO_Port, LED_11_GPIO_Port, LED_12_GPIO_Port
};

uint16_t LED_PINS[NUM_LEDS] = {
    LED_1_Pin,  LED_2_Pin,  LED_3_Pin,  LED_4_Pin,
    LED_5_Pin,  LED_6_Pin,  LED_7_Pin,  LED_8_Pin,
    LED_9_Pin,  LED_10_Pin, LED_11_Pin, LED_12_Pin
};

// ====== LED Patterns (4 trạng thái × 12 đèn) ======
// [0] green+red, [1] yellow+red, [2] red+green, [3] red+yellow

GPIO_PinState LEDS_state[NUM_PATTERNS][NUM_LEDS] = {
	//  XANH ,     VANG   ,  DO     , XANH   ,   VANG    , DO
    // pattern 0
    { INACTIVE, INACTIVE, ACTIVE, ACTIVE, INACTIVE, INACTIVE,
      INACTIVE, INACTIVE, ACTIVE, ACTIVE, INACTIVE, INACTIVE },

    // pattern 1
    { INACTIVE, INACTIVE, ACTIVE, INACTIVE, ACTIVE, INACTIVE,
      INACTIVE, INACTIVE, ACTIVE, INACTIVE, ACTIVE, INACTIVE },

    // pattern 2
    { ACTIVE, INACTIVE, INACTIVE, INACTIVE, INACTIVE, ACTIVE,
      ACTIVE, INACTIVE, INACTIVE, INACTIVE, INACTIVE, ACTIVE },

    // pattern 3
    { INACTIVE, ACTIVE, INACTIVE, INACTIVE, INACTIVE, ACTIVE,
      INACTIVE, ACTIVE, INACTIVE, INACTIVE, INACTIVE, ACTIVE }
};

// ====== Helpers ======
static inline void set_LEDS(const GPIO_PinState *state) {
    for (size_t i = 0; i < NUM_LEDS; ++i) {
        HAL_GPIO_WritePin(LED_PORTS[i], LED_PINS[i], state[i]);
    }
}

static inline void clear_all_leds(void) {
    for (size_t i = 0; i < NUM_LEDS; ++i) {
        HAL_GPIO_WritePin(LED_PORTS[i], LED_PINS[i], GPIO_PIN_RESET);
    }
}






// ====== Public APIs ======
void set_new_time(void) {
    // Cập nhật thời gian trục X
    time_red_x    = time_red_new_x;
    time_green_x  = time_green_new_x;  // Đã sửa
    time_yellow_x = time_yellow_new_x; // Đã sửa

    // Cập nhật thời gian trục Y
    time_red_y    = time_red_new_y;    // Đã sửa
    time_green_y  = time_green_new_y;  // Đã sửa
    time_yellow_y = time_yellow_new_y; // Đã sửa
}
void init_time(void) {
    time_red_x    = INIT_RED_X ;
    time_green_x  = INIT_GREEN_X ;
    time_yellow_x = INIT_YELLOW_X;
    time_red_y    = INIT_RED_Y ;
    time_green_y  = INIT_GREEN_Y ;
    time_yellow_y = INIT_YELLOW_Y ;
}

void init(void) {
    clear_all_leds();
    count_x=0;
    count_y=0;
}

void led_red_and_green(void) {
    set_LEDS(LEDS_state[2]);
}

void led_red_and_yellow(void) {
    set_LEDS(LEDS_state[3]);
}

void led_green_and_red(void) {
    set_LEDS(LEDS_state[0]);
}

void led_yellow_and_red(void) {
    set_LEDS(LEDS_state[1]);
}

// ====== Blink theo từng màu toàn ngã tư ======
// RED  = 3, 6, 9, 12
void blinking_led_red(void) {
    HAL_GPIO_TogglePin(LED_3_GPIO_Port,  LED_3_Pin);
    HAL_GPIO_TogglePin(LED_6_GPIO_Port,  LED_6_Pin);
    HAL_GPIO_TogglePin(LED_9_GPIO_Port,  LED_9_Pin);
    HAL_GPIO_TogglePin(LED_12_GPIO_Port, LED_12_Pin);
}

// GREEN = 1, 4, 7, 10 (đang đúng)
void blinking_led_green(void) {
    HAL_GPIO_TogglePin(LED_1_GPIO_Port,  LED_1_Pin);
    HAL_GPIO_TogglePin(LED_4_GPIO_Port,  LED_4_Pin);
    HAL_GPIO_TogglePin(LED_7_GPIO_Port,  LED_7_Pin);
    HAL_GPIO_TogglePin(LED_10_GPIO_Port, LED_10_Pin);
}

// YELLOW = 2, 5, 8, 11
void blinking_led_yellow(void) {
    HAL_GPIO_TogglePin(LED_2_GPIO_Port,  LED_2_Pin);
    HAL_GPIO_TogglePin(LED_5_GPIO_Port,  LED_5_Pin);
    HAL_GPIO_TogglePin(LED_8_GPIO_Port,  LED_8_Pin);
    HAL_GPIO_TogglePin(LED_11_GPIO_Port, LED_11_Pin);
}
// ====== Blink theo cặp X/Y ======

void blinking_red_x_green_y(void) {
    HAL_GPIO_TogglePin(LED_6_GPIO_Port,  LED_6_Pin);
    HAL_GPIO_TogglePin(LED_12_GPIO_Port,  LED_12_Pin);
    HAL_GPIO_TogglePin(LED_1_GPIO_Port,  LED_1_Pin);
    HAL_GPIO_TogglePin(LED_7_GPIO_Port, LED_7_Pin);
}

// đỏ X – vàng Y  -> X: (3,9), Y: (5,11)
void blinking_red_x_yellow_y(void) {
    HAL_GPIO_TogglePin(LED_6_GPIO_Port,  LED_6_Pin);
    HAL_GPIO_TogglePin(LED_12_GPIO_Port,  LED_12_Pin);
    HAL_GPIO_TogglePin(LED_2_GPIO_Port,  LED_2_Pin);
    HAL_GPIO_TogglePin(LED_8_GPIO_Port, LED_8_Pin);
}

// xanh X – đỏ Y  -> X: (1,7), Y: (6,12)
void blinking_green_x_red_y(void) {
    HAL_GPIO_TogglePin(LED_4_GPIO_Port,  LED_4_Pin);
    HAL_GPIO_TogglePin(LED_10_GPIO_Port,  LED_10_Pin);
    HAL_GPIO_TogglePin(LED_3_GPIO_Port,  LED_3_Pin);
    HAL_GPIO_TogglePin(LED_9_GPIO_Port, LED_9_Pin);
}

// vàng X – đỏ Y  -> X: (2,8), Y: (6,12)
void blinking_yellow_x_red_y(void) {
    HAL_GPIO_TogglePin(LED_5_GPIO_Port,  LED_5_Pin);
    HAL_GPIO_TogglePin(LED_11_GPIO_Port,  LED_11_Pin);
    HAL_GPIO_TogglePin(LED_3_GPIO_Port,  LED_3_Pin);
    HAL_GPIO_TogglePin(LED_9_GPIO_Port, LED_9_Pin);
}
void blinking_green_y(void) {
    HAL_GPIO_TogglePin(LED_1_GPIO_Port,  LED_1_Pin);
    HAL_GPIO_TogglePin(LED_7_GPIO_Port,  LED_7_Pin);
}
void blinking_yellow_y(void) {
    HAL_GPIO_TogglePin(LED_2_GPIO_Port,  LED_2_Pin);
    HAL_GPIO_TogglePin(LED_8_GPIO_Port,  LED_8_Pin);
}
void blinking_red_y(void) {
    HAL_GPIO_TogglePin(LED_3_GPIO_Port,  LED_3_Pin);
    HAL_GPIO_TogglePin(LED_9_GPIO_Port,  LED_9_Pin);
}

void blinking_green_x(void) {
    HAL_GPIO_TogglePin(LED_4_GPIO_Port,  LED_4_Pin);
    HAL_GPIO_TogglePin(LED_10_GPIO_Port, LED_10_Pin);
}
void blinking_yellow_x(void) {
    HAL_GPIO_TogglePin(LED_5_GPIO_Port,  LED_5_Pin);
    HAL_GPIO_TogglePin(LED_11_GPIO_Port, LED_11_Pin);
}
void blinking_red_x(void) {
    HAL_GPIO_TogglePin(LED_6_GPIO_Port,  LED_6_Pin);
    HAL_GPIO_TogglePin(LED_12_GPIO_Port, LED_12_Pin);
}
static inline void set_X_green(void){
    HAL_GPIO_WritePin(LED_4_GPIO_Port,  LED_4_Pin,  LED_ON);
    HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, LED_ON);
    HAL_GPIO_WritePin(LED_5_GPIO_Port,  LED_5_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, LED_OFF);
    HAL_GPIO_WritePin(LED_6_GPIO_Port,  LED_6_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_12_GPIO_Port, LED_12_Pin, LED_OFF);
}

static inline void set_X_yellow(void){
    HAL_GPIO_WritePin(LED_5_GPIO_Port,  LED_5_Pin,  LED_ON);
    HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, LED_ON);
    HAL_GPIO_WritePin(LED_4_GPIO_Port,  LED_4_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, LED_OFF);
    HAL_GPIO_WritePin(LED_6_GPIO_Port,  LED_6_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_12_GPIO_Port, LED_12_Pin, LED_OFF);
}

static inline void set_X_red(void){
    HAL_GPIO_WritePin(LED_6_GPIO_Port,  LED_6_Pin,  LED_ON);
    HAL_GPIO_WritePin(LED_12_GPIO_Port, LED_12_Pin, LED_ON);
    HAL_GPIO_WritePin(LED_4_GPIO_Port,  LED_4_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, LED_OFF);
    HAL_GPIO_WritePin(LED_5_GPIO_Port,  LED_5_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, LED_OFF);
}

// ===== Helpers: set màu cho nhánh Y =====
static inline void set_Y_green(void){
    HAL_GPIO_WritePin(LED_1_GPIO_Port,  LED_1_Pin,  LED_ON);
    HAL_GPIO_WritePin(LED_7_GPIO_Port,  LED_7_Pin,  LED_ON);
    HAL_GPIO_WritePin(LED_2_GPIO_Port,  LED_2_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_8_GPIO_Port,  LED_8_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_3_GPIO_Port,  LED_3_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_9_GPIO_Port,  LED_9_Pin,  LED_OFF);
}

static inline void set_Y_yellow(void){
    HAL_GPIO_WritePin(LED_2_GPIO_Port,  LED_2_Pin,  LED_ON);
    HAL_GPIO_WritePin(LED_8_GPIO_Port,  LED_8_Pin,  LED_ON);
    HAL_GPIO_WritePin(LED_1_GPIO_Port,  LED_1_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_7_GPIO_Port,  LED_7_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_3_GPIO_Port,  LED_3_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_9_GPIO_Port,  LED_9_Pin,  LED_OFF);
}

static inline void set_Y_red(void){
    HAL_GPIO_WritePin(LED_3_GPIO_Port,  LED_3_Pin,  LED_ON);
    HAL_GPIO_WritePin(LED_9_GPIO_Port,  LED_9_Pin,  LED_ON);
    HAL_GPIO_WritePin(LED_1_GPIO_Port,  LED_1_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_7_GPIO_Port,  LED_7_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_2_GPIO_Port,  LED_2_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_8_GPIO_Port,  LED_8_Pin,  LED_OFF);
}

// ===== 4 hàm set trạng thái cố định =====
void set_red_x_green_y(void){
    set_X_red();
    set_Y_green();
}

void set_red_x_yellow_y(void){
    set_X_red();
    set_Y_yellow();
}

void set_green_x_red_y(void){
    set_X_green();
    set_Y_red();
}

void set_yellow_x_red_y(void){
    set_X_yellow();
    set_Y_red();
}

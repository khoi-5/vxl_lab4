/*
 * button.c
 *
 *  Created on: Oct 15, 2025
 *      Author: DELL
 */



#include "button.h"

// Khởi tạo tất cả về NORMAL_STATE
int KeyReg0[10] = { [0 ... 9] = NORMAL_STATE };
int KeyReg1[10] = { [0 ... 9] = NORMAL_STATE };
int KeyReg2[10] = { [0 ... 9] = NORMAL_STATE };
int KeyReg3[10] = { [0 ... 9] = NORMAL_STATE };

int button1_flag[10]          = {0};
int button1_long_pressed[10]  = {0};

int StableCnt[10]  = {0};
int HoldTicks[10]  = {0};
int LongFired[10]  = {0};

static inline int readPinByIndex(int i) {
  switch (i) {
    case 0: return HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
    case 1: return HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
    case 2: return HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin);
    default: return NORMAL_STATE;
  }
}

int isButton1Pressed(int index) {
  if (button1_flag[index]) {
    button1_flag[index] = 0;
    return 1;
  }
  return 0;
}

int isButton1LongPressed(int index) {
  if (button1_long_pressed[index]) {
    button1_long_pressed[index] = 0;
    return 1;
  }
  return 0;
}

void getKeyInput(void) {
  // Gọi hàm này mỗi TICK_MS (ví dụ 10ms)
  for (int i = 0; i < 10; i++) {
    // Dịch thanh ghi để debounce
    KeyReg2[i] = KeyReg1[i];
    KeyReg1[i] = KeyReg0[i];
    KeyReg0[i] = readPinByIndex(i);

    // Kiểm tra ổn định 3 lần liên tiếp
    if (KeyReg0[i] == KeyReg1[i] && KeyReg1[i] == KeyReg2[i]) {
      // Tăng đếm ổn định cho debounce
      if (StableCnt[i] < DEBOUNCE_TICKS) StableCnt[i]++;
      // Khi qua ngưỡng debounce và khác với trạng thái đã chốt (KeyReg3), ta “chốt” trạng thái mới
      if (StableCnt[i] >= DEBOUNCE_TICKS && KeyReg2[i] != KeyReg3[i]) {
        KeyReg3[i] = KeyReg2[i]; // chốt

        if (KeyReg3[i] == PRESSED_STATE) {
          // Vừa nhấn (sau debounce): reset bộ đếm giữ, đánh dấu chưa bắn long
          HoldTicks[i] = 0;
          LongFired[i] = 0;
        } else { // NORMAL_STATE: vừa thả
          // Nếu chưa bắn long-press trước đó => đây là nhấn ngắn
          if (!LongFired[i]) {
            button1_flag[i] = 1; // short press event
          }
          // Reset lại đếm giữ (an toàn)
          HoldTicks[i] = 0;
          LongFired[i] = 0;
        }
      }
    } else {
      // Chưa ổn định: reset đếm debounce
      StableCnt[i] = 0;
    }

    // Nếu đang bị giữ ở mức PRESSED_STATE (đã chốt), ta đếm thời gian giữ
    if (KeyReg3[i] == PRESSED_STATE) {
      if (HoldTicks[i] < 0x7FFFFFFF) HoldTicks[i]++;
      // Nếu vượt ngưỡng long-press và chưa bắn cờ → bắn 1 lần
      if (!LongFired[i] && HoldTicks[i] >= LONG_PRESS_TICKS) {
        button1_long_pressed[i] = 1;
        LongFired[i] = 1;
        // Nếu bạn muốn auto-repeat theo chu kỳ, có thể reset HoldTicks[i] = 0; tại đây
        // để bắn lặp lại theo LONG_PRESS_TICKS. Còn không thì để 1 lần là đủ.
      }
    }
  }
}

/*
 * button.c
 *
 *  Created on: Oct 15, 2025
 *      Author: DELL
 */

#ifndef INC_BUTTON_C_
#define INC_BUTTON_C_

#include "main.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

// Tick và ngưỡng thời gian (đơn vị ms)
#define TICK_MS         10
#define DEBOUNCE_MS     30
#define LONG_PRESS_MS   2000

// Suy ra số tick
#define DEBOUNCE_TICKS   (DEBOUNCE_MS / TICK_MS)
#define LONG_PRESS_TICKS (LONG_PRESS_MS / TICK_MS)

// Cờ sự kiện (đọc xong sẽ tự xóa)
extern int button1_flag[10];          // nhấn ngắn
extern int button1_long_pressed[10];  // nhấn đè

// Thanh ghi và biến trạng thái
extern int KeyReg0[10], KeyReg1[10], KeyReg2[10], KeyReg3[10];
extern int StableCnt[10];             // đếm debounce
extern int HoldTicks[10];             // thời gian giữ (tính bằng tick)
extern int LongFired[10];             // đã bắn cờ long-press chưa?

void getKeyInput(void);
int  isButton1Pressed(int index);
int  isButton1LongPressed(int index);

#endif /* INC_BUTTON_C_ */

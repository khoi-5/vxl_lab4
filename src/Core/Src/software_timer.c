/*
 * software_timer.c
 *
 *  Created on: Oct 15, 2025
 *      Author: DELL
 */


#include "software_timer.h"

volatile int timer_flag[MAX_VALUE]    = {0};
volatile int timer_counter[MAX_VALUE] = {0};
int timer_cycle =10;
void setTimer(int index, int counter) {
	timer_flag[index] = 0;
	timer_counter[index] = counter / timer_cycle;
}
void timerRun() {
	for (int i = 0; i < 10; i++) {
		if (timer_counter[i] > 0) {
			timer_counter[i]--;
		}
		if (timer_counter[i] <= 0) {
			timer_flag[i] = 1;
		}
	}
}

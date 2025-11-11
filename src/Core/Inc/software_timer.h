/*
 * software_timer.h
 *
 *  Created on: Oct 15, 2025
 *      Author: DELL
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define MAX_VALUE 10

extern volatile int timer_flag[MAX_VALUE];
extern volatile int timer_counter[MAX_VALUE];
extern int timer_cycle;
void setTimer(int index, int counter);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */

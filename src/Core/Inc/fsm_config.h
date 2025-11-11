/*
 * fsm_maunal.h
 *
 *  Created on: Nov 1, 2025
 *      Author: DELL
 */

#ifndef INC_FSM_CONFIG_H_
#define INC_FSM_CONFIG_H_

#include "global.h"
int  inc99(int v);


void config_init_new_from_current(void);


void config_update_display_from_new_state(void);


void config_handle_button1_inc_new(void);


void config_handle_button2_commit(void);


void config_handle_button0_next_state(void);


void fsm_config_run(void);

static inline void config_update_display_from_new_pair(void){
}
void timer2();

#endif /* INC_FSM_CONFIG_H_ */

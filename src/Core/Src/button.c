/*
 * button.c
 *
 *  Created on: Oct 15, 2025
 *      Author: DELL
 */



#include "button.h"

int KeyReg0[10] = { NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE,
NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE,
NORMAL_STATE };
int KeyReg1[10] = { NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE,
NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE,
NORMAL_STATE };
int KeyReg2[10] = { NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE,
NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE,
NORMAL_STATE };
int KeyReg3[10] = { NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE,
NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE,
NORMAL_STATE };

int TimeOutForKeyPress = 500;
int button1_pressed[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int button1_long_pressed[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int button1_flag[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int isButton1Pressed(int index) {
	if (button1_flag[index] == 1) {
		button1_flag[index] = 0;
		return 1;
	}
	return 0;
}

int isButton1LongPressed(int index) {
	if (button1_long_pressed[index] == 1) {
		button1_long_pressed[index] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index) {
	//TODO
	//HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	button1_flag[index] = 1;
}

void getKeyInput() {
	for (int i = 0; i < 10; i++) {
		KeyReg2[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg0[i];
	}
	// Add your key
	KeyReg0[0] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
	KeyReg0[1] = HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
	KeyReg0[2] = HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin);
	/*KeyReg0[3] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
	 KeyReg0[4] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
	 KeyReg0[5] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
	 KeyReg0[6] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
	 KeyReg0[7] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
	 KeyReg0[8] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
	 KeyReg0[9] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);*/

	for (int i = 0; i < 10; i++) {
		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])) {
			if (KeyReg2[i] != KeyReg3[i]) {
				KeyReg3[i] = KeyReg2[i];

				if (KeyReg3[i] == PRESSED_STATE) {
					TimeOutForKeyPress = 500;
					//subKeyProcess();
					button1_flag[i] = 1;
				}

			} else {
				TimeOutForKeyPress--;
				if (TimeOutForKeyPress == 0) {
					TimeOutForKeyPress = 500;
					if (KeyReg3[i] == PRESSED_STATE) {
						//subKeyProcess();
						button1_flag[i] = 1;
					}
				}
			}
		}
	}
}

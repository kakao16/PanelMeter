/**
 * @file menu.c
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing definitions of functions for menu logic. 
 * @version 1.0
 */
 
#include "menu.h"

char display[21];
float results[4];

static const char *settings[] = {
	"exit              ",
  "div_voltage       ",
  "offset_voltage    "
};
static uint8_t cursorPos = 0;

enum screen active_screen = READOUT;

static uint8_t error;

uint8_t print_readout(void) {
	error = 0x00;
	
	sprintf(display, "Channel 1:          ");
	LCD1602_SetCursor(0,0);
	LCD1602_Print(display);
	
	sprintf(display, "U:%.3fV  I:%.3fA  ", (double)results[0], (double)results[1]);
	LCD1602_SetCursor(0,1);
	LCD1602_Print(display);
	
	sprintf(display, "Channel 2:          ");
	LCD1602_SetCursor(0,2);
	LCD1602_Print(display);
	
	sprintf(display, "U:%.3fV  I:%.3fA  ", (double)results[2], (double)results[3]);
	LCD1602_SetCursor(0,3);
	LCD1602_Print(display);
	
	return error;
}

uint8_t print_settings(void) {
	error = 0x00;
	
	for(uint8_t i = 0; i < sizeof(settings)/sizeof(settings[1]); i++) {
		if(i == cursorPos) {
			sprintf(display, "> %s", settings[i]);
		}
		else sprintf(display, "  %s", settings[i]);
		LCD1602_SetCursor(0,i);
		LCD1602_Print(display);
	}
	
	return error;
}

uint8_t print_calibration(void) {
	error = 0x00;
	
	sprintf(display, "  Ch1:U=%.3fV     ", (double)results[0]);
	LCD1602_SetCursor(0,0);
	LCD1602_Print(display);
	
	sprintf(display, "  Ch2:U=%.3fV     ", (double)results[2]);
	LCD1602_SetCursor(0,1);
	LCD1602_Print(display);
	
	switch(cursorPos) {
		case 1: 
			sprintf(display, "> div=%.5f", (double)div_voltage);
			LCD1602_SetCursor(0,2);
			LCD1602_Print(display);
			break;
		case 2:
			sprintf(display, "> offset=%.5f", (double)offset_voltage_amp);
			LCD1602_SetCursor(0,2);
			LCD1602_Print(display);
			break;
	}
	
	return error;
}

uint8_t update_readout(void) {
	error = 0x00;
	
	if(button) {
		active_screen = SETTINGS;
		LCD1602_ClearAll();
		button = 0;
	}
	return error;
}

uint8_t update_settings(void) {
	error = 0x00;
	
	if(button && cursorPos == 0) {
		active_screen = READOUT;
		LCD1602_ClearAll();
		button = 0;
	}
	
	else if(button) {
		active_screen = CALIBRATION;
		LCD1602_ClearAll();
		button = 0;
	}
	if(cursorPos > 0 && left) {
		cursorPos--;
		left = 0;
	}
	if(cursorPos < (sizeof(settings)/sizeof(settings[1]) - 1) && right) {
		cursorPos++;
		right = 0;
	}
	return error;
}

uint8_t update_calibration(void) {
	error = 0x00;
	
	if(button) {
		active_screen = SETTINGS;
		LCD1602_ClearAll();
		
		save_calibration();
		
		button = 0;
	}
	switch(cursorPos) {
		case 1: 
			if(left) {
				div_voltage -= 0.001f;
				left = 0;
			}
			else if(right) {
				div_voltage += 0.001f;
				right = 0;
			}
			break;
		case 2:
			if(left) {
				offset_voltage_amp -= 0.005f;
				left = 0;
			}
			else if(right) {
				offset_voltage_amp += 0.005f;
				right = 0;
			}
			break;
	}
	return error;
}

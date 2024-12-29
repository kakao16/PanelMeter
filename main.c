
#include "MKL05Z4.h"

#include "lcd1602.h"

#include <stdio.h>

volatile float adc_volt_coeff = (float)((float)2.897 / 4095);

int main(void) {
	char display[21];
	LCD1602_Init();
	LCD1602_Backlight(TRUE);
	
	for(uint8_t n = 0; n < 4; n++) {
		sprintf(display, "Line %d test 12345678", n);
		LCD1602_SetCursor(0,n);
		LCD1602_Print(display);
	}
	
	return 0;
}

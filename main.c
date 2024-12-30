
#include "main.h"

#include "MKL05Z4.h"

#include "lcd1602.h"
#include "ADC.h"
#include "pit.h"

#include <stdio.h>

static volatile float adc_volt_coeff = (float)((float)2.897 / 4095);
static volatile uint8_t result_ok = 0;
static volatile uint32_t temp;
static volatile float result;
static volatile uint8_t channel = 0;

int main() {
	char display[21];
	LCD1602_Init();
	LCD1602_Backlight(TRUE);
	
	for(uint8_t n = 0; n < 4; n++) {
		sprintf(display, "Line %d - test", n);
		LCD1602_SetCursor(0,n);
		LCD1602_Print(display);
	}
	
	if(ADC_Init()) {
		sprintf(display,"ADC calibration err");
		LCD1602_SetCursor(0,0);
		LCD1602_Print(display);
		while(1);
	}
	
	ADC0->SC1[0] = ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(3);

	PIT_Init();							// Inicjalizacja licznika PIT0
	
	LCD1602_ClearAll();
	while(1) {
		if(result_ok) {
			result = result*adc_volt_coeff;		
			sprintf(display,"U_u=%.5fV", result);
			LCD1602_SetCursor(0,0);
			LCD1602_Print(display);

			result_ok = 0;
		}
	}
}

void ADC0_IRQHandler() {	
	temp = ADC0->R[0];	// Odczyt danej i skasowanie flagi COCO
	if(!result_ok)				// Sprawdz, czy result skonsumowany przez petle glówna
	{
		result = (float)temp;			// Wyslij nowa dana do petli glównej
		result_ok = 1;
	}
}

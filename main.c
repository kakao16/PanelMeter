/**
 * @file main.c
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing main function loop.
 * @ver 1.0
 */

#include "main.h"

static volatile uint8_t result_ok = 0;
static volatile float result;

static const float adc_volt_coeff = 2.897f / 4095.0f;
static uint8_t measurement_cnt = 0;
static const uint8_t measurements[] = {
	VOLTAGE_1_CH, 
	CURRENT_1_CH, 
	VOLTAGE_2_CH, 
	CURRENT_2_CH
};

int main() {
	char display[21];
	LCD1602_Init();
	LCD1602_Backlight(TRUE);
	
	if(ADC_Init()) {
		sprintf(display,"ADC calibration");
		LCD1602_SetCursor(0,0);
		LCD1602_Print(display);
		
		printf(display,"failed");
		LCD1602_SetCursor(0,0);
		LCD1602_Print(display);
		
		while(1);
	}
	
	ADC0->SC1[0] = ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(3);

	PIT_Init();
	
	LCD1602_ClearAll();
	while(1) {
		if(result_ok) {
			result = result*adc_volt_coeff;
			switch(measurement_cnt) {
				case 0:
					sprintf(display,"U1=%.4fV", result);
					break;
				case 1:
					sprintf(display,"I1=%.4fV", result);
					break;
				case 2:
					sprintf(display,"U2=%.4fV", result);
					break;
				case 3:
					sprintf(display,"I2=%.4fV", result);
					break;
			}
			
			if(measurement_cnt < 4) {
				LCD1602_SetCursor(0,measurement_cnt);
				LCD1602_Print(display);
				measurement_cnt++;
			}
			else {
				measurement_cnt = 0;
			}
			ADC0->SC1[0] = ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(measurements[measurement_cnt]);
			result_ok = 0;
		}
	}
}

void ADC0_IRQHandler() {	
	static uint32_t temp;
	temp = ADC0->R[0];				// Read ADC data
	if(!result_ok)
	{
		result = (float)temp;
		result_ok = 1;
	}
}

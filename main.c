/**
 * @file main.c
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing main function loop.
 * @ver 1.0
 */

#include "main.h"

static volatile uint8_t result_ok = 0;
static volatile uint32_t temp;
static volatile float temp_f;
static volatile float results[4];

static const float adc_volt_coeff = 2.897f / 4095.0f;
static uint8_t measurement_cnt = 0;
static char display[21];
static const uint8_t measurements[] = {
	VOLTAGE_1_CH,
	CURRENT_1_CH,
	VOLTAGE_2_CH,
	CURRENT_2_CH
};

int main() {
	
	LCD1602_Init();
	LCD1602_Backlight(TRUE);
	
	if(ADC_Init()) {
		sprintf(display,"ADC calibration");
		LCD1602_SetCursor(0,0);
		LCD1602_Print(display);
		
		sprintf(display,"failed");
		LCD1602_SetCursor(0,1);
		LCD1602_Print(display);
		
		while(1);
	}
	
	ADC0->SC1[0] = ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(3);

	PIT_Init();
	
	LCD1602_ClearAll();
	while(1) {
		if(result_ok) {
			temp_f = temp_f*adc_volt_coeff;
			switch(measurement_cnt) {
				case 0:
					results[0] = temp_f * 5.0f * 0.03387f;
					break;
				case 1:
					results[1] = temp_f * 20.0f * 0.05f;
					break;
				case 2:
					results[2] = temp_f * 5.0f * 0.03387f;
					break;
				case 3:
					results[3] = temp_f * 20.0f * 0.05f;
					break;
			}
			
			if(measurement_cnt < 4) {
				measurement_cnt++;
			}
			else {
				print_readout();
				measurement_cnt = 0;
			}
			ADC0->SC1[0] = ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(measurements[measurement_cnt]);
			result_ok = 0;
		}
	}
}

void ADC0_IRQHandler() {	
	temp = ADC0->R[0];					// Read ADC data
	if(!result_ok)
	{
		temp_f = (float)temp;
		result_ok = 1;
	}
}

uint8_t print_readout(void) {
	sprintf(display, "Channel 1:          ");
	LCD1602_SetCursor(0,0);
	LCD1602_Print(display);
	
	sprintf(display, "U:%.3fV  I:%.3fA  ", results[0], results[1]);
	LCD1602_SetCursor(0,1);
	LCD1602_Print(display);
	
	sprintf(display, "Channel 2:          ");
	LCD1602_SetCursor(0,2);
	LCD1602_Print(display);
	
	sprintf(display, "U:%.3fV  I:%.3fA  ", results[2], results[3]);
	LCD1602_SetCursor(0,3);
	LCD1602_Print(display);
	
	return 0;
}

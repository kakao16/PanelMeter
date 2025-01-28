/**
 * @file main.c
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing definitions of main function, interrut handlers, helper functions and variables.
 * @version 1.0
 */

#include "main.h"

/**
 * ADC flags, values and constants.
 */
static volatile uint8_t result_ready = 0;
static volatile uint32_t temp;
static volatile float temp_f;

/**
 * Array with all used adc channels.
 */
static const uint8_t measurements[] = {
	VOLTAGE_1_CH,
	CURRENT_1_CH,
	VOLTAGE_2_CH,
	CURRENT_2_CH
};

int main() {
	LCD1602_Init();
	LCD1602_Backlight(TRUE);
	LCD1602_ClearAll();
	
	load_calibration();
	
	if(ADC_Init()) {
		sprintf(display,"ADC calibration");
		LCD1602_SetCursor(0,0);
		LCD1602_Print(display);
		
		sprintf(display,"failed");
		LCD1602_SetCursor(0,1);
		LCD1602_Print(display);
		
		while(1);
	}
	
	EEPROM_Init();
	
	Encoder_Init();
	Encoder_Int_Enable();
	
	PIT_Init();
	
	/* Program loop */
	while(1) {
		if(active_screen != SETTINGS) {
			for(uint8_t cnt = 0; cnt < 4; cnt++) {
				ADC0->SC1[0] = 	ADC_SC1_AIEN_MASK | 								/* Keep ADC enabled */
												ADC_SC1_ADCH(measurements[cnt]); 		/* Change ADC channel */
				while(!result_ready) __NOP(); 											/* Wait for new measurement */
				temp_f = temp_f*adc_volt_coeff;
				
				/* Calculate and save measurement results */
				if(cnt % 2) {
					results[cnt] = calculate_current(temp_f);
				}
				else {
					results[cnt] = calculate_voltage(temp_f);
				}
				result_ready = 0;
			}
		}
		switch(active_screen){
			case READOUT:
				print_readout();
				update_readout();
				break;
			
			case SETTINGS:
				print_settings();
				update_settings();
				break;
			
			case CALIBRATION:
				print_calibration();
				update_calibration();
				break;
		}
	}
}

void ADC0_IRQHandler() {	
	temp = ADC0->R[0];						/* Read ADC data */
	if(!result_ready)
	{
		temp_f = (float)temp;
		result_ready = 1;
	}
}

float calculate_voltage(float voltage_adc) {
	return ((voltage_adc / div_input) - offset_voltage_amp) / (div_voltage * gain_voltage_amp);
}

float calculate_current(float voltage_adc) {
	return voltage_adc / (current_shunt * gain_current_amp * div_input);
}

void PORTA_IRQHandler(void) {
	if(PTB->PDIR & ENC_B_MASK) {
		right = 1;
	}
	
	PORTA->ISFR |= ENC_A_MASK;
	NVIC_ClearPendingIRQ(PORTA_IRQn);
}

void PORTB_IRQHandler(void) {
	if(PTA->PDIR & ENC_A_MASK) {
		left = 1;
	}

	PORTB->ISFR |= ENC_B_MASK | BUTTON_MASK;	
	NVIC_ClearPendingIRQ(PORTB_IRQn);
}

void NMI_Handler(void) {
	if(!button) button = 1;
}

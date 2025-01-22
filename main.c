/**
 * @file main.c
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing main function loop.
 * @ver 1.0
 */

#include "main.h"

//----------------------------------------------
// ADC flags, values and constants
//----------------------------------------------
static volatile uint8_t result_ready = 0;

static volatile uint32_t temp;
static volatile float temp_f;

static const float adc_volt_coeff = 2.897f / 4095.0f;
static const uint8_t measurements[] = {
	VOLTAGE_1_CH,
	CURRENT_1_CH,
	VOLTAGE_2_CH,
	CURRENT_2_CH
};

//----------------------------------------------
// Buffers for display
//----------------------------------------------
static char display[21];
static float results[4];

//----------------------------------------------
// Analog path constants
//----------------------------------------------
static const float div_voltage = 94.0f / (2600.0f + 94.0f);
static const float gain_voltage_amp = 5.0f;
static const float offset_voltage_amp = 1.78f;

static const float current_shunt = 0.05f;
static const float gain_current_amp = 20.0f;

static const float div_input = 33.0f / (20.0f + 33.0f);

//----------------------------------------------
// Encoder flags
//----------------------------------------------
static volatile uint8_t B_first = 0;
static volatile uint8_t A_first = 0;

static volatile uint8_t right = 0;
static volatile uint8_t left = 0;

static volatile uint8_t button = 0;

int main() {
	LCD1602_Init();
	LCD1602_Backlight(TRUE);
	LCD1602_ClearAll();
	
	if(ADC_Init()) {
		sprintf(display,"ADC calibration");
		LCD1602_SetCursor(0,0);
		LCD1602_Print(display);
		
		sprintf(display,"failed");
		LCD1602_SetCursor(0,1);
		LCD1602_Print(display);
		
		while(1);
	}
	
	Encoder_Init();
	Encoder_Int_Enable();
	
	// Start ADC from first measurement
	uint8_t measurement_cnt = 0;
	ADC0->SC1[measurement_cnt] = ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(3);
	PIT_Init();
	
	//----------------------------------------------
	// Program loop
	//----------------------------------------------
	while(1) {
		if(result_ready) {
			temp_f = temp_f*adc_volt_coeff;
			switch(measurement_cnt) {
				case 0:
					results[0] = calculate_voltage(temp_f);
					break;
				case 1:
					results[1] = calculate_current(temp_f);
					break;
				case 2:
					results[2] = calculate_voltage(temp_f);
					break;
				case 3:
					results[3] = calculate_current(temp_f);
					break;
			}
			if(measurement_cnt < 4) {
				measurement_cnt++;
			}
			else {
				print_readout();
				measurement_cnt = 0;
			}
			
			// Change ADC channel after measurement
			ADC0->SC1[0] = ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(measurements[measurement_cnt]);
			result_ready = 0;
		}
		
	}
}

void ADC0_IRQHandler() {	
	temp = ADC0->R[0];						// Read ADC data
	if(!result_ready)
	{
		temp_f = (float)temp;
		result_ready = 1;
	}
}

uint8_t print_readout(void) {
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
	
	return 0;
}

float calculate_voltage(float voltage_adc) {
	return ((voltage_adc / div_input) - offset_voltage_amp) / (div_voltage * gain_voltage_amp);
}

float calculate_current(float voltage_adc) {
	return voltage_adc / (current_shunt * gain_current_amp * div_input);
}

void PORTA_IRQHandler(void) {
	if(B_first) {
		left = 1;
		A_first = 0;
		B_first = 0;
	}
	else {
		A_first = 1;
	}

	// Clear interrupt register
	PORTA->ISFR |= ENC_A_MASK;	
	NVIC_ClearPendingIRQ(PORTA_IRQn);
}

void PORTB_IRQHandler(void) {
	if(A_first) {
		right = 1;
		A_first = 0;
		B_first = 0;
	}
	else {
		B_first = 1;
	}

	// Clear interrupt register
	PORTB->ISFR |= ENC_B_MASK;
	NVIC_ClearPendingIRQ(PORTB_IRQn);
}

void NMI_Handler(void) {
	if(!button) button = 1;
}

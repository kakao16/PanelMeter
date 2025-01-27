/**
 * @file ADC.c
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing definitions for ADC module. 
 * @version 1.0
 * Based on file provided for tutorials.
 */

#include "ADC.h"

static uint8_t error;

uint8_t ADC_Init(void) {
	error = 0x00;
	
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;          // ADC0 clock enable
	
	// Clock gate configuration for					
	// Port A 
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	// Port B 	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;					
	
	// Pin configuration for adc0
	// Port A 
	PORTA->PCR[VOLTAGE_1_PIN]	|= PORT_PCR_MUX(0);
	PORTA->PCR[CURRENT_1_PIN]	|= PORT_PCR_MUX(0);
	// Port B
	PORTB->PCR[VOLTAGE_2_PIN] |= PORT_PCR_MUX(0);			
	PORTB->PCR[CURRENT_2_PIN] |= PORT_PCR_MUX(0);
	
	// ADC0 config for calibration
	ADC0->CFG1 =	ADC_CFG1_ADICLK(ADICLK_BUS_2) | 			// Input clk equal to BUS/2 = 10.49MHz, 
								ADC_CFG1_ADIV(ADIV_4) | 							// divided by 4 so ADCK = 2621440Hz,
								ADC_CFG1_ADLSMP_MASK;									// long sample time selected,
	ADC0->CFG2 = ADC_CFG2_ADHSC_MASK;										// High speed conversion enabled
	ADC0->SC3  = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);		// Averege from 32 samples
	
	ADC0->SC3 |= ADC_SC3_CAL_MASK;											// Start calibration
	while(ADC0->SC3 & ADC_SC3_CAL_MASK);								// Wait for calibration to finish
	
	if(ADC0->SC3 & ADC_SC3_CALF_MASK)										// Check for calibration error
	{
	  ADC0->SC3 |= ADC_SC3_CALF_MASK;
		error = I2C_ERR_CALIBRATION;
	  return error;
	}

	uint16_t cal_temp;
	cal_temp = 0x00;
	cal_temp += ADC0->CLP0;
	cal_temp += ADC0->CLP1;
	cal_temp += ADC0->CLP2;
	cal_temp += ADC0->CLP3;
	cal_temp += ADC0->CLP4;
	cal_temp += ADC0->CLPS;
	cal_temp += ADC0->CLPD;
	cal_temp /= 2;
	cal_temp |= 0x8000;                       					// MSB set to 1
	ADC0->PG = ADC_PG_PG(cal_temp);           					// Value stored to plus-side gain register
	
	// ADC0 config for normal operation
	ADC0->SC1[0] = ADC_SC1_ADCH(31);										// Disable ADC
	ADC0->CFG1 =	ADC_CFG1_ADICLK(ADICLK_BUS_2) | 			// Input clk equal to BUS/2 = 10.49MHz, 
								ADC_CFG1_ADIV(ADIV_1) | 							// divide by 1 so ADCK = 10.49MHz, 
								ADC_CFG1_ADLSMP_MASK | 								// long sample time selected,
								ADC_CFG1_MODE(MODE_12);								// set to 12 bit resolution
	ADC0->CFG2 |= ADC_CFG2_ADHSC_MASK;									// High speed conversion enabled
	ADC0->SC3  = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(2);		// Averege from 16 samples
	
	// ADC trigger config
	ADC0->SC2 |= ADC_SC2_ADTRG_MASK;										// Hardwear trigger selected
	SIM->SOPT7 |= SIM_SOPT7_ADC0ALTTRGEN_MASK | 	
								SIM_SOPT7_ADC0TRGSEL(4);							// ADC0 triggered from PIT0
	NVIC_ClearPendingIRQ(ADC0_IRQn);
	NVIC_EnableIRQ(ADC0_IRQn);
	
	return error;
}


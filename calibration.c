/**
 * @file calibration.c
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief file containing calibration variables definitions.
 * @ver 1.0
 */
 
#include "calibration.h"

//----------------------------------------------
// Analog path constants
//----------------------------------------------
const float adc_volt_coeff = ADC_VOLT_COEFF;

const float gain_voltage_amp = GAIN_VOLATAGE_AMP;

const float current_shunt = CURRENT_SHUNT;
const float gain_current_amp = GAIN_CURRENT_AMP;

const float div_input = DIV_INPUT;

//----------------------------------------------
// Analog path values for calibration
//----------------------------------------------
float div_voltage = DIV_VOLTAGE;
float offset_voltage_amp = OFFSET_VOTAGE_AMP;

//----------------------------------------------
// EEPROM operations error handler
//----------------------------------------------
static uint8_t error;

static uint8_t address_pointer;

static uint8_t memory_programmed_flag;

uint8_t load_calibration(void) {
	error = 0;
	address_pointer = 0;
	
	error |= EEPROM_Read_byte(&address_pointer, &memory_programmed_flag);
	if(memory_programmed_flag == MEMORY_PROGRAMMED) {
		error |= EEPROM_Read_f(&address_pointer, &div_voltage);
		error |= EEPROM_Read_f(&address_pointer, &offset_voltage_amp);
	}
	
	return error;
}

uint8_t save_calibration(void) {
	error = 0;
	address_pointer = 0;
	
	memory_programmed_flag = MEMORY_PROGRAMMED;
	error |= EEPROM_Write_byte(&address_pointer, memory_programmed_flag);
	
	error |= EEPROM_Write_f(&address_pointer, div_voltage);
	error |= EEPROM_Write_f(&address_pointer, offset_voltage_amp);
	
	
	return error;
}

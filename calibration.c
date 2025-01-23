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

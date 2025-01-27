/**
 * @file calibration.h
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing nominal values and global variable declaration.
 * @ver 1.0
 */

#include "MKL05Z4.h"
#include "eeprom.h"

#ifndef CALIBRATION_H
#define CALIBRATION_H

//----------------------------------------------
// Nominal values of constants
//----------------------------------------------
#define ADC_VOLT_COEFF 2.897f / 4095.0f
#define GAIN_VOLATAGE_AMP 5.0f
#define CURRENT_SHUNT 0.05f
#define GAIN_CURRENT_AMP 20.0f
#define DIV_INPUT	33.0f / (20.0f + 33.0f)

//----------------------------------------------
// Nominal values of calibration values
//----------------------------------------------
#define DIV_VOLTAGE 94.0f / (2600.0f + 94.0f)
#define OFFSET_VOTAGE_AMP 1.97f

//----------------------------------------------
// Value to check if epprom was programmed
//----------------------------------------------
#define MEMORY_PROGRAMMED 0x50

//----------------------------------------------
// Value to check if epprom was programmed
//----------------------------------------------
#define CALIBRATION_ADDRESS 0x01

//----------------------------------------------
// Constants used for calibration
//----------------------------------------------
extern const float adc_volt_coeff;

extern const float gain_voltage_amp;

extern const float current_shunt;
extern const float gain_current_amp;

extern const float div_input;

//----------------------------------------------
// Variables used for calibration
//----------------------------------------------
extern float div_voltage;
extern float offset_voltage_amp;

/**
 * @brief Loads calibration values from EEPROM.
 * @return Error.
 */
uint8_t load_calibration(void);

/**
 * @brief Saves calibration values to EEPROM.
 * @return Error.
 */
uint8_t save_calibration(void);

#endif

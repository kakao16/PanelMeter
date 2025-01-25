/**
 * @file eeprom.h
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File function declaration for eeprom.
 * @ver 1.0
 */

#include "i2c.h"

#ifndef EEPROM_H
#define EEPROM_H

/**
 * @brief Write float value to eeprom.
 * @return Errors.
 */
uint8_t EEPROM_Init(void);

/**
 * @brief Write float value to eeprom.
 * @param Memory address.
 * @param Value to write.
 * @return Errors.
 */
uint8_t EEPROM_Write_f(uint8_t address, float value);

/**
 * @brief Read float value from eeprom.
 * @param Memory address.
 * @param Variable to write to.
 * @return Errors.
 */
uint8_t EEPROM_Read_f(uint8_t address, float *value);

#endif

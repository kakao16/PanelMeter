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

#define EEPROM_ADDRESS 0x50

/**
 * @brief Write float value to eeprom.
 * @return Errors.
 */
uint8_t EEPROM_Init(void);

/**
 * @brief Write a byte to eeprom.
 * @param Memory address.
 * @param Byte to write to memory.
 * @return Errors.
 */
uint8_t EEPROM_Write_byte(uint8_t address, uint8_t value);

/**
 * @brief Read a byte from eeprom.
 * @param Memory address.
 * @param Variable to write to from memory.
 * @return Errors.
 */
uint8_t EEPROM_Read_byte(uint8_t address, uint8_t* value);

/**
 * @brief Write float value to eeprom.
 * @param Memory address.
 * @param Float value to write to memory.
 * @return Errors.
 */
uint8_t EEPROM_Write_f(uint8_t address, float value);

/**
 * @brief Read float value from eeprom.
 * @param Memory address.
 * @param Variable to write to from memory.
 * @return Errors.
 */
uint8_t EEPROM_Read_f(uint8_t address, float* value);

#endif

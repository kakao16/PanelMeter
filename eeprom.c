/**
 * @file eeprom.c
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File function definitions for eeprom.
 * @ver 1.0
 */
 
#include "eeprom.h"

uint8_t EEPROM_Init(void) {
	I2C_Init();
	return 0;
}

uint8_t EEPROM_Write_f(uint8_t address, float value) {
	return 1;
}

uint8_t EEPROM_Read_f(uint8_t address, float *value) {
	return 1;
}

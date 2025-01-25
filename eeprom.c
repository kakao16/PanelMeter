/**
 * @file eeprom.c
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File function definitions for eeprom.
 * @ver 1.0
 */
 
#include "eeprom.h"

static uint8_t eeprom_address = EEPROM_ADDRESS;
static uint8_t error;

uint8_t EEPROM_Init(void) {
	error = 0x00;
	I2C_Init();
	return error;
}

uint8_t EEPROM_Write_byte(uint8_t address, uint8_t value) {
	error = 0x00;
	error = I2C_WriteReg(eeprom_address, address, value);
	return error;
}

uint8_t EEPROM_Read_byte(uint8_t address, uint8_t* value) {
	error = 0x00;
	error = I2C_ReadReg(eeprom_address, address, value);
	return error;
}

uint8_t EEPROM_Write_f(uint8_t address, float value) {
	error = 0x00;
	
	
	
	return error;
}

uint8_t EEPROM_Read_f(uint8_t address, float* value) {
	error = 0x00;
	
	return error;
}

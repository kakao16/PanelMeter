/**
 * @file menu.h
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing declarations of functions for menu logic.
 * @version 1.0
 */

#include "MKL05Z4.h"
#include "lcd1602.h"
#include "encoder.h"
#include "calibration.h"

#include "eeprom.h"

#include <stdio.h>

#ifndef menu_h
#define menu_h

extern char display[21]; /** Global buffer for display. */
extern float results[4]; /** Global buffer with measured values. */

/**
 * @brief All possible menu screens.
 */
enum screen {
	READOUT,
	SETTINGS,
	CALIBRATION
};
/**
 * @brief Currently displayed screen.
 */
extern enum screen active_screen;

/**
 * @brief Prints all measurements on screen.
 * @return Error. 
 */
uint8_t print_readout(void);

/**
 * @brief Prints list of settings on screen.
 * @return Error. 
 */
uint8_t print_settings(void);

/**
 * @brief Prints calibration menu on screen.
 * @return Error. 
 */
uint8_t print_calibration(void);

/**
 * @brief Updates readout screen logic.
 * @return Error. 
 */
uint8_t update_readout(void);

/**
 * @brief Updates readout screen logic.
   @return Error. 
 */
uint8_t update_settings(void);

/**
 * @brief Updates readout screen logic.
 * @return Error. 
 */
uint8_t update_calibration(void);

#endif

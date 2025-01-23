/**
 * @file menu.h
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing declarations of functions for menu logic.
 * @ver 1.0
 */

#include "MKL05Z4.h"
#include "lcd1602.h"
#include "encoder.h"
#include "calibration.h"

#include <stdio.h>

#ifndef menu_h
#define menu_h

//----------------------------------------------
// Global buffers for display
//----------------------------------------------
extern char display[21];
extern float results[4];

enum screen {
	READOUT,
	SETTINGS,
	CALIBRATION
};
extern enum screen active_screen;

/**
 * @brief Prints all measurements on screen.
 */
uint8_t print_readout(void);

/**
 * @brief Prints list of settings on screen.
 */
uint8_t print_settings(void);

/**
 * @brief Prints calibration menu on screen.
 */
uint8_t print_calibration(void);

/**
 * @brief Updates readout screen logic.
 */
uint8_t update_readout(void);

/**
 * @brief Updates readout screen logic.
 */
uint8_t update_settings(void);

/**
 * @brief Updates readout screen logic.
 */
uint8_t update_calibration(void);

#endif

/**
 * @file pit.h
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing declarations for PIT module.
 * @ver 1.0
 * Based on file provided for tutorials.
 */

#include "MKL05Z4.h"

#ifndef pit_h
#define pit_h
#define BUS_CLOCK SystemCoreClock/2

/**
 * @brief PIT module initialization.
 */
void PIT_Init(void);

#endif

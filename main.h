/**
 * @file main.h
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief Header file containing declarations and includes of main loop.
 * @ver 1.0
 */

#include "MKL05Z4.h"

#include "lcd1602.h"
#include "ADC.h"
#include "pit.h"

#include <stdio.h>

int main(void);

/**
 * @brief Interrupt handler for ADC.
 */
void ADC0_IRQHandler(void);

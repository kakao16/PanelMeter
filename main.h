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
#include "encoder.h"

#include <stdio.h>

int main(void);

/**
 * @brief Interrupt handler for ADC.
 */
void ADC0_IRQHandler(void);

/**
 * @brief Prints all measurements on screen.
 */
uint8_t print_readout(void);

/**
 * @brief Calculates value of measured voltage.
 */
float calculate_voltage(float voltage_adc);

/**
 * @brief Calculates value of measured currnet.
 */
float calculate_current(float voltage_adc);

/**
 * @brief Interrupt handler for PORTA.
 */
void PORTA_IRQHandler(void);

/**
 * @brief Interrupt handler for PORTB.
 */
void PORTB_IRQHandler(void);

/**
 * @brief Non-maskable interrupt handler. Used for button press.
 */
void NMI_Handler(void);

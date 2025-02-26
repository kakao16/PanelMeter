/**
 * @file main.h
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing declarations of main function, interrut handlers and helper functions.
 * @version 1.0
 */

#include "MKL05Z4.h"

#include "lcd1602.h"
#include "ADC.h"
#include "pit.h"
#include "encoder.h"
#include "menu.h"
#include "calibration.h"

#include <stdio.h>

int main(void);

/**
 * @brief Interrupt handler for ADC.
 */
void ADC0_IRQHandler(void);

/**
 * @brief Calculates value of measured voltage.
 * @param Voltage read by the ADC.
 * @return Voltage value on meter input.
 */
float calculate_voltage(float voltage_adc);

/**
 * @brief Calculates value of measured current.
 * @param Voltage read by the ADC.
 * @return Current value flowing through the meter.
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



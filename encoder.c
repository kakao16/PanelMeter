/**
 * @file encoder.c
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing functions and flags definitions for rotary encoder. 
 * @ver 1.0
 */
 
 #include "encoder.h"
 
//----------------------------------------------
// Encoder flags
//----------------------------------------------
volatile uint8_t B_first = 0;
volatile uint8_t A_first = 0;

volatile uint8_t right = 0;
volatile uint8_t left = 0;

volatile uint8_t button = 0;
 
uint8_t Encoder_Init(void) {
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;			// PORTA clock enable
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;			// PORTB clock enable
	
	// Pins muxed for gpio
	PORTB->PCR[ENC_B] |= PORT_PCR_MUX(1);
	PORTA->PCR[ENC_A] |= PORT_PCR_MUX(1);
	PORTB->PCR[BUTTON] |= PORT_PCR_MUX(1);

	// Pins pull disable
	PORTB->PCR[ENC_B] &= ~PORT_PCR_PE_MASK;
	PORTA->PCR[ENC_A] &= ~PORT_PCR_PE_MASK;
	PORTB->PCR[BUTTON] &= ~PORT_PCR_PE_MASK;
	
	return 0;
}

uint8_t Encoder_Int_Enable(void) {
	PORTB -> PCR[ENC_B] |= PORT_PCR_IRQC(EDGE_FALLING);		
	PORTA -> PCR[ENC_A] |= PORT_PCR_IRQC(EDGE_FALLING);		
	// Button uses NMI_b pin (PTB5)
	PORTB -> PCR[BUTTON] |= PORT_PCR_IRQC(EDGE_FALLING);
	
	// Interrupt configuration for
	// Port A
	NVIC_SetPriority(PORTA_IRQn, 3); 
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTA_IRQn);
	
	// Port B
	NVIC_SetPriority(PORTB_IRQn, 3); 
	NVIC_ClearPendingIRQ(PORTB_IRQn);
	NVIC_EnableIRQ(PORTB_IRQn);
	
	return 0;
}

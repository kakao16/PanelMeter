/**
 * @file encoder.h
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief File containing declarations and constants for rotary encoder. 
 * @ver 1.0
 */
 
 #include "MKL05Z4.h"
 
#ifndef encoder_h
#define encoder_h


#define EDGE_FALLING 0xa

//----------------------------------------------
// Pins used by encoder
//----------------------------------------------
#define ENC_B_MASK	(1<<1)		/* PORT B*/
#define ENC_A_MASK	(1<<11)		/* PORT A*/
// Button uses NMI_b pin (PTB5)
#define BUTTON_MASK	(1<<5)		/* PORT B*/

#define ENC_B				1					/* PORT B*/
#define ENC_A				11				/* PORT A*/
// Button uses NMI_b pin (PTB5)
#define BUTTON			5					/* PORT B*/

/**
 * @brief Rotary encoder initialization.
 */
uint8_t Encoder_Init(void);

/**
 * @brief Enable interrupts for rotary encoder.
 */
uint8_t Encoder_Int_Enable(void);

#endif

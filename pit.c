/**
 * @file pit.c
 * @author Stanislaw Kusiak
 * @date winter 2024/2025 semester
 * @brief Header file containing definitions for PIT module.
 * @ver 1.0
 * Based on file provided for tutorials.
 */

#include	"pit.h"

void PIT_Init(void)
{
	uint32_t tsv;
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;							// Clock PIT enabled
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;								// Enable PIT module
	//tsv=BUS_CLOCK;															// 1s interval
	//tsv=BUS_CLOCK/2;														// 0.5s interval
	tsv=BUS_CLOCK/10;														// 100ms interval
	//tsv=BUS_CLOCK/100;														// 10ms interval
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(tsv);		// Conter initial value
	PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TEN_MASK;		// Start counter
}

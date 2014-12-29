/*
 * stm32_systick.c
 *
 *  Created on: 14-06-2012
 *      Author: Tomek
 */

#include <stm32l/systick.h>
#include <stm32l/rcc.h>

/* enable system timer */
void SYSTICK_Cmd(int enable)
{
	/* enable/disable */
	if (enable) {
		SYSTICK->CSR |= SYSTICK_CSR_ENABLE | SYSTICK_CSR_TICKINT |
				SYSTICK_CSR_CLKSOURCE;
	} else {
		SYSTICK->CSR &= ~(SYSTICK_CSR_ENABLE | SYSTICK_CSR_TICKINT |
				SYSTICK_CSR_CLKSOURCE);
	}
}

/* set frequency */
void SYSTICK_SetFreq(int hz)
{
	rcc_clocks_t clocks;
	/* get clock settings */
	RCC_GetClocksFreq(&clocks);

	uint32_t reg = clocks.hclk_frequency / hz;
	/* validate parameters */
	SYSTICK->RVR = reg;
	/* reset current value */
	SYSTICK->CVR = 0;
}

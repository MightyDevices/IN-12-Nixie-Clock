/*
 * wwdg.c
 *
 *  Created on: 08-07-2012
 *      Author: Tomek
 */

#include <stm32l/wwdg.h>

/* Sets the WWDG Prescaler */
void WWDG_SetPrescaler(int prescaler)
{
	uint32_t tmpreg = 0;
	/* Clear WDGTB[1:0] bits */
	tmpreg = WWDG->CFR & ~0x000000c0;
	/* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
	tmpreg |= prescaler;
	/* Store the new value */
	WWDG->CFR = tmpreg;
}

/* @brief  Sets the WWDG window value */
void WWDG_SetWindowValue(uint8_t window_value)
{
	uint32_t tmpreg = 0;

	/* Clear W[6:0] bits */
	tmpreg = WWDG->CFR & ~0x7f;

	/* Set W[6:0] bits according to WindowValue value */
	tmpreg |= window_value;

	/* Store the new value */
	WWDG->CFR = tmpreg;
}

/* Enables WWDG and load the counter value*/
void WWDG_Enable(uint8_t counter)
{
	/* enable */
	WWDG->CR = 0x80 | counter;
}

/* Sets the WWDG counter value. */
void WWDG_SetCounter(uint8_t counter)
{
	/* Write to T[6:0] bits to configure the counter value, no need to do
	 a read-modify-write; writing a 0 to WDGA bit does nothing */
	WWDG->CR = counter & 0x7f;
}

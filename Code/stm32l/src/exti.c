/*
 * exti.c
 *
 *  Created on: 24-02-2013
 *      Author: Tomek
 */

#include <stm32l/exti.h>

/* reset registers */
void EXTI_DeInit(void)
{
	EXTI->IMR = 0x00000000;
	EXTI->EMR = 0x00000000;
	EXTI->RTSR = 0x00000000;
	EXTI->FTSR = 0x00000000;
	EXTI->PR = 0x00FFFFFF;
}

/* initialize exti */
void EXTI_Init(exti_init_t *init)
{
	/* disable */
	EXTI->IMR &= ~init->line;
	EXTI->EMR &= ~init->line;

	/* enable? */
	if (init->line_cmd) {
		/* rising falling configuration */
		if (init->trigger & EXTI_TRIGGER_RISING) {
			EXTI->RTSR |= init->line;
		}
		/* falling */
		if (init->trigger & EXTI_TRIGGER_FALLING) {
			EXTI->FTSR |= init->line;
		}

		/* enable interrupt */
		if (init->mode & EXTI_MODE_INTERRUPT) {
			EXTI->IMR |= init->line;
		}
		/* enable event */
		if (init->mode & EXTI_MODE_EVENT) {
			EXTI->EMR |= init->line;
		}
	}
}

/* initialize struct */
void EXTI_StructInit(exti_init_t *init)
{
	init->line = 0;
	init->mode = EXTI_MODE_INTERRUPT;
	init->trigger = EXTI_TRIGGER_FALLING;
	init->line_cmd = DISABLE;
}

/* generate sw interrupt */
void EXTI_GenerateSWInterrupt(uint32_t line)
{
	EXTI->SWIER |= line;
}

/* clear pending flag */
void EXTI_ClearFlag(uint32_t line)
{
	EXTI->PR = line;
}

/* Checks whether the specified EXTI line is asserted or not. */
uint32_t EXTI_GetITStatus(void)
{
	return EXTI->PR;
}

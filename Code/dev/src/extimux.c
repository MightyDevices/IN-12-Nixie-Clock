/*
 * extimux.c
 *
 *  Created on: 20-12-2014
 *      Author: Tomek
 */

#include <stm32l/nvic.h>
#include <stm32l/exti.h>
#include <dev/extimux.h>
#include <util/string.h>
#include <sys/err.h>

/* pointers to exti isr routines */
static exticb_t e[5];

/* exti multiplexer isr */
static void ExtiMux_Exti5_9Isr(void)
{
	/* get pending register */
	uint32_t pr = EXTI->PR;

	/* call exti routines */
	if ((pr & EXTI_PR_PR5) && e[0]) e[0]();
	if ((pr & EXTI_PR_PR6) && e[1]) e[1]();
	if ((pr & EXTI_PR_PR7) && e[2]) e[2]();
	if ((pr & EXTI_PR_PR8) && e[3]) e[3]();
	if ((pr & EXTI_PR_PR9) && e[4]) e[4]();
}

/* initialize exti */
int ExtiMux_Init(void)
{
	/* mask out all interrupts */
	EXTI->IMR &= ~(EXTI_IMR_MR5 | EXTI_IMR_MR6 | EXTI_IMR_MR7 |
			EXTI_IMR_MR8 | EXTI_IMR_MR9);

	/* clear all routines */
	memset(e, 0, sizeof(e));

	/* prepare interrupt vector */
	NVIC_SetInterruptVector(NVIC_EXTI5_9, ExtiMux_Exti5_9Isr);
	/* set priority */
	NVIC_SetInterruptPriority(NVIC_EXTI5_9, 2);
	/* enable interrupt */
	NVIC_EnableInterrupt(NVIC_EXTI5_9);

	/* report status */
	return EOK;
}

/* deinit exti muxer */
int ExtiMux_Deinit(void)
{
	/* enable interrupt */
	NVIC_DisableInterrupt(NVIC_EXTI5_9);
	/* mask out all interrupts */
	EXTI->IMR &= ~(EXTI_IMR_MR5 | EXTI_IMR_MR6 | EXTI_IMR_MR7 |
			EXTI_IMR_MR8 | EXTI_IMR_MR9);

	/* report status */
	return EOK;
}

/* register interrupt callback */
void ExtiMux_Register(uint8_t num, exticb_t cb)
{
	/* disable interrupt */
	EXTI->IMR &= ~(1 << (num + 5));
	/* set new vector */
	e[num] = cb;
	/* re-enable interrupt */
	EXTI->IMR |= (1 << (num + 5));
}

/* unregister routine */
void ExtiMux_Unregister(uint8_t num)
{
	/* disable interrupt */
	EXTI->IMR &= ~(1 << (num + 5));
}


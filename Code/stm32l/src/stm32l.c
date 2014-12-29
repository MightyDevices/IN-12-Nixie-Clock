/*
 * stm32.c
 *
 *  Created on: 14-06-2012
 *      Author: Tomek
 */


/* enable interrupts */
void STM32_EnableInterrupts(void)
{
	asm volatile ("cpsie i");
}

void STM32_DisableInterrupts(void)
{
	asm volatile ("cpsid i");
}

/*
 * hsi.c
 *
 *  Created on: 23-04-2014
 *      Author: Tomek
 */

#include <stm32l/rcc.h>
#include <stm32l/timer.h>
#include <sys/err.h>

/* hsi init */
int HSI_Init(void)
{
	/* enable lsi clock */
	RCC->CR |= RCC_CR_HSION;
	/* wait till it settles */
	while ((RCC->CR & RCC_CR_HSIRDY) == 0);

	/* report status */
	return EOK;
}

/* deinitialize hsi */
int HSI_Deinit(void)
{
	/* enable lsi clock */
	RCC->CR &= ~RCC_CR_HSION;
	/* wait till it settles */
	while (RCC->CR & RCC_CR_HSIRDY);

	/* report status */
	return EOK;
}

/* enable disable lsi */
void HSI_Cmd(uint8_t state)
{
	/* lsi ready and on bits */
	bitband_t hsi_rd = BITBAND_PERIPH(&RCC->CR, 1);
	bitband_t hsi_on = BITBAND_PERIPH(&RCC->CR, 0);

	/* apply new state */
	*hsi_on = state;
	/* waitstate, loops till change takes place */
	while (*hsi_rd != state);
}

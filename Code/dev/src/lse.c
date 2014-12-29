/*
 * lse.c
 *
 *  Created on: 13-12-2014
 *      Author: Tomek
 */

#include <stm32l/rcc.h>
#include <stm32l/pwr.h>
#include <sys/err.h>
#include <dev/lse.h>

/* initialize lse oscillator */
int LSE_Init(void)
{
	/* enable power control */
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	/* enable access to lse configuration */
	PWR->CR |= PWR_CR_DBP;

	/* enable lse oscillator */
	LSE_Cmd(1);

	/* report status */
	return EOK;
}

/* enable/disable lse */
void LSE_Cmd(uint8_t state)
{
	/* lse bits */
	bitband_t lseon = BITBAND_PERIPH(&RCC->CSR, 8);
	bitband_t lserdy = BITBAND_PERIPH(&RCC->CSR, 9);

	/* enable access to lse configuration */
	PWR->CR |= PWR_CR_DBP;
	/* set state */
	*lseon = state != 0;
	/* wait till oscillator is ready */
	while (*lserdy != *lseon);
	/* disable access */
	PWR->CR &= ~PWR_CR_DBP;
}

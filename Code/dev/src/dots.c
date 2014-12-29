/*
 * dots.c
 *
 *  Created on: 18-12-2014
 *      Author: Tomek
 */

#include <stm32l/rcc.h>
#include <stm32l/gpio.h>
#include <sys/err.h>
#include <dev/dots.h>
#include <stdint.h>

static bitband_t dn = BITBAND_PERIPH(&GPIOC->ODR, 13);
static bitband_t up = BITBAND_PERIPH(&GPIOH->ODR, 1);

/* initialize dots */
int Dots_Init(void)
{
	/* initialize gpios */
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOHEN;

	/* reset port c */
	GPIOC->MODER &= ~GPIO_MODER_MODER13;
	/* reset port h */
	GPIOH->MODER &= ~GPIO_MODER_MODER1;

	GPIOC->MODER |= GPIO_MODER_MODER13_0;
	GPIOH->MODER |= GPIO_MODER_MODER1_0;

	/* reset dots */
	*dn = *up = 0;

	/* return status */
	return EOK;
}

/* de-initialize dots */
int Dots_Deinit(void)
{
	/* reset port c */
	GPIOC->MODER |= GPIO_MODER_MODER13;
	/* reset port h */
	GPIOH->MODER |= GPIO_MODER_MODER1;

	/* return status */
	return EOK;
}

/* set dots */
void Dots_Set(uint8_t mask)
{
	/* set dots */
	*dn = (mask & DOTS_DN) != 0;
	*up = (mask & DOTS_UP) != 0;
}

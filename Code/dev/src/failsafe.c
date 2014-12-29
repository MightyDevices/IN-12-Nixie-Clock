/*
 * failsafe.c
 *
 *  Created on: 20-12-2014
 *      Author: Tomek
 */

#include <stm32l/rcc.h>
#include <stm32l/gpio.h>
#include <stm32l/syscfg.h>
#include <stm32l/exti.h>
#include <stm32l/nvic.h>
#include <sys/err.h>
#include <sys/time.h>

/* initialize failsafe */
int Failsafe_Init(void)
{
	/* enable gpiob */
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	/* configure gpios */
	GPIOB->MODER &= ~GPIO_MODER_MODER5;
	/* enable pull-down */
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR5_1;

	/* report status */
	return EOK;
}

/* deinitialize failsafe */
int Failsafe_Deinit(void)
{
	/* configure gpios */
	GPIOB->MODER |= GPIO_MODER_MODER5;
	/* disable pull-down */
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR5;

	/* report status */
	return EOK;
}

/* power supply was interrupted? */
int FailSafe_IsPowerInterrupted(void)
{
	/* pin status */
	bitband_t pb5 = BITBAND_PERIPH(&GPIOB->IDR, 5);

	/* report status */
	return !(*pb5);
}


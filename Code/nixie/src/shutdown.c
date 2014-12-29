/*
 * shutdown.c
 *
 *  Created on: 21-12-2014
 *      Author: Tomek
 */
#include <stm32l/rcc.h>
#include <stm32l/gpio.h>
#include <stm32l/syscfg.h>
#include <stm32l/exti.h>
#include <lifecycle/lc.h>
#include <dev/power.h>

/* polling in shutdown mode */
void NixieShutdown_Poll(void)
{
	/* enable gpiob */
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	/* enable sysconfig */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* configure gpios */
	GPIOB->MODER &= ~GPIO_MODER_MODER5;
	/* enable pull-down */
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR5_1;

	/* route signal */
	SYSCFG->EXTICR2 |= 1 << 4;
	/* prepare rising edge detection */
	EXTI->RTSR |= EXTI_RTSR_TR5;
	/* enable event generation */
	EXTI->EMR |= EXTI_EMR_MR5;

	/* bring the clock down */
	RCC_MSIRangeConfig(MSI_FREQ_65K536);
	/* sleep */
	Power_StandbyMode();
	/* restore clock */
	RCC_MSIRangeConfig(MSI_FREQ_4M194);

	/* prepare rising edge detection */
	EXTI->RTSR &= ~EXTI_RTSR_TR5;
	/* enable event generation */
	EXTI->EMR &= ~EXTI_EMR_MR5;
	/* route signal */
	SYSCFG->EXTICR2 &= ~(0xf << 4);

	/* disable pin */
	GPIOB->MODER |= GPIO_MODER_MODER5;

	/* exit shutdown mode */
	LC_SetMode(LC_MODE_RUN);
}

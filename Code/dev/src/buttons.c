/*
 * buttons.c
 *
 *  Created on: 20-12-2014
 *      Author: Tomek
 */

#include <stm32l/rcc.h>
#include <stm32l/gpio.h>
#include <stm32l/syscfg.h>
#include <stm32l/exti.h>
#include <stm32l/nvic.h>
#include <dev/buttons.h>
#include <dev/extimux.h>
#include <dev/systime.h>
#include <sys/err.h>
#include <sys/time.h>

/* glitch filtering timers */
static timer_t dt, ut;
/* pressed flags */
static volatile uint8_t flags;

/* button interrupt */
static void Buttons_Exti7Isr(void)
{
	/* get pending register */
	uint32_t pr = EXTI->PR & (EXTI_PR_PR7);
	/* clear pending bits */
	EXTI->PR = pr;

	/* lower button is pressed */
	if (pr & EXTI_PR_PR7) {
		/* check glitch timer */
		if (time - dt > 400) {
			/* set flag */
			flags |= BUTTONS_DN;
			/* kick timer */
			dt = time;
		}
	}
}

/* button interrupt */
static void Buttons_Exti8Isr(void)
{
	/* get pending register */
	uint32_t pr = EXTI->PR & (EXTI_PR_PR8);
	/* clear interrupt */
	EXTI->PR = pr;

	/* upper button is pressed */
	if (pr & EXTI_PR_PR8) {
		/* check glitch timer */
		if (time - ut > 400) {
			/* set flag */
			flags |= BUTTONS_UP;
			/* kick timer */
			ut = time;
		}
	}
}

/* initialize buttons */
int Buttons_Init(void)
{
	/* enable gpiob */
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	/* enable system configuration for interrupt routing */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* configure gpios */
	GPIOB->MODER &= ~(GPIO_MODER_MODER7 | GPIO_MODER_MODER8);
	/* enable pull-ups */
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR7_0 | GPIO_PUPDR_PUPDR8_0;

	/* wait for voltage to stabilize */
	SysTime_Delay(5);

	/* route signals to exti lines */
	SYSCFG->EXTICR2 |= 1 << 12; SYSCFG->EXTICR3 |= 1 << 0;
	/* configure exti lines to react on push downs */
	EXTI->FTSR |= EXTI_FTSR_TR7 | EXTI_FTSR_TR8;

	/* register interrupts */
	ExtiMux_Register(EXTIMUX_EXTI7, Buttons_Exti7Isr);
	ExtiMux_Register(EXTIMUX_EXTI8, Buttons_Exti8Isr);

	/* reset flags */
	flags = 0x00;

	/* report status */
	return EOK;
}

/* initialize buttons */
int Buttons_Deinit(void)
{
	/* disable pull-ups */
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR7 | GPIO_PUPDR_PUPDR8);
	/* disable inputs */
	GPIOB->MODER |= GPIO_MODER_MODER7 | GPIO_MODER_MODER8;

	/* reset exti configuration */
	EXTI->FTSR &= ~(EXTI_FTSR_TR7 | EXTI_FTSR_TR8);

	/* register interrupts */
	ExtiMux_Unregister(EXTIMUX_EXTI7);
	ExtiMux_Unregister(EXTIMUX_EXTI8);

	/* report status */
	return EOK;
}

/* buttons were pressed? */
uint8_t Buttons_GetStatus(void)
{
	uint8_t rc = flags;

	/* clear flags */
	if (rc)
		flags = 0;

	/* return status */
	return rc;
}

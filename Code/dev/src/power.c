/*
 * power.c
 *
 *  Created on: 28-11-2014
 *      Author: Tomek
 */

#include <stm32l/pwr.h>
#include <stm32l/rcc.h>
#include <stm32l/scb.h>
#include <stm32l/exti.h>
#include <stm32l/syscfg.h>
#include <stm32l/gpio.h>
#include <stm32l/nvic.h>
#include <sys/err.h>

#define DEBUG
#include <dev/debug.h>

/* power level detector init */
int Power_Init(void)
{
	/* enable power */
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	/* enable all gpios for configuring before low power mode */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN |
			RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOHEN;

	/* set for lowest consumption */
	GPIOA->MODER = 0xffffffff; GPIOB->MODER = 0xffffffff;
	/* set for lowest consumption */
	GPIOC->MODER = 0xffffffff; GPIOH->MODER = 0xffffffff;

	/* set outputs for lowest consumption */
	GPIOB->ODR = 0; GPIOC->ODR = 0;

	/* pull down configuration (ports a and b) */
	GPIOA->PUPDR = 0x00000000; GPIOB->PUPDR = 0x00000000;
	/* pull down configuration (ports a and b) */
	GPIOC->PUPDR = 0x00000000; GPIOH->PUPDR = 0x00000000;


	/* 1.8v core voltage */
	PWR->CR = PWR_CR_VOS_0;
	/* reset wake up pin functionality */
	PWR->CSR = 0;

	/* all ok */
	return EOK;
}

/* enter standby mode */
void Power_StandbyMode(void)
{
	/* clear wakeup flag, enter ultra low power mode */
	PWR->CR |= PWR_CR_CWUF | PWR_CR_ULP | PWR_CR_LPSDSR;
	/* Set SLEEPDEEP bit of Cortex System Control Register */
	SCB->SCR |= SCB_SCR_SLEEPDEEP;

	/* go to sleep, wait for wakeup event */
	asm volatile ("wfe");

	/* reset deep sleep bit */
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP;
	/* disable low power run */
	PWR->CR &= ~PWR_CR_ULP;

	/* perform system reset */
	//SCB->AIRCR = SCB_AIRCR_VECTKEYSTAT | SCB_AIRCR_SYSRESETREQ;
}

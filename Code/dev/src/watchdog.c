/*
 * watchdog.c
 *
 *  Created on: 12-06-2013
 *      Author: Tomek
 */

#include <stm32l/wwdg.h>
#include <stm32l/rcc.h>
#include <stm32l/nvic.h>
#include <dev/watchdog.h>
#include <sys/err.h>

/* watchdog prescaler */
#define WDG_PRESCALER						2

/* software prescaler */
static uint8_t cnt;

/* interrupt routine */
static void Watchdog_Isr(void)
{
	/* clear status */
	WWDG->SR = 0;
	/* still kickable :)*/
	if (cnt) {
		/* fill register */
		WWDG->CR = WWDG_CR_T;
		/* decrement counter */
		cnt--;
	}
}

/* initialize watchdog */
int Watchdog_Init(void)
{
	/* set counter */
	cnt = WDG_PRESCALER;

	/* enable watchdog */
	RCC->APB1ENR |= RCC_APB1ENR_WWDGEN;
	/* configure for max interval */
	WWDG->CR = WWDG_CR_WDGA | WWDG_CR_T;
	/* set up prescaler and interrupt */
	WWDG->CFR = WWDG_CFR_EWI | WWDG_CFR_WDGTB | WWDG_CFR_W;

	/* set up interrupt */
	NVIC_SetInterruptVector(NVIC_WWDG, Watchdog_Isr);
	/* set up priority */
	NVIC_SetInterruptPriority(NVIC_WWDG, 0);
	/* enable interrupt */
	NVIC_EnableInterrupt(NVIC_WWDG);

	/* what could possibly go wrong here */
	return EOK;
}

/* kick the dog! */
void Watchdog_Kick(void)
{
	/* fill counter */
	cnt = WDG_PRESCALER;
	/* fill register */
	WWDG->CR = WWDG_CR_T;
}

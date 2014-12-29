/*
 * systime.c
 *
 *  Created on: 11-06-2013
 *      Author: Tomek
 */

#include <sys/err.h>
#include <sys/time.h>
#include <stm32l/systick.h>
#include <stm32l/nvic.h>

/* system timer interrupt routine */
static void SysTime_Isr(void)
{
	/* just as simple as that! */
	time++;
}

/* reset time base */
int SysTime_Init(void)
{
	/* configure vector */
	NVIC_SetCoreExceptionVector(NVIC_SYSTICK, SysTime_Isr);
	/* set priority, to lowest possible */
	NVIC_SetExceptionPriority(NVIC_SYSTICK, 0xff);

	/* enable systick */
	SYSTICK->CSR = SYSTICK_CSR_ENABLE | SYSTICK_CSR_TICKINT |
			SYSTICK_CSR_CLKSOURCE;
	/* set interval to 1 ms */
	SYSTICK->RVR = 1048 * 4;

	/* not much could go wrong here */
	return EOK;
}

/* deinitialize system tick timer */
int SysTime_Deinit(void)
{
	/* disable clock */
	SYSTICK->CSR = 0;
	/* not much to do here */
	return EOK;
}

/* delay in ms */
void SysTime_Delay(timer_t ms)
{
	timer_t t = time;
	/* blocking wait */
	while (time - t < ms);
}

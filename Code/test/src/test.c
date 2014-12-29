/*
 * test.c
 *
 *  Created on: 04-05-2014
 *      Author: Tomek
 */

#include <stm32l/timer.h>
#include <sys/err.h>
#include <sys/time.h>

#define DEBUG
#include <dev/debug.h>

/* test timer */
static timer_t timer;

/* initialize tests */
int Test_Init(void)
{
	/* report status */
	return EOK;
}

/* de-initialize tests */
int Test_Deinit(void)
{
	/* report status */
	return EOK;
}

/* poll test routines */
void Test_Poll(void)
{
	if (time - timer >= 100) {
	}
}

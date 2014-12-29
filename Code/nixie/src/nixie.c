/*
 * nixie.c
 *
 *  Created on: 20-12-2014
 *      Author: Tomek
 */

#include <dev/display.h>
#include <dev/buttons.h>
#include <dev/realtime.h>
#include <dev/dots.h>
#include <dev/failsafe.h>
#include <lifecycle/lc.h>
#include <sys/time.h>
#include <sys/err.h>

#define DEBUG
#include <dev/debug.h>

/* currently selected digit, selection state */
static uint8_t sel_dig, sel_state, dot_state;
/* timer, time setting timer */
static timer_t sel_timer, set_timer, dot_timer, shdn_timer;

/* display loop */
static void Nixie_SelectorPoll(void)
{
	/* no digit is selected */
	if (!sel_dig) {
		/* digit was hidden? */
		//if (!sel_state) {
			/* reset mask */
			Display_SetMask(0);
			/* reset state */
			sel_state = 1;
		//}
		/* not much to do */
		return;
	}

	/* blinking timer */
	if (sel_timer && time - sel_timer < 500) {
		return;
	}

	/* compute mask */
	uint8_t mask = sel_state ? 1 << (sel_dig - 1) : 0;
	/* apply mask */
	Display_SetMask(mask);
	/* next state */
	sel_state = !sel_state;
	/* kick timer */
	sel_timer = time;
}

/* time set poll */
static void Nixie_TimeSetPoll(void)
{
	/* get buttons status */
	uint8_t b = Buttons_GetStatus();

	/* enable/disable time setting */
	if (b & BUTTONS_UP) {
		/* kick timers */
		set_timer = time; sel_timer = 0; sel_state = 1;
		/* select next digit */
		sel_dig = (sel_dig + 1) % 5;
	}

	/* time setting disabled? */
	if (!sel_dig) {
		return;
	}

	/* button pressed? */
	if (b & BUTTONS_DN) {
		/* kick timers */
		set_timer = time; sel_timer = 0; sel_state = 0;

		/* current time */
		uint8_t h, m, s;
		/* get current time */
		RealTime_GetTime(&h, &m, &s);
		/* split digits */
		uint8_t mt = m / 10, mu = m % 10;
		uint8_t ht = h / 10, hu = h % 10;
		/* minute units */
		if (sel_dig == 4) {
			mu = (mu + 1) % 10;
		/* minute tens */
		} else if (sel_dig == 3) {
			mt = (mt + 1) % 6;
		/* hour units */
		} else if (sel_dig == 2) {
			/* limit hour units */
			if (ht == 2)
				hu = (hu + 1) % 4;
			else
				hu = (hu + 1) % 10;
		/* hours tens */
		} else {
			ht = (ht + 1) % 3;
			/* limit hour units */
			if (ht == 2 && hu > 3)
				hu = 3;
		}
		/* save time */
		RealTime_SetTime(ht * 10 + hu, mt * 10 + mu, s);
	}

	/* check timer */
	if (time - set_timer > 5000) {
		/* disable time setting */
		sel_dig = 0;
	}
}

/* time display */
static void Nixie_DisplayTime(void)
{
	/* get current time */
	uint8_t h, m, s, mask;

	/* check on dots, update time */
	if (dot_timer && time - dot_timer < 500) {
		return;
	}
	/* kick timer */
	dot_timer = time;

	/* get current time */
	RealTime_GetTime(&h, &m, &s);
	/* set display */
	Display_Set(h, m);

	/* dot mask */
	mask = s < 30 ? DOTS_UP : DOTS_DN;
	/* both dots enabled */
	if (!dot_state) {
		Dots_Set(DOTS_UP | DOTS_DN);
	/* blink one of the dots */
	} else {
		Dots_Set(mask);
	}

	/* next dots state */
	dot_state = !dot_state;
}

/* check for sudden loss of power */
static void Nixie_FailSafePoll(void)
{
	if (FailSafe_IsPowerInterrupted()) {
		/* time elapsed? */
		if (time - shdn_timer > 1000) {
			dprintf("ENTER SHDN\n");
			/* command shutdown operation */
			LC_SetMode(LC_MODE_SHDN);
		}
	/* no fail detected */
	} else {
		/* kick timer */
		shdn_timer = time;
	}
}

/* initialize devices */
int Nixie_Init(void)
{
	/* reset selected digit */
	sel_dig = 0; sel_state = 0;
	/* reset shutdown timer */
	dot_timer = shdn_timer = 0;
	/* report status */
	return EOK;
}

/* deinitialize */
int Nixie_Deinit(void)
{
	/* report status */
	return EOK;
}

/* device polling */
void Nixie_Poll(void)
{
	/* display loop */
	Nixie_SelectorPoll();
	/* time set poll */
	Nixie_TimeSetPoll();
	/* time display */
	Nixie_DisplayTime();
	/* check for sudden loss of power */
	Nixie_FailSafePoll();
}

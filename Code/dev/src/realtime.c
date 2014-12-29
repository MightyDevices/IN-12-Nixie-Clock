/*
 * realtime.c
 *
 *  Created on: 13-12-2014
 *      Author: Tomek
 */

#include <stm32l/rcc.h>
#include <stm32l/rtc.h>
#include <stm32l/pwr.h>
#include <sys/err.h>

#define DEBUG
#include <dev/debug.h>

/* initialize real time clock */
int RealTime_Init(void)
{
	/* enable power control */
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	/* enable access to lse configuration */
	PWR->CR |= PWR_CR_DBP;

	/* enable rtc */
	RCC->CSR |= RCC_CSR_RTCEN | RCC_CSR_RTCSEL_LSE;

	/* disable rtc protection */
	RTC->WPR = 0xCA; RTC->WPR = 0x53;

	/* enter initialization mode */
	RTC->ISR |= RTC_ISR_INIT;
	/* poll on init flag */
	while (!(RTC->ISR & RTC_ISR_INITF));
	/* write prescalers for lse */
	RTC->PRER = 127 << 16 | 255 << 0;
	/* exit initialization mode */
	RTC->ISR &= ~RTC_ISR_INIT;
	/* wait till registers are synced */
	while (!(RTC->ISR & RTC_ISR_RSF));
	/* enable write protection */
	RTC->WPR = 0xFF;

	/* return status */
	return EOK;
}

/* deinitialize realtime clock */
int RealTime_Deinit(void)
{
	/* return status */
	return EOK;
}

/* returns day of week */
uint8_t RealTime_GetDayofWeek(uint16_t y, uint8_t m, uint8_t d)
{
	/* temporary variables */
	uint16_t _a, _m, _y;
	/* day number */
	uint32_t dn;

	/* temporary variables */
	_a = (14 - m) / 12;
	_y = y + 4800 - _a;
	_m = m + 12 * _a - 3;

	/* day number */
	dn = d + (153 * _m + 2) / 5 + (365 * _y) + (_y / 4) -
			(_y / 100) + (_y / 400) - 32045;

	/* return day of week (iso format: 1 - Monday, 7 - Sunday) */
	return (dn % 7) + 1;
}

/* set up clock */
void RealTime_SetTime(uint8_t h, uint8_t m, uint8_t s)
{
	/* disable rtc protection */
	RTC->WPR = 0xCA; RTC->WPR = 0x53;

	/* enter initialization mode */
	RTC->ISR |= RTC_ISR_INIT;
	/* poll on init flag */
	while (!(RTC->ISR & RTC_ISR_INITF));
	/* write prescalers for lse */
	RTC->PRER = 127 << 16 | 255 << 0;
	/* store time */
	RTC->TR = (h / 10) << 20 | (h % 10) << 16 |
			  (m / 10) << 12 | (m % 10) <<  8 |
			  (s / 10) <<  4 | (s % 10) <<  0;
	/* exit initialization mode */
	RTC->ISR &= ~RTC_ISR_INIT;
	/* wait till registers are synced */
	while (!(RTC->ISR & RTC_ISR_RSF));

	/* enable write protection */
	RTC->WPR = 0xFF;
}

/* set date */
void RealTime_SetDate(uint8_t y, uint8_t m, uint8_t d)
{
	/* get day of week */
	uint8_t w = RealTime_GetDayofWeek(y + 2000, m, d);

	/* disable rtc protection */
	RTC->WPR = 0xCA; RTC->WPR = 0x53;

	/* enter initialization mode */
	RTC->ISR |= RTC_ISR_INIT;
	/* poll on init flag */
	while (!(RTC->ISR & RTC_ISR_INITF));
	/* write prescalers for lse */
	RTC->PRER = 127 << 16 | 255 << 0;
	/* store time */
	RTC->DR = (y / 10) << 20 | (y % 10) << 16 |
			  (w << 13) |
			  (m / 10) << 12 | (m % 10) <<  8 |
			  (d / 10) <<  4 | (d % 10) <<  0;
	/* exit initialization mode */
	RTC->ISR &= ~RTC_ISR_INIT;
	/* wait till registers are synced */
	while (!(RTC->ISR & RTC_ISR_RSF));

	/* enable write protection */
	RTC->WPR = 0xFF;
}

/* get current time */
void RealTime_GetTime(uint8_t *h, uint8_t *m, uint8_t *s)
{
	/* read bcd encoded values */
	uint32_t tr = RTC->TR;
	/* decode! */
	*h = ((tr >> 20) & 0x3) * 10 + ((tr >> 16) & 0xf);
	*m = ((tr >> 12) & 0x7) * 10 + ((tr >>  8) & 0xf);
	*s = ((tr >>  4) & 0x7) * 10 + ((tr >>  0) & 0xf);
}

/* get current date */
void RealTime_GetDate(uint8_t *y, uint8_t *m, uint8_t *d, uint8_t *w)
{
	/* read bcd encoded values */
	uint32_t dr = RTC->DR;
	/* decode! */
	*y = ((dr >> 20) & 0xf) * 10 + ((dr >> 16) & 0xf);
	*m = ((dr >> 12) & 0x1) * 10 + ((dr >>  8) & 0xf);
	*d = ((dr >>  4) & 0x3) * 10 + ((dr >>  0) & 0xf);
	*w = ((dr >> 13) & 0x7);
}

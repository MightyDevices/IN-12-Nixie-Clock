/*
 * rtc.c
 *
 *  Created on: 24-02-2013
 *      Author: Tomek
 */

#include <stm32l/rcc.h>
#include <stm32l/rtc.h>

/* convert to bcd */
static uint8_t RTC_ByteToBcd2(uint8_t Value)
{
	uint8_t bcdhigh = 0;

	while (Value >= 10) {
		bcdhigh++;
		Value -= 10;
	}

	return  ((uint8_t)(bcdhigh << 4) | Value);
}

/* deinitialize rtc */
void RTC_DeInit(void)
{
	/* Disable the write protection for RTC registers */
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	/* Set Initialization mode */
	RTC_EnterInitMode();

	/* Reset TR, DR and CR registers */
	RTC->TR = (uint32_t)0x00000000;
	RTC->DR = (uint32_t)0x00002101;
	/* Reset All CR bits except CR[2:0] */
	RTC->CR &= (uint32_t)0x00000007;

	/* Wait till RTC WUTWF flag is set and if Time out is reached exit */
	while (!(RTC->ISR & RTC_ISR_WUTWF));

	/* Reset all RTC CR register bits */
	RTC->CR        &= (uint32_t)0x00000000;
	RTC->WUTR      = (uint32_t)0x0000FFFF;
	RTC->PRER      = (uint32_t)0x007F00FF;
	RTC->CALIBR    = (uint32_t)0x00000000;
	RTC->ALRMAR    = (uint32_t)0x00000000;
	RTC->ALRMBR    = (uint32_t)0x00000000;
	RTC->SHIFTR    = (uint32_t)0x00000000;
	RTC->CALR       = (uint32_t)0x00000000;
	RTC->ALRMASSR  = (uint32_t)0x00000000;
	RTC->ALRMBSSR  = (uint32_t)0x00000000;

	/* Reset ISR register and exit initialization mode */
	RTC->ISR = (uint32_t)0x00000000;

	/* Reset Tamper and alternate functions configuration register */
	RTC->TAFCR = 0x00000000;

	/* Wait till the RTC RSF flag is set */
	RTC_WaitForSynchro();

	/* Enable the write protection for RTC registers */
	RTC->WPR = 0xFF;

}

/* initialize rtc */
void RTC_Init(rtc_init_t *init)
{
	/* Disable the write protection for RTC registers */
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	/* Set Initialization mode */
	RTC_EnterInitMode();

    /* Clear RTC CR FMT Bit */
    RTC->CR &= ((uint32_t)~(RTC_CR_FMT));
    /* Set RTC_CR register */
    RTC->CR |=  ((uint32_t)(init->hour_format));

    /* Configure the RTC PRER */
    RTC->PRER = (uint32_t)(init->synch_prediv);
    RTC->PRER |= (uint32_t)(init->asynch_prediv << 16);

    /* Exit Initialization mode */
    RTC_ExitInitMode();

	/* Enable the write protection for RTC registers */
	RTC->WPR = 0xFF;
}

/* init struct */
void RTC_StructInit(rtc_init_t *init)
{
	/* Initialize the RTC_HourFormat member */
	init->hour_format = RTC_HOURFORMAT_24;
	/* Initialize the RTC_AsynchPrediv member */
	init->asynch_prediv = (uint32_t)0x7F;
	/* Initialize the RTC_SynchPrediv member */
	init->synch_prediv = (uint32_t)0xFF;
}

/* enter init mode */
void RTC_EnterInitMode(void)
{
	/* Check if the Initialization mode is set */
	if ((RTC->ISR & RTC_ISR_INITF) == 0) {
		/* Set the Initialization mode */
		RTC->ISR |= 0xFFFFFFFF;

		/* Wait till RTC is in INIT state and if Time out is reached exit */
		while (!(RTC->ISR & RTC_ISR_INITF));
	}
}

/* exit init mode */
void RTC_ExitInitMode(void)
{
	/* Exit Initialization mode */
	RTC->ISR &= (uint32_t)~RTC_ISR_INIT;
}

/* write protection */
void RTC_WriteProtectionCmd(int state)
{
	if (state) {
		/* Enable the write protection for RTC registers */
		RTC->WPR = 0xFF;
	} else {
		/* Disable the write protection for RTC registers */
		RTC->WPR = 0xCA;
		RTC->WPR = 0x53;
	}
}

/* wait for synchro */
void RTC_WaitForSynchro(void)
{
	/* Disable the write protection for RTC registers */
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	/* Clear RSF flag */
	RTC->ISR &= (uint32_t)0xFFFFFF5F;

	/* Wait the registers to be synchronised */
	while (!(RTC->ISR & RTC_ISR_RSF));

	/* Enable the write protection for RTC registers */
	RTC->WPR = 0xFF;
}
/* Set the specified RTC Alarm. */
void RTC_SetAlarm(uint32_t format, uint32_t alarm, rtc_alarm_t *init)
{
	uint32_t tmpreg = 0;

	/* Check the input parameters format */
	if (format != RTC_FORMAT_BIN) {
		tmpreg = (((uint32_t)(init->time.hours) << 16) | \
				  ((uint32_t)(init->time.minutes) << 8) | \
				  ((uint32_t)init->time.seconds) | \
				  ((uint32_t)(init->time.h12_am_pm) << 16) | \
				  ((uint32_t)(init->date_weekday) << 24) | \
				  ((uint32_t)init->date_weekday_sel) | \
				  ((uint32_t)init->mask));
	} else {
		tmpreg = (((uint32_t)RTC_ByteToBcd2(init->time.hours) << 16) | \
				  ((uint32_t)RTC_ByteToBcd2(init->time.minutes) << 8) | \
				  ((uint32_t)RTC_ByteToBcd2(init->time.seconds)) | \
				  ((uint32_t)(init->time.h12_am_pm) << 16) | \
				  ((uint32_t)RTC_ByteToBcd2(init->date_weekday) << 24) | \
				  ((uint32_t)init->date_weekday_sel) | \
				  ((uint32_t)init->mask));
	}

	/* Disable the write protection for RTC registers */
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	/* Configure the Alarm register */
	if (alarm == RTC_ALARM_A) {
		RTC->ALRMAR = (uint32_t)tmpreg;
	} else {
		RTC->ALRMBR = (uint32_t)tmpreg;
	}

	/* Enable the write protection for RTC registers */
	RTC->WPR = 0xFF;
}

/* alarm struct init */
void RTC_AlarmStructInit(rtc_alarm_t *init)
{
	/* Alarm Time Settings : Time = 00h:00mn:00sec */
	init->time.h12_am_pm = RTC_H12_AM;
	init->time.hours = 0;
	init->time.minutes = 0;
	init->time.seconds = 0;

	/* Alarm Date Settings : Date = 1st day of the month */
	init->date_weekday_sel = RTC_ALARMDATEWEEKSEL_DATE;
	init->date_weekday = 1;

	/* Alarm Masks Settings : Mask =  all fields are not masked */
	init->mask = RTC_ALARMMASK_NONE;
}

/* enable/disable alarm */
void RTC_AlarmCmd(uint32_t alarm, int state)
{
	/* Disable the write protection for RTC registers */
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	/* Configure the Alarm state */
	if (state) {
		RTC->CR |= (uint32_t)alarm;
	} else {
		/* Disable the Alarm in RTC_CR register */
		RTC->CR &= (uint32_t)~alarm;
		/* Wait till RTC ALRxWF flag is set and if Time out is reached exit */
		while (!(RTC->ISR & (alarm >> 8)));
	}

	/* Enable the write protection for RTC registers */
	RTC->WPR = 0xFF;
}

/* wakeup clock config */
void RTC_WakeUpClockConfig(uint32_t clock)
{
	/* Disable the write protection for RTC registers */
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	/* Clear the Wakeup Timer clock source bits in CR register */
	RTC->CR &= (uint32_t)~RTC_CR_WUCKSEL;

	/* Configure the clock source */
	RTC->CR |= (uint32_t)clock;

	/* Enable the write protection for RTC registers */
	RTC->WPR = 0xFF;
}

/* set wakeup counter */
void RTC_SetWakeUpCounter(uint32_t counter)
{
	/* Disable the write protection for RTC registers */
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	/* Configure the Wakeup Timer counter */
	RTC->WUTR = counter;
	RTC->ISR &= ~RTC_ISR_WUTF;

	/* Enable the write protection for RTC registers */
	RTC->WPR = 0xFF;
}

/* get counter */
uint32_t RTC_GetWakeUpCounter(void)
{
	/* Get the counter value */
	return ((uint32_t)(RTC->WUTR & RTC_WUTR_WUT));
}

/* Enables or Disables the RTC WakeUp timer.*/
void RTC_WakeUpCmd(int state)
{
	/* Disable the write protection for RTC registers */
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	if (state) {
		/* Enable the Wakeup Timer */
		RTC->CR |= (uint32_t)RTC_CR_WUTE;
	} else {
		/* Disable the Wakeup Timer */
		RTC->CR &= (uint32_t)~RTC_CR_WUTE;
		/* Wait till RTC WUTWF flag is set and if Time out is reached exit */
		while (!(RTC->ISR & RTC_ISR_WUTWF));
	}

	/* Enable the write protection for RTC registers */
	RTC->WPR = 0xFF;
}

/* configure interrupt */
void RTC_ITConfig(uint32_t it, int state)
{
	/* Disable the write protection for RTC registers */
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	if (state) {
		/* Configure the Interrupts in the RTC_CR register */
		RTC->CR |= (uint32_t)(it & ~RTC_TAFCR_TAMPIE);
		/* Configure the Tamper Interrupt in the RTC_TAFCR */
		RTC->TAFCR |= (uint32_t)(it & RTC_TAFCR_TAMPIE);
	} else {
		/* Configure the Interrupts in the RTC_CR register */
		RTC->CR &= (uint32_t)~(it & (uint32_t)~RTC_TAFCR_TAMPIE);
		/* Configure the Tamper Interrupt in the RTC_TAFCR */
		RTC->TAFCR &= (uint32_t)~(it & RTC_TAFCR_TAMPIE);
	}

	/* Enable the write protection for RTC registers */
	RTC->WPR = 0xFF;
}

/* get flag status */
uint32_t RTC_GetFlagStatus(void)
{
	return RTC->ISR;
}

/* clear flag */
void RTC_ClearFlag(uint32_t flag)
{
	RTC->ISR = (uint32_t)((uint32_t)(~((flag | RTC_ISR_INIT)& 0x0001FFFF) |
			(uint32_t)(RTC->ISR & RTC_ISR_INIT)));
}

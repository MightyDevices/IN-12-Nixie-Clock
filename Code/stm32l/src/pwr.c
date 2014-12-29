/*
 * stm32_pwr.c
 *
 *  Created on: 01-08-2012
 *      Author: Tomek
 */

#include <stm32l/pwr.h>
#include <stm32l/rcc.h>
#include <stm32l/scb.h>

/* deinitialize power */
void PWR_DeInit(void)
{
	RCC_APB1PeriphResetCmd(APB1_PWR, ENABLE);
	RCC_APB1PeriphResetCmd(APB1_PWR, DISABLE);
}

/* enables or disables access to the RTC and backup registers */
void PWR_RTCAccessCmd(int state)
{
	if (state) {
		PWR->CR |= PWR_CR_DBP;
	} else {
		PWR->CR &= ~PWR_CR_DBP;
	}
}

/* configures the voltage threshold detected by the Power Voltage
 * Detector(PVD) */
void PWR_PVDLevelConfig(uint32_t level)
{
	uint32_t tmpreg = 0;

	tmpreg = PWR->CR;
	/* Clear PLS[7:5] bits */
	tmpreg &= ~PWR_CR_PLS;
	/* Set PLS[7:5] bits according to PWR_PVDLevel value */
	tmpreg |= level;

	/* Store the new value */
	PWR->CR = tmpreg;
}

/* power level detector enable/disable*/
void PWR_PVDCmd(int state)
{
	if (state) {
		PWR->CR |= PWR_CR_PVDE;
	} else {
		PWR->CR &= ~PWR_CR_PVDE;
	}
}

/* Enables or disables the WakeUp Pin functionality. */
void PWR_WakeUpPinCmd(uint32_t pins, int state)
{
	if (state) {
		PWR->CSR |= pins;
	} else {
		PWR->CSR &= ~pins;
	}
}

/* fast wakeup command enable/disable */
void PWR_FastWakeUpCmd(int state)
{
	if (state) {
		PWR->CR |= PWR_CR_FWU;
	} else {
		PWR->CR &= ~PWR_CR_FWU;
	}
}

/* ultra low power command */
void PWR_UltraLowPowerCmd(int state)
{
	if (state) {
		PWR->CR |= PWR_CR_ULP;
	} else {
		PWR->CR &= ~PWR_CR_ULP;
	}
}

/* Configures the voltage scaling range */
void PWR_VoltageScalingConfig(uint32_t scaling)
{
	uint32_t temp = 0;
	/* set new value */
	temp = (PWR->CR & ~PWR_CR_VOS) | scaling;
	/* bang */
	PWR->CR = temp;
}

/* enter low power run mode */
void PWR_EnterLowPowerRunMode(int state)
{
	if (state) {
		PWR->CR |= PWR_CR_LPSDSR;
		PWR->CR |= PWR_CR_LPRUN;
	} else {
		PWR->CR &= ~PWR_CR_LPRUN;
		PWR->CR &= ~PWR_CR_LPSDSR;
	}
}

/* enter sleep mode */
void PWR_EnterSleepMode(uint32_t regulator, int entry)
{
	uint32_t tmpreg = 0;

	/* Select the regulator state in Sleep mode */
	tmpreg = PWR->CR;
	/* Clear PDDS and LPDSR bits */
	tmpreg &= ~(PWR_CR_LPSDSR | PWR_CR_PDDS);
	/* Set LPDSR bit according to PWR_Regulator value */
	tmpreg |= regulator;
	/* Store the new value */
	PWR->CR = tmpreg;

	/* Clear SLEEPDEEP bit of Cortex System Control Register */
	SCB->SCR &= ~(SCB_SCR_SLEEPDEEP);

	/* Select SLEEP mode entry */
	if (entry == PWR_ENTRY_WFI) {
		/* Request Wait For Interrupt */
		asm volatile ("wfi");
		asm volatile ("nop");
		asm volatile ("nop");
	} else {
		/* Request Wait For Event */
	    asm volatile ("wfe");
	    asm volatile ("nop");
	    asm volatile ("nop");
	}
}

/* enter stop mode */
void PWR_EnterSTOPMode(uint32_t regulator, int entry)
{
	uint32_t tmpreg = 0;

	/* Select the regulator state in STOP mode */
	tmpreg = PWR->CR;
	/* Clear PDDS and LPDSR bits */
	tmpreg &= ~(PWR_CR_LPSDSR | PWR_CR_PDDS);
	/* Set LPDSR bit according to PWR_Regulator value */
	tmpreg |= regulator;
	/* Store the new value */
	PWR->CR = tmpreg;
	/* clear wakeup */
	PWR->CSR &= ~PWR_CSR_WUF;
	/* Set SLEEPDEEP bit of Cortex System Control Register */
	SCB->SCR |= SCB_SCR_SLEEPDEEP;

	/* Select SLEEP mode entry */
	if (entry == PWR_ENTRY_WFI) {
		/* Request Wait For Interrupt */
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("wfi");
	} else {
		/* Request Wait For Event */
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("wfe");
	}

	/* Reset SLEEPDEEP bit of Cortex System Control Register */
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP;
}

/* enter standby mode */
void PWR_EnterSTANDBYMode(void)
{
	/* Clear Wakeup flag */
	PWR->CR |= PWR_CR_CWUF;
	/* Select STANDBY mode */
	PWR->CR |= PWR_CR_PDDS;
	/* Set SLEEPDEEP bit of Cortex System Control Register */
	SCB->SCR |= SCB_SCR_SLEEPDEEP;

	/* get back to sleep */
	asm volatile ("nop");
	asm volatile ("nop");
	asm volatile ("wfi");
}

/* enter or exit */
void PWR_LowPowerRunMode(int state)
{
	if (state) {
		PWR->CR |= PWR_CR_LPSDSR;
		PWR->CR |= PWR_CR_LPRUN;
	} else {
		PWR->CR &= ~PWR_CR_LPSDSR;
		PWR->CR &= ~PWR_CR_LPRUN;
	}
}

/* clear flag */
void PWR_ClearFlag(uint32_t flag)
{
	PWR->CR |= flag;
}


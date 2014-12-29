/*
 * iwdg.c
 *
 *  Created on: 24-02-2013
 *      Author: Tomek
 */

#include <stm32l/iwdg.h>

/* Enable config registers access */
void IWDG_WriteAccessCmd(int state)
{
	if (state) {
		IWDG->KR = IWDG_WRITEACCESS_ENABLE;
	} else {
		IWDG->KR = IWDG_WRITEACCESS_DISABLE;
	}
}

/* Set IWDG prescaler */
void IWDG_SetPrescaler(uint8_t prescaler)
{
	IWDG->PR = prescaler;
}

/* Set reload value */
void IWDG_SetReload(uint16_t value)
{
	IWDG->RLR = value;
}

/* Reload the IWDG counter */
void IWDG_ReloadCounter(void)
{
	IWDG->KR = IWDG_KR_KEY_RELOAD;
}

/* Enable IWDG */
void IWDG_Enable(void)
{
	IWDG->KR = IWDG_KR_KEY_ENABLE;
}

/* Get IWDG status */
int IWDG_GetStatus(void)
{
	return IWDG->SR;
}

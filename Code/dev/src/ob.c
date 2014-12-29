/*
 * ob.c
 *
 *  Created on: 09-05-2014
 *      Author: Tomek
 */

#include <stm32l/flash.h>
#include <sys/err.h>

/* default configuration */
static uint32_t ob_user = 0xff8f0070;

/* initialize option bytes */
int OB_Init(void)
{
	/* get current setting */
	uint32_t ob = OB->USER;
	/* value does not match */
	if (ob != ob_user) {
		/* Unlocking the Data memory and FLASH_PECR register access */
		FLASH->PEKEYR = FLASH_PEKEY1; FLASH->PEKEYR = FLASH_PEKEY2;
		/* Unlocking the option bytes block access */
		FLASH->OPTKEYR = FLASH_OPTKEY1; FLASH->OPTKEYR = FLASH_OPTKEY2;
		/* wait till write is finished */
		while (FLASH->SR & FLASH_SR_BSY);
		/* store configuration */
		OB->USER = ob_user;
		/* wait till write is finished */
		while (FLASH->SR & FLASH_SR_BSY);
		/* perform option byte load */
		FLASH->PECR |= FLASH_PECR_OBL_LAUNCH;
	}

	/* report status */
	return EOK;
}

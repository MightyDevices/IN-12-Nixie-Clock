/*
 * syscfg.c
 *
 *  Created on: 31-03-2013
 *      Author: Tomek
 */

#include <stm32l/syscfg.h>

/* usb pullup configuration */
void SYSCFG_USBPuCmd(int state)
{
	/* enable/ disable pullup */
	if (state) {
		SYSCFG->PMC |= SYSCFG_PMC_USB_PU;
	} else {
		SYSCFG->PMC &= ~SYSCFG_PMC_USB_PU;
	}
}


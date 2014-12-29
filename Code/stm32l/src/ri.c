/*
 * ri.c
 *
 *  Created on: 24-09-2012
 *      Author: Tomek
 */

#include <stm32l/ri.h>

/* open/close analog switch on corresponding i/o */
void RI_IOSwitchConfig(uint32_t sw, int state)
{
	uint32_t ioswitchmask = 0;

	/* Read Analog switch register index */
	ioswitchmask = sw & 0x80000000;

	/* Get Bits[30:0] of the IO switch */
	sw  &= 0x7FFFFFFF;

	if (state != DISABLE) {
		if (ioswitchmask) {
			/* Close the analog switches */
			RI->ASCR1 |= sw;
		} else {
			/* Open the analog switches */
			RI->ASCR2 |= sw;
		}
	} else {
		if (ioswitchmask) {
			/* Close the analog switches */
			RI->ASCR1 &= (~ (uint32_t)sw);
		} else {
			/* Open the analog switches */
			RI->ASCR2 &= (~ (uint32_t)sw);
		}
	}
}

/* configure corresponding pin hysteresis */
void RI_HysteresisConfig(int port, uint16_t pin, int state)
{
	/* Check the parameters */
	switch (port) {
	/* porta */
	case RI_PORTA : {
		/* disable histeresis */
		if (state != DISABLE) {
		  /* Hysteresis on */
		  RI->HYSCR1 &= (uint32_t)~((uint32_t)pin);
		} else {
		  /* Hysteresis off */
		  RI->HYSCR1 |= (uint32_t) pin;
		}
	} break;
	/* portb */
	case RI_PORTB : {
		/* disable histeresis */
		if (state != DISABLE) {
			/* Hysteresis on */
			RI->HYSCR1 &= (uint32_t) (~((uint32_t)pin) << 16);
		} else {
			/* Hysteresis off */
			RI->HYSCR1 |= (uint32_t) ((uint32_t)(pin) << 16);
		}
	} break;
	/* portc */
	case RI_PORTC : {
		/* disable histeresis */
		if (state != DISABLE) {
			/* Hysteresis on */
			RI->HYSCR2 &= (uint32_t)~((uint32_t)pin);
		} else {
			/* Hysteresis off */
			RI->HYSCR2 |= (uint32_t) pin;
		}
	} break;
	/* portd */
	case RI_PORTD : {
		/* disable histeresis */
		if (state != DISABLE) {
			/* Hysteresis on */
			RI->HYSCR2 &= (uint32_t) (~((uint32_t)pin) << 16);
		} else {
			/* Hysteresis off */
			RI->HYSCR2 |= (uint32_t) ((uint32_t)(pin) << 16);
		}
	} break;
	/* porte */
	case RI_PORTE : {
		/* disable histeresis */
		if (state != DISABLE) {
			/* Hysteresis on */
			RI->HYSCR3 &= (uint32_t)~((uint32_t)pin);
		} else {
			/* Hysteresis off */
			RI->HYSCR3 |= (uint32_t) pin;
		}
	} break;
	/* portf */
	case RI_PORTF : {
		/* disable histeresis */
		if (state != DISABLE) {
			/* Hysteresis on */
			RI->HYSCR3 &= (uint32_t) (~((uint32_t)pin) << 16);
		} else {
			/* Hysteresis off */
			RI->HYSCR3 |= (uint32_t) ((uint32_t)(pin) << 16);
		}
	} break;
	/* portg */
	case RI_PORTG : {
		/* disable histeresis */
		if (state != DISABLE) {
			/* Hysteresis on */
			RI->HYSCR4 &= (uint32_t)~((uint32_t)pin);
		} else {
			/* Hysteresis off */
			RI->HYSCR4 |= (uint32_t) pin;
		}
	} break;
	}
}

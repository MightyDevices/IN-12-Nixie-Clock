/*
 * stm32_gpio.c
 *
 *  Created on: 13-06-2012
 *      Author: Tomek
 */

#include <stm32l/stm32l.h>
#include <stm32l/rcc.h>
#include <stm32l/gpio.h>


/* initialize pins */
void GPIO_Init(gpio_t *GPIOx, gpio_init_t *init)
{
	int i;
	/* for every pin */
	for (i = 0; i < 16 && init->pins; i++) {
		/* bit position */
		if (init->pins & (1 << i)) {
			/* clear mode */
			GPIOx->MODER  &= ~(0x3 << (i * 2));
			GPIOx->MODER |= init->mode << (i * 2);
			/* speed and output mode configuration */
			if ((init->mode == GPIO_OUTPUT) || (init->mode == GPIO_ALT)) {
				/* Speed mode configuration */
				GPIOx->OSPEEDR &= ~(0x3 << (i * 2));
				GPIOx->OSPEEDR |= init->speed << (i * 2);
				/* Output mode configuration */
				GPIOx->OTYPER  &= ~(1 << i);
				GPIOx->OTYPER |= init->otype << i;
				/* alternative mode */
				if (init->mode == GPIO_ALT) {
					if (i >= 8) {
						GPIOx->AFRH &= ~(0xf << ((i - 8) * 4));
						GPIOx->AFRH |= (init->af << ((i - 8) * 4));
					} else {
						GPIOx->AFRL &= ~(0xf << (i * 4));
						GPIOx->AFRL |= (init->af << (i * 4));
					}
				}
			}
			/* Pull-up Pull down resistor configuration */
			GPIOx->PUPDR &= ~(0x3 << (i * 2));
			GPIOx->PUPDR |= init->pupd << (i * 2);
		}
	}
}

/* Fills each GPIO_InitStruct member with its default value. */
void GPIO_StructInit(gpio_init_t* init)
{
	/* Reset GPIO init structure parameters values */
	init->pins  = 0xffff;
	init->mode = GPIO_INPUT;
	init->speed = GPIO_OS_400K;
	init->otype = GPIO_OT_PP;
	init->pupd = GPIO_P_NOPULL;
}

/* set alternate function */
void GPIO_SetAlternateFunction(gpio_t *GPIOx, uint16_t pins, int af)
{
	int i;

	/* set alternate functions */
	for (i = 0; i < 16; i++) {
		/* pin present */
		if (pins & (1 << i)) {
			/* lower register */
			if (i < 8) {
				GPIOx->AFRL &= ~(0xf << (i * 4));
				GPIOx->AFRL |=  af << (i * 4);
			} else {
				GPIOx->AFRH &= ~(0xf << ((i - 8) * 4));
				GPIOx->AFRH |= af << ((i - 8) * 4);
			}
		}
	}
}

/* set pin mode */
void GPIO_SetMode(gpio_t *GPIOx, uint16_t pins, int mode)
{
	int i;

	/* for all bits */
	for (i = 0; i < 16; i++) {
		if (pins & (1 << i)) {
			GPIOx->MODER &= ~(0x3 << (i * 2));
			GPIOx->MODER |= (mode << (i * 2));
		}
	}
}

/* set pullup/pulldown */
void GPIO_SetPull(gpio_t *GPIOx, uint16_t pins, int pupd)
{
	int i;

	/* for all bits */
	for (i = 0; i < 16; i++) {
		if (pins & 1) {
			GPIOx->PUPDR &= ~(0x3 << (i * 2));
			GPIOx->PUPDR |= (pupd << (i * 2));
		}
	}
}

/* get pin state */
uint16_t GPIO_GetPins(gpio_t *GPIOx)
{
	return GPIOx->IDR;
}

/* set pin state */
void GPIO_SetPins(gpio_t *GPIOx, uint16_t pins)
{
	GPIOx->BSRR = pins;
}

/* clear gpio pins */
void GPIO_ClearPins(gpio_t *GPIOx, uint16_t pins)
{
	GPIOx->BSRR = pins;
}

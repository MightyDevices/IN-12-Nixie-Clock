/*
 * syscfg.h
 *
 *  Created on: 31-03-2013
 *      Author: Tomek
 */

#ifndef STM32L_SYSCFG_H_
#define STM32L_SYSCFG_H_

#include <stm32l/stm32l.h>

/* register base */
#define SYSCFG_BASE							(0x40010000)
/* registers*/
#define SYSCFG								((syscfg_t *) SYSCFG_BASE)

/* registers */
typedef struct {
	uint32_t MEMRMP;
	uint32_t PMC;
	uint32_t EXTICR1;
	uint32_t EXTICR2;
	uint32_t EXTICR3;
	uint32_t EXTICR4;
} syscfg_t;

/* pullup bit */
#define SYSCFG_PMC_USB_PU					(0x00000001)

/* source port */
#define EXTI_PORTA       					(0x00)
#define EXTI_PORTB       					(0x01)
#define EXTI_PORTC       					(0x02)
#define EXTI_PORTD       					(0x03)
#define EXTI_PORTE       					(0x04)
#define EXTI_PORTH       					(0x05)

/* source pin */
#define EXTI_P0            					(0x00)
#define EXTI_P1            					(0x01)
#define EXTI_P2            					(0x02)
#define EXTI_P3            					(0x03)
#define EXTI_P4           				 	(0x04)
#define EXTI_P5            					(0x05)
#define EXTI_P6            					(0x06)
#define EXTI_P7            					(0x07)
#define EXTI_P8            					(0x08)
#define EXTI_P9            					(0x09)
#define EXTI_P10           					(0x0A)
#define EXTI_P11           					(0x0B)
#define EXTI_P12           					(0x0C)
#define EXTI_P13           					(0x0D)
#define EXTI_P14           					(0x0E)
#define EXTI_P15           					(0x0F)

/* usb pullup configuration */
void SYSCFG_USBPuCmd(int state);


#endif /* SYSCFG_H_ */

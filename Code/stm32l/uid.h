/*
 * stm32_uid.h
 *
 *  Created on: 21-11-2012
 *      Author: Tomek
 */

#ifndef STM32L_UID_H_
#define STM32L_UID_H_

#include <stm32l/stm32l.h>

/* base address */
#define UID								((uid_t *)0x1FF80050)

/* adcx registers */
typedef struct {
	reg32_t UID0;
	reg32_t UID1;
	reg32_t _RESERVED[3];
	reg32_t UID2;
} uid_t;

#endif /* STM32_UID_H_ */

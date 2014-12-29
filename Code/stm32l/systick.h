/*
 * stm32_systick.h
 *
 *  Created on: 14-06-2012
 *      Author: Tomek
 */

#ifndef STM32L_SYSTICK_H_
#define STM32L_SYSTICK_H_

#include <stm32l/stm32l.h>

/* reg base */
#define SYSTICK_BASE						0xE000E010
/* systick */
#define SYSTICK								((systick_t *)SYSTICK_BASE)

typedef struct {
	reg32_t CSR;
	reg32_t RVR;
	reg32_t CVR;
	reg32_t CAL;
} systick_t;

/* ctrl register */
#define SYSTICK_CSR_ENABLE                 	(0x00000001)
#define SYSTICK_CSR_TICKINT                	(0x00000002)
#define SYSTICK_CSR_CLKSOURCE              	(0x00000004)
#define SYSTICK_CSR_COUNTFLAG              	(0x00010000)

/* cal register */
#define SYSTICK_CALIB_TENMS                 (0x00FFFFFF)
#define SYSTICK_CALIB_SKEW                  (0x40000000)
#define SYSTICK_CALIB_NOREF                 (0x80000000)

/* enable system timer */
void SYSTICK_Cmd(int enable);
/* set frequency */
void SYSTICK_SetFreq(int hz);

#endif /* STM32_SYSTICK_H_ */

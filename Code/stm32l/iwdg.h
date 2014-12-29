/*
 * iwdg.h
 *
 *  Created on: 24-02-2013
 *      Author: Tomek
 */

#ifndef STM32L_IWDG_H_
#define STM32L_IWDG_H_

#include <stm32l/stm32l.h>

/* register base */
#define IWDG_BASE		            		0x40003000
/* registers */
#define IWDG              					((iwdg_t *) IWDG_BASE)

/* registers */
typedef struct {
	/* key register */
	reg32_t KR;
	/* prescaler register */
	reg32_t PR;
	/* reload register */
	reg32_t RLR;
	/* status register */
	reg32_t SR;
} __attribute__ ((packed)) iwdg_t;

/* Defines for watchdog operaitons */
#define IWDG_KR_KEY_RELOAD    				0xAAAA
#define IWDG_KR_KEY_ENABLE    				0xCCCC

/* Enable / disable IWDG config registers access */
#define IWDG_WRITEACCESS_ENABLE				0x5555
#define IWDG_WRITEACCESS_DISABLE    		0x0000

/* status register */
#define IWDG_SR_PVU							0x00000001
#define IWDG_SR_RVU							0x00000002

/* prescaler values */
/* max: 442.81 ms*/
#define IWDG_PRESCALER_4            		0x00
/* max: 885.621 ms */
#define IWDG_PRESCALER_8            		0x01
/* max: 1771.243 ms */
#define IWDG_PRESCALER_16          		 	0x02
/* max: 3542.486 ms */
#define IWDG_PRESCALER_32           		0x03
/* max: 7084.972 ms */
#define IWDG_PRESCALER_64           		0x04
/* max: 14169.945 ms */
#define IWDG_PRESCALER_128          		0x05
/* max: 28339.891 ms */
#define IWDG_PRESCALER_256          		0x06

/* Watchdog counter reload value update */
#define IWDG_FLAG_PVU               		0x0001
/* Watchdog prescaler value update */
#define IWDG_FLAG_RVU               		0x0002


/* Enable config registers access */
void IWDG_WriteAccessCmd(int state);
/* Set IWDG prescaler */
void IWDG_SetPrescaler(uint8_t prescaler);
/* Set reload value */
void IWDG_SetReload(uint16_t value);
/* Reload the IWDG counter */
void IWDG_ReloadCounter(void);
/* Enable IWDG */
void IWDG_Enable(void);
/* Get IWDG status */
int IWDG_GetStatus(void);

#endif /* IWDG_H_ */

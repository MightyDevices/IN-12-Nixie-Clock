/*
 * watchdog.h
 *
 *  Created on: 13-02-2013
 *      Author: Tomek
 */

#ifndef DEV_WATCHDOG_H_
#define DEV_WATCHDOG_H_

/* disable hardware watchdog */
#define WATCHDOG_HWMODE_DISABLE				0
/* enable hardware watchdog */
#define WATCHDOG_HWMODE_ENABLE				1

/* enable hardware watchdog */
int Watchdog_Init(void);
/* set maximal interval */
void Watchdog_SetMaxInterval(void);
/* kick the dog! */
void Watchdog_Kick(void);

#endif /* WATCHDOG_H_ */

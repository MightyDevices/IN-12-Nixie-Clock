/*
 * power.h
 *
 *  Created on: 28-11-2014
 *      Author: Tomek
 */

#ifndef DEV_POWER_H_
#define DEV_POWER_H_

/* power level detector init */
int Power_Init(void);
/* enter standby mode */
void Power_StandbyMode(void);
/* enter stop mode */
void Power_StopMode(void);


#endif /* POWER_H_ */

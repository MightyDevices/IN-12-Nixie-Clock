/*
 * failsafe.h
 *
 *  Created on: 20-12-2014
 *      Author: Tomek
 */

#ifndef DEV_FAILSAFE_H_
#define DEV_FAILSAFE_H_

/* initialize failsafe */
int Failsafe_Init(void);
/* deinitialize failsafe */
int Failsafe_Deinit(void);
/* power supply was interrupted? */
int FailSafe_IsPowerInterrupted(void);


#endif /* FAILSAFE_H_ */

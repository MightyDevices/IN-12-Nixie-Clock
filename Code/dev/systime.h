/*
 * systime.h
 *
 *  Created on: 11-06-2013
 *      Author: Tomek
 */

#ifndef DEV_SYSTIME_H_
#define DEV_SYSTIME_H_

#include <sys/time.h>

/* initialize system tick timer */
int SysTime_Init(void);
/* deinitialize system tick timer */
int SysTime_Deinit(void);
/* delay in ms */
void SysTime_Delay(timer_t ms);

#endif /* SYSTICK_H_ */

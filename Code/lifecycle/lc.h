/*
 * lc.h
 *
 *  Created on: 11-04-2014
 *      Author: Tomek
 */

#ifndef LIFECYCLE_LC_H_
#define LIFECYCLE_LC_H_

#include <stdint.h>

/* modes of operation */
/* normal run */
#define LC_MODE_RUN							0
/* shutdown */
#define LC_MODE_SHDN						1

/* initialize chip */
void LC_Init(void);
/* polling */
void LC_Poll(void);
/* puts device to sleep */
void LC_SetMode(uint8_t new_mode);

#endif /* LC_H_ */

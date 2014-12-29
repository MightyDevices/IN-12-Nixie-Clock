/*
 * time.h
 *
 *  Created on: 11-06-2013
 *      Author: Tomek
 */

#ifndef SYS_TIME_H_
#define SYS_TIME_H_

#include <stdint.h>

/* default timer type */
typedef uint32_t timer_t;

/* current time counter */
extern volatile timer_t time;


#endif


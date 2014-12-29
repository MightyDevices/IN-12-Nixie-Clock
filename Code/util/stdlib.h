/*
 * sstdlib.h
 *
 *  Created on: 05-01-2013
 *      Author: Tomek
 */

#ifndef UTIL_STDLIB_H_
#define UTIL_STDLIB_H_

#include <stdint.h>

/* size type */
typedef uint32_t size_t;
/* absolute value */
#define abs(x)				((x) < 0 ? -(x) : x)

#endif /* SSTDLIB_H_ */

/*
 * m2m.h
 *
 *  Created on: 26-04-2013
 *      Author: Tomek
 */

#ifndef DEV_M2M_H_
#define DEV_M2M_H_

#include <stdint.h>
#include <util/stdlib.h>

/* initialize memory to memory transfers */
int M2M_Init(void);
/* perform transfer (8-bit wide) */
void M2M_Copy(void *dst, void *src, size_t size);
/* perform transfer (8-bit wide) */
void M2M_Set(void *dst, uint32_t data, size_t size);

#endif /* M2M_H_ */

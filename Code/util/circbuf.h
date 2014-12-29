/*
 * circbuf.h
 *
 *  Created on: 12-04-2014
 *      Author: Tomek
 */

#ifndef UTIL_CIRCBUF_H_
#define UTIL_CIRCBUF_H_

#include <stdint.h>
#include <util/stdlib.h>

/* circular buffer */
typedef struct {
	/* pointers */
	volatile uint16_t head, tail;
	/* buffer size */
	uint16_t size;
	/* data buffer */
	uint8_t *buf;
} cb_t;

/* initilize circular buffer*/
void CB_Init(cb_t *cb, void *ptr, size_t size);
/* put data to buffer */
size_t CB_Put(cb_t *cb, void *ptr, size_t size);
/* get data from buffer */
size_t CB_Get(cb_t *cb, void *ptr, size_t size);
/* get pointer and size (till wrapping) to data present in buffer */
size_t CB_GetDataPtrInLinearSpace(cb_t *cb, void **ptr);
/* get pointer and size (till wrapping to free space for writing in buffer */
size_t CB_GetFreePtrInLinearSpace(cb_t *cb, void **ptr);

#endif /* CIRCBUF_H_ */

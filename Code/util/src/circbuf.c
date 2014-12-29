/*
 * circbuf.c
 *
 *  Created on: 12-04-2014
 *      Author: Tomek
 */

#include <util/circbuf.h>
#include <util/stdlib.h>
#include <util/string.h>
#include <util/minmax.h>

/* initilize circular buffer*/
void CB_Init(cb_t *cb, void *ptr, size_t size)
{
	/* store buffer */
	cb->buf = ptr;
	/* store size */
	cb->size = size;
	/* reset pointers */
	cb->head = cb->tail = 0;
}

/* put data to buffer */
size_t CB_Put(cb_t *cb, void *ptr, size_t size)
{
	/* data pointer */
	uint8_t *p = ptr;
	/* get number of bytes free */
	uint16_t bfree = cb->size - (cb->head - cb->tail);
	/* head pointer */
	uint16_t head = cb->head & (cb->size - 1);
	/* get number of bytes till wrap occurs */
	uint16_t bwrap = cb->size - head;

	/* limit size */
	size = min(size, bfree);
	/* wrapping occurs? */
	if (size > bwrap) {
		/* copy data */
		memcpy(cb->buf + head, p, bwrap);
		/* copy remaining bytes */
		memcpy(cb->buf, p + bwrap, size - bwrap);
	/* no wrapping */
	} else {
		memcpy(cb->buf + head, p, size);
	}

	/* update pointer */
	cb->head += size;

	/* report number of bytes written */
	return size;
}

/* get data from buffer */
size_t CB_Get(cb_t *cb, void *ptr, size_t size)
{
	/* data pointer */
	uint8_t *p = ptr;
	/* get number of bytes buffered */
	uint16_t bbuf = cb->head - cb->tail;
	/* head pointer */
	uint16_t tail = cb->tail & (cb->size - 1);
	/* get number of bytes till wrap occurs */
	uint16_t bwrap = cb->size - tail;

	/* limit size */
	size = min(bbuf, size);
	/* wrapping occurs? */
	if (size > bwrap) {
		/* copy data */
		memcpy(p, cb->buf + tail, bwrap);
		/* copy remaining bytes */
		memcpy(p + bwrap, cb->buf, size - bwrap);
	/* no wrapping */
	} else {
		memcpy(p, cb->buf + tail, size);
	}

	/* update pointer */
	cb->tail += size;

	/* report number of bytes read */
	return size;
}

/* get pointer and size (till wrapping) to data present in buffer */
size_t CB_GetDataPtrInLinearSpace(cb_t *cb, void **ptr)
{
	uint16_t bbuf, bwrap, tail;
	/* number of bytes buffered */
	bbuf = cb->head - cb->tail;
	/* tail index */
	tail = cb->tail & (cb->size - 1);
	/* number of bytes till wrapping occurs */
	bwrap = cb->size - tail;

	/* set pointer */
	*ptr = cb->buf + tail;
	/* report size */
	return min(bbuf, bwrap);
}

/* get pointer and size (till wrapping to free space for writing in buffer */
size_t CB_GetFreePtrInLinearSpace(cb_t *cb, void **ptr)
{
	uint16_t bfree, bwrap, head;
	/* number of bytes free */
	bfree = cb->size - (cb->head - cb->tail);
	/* head index */
	head = cb->head & (cb->size - 1);
	/* number of bytes till wrapping occurs */
	bwrap = cb->size - head;

	/* set pointer */
	*ptr = cb->buf + head;
	/* report size */
	return min(bfree, bwrap);
}

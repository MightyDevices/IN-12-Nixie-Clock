/*
 * sstring.c
 *
 *  Created on: 22-12-2012
 *      Author: Tomek
 */

#include <stdint.h>
#include <dev/m2m.h>
#include <util/stdlib.h>

/* memory compare */
int memcmp(void *ptr1, void *ptr2, size_t num)
{
	uint8_t *p1 = ptr1;
	uint8_t *p2 = ptr2;

	/* memory compare */
	while (num > 0) {
		/* greater than */
		if (*p1 > *p2) {
			return 1;
		/* less than */
		} else if (*p1 < *p2) {
			return -1;
		}
		/* next byte */
		p1++; p2++; num--;
	}
	/* all equal */
	return 0;
}

/* memory area copy  */
void * memcpy(void *destination, void *source, size_t size)
{
	/* copy */
	if (size) M2M_Copy(destination, source, size);
	/* return destination */
	return destination;
}

/* memory area set */
void * memset(void *ptr, int value, size_t size)
{
	/* set */
	if (size) M2M_Set(ptr, value, size);
	/* return pointer */
	return ptr;
}

/* return string length */
size_t strlen(void *ptr)
{
	char *p = ptr;
	size_t size = 0;

	/* loop till end of string is found */
	while (*(p++)) {
		size++;
	}

	return size;
}

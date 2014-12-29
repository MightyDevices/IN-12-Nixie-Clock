/*
 * string.h
 *
 *  Created on: 22-12-2012
 *      Author: Tomek
 */

#ifndef UTIL_STRING_H_
#define UTIL_STRING_H_

#include <util/stdlib.h>

/* memory compare */
int memcmp(void *ptr1, void *ptr2, size_t num);
/* memcpy */
void * memcpy(void *destination, void *source, size_t num);
/* memset */
void * memset(void *ptr, int value, size_t num);
/* return string length */
size_t strlen(void *ptr);

#endif /* SSTRING_H_ */

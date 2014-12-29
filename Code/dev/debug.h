/*
 * debug.h
 *
 *  Created on: 24-05-2012
 *      Author: Tomek
 */

#ifndef DEV_DEBUG_H_
#define DEV_DEBUG_H_

#include <util/stdio.h>
#include <util/stdlib.h>
//#undef DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...)											\
{                      													\
	char __b[128];        												\
	int __len = sprintf(__b, "["__FILE__":%d]" fmt, __LINE__, ##args);	\
	Debug_Send(__b, __len);												\
}

#define dprintf2(fmt, args...)											\
{                      													\
	char __b[128];        												\
	int __len = sprintf(__b, fmt, ##args);								\
	Debug_Send(__b, __len);												\
}

#else
#define dprintf(fmt, args...)
#define dprintf2(fmt, args...)
#endif

/* dump memory */
void Debug_DumpMem(void *ptr, size_t size);

/* send via debug */
void Debug_Send(char *c, int sz);


#endif /* DEBUG_H_ */

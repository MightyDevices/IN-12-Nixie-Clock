/*
 * debug.c
 *
 *  Created on: 25-05-2012
 *      Author: Tomek
 */

#include <dev/usart1.h>
#define DEBUG
#include <dev/debug.h>

/* send via debug */
void Debug_Send(char *c, int sz)
{
	int b;
	/* send all bytes */
	while (sz > 0) {
		/* send byte */
		b = USART1_Send(c, sz);
		/* next byte */
		c += b;
		sz -= b;
	}
	/* flush */
	//USART1_Send(0, 0);
}

/* dump memory */
void Debug_DumpMem(void *ptr, size_t size)
{
	size_t i;
	uint8_t *p = ptr;

	for (i = 0; i < size; i++) {
		/* start of line */
		if (i % 16 == 0) {
			dprintf2("0x%x: ", (unsigned int)i);
		}
		/* number */
		dprintf2("0x%x", p[i]);

		/* separator */
		if (i % 16 < 15) {
			dprintf2(" ");
		} else {
			dprintf2("\n");
		}
	}

	/* end */
	if (i % 16) {
		dprintf2("\n");
	}
}

/*
 * intm.c
 *
 *  Created on: 13-03-2014
 *      Author: Tomek
 */

#include <util/intm.h>

/* calculate sqrt of integer number */
uint32_t intm_sqrt(uint32_t n)
{
	/* magic! */
	register uint32_t root = 0, hi = 0, lo = n, test_div, count = 15;

	do {
		/* get 2 bits of arg */
		hi = (hi << 2) | (lo >> 30);
		lo = lo << 2;
		/* Get ready for the next bit in the root */
		root = root << 1;
		test_div = (root << 1) + 1;
		 /* Test radical */
		if (hi >= test_div) {
			hi -= test_div;
			root++;
		}
	} while (count-- != 0);

	/* return square root */
	return root;
}

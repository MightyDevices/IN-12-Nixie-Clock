/*
 * uid.c
 *
 *  Created on: 11-06-2013
 *      Author: Tomek
 */

#include <stm32l/uid.h>

/* get uid */
void UID_GetUID(uint32_t *uid)
{
	uid[0] = UID->UID0;
	uid[1] = UID->UID1;
	uid[2] = UID->UID2;
}

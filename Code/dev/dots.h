/*
 * dots.h
 *
 *  Created on: 18-12-2014
 *      Author: Tomek
 */

#ifndef DEV_DOTS_H_
#define DEV_DOTS_H_

#include <stdint.h>

/* lower dot */
#define DOTS_DN								0x01
/* upper dot */
#define DOTS_UP								0x02

/* initialize dots */
int Dots_Init(void);
/* de-initialize dots */
int Dots_Deinit(void);
/* set dots */
void Dots_Set(uint8_t mask);

#endif /* DOTS_H_ */

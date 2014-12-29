/*
 * display.h
 *
 *  Created on: 18-12-2014
 *      Author: Tomek
 */

#ifndef DEV_DISPLAY_H_
#define DEV_DISPLAY_H_

#include <stdint.h>

/* initialize display */
int Display_Init(void);
/* deinit display */
int Display_Deinit(void);
/* set display */
int Display_Set(uint8_t h, uint8_t m);
/* mask digits */
void Display_SetMask(uint8_t mask);

#endif /* DISPLAY_H_ */

/*
 * buttons.h
 *
 *  Created on: 20-12-2014
 *      Author: Tomek
 */

#ifndef DEV_BUTTONS_H_
#define DEV_BUTTONS_H_

/* upper button */
#define BUTTONS_UP				0x02
/* lower button */
#define BUTTONS_DN				0x01

/* initialize buttons */
int Buttons_Init(void);
/* initialize buttons */
int Buttons_Deinit(void);
/* buttons were pressed? */
uint8_t Buttons_GetStatus(void);


#endif /* BUTTONS_H_ */

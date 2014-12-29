/*
 * lse.h
 *
 *  Created on: 13-12-2014
 *      Author: Tomek
 */

#ifndef DEV_LSE_H_
#define DEV_LSE_H_

/* initialize lse oscillator */
int LSE_Init(void);
/* enable/disable lse */
void LSE_Cmd(uint8_t state);


#endif /* LSE_H_ */

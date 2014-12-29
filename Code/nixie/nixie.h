/*
 * nixie.h
 *
 *  Created on: 20-12-2014
 *      Author: Tomek
 */

#ifndef NIXIE_NIXIE_H_
#define NIXIE_NIXIE_H_

/* initialize devices */
int Nixie_Init(void);
/* deinitialize */
int Nixie_Deinit(void);
/* device polling */
void Nixie_Poll(void);

#endif /* NIXIE_H_ */

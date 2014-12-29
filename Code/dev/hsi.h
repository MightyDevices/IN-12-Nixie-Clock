/*
 * hsi.h
 *
 *  Created on: 23-06-2014
 *      Author: Tomek
 */

#ifndef DEV_HSI_H_
#define DEV_HSI_H_

#include <stdint.h>

/* hsi init */
int HSI_Init(void);
/* deinitialize hsi */
int HSI_Deinit(void);
/* enable disable lsi */
void HSI_Cmd(uint8_t state);

#endif /* HSI_H_ */

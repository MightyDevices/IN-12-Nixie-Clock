/*
 * dev.h
 *
 *  Created on: 29-11-2014
 *      Author: Tomek
 */

#ifndef DEV_DEV_H_
#define DEV_DEV_H_

/* initialize devices */
int Dev_Init(void);
/* deinitialize */
int Dev_Deinit(void);
/* device polling */
void Dev_Poll(void);


#endif /* DEV_H_ */

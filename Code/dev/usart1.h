/*
 * usart1.h
 *
 *  Created on: 18-06-2012
 *      Author: Tomek
 */

#ifndef DEV_USART1_H_
#define DEV_USART1_H_

#include <util/stdlib.h>

/* initialize usart1 */
int USART1_Init(void);
/* deinitialize usart1 */
int USART1_Deinit(void);
/* send data */
size_t USART1_Send(void *ptr, size_t size);
/* receive data */
size_t USART1_Recv(void *ptr, size_t size);

#endif /* USART1_H_ */

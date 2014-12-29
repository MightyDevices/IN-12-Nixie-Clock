/*
 * aes.h
 *
 *  Created on: 09-10-2013
 *      Author: Tomek
 */

#ifndef UTIL_AES_H_
#define UTIL_AES_H_

#include <stdint.h>

/* perform encryption */
void AES_Encrypt(uint8_t *key, uint8_t *state);


#endif /* AES_H_ */

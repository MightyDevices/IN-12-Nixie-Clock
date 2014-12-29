/*
 * sstdio.h
 *
 *  Created on: 22-12-2012
 *      Author: Tomek
 */

#ifndef SSTDIO_H_
#define SSTDIO_H_

/* simple sprintf */
int sprintf(char *out, char *fmt, ...);
/* simple sscanf */
int sscanf(char *in, char *fmt, ...);

/* check if character is digit */
int is_digit(char c);
/* check if character is hex digit */
int is_xdigit(char c);
/* is whitespace */
int is_space(char c);
/* convert string to integer */
int atoi(char *str);

#endif /* SSTDIO_H_ */

/*
 * fixpm.h
 *
 *  Created on: 14-03-2014
 *      Author: Tomek
 */

#ifndef UTIL_FIXPM_H_
#define UTIL_FIXPM_H_

#include <util/fixp.h>

/* transposition */
void fixpm_transpose(fixp_t *in, int in_rows, int in_cols, fixp_t *out);
/* multiplication */
void fixpm_multiply(fixp_t *a, int a_rows, int a_cols, fixp_t *b, int b_cols,
    fixp_t *out);
/* inversion */
int fixpm_invert4(fixp_t *m, fixp_t *inv);



#endif /* FIXPM_H_ */

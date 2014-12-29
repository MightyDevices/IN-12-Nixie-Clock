/*
 * fixpm.c
 *
 *  Created on: 14-03-2014
 *      Author: Tomek
 */

#include <util/fixpm.h>

/* transposition */
void fixpm_transpose(fixp_t *in, int in_rows, int in_cols, fixp_t *out)
{
    int row, col;
    /* perform transposition */
    for (row = 0; row < in_rows; row++) {
        for (col = 0; col < in_cols; col++) {
            out[in_rows * col + row] = in[in_cols * row + col];
        }
    }
}

/* multiplication */
void fixpm_multiply(fixp_t *a, int a_rows, int a_cols, fixp_t *b, int b_cols,
    fixp_t *out)
{
    int row, col, prod;
    fixp_t sum;

    for (row = 0; row < a_rows; row++) {
        for (col = 0; col < b_cols; col++) {
            /* reset sum */
            sum = 0;
            /* summation of products */
            for (prod = 0; prod < a_cols; prod++) {
                sum += fixp_mul(a[row * a_cols + prod], b[b_cols * prod + col]);
            }
            /* assign */
            out[row * b_cols + col] = sum;
        }
    }
}

/* inversion */
int fixpm_invert4(fixp_t *m, fixp_t *inv)
{
    fixp_t det; int i;

    /* coefficient 0 */
    inv[0]  =  fixp_mul3(m[5], m[10], m[15]) - fixp_mul3(m[5], m[11], m[14]) -
               fixp_mul3(m[9], m[6], m[15]) + fixp_mul3(m[9], m[7], m[14]) +
               fixp_mul3(m[13], m[6], m[11]) - fixp_mul3(m[13], m[7], m[10]);
    /* coefficient 4 */
    inv[4]  =  fixp_mul3(m[4], m[11], m[14]) - fixp_mul3(m[4], m[10], m[15]) +
               fixp_mul3(m[8], m[6], m[15]) - fixp_mul3(m[8], m[7], m[14]) -
               fixp_mul3(m[12], m[6], m[11]) + fixp_mul3(m[12], m[7], m[10]);
    /* coefficient 8 */
    inv[8]  =  fixp_mul3(m[4], m[9], m[15]) - fixp_mul3(m[4], m[11], m[13]) -
               fixp_mul3(m[8], m[5], m[15]) + fixp_mul3(m[8], m[7], m[13]) +
               fixp_mul3(m[12], m[5], m[11]) - fixp_mul3(m[12], m[7], m[9]);
    /* coefficient 12 */
    inv[12] =  fixp_mul3(m[4], m[10], m[13]) - fixp_mul3(m[4], m[9], m[14]) +
               fixp_mul3(m[8], m[5], m[14]) - fixp_mul3(m[8], m[6], m[13]) -
               fixp_mul3(m[12], m[5], m[10]) + fixp_mul3(m[12], m[6], m[9]);
    /* coefficient 1 */
    inv[1]  =  fixp_mul3(m[1], m[11], m[14]) - fixp_mul3(m[1], m[10], m[15]) +
               fixp_mul3(m[9], m[2], m[15]) - fixp_mul3(m[9], m[3], m[14]) -
               fixp_mul3(m[13], m[2], m[11]) + fixp_mul3(m[13], m[3], m[10]);
    /* coefficient 5 */
    inv[5]  =  fixp_mul3(m[0], m[10], m[15]) - fixp_mul3(m[0], m[11], m[14]) -
               fixp_mul3(m[8], m[2], m[15]) + fixp_mul3(m[8] , m[3], m[14]) +
               fixp_mul3(m[12], m[2], m[11]) - fixp_mul3(m[12], m[3], m[10]);
    /* coefficient 9 */
    inv[9]  =  fixp_mul3(m[0], m[11], m[13]) - fixp_mul3(m[0], m[9], m[15]) +
               fixp_mul3(m[8], m[1], m[15]) - fixp_mul3(m[8], m[3], m[13]) -
               fixp_mul3(m[12], m[1], m[11]) + fixp_mul3(m[12], m[3], m[9]);
    /* coefficient 13 */
    inv[13] =  fixp_mul3(m[0], m[9], m[14]) - fixp_mul3(m[0], m[10], m[13]) -
               fixp_mul3(m[8], m[1], m[14]) + fixp_mul3(m[8], m[2], m[13]) +
               fixp_mul3(m[12], m[1], m[10]) - fixp_mul3(m[12], m[2], m[9]);
    /* coefficient 2 */
    inv[2]  =  fixp_mul3(m[1], m[6], m[15]) - fixp_mul3(m[1], m[7], m[14]) -
               fixp_mul3(m[5], m[2], m[15]) + fixp_mul3(m[5], m[3], m[14]) +
               fixp_mul3(m[13], m[2], m[7]) - fixp_mul3(m[13], m[3], m[6]);
    /* coefficient 6 */
    inv[6]  =  fixp_mul3(m[0], m[7], m[14]) - fixp_mul3(m[0], m[6], m[15]) +
               fixp_mul3(m[4], m[2], m[15]) - fixp_mul3(m[4], m[3], m[14]) -
               fixp_mul3(m[12], m[2], m[7]) + fixp_mul3(m[12], m[3], m[6]);
    /* coefficient 10 */
    inv[10] =  fixp_mul3(m[0], m[5], m[15]) - fixp_mul3(m[0], m[7], m[13]) -
               fixp_mul3(m[4], m[1], m[15]) + fixp_mul3(m[4], m[3], m[13]) +
               fixp_mul3(m[12], m[1], m[7]) - fixp_mul3(m[12], m[3], m[5]);
    /* coefficient 14 */
    inv[14] =  fixp_mul3(m[0], m[6], m[13]) - fixp_mul3(m[0], m[5], m[14]) +
               fixp_mul3(m[4], m[1], m[14]) - fixp_mul3(m[4], m[2], m[13]) -
               fixp_mul3(m[12], m[1], m[6]) + fixp_mul3(m[12], m[2], m[5]);
    /* coefficient 3 */
    inv[3]  =  fixp_mul3(m[1], m[7], m[10]) - fixp_mul3(m[1], m[6], m[11]) +
               fixp_mul3(m[5], m[2], m[11]) - fixp_mul3(m[5], m[3], m[10]) -
               fixp_mul3(m[9], m[2], m[7]) + fixp_mul3(m[9], m[3], m[6]);
    /* coefficient 7 */
    inv[7]  =  fixp_mul3(m[0], m[6], m[11]) - fixp_mul3(m[0], m[7], m[10]) -
               fixp_mul3(m[4], m[2], m[11]) + fixp_mul3(m[4], m[3], m[10]) +
               fixp_mul3(m[8], m[2], m[7]) - fixp_mul3(m[8], m[3], m[6]);
    /* coefficient 11 */
    inv[11] =  fixp_mul3(m[0], m[7], m[9]) - fixp_mul3(m[0], m[5], m[11]) +
               fixp_mul3(m[4], m[1], m[11]) - fixp_mul3(m[4], m[3], m[9]) -
               fixp_mul3(m[8], m[1], m[7]) + fixp_mul3(m[8], m[3], m[5]);
    /* coefficient 15 */
    inv[15] =  fixp_mul3(m[0], m[5], m[10]) - fixp_mul3(m[0], m[6], m[9]) -
               fixp_mul3(m[4], m[1], m[10]) + fixp_mul3(m[4], m[2], m[9]) +
               fixp_mul3(m[8], m[1], m[6]) - fixp_mul3(m[8], m[2], m[5]);

    /* neat little way to get determinant */
    det = fixp_mul(m[0], inv[0]) + fixp_mul(m[1], inv[4]) +
        fixp_mul(m[2], inv[8]) + fixp_mul(m[3], inv[12]);

    /* determinant is equal to zero, unable to inert */
    if (det == 0) {
        return -1;
    }
    /* it's alaways better to mutliplty that to divide :)*/
    det = fixp_rec(det);

    /* apply determinant */
    for (i = 0; i < 16; i++) {
        inv[i] = fixp_mul(inv[i], det);
    }

    return 0;
}

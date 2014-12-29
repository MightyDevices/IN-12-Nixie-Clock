/*
 * fixp.h
 *
 *  Created on: 22-12-2012
 *      Author: Tomek
 */

#ifndef UTIL_FIXP_H_
#define UTIL_FIXP_H_

#include <stdint.h>

/* fixed point basic type */
typedef int32_t fixp_t;
/* fixed point accumulator */
typedef int64_t afixp_t;

/* overall bits */
#define FIXP_BITS               	(sizeof(fixp_t) * 8)
/* frac bits */
#define FIXP_FRACBITS               16
/* frac mask */
#define FIXP_FRACMASK	        	(FIXP_ONE - 1)

/* convert to int */
#define fixp_toint(a)               ((int)((a) >> FIXP_FRACBITS))
/* convert from int */
#define fixp_tofixp(a)              ((fixp_t)((a) * FIXP_ONE))

/* add */
#define fixp_add(a, b)              ((a) + (b))
/* subtract */
#define fixp_sub(a, b)              ((a) - (b))
/* multiply */
#define fixp_mul(a, b)              ((fixp_t)(((afixp_t)(a) * (afixp_t)(b)) \
									>> FIXP_FRACBITS))
/* muliply three factors */
#define fixp_mul3(a, b, c)          (fixp_mul((a), fixp_mul((b), (c))))
/* divide */
#define fixp_div(a, b)              (((afixp_t)(a) << FIXP_FRACBITS) \
									/ (afixp_t)(b))
/* reciprocal */
#define fixp_rec(x)                 (((fixp_t)((1 << (FIXP_BITS - 2)) \
										+ (x) - 1) \
                                        / (fixp_t)(x)) << \
                                        (2 * FIXP_FRACBITS - (FIXP_BITS - 2)))

/* constant */
#define fixp_const(R)               ((afixp_t)((R) * (((afixp_t)1 \
									<< FIXP_FRACBITS) \
	                                + ((R) >= 0 ? 0.5 : -0.5))))
/* constant */
#define fixp(c)                     ((fixp_t)((c) * FIXP_ONE + \
									((c) >= 0 ? 0.5 : -0.5)))
/* absolute value */
#define fixp_abs(A)                 ((A) < 0 ? -(A) : (A))
/* convert radioans to deg */
#define fixp_rad2deg(a)				(fixp_mul(a, FIXP_RAD))

/* constants */
#define FIXP_ONE	                ((fixp_t)((fixp_t)1 << FIXP_FRACBITS))
#define FIXP_ONE_HALF               (FIXP_ONE >> 1)
#define FIXP_TWO	                (FIXP_ONE + FIXP_ONE)
#define FIXP_PI	                    fixp(3.14159265358979323846)
#define FIXP_TWO_PI	                fixp(2 * 3.14159265358979323846)
#define FIXP_HALF_PI	            fixp(3.14159265358979323846 / 2)
#define FIXP_1_PI	                fixp(1 / 3.14159265358979323846)
#define FIXP_RAD					fixp(57.29577951308232087679815)
#define FIXP_E	                    fixp(2.7182818284590452354)

/* return exp */
fixp_t fixp_exp(fixp_t x);
/* calculate log */
fixp_t fixp_log(fixp_t x);
/* Returns the value exp(x), i.e. e^x of the given fixp_t number. */
fixp_t fixp_pow(fixp_t base, fixp_t exponent);
/* return cosine */
fixp_t fixp_cos(fixp_t x);
/* return sine */
fixp_t fixp_sin(fixp_t x);
/* return tangens */
fixp_t fixp_tan(fixp_t x);
/* return arcus tangens */
fixp_t fixp_atan(fixp_t x);
/* square root */
fixp_t fixp_sqrt(fixp_t x);
/* arcus sinus */
fixp_t fixp_asin(fixp_t x);
/* return arcus tangent 2 */
fixp_t fixp_atan2(fixp_t y, fixp_t x);

#endif


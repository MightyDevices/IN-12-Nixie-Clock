/*
 * fixp.c
 *
 *  Created on: 22-01-2013
 *      Author: Tomek
 */

#include <util/fixp.h>

#define DEBUG
#include <dev/debug.h>

/* return exp */
fixp_t fixp_exp(fixp_t x)
{
    /* temporary variables */
    fixp_t temp, frac, absx, z, quot, base, f1, f2, result;
    /* log */
    int pow, inv;
    /* denominators */
	const fixp_t den[] = {
		fixp(5.00000000000000000000e-01),
		fixp(3.33333333333333333333e-01),
		fixp(2.50000000000000000000e-01),
        fixp(2.00000000000000000000e-01),
        fixp(1.66666666666666666667e-01),
	};
    /* shift to improve precision */
    const int shift = (sizeof(fixp_t) * 8 - FIXP_FRACBITS - 4);

    /* inverse? */
    if (x < 0) {
        inv = 1;
    }

    absx = fixp_abs(x);
    /* get only frac bits */
    z = absx & FIXP_FRACMASK;
    pow = absx >> FIXP_FRACBITS;


    /* limit fractional part */
    if (z > FIXP_ONE_HALF) {
        pow++;
        z -= FIXP_ONE;
    }

    /* taylor */
    /* 1st and 2nd term */
    temp = z << shift;
    frac = temp;
    /* 3rd */
    temp = fixp_mul(fixp_mul(temp, z), den[0]);
    frac += temp;
    /* 4th */
    temp = fixp_mul(fixp_mul(temp, z), den[1]);
    frac += temp;
    /* 5th */
    temp = fixp_mul(fixp_mul(temp, z), den[2]);
    frac += temp;
    /* 6th */
    temp = fixp_mul(fixp_mul(temp, z), den[3]);
    frac += temp;
    /* 7th */
    temp = fixp_mul(fixp_mul(temp, z), den[4]);
    frac += temp;

    /* taylor result */
    frac += FIXP_ONE << shift;
    /* split into two parts */
    f1 = frac >> shift;
    f2 = frac & ((1 << shift) - 1);

    /* start condition */
    quot = FIXP_ONE; base = FIXP_E;
    /* power up */
    while (pow) {
        if (pow & 1) {
            quot  = fixp_mul(quot, base);
        }
        base = fixp_mul(base, base);
        pow >>= 1;
    }

    /* first part of the result */
    temp = fixp_mul(quot, f2);
    /* rounding */
    temp += (1 << (shift - 1));
    /* add first term */
    result = temp >> shift;
    /* add second term */
    result += fixp_mul(quot, f1);
    /* invert */
    if (inv) {
        result = fixp_rec(result);
    }

    return result;
}

/* calculate log */
fixp_t fixp_log(fixp_t x)
{
    /* binary logarithm of e (inverted) */
    const fixp_t lgeinv = fixp(6.93147180559945309417e-01);
    /* denominators */
	const fixp_t den[] = {
		fixp(5.00000000000000000000e-01),
		fixp(3.33333333333333333333e-01),
		fixp(2.50000000000000000000e-01),
        fixp(2.00000000000000000000e-01),
        fixp(1.66666666666666666667e-01),
        fixp(1.42857142857142857142e-01),
	};
    /* temporary */
    fixp_t lg = 0, temp, frac, z, result;

    /* compute integral part of lg(x) */
    while (x >= FIXP_TWO) {
        x >>= 1;
        lg += FIXP_ONE;
    }

    /* taylor for natural logarithm */
    z = x - FIXP_ONE;
    /* 1st operation */
    temp = z;
    frac = temp;
    /* 2nd */
    temp = fixp_mul(temp, z);
    frac -= fixp_mul(temp, den[0]);
    /* 3rd */
    temp = fixp_mul(temp, z);
    frac += fixp_mul(temp, den[1]);
    /* 4th */
    temp = fixp_mul(temp, z);
    frac -= fixp_mul(temp, den[2]);
    /* 5th */
    temp = fixp_mul(temp, z);
    frac += fixp_mul(temp, den[3]);
    /* 6th */
    temp = fixp_mul(temp, z);
    frac -= fixp_mul(temp, den[4]);
    /* 7th */
    temp = fixp_mul(temp, z);
    frac += fixp_mul(temp, den[5]);

    /* convert to the base of e */
    result = fixp_mul(lg, lgeinv);
    /* add mantissa */
    result += frac;

    return result;
}

/* Returns the value exp(x), i.e. e^x of the given fixp_t number. */
fixp_t fixp_pow(fixp_t base, fixp_t exponent)
{
    /* return exponent */
    return fixp_exp(fixp_mul(exponent, fixp_log(base)));
}

/* return cosine */
fixp_t fixp_cos(fixp_t x)
{
    /* sign */
	int sign = 1;
    /* result, temporary storage, square */
	fixp_t result, temp, sqr, quot;
    /* denominator */
	const fixp_t den[4] = {
		fixp(5.0000000000000000000000e-01),
		fixp(8.3333333333333333333333e-02),
        fixp(3.3333333333333333333333e-02),
        fixp(1.7857142857142857142857e-02)
	};

    /* limit the angle */
	quot = (x / FIXP_TWO_PI);
	quot = quot * FIXP_TWO_PI;
	x -= quot;
	/* no negative arguments */
    if (x < 0) {
		x = FIXP_TWO_PI + x;
	}

    /* 4th quarter */
    if (x > FIXP_PI + FIXP_HALF_PI) {
        x = FIXP_TWO_PI - x;
    /* 3rd quarter */
    } else if (x > FIXP_PI) {
        x = x - FIXP_PI;
        sign = -1;
    /* 2nd quarter */
    } else if (x > FIXP_HALF_PI) {
        x = FIXP_PI - x;
        sign = -1;
    }

    /* get square of x */
    sqr = fixp_mul(x, x);

    /* taylor */
    /* first iteration */
    temp = FIXP_ONE;
    result = temp;
    /* 2nd iteration */
    temp = fixp_mul(fixp_mul(temp, sqr), den[0]);
    result -= temp;
    /* 3rd iteration */
    temp = fixp_mul(fixp_mul(temp, sqr), den[1]);
    result += temp;
    /* 4th iteration */
    temp = fixp_mul(fixp_mul(temp, sqr), den[2]);
    result -= temp;
    /* 5th iteration */
    temp = fixp_mul(fixp_mul(temp, sqr), den[3]);
    result += temp;

	return sign * result;
}

/* return sine */
fixp_t fixp_sin(fixp_t x)
{
    /* sign */
	int sign = 1;
    /* result, temporary storage, square */
	fixp_t result, temp, sqr;
    /* denominator */
	const fixp_t den[4] = {
		fixp(1.6666666666666666666667e-01),
		fixp(5.0000000000000000000000e-02),
        fixp(2.3809523809523809523809e-02),
        fixp(1.3888888888888888888888e-02)
	};

    /* limit the angle */
	x %= FIXP_TWO_PI;
	/* no negative arguments */
    if (x < 0) {
		x = FIXP_TWO_PI + x;
	}

    /* 4th quarter */
    if (x > FIXP_PI + FIXP_HALF_PI) {
        x = FIXP_TWO_PI - x;
        sign = -1;
    /* 3rd quarter */
    } else if (x > FIXP_PI) {
        x = x - FIXP_PI;
        sign = -1;
    /* 2nd quarter */
    } else if (x > FIXP_HALF_PI) {
        x = FIXP_PI - x;
    }

    /* get square of x */
    sqr = fixp_mul(x, x);

    /* taylor */
    /* first iteration */
    temp = x;
    result = temp;
    /* 2nd iteration */
    temp = fixp_mul(fixp_mul(temp, sqr), den[0]);
    result -= temp;
    /* 3rd iteration */
    temp = fixp_mul(fixp_mul(temp, sqr), den[1]);
    result += temp;
    /* 4th iteration */
    temp = fixp_mul(fixp_mul(temp, sqr), den[2]);
    result -= temp;
    /* 5th iteration */
    temp = fixp_mul(fixp_mul(temp, sqr), den[3]);
    result += temp;

	return sign * result;
}

/* return tangent */
fixp_t fixp_tan(fixp_t x)
{
	int sign = 1, inv = 0;
    /* temporary variables */
	fixp_t sqr, result, temp;
    /* denominators */
	const fixp_t den[4] = {
		fixp(3.3333333333333333333333e-01),
		fixp(1.3333333333333333333333e-01),
        fixp(5.3968253968253968253968e-02),
        fixp(2.1869488536155202821869e-02)
	};


    /* limit the angle */
	x %= FIXP_PI;
	/* no negative arguments */
    if (x < 0) {
		x = FIXP_PI + x;
	}

    /* 4th quarter */
    if (x > FIXP_HALF_PI + FIXP_HALF_PI / 2) {
        x = FIXP_PI - x;
        sign = -1;
    /* 3rd quarter */
    } else if (x > FIXP_HALF_PI) {
		x = x - FIXP_HALF_PI;
		sign = -1;
        inv = 1;
    /* 2nd quarter */
    } else if (x > FIXP_HALF_PI / 2) {
		x = FIXP_HALF_PI - x;
        inv = 1;
    }

    /* get square of x */
    sqr = fixp_mul(x, x);

    /* taylor */
    /* first iteration */
    temp = x;
    result = temp;
    /* 2nd iteration */
    temp = fixp_mul(temp, sqr);
    result += fixp_mul(temp, den[0]);
    /* 3rd iteration */
    temp = fixp_mul(temp, sqr);
    result += fixp_mul(temp, den[1]);
    /* 4th iteration */
    temp = fixp_mul(temp, sqr);
    result += fixp_mul(temp, den[2]);
    /* 5th iteration */
    temp = fixp_mul(temp, sqr);
    result += fixp_mul(temp, den[3]);

    /* invert if needed */
    if (inv) {
        result = fixp_rec(result);
    }

	return sign * result;
}

/* return arcus tangens */
fixp_t fixp_atan(fixp_t x)
{
	int inv = 0, sign = 1;
    /* temporary variables */
	fixp_t sqr, result, temp;
    /* denominators fox x0 = 0 */
	const fixp_t den_0[4] = {
		fixp(3.3333333333333333333333e-01),
		fixp(2.0000000000000000000000e-01),
        fixp(1.4285714285714285714285e-01),
        fixp(1.1111111111111111111111e-01),
	};
    /* denominators fox x0 = 1 */
	const fixp_t den_1[4] = {
		fixp(2.5000000000000000000000e-01),
        fixp(8.3333333333333333333333e-02),
        fixp(2.5000000000000000000000e-02),
        fixp(2.0833333333333333333333e-02),
	};

    /* sign */
    if (x < 0) {
        /* flag */
        sign = -1;
        /* absolute value */
        x = fixp_abs(x);
    }

    /* limit argument */
    if (x > FIXP_ONE) {
        /* invert */
        x = fixp_rec(x);
        /* set flag */
        inv = 1;
    }

    /* taylor centered at x0 = 0 */
    if (x < FIXP_ONE_HALF) {
        /* get square of x */
        sqr = fixp_mul(x, x);

        /* taylor */
        /* first iteration */
        temp = x;
        result = temp;
        /* 2nd iteration */
        temp = fixp_mul(temp, sqr);
        result -= fixp_mul(temp, den_0[0]);
        /* 3rd iteration */
        temp = fixp_mul(temp, sqr);
        result += fixp_mul(temp, den_0[1]);
        /* 4th iteration */
        temp = fixp_mul(temp, sqr);
        result -= fixp_mul(temp, den_0[2]);
        /* 5th iteration */
        temp = fixp_mul(temp, sqr);
        result += fixp_mul(temp, den_0[3]);
    /* taylor centered at x0 = 1 */
    } else {
        /* shift x */
        x = x - FIXP_ONE;
        /* get square of x */
        sqr = fixp_mul(x, x);

        /* taylor */
        /* first iteration */
        temp = x;
        result = FIXP_HALF_PI / 2 + temp / 2;
        /* 2nd iteration */
        temp = fixp_mul(temp, x);
        result -= fixp_mul(temp, den_1[0]);
        /* 3rd iteration */
        temp = fixp_mul(temp, x);
        result += fixp_mul(temp, den_1[1]);
        /* 4th iteration */
        temp = fixp_mul(temp, sqr);
        result -= fixp_mul(temp, den_1[2]);
        /* 5th iteration */
        temp = fixp_mul(temp, x);
        result += fixp_mul(temp, den_1[3]);

    }

    /* invert needed */
    if (inv) {
        result = FIXP_HALF_PI - result;
    }

	return sign * result;
}

/* square root */
fixp_t fixp_sqrt(fixp_t x)
{
    /* temporary variables */
    fixp_t temp, frac, z, result;
    /* square root of 2 */
	const fixp_t sqrt2 = fixp(1.414213562373095048801688e+0);
	/* inverse square root of 2 */
	const fixp_t isqrt2 = fixp(7.071067811865475244008440e-1);
	/* counter */
	int count = 0;
    /* denominators fox x0 = 0 */
	const fixp_t den[8] = {
		fixp(2.5000000000000000000000e-01),
		fixp(5.0000000000000000000000e-01),
        fixp(6.2500000000000000000000e-01),
        fixp(7.0000000000000000000000e-01),
        fixp(7.5000000000000000000000e-01),
        fixp(7.8571428571428571428571e-01),
        fixp(8.1250000000000000000000e-01),
        fixp(8.3333333333333333333333e-01)
	};

	/* sanity check */
	if (x <= 0) {
	    return 0;
	}

	/* big number? */
	if (x >= sqrt2) {
		/* divide by two */
		while (x >= sqrt2) {
			x = x >> 1;
			count++;
		}
	/* small number? */
	} else {
		while (x <= isqrt2) {
			x = x << 1;
			count--;
		}
	}

	/* reduce */
	z = x - FIXP_ONE;
	/* 1st and 2nd iteration */
	temp = z >> 1;
	frac = FIXP_ONE + temp;
	/* 3rd */
	temp = fixp_mul(fixp_mul(temp, z), den[0]);
	frac -= temp;
	/* 4th */
	temp = fixp_mul(fixp_mul(temp, z), den[1]);
	frac += temp;
    /* 5th */
    temp = fixp_mul(fixp_mul(temp, z), den[2]);
    frac -= temp;
    /* 6th */
    temp = fixp_mul(fixp_mul(temp, z), den[3]);
    frac += temp;
    /* 7th */
    temp = fixp_mul(fixp_mul(temp, z), den[4]);
    frac -= temp;
    /* 8th */
    temp = fixp_mul(fixp_mul(temp, z), den[5]);
    frac += temp;
    /* 8th */
    temp = fixp_mul(fixp_mul(temp, z), den[6]);
    frac -= temp;
    /* 9th */
    temp = fixp_mul(fixp_mul(temp, z), den[7]);
    frac += temp;

	/* base */
	result = FIXP_ONE;

	/* apply extracted twos */
	if (count > 0) {
		/* full two's */
		result = FIXP_ONE << (count / 2);
		/* one bit might be left */
		if (count & 1) {
			/* additonal sqrt of two */
			result = fixp_mul(result, sqrt2);
		}
	/* apply extracted halves */
	} else if (count < 0) {
		/* get rid of negation :) */
		count = -count;
		/* extract halves */
		result = FIXP_ONE >> (count / 2);
		/* one bit might be left */
		if (count & 1) {
			/* additonal inversion of sqrt of two */
			result = fixp_mul(result, isqrt2);
		}
	}

	/* final form! :) */
	return fixp_mul(result, frac);
}

/* return arcus sinus */
fixp_t fixp_asin(fixp_t x)
{
    /* temporary variables */
    fixp_t temp, frac, z, sqr;
    /* arcus sine of 0.95 */
    const fixp_t asin_095 = fixp(1.2532358975033752587371039e+00);
    /* arcus sine of 0.99 */
    const fixp_t asin_099 = fixp(1.4292568534704694004855323e+00);
    /* value of 0.95 */
    const fixp_t val_095 = fixp(9.5000000000000000000000000e-01);
    /* value of 0.90 */
    const fixp_t val_090 = fixp(9.0000000000000000000000000e-01);
    /* value of 0.95 */
    const fixp_t val_098 = fixp(9.8000000000000000000000000e-01);
    /* value of 0.99 */
    const fixp_t val_099 = fixp(9.9000000000000000000000000e-01);
    /* denominators fox x0 = 0 */
	const fixp_t den_0[] = {
		fixp(1.6666666666666666666667e-01),
		fixp(4.5000000000000000000000e-01),
        fixp(5.9523809523809523809524e-01),
        fixp(6.8055555555555555555556e-01)
	};

    /* denominators fox x0 = 0.95 (radius (0.05)) */
	const fixp_t den_1[] = {
	    fixp(3.2025630761017426696651e+00),
	    fixp(4.8717948717948717948718e+00),
		fixp(1.0094466936572199730094e+01),
        fixp(1.2518168106403400521047e+01)
	};

    /* denominators fox x0 = 0.99 (radius (0.01)) */
	const fixp_t den_2[] = {
	    fixp(7.0888120500833590076543e+00)
	};

	/* stuff :) */
	int neg = 1;

	/* absolute value */
	if (x < 0) {
	    x = -x;
	    neg = -1;
	}

	/* limit valuest set */
	if (x > FIXP_ONE) {
	    x = FIXP_ONE;
	}

	/* calculate for x0 = 0 */
	if (x < val_090) {
	    /* no offset needed */
	    z = x;
	    /* square */
	    sqr = fixp_mul(z, z);
	    /* 1st term */
	    temp = z;
	    frac = temp;
	    /* 2nd term */
	    temp = fixp_mul(fixp_mul(temp, sqr), den_0[0]);
	    frac += temp;
	    /* 3rd term */
	    temp = fixp_mul(fixp_mul(temp, sqr), den_0[1]);
	    frac += temp;
	    /* 4th term */
	    temp = fixp_mul(fixp_mul(temp, sqr), den_0[2]);
	    frac += temp;
	    /* 5th term */
	    temp = fixp_mul(fixp_mul(temp, sqr), den_0[3]);
	    frac += temp;
	/* computation for x0 = 0.95 */
	} else if (x < val_098) {
	    /* offset needed */
	    z = x - val_095;
        /* 1st term */
	    frac = asin_095;
	    /* 2nd term */
	    temp = fixp_mul(z, den_1[0]);
	    frac += temp;
	    /* 3rd term */
	    temp = fixp_mul(fixp_mul(temp, z), den_1[1]);
	    frac += temp;
	    /* 4th term */
	    temp = fixp_mul(fixp_mul(temp, z), den_1[2]);
	    frac += temp;
	    /* 5th term */
	    temp = fixp_mul(fixp_mul(temp, z), den_1[3]);
	    frac += temp;
	} else {
	    /* offset needed */
	    z = x - val_099;
        /* 1st term */
	    frac = asin_099;
	    /* 2nd term */
	    temp = fixp_mul(z, den_2[0]) * 2;
	    frac += temp;
	}

	/* limit */
	if (frac > FIXP_HALF_PI) {
	    frac = FIXP_HALF_PI;
	}

	return frac * neg;
}

/* return arcus tangent 2 */
fixp_t fixp_atan2(fixp_t y, fixp_t x)
{
	fixp_t result = 0, inv_x, arg;

	/* Calculate reciprocal of x */
	inv_x = fixp_rec(x);
	/* divide */
	arg = fixp_mul(y, inv_x);

	if (x > 0) {
		result = fixp_atan(arg);
	} else if (y >= 0 && x < 0) {
		result = fixp_atan(arg) + FIXP_PI;
	} else if (y < 0 && x < 0) {
		result = fixp_atan(arg) - FIXP_PI;
	} else if (y > 0 && x == 0) {
		result = FIXP_HALF_PI;
	} else if (y < 0 && x == 0) {
		result = -FIXP_HALF_PI;
	}

	return result;
}


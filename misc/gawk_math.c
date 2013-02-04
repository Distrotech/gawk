/*
 * gawk_math.c - routines for replacement AWKLDBL math functions.
 */

/* 
 * Copyright (C) 2013 the Free Software Foundation, Inc.
 * 
 * This file is part of GAWK, the GNU implementation of the
 * AWK Programming Language.
 * 
 * GAWK is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * GAWK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */


#define _0L	LDC(0.0)
#define _1L	LDC(1.0)
#define _2L	LDC(2.0)
#define _3L	LDC(3.0)
#define _4L	LDC(4.0)

/*
 * Constants for computation using long doubles with enough digits for the 128-bit quad.
 */

#define	GAWK_LOG2	LDC(0.693147180559945309417232121458176568)  /* log 2 (base e) */
#define	GAWK_LOG2_HIGH	LDC(0.6931471801362931728363037109375)       /* high 32 bits (exact representation) */
#define	GAWK_LOG2_LOW	LDC(4.236521365809284105206765680755001344e-10)	/* variable precision low bits */

#define	GAWK_SQRT2	LDC(1.414213562373095048801688724209698079)	/* sqrt(2) */
#define	GAWK_SQRT1_2	LDC(0.707106781186547524400844362104849039)	/* 1/sqrt(2) */

#define	GAWK_PI		LDC(3.141592653589793238462643383279502884)	/* pi */
#define	GAWK_PI_2	LDC(1.570796326794896619231321691639751442)	/* pi/2 */
#define	GAWK_PI_4	LDC(0.785398163397448309615660845819875721)	/* pi/4 */
#define	GAWK_PI_4_HIGH	LDC(0.78539816313423216342926025390625)		/* 32-bit 1st part */
#define	GAWK_PI_4_MED	LDC(2.632161460363116600724708860070677474e-10)	/* 32-bit 2nd part */
#define	GAWK_PI_4_LOW	LDC(1.500889318411548350422246024296643642e-19)	/* variable precision 3rd part */

static AWKLDBL taylor_exp(AWKLDBL x);
static AWKLDBL taylor_cos(AWKLDBL x);
static AWKLDBL taylor_sin(AWKLDBL x);
static AWKLDBL euler_atan_1(AWKLDBL x);
static AWKLDBL gawk_frexpl(AWKLDBL x, int *exponent);

/* gawk_sinl --- Compute sin(x) */

static AWKLDBL
gawk_sinl(AWKLDBL x)
{
	AWKLDBL sinval, dq;
	int sign = 1;

	if (isinf(x) || isnan(x))
		return GAWK_NAN;

	if (x == _0L)	/* XXX: sin(-0.0) = -0.0 */
		return x;

	if (x < _0L) {
		/* sin(-x) = - sin(x) */
		sign = -1;
		x = -x;
	}

	/* range reduction -- 0 <= x < pi / 4 */

	dq = double_to_int(x / GAWK_PI_4);

	if (dq < pow2ld(32)) {
		gawk_uint_t q = (gawk_uint_t) dq; 

		sign *= ( (q / 4) % 2 ? -1 : 1 );
		switch (q % 4) {
		case 0:
			x -= q * GAWK_PI_4_HIGH;
			x -= q * GAWK_PI_4_MED;
			x -= q * GAWK_PI_4_LOW;
			sinval = taylor_sin(x);
			break;
		case 1:
			q++;
			x -= q * GAWK_PI_4_HIGH;
			x -= q * GAWK_PI_4_MED;
			x -= q * GAWK_PI_4_LOW;
			sinval = taylor_cos(-x);
			break;
		case 2:
			x -= q * GAWK_PI_4_HIGH;
			x -= q * GAWK_PI_4_MED;
			x -= q * GAWK_PI_4_LOW;
			sinval = taylor_cos(x);
			break;
		case 3:
			q++;
			x -= q * GAWK_PI_4_HIGH;
			x -= q * GAWK_PI_4_MED;
			x -= q * GAWK_PI_4_LOW;
			sinval = taylor_sin(-x);
			break;
		default:
			break;
		}
	} else {
		/* FIXME -- Payne and Hanek Reduction Algorithm ? */

		sinval = (AWKLDBL) sin( (double) x);
	}

	return sign > 0 ? sinval : -sinval;
}

/* gawk_cosl --- Compute cos(x) */

static AWKLDBL
gawk_cosl(AWKLDBL x)
{
	AWKLDBL cosval, dq;
	int sign = 1;

	if (isinf(x) || isnan(x))
		return GAWK_NAN;
	if (x < _0L) {
		/* cos(-x) = cos(x) */
		x = -x;
	}
	if (x == _0L)
		return _1L;

	/* range reduction -- 0 <= x < pi / 4 */

	dq = double_to_int(x / GAWK_PI_4);

	if (dq < pow2ld(32)) {
		gawk_uint_t q = (gawk_uint_t) dq; 

		sign *= ( (q / 4) % 2 ? -1 : 1 );
		switch (q % 4) {
		case 0:
			x -= q * GAWK_PI_4_HIGH;
			x -= q * GAWK_PI_4_MED;
			x -= q * GAWK_PI_4_LOW;
			cosval = taylor_cos(x);
			break;
		case 1:
			q++;
			x -= q * GAWK_PI_4_HIGH;
			x -= q * GAWK_PI_4_MED;
			x -= q * GAWK_PI_4_LOW;
			cosval = taylor_sin(-x);
			break;
		case 2:
			x -= q * GAWK_PI_4_HIGH;
			x -= q * GAWK_PI_4_MED;
			x -= q * GAWK_PI_4_LOW;
			cosval = -taylor_sin(x);
			break;
		case 3:
			q++;
			x -= q * GAWK_PI_4_HIGH;
			x -= q * GAWK_PI_4_MED;
			x -= q * GAWK_PI_4_LOW;
			cosval = -taylor_cos(-x);
			break;
		default:
			break;
		}
	} else {
		/* FIXME Payne and Hanek Reduction Algorithm ? */

		cosval = (AWKLDBL) cos( (double) x);
	}

	return sign > 0 ? cosval : -cosval;
}


/* gawk_atan2l(x) --- Compute atan2(y, x) */

static AWKLDBL
gawk_atan2l(AWKLDBL y, AWKLDBL x)
{
	int sign;

	/*
	 * Using Euler atan(1/x) and the identity:
	 * 	atan(x) = - pi / 2 - atan(1/x),		x < 0
	 *       	= pi / 2 - atan(1/x),		x > 0
	 */

	if (isnan(x) || isnan(y))
		return GAWK_NAN;

	if (isinf(y)) {
		if (y > _0L) {
			if (isinf(x))
				return x < _0L ? _3L * GAWK_PI_4 : GAWK_PI_4;
			return GAWK_PI_2;
		}
		if (isinf(x))
			return x < _0L ? -_3L * GAWK_PI_4 : -GAWK_PI_4;
		return -GAWK_PI_2;
	}

	if (isinf(x)) {
		if (x > _0L)
			return y < _0L ? -_0L : _0L;
		/* x = -Infinity */
		return (y >= _0L) ? GAWK_PI : -GAWK_PI;
	}

	if (x > _0L) {
		if (y == _0L)
			return y;	/* +0 or -0 */
		sign = 1;
		if (y < _0L) {
			sign = -1;
			y = -y;
		}
		if (y > x)
			return sign * (GAWK_PI_2 - euler_atan_1(y / x));
		return sign * euler_atan_1(x / y);
	}

	if (x < _0L) {
		if (y == _0L)
			return atan2( (double) y, -_1L) < 0.0 ? -GAWK_PI : GAWK_PI;

		x = -x;
		if (y < _0L) {
			y = -y;
			if (y > x)
				return -GAWK_PI_2 - euler_atan_1(y / x);
			return euler_atan_1(x / y) - GAWK_PI;
		}
		/* y > 0 */
		if (y > x)
			return GAWK_PI_2 + euler_atan_1(y / x);
		return - euler_atan_1(x / y) + GAWK_PI;
	}

	/*
	 * XXX -- using atan2 instead of trying to detect +0 or -0. No need for signbit(x)!
	 * We need to make sure the value of y is in the double range;
	 * Replace positive (negative) y with 1 (-1), the actual value isn't important.
	 */

	if ( y > _0L)
		y = _1L;
	else if (y < _0L)
		y = -_1L;

	/* x = +0 or -0 */
	if (atan2( (double) y, (double) x) < 0.0)
		return -GAWK_PI;
	if (atan2( (double) y, (double) x) > 0.0)
		return GAWK_PI;
	/* x = +0 and y = +0 or -0 */
	return _0L;
}


/* gawk_logl --- Compute log(x) */

static AWKLDBL
gawk_logl(AWKLDBL x)
{
	AWKLDBL frac, exponent;
	AWKLDBL y, ypow2, ypow_odd, sum, term, err;
	int iexp, sign, i;
	
	/*
	 *	ln(x) = 2 * arctanh(y)
	 *	      = 2 * (y + y^3 / 3 + y^5 / 5 + ..) where y = (x - 1) / (x + 1) 
	 */

	if (isnan(x) || (isinf(x) && x > _0L))
		return x;
	if (x < _0L)		/* XXX: not setting errno = EDOM */
		return GAWK_NAN;
	if (x == _0L)		/* XXX: not setting errno = ERANGE */
		return -GAWK_INFINITY;
	
	if (x == _1L)	/* special case */
		return _0L;
	if (x == _2L)	/* special case */
		return GAWK_LOG2;

	frac = gawk_frexpl(x, & iexp);	/* frac in [1, 2) */
	exponent = (AWKLDBL) iexp;


	/*
	 * arctanh(x) series has faster convergence when x is close to 1.
	 * Perform a range reduction so that 1 / sqrt(2) <= x <= sqrt(2).
	 */

	if (frac > GAWK_SQRT2 || frac < GAWK_SQRT1_2) {
		/*
		 * Instead of frac = frac / sqrt(2), compute y directly:
		 * 	y = (f /sqrt(2) - 1) / (f / sqrt(2) + 1)
		 *	  = (f - sqrt(2)) / (f + sqrt(2))
		 */

		y = (frac - GAWK_SQRT2) / (frac + GAWK_SQRT2);
		exponent += LDC(0.5);
	} else
		y = (frac - _1L) / (frac + _1L);

	if (y == _0L)	/* tricky special case */
		return exponent * GAWK_LOG2;

	sign = 1;
	if (y < _0L) {
		sign = -1;
		y = -y;
	}

	i = 1;
	ypow2 = y * y;
	ypow_odd = y;
	sum = y;
	do {
		ypow_odd *= ypow2;
		i += 2;
		term = ypow_odd / ((AWKLDBL) i);
		sum += term;
		err = term / sum;
	} while (err > REL_ERROR);
	sum = LDC(2.0) * sum + exponent * GAWK_LOG2;

	return (sign > 0 ? sum : -sum);
}

/* gawk_expl --- Compute exp(x) */

static AWKLDBL
gawk_expl(AWKLDBL x)
{
	AWKLDBL expval, k = _0L;
	int sign;

	if (isnan(x) || (isinf(x) && x > _0L))
		return x;
	if (isinf(x))	/* -inf */
		return _0L;
	if (x == _0L)
		return _1L;
	if (x >= (AWKLDBL) LDBL_MAX_EXP * GAWK_LOG2)	/* overflow */
		return GAWK_INFINITY;
	if (x <= (AWKLDBL) (LDBL_MIN_EXP - LDBL_MANT_DIG - 1) * GAWK_LOG2)	/* underflow */
		return _0L;

	sign = 1;
	if (x < _0L) {
		sign = -1;
		x = -x;
	}

	/* XXX: Outside overflow and underflow range k has at most 14 bits. */
	if (x >= GAWK_LOG2)
		k = double_to_int(x / GAWK_LOG2);  

	if (k == _0L)
		expval = taylor_exp(x);
	else {
		/* range reduction -- 0 < x < log(2) (0.693...) */

		AWKLDBL y;

		/* High precision calculation using limited precision float */
		/*
		 * We need to calculate x - k * log2 with extra precision. If k is not a power
		 * of 2, it would require more than LDBL_MANT_DIG bits for the product
		 * to be precise to LDBL_MANT_DIG bits.
 		 */

		y = x - k * GAWK_LOG2_HIGH;
		y -= k * GAWK_LOG2_LOW;

#if 0
		if (y > GAWK_LOG2 || y < _0L)	/* kludge */
			return sign > 0 ? GAWK_INFINITY : _0L;
#endif
		expval = taylor_exp(y);
		expval *= pow2ld((unsigned int) k);
	}

	return sign < 0 ? (_1L / expval) : expval;
}

static AWKLDBL
gawk_fmodl(AWKLDBL x, AWKLDBL y)
{
	return fmod( (double) x, (double) y);
}


#define	GAWK_LDBL_INTEGER	1
#define	GAWK_LDBL_EVEN_INTEGER	2
#define	GAWK_LDBL_ODD_INTEGER	4

/* gawk_is_integer__p --- is x an (even or odd) integer ? */

static unsigned int
gawk_is_integer__p(AWKLDBL x)
{
	AWKLDBL ival;
	unsigned ret = 0;

	if (isnan(x) || isinf(x))
		return (unsigned int) false;
	if (x < _0L)
		x = -x;
	if (x < _1L)
		return (unsigned int) false;
	if ((ival = double_to_int(x)) != x)
		return (unsigned int) false;
	ret = GAWK_LDBL_INTEGER;
	if (ival >= pow2ld(LDBL_MANT_DIG))
		ret |= GAWK_LDBL_EVEN_INTEGER;
	else {
		ival /= _2L;
		if (ival == double_to_int(ival))
			ret |= GAWK_LDBL_EVEN_INTEGER;
		else
			ret |= GAWK_LDBL_ODD_INTEGER;
	}
	return ret;
}

#define gawk_is_integer(x)	((gawk_is_integer__p(x) & GAWK_LDBL_INTEGER) != 0)
#define gawk_is_odd_integer(x)	((gawk_is_integer__p(x) & GAWK_LDBL_ODD_INTEGER) != 0)

/* gawk_powl --- Compute x^y */

static AWKLDBL
gawk_powl(AWKLDBL x, AWKLDBL y)
{
	AWKLDBL expval;
	int sign;

	if ((! isnan(x) && x == _1L) || (! isnan(y) && y == _0L))
		return _1L;
	if (isnan(x) || isnan(y))
		return GAWK_NAN;

	/* Neither x or y is NaN and y isn't 0 */
	if (isinf(x)) {
		if (x > _0L)
			return y < _0L ? _0L : GAWK_INFINITY;

		/* x == -inf */
		if (y < _0L)
			return (! isinf(y) && gawk_is_odd_integer(y)) ? -_0L : _0L;
		if (y > _0L)
			return (! isinf(y) && gawk_is_odd_integer(y)) ? -GAWK_INFINITY : GAWK_INFINITY;

	} else {
		/* x isn't infinity */
		if (x < _0L && ! isinf(y) && ! gawk_is_integer(y)) 
			return GAWK_NAN;

		if (isinf(y)) {
			if (x == -_1L)
				return _1L;
			/* x == +1 handled above */
			if (x > -_1L && x < _1L)
				return (y == -GAWK_INFINITY) ? GAWK_INFINITY : _0L;
			/* abs(x) > 1 */
			return (y < _0L) ? _0L : GAWK_INFINITY;
		}

		/* y isn't infinity */
		if (x == _0L && y > _0L)
			return gawk_is_odd_integer(y) ? x : _0L;

		if (x == _0L && y < _0L) {
			if (gawk_is_odd_integer(y))	/* HUGE_VALL with same sign as x */
				return (AWKLDBL) pow((double) x, (double) y);
			/* + HUGE_VALL */
			return GAWK_INFINITY;
		}
	}

	sign = 1;
	if (y < _0L) {
		sign = -1;
		y = -y;
	}

	if (x < _0L) {
		AWKLDBL result, d;

		/* y is integer and != 0 */

		result = x;
		for (d = _1L; d < y; d += _1L)
			result *= x;
		return sign > 0 ? result : _1L / result;
	}

	/* x^y =  exp(y * log(x)), x > 0 */

	if (y <= (AWKLDBL) GAWK_UINT_MAX) {
		AWKLDBL frac;
		gawk_uint_t intpart;

		/*
		 * divide y into integral and fractional parts, use "repeated squaring"
	 	 * to compute x^integer and exp(fraction * log(x)) for the fractional power.
	 	 */

		intpart = (gawk_uint_t) double_to_int(y);
		frac = y - (AWKLDBL) intpart;
		expval = _1L;
		if (intpart > 0) {
			AWKLDBL z = x;
			while (intpart > 1) {
				if ((intpart % 2) == 1)
					expval *= z;
				z *= z;
				intpart /= 2;
			}
			expval *= z;
		}
		expval *= gawk_expl(frac * gawk_logl(x));
	} else
		expval = gawk_expl(y * gawk_logl(x));	/* XXX: likely infinity or zero */ 

	return sign > 0 ? expval : (_1L / expval);
}

/* gawk_sqrtl --- Compute sqrt(x) using Newton's method */

static AWKLDBL
gawk_sqrtl(AWKLDBL x)
{
	AWKLDBL yn;

	if (isnan(x) || (isinf(x) && x > _0L))	/* NaN or +inf */
		return x;
	if (isinf(x) || x < _0L)	/* -inf or negative */
		return GAWK_NAN;	/* XXX: not setting errno = EDOM */
	if (x == _0L)
		return x;	/* return +0 or -0 */

	if (x <= DBL_MAX && x >= DBL_MIN) {
		/* use double-precision sqrt value as the initial guess. */

		yn = sqrt( (double) x);
	} else {
		/*
		 * outside of the range of C double, we have to compute
		 * the initial guess differently.
		 */

		AWKLDBL frac;
		int iexp;

		frac = gawk_frexpl(x, & iexp);	/* frac is in [1, 2) */
		if ((iexp % 2) != 0) {
			/* force the exponent to be an even integer */ 
			frac /= _2L;
			iexp++;
		}
		yn = sqrt( (double) frac);
		iexp /= 2;
		if (iexp >= 0)
			yn *= pow2ld(iexp);
		else
			yn /= pow2ld(-iexp);
	}

	/* XXX: Exactly 3 iterations. 2 maybe enough ? */
	yn = (yn + x / yn) / _2L;
	yn = (yn + x / yn) / _2L;
	yn = (yn + x / yn) / _2L;

	return yn;
}


/*
 * gawk_frexpl --- split the number x into a normalized fraction and an exponent.
 *	The fraction is in the range [1, 2) (and NOT [0.5, 1)).
 */

static AWKLDBL
gawk_frexpl(AWKLDBL x, int *exponent)
{
	AWKLDBL y;
	unsigned low, high, mid;

	/* (isnormal(x) && x > 0) is assumed to be true */

	assert(exponent != NULL);
	*exponent = 0;

	low = 0;
	if (x > _2L) {
		high = LDBL_MAX_EXP - 1;	/* XXX: should be 4 * LDBL_MAX_EXP - 1 if FLT_RADIX = 16 ? */
		while (low <= high) {
			mid = (low + high) / 2;
			y = x / pow2ld(mid);
			if (y > _2L)
				low = mid + 1;
			else
				high = mid - 1;
		}
		x /= pow2ld(low);
		*exponent = low;
	} else if (x < _1L) {
		high = LDBL_MAX_EXP - 1;	/* could be -LDBL_MIN_EXP, but no harm in using LDBL_MAX_EXP */
		while (low <= high) {
			mid = (low + high) / 2;
			y =  x * pow2ld(mid);
			if (y < _1L)
				low = mid + 1;
			else
				high = mid - 1;
		}
		x *= pow2ld(low);
		*exponent = -low;
	}
	if (x == _2L) {
		x = _1L;
		++*exponent;
	}
	return x;
}

/* taylor_exp --- Compute exp(x) using Taylor series and modified squaring reduction */

static AWKLDBL
taylor_exp(AWKLDBL x)
{
	AWKLDBL xpow, expval;
	AWKLDBL err, term, y, fact;
	unsigned int i;
	int k;

	/*
	 * Method: Taylor series and squaring for large x.
	 *	exp(x) = 1 + x + x ^ 2 / 2! + x ^ 3 / 3! + ..., x < 1 
	 *
	 *	A modification of the squaring reduction allows to significantly reduce the
 	 *	round-off error [*]. Instead of exp(x) = exp(x/2)^2, we use the identity
 	 *		exp(x) - 1 = (exp(x/2) - 1)*(exp(x/2) + 1)
 	 *	and reduce exp(x) - 1 directly to exp(x/2) - 1. If y = exp(x/2) - 1, then
 	 *		exp(x) - 1 = 2*y + y^2.
 	 *
 	 *	[*] R. P. Brent, A Fortran Multiple-Precision Arithmetic Package,
	 *	ACM Transactions on Mathematical Software 4, no. 1 (1978), p. 57. 
	 */

	if (x == _0L)
		return _1L;

	k = 1;
	while (x > LDC(0.001)) {
		/* XXX: For x <= 0.001, max(k) = 10, and max # of terms 6 (80-bit) / 10 (128-bit) */
		
		x /= _2L; 
		k++;
	}

	y = xpow = x;
	fact = _1L;
	i = 1;
	do {
		fact *= (AWKLDBL) ++i;
		xpow *= x;
		term = xpow / fact;
		y += term;
		err = term / y;
	} while (err > REL_ERROR);

	/* squaring reduction */
	while (--k > 0)
		y = 2 * y + y * y;
	return y + _1L;
}

/* taylor_sin --- Compute sin(x) using Taylor series */

static AWKLDBL
taylor_sin(AWKLDBL x)
{
	AWKLDBL xpow, xpow_odd, sinval;
	AWKLDBL err, term, fact;
	unsigned int i;

	assert(x >= _0L);

	if (x == _0L)
		return x;

	i = 3;
	fact = LDC(6.0);	/* 3! */
	xpow = x * x;
	xpow_odd = xpow * x;
	sinval = x - xpow_odd / fact;

	do {
		fact *= (AWKLDBL) ((i + 1) * (i + 2));
		i += 2;
		xpow_odd *= xpow;
		term = xpow_odd / fact;

		fact *= (AWKLDBL) ((i + 1) * (i + 2));
		i += 2;
		xpow_odd *= xpow;
		term -= xpow_odd / fact;

		sinval += term;
		err = term / sinval;
	} while (err > REL_ERROR);
	return sinval;
}

/* taylor_cos --- Compute cos(x) using Taylor series */

static AWKLDBL
taylor_cos(AWKLDBL x)
{
	AWKLDBL xpow, xpow_even, cosval;
	AWKLDBL err, term, fact;
	unsigned int i;

	if (x == _0L)
		return _1L;

	i = 2;
	fact = _2L;	/* 2! */
	xpow = x * x;
	xpow_even = xpow;
	cosval = _1L - xpow / fact;

	do {
		fact *= (AWKLDBL) ((i + 1) * (i + 2));
		i += 2;
		xpow_even *= xpow;
		term = xpow_even / fact;

		fact *= (AWKLDBL) ((i + 1) * (i + 2));
		i += 2;
		xpow_even *= xpow;
		term -= xpow_even / fact;

		cosval += term;
		err = term / cosval;
	} while (err > REL_ERROR);
	return cosval;
}

/* euler_atan_1 --- Compute Euler arctan(1/x) approximation */ 

static AWKLDBL
euler_atan_1(AWKLDBL x)
{
	AWKLDBL xpow2_plus_one, term, sum, err;
	int sign = 1;
	unsigned int i;

	/*
	 * Euler atan formula (http://mathworld.wolfram.com/InverseTangent.html):
 	 *	atan(x) = (y/x) (1 + 2/3 y + (2·4)/(3·5) y^2 + (2·4·6)/(3·5·7) y^3 + ...)
	 *  where
	 *	y = (x^2) / (1 + x^2) and -1 <= x <= 1
	 *
	 * Substituting x = 1/x, for x >= 1
	 * 	atan(1/x) = (x / (1 + x^2))    + (2/3) * (x / (1 + x^2)^2)
	 *	                               + (2*4/(3*5)) * (x / (1 + x^2)^3)
	 *	                               + (2*4*6/(3*5*7)) * (x / (1 + x^2)^4) + ...
	 */

	if (x < _0L) {
		sign = -1;
		x = -x;
	}

	xpow2_plus_one = x * x + _1L;
	term = x / xpow2_plus_one;
	sum = term;
	i = 0;

	do {
		term *= (AWKLDBL) (i + 2);
		term /= ((AWKLDBL) (i + 3)) * xpow2_plus_one;
		i += 2;
		sum += term;
		err = term / sum;
	} while (err > REL_ERROR);

	return sign > 0 ? sum : -sum;
}

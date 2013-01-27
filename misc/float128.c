/*
 * float128.c - routines for a quad-precision (binary 128) floating-point.
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

#include "awk.h"

#if defined(LDBLTEST) && LDBLTEST == 1
#include <math.h>
#include "random.h"
#if 0
#include "floatmagic.h"	/* definition of isnan -- XXX: only for float or double or long double */
#endif

#include "format.h"

#include <gmp.h>
#include <mpfr.h>
#ifndef MPFR_RNDN
/* for compatibility with MPFR 2.X */
#define MPFR_RNDN GMP_RNDN
#define MPFR_RNDZ GMP_RNDZ
#define MPFR_RNDU GMP_RNDU
#define MPFR_RNDD GMP_RNDD
#endif

/* XXX: No libquadmath, and don't want or need it anyway. */

/*
 * Macros copied from quadmath.h
 * 	https://github.com/mirrors/gcc/blob/master/libquadmath/quadmath.h
 */

#define FLT128_MAX 1.18973149535723176508575932662800702e4932Q
#define FLT128_MIN 3.36210314311209350626267781732175260e-4932Q
#define FLT128_EPSILON 1.92592994438723585305597794258492732e-34Q
#define FLT128_DENORM_MIN 6.475175119438025110924438958227646552e-4966Q
#define FLT128_MANT_DIG 113
#define FLT128_MIN_EXP (-16381)
#define FLT128_MAX_EXP 16384
#define FLT128_DIG 33
#define FLT128_MIN_10_EXP (-4931)
#define FLT128_MAX_10_EXP 4932

/* #define HUGE_VALQ __builtin_huge_valq() */
/* The following alternative is valid, but brings the warning:
   (floating constant exceeds range of ‘__float128’)  */
#define HUGE_VALQ (__extension__ 0x1.0p32767Q)

#define IEEE_FLOAT128_BIAS 0x3fff

/* end of Macros from quadmath.h */


#define LDBL_FRAC_BITS	FLT128_MANT_DIG
#define	LDBL_INT_BITS	128

#define AWKLDBL	__float128
#define LDBL_VAL(n)	(*((AWKLDBL *) (n)->qnumbr))
#define LDC(x)		x##Q

#define get_long_double(d)	emalloc(d, void *, sizeof(AWKLDBL), "float128")
#define free_long_double(d)	efree(d)

/* we want to format integers ourself */
#define GAWK_FMT_INT 1

#define gawk_int_t long long
#define gawk_uint_t unsigned long long
#ifdef SIZEOF_GAWK_INT
#undef SIZEOF_GAWK_INT
#undef GAWK_INT_MAX
#undef GAWK_INT_MIN
#undef GAWK_UINT_MAX
#endif

#define SIZEOF_GAWK_INT	8
#define	GAWK_INT_MAX	LLONG_MAX
#define	GAWK_INT_MIN	LLONG_MIN
#define	GAWK_UINT_MAX	ULLONG_MAX

static int format_uint_finite_p(char *str, size_t size, AWKLDBL x);
static AWKLDBL gawk_floorl_finite_p(AWKLDBL x, gawk_uint_t *chunk);
static int format_float_1(char *str, size_t size, const char *format, int fw, int prec, AWKLDBL x);
static inline int format_uint_1(char *str, size_t size, AWKLDBL x);
static AWKLDBL double_to_int(AWKLDBL x);

static __float128 strtofloat128(const char *str, char **endptr);
#define gawk_strtold strtofloat128

#if 0
/* if have __float128, also have strtold. No ? */

static inline AWKLDBL
gawk_strtold(const char *str, char **endptr)
{
	return strtold(str, endptr);
}
#endif

#define GAWK_INFINITY	HUGE_VALQ
#define GAWK_NAN	(LDC(0.0) / LDC(0.0))

/* Define isnan() and isinf() before including the two .h files */

static inline int isnan_awkldbl(AWKLDBL x) { return x != x; }
#ifdef isnan
#undef isnan
#endif
#define isnan isnan_awkldbl

static inline int isinf_awkldbl(AWKLDBL x) { return isnan(x - x); }
#ifdef isinf
#undef isinf
#endif
#define isinf isinf_awkldbl

numbr_handler_t float128_hndlr;

#define awkldbl_hndlr float128_hndlr

#define TEST_NUMBR 1

#include "misc/gawk_math.h"
#include "long_double.h"
#include "misc/gawk_math.c"


/* XXX: This is for little-endian architecture only */
typedef union {
	__float128  val;

	/* 64 mantissa LSBs */
	/* 48 mantissa MSBs */
	/* 15 exponent bits */
	/* 1 sign bit */

	struct {
		uint8_t si[14];
		uint16_t se;
	} w1;
	struct {
		uint64_t low;
		uint64_t high;
	} w2;
} gfloat128_t;


/* hex_to_float128 --- hexadecimal string to __float128 conversion */

static __float128
hex_to_float128(const char *hexstr)
{
	int sign, leading_bit, exp_sign;
	char *p;
	uint8_t ch, leading_hex;
	int exponent;
	int i, k;
	gfloat128_t fv;

	memset(& fv, '\0', sizeof (gfloat128_t));
	
	p = (char *) hexstr;
	/* optional sign */
	sign = 0;
	if (*p == '-') {
		sign = 1;
		p++;
	} else if (*p == '+')
		p++;

#define XX (('a' - '0') - 10)

	/* optional "0x" prefix */
	if (*p == '0' && *(p + 1) == 'x')
		p += 2;

	leading_bit = 0;
	k = 0;
	if (*p != '0') {
		/* normalized number */
		leading_hex = ch = (uint8_t)((*p - '0') % XX);
		while (ch >= 2) {
			ch /= 2;
			k++;
		}		
		leading_bit = 1;
	}
	p++;

	if (*p == '.')	/* may not have a decimal point: 0xfp+0 */
		*p++;

	/* maximum of 28 hex digits */
	for (i = 13; i >= 0; i--) {
		if (*p == 'p')
			break;
		ch = (uint8_t) ((*p++ - '0') % XX) ;
		fv.w1.si[i] |= (ch << 4);
		if (*p == 'p')
			break;
		ch = (uint8_t) ((*p++ - '0') % XX);
		fv.w1.si[i] |= ch;
	}

	if (k > 0) {
		/* normalized number leading digit not 1; 1 <= k <= 3 */
		/* shift mantissa to right by k; adjust 4 MSBs */
		fv.w2.low = fv.w2.low >> k;	/* drop k LSBs from low part */
		fv.w2.low |= (fv.w2.high << (64 - k));	/* move k LSBs from low to MSBs of high */
		fv.w2.high = fv.w2.high >> k;	/* drop k LSBs from high */
		fv.w1.si[13] |= leading_hex << (8 - k);	/* move k LSBs from leading hex digit ... */
		fv.w1.se = 0;	/* clear sign + exponent part */
	}

	*p++;	/* skip `p' */

	/* sign of exponent */
	exp_sign = 0;
	if (*p == '-') {
		exp_sign = 1;
		p++;
	} else if (*p == '+')
		p++;
	exponent = (int) strtol(p, NULL, 10);

	/* adjust exponent for 1 <= significand < 2 */
	if (exp_sign == 0)
		exponent += k;
	else if (exponent > k)
		exponent -= k;
 	else {
		exponent = k - exponent;
		exp_sign = 0;
	}
	assert(exponent >= 0);

	/* calculate biased exponent */
	if (exponent == IEEE_FLOAT128_BIAS - 1 && exp_sign && ! leading_bit)	/* de-normal number */
		exponent = 0;
	else if (leading_bit) {
		if (exp_sign)
			exponent = IEEE_FLOAT128_BIAS - exponent;
		else
			exponent += IEEE_FLOAT128_BIAS;
	}
#if 0
	fprintf(stderr, "======= hex2float=======\n%s\n", hexstr);
	fprintf(stderr, "exponent (biased) = %d\n", exponent);
	fprintf(stderr, "sign = %d\n", sign);
	fprintf(stderr, "significand = %012llx %016llx\n", fv.w2.high, fv.w2.low);
	fprintf(stderr, "========================\n");
#endif
	/* set exponent */
	fv.w1.se |= (uint16_t) exponent;
	/* set sign */
	fv.w1.se |= (uint16_t) (sign << 15);
	return fv.val;
}


/* float128_to_hex --- __float128 to hexadecimal string conversion */

static const char *
float128_to_hex(__float128 x)
{
	static char buf[64];
	char *p; 
	int i, exponent, sign, exp_sign;
	int extra_bit;
	gfloat128_t fv;

	/* XXX: we don't need to handle infinity and nan here. */

	fv.val = x;
	p = buf;

	sign = (fv.w1.se & (1 << 15)) != 0;
	exponent = (fv.w1.se & ((1 << 15) - 1));
	extra_bit = 1;
	exp_sign = 0;

	/* calculate unbiased exponent */
	if (exponent == 0) {
		int nonzero_significand = ((fv.w2.high & ((1ULL << 48) - 1)) | fv.w2.low) != 0;

		extra_bit = 0;
		if (nonzero_significand) {
			exp_sign = 1;
			exponent = IEEE_FLOAT128_BIAS - 1;
		}
	} else if (exponent >= IEEE_FLOAT128_BIAS)
		exponent -= IEEE_FLOAT128_BIAS;
	else {
		exp_sign = 1;
		exponent = -(exponent - IEEE_FLOAT128_BIAS);	
	}

	if (sign)
		*p++ = '-';
	*p++ = extra_bit ? '1' : '0';
	*p++ = '.';

	/* all 28 hex digits -- XXX: quit early if last 64-bits all 0s ? */
	for (i = 13; i >= 0; i--) {
		*p++ = lchbuf[(fv.w1.si[i] & 0xF0) >> 4];
		*p++ = lchbuf[(fv.w1.si[i] & 0x0F)];
	}

	*p++ = 'p';
	*p++ = exp_sign ? '-' : '+';
	sprintf(p, "%d", exponent);	/* decimal exponent */

	/* assert(hex_to_float128(buf) == x); */
	return buf;
}

/*
 * format_float_1 --- format a single AWKLDBL value according to FORMAT.
 *	The value must be finite.
 */

static int
format_float_1(char *str, size_t size, const char *format, int fw, int prec, AWKLDBL x)
{
	char alt_format[32];
	size_t len;
	int ret = -1;
	const char *hexstr;
	mpfr_t ap_float;

	if (isnan(x) || isinf(x)) {
		/* FIXME: ignoring sign */
		if (size < 4)
			return 3;
		strcpy(str, isnan(x) ? "nan" : "inf");
		return 3;
	}

	len = strlen(format);

	/* expect %Lf, %LF, %Le, %LE, %Lg or %LG */
	assert(len >= 2 && format[len - 2] == 'L');
	
	memcpy(alt_format, format, len + 1);
	alt_format[len - 2] = 'R';	/* replace `L' with `R' */ 
	alt_format[len] = alt_format[len - 1];
	alt_format[len - 1] = 'N';	/* rounding mode = MPFR_RNDN */
	alt_format[len + 1] = '\0';

	/* loss-less conversion to hexadecimal string */
	hexstr = float128_to_hex(x);

	/* fprintf(stderr, "hexfloat = %s\n", hexstr); */

	mpfr_init2(ap_float, 113);
	if (mpfr_set_str(ap_float, hexstr, 16, MPFR_RNDN) < 0) {
		/* XXX: Invalid string? can it be? */
		return -1;
	}

	ret = mpfr_snprintf(str, size, alt_format, fw, prec, ap_float);
	mpfr_clear(ap_float);
	return ret;
}

/*
 * format_uint_1 --- format a long double as an unsigned integer. The double value
 *	must be finite and >= 0.
 */

static inline int
format_uint_1(char *str, size_t size, AWKLDBL x)
{
	int ret;
	if ((ret = format_uint_finite_p(str, size, x)) < 0) {
		/* outside useful range */
		/* FIXME -- use format_float_1 (MPFR) */
		return snprintf(str, size, "%.0Lf", (long double) x);
	}
	return ret;
}

/* double_to_int --- convert double to int, used in several places */

static AWKLDBL
double_to_int(AWKLDBL x)
{
	AWKLDBL intval;
	int sign = 1;

	if (isnan(x) || isinf(x) || x == LDC(0.0))
		return x;
	if (x < LDC(0.0)) {
		sign = -1;
		x = -x;
	}
	if ((intval = gawk_floorl_finite_p(x, NULL)) < LDC(0.0)) {
		/* outside range */
		/* FIXME -- use format_float_1 with "%.0Lf" (MPFR) */
		intval = (AWKLDBL) floorl((long double) x);
	}
	return intval * ((AWKLDBL) sign);
}

/* strtofloat128 --- convert string to __float128 */

static __float128
strtofloat128(const char *str, char **endptr)
{
	static char hexstr[64];
	mpfr_t ap_float;

	/* store as MPFR number */
	mpfr_init2(ap_float, 113);
	(void) mpfr_strtofr(ap_float, str, endptr, 10, MPFR_RNDN);

	/* get back a hexadecimal string representation */
	(void) mpfr_snprintf(hexstr, 64, "%RNa", ap_float);
	mpfr_clear(ap_float);

	/* fprintf(stderr, "hexfloat (mpfr): %s\n", hexstr); */

	return hex_to_float128(hexstr);	
}

#endif	/* LDBLTEST == 1 */

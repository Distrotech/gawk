/*
 * long_double.c - routines for C long double support in gawk.
 */

/* 
 * Copyright (C) 2012 the Free Software Foundation, Inc.
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

#ifdef USE_LONG_DOUBLE

#include <math.h>
#include "random.h"
#include "floatmagic.h"	/* definition of isnan */

#include "format.h"

#define AWKLDBL	long double
#define LDBL_VAL(n)	(*((AWKLDBL *) (n)->qnumbr))
#define LDC(x)		x##L

#ifndef FLT_RADIX
#define FLT_RADIX 2
#endif

/*
 * XXX: LDBL_MANT_DIG is defined if we are here. Assume FLT_RADIX = 2 or 16.
 */
#if FLT_RADIX == 2
#define GAWK_LDBL_FRAC_BITS	LDBL_MANT_DIG
#else
#define GAWK_LDBL_FRAC_BITS	(4 * LDBL_MANT_DIG)
#endif

#define GAWK_LDBL_MAX_EXP	LDBL_MAX_EXP

/*
 * N.B: If printf does not have "%Lf" format and the long double type is capable of
 * supporting integers wider than 64 bits, must have 64-bit long type.
 *
 * We actually use a maximum of 113 bits when GAWK_LDBL_INT_BITS is 128.
 */

#if SIZEOF_GAWK_INT == 8 && GAWK_LDBL_FRAC_BITS > 64
#define	GAWK_LDBL_INT_BITS	128
#else
#define	GAWK_LDBL_INT_BITS	64
#endif

#define get_long_double(d) 	getblock(d, BLOCK_LDBL, AWKLDBL *)
#define free_long_double(d)	freeblock(d, BLOCK_LDBL)

#ifdef USE_INCLUDED_MATH_FUNCS
#include "misc/gawk_math.h"
#else
#define gawk_sinl	sinl
#define gawk_cosl	cosl
#define gawk_atan2l	atan2l
#define gawk_logl	logl
#define gawk_expl	expl
#define gawk_powl	powl
#define gawk_sqrtl	sqrtl
#endif

#ifdef HAVE_FMODL
#define gawk_fmodl	fmodl
#else
static AWKLDBL gawk_fmodl(AWKLDBL x, AWKLDBL y);
#endif

#ifdef HAVE_STRTOLD
#define gawk_strtold	strtold
#else
static inline AWKLDBL
gawk_strtold(const char *str, char **endptr)
{
	return strtod(str, endptr);
}
#endif

#if defined(USE_INCLUDED_MATH_FUNCS) || ! defined(HAVE_FMODL) 
#define GAWK_INFINITY	HUGE_VALL
#define GAWK_NAN	(LDC(0.0) / LDC(0.0))
#if GAWK_LDBL_FRAC_BITS > 64 
#define REL_ERROR	LDC(1.0e-35)
#else
#define REL_ERROR	LDC(1.0e-20)
#endif
#endif

/* N.B: if floorl() or ceill() or "%Lf" is missing format integers ourself */

#if ! (defined(HAVE_FLOORL) && defined(HAVE_CEILL) && defined(PRINTF_HAS_LF_FORMAT)) 
#define GAWK_FMT_INT 1
#endif


#if ! defined(PRINTF_HAS_LF_FORMAT)

/*
 * format_float_1 --- format a single AWKLDBL value according to FORMAT.
 *	The value must be finite.	
 */

static int
format_float_1(char *str, size_t size, const char *format, int fw, int prec, AWKLDBL x)
{
	char alt_format[16];
	size_t len;

	len = strlen(format);

	/* expect %Lf, %LF, %Le, %LE, %Lg or %LG */
	assert(len >= 2 && format[len - 2] == 'L');

	memcpy(alt_format, format, len - 2);
	alt_format[len - 2] = format[len - 1];	/* skip the `L' */ 
	alt_format[len - 1] = '\0';
	return snprintf(str, size, alt_format, fw, prec, (double) x);
}
#else

static inline int
format_float_1(char *str, size_t size, const char *format, int fw, int prec, AWKLDBL x)
{
	return snprintf(str, size, format, fw, prec, x);
}
#endif


#if	defined(GAWK_FMT_INT)

static int format_uint_finite_p(char *str, size_t size, AWKLDBL x);
static AWKLDBL gawk_floorl_finite_p(AWKLDBL x, gawk_uint_t *chunk);

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
		return snprintf(str, size, "%.0f", (double) x);
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
#ifdef HAVE_FLOORL
		intval = floorl(x);
#else
		intval = (AWKLDBL) Floor((double) x);
#endif
	}
	return intval * ((AWKLDBL) sign);
}

#else

static inline int
format_uint_1(char *str, size_t size, AWKLDBL x)
{
	return snprintf(str, size, "%.0Lf", x);
}

/* double_to_int --- convert double to int, used in several places */

static inline AWKLDBL
double_to_int(AWKLDBL x)
{
	return (x >= LDC(0.0)) ? floorl(x) : ceill(x);
}
#endif


#include "long_double.h"
#include "misc/gawk_math.c"

#else	/* ! USE_LONG_DOUBLE */

static bool awkldbl_init(bltin_t **bltins);

numbr_handler_t awkldbl_hndlr = {
	awkldbl_init,
	NULL,
	NULL,
};

/* awkldbl_init --- initialization routine */

static bool
awkldbl_init(bltin_t **bltins)
{
	*bltins = NULL;
	return false;
}
#endif


numbr_handler_t *
get_ldbl_handler(char *arg)
{
#ifdef NUMDEBUG
	extern numbr_handler_t float128_hndlr;
	extern numbr_handler_t float80_hndlr;
	if (arg != NULL && arg[0] == '1')
		return & float128_hndlr;
	if (arg != NULL && arg[0] == '0')
		return & float80_hndlr;
#endif
	return  & awkldbl_hndlr;
}
